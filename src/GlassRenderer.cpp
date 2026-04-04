#include "GlassRenderer.h"

#include "GraphicsDevice.h"
#include "Fonts/Font.h"

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
        fbo = FrameBuffer::New();

#pragma region Shaders
        // language=GLSL
        render->shader = Shader::New(
// vertex
R"(
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec2 rs;
layout (location = 3) in int prim;
out vec4 vUVs;
flat out int vPrim;
uniform vec2 screenSize;

void main() {
   gl_Position = vec4(position * 2 / screenSize - 1.0, 1.0, 1.0);
   vUVs = vec4(uv, rs);
   vPrim = prim;
}
)",
// fragment
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec4 vUVs;
flat in int vPrim;
uniform float strength, bevelRadius;
uniform sampler2D fontSDF;

// returns gradient + distance
vec3 sdfCirc(vec2 p, float r, float t) {
    float l = length(p);
    return vec3(p / l, l * r - t);
}
vec3 sdfTex(vec2 coords, float r, float t) {
    float h = (max(-texture(fontSDF, coords).r + 0.5, -t) - t) * r;
    // smoother version:
    // vec2 dx = dFdx(coords), dy = dFdy(coords);
    // vec2 grad = vec2(texture(fontSDF, coords - dx).r - texture(fontSDF, coords + dx).r,
    //                  texture(fontSDF, coords - dy).r - texture(fontSDF, coords + dy).r);
    vec2 grad = vec2(dFdx(h), dFdy(h));
    return vec3(grad, h);
}
vec3 SDF(vec4 uv, int prim) {
    switch (prim) {
        case 0: return sdfCirc(2 * uv.xy - 1, uv.z, uv.w);
        case 1: return vec3(0, 0, uv.z);
        case 2: return sdfTex(uv.xy, uv.z, uv.w);
        default: return vec3(0);
    }
}

void main() {
    vec3 sdf = SDF(vUVs, vPrim);
    float s = exp(min(-sdf.z / strength, bevelRadius));
    glColor = vec4(sdf.xy * s, s, -sdf.z);
})");

/*
 * calculating new gradient:
 * given H(x, y) = h(g(f(x, y))) where f: R^3 -> R, g(x) = -ln(x) * strength
 * then grad H = grad (g comp f) * h'(g comp f)
 *             = (grad f * g'(f)) * h'(g comp f)
 * if d = f(x, y) and G = grad f(x, y), z = -ln(d) * s, and h'(x) = p(x)/q(x)
 * then grad H = G * g'(d) * h'(g(d))
 *             = G * -s/d * h'(-ln(x) * s);
 *             = (N * p(z)) / (d * q(z))
 *             (we can set G * s = N because in the render shader we store N instead of G)
 *       and H = h(-ln(x) * s) = h(z);
 *
 *       which means we control p(z), q(z) and h(z) to our needs.
 */

/*  useful h functions:
 *  (to find one, first use a simple function, take its derivative and separate the numerator and denom.)
 *  return value is in (p, q, h) where p/q = h' and h is the actual result
 *
 *  - circular:
 *      vec3 height(float z) {
 *          z = clamp(z, 0, bevelRadius);
 *          float H = sqrt((2 * bevelRadius - z) * z);
 *          return vec3(bevelRadius - H, H, H);
 *      }
 *      // pros: simple, cons: non C2 continuous, lighting artefacts may appear
 *  - squricle:
 *      vec3 height(float z) {
 *          z = 1 - clamp(z / bevelRadius, 0, 1);
 *          float z3 = z * z * z, H4 = 1 - z3 * z, H = sqrt(sqrt(H4));
 *          return vec3(z3 * H, H4, bevelRadius * H);
 *      }
 *      // pros: C2 continuous, cons: slow
 */

        heightCalcShader = Shader::NewFragment(
// language=GLSL
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D disGraMap;
uniform float bevelRadius, strength;

// returns h' in form of p/q, and h itself
vec3 height(float z) {
    z = 1 - clamp(z / bevelRadius, 0, 1);
    float z3 = z * z * z, H4 = 1 - z3 * z, H = sqrt(sqrt(H4));
    return vec3(z3 * H, H4, bevelRadius * H);
}

void main() {
    // !! DO NOT CHANGE THIS PART (expect height(z)) !!
    vec3 d_gra = texture(disGraMap, vPosition).xyz;
    float d = d_gra.z, z = log(d) * strength;
    vec3 h = height(z);
    vec3 n = vec3(d_gra.xy * h.x, d * h.y);
    glColor = vec4(normalize(n), h.z);
}
)");

        glassShader = Shader::NewFragment(
            // language=GLSL
            R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap, bgPlain, bgGlass;
uniform vec3 lightSource;
uniform vec2 screenSize;
uniform float eta, height, bevelRadius;
uniform vec4 glassTint;

float lumi(vec3 col) {
    return dot(col, vec3(0.2126, 0.7152, 0.0722));
}
// All components are in the range [0…1], including hue.
vec3 rgb2hsv(vec3 c) {
    const vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = c.g < c.b ? vec4(c.bg, K.wz) : vec4(c.gb, K.xy);
    vec4 q = c.r < p.x ? vec4(p.xyw, c.r) : vec4(c.r, p.yzx);

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}
// All components are in the range [0…1], including hue.
vec3 hsv2rgb(vec3 c) {
    const vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec4 h = texture(heightmap, vPosition);
    if (h.w == 0.0) {
        vec3 result = texture(bgPlain, vPosition).rgb;

        float w = texture(heightmap, vPosition + lightSource.xy / screenSize * (bevelRadius / lightSource.z)).w / bevelRadius;
        result *= 1 - smoothstep(0, 1, 0.4 * w * w) * 0.5;

        glColor = vec4(result, 1.0);
        return;
    }

    vec3 pos = vec3(vPosition * screenSize, h.w);
    pos.xy /= screenSize;
    pos.z += height;

    vec3 dirR = refract(vec3(0, 0, -1), h.xyz, eta * 1.15),
         dirG = refract(vec3(0, 0, -1), h.xyz, eta),
         dirB = refract(vec3(0, 0, -1), h.xyz, eta * 0.87);

    vec3 result = vec3(
        texture(bgGlass, pos.xy - dirR.xy / screenSize * (pos.z / dirR.z)).r,
        texture(bgGlass, pos.xy - dirG.xy / screenSize * (pos.z / dirG.z)).g,
        texture(bgGlass, pos.xy - dirB.xy / screenSize * (pos.z / dirB.z)).b
    );

    result = result * mix(vec3(1), glassTint.rgb, glassTint.a);

    float L = -cos(3.1415926 * dot(h.xy, normalize(lightSource.xy)));
    float lum = lumi(result), light = (0.8 + L) * 0.2, invlum = 1 / sqrt(lum + 0.01);
    float glare = (1 + L) * pow(max(0.001, 1 - h.z * h.z), bevelRadius / 3.0f);

    result *= 1.04 + light * invlum;
    vec3 hsv = rgb2hsv(result);
    result = hsv2rgb(hsv * vec3(1.0, 1.25, 1.0));
    result += (0.25 * glare * invlum) * hsv2rgb(vec3(hsv.x, hsv.y * 0.4, hsv.z));

    glColor = vec4(result, 1.0);
})");

#ifndef NDEBUG
        heightVis = Shader::NewFragment(
// language=GLSL
R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap;
uniform float bevelRadius;
uniform int showActualHeight;

void main() {
    vec4 h = texture(heightmap, vPosition);
    glColor = h.w == 0 ? vec4(0.0) : showActualHeight == 1 ? vec4(h.w / bevelRadius) : vec4(h.xyz * 0.5 + 0.5, h.w / bevelRadius);
}
)");
#endif
#pragma endregion
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
        fv2 N = (end - start).Norm(), T = N.Perpend(), X = T * (r + padding);

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

            batch.PushV(Vtx::TexSDF(start,                      uv.BottomLeft(),  R, thickness));
            batch.PushV(Vtx::TexSDF(start + fv2(dim.x, 0),      uv.BottomRight(), R, thickness));
            batch.PushV(Vtx::TexSDF(start + fv2(dim.x, -dim.y), uv.TopRight(),    R, thickness));
            batch.PushV(Vtx::TexSDF(start + fv2(0,     -dim.y), uv.TopLeft(),     R, thickness));
            batch.Quad(0, 1, 2, 3);
            batch.Reload();

            pen.x += (float)glyph.advance.x * relativeFontSize;
        }
    }

    void GlassRenderer::BindFont(const Font& font) {
        static constexpr int SDF_ACTIVATE_ID = 8;
        render->shader.Bind();
        render->shader.SetUniformTex("fontSDF", font.GetTexture(), SDF_ACTIVATE_ID);
    }

    void GlassRenderer::Render() {
        // use additive rendering for heightmap; no need for alpha blending
        Render::UseBlendFunc(BlendFactor::ONE, BlendFactor::ONE);
        Render::DisableDepth();

        fbo.Bind();
        fbo.Attach(distanceMap);
        fbo.BindDrawDest();
        Render::SetClearColor({ 0, 0 });
        Render::Clear();
        render.Draw(Spans::Only(mesh), {
            .arguments = {
                { "screenSize", (fv2)canvasSize },
                { "strength",   strength },
                { "bevelRadius", bevelRadius }
            },
            .useDefaultArguments = false
        });

        fbo.Bind();
        fbo.Attach(heightMap);
        fbo.BindDrawDest();
        Render::Clear();
        heightCalcShader.Bind();
        heightCalcShader.SetUniformFloat("bevelRadius", bevelRadius);
        heightCalcShader.SetUniformFloat("strength", strength);
        heightCalcShader.SetUniformTex("disGraMap", distanceMap, 0);
        Render::DrawScreenQuad(heightCalcShader);
        fbo.Unbind();

        mesh.Clear();

        Render::UseBlendFunc(BlendFactor::SRC_ALPHA, BlendFactor::INVERT_SRC_ALPHA);
        Render::EnableDepth();

#ifndef NDEBUG
        if (debugHeightmap) {
            heightVis.Bind();
            heightVis.SetUniformArgs({
                { "heightmap",        heightMap, 0 },
                { "bevelRadius",      bevelRadius },
                { "showActualHeight", showActualHeight }
            });
            Render::DrawScreenQuad(heightVis);
            return;
        }
#endif

        glassShader.Bind();
        glassShader.SetUniformArgs({
            { "heightmap",   heightMap, 0 },
            { "bgPlain",     background,      1 },
            { "bgGlass",     backgroundGlass, 2 },
            { "lightSource", lightDirection },
            { "screenSize",  (fv2)canvasSize },
            { "eta",         eta },
            { "height",      height },
            { "bevelRadius", bevelRadius },
            { "glassTint",   glassTint }
            // { "S", S }
        });
        // glassShader.SetUniformFloat("maxZ", renderer.bevelSize);
        Render::DrawScreenQuad(glassShader);
    }
} // Carpet