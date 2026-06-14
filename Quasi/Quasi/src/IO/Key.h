#pragma once
#include "Utils/Str.h"

namespace Quasi::IO {
    enum class MouseBtn : int {
        LEFT    = 0,
        RIGHT   = 1,
        MIDDLE  = 2,
        MOUSE_4 = 3,
        MOUSE_5 = 4,
        MOUSE_6 = 5,
        MOUSE_7 = 6,
        MOUSE_8 = 7,
        NUM     = 8
    };

    enum class CursorShape : int {
        DEFAULT = 0, ARROW = DEFAULT,
        TEXT_SELECT,
        CROSSHAIR,
        HAND,
        H_RESIZE,    // (horizontal resize)
        V_RESIZE,    // (vertical resize)
        BS_RESIZE,   // (diagonal top-left to bottom-right)
        FS_RESIZE,   // (diagonal top-right to bottom-left)
        ALL_RESIZE,  // (omnidirectional resize)
        NOT_ALLOWED, // (action not allowed/slash)
    };

    struct ModKey {
        enum E : unsigned char {
            SHIFT = 1 << 0,
            CTRL  = 1 << 1,
            ALT   = 1 << 2,
            WIN   = 1 << 3,
            CAPS  = 1 << 4,
            NUMLK = 1 << 5,
            NONE = 0,
        };
        static E FromStr(Str combo);
    };

    struct Key {
        // optimized loadout
        enum E_ : unsigned char {
            UNKNOWN = 255,
            // MODS
            LSHIFT = 24, LCONTROL, LALT, LWIN,
            RSHIFT = 28, RCONTROL, RALT, RWIN,
            // SYMBOLS
            SPACE = 32, QUOTES, COMMA, MINUS, PERIOD, SLASH, SEMICOLON, EQUAL,
            L_BRACKET, BACKSLASH, R_BRACKET, GRAVE_ACCENT,
            // ARROW KEYS
            RIGHT, LEFT, DOWN, UP,
            // NUMBER
            NUM_0 = 48, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9 = 57,
            // UTIL
            ESCAPE, ENTER, TAB, BACKSPACE, INSERT, DELETE, MENU,
            // CHARACTER
            A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z = 90,
            // OTHER
            NON_US_1 = 91, NON_US_2 = 92,
            // LOCKS
            CAPS_LOCK, SCROLL_LOCK, NUM_LOCK,
            // KEYPAD
            KEYPAD_0 = 96, KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_7, KEYPAD_8, KEYPAD_9,
            KEYPAD_DECIMAL, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD, KEYPAD_ENTER, KEYPAD_EQUAL,
            // FUNCTION
            F1 = 113, F2, F3, F4, F5, F6, F7, F8, F9, F10,
            F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
            // UTILITY
            PAGE_UP, PAGE_DOWN, HOME, END, PRINT_SCREEN, PAUSE,

            MIN = 24, LAST = 143, MAX = 144, NUM = MAX - MIN
        };
        static E_ GlfwCodeToKey(int code);
        static Str ToStr(E_ key);
        // also returns if needs to shift
        static Tuple<E_, bool> FromChar(char c);
        static E_ FromName(Str name);
    };

    struct KeyCombo {
        Key::E_ key; ModKey::E mods;
        KeyCombo(Key::E_ key, ModKey::E mods);
        KeyCombo(Str keystroke);
    };
}
