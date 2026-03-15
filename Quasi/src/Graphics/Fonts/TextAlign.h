#pragma once
#include "Font.h"

namespace Quasi::Graphics {
    struct Glyph;

    struct TextAlign {
        enum AlignOptions {
            LEFT    = 1 << 0,
            RIGHT   = 1 << 1,
            JUSTIFY = LEFT | RIGHT,
            CENTER  = 0,
            ALIGN_MASK = LEFT | RIGHT,

            VTOP     = 1 << 2,
            VBOTTOM  = 1 << 3,
            VCENTER  = 0,
            VMASK    = VTOP | VBOTTOM,

            WORD_WRAP = 1 << 4,

            DEFAULT = 0
        };

        int alignment = DEFAULT;
        Math::fv2 rect = { f32s::INFINITY, 0 };
        float letterSpacing = 0; // this is extra offset
        float lineSpacing = 1; // this is a multiplier

        float GetAdvance(const Glyph& glyph, float scaleRatio) const {
            return glyph.advance.x * scaleRatio + letterSpacing;
        }
    };
}
