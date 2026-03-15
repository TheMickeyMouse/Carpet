#include "String.h"

#include "CStr.h"
#include "Text/StringWriter.h"

namespace Quasi {
    String String::WithCap(usize cap) {
        if (cap <= Small::MAXLEN) {
            return Empty();
        } else {
            return Large { 1, cap, AllocateString(cap) };
        }
    }

    String String::FromChars(Vec<char> chars) {
        if (chars.Length() <= Small::MAXLEN) {
            String string;
            Memory::MemCopyNoOverlap(string.small.data, chars.Data(), chars.Length());
            string.small.SetSize(chars.Length());
            return string;
        } else {
            const auto [data, size, capacity] = chars.Decompose();
            return Large { size * 2 + 1, capacity, data };
        }
    }

    String String::FromChars(Span<const char> chars) {
        if (chars.Length() <= Small::MAXLEN) {
            String string;
            Memory::MemCopyNoOverlap(string.small.data, chars.Data(), chars.Length());
            string.small.SetSize(chars.Length());
            return string;
        } else {
            char* str = AllocateString(chars.Length());
            Memory::MemCopyNoOverlap(str, chars.Data(), chars.Length());
            return Large { chars.Length() * 2 + 1, chars.Length(), str };
        }
    }

    String String::FromStr(Str str) {
        return FromChars(str.AsSpan());
    }

    String String::Compose(char* data, usize size, usize cap) {
        return FromChars(Vec<char>::Compose(data, size, cap));
    }

    String String::Clone() const {
        return FromChars(AsSpan());
    }

    String::String(const String& s) : String(s.Clone()) { }
    String& String::operator=(const String& s) {
        this->~String();
        Memory::ConstructCopyAt(this, s);
        return *this;
    }

    String::String(String&& s) noexcept {
        if (s.IsSmallString()) {
            small = Small { s.small };
        } else {
            large = Large { s.large.sizePackedFlag, s.large.cap, s.large.data };
            s.SetEmptyUnsafe();
        }
    }

    String& String::operator=(String&& s) noexcept {
        this->~String();
        Memory::ConstructMoveAt(this, std::move(s));
        return *this;
    }

    String::~String() {
        if (IsLargeString()) {
            Memory::FreeRaw(large.data);
        }
    }

    usize String::GrowCap(usize cap) {
        return cap * 3 / 2;
    }

    void String::OptimizeAsSmall() {
        char* string = large.data;
        const usize size = large.GetSize();
        Memory::MemCopyNoOverlap(small.data, string, size);
        small.SetSize(size);
        Memory::FreeRaw(string);
    }

    void String::CopyToLarge(char* dest, usize size) {
        const usize originalSize = small.GetSize();
        Memory::MemCopyNoOverlap(dest, small.data, originalSize);
        large.data = dest;
        large.cap  = size;
        large.SetSize(originalSize);
    }

    void String::MoveBuffer(char* dest, usize cap) {
        Memory::MemCopyNoOverlap(dest, large.data, large.GetSize());
        Memory::FreeRaw(large.data);
        large.data = dest;
        large.cap = cap;
    }

    char* String::AllocateString(usize size) {
        return (char*)Memory::AllocateRaw(size * sizeof(char));
    }

    bool String::CanFit(usize amount) const {
        return Length() + amount <= Capacity();
    }

    void String::TryGrow(usize amount) {
        if (!CanFit(amount)) Reserve(amount);
    }

    const char* String::DataImpl()   const { return IsSmallString() ? &small.data[0]   : large.data; }
    char*       String::DataImpl()         { return IsSmallString() ? &small.data[0]   : large.data; }
    usize       String::LengthImpl() const { return IsSmallString() ?  small.GetSize() : large.GetSize(); }
    usize       String::Capacity()   const { return IsSmallString() ? Small::MAXLEN    : large.cap; }

    void String::Reserve(usize extra) {
        if (IsSmallString()) {
            if (small.GetSize() + extra > Small::MAXLEN) {
                const usize newCap = std::max<usize>(32, small.GetSize() + extra);
                return CopyToLarge(AllocateString(newCap), newCap);
            }
        } else {
            if (large.GetSize() + extra > large.cap) {
                const usize newCap = std::max<usize>(GrowCap(large.cap), large.GetSize() + extra);
                return MoveBuffer(AllocateString(newCap), newCap);
            }
        }
    }

    void String::ReserveExact(usize extra) {
        if (IsSmallString() && small.GetSize() + extra > Small::MAXLEN) {
            const usize newCap = small.GetSize() + extra;
            return CopyToLarge(AllocateString(newCap), newCap);
        } else if (IsLargeString() && large.GetSize() + extra > large.cap) {
            const usize newCap = large.GetSize() + extra;
            return MoveBuffer(AllocateString(newCap), newCap);
        }
    }

    void String::Resize(usize size) {
        if (IsSmallString()) {
            if (size > Small::MAXLEN) {
                const usize newCap = std::max<usize>(32, size), original = small.GetSize();
                CopyToLarge(AllocateString(newCap), newCap);
                Memory::MemSet(large.data + original, 0, size - original);
            } else if (size <= small.GetSize()) {
                small.SetSize(size);
            } else {
                Memory::MemSet(&small.data[small.GetSize()], 0, size - small.GetSize());
                small.SetSize(size);
            }
        } else {
            if (size > large.cap) {
                const usize newCap = std::max<usize>(GrowCap(large.cap), size), original = large.GetSize();
                MoveBuffer(AllocateString(newCap), newCap);
                Memory::MemSet(large.data + original, 0, size - original);
            } else if (size > Small::MAXLEN) {
                large.SetSize(size);
            } else {
                char buf[24] { 0 };
                Memory::MemCopy(buf, large.data, size);
                Memory::MemCopy(small.data, buf, size);
                small.SetSize(size);
            }
        }
    }

    void String::SetEmptyUnsafe() {
        small = {};
    }

    Nullable<char*> String::ReleaseLargeString() {
        if (IsLargeString()) {
            char* string = large.data;
            large.data = nullptr;
            return string;
        }
        return nullptr;
    }

    Option<Vec<char>> String::IntoLargeString() {
        if (IsLargeString()) {
            char* string = large.data;
            const usize size = large.GetSize(), cap = large.cap;
            SetEmptyUnsafe();
            return Vec<char>::Compose(string, size, cap);
        }
        else return nullptr;
    }

    Option<StrMut> String::TryAsSmallString() {
        if (IsSmallString()) {
            return StrMut::Slice(small.data, small.GetSize());
        }
        return Option<StrMut>::None();
    }

    void String::TryOptimize() {
        if (IsLargeString() && large.GetSize() <= Small::MAXLEN) {
            OptimizeAsSmall();
        }
    }

    Vec<char> String::IntoChars() {
        if (IsLargeString()) {
            char* string = large.data;
            const usize size = large.GetSize(), cap = large.cap;
            SetEmptyUnsafe();
            return Vec<char>::Compose(string, size, cap);
        } else {
            Vec chars = Vec<char>::New(small.data);
            SetEmptyUnsafe();
            return chars;
        }
    }

    Vec<byte> String::IntoBytes() {
        const auto [data, size, capacity] = IntoChars().Decompose();
        return Vec<byte>::Compose((byte*)data, size, capacity);
    }

    ArrayBox<char> String::IntoBox() {
        if (IsLargeString()) {
            char* string = large.data;
            const usize size = large.GetSize();
            SetEmptyUnsafe();
            return ArrayBox<char>::Own(string, size);
        } else
            return nullptr;
    }

    void String::Append(char c) {
        TryGrow(1);
        if (IsSmallString()) {
            small.data[small.sizePackedFlag >> 1] = c;
            small.AddSize(1);
        } else {
            large.data[large.sizePackedFlag >> 1] = c;
            large.AddSize(1);
        }
    }

    void String::AppendStr(Str str) {
        TryGrow(str.Length());
        if (IsSmallString()) {
            Memory::MemCopyNoOverlap(&small.data[small.GetSize()], str.Data(), str.Length());
            small.AddSize(str.Length());
        } else {
            Memory::MemCopyNoOverlap(&large.data[large.GetSize()], str.Data(), str.Length());
            large.AddSize(str.Length());
        }
    }

    void String::Insert(char c, usize i) {
        TryGrow(1);
        if (IsSmallString()) {
            Memory::MemCopyRev(&small.data[i + 1], &small.data[i], small.GetSize() - i);
            small.data[i] = c;
            small.sizePackedFlag += 2;
        } else {
            Memory::MemCopyRev(&large.data[i + 1], &large.data[i], large.GetSize() - i);
            large.data[i] = c;
            large.sizePackedFlag += 2;
        }
    }

    void String::InsertStr(Str str, usize i) {
        TryGrow(str.Length());
        if (IsSmallString()) {
            Memory::MemCopyRev(&small.data[i + str.Length()], &small.data[i], small.GetSize() - i);
            Memory::MemCopyNoOverlap(&small.data[i], str.Data(), str.Length());
            small.AddSize(str.Length());
        } else {
            Memory::MemCopyRev(&large.data[i + str.Length()], &large.data[i], large.GetSize() - i);
            Memory::MemCopyNoOverlap(&large.data[i], str.Data(), str.Length());
            large.AddSize(str.Length());
        }
    }

    void String::AddNullTerm() {
        return Append('\0');
    }

    void String::TruncNullTerm() {
        if (Last() == '\0')
            Truncate(Length() - 1);
    }

    CStr String::IntoCStr() {
        AddNullTerm();
        return CStr::SliceUnchecked(DataImpl(), LengthImpl() - 1);
    }

    char String::Pop() {
        if (IsSmallString()) {
            return small.data[(small.sizePackedFlag -= 2) >> 1];
        } else {
            const char last = large.data[(small.sizePackedFlag -= 2) >> 1];
            if (large.GetSize() <= Small::MAXLEN)
                OptimizeAsSmall();
            return last;
        }
    }
    char String::Pop(usize index) {
        if (IsSmallString()) {
            const char out = small.data[index];
            Memory::MemCopy(&small.data[index], &small.data[index + 1], small.GetSize() - index);
            small.sizePackedFlag -= 2;
            return out;
        } else {
            const char out = large.data[index];
            if (large.GetSize() - 1 <= Small::MAXLEN) {
                char* str = large.data;
                const usize size = large.GetSize();
                SetEmptyUnsafe();
                Memory::MemCopyNoOverlap( small.data,         str,            index);
                Memory::MemCopyNoOverlap(&small.data[index], &str[index + 1], size - index - 1);
                Memory::FreeRaw(str);
                small.SetSize(size);
            } else {
                Memory::MemCopy(&large.data[index], &large.data[index + 1], large.GetSize() - index - 1);
                large.sizePackedFlag -= 2;
            }
            return out;
        }
    }

    void String::RemoveAllOf(char c) {
        return RemoveIf([=] (Str s) { return s[0] == c ? 1 : 0; });
    }

    void String::RemoveAllOf(Str str) {
        if (str.IsEmpty()) return;
        return RemoveIf([&] (Str s) { return s.StartsWith(str) ? str.Length() : 0; });
    }

    void String::RemoveAllOfEach(Span<const char> anyc) {
        if (anyc.IsEmpty()) return;
        const Chr::Set set = { anyc };
        return RemoveIf([&] (Str s) { return set(s[0]) ? 1 : 0; });
    }

    void String::RemoveAllOfEach(Span<const Str> anystr) {
        if (anystr.IsEmpty()) return;
        return RemoveIf([&] (Str str) {
           const OptionUsize i = str.StartsWithOneOf(anystr);
           return i ? anystr[*i].Length() : 0;
        });
    }

    void String::Clear() {
        if (IsLargeString())
            large.sizePackedFlag = 1;
        else
            small.sizePackedFlag = 0;
    }

    String String::SplitOff(usize index) {
        String right = FromStr(Substr(index));
        if (IsSmallString()) {
            small.SetSize(index);
        } else if (IsLargeString()) {
            large.SetSize(index);
            if (index <= Small::MAXLEN) {
                OptimizeAsSmall();
            }
        }
        return right;
    }

    void String::ShrinkToFit() {
        if (IsSmallString()) return;
        MoveBuffer(AllocateString(large.GetSize()), large.GetSize());
    }

    void String::ShrinkTo(usize mincap) {
        if (IsSmallString()) return;
        const usize size = std::max(large.GetSize(), mincap);
        MoveBuffer(AllocateString(size), size);
    }

    void String::Truncate(usize len) {
        if (IsSmallString()) {
            small.SetSize(len);
        } else {
            large.SetSize(len);
        }
    }

    String String::Escape() const {
        return AsStr().Escape();
    }

    usize String::WriteEscape(Text::StringWriter output) const {
        return AsStr().WriteEscape(output);
    }

    Option<String> String::Unescape() const {
        return AsStr().Unescape();
    }

    String String::operator+(char rhs) const {
        return operator+(Str::Slice(&rhs, 1));
    }

    String& String::operator+=(char rhs) {
        Append(rhs);
        return *this;
    }

    String String::operator+(Str rhs) const {
        String sum = WithCap(Length() + rhs.Length());
        Memory::MemCopyNoOverlap(sum.Data(),            Data(),     Length());
        Memory::MemCopyNoOverlap(sum.Data() + Length(), rhs.Data(), rhs.Length());
        if (sum.IsSmallString())
            sum.small.SetSize(Length() + rhs.Length());
        else
            sum.large.SetSize(sum.large.cap);
        return sum;
    }

    String& String::operator+=(Str rhs) {
        AppendStr(rhs);
        return *this;
    }
}
