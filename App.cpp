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
        glassShader     = Shader::FromFragment("../glass.glsl");
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
        renderer.DrawCirc(pos, 200);
        renderer.Render();

        if (debugHeightmap) {
            heightVis.Bind();
            heightVis.SetUniformTex("heightmap", renderer.GetHeightmap(), 0);
            heightVis.SetUniformFloat("extrudeZ", renderer.bevelSize);
            Render::DrawScreenQuad(heightVis);
        } else {
            glassShader.Bind();
            glassShader.SetUniformTex("heightmap", renderer.GetHeightmap(), 0);
            glassShader.SetUniformTex("bgPlain", background,      1);
            glassShader.SetUniformTex("bgGlass", backgroundGlass, 2);
            glassShader.SetUniformFv3("lightSource", { 960.0f, 540.0f, 100.0f });
            glassShader.SetUniformFv2("screenSize", (fv2)gdevice.GetWindowSize());
            glassShader.SetUniformFloat("eta", eta);
            glassShader.SetUniformFloat("height", height);
            // glassShader.SetUniformFloat("maxZ", renderer.bevelSize);
            Render::DrawScreenQuad(glassShader);
        }

        canvas.Update(gdevice.GetIO().DeltaTime());
        canvas.EndFrame();

        ImGui::EditVector("circle pos", pos);
        ImGui::EditRect("rect", rect);
        ImGui::EditScalar("eta", eta, 0.01f, fRange { 0, 1 });
        ImGui::EditScalar("height", height);
        ImGui::EditScalar("bevel", renderer.bevelSize);
        debugHeightmap ^= ImGui::Button("View Heightmap");

        gdevice.End();
        return gdevice.WindowIsOpen();
    }

    void App::Trigger() {
        g = 1.0f;
    }
}
