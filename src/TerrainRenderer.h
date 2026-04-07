#pragma once
#include "Common.h"
#include "Mesh.h"
#include "RenderObject.h"
#include "GLs/Shader.h"

namespace Carpet {
    class TerrainRenderer {
        struct Vtx {
            fv3 Position;
            uColor Color;

            QuasiDefineVertex$(Vtx, 3D, (Position, Position)(Color));
        };

        RenderObject<Vtx> render;
        Mesh<Vtx> terrain;
        fv2 focusPosition = 0.5f;
    public:
        float fogFalloff = 0.004;
        fColor3 fogBlue = { 0.041, 0.114, 0.280 }, fogYellow = { 1.0, 0.935, 0.750 };
        fv3 lightSource = { 1.2, 0.55, 3.45 }, cameraSource = { 4.379, 3.8, -3.12 };
        float zOffset = 0.0, xOffset = 0.0f, yOffset = 0.24f;
        float steepness = 3.5f, slopeZ = 0.034f;
    public:
        TerrainRenderer(GraphicsDevice& gd);

        void SetupTerrain(Span<const fColor> colors, int layers);
        void Render(GraphicsDevice& gd);
    };
}
