#pragma once
#include "Utils/Option.h"
#include "Utils/Str.h"

namespace Quasi::Text {
    /* required methods:
     * usize ParseUntil(Str string, T& out, const ParseOptions& options);
     * (optional) ParseOptions ConfigureOptions(Str out);
     */
    template <class T> struct Parser {};

    template <class T>
    OptionUsize ParseUntil(Str string, Out<T&> out, const typename Parser<T>::ParseOptions& options = {}) {
        return Parser<T>::ParseUntil(string, out, options);
    }

    template <class T>
    OptionUsize ParseUntil(Str string, Out<T&> out, Str options) {
        if constexpr (requires (Str x) { Parser<T>::ConfigureOptions(x); })
            return Text::ParseUntil(string, out, Parser<T>::ConfigureOptions(options));
        else return Parser<T>::ParseUntil(string, out, options);
    }

    template <class T>
    Option<T> Parse(Str string, const typename Parser<T>::ParseOptions& options = {}) {
        T value;
        const OptionUsize i = Text::ParseUntil(string, value, options);
        return i == string.Length() ? Options::Some(value) : nullptr;
    }

    template <class T>
    Option<T> Parse(Str string, Str options) {
        if constexpr (requires (Str x) { Parser<T>::ConfigureOptions(x); })
            return Text::Parse<T>(string, Parser<T>::ConfigureOptions(options));
        else return Text::Parse<T>(string, options);
    }

    template <class T>
    Tuple<OptionUsize, Option<T>> ParsePartial(Str string, const typename Parser<T>::ParseOptions& options = {}) {
        T value;
        const OptionUsize i = ParseUntil(string, value, options);
        if (i) return { i, value }; else return { nullptr, nullptr };
    }

    template <class T>
    Tuple<OptionUsize, Option<T>> ParsePartial(Str string, Str options) {
        return ParsePartial<T>(string, Parser<T>::ConfigureOptions(options));
    }

    struct TextParseOptions {
        enum Enum : u32 {
            ESCAPE         = 1 << 0,
            QUOTED         = 1 << 1,
            SINGLE_QUOTES  = 1 << 2,
            DOUBLE_QUOTES  = 1 << 3,
            ANY_QUOTES     = SINGLE_QUOTES | DOUBLE_QUOTES,
            GENERAL        = ESCAPE | QUOTED | ANY_QUOTES,
        } features = GENERAL;
    };

    template <>
    struct Parser<char> {
        using ParseOptions = TextParseOptions;
        static OptionUsize ParseUntil   (Str string, Out<char&> out, ParseOptions options);
        static OptionUsize ParseUnquoted(Str string, Out<char&> out, bool allowEscape);
    };

    template <>
    struct Parser<String> {
        using ParseOptions = TextParseOptions;
        static OptionUsize ParseUntil   (Str string, Out<String&> out, ParseOptions options);
        static OptionUsize ParseUnquoted(Str string, Out<String&> out, bool allowEscape, Option<char> endString);
        static OptionUsize ParseHex     (Str string, Out<String&> out);
        static OptionUsize ParseOctal   (Str string, Out<String&> out);
        static OptionUsize ParseUnicode (Str string, Out<String&> out);
    };
}
