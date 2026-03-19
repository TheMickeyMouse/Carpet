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
        Shader glassShader;
        float g = 1.0f, eta = 0.667;
        fv2 pos;
    public:
        String debug = "test";

        App();
        bool Run();

        void Trigger();
    };
}