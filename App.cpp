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
    }

    bool App::Run() {
        Render::SetClearColor({ 0.8f, 1.0f });

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

        renderer.DrawBox({ { 300, 400 }, { 600, 1000 } }, 50);
        renderer.DrawCirc(pos, 200);
        renderer.Render();

        glassShader.Bind();
        glassShader.SetUniformTex("heightmap", renderer.GetHeightmap(), 0);
        glassShader.SetUniformTex("bgPlain", background,      1);
        glassShader.SetUniformTex("bgGlass", backgroundGlass, 2);
        glassShader.SetUniformFv3("lightSource", { 0.1, 0.5, 1.4 });
        glassShader.SetUniformFloat("eta", eta);
        Render::DrawScreenQuad(glassShader);

        canvas.Update(gdevice.GetIO().DeltaTime());
        canvas.EndFrame();

        ImGui::EditVector("circle pos", pos);
        ImGui::EditScalar("eta", eta, 0.01f, fRange { 0, 1 });

        gdevice.End();
        return gdevice.WindowIsOpen();
    }

    void App::Trigger() {
        g = 1.0f;
    }
}
