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

        // note to self: how to make decent glassy bgs:
        // duplicate layer -> gaussian blur (r=25)
        // if original layer is C, blurred layer is B
        // then final image E = mix(B, B * C, 0.75)
        // final gaussian blur (r=5) produces the final glass image

        // assRenderer.background      = Texture2D::LoadPNG("../bg_day_plain.png");
        // assRenderer.backgroundGlass = Texture2D::LoadPNG("../bg_day_glass.png");
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

        glassRenderer.BeginBackground();
        Render::Clear();
        terrainRenderer.Render(gdevice);
        glassRenderer.EndBackground();

        glassRenderer.DrawBox(fRect2D { { 600, 50 }, { 1320, 400 } } + pos, 25);
        glassRenderer.DrawCirc(pos + fv2 { 670, 395 }, 30);
        glassRenderer.DrawCirc(pos + fv2 { 745, 395 }, 30);
        glassRenderer.DrawSegment(pos + fv2 { 530, 100 }, pos + fv2 { 530, 350 }, 50);

        Debug::DateTime time = Debug::Timer::Now();
        glassRenderer.DrawText(font, Text::Format("{:%H:%m:%s}", time), pos + fv2 { 960, 500 }, 240, 10.0f);

        glassRenderer.Render();

        // canvas.DrawText("Welcome back!", 64, { 660, 700 }, { .alignment = TextAlign::CENTER, .rect = { 600, 10 } });
        // canvas.DrawRect({ { 200, 300 }, { 600, 600 } });

        canvas.Update(gdevice.GetIO().DeltaTime());
        canvas.EndFrame();

        showDebug ^= gdevice.GetIO()['H'].OnPress();
        if (showDebug) {
            float s = glassRenderer.GetSmoothingStrength();
            ImGui::EditScalar("smoothing", s, 0.01, fRange { 1, 10 });
            if (s != glassRenderer.GetSmoothingStrength()) glassRenderer.SetSmoothing(s);

            // glassRenderer.debugHeightmap ^= ImGui::Button("View Heightmap");
            // ImGui::Checkbox("Show Actual Height", &glassRenderer.showActualHeight);

            ImGui::EditVector("Pos", pos);
            ImGui::EditRotation2D("Light", light);
            glassRenderer.lightDirection = fv3::FromSpheric(1.0, light, Degrees(60.0f))["xzy"];

            ImGui::EditColor("Tint", glassRenderer.glassTint);

            ImGui::EditScalar("Drop Radius", glassRenderer.dropShadowRadius, 0.2,  fRange { 0, 10 });
            ImGui::EditScalar("Drop Pow",    glassRenderer.dropShadowPow,    0.05, fRange { 0, 1 });
            ImGui::EditScalar("Main Dist",   glassRenderer.mainShadowDist,   0.4,  fRange { 0, 50 });
            ImGui::EditScalar("Main Pow",    glassRenderer.mainShadowPow,    0.05, fRange { 0, 1 });

            ImGui::Separator();

            ImGui::EditScalar("Fog Falloff", terrainRenderer.fogFalloff, 0.03, fRange { 0, 3 });
            ImGui::EditColor("Fog Blue", terrainRenderer.fogBlue);
            ImGui::EditColor("Fog Yellow", terrainRenderer.fogYellow);
            ImGui::EditVector("Light Source", terrainRenderer.lightSource, 0.05);
            ImGui::EditVector("Camera", terrainRenderer.cameraSource, 0.05);
            ImGui::EditScalar("Z Offset", terrainRenderer.zOffset, 0.03);
            ImGui::EditScalar("X Offset", terrainRenderer.xOffset, 0.03);
            ImGui::EditScalar("Y Offset", terrainRenderer.yOffset, 0.001);
            ImGui::EditScalar("Steepness", terrainRenderer.steepness, 0.01);
            ImGui::EditScalar("Slope Z",   terrainRenderer.slopeZ,    0.01);

            gdevice.DebugMenu();
        }

        // ImGui::EditScalar("S", glassRenderer.S, 0.04, fRange { 0, 100 });

        gdevice.End();
        return gdevice.WindowIsOpen();
    }
}
