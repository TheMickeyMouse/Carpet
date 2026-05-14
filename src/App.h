#pragma once
#include "GraphicsDevice.h"
#include "GlassRenderer.h"
#include "TerrainRenderer.h"
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
        TerrainRenderer terrainRenderer;

        fv2 pos = {};
        Rotor2D light = Degrees(60.0f);
        Font font;
        bool showDebug = true;
    public:
        App(const iv2& screenSize);
        bool Run();
    };
}