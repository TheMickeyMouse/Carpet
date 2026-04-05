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
        })), canvas(gdevice), glassRenderer(gdevice), terrainRenderer(gdevice) {
#ifdef CARPET_SET_BACKGROUND_BY_DEFAULT
        Sys::PrepareBgWindow(gdevice);
#endif
        Instance = *this;

        glassRenderer.background      = Texture2D::LoadPNG("../bg_day_plain.png");
        glassRenderer.backgroundGlass = Texture2D::LoadPNG("../bg_day_glass.png");
        glassRenderer.bevelRadius = 25;
        glassRenderer.height = 80.0f;
        glassRenderer.lightDirection = fv3 { 4, 7, 10 };

        font = Font::LoadFile("C:/Users/User/AppData/Local/Microsoft/Windows/Fonts/JetbrainsMono-Medium.ttf", 64);
        glassRenderer.BindFont(font);
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

        ImGui::Combo("Renderer", (int*)&rendererID, "Glass\0Terrain\0\0");

        if (rendererID == GLASS) {
            glassRenderer.DrawBox(fRect2D { { 600, 50 }, { 1320, 400 } } + pos, 25);
            glassRenderer.DrawCirc(pos + fv2 { 670, 395 }, 30);
            glassRenderer.DrawCirc(pos + fv2 { 745, 395 }, 30);
            glassRenderer.DrawSegment(pos + fv2 { 530, 100 }, pos + fv2 { 530, 350 }, 50);

            Debug::DateTime time = Debug::Timer::Now();
            glassRenderer.DrawText(font, Text::Format("{:%H:%m:%s}", time), fv2 { 960, 700 }, 240, 10.0f);

            glassRenderer.Render();
        } else if (rendererID == TERRAIN) {
            terrainRenderer.Render(gdevice);
        }

        // canvas.DrawText("Welcome back!", 64, { 660, 700 }, { .alignment = TextAlign::CENTER, .rect = { 600, 10 } });
        // canvas.DrawRect({ { 200, 300 }, { 600, 600 } });

        canvas.Update(gdevice.GetIO().DeltaTime());
        canvas.EndFrame();

        if (rendererID == GLASS) {
            float s = glassRenderer.GetSmoothingStrength();
            ImGui::EditScalar("smoothing", s, 0.01, fRange { 1, 10 });
            if (s != glassRenderer.GetSmoothingStrength()) glassRenderer.SetSmoothing(s);

            glassRenderer.debugHeightmap ^= ImGui::Button("View Heightmap");
            ImGui::Checkbox("Show Actual Height", &glassRenderer.showActualHeight);

            ImGui::EditVector("Pos", pos);
            ImGui::EditRotation2D("Light", light);
            glassRenderer.lightDirection = fv3::FromSpheric(1.0, light, Degrees(60.0f))["xzy"];

            ImGui::EditColor("Tint", glassRenderer.glassTint);
        }

        // ImGui::EditScalar("S", glassRenderer.S, 0.04, fRange { 0, 100 });

        gdevice.End();
        return gdevice.WindowIsOpen();
    }
}
