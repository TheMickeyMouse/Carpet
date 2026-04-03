#pragma once
#include "Common.h"
#include "Mesh.h"
#include "RenderObject.h"
#include "GLs/FrameBuffer.h"
#include "GLs/RenderBuffer.h"
#include "GLs/Texture.h"

namespace Quasi::Graphics {
    class Font;
}

namespace Carpet {
    class GlassRenderer {
        enum SDFType { CIRCLE, FLAT, SDF };
        // circle: uvw stores xy + r,             sdf = (length(UV.xy) - 1) * UV.z
        // box:    uvw stores r,                  sdf = r
        // sdf:    uvw stores xy + r + thickness, sdf = texture(SDF, xy) - 1
        struct Vtx {
            fv2 Position;
            fv3 UVW;
            u32 Prim = 0;
            QuasiDefineVertex$(Vtx, 2D, (Position, Position)(UVW)(Prim));
        };

        FrameBuffer fbo;
        Texture2D distanceMap, heightMap;
        iv2 canvasSize;

        RenderObject<Vtx> render;
        Mesh<Vtx> mesh;
        Shader heightCalcShader, glassShader;

#ifndef NDEBUG
        Shader heightVis;
    public:
        bool debugHeightmap = false, showActualHeight = false;
#endif
    private:
        float strength = 5.0f, padding;
    public:
        Texture2D background, backgroundGlass;
        float eta = 0.667, height = 60.0f, bevelRadius = 20.0f;
        fv3 lightDirection = { 0.48f, 0.36f, 0.8f };
    public:
        GlassRenderer(GraphicsDevice& gd);

        Texture2D& GetHeightmap() { return heightMap; }

        float GetPadding() const;
        void SetSmoothing(float strength);
        float GetSmoothingStrength() const { return strength; }

        void DrawBox(const fRect2D& rect, float r);
        void DrawCirc(const fv2& center, float r);
        void DrawSemiCirc(const fv2& center, const fv2& direction, float r);
        void DrawSegment(const fv2& start, const fv2& end, float r);
        void DrawText(const Font& font, Str text, const fv2& pos, float size, float r);
        void BindFont(const Font& font);

        void Render();
    };
} // Carpet