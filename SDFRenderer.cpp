#include "SDFRenderer.h"

#include "GraphicsDevice.h"

namespace Carpet {
    SDFRenderer::SDFRenderer(GraphicsDevice& gd)
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

        render.UseShader(QShader$(330 core, R"(
            layout (location = 0) in vec2 position;
            layout (location = 1) in vec3 uvw;
            layout (location = 2) in int prim;
            out vec3 vUVW;
            flat out int vPrim;
            uniform vec2 screenSize;

            void main() {
               gl_Position = vec4(position * 2 / screenSize - 1.0, 1.0, 1.0);
               vUVW = uvw;
               vPrim = prim;
            }
        )", R"(
            layout (location = 0) out vec4 glColor;
            in vec3 vUVW;
            flat in int vPrim;
            uniform float strength;

            // returns gradient + distance
            vec3 sdfCirc(vec2 p, float r) {
               float l = length(p);
               return vec3(p / l, (l - 1.0) * r);
            }
            vec3 SDF(vec3 uvw, int prim) {
               switch (prim) {
                   case 0: return sdfCirc(uvw.xy, uvw.z);
                   case 1: return vec3(0, 0, uvw.x);
               }
            }

            void main() {
               vec3 sdf = SDF(vUVW, vPrim);
               float s = exp(min(-sdf.z / strength, 20.0));
               glColor = vec4(sdf.xy * s, s, -sdf.z);
            }
        )"));
        heightCalcShader = Shader::NewFragment(R"(
            #version 330 core
            layout (location = 0) out vec4 glColor;
            in vec2 vPosition;
            uniform sampler2D disGraMap;
            uniform float bevelRadius, strength;
            void main() {
               vec4 d_gra = texture(disGraMap, vPosition);
               float d = d_gra.z;
               float h = clamp(log(d) * strength, 0, bevelRadius);
               float z = sqrt((2 * bevelRadius - h) * h);
               vec3 n = vec3(d_gra.xy * (bevelRadius - h), d * z);
               glColor = z > 0.0 ? vec4(normalize(n), z) : vec4(0.0, 0.0, 1.0, 0.0);
            }
        )");
    }

    float SDFRenderer::GetPadding() const {
        static constexpr float DISCARD_THRESHOLD = 0.01;
        // H = exp(-d / strength); we want to find when this is lower
        // than the discard threshold;

        // threshold = exp(-d / strength);
        // -strength * log(threshold) = d
        return -strength * std::log(DISCARD_THRESHOLD);
    }

    void SDFRenderer::SetSmoothing(float strength) {
        this->strength = strength;
        padding = GetPadding();
    }

    void SDFRenderer::Render() {
        // use additive rendering; no need for alpha blending
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
                { "strength",   strength }
                // { "extrudeZ",   bevelSize },
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
    }

    void SDFRenderer::DrawBox(const fRect2D& rect, float r) {
        auto b = mesh.NewBatch();

        const float p = padding / r;
        const float xs[4] = { rect.max.x + padding, rect.max.x - r, rect.min.x + r, rect.min.x - padding },
                    ys[4] = { rect.max.y + padding, rect.max.y - r, rect.min.y + r, rect.min.y - padding };
        const float UVs[4] = { 1 + p, 0, 0, -1 - p };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                b.PushV({ { xs[i], ys[j] }, { UVs[i], UVs[j], r }, CIRCLE });
            }
        }
        for (const int k : { 0, 1, 2, 4, /* skip middle 5, */ 6, 8, 9, 10 }) {
            b.Quad(k, k + 1, k + 5, k + 4);
        }

        // centerpiece
        b.PushV({ { xs[1], ys[1] }, { -r, 0, 0 }, FLAT }); // 16
        b.PushV({ { xs[1], ys[2] }, { -r, 0, 0 }, FLAT });
        b.PushV({ { xs[2], ys[2] }, { -r, 0, 0 }, FLAT });
        b.PushV({ { xs[2], ys[1] }, { -r, 0, 0 }, FLAT });
        b.Quad(16, 17, 18, 19);
    }

    void SDFRenderer::DrawCirc(const fv2& center, float r) {
        // by rendering an octogon, we waste very little area with low polygons
        // circle:   true area = π = 3.14159..., area waste = 1 - π/area

        // triangle: mesh area = 3√3 = 5.1962..., waste = 39.54%;
        // square:   mesh area = 4,               waste = 21.46%;
        // hexagon:  mesh area = 2√3 = 3.4641..., waste =  9.31%;
        // octagon:     area = 8√2-8 = 3.3137..., waste =  5.19%;
        auto b = mesh.NewBatch();
        const float R = r + padding, S = R * (ROOT_2 - 1.0f),
                    U = R / r, V = U * (ROOT_2 - 1.0f);
        b.PushV({ { center.x - S, center.y + R }, { -V, +U, r }, CIRCLE });
        b.PushV({ { center.x + S, center.y + R }, { +V, +U, r }, CIRCLE });
        b.PushV({ { center.x + R, center.y + S }, { +U, +V, r }, CIRCLE });
        b.PushV({ { center.x + R, center.y - S }, { +U, -V, r }, CIRCLE });
        b.PushV({ { center.x + S, center.y - R }, { +V, -U, r }, CIRCLE });
        b.PushV({ { center.x - S, center.y - R }, { -V, -U, r }, CIRCLE });
        b.PushV({ { center.x - R, center.y - S }, { -U, -V, r }, CIRCLE });
        b.PushV({ { center.x - R, center.y + S }, { -U, +V, r }, CIRCLE });
        b.TriFan((const u32[]) { 0, 1, 2, 3, 4, 5, 6, 7 });
    }
}
