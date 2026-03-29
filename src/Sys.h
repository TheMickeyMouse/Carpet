#pragma once
#include "Utils/Math/Vector.h"

namespace Quasi::Graphics {
    class GraphicsDevice;
}

namespace Sys {
    using namespace Quasi;
    void FetchProgman();
    void PrepareBgWindow(Graphics::GraphicsDevice& gd);
    Math::iv2 GetMonitorSize();
}
