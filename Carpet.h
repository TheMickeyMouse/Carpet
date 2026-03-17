#pragma once
#include "GraphicsDevice.h"
#include "GUI/Canvas.h"

using namespace Quasi;

class Carpet {
public:
    inline static OptRef<Carpet> Instance = nullptr;
private:
    Graphics::GraphicsDevice gdevice;
    Graphics::Canvas canvas;
    float g = 1.0f;
public:
    String debug = "test";

    Carpet();
    bool Run();

    void Trigger();
};