#include <GLFW/glfw3.h>

#include "Key.h"
#include "Utils/Iter/SplitIter.h"

namespace Quasi::IO {
    Key::E_ Key::GlfwCodeToKey(int code) {
#define CASE_STR(GLFW_NAME, NAME) case GLFW_KEY_##GLFW_NAME: return NAME;
        using enum E_;
        switch (code) {
            CASE_STR(SPACE,         SPACE)
            CASE_STR(APOSTROPHE,    QUOTES)
            CASE_STR(COMMA,         COMMA)
            CASE_STR(MINUS,         MINUS)
            CASE_STR(PERIOD,        PERIOD)
            CASE_STR(SLASH,         SLASH)
            CASE_STR(0,             NUM_0)
            CASE_STR(1,             NUM_1)
            CASE_STR(2,             NUM_2)
            CASE_STR(3,             NUM_3)
            CASE_STR(4,             NUM_4)
            CASE_STR(5,             NUM_5)
            CASE_STR(6,             NUM_6)
            CASE_STR(7,             NUM_7)
            CASE_STR(8,             NUM_8)
            CASE_STR(9,             NUM_9)
            CASE_STR(SEMICOLON,     SEMICOLON)
            CASE_STR(EQUAL,         EQUAL)
            CASE_STR(A,             A)
            CASE_STR(B,             B)
            CASE_STR(C,             C)
            CASE_STR(D,             D)
            CASE_STR(E,             E)
            CASE_STR(F,             F)
            CASE_STR(G,             G)
            CASE_STR(H,             H)
            CASE_STR(I,             I)
            CASE_STR(J,             J)
            CASE_STR(K,             K)
            CASE_STR(L,             L)
            CASE_STR(M,             M)
            CASE_STR(N,             N)
            CASE_STR(O,             O)
            CASE_STR(P,             P)
            CASE_STR(Q,             Q)
            CASE_STR(R,             R)
            CASE_STR(S,             S)
            CASE_STR(T,             T)
            CASE_STR(U,             U)
            CASE_STR(V,             V)
            CASE_STR(W,             W)
            CASE_STR(X,             X)
            CASE_STR(Y,             Y)
            CASE_STR(Z,             Z)
            CASE_STR(LEFT_BRACKET,  L_BRACKET)
            CASE_STR(BACKSLASH,     BACKSLASH)
            CASE_STR(RIGHT_BRACKET, R_BRACKET)
            CASE_STR(GRAVE_ACCENT,  GRAVE_ACCENT)
            CASE_STR(WORLD_1,       NON_US_1)
            CASE_STR(WORLD_2,       NON_US_2)
            CASE_STR(ESCAPE,        ESCAPE)
            CASE_STR(ENTER,         ENTER)
            CASE_STR(TAB,           TAB)
            CASE_STR(BACKSPACE,     BACKSPACE)
            CASE_STR(INSERT,        INSERT)
            CASE_STR(DELETE,        DELETE)
            CASE_STR(RIGHT,         RIGHT)
            CASE_STR(LEFT,          LEFT)
            CASE_STR(DOWN,          DOWN)
            CASE_STR(UP,            UP)
            CASE_STR(PAGE_UP,       PAGE_UP)
            CASE_STR(PAGE_DOWN,     PAGE_DOWN)
            CASE_STR(HOME,          HOME)
            CASE_STR(END,           END)
            CASE_STR(CAPS_LOCK,     CAPS_LOCK)
            CASE_STR(SCROLL_LOCK,   SCROLL_LOCK)
            CASE_STR(NUM_LOCK,      NUM_LOCK)
            CASE_STR(PRINT_SCREEN,  PRINT_SCREEN)
            CASE_STR(PAUSE,         PAUSE)
            CASE_STR(F1,            F1)
            CASE_STR(F2,            F2)
            CASE_STR(F3,            F3)
            CASE_STR(F4,            F4)
            CASE_STR(F5,            F5)
            CASE_STR(F6,            F6)
            CASE_STR(F7,            F7)
            CASE_STR(F8,            F8)
            CASE_STR(F9,            F9)
            CASE_STR(F10,           F10)
            CASE_STR(F11,           F11)
            CASE_STR(F12,           F12)
            CASE_STR(F13,           F13)
            CASE_STR(F14,           F14)
            CASE_STR(F15,           F15)
            CASE_STR(F16,           F16)
            CASE_STR(F17,           F17)
            CASE_STR(F18,           F18)
            CASE_STR(F19,           F19)
            CASE_STR(F20,           F20)
            CASE_STR(F21,           F21)
            CASE_STR(F22,           F22)
            CASE_STR(F23,           F23)
            CASE_STR(F24,           F24)
            CASE_STR(F25,           F25)
            CASE_STR(KP_0,          KEYPAD_0)
            CASE_STR(KP_1,          KEYPAD_1)
            CASE_STR(KP_2,          KEYPAD_2)
            CASE_STR(KP_3,          KEYPAD_3)
            CASE_STR(KP_4,          KEYPAD_4)
            CASE_STR(KP_5,          KEYPAD_5)
            CASE_STR(KP_6,          KEYPAD_6)
            CASE_STR(KP_7,          KEYPAD_7)
            CASE_STR(KP_8,          KEYPAD_8)
            CASE_STR(KP_9,          KEYPAD_9)
            CASE_STR(KP_DECIMAL,    KEYPAD_DECIMAL)
            CASE_STR(KP_DIVIDE,     KEYPAD_DIVIDE)
            CASE_STR(KP_MULTIPLY,   KEYPAD_MULTIPLY)
            CASE_STR(KP_SUBTRACT,   KEYPAD_SUBTRACT)
            CASE_STR(KP_ADD,        KEYPAD_ADD)
            CASE_STR(KP_ENTER,      KEYPAD_ENTER)
            CASE_STR(KP_EQUAL,      KEYPAD_EQUAL)
            CASE_STR(LEFT_SHIFT,    LSHIFT)
            CASE_STR(LEFT_CONTROL,  LCONTROL)
            CASE_STR(LEFT_ALT,      LALT)
            CASE_STR(LEFT_SUPER,    LWIN)
            CASE_STR(RIGHT_SHIFT,   RSHIFT)
            CASE_STR(RIGHT_CONTROL, RCONTROL)
            CASE_STR(RIGHT_ALT,     RALT)
            CASE_STR(RIGHT_SUPER,   RWIN)
            CASE_STR(MENU,          MENU)
            default: return UNKNOWN;
        }
#undef CASE_STR
    }

    Str Key::ToStr(E_ key) {
#define CASE_STR(NAME, STR) case NAME: return STR;
        using enum E_;
        switch (key) {
            CASE_STR(SPACE,           "[Space]")
            CASE_STR(QUOTES,          "'")
            CASE_STR(COMMA,           ",")
            CASE_STR(MINUS,           "-")
            CASE_STR(PERIOD,          ".")
            CASE_STR(SLASH,           "/")
            CASE_STR(NUM_0,           "0")
            CASE_STR(NUM_1,           "1")
            CASE_STR(NUM_2,           "2")
            CASE_STR(NUM_3,           "3")
            CASE_STR(NUM_4,           "4")
            CASE_STR(NUM_5,           "5")
            CASE_STR(NUM_6,           "6")
            CASE_STR(NUM_7,           "7")
            CASE_STR(NUM_8,           "8")
            CASE_STR(NUM_9,           "9")
            CASE_STR(SEMICOLON,       ";")
            CASE_STR(EQUAL,           "=")
            CASE_STR(A,               "A")
            CASE_STR(B,               "B")
            CASE_STR(C,               "C")
            CASE_STR(D,               "D")
            CASE_STR(E,               "E")
            CASE_STR(F,               "F")
            CASE_STR(G,               "G")
            CASE_STR(H,               "H")
            CASE_STR(I,               "I")
            CASE_STR(J,               "J")
            CASE_STR(K,               "K")
            CASE_STR(L,               "L")
            CASE_STR(M,               "M")
            CASE_STR(N,               "N")
            CASE_STR(O,               "O")
            CASE_STR(P,               "P")
            CASE_STR(Q,               "Q")
            CASE_STR(R,               "R")
            CASE_STR(S,               "S")
            CASE_STR(T,               "T")
            CASE_STR(U,               "U")
            CASE_STR(V,               "V")
            CASE_STR(W,               "W")
            CASE_STR(X,               "X")
            CASE_STR(Y,               "Y")
            CASE_STR(Z,               "Z")
            CASE_STR(L_BRACKET,       "[")
            CASE_STR(BACKSLASH,       "\\")
            CASE_STR(R_BRACKET,       "]")
            CASE_STR(GRAVE_ACCENT,    "`")
            CASE_STR(NON_US_1,        "Non-US-1")
            CASE_STR(NON_US_2,        "Non-US-2")
            CASE_STR(ESCAPE,          "[Esc]")
            CASE_STR(ENTER,           "[Enter]")
            CASE_STR(TAB,             "[Tab]")
            CASE_STR(BACKSPACE,       "[Backspace]")
            CASE_STR(INSERT,          "[Ins]")
            CASE_STR(DELETE,          "[Del]")
            CASE_STR(RIGHT,           "[Right]")
            CASE_STR(LEFT,            "[Left]")
            CASE_STR(DOWN,            "[Down]")
            CASE_STR(UP,              "[Up]")
            CASE_STR(PAGE_UP,         "[PgUp]")
            CASE_STR(PAGE_DOWN,       "[PgDn]")
            CASE_STR(HOME,            "[Home]")
            CASE_STR(END,             "[End]")
            CASE_STR(CAPS_LOCK,       "[Caps Lock]")
            CASE_STR(SCROLL_LOCK,     "[Scroll Lock]")
            CASE_STR(NUM_LOCK,        "[Num Lock]")
            CASE_STR(PRINT_SCREEN,    "[PrtScn]")
            CASE_STR(PAUSE,           "[Pause]")
            CASE_STR(F1,              "F1")
            CASE_STR(F2,              "F2")
            CASE_STR(F3,              "F3")
            CASE_STR(F4,              "F4")
            CASE_STR(F5,              "F5")
            CASE_STR(F6,              "F6")
            CASE_STR(F7,              "F7")
            CASE_STR(F8,              "F8")
            CASE_STR(F9,              "F9")
            CASE_STR(F10,             "F10")
            CASE_STR(F11,             "F11")
            CASE_STR(F12,             "F12")
            CASE_STR(F13,             "F13")
            CASE_STR(F14,             "F14")
            CASE_STR(F15,             "F15")
            CASE_STR(F16,             "F16")
            CASE_STR(F17,             "F17")
            CASE_STR(F18,             "F18")
            CASE_STR(F19,             "F19")
            CASE_STR(F20,             "F20")
            CASE_STR(F21,             "F21")
            CASE_STR(F22,             "F22")
            CASE_STR(F23,             "F23")
            CASE_STR(F24,             "F24")
            CASE_STR(F25,             "F25")
            CASE_STR(KEYPAD_0,        "KP-0")
            CASE_STR(KEYPAD_1,        "KP-1")
            CASE_STR(KEYPAD_2,        "KP-2")
            CASE_STR(KEYPAD_3,        "KP-3")
            CASE_STR(KEYPAD_4,        "KP-4")
            CASE_STR(KEYPAD_5,        "KP-5")
            CASE_STR(KEYPAD_6,        "KP-6")
            CASE_STR(KEYPAD_7,        "KP-7")
            CASE_STR(KEYPAD_8,        "KP-8")
            CASE_STR(KEYPAD_9,        "KP-9")
            CASE_STR(KEYPAD_DECIMAL,  "KP-Decimal")
            CASE_STR(KEYPAD_DIVIDE,   "KP-Divide")
            CASE_STR(KEYPAD_MULTIPLY, "KP-Multiply")
            CASE_STR(KEYPAD_SUBTRACT, "KP-Subtract")
            CASE_STR(KEYPAD_ADD,      "KP-Add")
            CASE_STR(KEYPAD_ENTER,    "KP-Enter")
            CASE_STR(KEYPAD_EQUAL,    "KP-Equal")
            CASE_STR(LSHIFT,          "[Shift]")
            CASE_STR(LCONTROL,        "[Control]")
            CASE_STR(LALT,            "[Alt]")
            CASE_STR(LWIN,            "[Super]")
            CASE_STR(RSHIFT,          "[R-Shift]")
            CASE_STR(RCONTROL,        "[R-Control]")
            CASE_STR(RALT,            "[R-Alt]")
            CASE_STR(RWIN,            "[R-Super]")
            CASE_STR(MENU,            "[Menu]")
            default: return "[UNKNOWN]";
        }
#undef CASE_STR
    }

    Tuple<Key::E_, bool> Key::FromChar(char c) {
        if (Chr::IsAlpha(c)) return { (E_)(c & ~0x20), c < 96 };
        if (Chr::IsDigit(c)) return { (E_)c, false };
        switch (c) {
            case ' ':  return { SPACE, false };
            case '!':  return { NUM_1, true  };
            case '@':  return { NUM_2, true  };
            case '#':  return { NUM_3, true  };
            case '$':  return { NUM_4, true  };
            case '%':  return { NUM_5, true  };
            case '^':  return { NUM_6, true  };
            case '&':  return { NUM_7, true  };
            case '*':  return { NUM_8, true  };
            case '(':  return { NUM_9, true  };
            case ')':  return { NUM_0, true  };
            case '-':  return { MINUS, false }; case '_':  return { SPACE, true };
            case '=':  return { EQUAL, false }; case '+':  return { SPACE, true };
            case '`':  return { GRAVE_ACCENT, false }; case '~':  return { GRAVE_ACCENT, true };
            case '[':  return { L_BRACKET,    false }; case '{':  return { L_BRACKET,    true };
            case ']':  return { R_BRACKET,    false }; case '}':  return { R_BRACKET,    true };
            case '\\': return { BACKSLASH,    false }; case '|':  return { BACKSLASH,    true };
            case ';':  return { SEMICOLON,    false }; case ':':  return { SEMICOLON,    true };
            case '\'': return { QUOTES,       false }; case '"':  return { QUOTES,       true };
            case ',':  return { COMMA,        false }; case '<':  return { COMMA,        true };
            case '.':  return { PERIOD,       false }; case '>':  return { PERIOD,       true };
            case '/':  return { SLASH,        false }; case '?':  return { SLASH,        true };
            default: return { UNKNOWN, false };
        }
    }

    Key::E_ Key::FromName(Str name) {
        if (name.IsEmpty()) return UNKNOWN;
        if (name.Length() == 1) return FromChar(name[0])[1_st];
        if (name.StartsWith('[') && name.EndsWith(']')) {
            name = name.Substr(1, name.Length() - 2);
        }
        // idk why im doing this but its cool i guess
        // removes lowercase
        const int len = name.Length();
        const u64 text = (Memory::ReadU64Big(name.Data()) & 0xDFDFDFDFDFDFDFDF) >> (64 - std::min(64, (int)(8 * len)));
        if (text == "SPACE"_u64  && len == 5) return SPACE;
        if (text == "ESC"_u64    && len == 3) return ESCAPE;
        if (text == "ESCAPE"_u64 && len == 6) return ESCAPE;
        if (text == "ENTER"_u64  && len == 5) return ENTER;
        if (text == "TAB"_u64    && len == 3) return TAB;
        if (text == "INSERT"_u64 && len == 6) return INSERT;
        if (text == "INS"_u64    && len == 3) return INSERT;
        if (text == "DEL"_u64    && len == 3) return DELETE;
        if (text == "DELETE"_u64 && len == 6) return DELETE;
        if (text == "RIGHT"_u64  && len == 5) return RIGHT;
        if (text == "LEFT"_u64   && len == 4) return LEFT;
        if (text == "DOWN"_u64   && len == 4) return DOWN;
        if (text == "UP"_u64     && len == 2) return UP;
        if (text == "PGUP"_u64   && len == 4) return PAGE_UP;
        if (text == "PGDN"_u64   && len == 4) return PAGE_DOWN;
        if (text == "HOME"_u64   && len == 4) return HOME;
        if (text == "END"_u64    && len == 3) return END;
        if (text == "PRTSCN"_u64 && len == 6) return PRINT_SCREEN;
        if (text == "PAUSE"_u64  && len == 5) return PAUSE;
        if (text == "SHIFT"_u64    && len == 5) return LSHIFT;
        if (text == "CTRL"_u64     && len == 4) return LCONTROL;
        if (text == "CONTROL"_u64  && len == 7) return LCONTROL;
        if (text == "ALT"_u64      && len == 3) return LALT;
        if (text == "WIN"_u64      && len == 3) return LWIN;
        if (text == "RSHIFT"_u64   && len == 6) return RSHIFT;
        if (text == "RCONTROL"_u64 && len == 8) return RCONTROL;
        if (text == "RCTRL"_u64    && len == 5) return RCONTROL;
        if (text == "RALT"_u64     && len == 4) return RALT;
        if (text == "RSUPER"_u64   && len == 6) return RWIN;
        if (text == "MENU"_u64     && len == 4) return MENU;
        if (text == "CAPS"_u64     && len == 4) return CAPS_LOCK;

        if (name.EqualsIgnoreCase("CAPS LOCK"))   return CAPS_LOCK;
        if (name.EqualsIgnoreCase("SCROLL LOCK")) return SCROLL_LOCK;
        if (name.EqualsIgnoreCase("NUM LOCK"))    return NUM_LOCK;
        if (name.EqualsIgnoreCase("BACKSPACE"))   return BACKSPACE;
        return UNKNOWN;
    }

    ModKey::E ModKey::FromStr(Str combo) {
        int mods = NONE;
        for (const Str modKey : combo.Split("+")) {
            if (modKey.IsEmpty()) continue;
            if (modKey.Length() > 8) return NONE;

            const int len = modKey.Length();
            const u64 text = (Memory::ReadU64Big(modKey.Data()) & 0xDFDFDFDFDFDFDFDF) >> (64 - std::min(64, (int)(8 * len)));
            if (text == "CTRL"_u64  && len == 4) { mods |= CTRL;  continue; }
            if (text == "SHIFT"_u64 && len == 5) { mods |= SHIFT; continue; }
            if (text == "ALT"_u64   && len == 3) { mods |= ALT;   continue; }
            if (text == "WIN"_u64   && len == 3) { mods |= WIN;   continue; }
            if (text == "CAPS"_u64  && len == 4) { mods |= CAPS;  continue; }
            if (text == "NUMS"_u64  && len == 4) { mods |= NUMLK; continue; }
            return NONE;
        }
        return (E)mods;
    }

    KeyCombo::KeyCombo(Str keystroke) {
        if (keystroke.StartsWith('<') && keystroke.EndsWith('>')) { // vim notation
            keystroke = keystroke.Substr(1, keystroke.Length() - 2);
            if (keystroke.Length() > 3 || keystroke.Length() == 2) return;
            if (keystroke.StartsWith("C-")) { // vim ctrl
                const auto [k, shift] = Key::FromChar(keystroke[2]);
                key = k;
                mods = (ModKey::E)(ModKey::CTRL | (shift ? ModKey::SHIFT : ModKey::NONE));
                return;
            }
            if (keystroke.StartsWith("M-")) { // vim alt
                const auto [k, shift] = Key::FromChar(keystroke[2]);
                key = k;
                mods = (ModKey::E)(ModKey::ALT | (shift ? ModKey::SHIFT : ModKey::NONE));
                return;
            }
            if (keystroke.Length() > 1) return;
            const auto [k, shift] = Key::FromChar(keystroke[0]);
            key = k;
            mods = shift ? ModKey::SHIFT : ModKey::NONE;
            return;
        }

        if (keystroke.Contains('+')) {
            const auto [modList, keyName] = keystroke.RevSplitOnceOn(Cmp::Equals { '+' });
            key = Key::FromName(keyName);
            mods = ModKey::FromStr(modList);
            return;
        }

        key = Key::FromName(keystroke);
    }
}
