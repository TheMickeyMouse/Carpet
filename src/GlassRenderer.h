#pragma once
#include "Common.h"
#include "Mesh.h"
#include "RenderObject.h"
#include "GLs/FrameBuffer.h"
#include "GLs/RenderBuffer.h"
#include "GLs/Texture.h"

namespace Carpet {
    class GlassRenderer {
        enum SDFType { CIRCLE, FLAT };
        // circle: uv is interpreted as xy + r, sdf = (length(UV.xy) - 1) * UV.z
        // box:    uv is interpreted as r,      sdf = r
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

        void Render();
    };
} // Carpet