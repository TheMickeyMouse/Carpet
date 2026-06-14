#include "Text.h"

#include <fstream>

#include "CStr.h"
#include "Utils/Debug/Logger.h"
#include "Text/Num.h"

namespace Quasi::Text {
    Option<String> ReadFile(CStr fname) {
        // standard C implementation
        std::FILE *fp = std::fopen(fname.Data(), "r");
        if (fp) {
            std::fseek(fp, 0, SEEK_END);
            usize length = std::ftell(fp);
            // ownership is transfered at return
            char* const contentsRaw = (char*)Memory::AllocateRaw(length * sizeof(char));

            std::rewind(fp);
            length = std::fread(contentsRaw, 1, length, fp);
            std::fclose(fp);
            return String::Compose(contentsRaw, length, length);
        }
        return nullptr;
    }

    Option<String> ReadFileBinary(CStr fname) {
        std::FILE *fp = std::fopen(fname.Data(), "rb");
        if (fp) {
            std::fseek(fp, 0, SEEK_END);
            usize length = std::ftell(fp);
            // ownership is transfered at return
            char* const contentsRaw = (char*)Memory::AllocateRaw(length * sizeof(char));

            std::rewind(fp);
            length = std::fread(contentsRaw, 1, length, fp);
            std::fclose(fp);
            return String::Compose(contentsRaw, length, length);
        }
        return nullptr;
    }

    bool WriteFile(CStr fname, Str contents) {
        if (std::ofstream out { fname.Data() }) {
            out.write(contents.Data(), (isize)contents.Length());
            return true;
        }
        return false;
    }

    bool WriteFileBinary(CStr fname, Str contents) {
        if (std::ofstream out { fname.Data(), std::ios_base::out | std::ios_base::binary }) {
            out.write(contents.Data(), (isize)contents.Length());
            return true;
        }
        return false;
    }

    bool WriteFileBinary(CStr fname, Bytes contents) {
        return WriteFileBinary(fname, contents.Transmute<char>().AsStr());
    }

    bool ExistsFile(CStr fname) {
        return std::ifstream { fname.Data() }.good();
    }

    Tuple<Str, Str> SplitDirectory(Str fname) {
        const auto [pos, _] = fname.RevFindOneOf("\\/");
        return pos ?
            Tuple { fname.Substr(0, *pos),
                    fname.Substr(*pos + 1) } :
            Tuple { Str::Empty(), fname };
    }

    String AutoIndent(Str text) {
        String ss;
        u32 indent = 0;
        for (usize i = 0; i < text.Length() - 1; ++i) {
            const char c = text[i];
            if (text[i] == '{' || text[i] == '[') {
                ++indent;
            }
            if (text[i + 1] == '}' || text[i + 1] == ']') {
                Debug::AssertMsg(indent > 0, "unindenting past level 0");
                --indent;
            }
            if (c == '\n') {
                ss += '\n';
                for (u32 j = 0; j < indent; ++j) ss += ' ';
                continue;
            }
            ss += c;
        }
        ss += text.Last();
        return ss;
    }

    String Quote(Str txt, char quote) {
        String quoted = String::WithCap(txt.Length() + 2);
        quoted.Append(quote);
        quoted.AppendStr(txt);
        quoted.Append(quote);
        return quoted;
    }

    ColoredStr Dye(ConsoleColor col, Str txt) {
        return { col, txt };
    }

    usize Formatter<ConsoleColor>::FormatTo(StringWriter output, ConsoleColor c, Str) {
        output.Write("\x1B["_str);
        if (IsBold(c))
            output.Write("1;"_str);

        if (c == ConsoleColor::RESET) {
            return 2 + (IsBold(c) ? 2 : 0) + output.Write("0m");
        }

        char regbuf[3] = { '\0', '\0', 'm' };
        u16 byte2 = Regular(c);
        byte2 += (byte2 * 103 >> 10) * (256 - 10);
        byte2 |= 0x3030;
        Memory::WriteU16Big(byte2, regbuf);

        output.Write(Str::Slice(regbuf, 3));
        return 2 + (IsBold(c) ? 2 : 0) + 3;
    }

    usize Formatter<ColoredStr>::FormatTo(StringWriter output, const ColoredStr& cstr, const FormatOptions& options) {
        usize padLen = options.targetLength - cstr.text.Length();
        padLen &= -(padLen <= options.targetLength); // fun bithacks that turn negative numbers into 0
        const usize right = padLen * (usize)options.alignment / 2;

        return output.WriteRepeat(options.pad, padLen - right) +
               output.SetColor(cstr.color) +
               output.Write(cstr.text) +
               output.Write("\x1B[0m"_str) +
               output.WriteRepeat(options.pad, right);
    }
}
