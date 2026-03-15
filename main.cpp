#include <windows.h>
#include <dwmapi.h>
#undef IN
#undef OUT
#undef ERROR
#undef DELETE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <iostream>

#include "Dependencies/GLFW/include/GLFW/glfw3.h"
#include "Dependencies/GLFW/include/GLFW/glfw3native.h"
#include "GraphicsDevice.h"
#include "GUI/Canvas.h"

using namespace Quasi;

#define Z_SHOW (SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER)

bool topmost = false;
HWND hWindow = nullptr, hProgman = nullptr, hWorkerW;
bool showDesktop = false;
float t = 0.0f;

void AlwaysShowHook(HWINEVENTHOOK hWinEventHook, DWORD eventType, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime) {
    if (eventType == EVENT_SYSTEM_FOREGROUND) {
        TCHAR className[256] = {};
        usize len = GetClassName(hwnd, className, 256);
        if (strcmp(className, "WorkerW") == 0 || strcmp(className, "Progman") == 0) {
            t = 1.0f;
            Sleep(2);
            SetWindowPos(hProgman, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE);
            // ShowWindow(hProgman, SW_SHOWNA);
        }
    }
}

int main() {
    {
        const int WIDTH = GetSystemMetrics(SM_CXSCREEN), HEIGHT = GetSystemMetrics(SM_CYSCREEN);
        Graphics::GraphicsDevice gd = Graphics::GraphicsDevice::Initialize({ 1920, 1080 }, {
            .resizable = false, .decorated = false, .initalFocused = false,
            .floating = false,
            .transparent = true, .focusOnShow = false
        });
        Graphics::Canvas canvas = gd;

        hWindow = glfwGetWin32Window(gd.GetWindow());
        hProgman = FindWindow(TEXT("Progman"), TEXT("Program Manager"));
        Debug::QInfo$("wid: {:08x}, progman: {:08x}", (usize)hWindow, (usize)hProgman);
        // DwmSetWindowAttribute(w, DWMWA_EXCLUDED_FROM_PEEK, 0x0000003463d3eee4, 4 );

        SetWinEventHook (3, 3, nullptr, &AlwaysShowHook, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        SetWindowLongPtr(hWindow, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_NOACTIVATE);

        // ShowWindow(hWindow, SW_HIDE);
        SetWindowPos(hWindow, HWND_BOTTOM, 0, 0, WIDTH, HEIGHT,
            SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSIZE);
        // ShowWindow(hWindow, SW_SHOWNA);
        // SetWindowLongPtr(hWindow, GWL_STYLE, GetWindowLong(hWindow, GWL_STYLE) | WS_POPUP);

        float g = 1.0f;
        Graphics::Render::SetClearColor({ 0.8f, 1.0f });
        while (gd.WindowIsOpen()) {
            gd.Begin();
            canvas.BeginFrame();

            canvas.Fill({ t, g, 0 });
            t *= 0.99f; g *= 0.98f;
            Math::fv2 p = gd.GetIO().GetMousePos();
            p.y = 1080 - p.y;
            canvas.DrawCircle(p, 100);
            if (gd.GetIO().LeftMouse().OnPress()) {
                g = 1.0f;
            }
            if (gd.GetIO()['K'].OnPress()) {
                break;
            }

            canvas.Update(gd.GetIO().DeltaTime());
            canvas.EndFrame();
            gd.End();
        }
    }

    return 0;
}