#include "GlassRenderer.h"

#include "GraphicsDevice.h"

namespace Carpet {
    GlassRenderer::GlassRenderer(GraphicsDevice& gd)
        : canvasSize(gd.GetWindowSize()), render(gd.CreateNewRender<Vtx>()), padding(GetPadding()) {
        // stores gradient (X,656 Y), exp distance
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
            uniform float strength, bevelRadius;

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
               float s = exp(min(-sdf.z / strength, bevelRadius));
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

        glassShader = Shader::NewFragment(R"(
#version 330 core
layout (location = 0) out vec4 glColor;
in vec2 vPosition;
uniform sampler2D heightmap, bgPlain, bgGlass;
uniform vec3 lightSource;
uniform vec2 screenSize;
uniform float eta, height, bevelRadius, S;

float lumi(vec3 col) {
    return dot(col, vec3(0.2126, 0.7152, 0.0722));
}
// All components are in the range [0…1], including hue.
vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}
// All components are in the range [0…1], including hue.
vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec4 h = texture(heightmap, vPosition);
    if (h.w == 0.0) {
        vec3 result = texture(bgPlain, vPosition).rgb;

        float w = texture(heightmap, vPosition + lightSource.xy / screenSize * (bevelRadius / lightSource.z)).w / bevelRadius;
        const float gamma = 2.2;
        result = pow(pow(result, vec3(1 / gamma)) - 0.5 * smoothstep(0, 1, 0.4 * w * w), vec3(gamma));

        glColor = vec4(result, 1.0);
        return;
    }

    vec3 pos = vec3(vPosition * screenSize, h.w);
    vec3 dir = refract(vec3(0, 0, -1), h.xyz, eta);

    float raylen = (pos.z + height) / -dir.z;
    vec3 hit = pos + raylen * dir;

    vec3 result = texture(bgGlass, hit.xy / screenSize).xyz;
    float L = -cos(3.1415926 * dot(h.xy, normalize(lightSource.xy)));
    float lum = lumi(result), light = (0.8 + L) * 0.15;
    float glare = (1 + L) * pow(max(0.001, 1 - h.z * h.z), bevelRadius / 3.0f);
    result *= 0.7 + 0.5 * lum + (0.1 + light) * sqrt(max(0.0001, light) + 0.05) * 1.3 * (4.0 - 2.7 * lum);
    result += hsv2rgb(rgb2hsv(result) * vec3(1.0, 1.0 + 0.32 * glare - 0.6 * lum, 1.2)) * (0.2 * glare / lum);
    glColor = vec4(result, 1.0);
})");

#ifndef NDEBUG
        heightVis = Shader::NewFragment(R"(
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

    void GlassRenderer::DrawCirc(const fv2& center, float r) {
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
            // { "S", S }
        });
        // glassShader.SetUniformFloat("maxZ", renderer.bevelSize);
        Render::DrawScreenQuad(glassShader);
    }
} // Carpet