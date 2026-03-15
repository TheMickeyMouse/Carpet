#pragma once
#include "Utils/Numeric.h"
#include "Formatting.h"
#include "Parsing.h"

namespace Quasi::Text {
#pragma region Format
    template <> struct Formatter<bool> : Formatter<Str> {
        using FormatOptions = TextFormatOptions;
        static usize FormatTo(StringWriter sw, bool input, const FormatOptions& options);
    };

    struct IntFormatter {
        // see python's int options
        struct FormatOptions {
            u32 numLen = 0;
            u32 width = 0;

            TextFormatOptions::Alignment alignment = TextFormatOptions::LEFT;
            char pad = ' ';
            bool showSign = false, shouldPadZero = false, showPrefix = false;
            enum Base { DECIMAL, BINARY, OCTAL, HEX, CAP_HEX } base = DECIMAL;
        };
        static FormatOptions ConfigureOptions(Str opt);
        template <class N> static usize FormatTo(StringWriter sw, N num, const FormatOptions& options);
    };

    template <> struct Formatter<u16> : IntFormatter {};
    template <> struct Formatter<i16> : IntFormatter {};
    template <> struct Formatter<u32> : IntFormatter {};
    template <> struct Formatter<i32> : IntFormatter {};
    template <> struct Formatter<u64> : IntFormatter {};
    template <> struct Formatter<i64> : IntFormatter {};

    struct FloatFormatter {
        // ((?'pad'.?)(?'align'[<^>])(?'totalLen'[0-9]+)\,)?(?'showSign'\+?)(?'shouldPadZero'0?)(?'width'[0-9]*)\.(?'precision'[0-9]*)(?'mode'[feEgG%])
        struct FormatOptions {
            u32 width = 0, precision = ~0;

            TextFormatOptions::Alignment alignment = TextFormatOptions::LEFT;
            char pad = ' ';
            bool showSign = false, shouldPadZero = false;
            enum Mode { SCIENTIFIC, FIXED, GENERAL, SCI_CAP, GEN_CAP, PERCENTAGE } mode = FIXED;
        };
        static FormatOptions ConfigureOptions(Str opt);
        template <class N> static usize FormatTo(StringWriter sw, N num, const FormatOptions& options);
    };

    template <> struct Formatter<f32> : FloatFormatter {};
    template <> struct Formatter<f64> : FloatFormatter {};
#pragma endregion

#pragma region Parse
    struct BoolParser {
        struct ParseOptions {
            enum {
                ALLOW_NUMERIC = 1, USE_WORDS = 2, GENERAL = ALLOW_NUMERIC | USE_WORDS
            } format = GENERAL;
        };
        static OptionUsize ParseUntil(Str string, Out<bool&> out, ParseOptions options);
    };

    template <> struct Parser<bool> : BoolParser {};

    struct IntParser {
        struct ParseOptions {
            enum {
                ADAPTIVE = 0,  BASE_N   = 0,
                BASE_2   = 2,  BINARY   = 2,
                BASE_10  = 10, DECIMAL  = 10,
                BASE_16  = 16, HEX      = 16,
            } radix = DECIMAL;
        };
        template <class N> static OptionUsize ParseUntil(Str string, Out<N&> out, ParseOptions options);
    };

    template <> struct Parser<u16> : IntParser {};
    template <> struct Parser<i16> : IntParser {};
    template <> struct Parser<u32> : IntParser {};
    template <> struct Parser<i32> : IntParser {};
    template <> struct Parser<u64> : IntParser {};
    template <> struct Parser<i64> : IntParser {};

    struct FloatParser {
        struct ParseOptions {
            enum {
                SCIENTIFIC = 1, FIXED = 2, GENERAL = SCIENTIFIC | FIXED,
            } format = GENERAL;
        };
    };

    namespace NumberConversion {
        template <class N>
        struct FloatConv {
            static OptionUsize ParseUntil(Str string, Out<N&> out, FloatParser::ParseOptions options);
            static usize ParseInteger(Str string, Out<N&> out);
            static usize ParseDecimal(Str string, InOut<N&> out);
            static OptionUsize ParseExponent(Str string, InOut<N&> out);
        };
    }

    template <> struct Parser<f32> : FloatParser, NumberConversion::FloatConv<f32> {};
    template <> struct Parser<f64> : FloatParser, NumberConversion::FloatConv<f64> {};
#pragma endregion

    namespace NumberConversion {
        bool AreAllHexDigits4(u32 digits);

        u32 ConvertHexDigits4(u32 chars);
        u64 ParseDigits8(u64 digits);
        u32 ParseDigits4(u32 digits);
        u32 ParseHexDigits4(u32 xdigits);

        OptionUsize ParseBinaryInt (Str string, Out<u64&> out, u32 bits);
        OptionUsize ParseDecimalInt(Str string, Out<u64&> out, u32 bits);
        OptionUsize ParseHexInt    (Str string, Out<u64&> out, u32 bits);
        OptionUsize ParseRadixInt  (Str string, Out<u64&> out, u32 bits, u32 radix);
        template <Integer I>
        OptionUsize ParseInt(Str string, Out<I&> out, IntParser::ParseOptions options);

        template <Floating F>
        OptionUsize ParseNanOrInf(Str string, Out<F&> out);

        // formatting functions
        u64 U64ToBCD2(u64 x);
        u64 U64ToBCD4(u64 x);
        u64 U64ToBCD8(u64 x);

        u32 SmallU64ToString(u64 x, char* out);
		u32 U64ToString     (u64 x, char* out);
		u32 U64FullToString (u64 x, char* out);
        usize FormatU64(StringWriter sw, u64 num, const IntFormatter::FormatOptions& options, char sign = '\0');
        usize FormatI64(StringWriter sw, i64 num, const IntFormatter::FormatOptions& options);

        void WriteU64Decimal(StringWriter sw, u64 num);
        void WriteU64Binary (StringWriter sw, u64 num, u32 bitwidth);
        void WriteU64Octal  (StringWriter sw, u64 num, u32 octalDigits);
        void WriteU64Hex    (StringWriter sw, u64 num, u32 hexDigits, bool upperCase);

        char* AddSign(f64 f, char* out, bool alwaysShowSign = false);
        char* WriteFltDecimal(f64 f, char* out, u32 precision = ~0);
        char* WriteFltSci(f64 f, char* out, u32 precision = ~0, char e = 'e', int log10 = i32s::MIN);
        char* WriteFltFxd(f64 f, char* out, u32 width = 0, u32 precision = ~0, int log10 = i32s::MIN, char pad = ' ');
        char* WriteFltGen(f64 f, char* out, u32 width = 0, u32 precision = ~0, char e = 'e');

        usize FormatFltSci  (StringWriter sw, f64 f, const FloatFormatter::FormatOptions& options);
        usize FormatFltFxd  (StringWriter sw, f64 f, const FloatFormatter::FormatOptions& options);
        usize FormatFloating(StringWriter sw, f64 f, const FloatFormatter::FormatOptions& options);
    }

    template <class N> usize FloatFormatter::FormatTo(StringWriter sw, N num, const FormatOptions& options) {
        return NumberConversion::FormatFloating(sw, num, options);
    }

    template <class N> OptionUsize IntParser::ParseUntil(Str string, Out<N&> out, ParseOptions options) {
        return NumberConversion::ParseInt(string, out, options);
    }

    template <>
    struct Formatter<OptionUsize> : Formatter<usize> {
        using Formatter<usize>::FormatOptions;
        static usize FormatTo(StringWriter sw, OptionUsize n, const FormatOptions& options) {
            if (n) {
                sw.Write("Some("_str);
                const usize i = Formatter<usize>::FormatTo(sw, *n, options);
                sw.Write(')');
                return i + 6;
            } else { sw.Write("None"_str); return 4; }
        }
    };
}
