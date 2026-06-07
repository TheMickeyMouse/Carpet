#pragma once
#include "El.h"

namespace Carpet {
    class UIDoc {
    public:
        El root;
        fv2 dimensions = { 1920, 1080 };

        void ComputeLayouts();
        void Draw(Canvas& canvas);
        void DrawGlass(GlassRenderer& glass);

        bool Compile(Str src, OptRef<Debug::Logger> logger = nullptr);
    };
}
