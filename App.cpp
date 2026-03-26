#include "Sys.h"
#include "App.h"

#include "GUI/ImGuiExt.h"

namespace Carpet {
    App::App()
        : gdevice(GraphicsDevice::Initialize(Sys::GetMonitorSize(), {
            .resizable = false, .decorated = false, .initalFocused = false,
            .floating = false,
            .transparent = true, .focusOnShow = false
        })), canvas(gdevice), renderer(gdevice) {
#ifdef CARPET_SET_BACKGROUND_BY_DEFAULT
        Sys::PrepareBgWindow(gdevice);
#endif
        Instance = *this;

        background      = Texture2D::LoadPNG("../plain.png");
        backgroundGlass = Texture2D::LoadPNG("../glass.png");
        glassShader     = Shader::FromFragment("../glass2.glsl");
        heightVis       = Shader::FromFragment("../height.glsl");
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

        renderer.DrawBox(rect, 50);
        renderer.DrawCirc(pos, 100);
        renderer.DrawCirc({ 1400, 400 }, 100);
        renderer.Render();

        if (debugHeightmap) {
            heightVis.Bind();
            heightVis.SetUniformArgs({
                { "heightmap",        renderer.GetHeightmap(), 0 },
                { "bevelRadius",      renderer.bevelRadius },
                { "showActualHeight", showActualHeight }
            });
            Render::DrawScreenQuad(heightVis);
        } else {
            glassShader.Bind();
            glassShader.SetUniformArgs({
                { "heightmap",  renderer.GetHeightmap(), 0 },
                { "bgPlain",    background,      1 },
                { "bgGlass",    backgroundGlass, 2 },
                { "lightSource", fv3 { 0.36, 0.48, 0.8 } },
                { "screenSize", (fv2)gdevice.GetWindowSize() },
                { "eta",         eta },
                { "height",      height },
                { "bevelRadius", renderer.bevelRadius },
            });
            // glassShader.SetUniformFloat("maxZ", renderer.bevelSize);
            Render::DrawScreenQuad(glassShader);
        }

        canvas.Update(gdevice.GetIO().DeltaTime());
        canvas.EndFrame();

        ImGui::EditVector("circle pos", pos);
        ImGui::EditRect("rect", rect);
        ImGui::EditScalar("eta", eta, 0.01f, fRange { 0, 1 });
        ImGui::EditScalar("height", height);
        ImGui::EditScalar("bevel", renderer.bevelRadius);

        float s = renderer.GetSmoothingStrength();
        ImGui::EditScalar("smoothing", s);
        if (s != renderer.GetSmoothingStrength()) renderer.SetSmoothing(s);

        debugHeightmap ^= ImGui::Button("View Heightmap");
        ImGui::Checkbox("Show Actual Height", &showActualHeight);

        gdevice.End();
        return gdevice.WindowIsOpen();
    }

    void App::Trigger() {
        g = 1.0f;
    }
}
