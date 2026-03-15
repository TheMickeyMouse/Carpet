#pragma once
#include "Utils/Math/Vector.h"
#include "Key.h"
// ! THIS INCLUDES GLEW.H !

struct GLFWwindow;
struct GLFWcursor;

namespace Quasi::Graphics {
    class GraphicsDevice;
}

namespace Quasi::IO {
    class IO {
    private:
        Ref<Graphics::GraphicsDevice> gdevice;
    public:
        IO(Graphics::GraphicsDevice& gd);

        GLFWwindow* InputWindow();
        void SetUserPtr();
        static IO* GetIOPtr(GLFWwindow* win);
        static void AttachCallbacks(GLFWwindow* win);

        void Update();
        void UpdateMouse();
        void UpdateCursorPos();
        void UpdateKeyboard();
        void UpdateTime();

        static constexpr float DOUBLE_CLICK_INTERVAL = 0.5f;
        struct MouseBtnInfo {
        private:
            bool down = false; bool doubleClick = false;
            float downDuration = 0.0f; // negative means unheld time, 0 means just clicked, positive = held time
            Math::fv2 eventPos;
            float clickTime = 0.0, releaseTime = 0.0f;
        public:
            void Click(IO& io, bool click = true);
            void Update(float dt);

            bool Pressed()         const { return down; }
            bool OnPress()         const { return down  && downDuration == 0.0f; }
            bool OnRelease()       const { return !down && downDuration == 0.0f; }
            bool OnDoubleClick()   const { return doubleClick; }
            Math::fv2 ClickedPos() const { return eventPos; }
            float PressDuration()  const { return downDuration; }
            float OnPressTime()    const { return clickTime; }
            float OnReleaseTime()  const { return releaseTime; }
        };

    private:
        bool prevMouseAnyDown = false, mouseAnyDown = false, nextMouseAnyDown = false;
        Math::fv2 currMousePos, prevMousePos, mousePosDelta; // prev is not meant to be accessed
        float prevScroll,  mouseScroll,  mouseScrollDelta; // prev is not meant to be accessed
        float prevScrollX, mouseScrollX, mouseScrollDeltaX; // prev is not meant to be accessed
        bool onScrollUp = false, onScrollDown = false;
        MouseBtnInfo mouseBtnInfo[(int)MouseBtn::NUM];
        CursorShape cursorShape = CursorShape::DEFAULT;
        static GLFWcursor* DEFAULT_CURSOR_SHAPES[9];
    public:
        void Click(MouseBtn mouseBtn, bool click);
        void MoveCursor(const Math::fv2& positionPx);
        void Scroll(float deltaY, float deltaX = 0);

        static void OnGlfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void OnGlfwCursorMoveCallback(GLFWwindow* window, double x, double y);
        static void OnGlfwMouseCallback(GLFWwindow* window, int mouse, int action, int mods);
        static void OnGlfwScrollCallback(GLFWwindow* window, double xOff, double yOff);
        static void OnGlfwKeyCallback(GLFWwindow* window, int key, int positionCode, int action, int modifierBits);

        void CursorLock();
        void CursorHide();
        void CursorShow(); // will also unlock the cursor

        Math::fv2 GetMousePos()      const { return currMousePos; }
        Math::fv2 GetPrevMousePos()  const { return prevMousePos; }
        Math::fv2 GetMousePosDelta() const { return mousePosDelta; }
        bool MouseInWindow()         const;
        float GetMouseScroll()       const { return mouseScroll; }
        float GetMouseScrollDelta()  const { return mouseScrollDelta; }
        float GetMouseScrollX()       const { return mouseScrollX; }
        float GetMouseScrollDeltaX()  const { return mouseScrollDeltaX; }

        const MouseBtnInfo& operator[](MouseBtn btn) const { return MouseButton(btn); }
        const MouseBtnInfo& LeftMouse()   const { return MouseButton(MouseBtn::LEFT); }
        const MouseBtnInfo& RightMouse()  const { return MouseButton(MouseBtn::RIGHT); }
        const MouseBtnInfo& MiddleMouse() const { return MouseButton(MouseBtn::MIDDLE); }
        const MouseBtnInfo& MouseButton(MouseBtn btn) const { return mouseBtnInfo[(int)btn]; }
        bool MouseAnyPressed()   const { return mouseAnyDown; }
        bool MouseAnyOnPress()   const { return !prevMouseAnyDown && mouseAnyDown; }
        bool MouseAnyOnRelease() const { return prevMouseAnyDown && !mouseAnyDown; }

        void SetCursorShape(CursorShape shape);

        struct KeyBtnInfo {
        private:
            bool down = false;
            float downDuration = 0.0f;
            float clickTime = 0.0, releaseTime = 0.0f;
        public:
            void Press(IO& io, bool pressed = true);
            void Update(float dt);

            bool Pressed()         const { return down; }
            bool OnPress()         const { return down  && downDuration == 0.0f; }
            bool OnRelease()       const { return !down && downDuration == 0.0f; }
            float OnPressTime()    const { return clickTime; }
            float OnReleaseTime()  const { return releaseTime; }
        };

    private:
        bool prevKeyAnyDown = false, keyAnyDown = false, nextKeyAnyDown = false;
        KeyBtnInfo keyInfo[(int)Key::NUM];
        ModKey::E modifiers = ModKey::E::NONE;
    public:
        void PressKey(Key::E_ key, bool action);
        void PressMods(ModKey::E mods);

        const KeyBtnInfo& GetKey(Key::E_ k) const { return keyInfo[(int)k]; }
        const KeyBtnInfo& operator[](Key::E_ k) const { return GetKey(k); }
        const KeyBtnInfo& operator[](char name) const { return GetKey(Key::FromChar(name)[1_st]); }
        const KeyBtnInfo& operator[](Str name) const { return GetKey(Key::FromName(name)); }
        ModKey::E GetMods() const { return modifiers; }
        bool KeyCombo(KeyCombo kcombo) const;

        bool KeyAnyPressed()   const { return keyAnyDown; }
        bool KeyAnyOnPress()   const { return !prevKeyAnyDown && keyAnyDown; }
        bool KeyAnyOnRelease() const { return prevKeyAnyDown && !keyAnyDown; }

        bool Shift() const { return modifiers & ModKey::SHIFT; }
        bool Ctrl()  const { return modifiers & ModKey::CTRL; }
        bool Alt()   const { return modifiers & ModKey::ALT; }
        bool Win()   const { return modifiers & ModKey::WIN; }
        bool Caps()  const { return modifiers & ModKey::CAPS; }
    private:
        static constexpr u32 DELTATIME_HISTORY_NUM = 120; // 2 sec of data
        float deltaTime[DELTATIME_HISTORY_NUM] {};
        float timeFor2s = 0.0f;
        u32 dtIndex = DELTATIME_HISTORY_NUM - 1;

        u64 currentFrame = 0;
        float currentTime = 0;
    public:
        void SetTime(float time);
        float GetTime() const;

        float DeltaTime() const { return deltaTime[dtIndex]; }
        float Framerate() const;
    };
}
