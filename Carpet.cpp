#include "Sys.h"
#include "Carpet.h"

Carpet::Carpet()
    : gdevice(Graphics::GraphicsDevice::Initialize(Sys::GetMonitorSize(), {
        .resizable = false, .decorated = false, .initalFocused = false,
        .floating = false,
        .transparent = true, .focusOnShow = false
    })), canvas(gdevice) {
    Sys::PrepareBgWindow(gdevice);
    Instance = *this;
}

bool Carpet::Run() {
    Graphics::Render::SetClearColor({ 0.8f, 1.0f });

    gdevice.Begin();
    canvas.BeginFrame();

    canvas.Fill({ 0, g, 0 });
    g *= 0.98f;
    Math::fv2 p = gdevice.GetIO().GetMousePos();
    p.y = 1080 - p.y;
    canvas.DrawCircle(p, 100);
    canvas.DrawText(debug, 64, { 960, 1000 });

    if (gdevice.GetIO().LeftMouse().OnPress()) {
        g = 1.0f;
    }
    if (gdevice.GetIO()['K'].OnPress()) {
        return false;
    }

    canvas.Update(gdevice.GetIO().DeltaTime());
    canvas.EndFrame();
    gdevice.End();
    return gdevice.WindowIsOpen();
}

void Carpet::Trigger() {
    g = 1.0f;
}
