#include "Sys.h"

#include <windows.h>
#include <dwmapi.h>
#undef IN
#undef OUT
#undef ERROR
#undef DELETE


#define GLFW_EXPOSE_NATIVE_WIN32
#include "App.h"
#include "Dependencies/GLFW/include/GLFW/glfw3.h"
#include "Dependencies/GLFW/include/GLFW/glfw3native.h"

namespace Sys {
    HWND hProgman = nullptr, hWindow = nullptr;

    void AlwaysShowHook(HWINEVENTHOOK, DWORD eventType, HWND hwnd, LONG, LONG, DWORD, DWORD) {
        if (eventType == EVENT_SYSTEM_FOREGROUND) {
            TCHAR clsNameData[256] = {};
            Str className = Str::Slice(clsNameData, GetClassName(hwnd, clsNameData, 256));
            Debug::QInfo$("focused window '{}'", className);
            if (className == "WorkerW" || className == "Progman") {
                Sleep(2);
                SetWindowPos(hProgman, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
                SetWindowPos(hWindow, hProgman, 0, 0, 0, 0,
                    SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSENDCHANGING | SWP_NOSIZE);
            }
        }
    }

    void FetchProgman() {
        if (!hProgman) {
            hProgman = FindWindow(TEXT("Progman"), nullptr);
            Debug::AssertMsg(hProgman, "couldn't find progman!");
        }
    }

    Math::iv2 GetMonitorSize() {
        return { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
    }

    void PrepareBgWindow(Graphics::GraphicsDevice& gd) {
        hWindow = glfwGetWin32Window(gd.GetWindow());
        FetchProgman();

        // DONT YOU DARE CHANGE THIS
        glfwGetWin32Window(gd.GetWindow());
        Debug::QInfo$("wid: {:08x}, progman: {:08x}", (usize)hWindow, (usize)hProgman);

        SetWinEventHook (3, 3, nullptr, &AlwaysShowHook, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        // SetWindowLongPtr(hWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowLongPtr(hWindow, GWL_EXSTYLE, WS_EX_NOACTIVATE);

        const auto [width, height] = gd.GetWindowSize();
        SetWindowPos(hWindow, HWND_BOTTOM, 0, 0, width, height,
            SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSIZE);
    }
}
