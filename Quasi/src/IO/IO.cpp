#include <GLFW/glfw3.h>

#include "IO.h"

#include "imgui_impl_glfw.h"
#include "Graphics/GraphicsDevice.h"

namespace Quasi::IO {
    IO::IO(Graphics::GraphicsDevice& gd) : gdevice(gd) {
        SetUserPtr();
        AttachCallbacks(InputWindow());

        for (int i = 0; i < 9; ++i) {
            DEFAULT_CURSOR_SHAPES[i] = glfwCreateStandardCursor(i + GLFW_ARROW_CURSOR + 1);
        }
    }

    GLFWwindow* IO::InputWindow() {
        return gdevice->GetWindow();
    }

    void IO::SetUserPtr() {
        glfwSetWindowUserPointer(InputWindow(), this);
    }

    IO* IO::GetIOPtr(GLFWwindow* win) {
        return (IO*)glfwGetWindowUserPointer(win);
    }

    void IO::AttachCallbacks(GLFWwindow* win) {
        glfwSetFramebufferSizeCallback(win, &OnGlfwFramebufferSizeCallback);
        glfwSetCursorPosCallback      (win, &OnGlfwCursorMoveCallback);
        glfwSetMouseButtonCallback    (win, &OnGlfwMouseCallback);
        glfwSetScrollCallback         (win, &OnGlfwScrollCallback);
        glfwSetKeyCallback            (win, &OnGlfwKeyCallback);
    }

    void IO::Update() {
        UpdateTime();
        UpdateCursorPos();
        UpdateMouse();
        UpdateKeyboard();
    }

    void IO::UpdateMouse() {
        prevMouseAnyDown = mouseAnyDown;
        mouseAnyDown = nextMouseAnyDown;
        nextMouseAnyDown = false;

        for (auto& mbtn : mouseBtnInfo) {
            mbtn.Update(DeltaTime());
        }

        glfwSetCursor(InputWindow(), cursorShape != CursorShape::DEFAULT ? DEFAULT_CURSOR_SHAPES[(int)cursorShape - 1] : nullptr);
    }

    void IO::UpdateCursorPos() {
        mousePosDelta = currMousePos - prevMousePos;
        prevMousePos = currMousePos;

        mouseScrollDelta  = mouseScroll  - prevScroll;
        mouseScrollDeltaX = mouseScrollX - prevScrollX;
        prevScroll  = mouseScroll;
        prevScrollX = mouseScrollX;
    }

    void IO::UpdateKeyboard() {
        prevKeyAnyDown = keyAnyDown;
        keyAnyDown = nextKeyAnyDown;
        nextKeyAnyDown = false;
        
        for (KeyBtnInfo& kInfo : keyInfo) {
            kInfo.Update(DeltaTime());
        }
    }

    void IO::UpdateTime() {
        ++currentFrame;
        const float newTime = (float)glfwGetTime();

        dtIndex = (dtIndex + 1) % DELTATIME_HISTORY_NUM;
        timeFor2s -= deltaTime[dtIndex];
        deltaTime[dtIndex] = newTime - currentTime;
        timeFor2s += deltaTime[dtIndex];

        currentTime = newTime;
    }

    void IO::MouseBtnInfo::Click(IO& io, bool click) {
        eventPos = io.currMousePos;

        (click ? clickTime : releaseTime) = io.currentTime;
        doubleClick = click && !down && (clickTime - releaseTime <= DOUBLE_CLICK_INTERVAL);
        down = click;
    }

    void IO::MouseBtnInfo::Update(float dt) {
        if (down) {
            if (downDuration < 0.0f) {
                downDuration = 0.0f;
            } else {
                downDuration += dt;
                doubleClick = false;
            }
        } else {
            if (downDuration > 0.0f) downDuration = 0.0f;
            else downDuration -= dt;
        }
    }

    void IO::Click(MouseBtn mouseBtn, bool click) {
        mouseBtnInfo[(int)mouseBtn].Click(*this, click);
        nextMouseAnyDown |= click;
    }

    void IO::MoveCursor(const Math::fv2& positionPx) {
        currMousePos = positionPx;
    }

    void IO::Scroll(float deltaY, float deltaX) {
        onScrollUp   = deltaY > 0.0f && mouseScrollDelta == 0.0;
        onScrollDown = deltaY < 0.0f && mouseScrollDelta == 0.0;
        mouseScroll += deltaY; mouseScrollX += deltaX;
    }

    void IO::OnGlfwFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
        GetIOPtr(window)->gdevice->windowSize = { width, height };
    }

    void IO::OnGlfwCursorMoveCallback(GLFWwindow* window, double x, double y) {
#ifndef Q_NO_IMGUI
        ImGui_ImplGlfw_CursorPosCallback(window, x, y);
#endif
        IO& io = *GetIOPtr(window);
        io.MoveCursor({ (float)x, (float)y });
    }

    void IO::OnGlfwMouseCallback(GLFWwindow* window, int mouse, int action, int mods) {
#ifndef Q_NO_IMGUI
        ImGui_ImplGlfw_MouseButtonCallback(window, mouse, action, mods);
#endif
        IO& io = *GetIOPtr(window);
        io.Click((MouseBtn)mouse, action == GLFW_PRESS);
        io.PressMods((ModKey::E)mods);
    }

    void IO::OnGlfwScrollCallback(GLFWwindow* window, double xOff, double yOff) {
#ifndef Q_NO_IMGUI
        ImGui_ImplGlfw_ScrollCallback(window, xOff, yOff);
#endif
        IO& io = *GetIOPtr(window);
        io.Scroll((float)yOff, (float)xOff);
    }

    void IO::OnGlfwKeyCallback(GLFWwindow* window, int key, int positionCode, int action, int modifierBits) {
#ifndef Q_NO_IMGUI
        ImGui_ImplGlfw_KeyCallback(window, key, positionCode, action, modifierBits);
#endif
        IO& io = *GetIOPtr(window);
        io.PressKey(Key::GlfwCodeToKey(key), action != GLFW_RELEASE);
        io.PressMods((ModKey::E)modifierBits);
    }

    void IO::CursorLock() {
        glfwSetInputMode(InputWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void IO::CursorHide() {
        glfwSetInputMode(InputWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void IO::CursorShow() {
        glfwSetInputMode(InputWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    bool IO::MouseInWindow() const {
        const Math::iv2& windowSize = gdevice->windowSize;
        const Math::fv2& p = currMousePos;
        return windowSize.x >= p.x && windowSize.y >= p.y && p.x >= 0 && p.y >= 0;
    }

    void IO::SetCursorShape(CursorShape shape) {
       cursorShape = shape;
    }

    void IO::KeyBtnInfo::Press(IO& io, bool pressed) {
        (pressed ? clickTime : releaseTime) = io.currentTime;
        down = pressed;
    }

    void IO::KeyBtnInfo::Update(float dt) {
        if (down) {
            if (downDuration < 0.0f) {
                downDuration = 0.0f;
            } else {
                downDuration += dt;
            }
        } else {
            if (downDuration > 0.0f) downDuration = 0.0f;
            else downDuration -= dt;
        }
    }

    void IO::PressKey(Key::E_ key, bool action) {
        keyInfo[(int)key].Press(*this, action);
        nextKeyAnyDown |= action;
    }

    void IO::PressMods(ModKey::E mods) {
        modifiers = mods;
    }

    bool IO::KeyCombo(Quasi::IO::KeyCombo kcombo) const {
        return (GetMods() & kcombo.mods) && GetKey(kcombo.key).OnPress();
    }

    void IO::SetTime(float time) {
        glfwSetTime(time);
    }

    float IO::GetTime() const {
        return currentTime;
    }

    float IO::Framerate() const {
        return (float)DELTATIME_HISTORY_NUM / timeFor2s;
    }

    GLFWcursor* IO::DEFAULT_CURSOR_SHAPES[9] { nullptr };
}
