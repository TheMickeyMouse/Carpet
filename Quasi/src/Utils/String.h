#pragma once
#include "Str.h"
#include "Vec.h"

namespace Quasi {
    struct CStr;

    struct String : StringHolder<char, String> {
        friend IContinuous;
        friend StringHolder;
        using StringHolder::operator==;
        using StringHolder::operator<=>;
    private:
        // byte representation:
        // [_____________________________DATA_____________________________]
        // [_____________________________CAPC_____________________________]
        // [_____________________________SIZE___________________________] M <-- short: 0 or long: 1 mask (single bit)
        // when short, DATA + CAP + SIZE becomes the character buffer except last byte
        // when long, it becomes a Vec<char>
        // since we store the last bit in the struct as the short or long mask,
        // many size operations require extra math (x2)

        struct Large {
            usize sizePackedFlag = 1;
            usize cap = 0;
            char* data = nullptr;

            usize GetSize() const { return sizePackedFlag >> 1; }
            void SetSize(usize x) { sizePackedFlag =  x * 2 + 1; }
            void AddSize(usize x) { sizePackedFlag += x * 2; }
        };
        struct Small {
            static constexpr usize MAXLEN = sizeof(usize) / sizeof(char) * 3 - 1;
            byte sizePackedFlag = 0;
            char data[MAXLEN] { 0 };

            usize GetSize() const { return sizePackedFlag >> 1; }
            void SetSize(usize x) { sizePackedFlag =  (byte)(x * 2); }
            void AddSize(usize x) { sizePackedFlag += (byte)(x * 2); }
        };

        union {
            Small small {};
            Large large;
        };

        String(const Large& large) : large(large) {}
        String(const Small& small) : small(small) {}
    public:
        String() = default;
        String(Nullptr) : String() {}
        String(Str str) : String(FromStr(str)) {}
        String(const char* cstr) : String(FromStr({ cstr })) {}

        // TODO: complete utf8 support

        static String Empty() { return {}; }
        static String WithCap(usize cap);
        static String FromChars(Vec<char> chars);
        static String FromChars(Span<const char> chars);
        static String FromStr(Str str);
        static String Compose(char* data, usize size, usize cap);
        static String Join(const Collection<Str> auto& strings, Str sep) {
            String s;
            for (const Str part : strings) {
                if (s) s.AppendStr(sep);
                s.AppendStr(part);
            }
            return s;
        }

        String Clone() const;

        String(const String& s);
        String& operator=(const String& s);
        String(String&& s) noexcept;
        String& operator=(String&& s) noexcept;

        ~String();
    private:
        static usize GrowCap(usize cap);
        // assumes large strings
        void OptimizeAsSmall();
        // assumes small strings
        void CopyToLarge(char* dest, usize size);
        void MoveBuffer(char* dest, usize cap);
    public:
        static char* AllocateString(usize size);

        bool CanFit(usize amount) const;
        void TryGrow(usize amount);

        bool IsSmallString() const { return !(large.sizePackedFlag & 1); }
        bool IsLargeString() const { return   large.sizePackedFlag & 1;  }
    protected:
        const char* DataImpl() const;
        char* DataImpl();
        usize LengthImpl()     const;
    public:
        usize Capacity() const;

        void Reserve(usize extra);
        void ReserveExact(usize extra);
        void Resize(usize size);

        void SetEmptyUnsafe();

        Nullable<char*> ReleaseLargeString();
        Option<Vec<char>> IntoLargeString();
        Option<StrMut> TryAsSmallString();
        void TryOptimize();

        Vec<char> IntoChars();
        Vec<byte> IntoBytes();
        ArrayBox<char> IntoBox();

        void Append(char c);
        void AppendStr(Str str);
        // void AppendFromSelf(IntegerRange range);
        void Insert(char c, usize i);
        void InsertStr(Str str, usize i);

        void AddNullTerm();
        void TruncNullTerm();
        CStr IntoCStr();

        char Pop();
        char Pop(usize index);

        void RemoveAllOf(char c);
        void RemoveAllOf(Str str);
        void RemoveAllOfEach(Span<const char> anyc);
        void RemoveAllOfEach(Span<const Str> anystr);
        void RemoveIf(Fn<usize, Str> auto&& pred) {
            char* data = Data();
            const usize size = Length();

            usize fast = 0, slow = 0;
            while (fast < size) {
                if (const usize i = pred(Str::Slice(data + fast, size - fast)); i == 0) {
                    data[slow++] = data[fast++];
                } else fast += i;
            }

            if (IsSmallString())
                small.sizePackedFlag = slow * 2;
            else {
                large.sizePackedFlag = slow * 2;
                if (slow <= Small::MAXLEN)
                    OptimizeAsSmall();
            }
        }
        void Clear();

        String SplitOff(usize index);

        // void Erase(IntegerRange r); // removes all the elements in the interger range
        // Vec Drain(IntegerRange r); // the erased values get returned as a new vecotr
        // void Replace(IntegerRange, Span) // replaced values with span values

        void ShrinkToFit();
        void ShrinkTo(usize mincap);

        void Truncate(usize len);

        // bool IsUtfBoundary(usize index) const;
        // usize FloorUtfBoundary(usize index) const;
        // usize CeilUtfBoundary(usize index) const;

        String Escape() const;
        usize WriteEscape(Text::StringWriter output) const;
        Option<String> Unescape() const;

        operator Str() const { return AsStr(); }
        String  operator+ (char rhs) const;
        String& operator+=(char rhs);
        String  operator+ (Str rhs) const;
        String& operator+=(Str rhs);
    };

    template <class Char, class Super>
    String StringHolder<Char, Super>::ReplaceIf(Fn<usize, Str> auto&& pred, Str to) const {
        String repl;
        usize i = 0;
        while (i < super().LengthImpl()) {
            if (const usize j = pred(Substr(i)); j == 0) {
                repl.Append(At(i++));
            } else {
                repl.AppendStr(to);
                i += j;
            }
        }
        return repl;
    }

    String operator ""_string(const char* str, usize len);
}