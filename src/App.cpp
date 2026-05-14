#include "Sys.h"
#include "App.h"

#include "glp.h"
#include "GUI/ImGuiExt.h"

namespace Carpet {
    App::App(const iv2& screenSize)
        : gdevice(GraphicsDevice::Initialize(screenSize, {
            .resizable = false,
            // .decorated = false,
            .initalFocused = false,
            .floating = false,
            .transparent = true, .focusOnShow = false
        })), canvas(gdevice), glassRenderer(gdevice), terrainRenderer(gdevice, 8, 10) {
#ifdef CARPET_SET_BACKGROUND_BY_DEFAULT
        Sys::PrepareBgWindow(gdevice);
#endif
        Instance = *this;

        canvas.SetViewport({ 0, { 1920, 1080 } });

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

        font = Font::LoadFile("C:/Users/User/AppData/Local/Microsoft/Windows/Fonts/JetbrainsMono-Bold.ttf", 64);
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

        glassRenderer.DrawBox(fRect2D { { 730, 90 }, { 1190, 550 } } + pos, 30);
        glassRenderer.DrawBox(fRect2D { { 1450, 120 }, { 1890, 1050 } } + pos, 30);
        glassRenderer.DrawSegment(pos + fv2 { 1510, 60 }, pos + fv2 { 1830, 60 }, 30);

        Debug::DateTime time = Debug::Timer::Now();
        glassRenderer.DrawText(font, Text::Format("{:%H:%m:%s}", time), pos + fv2 { 960, 700 }, 180, 10.0f);

        glassRenderer.Render();

        canvas.SetFont(font);
        canvas.Stroke(0x2c313c_rgb);
        canvas.DrawText("Welcome back!", 64, { 660, 700 }, { .alignment = TextAlign::CENTER, .rect = { 600, 10 } });

        canvas.Stroke(0xeeeeee_rgb);
        canvas.DrawText("Apps", 64, { 1670, 1000 });

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
