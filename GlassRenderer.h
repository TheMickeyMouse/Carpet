#pragma once
#include "SDFRenderer.h"
#include "GLs/Texture.h"

namespace Carpet {
    class GlassRenderer {
        SDFRenderer sdfRenderer;
        Shader glassShader;
#ifndef NDEBUG
        Shader heightVis;
    public:
        bool debugHeightmap = false, showActualHeight = false;
    private:
#endif
    public:
        Texture2D background, backgroundGlass;
        float eta = 0.667, height = 60.0f, S = 13.68;
        fv3 lightDirection = { 0.48f, 0.36f, 0.8f };
    public:
        GlassRenderer(GraphicsDevice& gd);

        void SetSmoothing(float strength);
        float GetSmoothingStrength() const;
        void SetBevel(float radius);
        float GetBevelRadius() const;

        void DrawBox(const fRect2D& rect, float r);
        void DrawCirc(const fv2& center, float r);

        void Render();
    };
} // Carpet