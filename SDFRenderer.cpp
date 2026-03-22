#include "SDFRenderer.h"

#include "GraphicsDevice.h"

namespace Carpet {
    SDFRenderer::SDFRenderer(GraphicsDevice& gd)
        : canvasSize(gd.GetWindowSize()), render(gd.CreateNewRender<Vtx>()) {
        distanceMap = Texture2D::New(nullptr, canvasSize, {
            .internalformat = TextureIFormat::RGB_32F, .type = TID::FLOAT,
        });
        heightMap = Texture2D::New(nullptr, canvasSize, {
            .internalformat = TextureIFormat::RGBA_32F, .type = TID::FLOAT,
        });
        fbo = FrameBuffer::New();

        render.UseShader(QShader$(330 core,
            "layout (location = 0) in vec2 position;\n"
            "layout (location = 1) in vec3 uvw;\n"
            "layout (location = 2) in int prim;\n"
            "out vec3 vUVW;\n"
            "flat out int vPrim;"
            "uniform vec2 screenSize;\n"
            "\n"
            "void main() {\n"
            "   gl_Position = vec4(position * 2 / screenSize - 1.0, 1.0, 1.0);\n"
            "   vUVW = uvw;\n"
            "   vPrim = prim;\n"
            "}\n",
            "layout (location = 0) out vec4 glColor;\n"
            "in vec3 vUVW;\n"
            "flat in int vPrim;\n"
            "uniform float strength;\n"
            "\n"
            // returns gradient + distance
            "vec3 sdfCirc(vec2 p, float r) {\n"
            "   float l = length(p);"
            "   return vec3(p / l, (l - 1.0) * r);"
            "}\n"
            ""
            "vec3 SDF(vec3 uvw, int prim) {\n"
            "   switch (prim) {\n"
            "       case 0: return sdfCirc(uvw.xy, uvw.z);\n"
            "       case 1: return vec3(0, 0, uvw.x);\n"
            "   }\n"
            "}\n"
            "\n"
            "void main() {\n"
            "   vec3 sdf = SDF(vUVW, vPrim);\n"
            "   float s = exp(-sdf.z / strength);\n"
            "   glColor = vec4(sdf.xy * s, s, 1.0);"
            "}\n"
        ));
        heightCalcShader = Shader::NewFragment(
            "#version 330 core\n"
            "layout (location = 0) out vec4 glColor;\n"
            "in vec2 vPosition;\n"
            "uniform sampler2D disGraMap;\n"
            "uniform float bevelRadius, strength;\n"
            "void main() {\n"
            "   vec4 d_gra = texture(disGraMap, vPosition);\n"
            "   float d = d_gra.z;\n"
            "   float h = clamp(log(d) * strength, 0, bevelRadius);\n"
            "   float z = sqrt((2 * bevelRadius - h) * h);\n"
            "   vec3 n = vec3(d_gra.xy * ((h - bevelRadius)), d * z);\n"
            "   glColor = vec4(normalize(n), z);\n"
            "}\n"
        );
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

        const float p = r * PADDING;
        const float xs[4] = { rect.max.x + p, rect.max.x - r, rect.min.x + r, rect.min.x - p },
                    ys[4] = { rect.max.y + p, rect.max.y - r, rect.min.y + r, rect.min.y - p };
        static constexpr float UVs[4] = { 1 + PADDING, 0, 0, -1 - PADDING };

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
        auto b = mesh.NewBatch();
        const float p = r * (ROOT_2 * (1 + PADDING));
        static constexpr float U = ROOT_2 * (1 + PADDING);
        b.PushV({ { center.x + p, center.y }, { +U, 0, r }, CIRCLE });
        b.PushV({ { center.x, center.y + p }, { 0, +U, r }, CIRCLE });
        b.PushV({ { center.x - p, center.y }, { -U, 0, r }, CIRCLE });
        b.PushV({ { center.x, center.y - p }, { 0, -U, r }, CIRCLE });
        b.Quad(0, 1, 2, 3);
    }
}
