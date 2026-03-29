#pragma once
#include "GraphicsDevice.h"
#include "GlassRenderer.h"
#include "GUI/Canvas.h"

using namespace Quasi;

namespace Carpet {
    class App {
    public:
        inline static OptRef<App> Instance = nullptr;
    private:
        GraphicsDevice gdevice;
        Canvas canvas;
        GlassRenderer glassRenderer;

        fv2 pos = {};
        Rotor2D light = Degrees(60.0f);
    public:
        App();
        bool Run();
    };
}