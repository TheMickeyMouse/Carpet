#pragma once
#include "GraphicsDevice.h"
#include "SDFRenderer.h"
#include "GUI/Canvas.h"

using namespace Quasi;

namespace Carpet {
    class App {
    public:
        inline static OptRef<App> Instance = nullptr;
    private:
        GraphicsDevice gdevice;
        Canvas canvas;

        Texture2D background, backgroundGlass;
        SDFRenderer renderer;
        Shader glassShader, heightVis;
        float g = 1.0f, eta = 0.667, height = 60.0f;
        fv2 pos = { 1200, 700 }; fRect2D rect = { { 200, 300 }, { 800, 800 } };
        bool debugHeightmap = false, showActualHeight = false;
    public:
        String debug = "test";

        App();
        bool Run();

        void Trigger();
    };
}