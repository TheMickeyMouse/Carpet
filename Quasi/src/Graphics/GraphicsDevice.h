#pragma once

#include "RenderObject.h"
#include "Utils/Debug/Timer.h"
#include "GLs/Render.h"
#include "IO/IO.h"
#include "Utils/Math/Random.h"
#include "Utils/Box.h"
#include "Fonts/FontDevice.h"

namespace Quasi::Graphics {
    class RenderData;

    struct WindowArgs {
        // default args
        bool resizable     = true,
             initalVisible = true,
             decorated     = true,
             initalFocused = true,
             floating      = false,
             maximized     = false,
             transparent   = false,
             focusOnShow   = true,
             passthru      = false,
             fullscreen    = false;
        Math::iv2 beginPosition = { (int)0x80000000 }; // <-- this is GLFW's way of specifying any position
    };

    class GraphicsDevice {
        static constexpr usize MAX_VERTEX_COUNT = 1024;
        static constexpr usize MAX_INDEX_COUNT = 1024;

        using RenderHandle = Box<RenderData>;
    private:
        Vec<RenderHandle> renders;
        VertexArray emptyVAO = VertexArray::New();

        Math::iv2 windowSize;
        GLFWwindow* mainWindow;

        struct GLRenderOptions {
            RenderMode renderMode = RenderMode::FILL;
            float pointSize = 10.0f;
            Math::fColor clearColor;
            u32 drawCalls;
        } renderOptions;

        FontDevice fontDevice = {};
        IO::IO ioDevice { *this };
        Math::RandomGenerator randDevice {};

        friend IO::IO;

        Debug::DateTime frameBeginTime;
        Debug::TimeDuration frameDurationTime;

        inline static OptRef<GraphicsDevice> Instance;
        inline static bool ShowDebugMenu = false;
    public:
        explicit GraphicsDevice(GLFWwindow* window, Math::iv2 winSize);

        void Quit();
        void Terminate();
        ~GraphicsDevice();

        GraphicsDevice(const GraphicsDevice&) = delete;
        GraphicsDevice& operator=(const GraphicsDevice&) = delete;
        static void Transfer(GraphicsDevice& dest, GraphicsDevice&& from);
        GraphicsDevice(GraphicsDevice&& gd) noexcept { Transfer(*this, std::move(gd)); }
        GraphicsDevice& operator=(GraphicsDevice&& gd) noexcept { Transfer(*this, std::move(gd)); return *this; }

        void Begin();
        void End();

        template <class T> RenderObject<T> CreateNewRender(usize vsize = MAX_VERTEX_COUNT, usize isize = MAX_INDEX_COUNT);
        void BindRender(RenderData& render);
        void DeleteRender(u32 index);
        void DeleteAllRenders();
        RenderData& GetRender(u32 index);

        void Render(RenderData& r, Shader& s, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true);
        void Render(RenderData& r, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true) { Render(r, r.shader, args, setDefaultShaderArgs); }
        void Render(u32 index, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true) { Render(GetRender(index), args, setDefaultShaderArgs); }
        void RenderInstanced(RenderData& r, int instances, Shader& s, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true);
        void RenderInstanced(RenderData& r, int instances, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true) {
            RenderInstanced(r, instances, r.shader, args, setDefaultShaderArgs);
        }
        void RenderInstanced(u32 index, int instances, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true) {
            RenderInstanced(GetRender(index), instances, args, setDefaultShaderArgs);
        }

        void ClearColor(const Math::fColor& color);

        bool IsClosed() const { return !mainWindow; }
        bool WindowIsOpen() const;
    
        Math::iv2 GetWindowSize() const { return windowSize; }
        float GetAspectRatio() const { return (float)windowSize.x / (float)windowSize.y; }
        GLFWwindow* GetWindow() { return mainWindow; }
        const GLFWwindow* GetWindow() const { return mainWindow; }

        void EnterFullscreen();

        FontDevice& GetFontDevice() { return fontDevice; }
        const FontDevice& GetFontDevice() const { return fontDevice; }

        void SetDrawMode(RenderMode mode);
        static void RenderInMode(RenderMode mode);

        void DebugMenu();
    private:
        void ShowDebugWindow();
    public:

        static GraphicsDevice& GetDeviceInstance() { return *Instance; }
        static GLFWwindow* GetMainWindow() { return Instance->mainWindow; }
        static const VertexArray& GetEmptyVAO() { return Instance->emptyVAO; }

        IO::IO& GetIO() { return ioDevice; }
        const IO::IO& GetIO() const { return ioDevice; }
        Math::RandomGenerator& GetRand() { return randDevice; }
        const Math::RandomGenerator& GetRand() const { return randDevice; }

        static GraphicsDevice Initialize(Math::iv2 winSize = { 640, 480 }, const WindowArgs& windowArgs = {});
    };

    template <class T>
    RenderObject<T> GraphicsDevice::CreateNewRender(usize vsize, usize isize) {
        renders.Push(Box<RenderData>::Build(*this, vsize, 3 * isize, sizeof(T), VertexLayoutOf<T>()));
        BindRender(*renders.Last());
        return *renders.Last();
    }
}
