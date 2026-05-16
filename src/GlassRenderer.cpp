#include "GlassRenderer.h"

#include "glp.h"
#include "GraphicsDevice.h"
#include "Fonts/Font.h"
#include "res/Shaders.h"

namespace Carpet {
    GlassRenderer::GlassRenderer(GraphicsDevice& gd)
        : canvasSize(gd.GetWindowSize()), render(gd.CreateNewRender<Vtx>()), padding(GetPadding()) {
        // stores gradient (X, Y), exp distance
        //        in        R  G   B
        distanceMap = Texture2D::New(nullptr, canvasSize, {
            .internalformat = TextureIFormat::RGB_32F, .type = TID::FLOAT,
        });
        heightMap = Texture2D::New(nullptr, canvasSize, {
            .internalformat = TextureIFormat::RGBA_32F, .type = TID::FLOAT,
        });

        background = Texture2D::New(nullptr, canvasSize);
        backgroundGlass[0] = Texture2D::New(nullptr, canvasSize);
        backgroundGlass[1] = Texture2D::New(nullptr, canvasSize);

        fboSDF = FrameBuffer::With(distanceMap);
        fboHeight = FrameBuffer::With(heightMap);

        rboBackground = RenderBuffer::New(TextureIFormat::DEPTH, canvasSize);
        fboBackground[0] = FrameBuffer::New();
        fboBackground[0].Bind();
        fboBackground[0].Attach(rboBackground, AttachmentType::DEPTH);

        fboBackground[1] = FrameBuffer::With(backgroundGlass[1]);

        render->shader = Shader::New(Shaders::SDFCalcVert, Shaders::SDFCalcFrag);

        heightCalcShader = Shader::NewFragment(Shaders::HeightCalcFrag);
        heightCalcShader.Bind();
        heightCalcShader.SetUniformArgs({
            { "disGraMap", distanceMap, SDFMAP }
        });

        glassShader = Shader::NewFragment(Shaders::GlassFrag);
        glassShader.Bind();
        glassShader.SetUniformArgs({
            { "bgPlain",   background,         BACKGROUND },
            { "bgGlass",   backgroundGlass[0], BACKGROUND_GLASS_0 },
            { "heightmap", heightMap,          HEIGHTMAP },
        });
        backgroundGlass[1].Activate(BACKGROUND_GLASS_1);
        GL::ActiveTexture(GL::TEXTURE0);

        gaussBlurShader = Shader::NewFragment(Shaders::GaussBlurFrag);
        gaussBlurShader.Bind();

#ifndef NDEBUG
        heightVis = Shader::NewFragment(Shaders::HeightDebugFrag);
#endif
    }

    float GlassRenderer::GetPadding() const {
        static constexpr float DISCARD_THRESHOLD = 0.01;
        // H = exp(-d / strength); we want to find when this is lower
        // than the discard threshold;

        // threshold = exp(-d / strength);
        // -strength * log(threshold) = d
        return -strength * std::log(DISCARD_THRESHOLD);
    }

    void GlassRenderer::SetSmoothing(float strength) {
        this->strength = strength;
        padding = GetPadding();
    }

    void GlassRenderer::DrawBox(const fRect2D& rect, float r) {
        auto b = mesh.NewBatch();

        const float xs[4] = { rect.max.x + padding, rect.max.x - r, rect.min.x + r, rect.min.x - padding },
                    ys[4] = { rect.max.y + padding, rect.max.y - r, rect.min.y + r, rect.min.y - padding };
        static constexpr float UVs[4] = { 1, 0, 0, -1 };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                b.PushV(Vtx::Circ({ xs[i], ys[j] }, { UVs[i], UVs[j] }, r + padding, r));
            }
        }
        for (const int k : { 0, 1, 2, 4, /* skip middle 5, */ 6, 8, 9, 10 }) {
            b.Quad(k, k + 1, k + 5, k + 4);
        }

        // centerpiece
        b.PushV(Vtx::Flat({ xs[1], ys[1] }, -r)); // 16
        b.PushV(Vtx::Flat({ xs[1], ys[2] }, -r));
        b.PushV(Vtx::Flat({ xs[2], ys[2] }, -r));
        b.PushV(Vtx::Flat({ xs[2], ys[1] }, -r));
        b.Quad(16, 17, 18, 19);
    }

    void GlassRenderer::DrawCirc(const fv2& center, float r) {
        // by rendering an octogon, we waste very little area with low polygons
        // circle:   true area = π = 3.14159..., area waste = 1 - π/area

        // triangle: mesh area = 3√3 = 5.1962..., waste = 39.54%;
        // square:   mesh area = 4,               waste = 21.46%;
        // hexagon:  mesh area = 2√3 = 3.4641..., waste =  9.31%;
        // octagon:     area = 8√2-8 = 3.3137..., waste =  5.19%;
        auto b = mesh.NewBatch();
        static constexpr float U = (ROOT_2 - 1.0f);
        const float R = r + padding, S = R * U;
        b.PushV(Vtx::Circ({ center.x - S, center.y + R }, { -U, +1 }, r + padding, r));
        b.PushV(Vtx::Circ({ center.x + S, center.y + R }, { +U, +1 }, r + padding, r));
        b.PushV(Vtx::Circ({ center.x + R, center.y + S }, { +1, +U }, r + padding, r));
        b.PushV(Vtx::Circ({ center.x + R, center.y - S }, { +1, -U }, r + padding, r));
        b.PushV(Vtx::Circ({ center.x + S, center.y - R }, { +U, -1 }, r + padding, r));
        b.PushV(Vtx::Circ({ center.x - S, center.y - R }, { -U, -1 }, r + padding, r));
        b.PushV(Vtx::Circ({ center.x - R, center.y - S }, { -1, -U }, r + padding, r));
        b.PushV(Vtx::Circ({ center.x - R, center.y + S }, { -1, +U }, r + padding, r));
        b.TriFan((const u32[]) { 0, 1, 2, 3, 4, 5, 6, 7 });
    }

    void GlassRenderer::DrawSemiCirc(const fv2& center, const fv2& direction, float r) {
        auto b = mesh.NewBatch();
        static constexpr float U = ROOT_2 - 1.0f;

        const float R = r + padding;
        for (const fv2 z : (const fv2[]) { { 0, 1 }, { U, 1 }, { 1, U } }) {
            const fv2 P = direction.ComplexMul(z), Q = direction.ComplexMul({ z.x, -z.y });
            b.PushV(Vtx::Circ(center + P * R, P, R, r));
            b.PushV(Vtx::Circ(center + Q * R, Q, R, r));
        }
        b.TriFan((const u32[]) { 0, 2, 4, 5, 3, 1 });
    }

    void GlassRenderer::DrawSegment(const fv2& start, const fv2& end, float r) {
        const fv2 N = (end - start).Norm(), T = N.Perpend(), X = T * (r + padding);

        DrawSemiCirc(start, -N, r);
        DrawSemiCirc(end,    N, r);
        auto b = mesh.NewBatch();
        b.PushV(Vtx::Circ(start + X,  T, r + padding, r));
        b.PushV(Vtx::Circ(end   + X,  T, r + padding, r));
        b.PushV(Vtx::Circ(end   - X, -T, r + padding, r));
        b.PushV(Vtx::Circ(start - X, -T, r + padding, r));
        b.Quad(0, 1, 2, 3);
    }

    void GlassRenderer::DrawText(const Font& font, Str text, const fv2& pos, float size, float r) {
        const float pointScale = size / (float)font.FontSize();
        const float relativeFontSize = pointScale * 64.0f;
        const float w = font.CalcTextWidth(text) * relativeFontSize;

        const Texture2D& fontAtlas = font.GetTexture();
        auto batch = mesh.NewBatch();

        // from freetype
        const float R = 2 * (FontDevice::SPREAD) * relativeFontSize;
        const float thickness = r * 0.5f / R;

        // idk why but this makes the glass look better. help.
        // you might have to change this depending on the font.
        static constexpr float H_SCALE = 1.8f;

        fv2 pen = pos - fv2 { w / 2.0f, (float)font.GetMetric().descend * pointScale };
        for (const char c : text) {
            if (Chr::IsWhitespace(c)) {
                pen.x += font.GetGlyphRect(' ').advance.x * relativeFontSize;
                continue;
            }
            const Glyph& glyph = font.GetGlyphRect(c);
            const fv2 rsize  = glyph.rect.Size() * (fv2)fontAtlas.Size(); // real-scale size of the quad
            const fRect2D uv = glyph.rect;
            const fv2 start = (fv2)glyph.offset * relativeFontSize + pen,
                      dim   = rsize * relativeFontSize;

            batch.PushV(Vtx::TexSDF(start,                      uv.BottomLeft(),  R * H_SCALE, thickness));
            batch.PushV(Vtx::TexSDF(start + fv2(dim.x, 0),      uv.BottomRight(), R * H_SCALE, thickness));
            batch.PushV(Vtx::TexSDF(start + fv2(dim.x, -dim.y), uv.TopRight(),    R * H_SCALE, thickness));
            batch.PushV(Vtx::TexSDF(start + fv2(0,     -dim.y), uv.TopLeft(),     R * H_SCALE, thickness));
            batch.Quad(0, 1, 2, 3);
            batch.Reload();

            pen.x += (float)glyph.advance.x * relativeFontSize;
        }
    }

    void GlassRenderer::BindFont(const Font& font) {
        render->shader.Bind();
        render->shader.SetUniformTex("fontSDF", font.GetTexture(), FONT_SDF);
    }

    void GlassRenderer::Render() {
        // use additive rendering for heightmap; no need for alpha blending
        Render::UseBlendFunc(BlendFactor::ONE, BlendFactor::ONE);

        fboSDF.BindDrawDest();
        Render::SetClearColor({ 0, 0 });
        // Render::EnableStencil();
        Render::Clear();

        // Render::UseStencilTest(CmpOperation::ALWAYS, 1);
        // Render::UseStencilWriteOp(StencilOperation::REPLACE);
        // Render::EnableStencilWrite();
        render.Draw(Spans::Only(mesh), {
            .arguments = {
                { "screenSize", fv2 { 1920, 1080 } },
                { "strength",   strength },
                { "bevelRadius", bevelRadius }
            },
            .useDefaultArguments = false
        });

        fboHeight.BindDrawDest();
        Render::DisableBlend();
        heightCalcShader.Bind();
        heightCalcShader.SetUniformFloat("bevelRadius", bevelRadius);
        heightCalcShader.SetUniformFloat("strength", strength);

        // Render::UseStencilTest(CmpOperation::EQUAL, 1);
        // Render::UseStencilWriteOp(StencilOperation::KEEP);
        // Render::DisableStencilWrite();
        Render::DrawScreenQuad(heightCalcShader);

        FrameBuffer::UnbindDrawDest();
        // Render::DisableStencil();

        mesh.Clear();

        Render::EnableBlend();
        Render::UseBlendFunc(BlendFactor::ONE, BlendFactor::INVERT_SRC_ALPHA);
        Render::EnableDepth();

#ifndef NDEBUG
        if (debugHeightmap) {
            heightVis.Bind();
            heightVis.SetUniformArgs({
                { "heightmap",        HEIGHTMAP },
                { "bevelRadius",      bevelRadius },
                { "showActualHeight", showActualHeight }
            });
            Render::DrawScreenQuad(heightVis);
            return;
        }
#endif

        glassShader.Bind();
        glassShader.SetUniformArgs({
            { "lightSource", lightDirection },
            { "screenSize",  (fv2)canvasSize },
            { "eta",         eta },
            { "height",      height },
            { "bevelRadius", bevelRadius },
            { "glassTint",   glassTint },
            { "dropShadowRadius", dropShadowRadius },
            { "dropShadowPow",    dropShadowPow },
            { "mainShadowDist",   mainShadowDist },
            { "mainShadowPow",    mainShadowPow }
        });
        // glassShader.SetUniformFloat("maxZ", renderer.bevelSize);
        Render::DrawScreenQuad(glassShader);
    }

    void GlassRenderer::BeginBackground() {
        fboBackground[0].Bind();
        fboBackground[0].Attach(background);
    }

    void GlassRenderer::EndBackground() {
        Render::DisableDepth();

        {
            fboBackground[1].Bind();
            gaussBlurShader.Bind();
            gaussBlurShader.SetUniformInt("image", BACKGROUND);
            gaussBlurShader.SetUniformFv2("offsetDir", { 5, 0 });
            Render::DrawScreenQuad(gaussBlurShader);

            fboBackground[0].Bind();
            fboBackground[0].Attach(backgroundGlass[0]);
            gaussBlurShader.SetUniformInt("image", BACKGROUND_GLASS_1);
            gaussBlurShader.SetUniformFv2("offsetDir", { 0, 5 });
            Render::DrawScreenQuad(gaussBlurShader);

            fboBackground[1].Bind();
            gaussBlurShader.SetUniformInt("image", BACKGROUND_GLASS_0);
            gaussBlurShader.SetUniformFv2("offsetDir", { 1, 0 });
            Render::DrawScreenQuad(gaussBlurShader);

            fboBackground[0].Bind();
            gaussBlurShader.SetUniformInt("image", BACKGROUND_GLASS_1);
            gaussBlurShader.SetUniformFv2("offsetDir", { 0, 1 });
            Render::DrawScreenQuad(gaussBlurShader);
        }
    }
} // Carpet