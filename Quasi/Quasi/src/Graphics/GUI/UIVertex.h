#pragma once
#include "../GLs/VertexElement.h"
#include "Utils/Math/Color.h"

namespace Quasi::Graphics {
    struct UIVertex {
        Math::fv2 Position;
        Math::fv2 TexCoord;
        Math::uColor Color;
        Math::fv4 STUV;
        u32 RenderPrim = 0;

        QuasiDefineVertex$(UIVertex, 2D, (Position, Position)(TexCoord)(Color)(STUV)(RenderPrim))
    };

    namespace UIRender {
        enum RenderPrimitive {
            PLAIN  = 0, // flat triangles
            CIRCLE = 1, // circles
            ARC    = 2, // defines a inner radius
            QBEZ   = 3, // quadratic bezier
            CBEZ   = 4, // cubic bezier
            RADIAL = 5, // a radial glow object
            SDF    = 6, // an sdf texture

            PRIMITIVE_TYPE = 0x7,
            INVERT = 0x8,

            TEXTURE_ID_MASK = 0xF0,
            TEXTURE_ID = 0x10,

            SDF_ID_MASK = 0xF00,
            SDF_ID = 0x100,
        };

        enum RenderStyle {
            ROUND_CAP  = 0x0,
            SQUARE_CAP = 0x1,
            ARROW_CAP  = 0x2,
            FLAT_CAP   = 0x3,
            CAP_MASK   = 0xF,

            ROUND_JOIN = 0x00,
            MITER_JOIN = 0x10,
            BEVEL_JOIN = 0x20,
            JOIN_MASK  = 0xF0,

            NO_FILL    = 0x100,
            NO_STROKE  = 0x200,
            NO_RENDER  = NO_FILL | NO_STROKE
        };
    }
}
