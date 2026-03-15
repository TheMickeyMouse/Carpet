#pragma once

#include "Macros.h"
#include "Option.h"
#include "Text/Formatting.h"

namespace Quasi {
    struct CStr;
}

namespace Quasi::Text {
    Option<String> ReadFile(CStr fname);
    Option<String> ReadFileBinary(CStr fname);
    bool WriteFile(CStr fname, Str contents);
    bool WriteFileBinary(CStr fname, Str contents);
    bool WriteFileBinary(CStr fname, Bytes contents);
    bool ExistsFile(CStr fname);

    Tuple<Str, Str> SplitDirectory(Str fname);

    String AutoIndent(Str text);
    String Quote(Str txt, char quote = '\"');

    // adapted from https://stackoverflow.com/a/59522794/19968422
    namespace _helper {
        template <class T> constexpr const char* t() { return Q_FUNC_NAME(); }
        static constexpr usize T_START_IDX = [] {
            const char* templateString = t<void>();
            for (usize i = 0; templateString[i]; ++i) if (templateString[i] == 'v') return i;
            return 0_usize;
        } ();
        static constexpr usize T_TOTAL_SIZE = [] {
            const char* templateString = t<void>();
            usize i = 0;
            for (; templateString[i]; ++i) {}
            return i - Q_STRLIT_LEN("void");
        } ();

        // ReSharper disable once CppStaticAssertFailure
        static_assert(T_START_IDX, "nameof type couldn't be found");
    }

    template <class T> Str TypeName() {
        const Str fullname = _helper::t<T>();
        return fullname.Substr(_helper::T_START_IDX, fullname.Length() - _helper::T_TOTAL_SIZE);
    }
    template <usize N>
    struct FixedString  {
        char buf[N + 1]{};
        constexpr FixedString(const char* s) {
            for (unsigned i = 0; i != N; ++i) buf[i] = s[i];
        }
        constexpr operator const char*() const { return buf; }
        static constexpr usize SIZE = N;
    };
    template <usize N> FixedString(const char (&)[N]) -> FixedString<N - 1>;

    enum ConsoleColor : u32 {
        RESET = 0,

        BLACK   = 0, H_BLACK   = 60,
        RED     = 1, H_RED     = 61,
        GREEN   = 2, H_GREEN   = 62,
        YELLOW  = 3, H_YELLOW  = 63,
        BLUE    = 4, H_BLUE    = 64,
        MAGENTA = 5, H_MAGENTA = 65,
        CYAN    = 6, H_CYAN    = 66,
        GRAY    = 7, H_GRAY    = 67,

        FG_BLACK    = 30, BG_BLACK    = 40,
        FG_RED      = 31, BG_RED      = 41,
        FG_GREEN    = 32, BG_GREEN    = 42,
        FG_YELLOW   = 33, BG_YELLOW   = 43,
        FG_BLUE     = 34, BG_BLUE     = 44,
        FG_MAGENTA  = 35, BG_MAGENTA  = 45,
        FG_CYAN     = 36, BG_CYAN     = 46,
        FG_GRAY     = 37, BG_GRAY     = 47,
        HFG_BLACK   = 90, HBG_BLACK   = 100,
        HFG_RED     = 91, HBG_RED     = 101,
        HFG_GREEN   = 92, HBG_GREEN   = 102,
        HFG_YELLOW  = 93, HBG_YELLOW  = 103,
        HFG_BLUE    = 94, HBG_BLUE    = 104,
        HFG_MAGENTA = 95, HBG_MAGENTA = 105,
        HFG_CYAN    = 96, HBG_CYAN    = 106,
        HFG_GRAY    = 97, HBG_GRAY    = 107,

        HIGHLIGHT = 60,
        BACKGROUND = 40,
        FOREGROUND = 30,

        BOLD_FLAG = 128,
        REGULAR_MASK = 127
    };

    constexpr char ANSI_ESCAPE_CHAR = '\x1B';

    constexpr ConsoleColor Highlight(ConsoleColor color) { return (ConsoleColor)(color + HIGHLIGHT); }
    constexpr ConsoleColor BgColor(ConsoleColor color)   { return (ConsoleColor)(color + BACKGROUND); }
    constexpr ConsoleColor FgColor(ConsoleColor color)   { return (ConsoleColor)(color + FOREGROUND); }
    constexpr ConsoleColor HBgColor(ConsoleColor color)  { return BgColor(Highlight(color)); }
    constexpr ConsoleColor HFgColor(ConsoleColor color)  { return FgColor(Highlight(color)); }

    constexpr bool IsBold(ConsoleColor color) { return (color & BOLD_FLAG) != 0; }
    constexpr ConsoleColor Bold(ConsoleColor color) { return (ConsoleColor)(color | BOLD_FLAG); }
    constexpr ConsoleColor Regular(ConsoleColor color) { return (ConsoleColor)(color & REGULAR_MASK); }

    struct ColoredStr { ConsoleColor color; Str text; };
    ColoredStr Dye(ConsoleColor col, Str txt);

    template <>
    struct Formatter<ConsoleColor> {
        static usize FormatTo(StringWriter output, ConsoleColor c, Str);
    };

    template <>
    struct Formatter<ColoredStr> : Formatter<Str> {
        static usize FormatTo(StringWriter output, const ColoredStr& cstr, const FormatOptions& options);
    };
}
