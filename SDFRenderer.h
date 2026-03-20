#pragma once
#include "Common.h"
#include "Mesh.h"
#include "RenderObject.h"
#include "GLs/FrameBuffer.h"
#include "GLs/RenderBuffer.h"
#include "GLs/Texture.h"

namespace Carpet {
     class SDFRenderer {
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
          Texture2D heightmap;
          RenderBuffer depthBuffer;
          iv2 canvasSize;

          RenderObject<Vtx> render;
          Mesh<Vtx> mesh;
     public:
          float bevelSize = 40.0f;
     public:
          SDFRenderer(GraphicsDevice& gd);

          Texture2D& GetHeightmap() { return heightmap; }

          void Render();

          void DrawBox(const fRect2D& rect, float r);
          void DrawCirc(const fv2& center, float r);
     };
}
