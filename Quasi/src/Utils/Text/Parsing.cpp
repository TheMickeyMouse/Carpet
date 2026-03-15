#include "Utils/String.h"
#include "Utils/Func.h"
#include "Parsing.h"
#include "Num.h"

namespace Quasi::Text {
    OptionUsize Parser<char>::ParseUntil(Str string, Out<char&> out, ParseOptions options) {
        using enum TextParseOptions::Enum;

        if (!string) return nullptr;

        if (options.features & QUOTED) {
            const char q = string.First();
            if (!((q == '\'' && options.features & SINGLE_QUOTES) ||
                  (q == '\"' && options.features & DOUBLE_QUOTES)))
                return nullptr;

            if (string.Length() <= 2) return nullptr;

            string.Advance(1);
            char c;
            const OptionUsize i = ParseUnquoted(string, c, options.features & ESCAPE);
            if (!i) return i;
            if (c == q) return nullptr;
            out = c;

            if (string[*i] == q)
                return *i + 2;
            else return nullptr;
        } else {
            return ParseUnquoted(string, out, options.features & ESCAPE);
        }
    }

    OptionUsize Parser<char>::ParseUnquoted(Str string, Out<char&> out, bool allowEscape) {
        using enum TextParseOptions::Enum;

        if (!string) return nullptr;

        if (string[0] == '\\' && allowEscape) {
            string.Advance(1);
            if (!string) return nullptr;
            if (const Option esc = Chr::UnescapeRepr(string[0])) {
                out = *esc;
                return 2;
            }
            if (string[0] == 'x') {
                if (string.Length() < 4) return nullptr;
                const Option x1 = Chr::TryToHexDigit(string[1]),
                             x2 = Chr::TryToHexDigit(string[2]);
                if (!x1 || !x2) return nullptr;
                out = (char)(*x1 * 16 + *x2);
                return 4;
            }
            {
                char c = '\0';
                for (usize i = 0; i < 3; ++i) {
                    if (i >= string.Length()) return i > 0 ? OptionUsize(i + 1) : nullptr;
                    const Option octDigit = Chr::TryToDigitRadix(string[i], 8);
                    if (!octDigit) return i > 0 ? OptionUsize(i + 1) : nullptr;
                    c = (char)(c * 8 + *octDigit);
                }
                return 4;
            }
        } else {
            out = string[0];
            return 1;
        }
    }

    OptionUsize Parser<String>::ParseUntil(Str string, Out<String&> out, ParseOptions options) {
        using enum TextParseOptions::Enum;

        if (!string) return nullptr;

        if (options.features & QUOTED) {
            const char q = string.First();
            if (!((q == '\'' && options.features & SINGLE_QUOTES) ||
                  (q == '\"' && options.features & DOUBLE_QUOTES)))
                return nullptr;

            if (string.Length() < 2) return nullptr;

            string.Advance(1);

            const OptionUsize end = ParseUnquoted(string, out, options.features & ESCAPE, q);
            if (!end) return nullptr;

            return 2 + *end;
        } else {
            return ParseUnquoted(string, out, options.features & ESCAPE, nullptr);
        }
    }

    OptionUsize Parser<String>::ParseUnquoted(Str string, Out<String&> out, bool allowEscape, Option<char> endString) {
        if (allowEscape) {
            String s;
            usize i = 0, prev = 0;
            while (string[i] != endString && i < string.Length()) {
                const char c = string[i];
                if (c != '\\') { ++i; continue; }

                s += string.Substr(prev, i - prev);

                if (i + 1 >= string.Length()) return nullptr;
                if (const Option esc = Chr::UnescapeRepr(string[i + 1])) {
                    s += *esc;
                    i += 2;
                    prev = i + 1;
                    continue;
                }
                if (string[i + 1] == 'x') {
                    const OptionUsize xRes = ParseHex(string.Skip(i), s);
                    if (!xRes) return nullptr;
                    prev = (i += *xRes);
                    continue;
                }
                if (string[i + 1] == 'u') {
                    const OptionUsize uniRes = ParseUnicode(string.Skip(i), s);
                    if (!uniRes) return nullptr;
                    prev = (i += *uniRes);
                    continue;
                }
                {
                    const OptionUsize oRes = ParseOctal(string.Skip(i), s);
                    if (!oRes) return nullptr;
                    prev = (i += *oRes);
                    continue;
                }
            }
            s += string.Substr(prev, i - prev);
            out = std::move(s);
            return i;
        } else {
            const usize end = endString.AndThen(Qfn$(string.Find))
                                       .UnwrapOr(string.Length());
            out = string.First(end);
            return end;
        }
    }

    OptionUsize Parser<String>::ParseHex(Str string, Out<String&> out) {
        if (3 >= string.Length()) return nullptr;
        const Option x1 = Chr::TryToHexDigit(string[2]),
                     x2 = Chr::TryToHexDigit(string[3]);
        if (!x1 || !x2) return nullptr;
        out.Append((char)(*x1 * 16 + *x2));
        return 4;
    }

    OptionUsize Parser<String>::ParseOctal(Str string, Out<String&> out) {
        if (1 >= string.Length()) return nullptr;
        const Option firstOct = Chr::TryToDigitRadix(string[1], 8);
        if (!firstOct) return nullptr;
        char o = (char)*firstOct;

        usize k = 2;
        for (; k < std::min<usize>(4, string.Length()); ++k) {
            const Option octDigit = Chr::TryToDigitRadix(string[k], 8);
            if (!octDigit) break;
            o = (char)(o * 8 + *octDigit);
        }
        out.Append(o);
        return k;
    }

    OptionUsize Parser<String>::ParseUnicode(Str string, Out<String&> out) {
        if (5 >= string.Length()) return nullptr;

        const u32 first4Digits = Memory::ReadU32Big(string.Data() + 2);
        if (!NumberConversion::AreAllHexDigits4(first4Digits)) return nullptr;
        u32 codepoint = NumberConversion::ParseHexDigits4(first4Digits);

        usize k = 6;
        const Option possibleLast = Chr::TryToHexDigit(string[k]);
        if (possibleLast) {
            codepoint = codepoint * 16 + *possibleLast;
            ++k;
        }

        // unicode to utf-8 (https://en.wikipedia.org/wiki/UTF-8#Description)
        // let codepoint be 0b'uuuu'vvvv'wwww'xxxx'yyyy'zzzz
        if (codepoint <= 0x007F) { // plain ascii
            out.Append((char)codepoint); // 0b'0yyy'zzzz
        } else if (codepoint <= 0x07FF) { // two bytes
            out.Append((char)((codepoint >> 6)   | 0xC0)); // 0b'110x'xxyy
            out.Append((char)((codepoint & 0x3F) | 0x80)); // 0b'10yy'zzzz
        } else if (codepoint <= 0xFFFF) { // three bytes
            out.Append((char)((codepoint >> 12)       | 0xE0)); // 0b'1110'wwww
            out.Append((char)((codepoint >> 6 & 0x3F) | 0x80)); // 0b'10xx'xxyy
            out.Append((char)((codepoint & 0x3F)      | 0x80)); // 0b'10yy'zzzz
        } else if (codepoint <= 0x10FFFF) { // four bytes
            out.Append((char)((codepoint >> 18)        | 0xF0)); // 0b'1111'0uvv
            out.Append((char)((codepoint >> 12 & 0x3F) | 0x80)); // 0b'10vv'wwww
            out.Append((char)((codepoint >> 6 & 0x3F)  | 0x80)); // 0b'10xx'xxyy
            out.Append((char)((codepoint & 0x3F)       | 0x80)); // 0b'10yy'zzzz
        }

        return k;
    }
}
