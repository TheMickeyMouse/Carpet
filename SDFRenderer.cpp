#include "SDFRenderer.h"

#include "GraphicsDevice.h"

namespace Carpet {
    SDFRenderer::SDFRenderer(GraphicsDevice& gd)
        : canvasSize(gd.GetWindowSize()), render(gd.CreateNewRender<Vtx>()) {
        heightmap = Texture2D::New(nullptr, canvasSize, {
            .internalformat = TextureIFormat::RGBA_32F, .type = TID::FLOAT,
        });
        depthBuffer = RenderBuffer::New(TextureIFormat::DEPTH_32F, canvasSize);
        fbo = FrameBuffer::New();
        fbo.Bind();
        fbo.Attach(heightmap);
        fbo.Attach(depthBuffer, AttachmentType::DEPTH);
        fbo.Complete();

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
            "uniform float extrudeZ;\n"
            "\n"
            // returns gradient in homogenous + distance
            "vec4 sdfCirc(vec2 p, float r) {\n"
            "   float l = length(p);"
            "   return vec4(p, l, (l - 1.0) * r);"
            "}\n"
            ""
            "vec4 SDF(vec3 uvw, int prim) {\n"
            "   switch (prim) {\n"
            "       case 0: return sdfCirc(uvw.xy, uvw.z);\n"
            "       case 1: return vec4(0, 0, 1, uvw.x);\n"
            "   }\n"
            "}\n"
            // returns dx, z, dz
            "vec3 profile(float dist) {"
            "   float d = clamp(1 + dist / extrudeZ, 0, 1), y = sqrt(1 - d * d);"
            "   return vec3(d, y * extrudeZ, y);"
            "}"
            "\n"
            "void main() {\n"
            "   vec4 sdf = SDF(vUVW, vPrim);\n"
            "   vec3 hzx = profile(sdf.w);\n"
            "   vec4 hmap = vec4(normalize(vec3(hzx.x * sdf.xy, hzx.z * sdf.z)), hzx.y);\n"
            "   glColor = hmap;"
            "}\n"
        ));
    }

    void SDFRenderer::Render() {
        // use additive rendering; no need for alpha blending
        Render::UseBlendEqSeparate(BlendOp::ADD, BlendOp::MAX);
        Render::UseBlendFunc(BlendFactor::INVERT_DST_ALPHA, BlendFactor::DST_ALPHA);

        fbo.BindDrawDest();
        Render::SetClearColor({ 0, 0 });
        Render::Clear();
        render.Draw(Spans::Only(mesh), {
            .arguments = {
                { "screenSize", (fv2)canvasSize },
                { "extrudeZ",   bevelSize }
            },
            .useDefaultArguments = false
        });
        fbo.UnbindDrawDest();

        mesh.Clear();

        Render::UseBlendEq(BlendOp::ADD);
        Render::UseBlendFunc(BlendFactor::SRC_ALPHA, BlendFactor::INVERT_SRC_ALPHA);
    }

    void SDFRenderer::DrawBox(const fRect2D& rect, float r) {
        auto b = mesh.NewBatch();
        const float xs[4] = { rect.max.x, rect.max.x - r, rect.min.x + r, rect.min.x },
                    ys[4] = { rect.max.y, rect.max.y - r, rect.min.y + r, rect.min.y };
        static constexpr float UVs[4] = { +1, 0, 0, -1 };
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
        b.PushV({ { center.x + r, center.y + r }, { +1, +1, r }, CIRCLE });
        b.PushV({ { center.x + r, center.y - r }, { +1, -1, r }, CIRCLE });
        b.PushV({ { center.x - r, center.y - r }, { -1, -1, r }, CIRCLE });
        b.PushV({ { center.x - r, center.y + r }, { -1, +1, r }, CIRCLE });
        b.Quad(0, 1, 2, 3);
    }
}
