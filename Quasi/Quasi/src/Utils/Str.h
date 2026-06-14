#pragma once
#include "Continuous.h"

namespace Quasi {
    namespace Text {
        struct StringWriter;
    }

    namespace Iter {
        struct LinesIter;
    }

    struct Str;
    struct StrMut;
    struct String;
    struct CStr;

    template <class... Ts> struct Tuple;

    namespace Chr {
        constexpr char  NULL_TERM = '\0',
                        MIN       = '\0',
                        MAX       = 127,
                        SMIN      = -128;
        constexpr uchar UMAX      = 255;

        char FromDigit(u32 digit), FromHexDigit(u32 digit); // hex digits are uppercase
        u32  ToDigit(char digit),  ToHexDigit(char digit); // any case is allowed
        Option<char> TryFromDigit(u32 digit), TryFromHexDigit(u32 digit), TryFromDigitRadix(u32 digit, u32 radix);
        Option<u32>  TryToDigit(char digit),  TryToHexDigit(char digit),  TryToDigitRadix(char digit, u32 radix); // any case is allowed

        bool IsDigit(char digit), IsHexDigit(char digit), IsDigitRadix(char digit, u32 radix);

        Option<char> EscapeRepr(char c);
        usize WriteEscape(char c, char* out);
        Option<char> UnescapeRepr(char c);

        bool IsAscii(char c), IsNonAscii(char c);

        char ToLower(char c), ToUpper(char c);
        bool IsLower(char c), IsUpper(char c);

        bool IsBlank(char c), IsWhitespace(char c), IsAlpha(char c), IsNumeric(char c), IsAlphaNum(char c);
        bool IsPrintable(char c), IsControl(char c), IsGraphic(char c), IsPunct(char c);

        struct Set {
            u64 bitmask[4] {};
            Set(Span<const char> chars);
            bool operator()(char c) const;
            bool operator()(Str str) const;
        };
    }

    template <class Char, class Super>
    struct StringHolder : IContinuous<Char, Super> {
        friend IContinuous<Char, Super>;
    private:
        static constexpr bool mut = IsMut<Char>;

        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }
    public:
        bool IsEmpty()           const { return super().Length() == 0; }
        explicit operator bool() const { return super().Length() != 0; }

        Hashing::Hash GetHashCode() const;

        const char& At(usize i)              const { return super().DataImpl()[i]; }
        char& At(usize i)             requires mut { return super().DataImpl()[i]; }
        const char& AtWrap(WrappingIndex i)  const { return At(i(super().LengthImpl())); }
        char& AtWrap(WrappingIndex i) requires mut { return At(i(super().LengthImpl())); }

        BufferIterator<const char&> Iter() const;
        BufferIterator<char&> IterMut() requires mut;
        // Utf8CharsIter Utf8Chars() const;
        // SplitWhitespaceIter SplitWhitespace() const;
        Iter::SplitIter<Str> Split(Str sep) const;
        Iter::LinesIter Lines() const;
        usize CountLines() const;
        usize CountChars(char c) const;

        Str              AsStr()      const;
        StrMut           AsStrMut()   requires mut;
        Span<const char> AsSpan()     const;
        Span<char>       AsSpanMut()  requires mut;
        Span<const byte> AsBytes()    const;
        Span<byte>       AsBytesMut() requires mut;
        operator Str() const;
        operator StrMut() requires mut;

        char&       FirstMut() requires mut { return At(0); }
        char&       LastMut()  requires mut { return At(super().LengthImpl() - 1); }
        const char& First()    const        { return At(0); }
        const char& Last()     const        { return At(super().LengthImpl() - 1); }
        OptRef<char>       TryFirstMut() requires mut;
        OptRef<char>       TryLastMut()  requires mut;
        OptRef<const char> TryFirst()    const;
        OptRef<const char> TryLast()     const;

        Span<const char> Subspan   (usize start) const;
        Str              Substr    (usize start) const;
        Span<const char> Subspan   (usize start, usize count) const;
        Str              Substr    (usize start, usize count) const;
        Span<char>       SubspanMut(usize start) requires mut;
        StrMut           SubstrMut (usize start) requires mut;
        Span<char>       SubspanMut(usize start, usize count) requires mut;
        StrMut           SubstrMut (usize start, usize count) requires mut;

        StrMut           FirstMut(usize num) requires mut;
        StrMut           SkipMut(usize len)  requires mut;
        StrMut           TailMut()           requires mut;
        StrMut           LastMut(usize num)  requires mut;
        StrMut           TruncMut(usize len) requires mut;
        StrMut           InitMut()           requires mut;
        Tuple<char&,  StrMut>        SplitFirstMut()      requires mut;
        Tuple<StrMut, char&>         SplitLastMut()       requires mut;
        Tuple<StrMut, StrMut>        CutAtMut(usize at)   requires mut;
        Tuple<StrMut, StrMut>        SplitAtMut(usize at) requires mut;
        Tuple<StrMut, char&, StrMut> PartitionAtMut(usize at) requires mut;
        Tuple<StrMut, StrMut>        SplitOnMut(Predicate<char> auto&& pred) requires mut;
        Tuple<StrMut, StrMut>        RevSplitOnMut(Predicate<char> auto&& pred) requires mut;
        Tuple<StrMut, StrMut>        SplitOnceMut(char c) requires mut;

        Str First(usize num) const;
        Str Skip(usize len)  const;
        Str Tail()           const;
        Str Last(usize num)  const;
        Str Trunc(usize len) const;
        Str Init()           const;
        Tuple<const char&, Str>      SplitFirst()                            const;
        Tuple<Str, const char&>      SplitLast()                             const;
        Tuple<Str, Str>              CutAt(usize at)                         const;
        Tuple<Str, Str>              SplitAt(usize at)                       const;
        Tuple<Str, const char&, Str> PartitionAt(usize at)                   const;
        Tuple<Str, Str> SplitOnceOn(Predicate<char> auto&& pred) const;
        Tuple<Str, Str> RevSplitOnceOn(Predicate<char> auto&& pred) const;
        Tuple<Str, Str> SplitOnce(char c) const;
        Tuple<Str, Str> SplitOnce(Str sep) const;

        bool RefEquals     (Str other) const;
        bool ContainsBuffer(Str buf)   const;
        bool OverlapsBuffer(Str buf)   const;

        bool Equals          (Str other) const;
        bool EqualsIgnoreCase(Str other) const;
        bool operator==      (Str other) const;
        bool operator==      (const String& other) const;
        bool operator==      (const char* other) const;
        template <usize N> bool operator==(const char other[N]) const { return Equals(other); }

        Comparison Cmp(Str other) const;
        Comparison CmpSized(Str other) const;
        Comparison operator<=>(Str other) const;

        bool All(Predicate<char> auto&& pred = Combinate::Identity {}) const { return AsSpan().All(pred); }
        bool Any(Predicate<char> auto&& pred = Combinate::Identity {}) const { return AsSpan().Any(pred); }

        void Reverse() requires mut;

        OptionUsize FindIf(Predicate<char> auto&& pred) const {
            for (usize i = 0; i < super().LengthImpl(); ++i)
                if (pred(At(i))) return i;
            return nullptr;
        }
        OptionUsize RevFindIf(Predicate<char> auto&& pred) const {
            for (usize i = super().LengthImpl(); i --> 0; )
                if (pred(At(i))) return i;
            return nullptr;
        }
        bool ContainsIf   (Predicate<char> auto&& pred) const { return FindIf(pred); }
        bool RevContainsIf(Predicate<char> auto&& pred) const { return RevFindIf(pred); }
        OptionUsize Find       (char c) const;
        OptionUsize RevFind    (char c) const;
        bool        Contains   (char c) const;
        bool        RevContains(char c) const;
        OptionUsize Find       (Str str) const;
        OptionUsize RevFind    (Str str) const;
        bool        Contains   (Str str) const;
        bool        RevContains(Str str) const;
        Tuple<OptionUsize, OptionUsize> FindOneOf       (Span<const char> anyc) const;
        Tuple<OptionUsize, OptionUsize> RevFindOneOf    (Span<const char> anyc) const;
        OptionUsize                     ContainsOneOf   (Span<const char> anyc) const;
        OptionUsize                     RevContainsOneOf(Span<const char> anyc) const;
        Tuple<OptionUsize, OptionUsize> FindOneOf       (Span<const Str> anystr) const;
        Tuple<OptionUsize, OptionUsize> RevFindOneOf    (Span<const Str> anystr) const;
        OptionUsize                     ContainsOneOf   (Span<const Str> anystr) const;
        OptionUsize                     RevContainsOneOf(Span<const Str> anystr) const;

        bool  StartsWith(char prefix) const;
        bool  EndsWith  (char suffix) const;
        bool  StartsWith(Str prefix) const;
        bool  EndsWith  (Str suffix) const;
        OptionUsize StartsWithOneOf(Span<const char> anyprefix) const;
        OptionUsize EndsWithOneOf  (Span<const char> anysuffix) const;
        OptionUsize StartsWithOneOf(Span<const Str> anyprefix) const;
        OptionUsize EndsWithOneOf  (Span<const Str> anysuffix) const;

        Str TrimIf     (Predicate<char> auto&& pred) const;
        Str TrimStartIf(Predicate<char> auto&& pred) const;
        Str TrimEndIf  (Predicate<char> auto&& pred) const;
        Str Trim     () const;
        Str TrimStart() const;
        Str TrimEnd  () const;
        Str Trim     (char c) const;
        Str TrimStart(char c) const;
        Str TrimEnd  (char c) const;
        Str TrimOneOf     (Span<const char> anyc) const;
        Str TrimStartOneOf(Span<const char> anyc) const;
        Str TrimEndOneOf  (Span<const char> anyc) const;
        StrMut TrimIfMut     (Predicate<char> auto&& pred) requires mut;
        StrMut TrimStartIfMut(Predicate<char> auto&& pred) requires mut;
        StrMut TrimEndIfMut  (Predicate<char> auto&& pred) requires mut;
        StrMut TrimMut     () requires mut;
        StrMut TrimStartMut() requires mut;
        StrMut TrimEndMut  () requires mut;
        StrMut TrimMut     (char c) requires mut;
        StrMut TrimStartMut(char c) requires mut;
        StrMut TrimEndMut  (char c) requires mut;
        StrMut TrimOneOfMut     (Span<const char> anyc) requires mut;
        StrMut TrimStartOneOfMut(Span<const char> anyc) requires mut;
        StrMut TrimEndOneOfMut  (Span<const char> anyc) requires mut;

        Str RemovePrefix(char prefix) const;
        Str RemoveSuffix(char suffix) const;
        Str RemovePrefix(Str prefix) const;
        Str RemoveSuffix(Str suffix) const;
        Str RemovePrefixOneOf(Span<const char> prefix) const;
        Str RemoveSuffixOneOf(Span<const char> suffix) const;
        Str RemovePrefixOneOf(Span<const Str> prefix) const;
        Str RemoveSuffixOneOf(Span<const Str> suffix) const;
        StrMut RemovePrefixMut(char prefix) requires mut;
        StrMut RemoveSuffixMut(char suffix) requires mut;
        StrMut RemovePrefixMut(Str prefix) requires mut;
        StrMut RemoveSuffixMut(Str suffix) requires mut;
        StrMut RemovePrefixOneOfMut(Span<const char> prefix) requires mut;
        StrMut RemoveSuffixOneOfMut(Span<const char> suffix) requires mut;
        StrMut RemovePrefixOneOfMut(Span<const Str> prefix) requires mut;
        StrMut RemoveSuffixOneOfMut(Span<const Str> suffix) requires mut;

        Iter::SplitIter<Str> Split(Str sep);

        // SplitIfIter           SplitIf(Fn<bool, char> pred)
        // SplitIfInclIter       SplitIfIncl(Fn<bool, char> pred)
        // RevSplitIter          RevSplit(const char sep)
        // RevSplitIfIter        RevSplitIf(Fn<bool, char> pred)
        // SplitAtmostIfIter     SplitIfAtmost(usize maxLen, Fn<bool, char, char> pred)
        // RevSplitAtmostIfIter  RevSplitIfAtmost(usize maxLen, Fn<bool, char, char> pred)
        // SplitTermIter         SplitTerms()
        // blah blah
        // MatchIter             Matches(...)
        // MatchIndiciesIter     MatchesIndices(...)

        // EscapeIter Escaped();
        // EscapeUtf8Iter EscapedUtf8();
        String ToString() const;
        String Reversed() const;

        String ToUpper() const;
        String ToLower() const;
        void MakeUpper() requires mut;
        void MakeLower() requires mut;

        String Repeat(usize n) const;

        String Replace(char from, Str to) const;
        String Replace(Str  from, Str to) const;
        String ReplaceAnyOf(Span<const char> from, Str to) const;
        String ReplaceAnyOf(Span<const Str>  from, Str to) const;
        String ReplaceIf(Fn<usize, Str> auto&& pred, Str to) const;
    };

    struct Str : StringHolder<const char, Str> {
        friend IContinuous;
        friend StringHolder;
        using StringHolder::operator==;
        using StringHolder::operator<=>;
    private:
        const char* data = nullptr;
        usize size = 0;
        constexpr Str(const char* data, usize size) : data(data), size(size) {}
    protected:
        const char* DataImpl() const { return data; }
        usize LengthImpl()     const { return size; }
    public:
        constexpr Str() = default;
        constexpr Str(Nullptr) : Str() {}
        constexpr Str(const char* zstr) : data(zstr) { while (data[size]) ++size; }

        static constexpr Str Empty() { return nullptr; }
        static constexpr Str Slice(const char* data, usize size) { return { data, size }; }

        Str&        Advance(usize num);
        Str&        Shorten(usize amount);
        Str         TakeFirst(usize num);
        Str         TakeLast(usize num);
        const char& TakeFirst();
        const char& TakeLast();
        Str         TakeAfter(usize i);

        String Escape() const;
        usize WriteEscape(Text::StringWriter output) const;
        Option<String> Unescape() const;

        StrMut AsMut();
    };

    struct StrMut : StringHolder<char, StrMut> {
        friend IContinuous;
        friend StringHolder;
        using StringHolder::operator==;
        using StringHolder::operator<=>;
    private:
        char* data = nullptr;
        usize size = 0;
        StrMut(char* data, usize size) : data(data), size(size) {}
    protected:
        const char* DataImpl() const { return data; }
        char* DataImpl()          { return data; }
        usize LengthImpl()     const { return size; }
    public:
        StrMut() = default;
        StrMut(Nullptr) : StrMut() {}

        static StrMut Empty() { return nullptr; }
        static StrMut Slice(char* data, usize size) { return { data, size }; }

        StrMut&     Advance(usize num);
        StrMut&     Shorten(usize amount);
        StrMut      TakeFirstMut(usize num);
        StrMut      TakeLastMut(usize num);
        char&       TakeFirstMut();
        char&       TakeLastMut();
        StrMut      TakeAfterMut(usize i);
        Str         TakeFirst(usize num);
        Str         TakeLast(usize num);
        const char& TakeFirst();
        const char& TakeLast();
        Str         TakeAfter(usize i);

        Str AsConst() const { return AsStr(); }
    };

    constexpr Str operator ""_str(const char* data, usize size) {
        return Str::Slice(data, size);
    }

#define strdef template <class Char, class Super>
#define strcls StringHolder<Char, Super>
    strdef Tuple<StrMut, StrMut> strcls::SplitOnMut(Predicate<char> auto&& pred) requires mut {
        const OptionUsize i = FindIf(pred);
        return SplitAtMut(i.UnwrapOr(super().LengthImpl()));
    }
    strdef Tuple<StrMut, StrMut> strcls::RevSplitOnMut(Predicate<char> auto&& pred) requires mut {
        const OptionUsize i = RevFindIf(pred);
        return SplitAtMut(i.UnwrapOr(0));
    }
    strdef Tuple<StrMut, StrMut> strcls::SplitOnceMut(char c) requires mut {
        const OptionUsize i = Find(c);
        return SplitAtMut(i.UnwrapOr(super().LengthImpl()));
    }
    strdef Tuple<Str, Str> strcls::SplitOnceOn(Predicate<char> auto&& pred) const {
        const OptionUsize i = FindIf(pred);
        return SplitAt(i.UnwrapOr(super().LengthImpl()));
    }
    strdef Tuple<Str, Str> strcls::RevSplitOnceOn(Predicate<char> auto&& pred) const {
        const OptionUsize i = RevFindIf(pred);
        return SplitAt(i.UnwrapOr(0));
    }
    strdef Str strcls::TrimIf(Predicate<char> auto&& pred) const {
        return TrimStartIf(pred).TrimEndIf(pred);
    }
    strdef Str strcls::TrimStartIf(Predicate<char> auto&& pred) const {
        usize beg = 0;
        while (beg < super().LengthImpl() && pred(At(beg))) ++beg;
        return Skip(beg);
    }
    strdef Str strcls::TrimEndIf(Predicate<char> auto&& pred) const {
        usize end = super().LengthImpl();
        while (end --> 0 && pred(At(end))) {}
        return First(end + 1);
    }
    strdef StrMut strcls::TrimIfMut(Predicate<char> auto&& pred) requires mut {
        return TrimStartIfMut(pred).TrimEndIfMut(pred);
    }
    strdef StrMut strcls::TrimStartIfMut(Predicate<char> auto&& pred) requires mut {
        usize beg = 0;
        while (beg < super().LengthImpl() && pred(At(beg))) ++beg;
        return SkipMut(beg);
    }
    strdef StrMut strcls::TrimEndIfMut(Predicate<char> auto&& pred) requires mut {
        usize end = super().LengthImpl();
        while (end --> 0 && pred(At(end))) {}
        return FirstMut(end + 1);
    }
#undef strdef
#undef strcls

    template <class T, class Super>
    Str    IContinuous<T, Super>::AsStr() const requires (sizeof(T) == sizeof(char)) { return Str::Slice((const char*)Data(), Length()); }
    template <class T, class Super>
    StrMut IContinuous<T, Super>::AsStrMut() requires (sizeof(T) == sizeof(char)) && IsMut<T> { return StrMut::Slice((char*)Data(), Length()); }
} // Quasi
