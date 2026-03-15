#include "Formatting.h"

#include "Num.h"
#include "Utils/Debug/Logger.h"

namespace Quasi::Text {
    usize FormatToDynamic(StringWriter output, Str fmt, const void* const argParams[],
        const FuncPtr<usize, StringWriter, const void*, Str> writerParams[], usize n) {
        const auto WriteNth = [&] (usize i, Str opt) {
            Debug::QAssert$(i < n, "tried formatting argument number #{} when there are only {} arguments", i + 1, n);
            return writerParams[i](output, argParams[i], opt);
        };

        usize i = 0, prev = 0, currentWriteIndex = 0, writeLen = 0;
        while (i < fmt.Length()) {
            const char c = fmt[i];
            if (c != '{' && c != '}') { ++i; continue; }
            if (i + 1 < fmt.Length() && fmt[i + 1] == c) {
                writeLen += output.Write(c);
                i = (prev = i + 2);
                continue;
            }

            writeLen += output.Write(fmt.Substr(prev, i - prev));
            // '{'
            Debug::QAssert$(c == '{', "formatting string {:?} is ill-formed", fmt);
            usize p = 0, q = 0;
            for (usize j = i + 1; j < fmt.Length(); ++j) {
                if (fmt[j] == '}') { q = j; break; }
                if (fmt[j] == ':' && p == 0) { p = j; }
            }

            Debug::QAssert$(q, "no closing '}}' in format string {:?}", fmt);
            if (q == i + 1) { // empty, {}
                writeLen += WriteNth(currentWriteIndex, "");
            } else if (p == 0) { // no colon, {index}
                const usize specifiedIndex = Parse<usize>(fmt.Substr(i + 1, q - i - 1)).UnwrapOr(currentWriteIndex);
                writeLen += WriteNth(specifiedIndex, "");
            } else if (p == i + 1) { // colon at beginning, {:options}
                writeLen += WriteNth(currentWriteIndex, fmt.Substr(p + 1, q - p - 1));
            } else { // colon at middle, {index:options}
                const usize specifiedIndex = Parse<usize>(fmt.Substr(i + 1, p - i - 1)).UnwrapOr(currentWriteIndex);
                writeLen += WriteNth(specifiedIndex, fmt.Substr(p + 1, q - p - 1));
            }
            i = prev = q + 1;
            ++currentWriteIndex;
        }
        writeLen += output.Write(fmt.Substr(prev));
        return writeLen;
    }

    TextFormatOptions TextFormatOptions::Configure(Str opt) {
        // the format specifier follows: (?'char'.)?(?'align'[<^>])(?'len'[0-9]+)
        // 'char': fill character, 'align': left, middle (prioritize filling right) or right, 'len' is len
        TextFormatOptions options;
        if (!opt) return options;

        if (opt[0] != '<' && opt[0] != '^' && opt[0] != '>') {
            options.pad = opt[0];
            opt.Advance(1);
        }

        if (!opt) return options;
        if (opt[0] == '^') {
            options.alignment = CENTER;
        } else {
            options.alignment = (Alignment)(opt[0] - '<');
        }

        if (opt.Last() == '?') {
            options.escape = true;
            opt.Shorten(1);
        }
        if (!opt) return options;

        options.targetLength = Parse<usize>(opt.Tail()).Assert();

        return options;
    }

    usize Formatter<Str>::FormatTo(StringWriter sw, Str input, const FormatOptions& options) {
        if (options.alignment == TextFormatOptions::LEFT) {
            const usize len = options.escape ? input.WriteEscape(sw) : sw.Write(input);
            const usize m = std::max(len, options.targetLength);
            sw.WriteRepeat(options.pad, m - len);
            return m;
        }

        if (options.escape) {
            const String esc = input.Escape();
            return FormatNoEscape(sw, esc, options);
        } else {
            return FormatNoEscape(sw, input, options);
        }
    }

    usize Formatter<Str>::FormatNoEscape(StringWriter sw, Str input, const FormatOptions& options) {
        usize padLen = options.targetLength - input.Length();
        padLen &= -(padLen <= options.targetLength); // fun bithacks that turn negative numbers into 0
        const usize right = padLen * (usize)options.alignment / 2;

        return sw.WriteRepeat(options.pad, padLen - right) +
               sw.Write(input) +
               sw.WriteRepeat(options.pad, right);
    }

    usize Formatter<char>::FormatTo(StringWriter sw, char c, const FormatOptions& options) {
        if (options.escape) {
            char buf[4];
            return Formatter<Str>::FormatTo(sw,
                Str::Slice(buf, Chr::WriteEscape(c, buf)),
                { options.targetLength, options.alignment, options.pad, false }
            );
        } else {
            if (options.targetLength <= 1) {
                sw.Write(c);
                return 1;
            }

            const usize rest = options.targetLength - 1;
            switch (options.alignment) {
                case TextFormatOptions::LEFT: {
                    sw.WriteRepeat(options.pad, rest);
                    sw.Write(c);
                    break;
                }
                case TextFormatOptions::CENTER: {
                    sw.WriteRepeat(options.pad, rest / 2);
                    sw.Write(c);
                    sw.WriteRepeat(options.pad, rest - rest / 2);
                    break;
                }
                case TextFormatOptions::RIGHT: {
                    sw.Write(c);
                    sw.WriteRepeat(options.pad, rest);
                    break;
                }
                default:;
            }
            return options.targetLength;
        }
    }

    usize Formatter<void*>::FormatTo(StringWriter sw, void* fres, Str) {
        sw.Write("(address at 0x");
        NumberConversion::WriteU64Hex(sw, reinterpret_cast<u64>(fres), u64s::HEX_DIGITS, true);
        sw.Write(')');
        return Q_STRLIT_LEN("(address at 0x)") + u64s::HEX_DIGITS;
    }
}
