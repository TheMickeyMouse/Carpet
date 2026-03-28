#include "Sys.h"
#include "App.h"

#include "glp.h"
#include "GUI/ImGuiExt.h"

namespace Carpet {
    App::App()
        : gdevice(GraphicsDevice::Initialize(Sys::GetMonitorSize(), {
            .resizable = false, .decorated = false, .initalFocused = false,
            .floating = false,
            .transparent = true, .focusOnShow = false
        })), canvas(gdevice), glassRenderer(gdevice) {
#ifdef CARPET_SET_BACKGROUND_BY_DEFAULT
        Sys::PrepareBgWindow(gdevice);
#endif
        Instance = *this;

        glassRenderer.background      = Texture2D::LoadPNG("../bg_day_plain.png");
        glassRenderer.backgroundGlass = Texture2D::LoadPNG("../bg_day_glass.png");
        glassRenderer.SetBevel(25);
        glassRenderer.height = 80.0f;
        glassRenderer.lightDirection = fv3 { 4, 7, 10 };
    }

    bool App::Run() {
        gdevice.Begin();
        canvas.BeginFrame();

        // canvas.DrawText(debug, 64, { 960, 1000 });

#ifndef CARPET_SET_BACKGROUND_BY_DEFAULT
        if (gdevice.GetIO()['D'].OnPress()) {
            Sys::PrepareBgWindow(gdevice);
        }
#endif

        if (gdevice.GetIO()['K'].OnPress()) {
            return false;
        }

        glassRenderer.DrawBox(fRect2D { { 600, 50 }, { 1320, 400 } } + pos, 25);
        glassRenderer.DrawCirc(pos + fv2 { 670, 395 }, 30);
        glassRenderer.DrawCirc(pos + fv2 { 745, 395 }, 30);
        glassRenderer.Render();

        canvas.Update(gdevice.GetIO().DeltaTime());
        canvas.EndFrame();

        float s = glassRenderer.GetSmoothingStrength();
        ImGui::EditScalar("smoothing", s, 0.01, fRange { 1, 10 });
        if (s != glassRenderer.GetSmoothingStrength()) glassRenderer.SetSmoothing(s);

        glassRenderer.debugHeightmap ^= ImGui::Button("View Heightmap");
        ImGui::Checkbox("Show Actual Height", &glassRenderer.showActualHeight);

        ImGui::EditVector("Pos", pos);
        ImGui::EditRotation2D("Light", light);
        glassRenderer.lightDirection = fv3::FromSpheric(1.0, light, Degrees(60.0f))["xzy"];

        ImGui::EditScalar("S", glassRenderer.S, 0.04, fRange { 0, 100 });

        gdevice.End();
        return gdevice.WindowIsOpen();
    }
}
