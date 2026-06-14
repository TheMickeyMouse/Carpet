#include "CStr.h"

#include "Hash.h"
#include "Span.h"
#include "Str.h"
#include "String.h"

namespace Quasi {
    Option<CStr> CStr::TrySlice(const char* data, usize size) {
        return data[size] == '\0' ? Options::Some(CStr { data, size }) : nullptr;
    }

    CStr CStr::SliceUnchecked(const char* data, usize size) {
        return { data, size };
    }

    Option<CStr> CStr::TryFrom(Str s) {
        return s[s.Length()] == '\0' ? Options::Some(CStr { s.Data(), s.Length() }) : nullptr;
    }

    Option<CStr> CStr::TryFromWithNull(Str zs) {
        return TryFrom(zs.Init());
    }

    CStr CStr::FromUnchecked(Str s) {
        return SliceUnchecked(s.Data(), s.Length());
    }

    Str CStr::AsStr()                        const { return Str::Slice(data, size); }
    Str CStr::AsStrWithNull()                const { return Str::Slice(data, size + 1); }
    Span<const char> CStr::AsSpan()          const { return Spans::Slice(data, size); }
    Span<const char> CStr::AsSpanWithNull()  const { return Spans::Slice(data, size + 1); }
    Span<const byte> CStr::AsBytes()         const { return Spans::Slice(Memory::AsBytePtr(data), size); }
    Span<const byte> CStr::AsBytesWithNull() const { return Spans::Slice(Memory::AsBytePtr(data), size + 1); }
    CStr::operator Str() const { return AsStr(); }

    Str CStr::First(usize num) const { return Str::Slice(data, num); }
    CStr CStr::Skip(usize len) const { return SliceUnchecked(data, len); }
    CStr CStr::Tail() const { return SliceUnchecked(data + 1, size - 1); }
    CStr CStr::Last(usize num) const { return SliceUnchecked(data + size - num, num); }
    Str CStr::Trunc(usize len) const { return Str::Slice(data, size - len); }
    Str CStr::Init() const { return Str::Slice(data, size - 1); }

    Tuple<const char&, CStr> CStr::SplitFirst() const { return { this->First(), Tail() }; }
    Tuple<Str, const char&> CStr::SplitLast() const { return { Init(), Last() }; }
    Tuple<Str, CStr> CStr::SplitAt(usize at) const { return { First(at), Skip(at) }; }
    Tuple<Str, const char&, CStr> CStr::PartitionAt(usize at) const { return { First(at), At(at), Skip(at + 1) }; }

    CStr& CStr::Advance(usize num) {
        data += num;
        size -= num;
        return *this;
    }

    Str CStr::TakeFirst(usize i) {
        const Str first = First(i);
        data += i;
        return first;
    }

    const char& CStr::TakeFirst() {
        const char& first = this->First();
        ++data;
        return first;
    }

    CStr operator ""_cstr(const char* zstr, usize len) {
        return CStr::SliceUnchecked(zstr, len);
    }
}
