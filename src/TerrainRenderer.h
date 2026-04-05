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
    public:
        TerrainRenderer(GraphicsDevice& gd);

        void SetupTerrain(Span<const fColor> colors, int layers);
        void Render(GraphicsDevice& gd);
    };
}
