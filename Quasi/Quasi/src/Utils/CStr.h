#pragma once
#include "Str.h"

namespace Quasi {
    struct CStr : StringHolder<const char, CStr> {
        friend IContinuous;
        friend StringHolder;
    private:
        const char* data = nullptr;
        usize size = 0;
        CStr(const char* data, usize size) : data(data), size(size) {}
    public:
        CStr() = default;
        CStr(Nullptr) : CStr() {}
        CStr(const char* zstr) : data(zstr) { while (data[size]) ++size; }
    protected:
        const char* DataImpl() const { return data; }
        usize LengthImpl()     const { return size; }
    public:
        static CStr Empty() { return nullptr; }
        static Option<CStr> TrySlice(const char* data, usize size);
        static CStr SliceUnchecked(const char* data, usize size);

        static Option<CStr> TryFrom(Str s);
        static Option<CStr> TryFromWithNull(Str zs);
        static CStr FromUnchecked(Str s);

        const char* DataEndWithNull() const { return data + size + 1; }
        usize LengthWithNull() const { return size + 1; }

        bool IsEmpty()           const { return size == 0; }
        explicit operator bool() const { return size != 0; }

        // CharsIter Chars() const;
        // Utf8CharsIter Utf8Chars() const;
        // SplitWhitespaceIter SplitWhitespace() const;
        // LinesIter Lines() const;

        Str              AsStr()           const;
        Str              AsStrWithNull()   const;
        Span<const char> AsSpan()          const;
        Span<const char> AsSpanWithNull()  const;
        Span<const byte> AsBytes()         const;
        Span<const byte> AsBytesWithNull() const;
        operator Str() const;

        using StringHolder::First;
        using StringHolder::Last;
        Str  First(usize num) const;
        CStr Skip(usize len)  const;
        CStr Tail()           const;
        CStr Last(usize num)  const;
        Str  Trunc(usize len) const;
        Str  Init()           const;
        Tuple<const char&, CStr>      SplitFirst()                            const;
        Tuple<Str, const char&>       SplitLast()                             const;
        Tuple<Str, CStr>              SplitAt   (usize at)                    const;
        Tuple<Str, const char&, CStr> PartitionAt(usize at)                   const;
        Tuple<Str, CStr>              SplitOn(Predicate<char> auto&& pred)    const {
            const usize i = FindIf(pred);
            return SplitAt(i == -1 ? Length() : i);
        }
        Tuple<Str, CStr>              RevSplitOn(Predicate<char> auto&& pred) const {
            const usize i = RevFindIf(pred);
            return SplitAt(i == -1 ? 0 : i + 1);
        }

        CStr&       Advance(usize num);
        Str         TakeFirst(usize i);
        const char& TakeFirst();
    };

    CStr operator ""_cstr(const char* zstr, usize len);
}
