#include "Sys.h"
#include "App.h"

#include "glp.h"
#include "GUI/ImGuiExt.h"

namespace Carpet {
    App::App(const iv2& screenSize)
        : gdevice(GraphicsDevice::Initialize(screenSize, {
            .resizable = false,
            .decorated = false,
            .initalFocused = false,
            .floating = false,
            .transparent = true, .focusOnShow = false
        })), canvas(gdevice), glassRenderer(gdevice), terrainRenderer(gdevice, 8, 10) {
#ifdef CARPET_SET_BACKGROUND_BY_DEFAULT
        Sys::PrepareBgWindow(gdevice);
#endif
        Instance = *this;

        canvas.SetViewport({ 0, { 1920, 1080 } });

        glassRenderer.bevelRadius = 25;
        glassRenderer.height = 80.0f;
        glassRenderer.lightDirection = fv3 { 4, 7, 10 };

        font = Font::LoadFile("C:/Users/User/AppData/Local/Microsoft/Windows/Fonts/JetbrainsMono-Bold.ttf", 64);
        glassRenderer.BindFont(font);
        canvas.SetFont(font);
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

        anim = std::lerp(anim, gdevice.GetIO().GetMousePos().IsIn({ 30, 30 }, { 1890, 1050 }) ? 0.0f : 1.0f, 0.13f);
        const fv2 posBottom = anim * fv2 { 0, -600 }, posRight = anim * fv2 { 700, 0 }, posMid = anim * fv2 { 0, -160 };

        glassRenderer.BeginBackground();
        Render::Clear();
        terrainRenderer.Render(gdevice);

        canvas.Stroke(0x2c313c_rgb);
        {
            [[maybe_unused]] const auto shadow = canvas.BeginShadow(fv2 { 0, -3 }, 5, fColor { 0, 0.3f });
            canvas.DrawText("Apps", 64, fv2 { 1670, 1000 } + posRight);
        }

        {
            [[maybe_unused]] const auto shadow = canvas.BeginShadow(fv2 { 0, -3 }, 7, fColor { 0, 0.3f });
            canvas.DrawText("Welcome back!", 64, fv2 { 960, 700 } + posMid);
        }

        canvas.Update(gdevice.GetIO().DeltaTime());
        canvas.EndFrame();

        glassRenderer.EndBackground();

        glassRenderer.DrawBox(fRect2D { { 730, 90 }, { 1190, 550 } } + posBottom, 30);
        glassRenderer.DrawBox(fRect2D { { 1450, 120 }, { 1890, 1050 } } + posRight, 30);
        glassRenderer.DrawSegment(posRight + fv2 { 1510, 60 }, posRight + fv2 { 1830, 60 }, 30);
        Debug::DateTime time = Debug::Timer::Now();
        time += std::chrono::hours(8); // utc offset
        glassRenderer.DrawText(font, Text::Format("{:%H:%m:%s}", time), posMid + fv2 { 960, 700 }, 180, 10.0f);
        // glassRenderer.DrawText(font, "Welcome back!", posMid + fv2 { 960, 650 }, 64, 5.0f);

        fv2 mouse = gdevice.GetIO().GetMousePos();
        mouse *= fv2 { 1920, 1080 } / (fv2)gdevice.GetWindowSize();
        mouse.y = 1080 - mouse.y;
        bubblePos.LerpToward(mouse + fv2 { 6, -6 }, 0.2f); // offset to center at cursor
        bubble = std::lerp(bubble, gdevice.GetIO().LeftMouse().Pressed() ? 50.0f : 30.0f, 0.12f);

        // mimic an ellipse with 3 differently sized circles
        fv2 delta = gdevice.GetIO().GetMousePosDelta().FlipY();
        const auto [nd, speed] = !delta.IsZero() ? delta.NormAndLen() : Tuple { fv2(0), 0.0f };
        const float ecc = std::min(0.15f, 0.02f * speed);
        const float off = std::min(speed, bubble * 0.4f);
        glassRenderer.DrawCirc(bubblePos + nd * off, bubble * (0.6f + ecc));
        glassRenderer.DrawCirc(bubblePos - nd * off, bubble * (0.6f + ecc));
        glassRenderer.DrawCirc(bubblePos, bubble * (1 - ecc));

        glassRenderer.Render();

        showDebug ^= gdevice.GetIO()['H'].OnPress();
        if (showDebug) {
            float s = glassRenderer.GetSmoothingStrength();
            ImGui::EditScalar("smoothing", s, 0.01, fRange { 1, 10 });
            if (s != glassRenderer.GetSmoothingStrength()) glassRenderer.SetSmoothing(s);

            glassRenderer.debugHeightmap ^= ImGui::Button("View Heightmap");
            ImGui::Checkbox("Show Actual Height", &glassRenderer.showActualHeight);

            ImGui::EditRotation2D("Light", light);
            glassRenderer.lightDirection = fv3::FromSpheric(1.0, light, Degrees(60.0f))["xzy"];

            ImGui::EditColor("Tint", glassRenderer.glassTint);

            ImGui::EditScalar("Drop Radius", glassRenderer.dropShadowRadius, 0.2,  fRange { 0, 10 });
            ImGui::EditScalar("Drop Pow",    glassRenderer.dropShadowPow,    0.05, fRange { 0, 1 });
            ImGui::EditScalar("Main Dist",   glassRenderer.mainShadowDist,   0.4,  fRange { 0, 50 });
            ImGui::EditScalar("Main Pow",    glassRenderer.mainShadowPow,    0.05, fRange { 0, 1 });
            ImGui::EditScalar("Eta",         glassRenderer.eta,              0.01, fRange { 0, 1 });
            ImGui::EditScalar("Blur Radius", glassRenderer.blurRadius, 0.5, fRange { 0, 25 });

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

        gdevice.End();
        return gdevice.WindowIsOpen();
    }
}
