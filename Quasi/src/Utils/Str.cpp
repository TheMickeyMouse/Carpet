#include "Str.h"

#include "Hash.h"
#include "Span.h"
#include "String.h"
#include "CStr.h"
#include "Iter/LinesIter.h"
#include "Iter/SplitIter.h"
#include "Text/StringWriter.h"

namespace Quasi {
    namespace Chr {
        char         FromDigit   (u32 digit) { return (char)('0' + digit); }
        char         FromHexDigit(u32 digit) { return (char)(digit < 10 ? '0' + digit : 'A' + digit); }
        Option<char> TryFromDigit   (u32 digit)              { return digit < 10    ? Options::Some(FromDigit(digit))    : nullptr; }
        Option<char> TryFromHexDigit(u32 digit)              { return digit < 16    ? Options::Some(FromHexDigit(digit)) : nullptr; }
        Option<char> TryFromDigitRadix(u32 digit, u32 radix) { return digit < radix ? Options::Some(FromHexDigit(digit)) : nullptr; }

        u32         ToDigit      (char digit) { return (u32)(digit - '0'); }
        u32         ToHexDigit   (char digit) { return IsNumeric(digit) ? digit - '0' : IsUpper(digit) ? digit - 'A' : digit - 'a'; }
        Option<u32> TryToDigit   (char digit) { return IsDigit(digit)    ? Options::Some(ToDigit(digit))    : nullptr; }
        Option<u32> TryToHexDigit(char digit) { return IsHexDigit(digit) ? Options::Some(ToHexDigit(digit)) : nullptr; }
        Option<u32> TryToDigitRadix(char digit, u32 radix) { return IsDigitRadix(digit, radix) ? Options::Some(ToHexDigit(digit)) : nullptr; }

        bool IsDigit   (char digit) { return '0' <= digit && digit <= '9'; }
        bool IsHexDigit(char digit) { return IsDigit(digit) || ('A' <= digit && digit <= 'F') || ('a' <= digit && digit <= 'f') ; }
        bool IsDigitRadix(char digit, u32 radix) {
            if (radix <= 10) return '0' <= digit && digit < '0' + radix;
            return IsDigit(digit) || ('A' <= digit && digit < 'A' + radix - 10) || ('a' <= digit && digit < 'a' + radix - 10);
        }

        Option<char> EscapeRepr(char c) {
            switch (c) {
                case '\'': return '\'';
                case '\"': return '"';
                case '\?': return '?';
                case '\\': return '\\';
                case '\a': return 'a';
                case '\b': return 'b';
                case '\f': return 'f';
                case '\n': return 'n';
                case '\r': return 'r';
                case '\t': return 't';
                case '\v': return 'v';
                default:   return nullptr;
            }
        }

        usize WriteEscape(char c, char* out) {
            if (const auto escVer = EscapeRepr(c)) {
                Memory::WriteU16(*escVer << 8 | '\\', out);
                return 2;
            } else if (!IsPrintable(c)) {
                static constexpr char hexdig[17] = "0123456789ABCDEF";
                Memory::WriteU32(hexdig[c & 0xF] << 24 | hexdig[c >> 4] << 16 | "x\\"_u32 , out);
                return 4;
            } else {
                out[0] = c;
                return 1;
            }
        }

        Option<char> UnescapeRepr(char c) {
            switch (c) {
                case '\'': return '\'';
                case '"':  return '\"';
                case '?':  return '\?';
                case '\\': return '\\';
                case 'a':  return '\a';
                case 'b':  return '\b';
                case 'f':  return '\f';
                case 'n':  return '\n';
                case 'r':  return '\r';
                case 't':  return '\t';
                case 'v':  return '\v';
                default:   return nullptr;
            }
        }

        bool IsAscii(char c) { return ' ' <= c && c <= '~'; }
        bool IsNonAscii(char c) { return !IsAscii(c); }

        char ToLower(char c) { return IsUpper(c) ? (char)(c |  32) : c; }
        char ToUpper(char c) { return IsLower(c) ? (char)(c & ~32) : c; }
        bool IsLower(char c) { return 'a' <= c && c <= 'z'; }
        bool IsUpper(char c) { return 'A' <= c && c <= 'Z'; }

        bool IsBlank     (char c) { return c == ' ' || c == '\t'; }
        bool IsWhitespace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
        bool IsAlpha     (char c) { return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'); }
        bool IsNumeric   (char c) { return IsDigit(c); }
        bool IsAlphaNum  (char c) { return IsAlpha(c) || IsNumeric(c); }
        bool IsPrintable (char c) { return 0x1f < c && c < 0x7f; }
        bool IsControl   (char c) { return (0x00 <= c && c <= 0x1f) || c == 0x7f; }
        bool IsGraphic   (char c) { return IsPrintable(c) && c != ' '; }
        bool IsPunct     (char c) { return IsGraphic(c) && !IsAlphaNum(c); }


        Set::Set(Span<const char> chars) {
            for (const char c : chars) {
                bitmask[(uchar)c / 64] |= 1 << ((uchar)c & 63);
            }
        }

        bool Set::operator()(char c) const {
            return bitmask[(uchar)c / 64] & 1 << ((uchar)c & 63);
        }
        bool Set::operator()(Str str) const { return operator()(str[0]); }
    }

#define strdef template <class Char, class Super>
#define strcls StringHolder<Char, Super>

    strdef Hashing::Hash strcls::GetHashCode() const {
        return Hashing::HashBytes(AsBytes());
    }

    strdef BufferIterator<const char&> strcls::Iter()    const        { return { this->Data(), this->DataEnd() }; }
    strdef BufferIterator<char&>       strcls::IterMut() requires mut { return { this->Data(), this->DataEnd() }; }

    strdef Iter::SplitIter<Str> strcls::Split(Str sep) const { return Iter::SplitIter<Str>::New(AsStr(), sep); }
    strdef Iter::LinesIter strcls::Lines() const { return Iter::LinesIter::New(AsStr()); }
    strdef usize strcls::CountLines() const { return CountChars('\n') + 1; }
    strdef usize strcls::CountChars(char c) const {
        usize zeroCount = 0;
        for (usize i = 0; i < this->Length(); ++i) {
            zeroCount += this->Data()[i] == c;
        }
        return zeroCount;
    }

    strdef Str              strcls::AsStr()      const        { return Str   ::Slice(this->Data(), this->Length()); }
    strdef StrMut           strcls::AsStrMut()   requires mut { return StrMut::Slice(this->Data(), this->Length()); }
    strdef Span<const char> strcls::AsSpan()     const        { return Span<const char>::Slice(this->Data(), this->Length()); }
    strdef Span<char>       strcls::AsSpanMut()  requires mut { return Span<char>      ::Slice(this->Data(), this->Length()); }
    strdef Span<const byte> strcls::AsBytes()    const        { return Span<const byte>::Slice((const byte*)this->Data(), this->Length()); }
    strdef Span<byte>       strcls::AsBytesMut() requires mut { return Span<byte>      ::Slice((byte*)this->Data(),       this->Length()); }
    strdef strcls::operator Str()    const        { return AsStr(); }
    strdef strcls::operator StrMut() requires mut { return AsStrMut(); }

    strdef OptRef<char> strcls::TryFirstMut() requires mut { return this->Length() ? OptRefs::SomeRef(At(0))                  : nullptr; }
    strdef OptRef<char> strcls::TryLastMut()  requires mut { return this->Length() ? OptRefs::SomeRef(At(this->Length() - 1)) : nullptr; }
    strdef OptRef<const char> strcls::TryFirst() const     { return this->Length() ? OptRefs::SomeRef(At(0))                  : nullptr; }
    strdef OptRef<const char> strcls::TryLast()  const     { return this->Length() ? OptRefs::SomeRef(At(this->Length() - 1)) : nullptr; }

    strdef Span<const char> strcls::Subspan   (usize start) const              { return Subspan(start, this->Length() - start); }
    strdef Str              strcls::Substr    (usize start) const              { return Substr (start, this->Length() - start); }
    strdef Span<const char> strcls::Subspan   (usize start, usize count) const { return Span<const char>::Slice(this->Data() + start, count); }
    strdef Str              strcls::Substr    (usize start, usize count) const { return Str             ::Slice(this->Data() + start, count); }
    strdef Span<char>       strcls::SubspanMut(usize start) requires mut { return SubspanMut(start, this->Length() - start); }
    strdef StrMut           strcls::SubstrMut (usize start) requires mut { return SubstrMut (start, this->Length() - start); }
    strdef Span<char>       strcls::SubspanMut(usize start, usize count) requires mut { return Span<char>::Slice(this->Data() + start, count); }
    strdef StrMut           strcls::SubstrMut (usize start, usize count) requires mut { return StrMut    ::Slice(this->Data() + start, count); }

    strdef StrMut strcls::FirstMut(usize num) requires mut { return SubstrMut(0, num); }
    strdef StrMut strcls::SkipMut(usize len)  requires mut { return SubstrMut(len); }
    strdef StrMut strcls::TailMut()           requires mut { return SubstrMut(1); }
    strdef StrMut strcls::LastMut(usize num)  requires mut { return SubstrMut(this->Length() - num, num); }
    strdef StrMut strcls::TruncMut(usize len) requires mut { return SubstrMut(0, this->Length() - len); }
    strdef StrMut strcls::InitMut()           requires mut { return SubstrMut(this->Length() - 1); }
    strdef Tuple<char&,  StrMut>        strcls::SplitFirstMut()          requires mut { return { FirstMut(),   TailMut() }; }
    strdef Tuple<StrMut, char&>         strcls::SplitLastMut()           requires mut { return { InitMut(),    LastMut() }; }
    strdef Tuple<StrMut, StrMut>        strcls::CutAtMut(usize at)       requires mut { return { FirstMut(at), SkipMut(at) }; }
    strdef Tuple<StrMut, StrMut>        strcls::SplitAtMut(usize at)     requires mut { return { FirstMut(at), SkipMut(at + 1) }; }
    strdef Tuple<StrMut, char&, StrMut> strcls::PartitionAtMut(usize at) requires mut { return { FirstMut(at), At(at), SkipMut(at + 1) }; }
    strdef Str strcls::First(usize num) const { return Substr(0, num); }
    strdef Str strcls::Skip(usize len)  const { return Substr(len); }
    strdef Str strcls::Tail()           const { return Substr(1); }
    strdef Str strcls::Last(usize num)  const { return Substr(this->Length() - num, num); }
    strdef Str strcls::Trunc(usize len) const { return Substr(0, this->Length() - len); }
    strdef Str strcls::Init()           const { return Substr(this->Length() - 1); }
    strdef Tuple<const char&, Str>      strcls::SplitFirst()          const { return { First(),   Tail() }; }
    strdef Tuple<Str, const char&>      strcls::SplitLast()           const { return { Init(),    Last() }; }
    strdef Tuple<Str, Str>              strcls::CutAt(usize at)       const { return { First(at), Skip(at) }; }
    strdef Tuple<Str, Str>              strcls::SplitAt(usize at)     const { return { First(at), Skip(at + 1) }; }
    strdef Tuple<Str, const char&, Str> strcls::PartitionAt(usize at) const { return { First(at), At(at), Skip(at + 1) }; }

    strdef Tuple<Str, Str> strcls::SplitOnce(char c)  const { return SplitAt(Find(c).UnwrapOr(this->Length())); }
    strdef Tuple<Str, Str> strcls::SplitOnce(Str sep) const { const OptionUsize i = Find(sep); if (i) return { First(*i), Skip(*i + sep.Length()) }; else return { *this, {} }; }

    strdef bool strcls::RefEquals     (Str other) const { return this->Data() == other.Data() && this->Length() == other.Length(); }
    strdef bool strcls::ContainsBuffer(Str buf)   const { return buf.Data() >= this->Data() && this->DataEnd() >= buf.DataEnd(); }
    strdef bool strcls::OverlapsBuffer(Str buf)   const {
        const char* end = this->DataEnd(), *bufEnd = buf.DataEnd();
        return end >= buf.Data() && bufEnd >= this->Data();
    }

    strdef bool strcls::Equals(Str other) const {
        if (this->Length() != other.Length()) return false;
        usize i = 0;
        for (; i < (this->Length() & -8); i += 8)
            if (Memory::ReadU64Native(this->Data() + i) != Memory::ReadU64Native(other.Data() + i)) return false;

        for (; i < this->Length(); ++i)
            if (At(i) != other.At(i)) return false;
        return true;
    }

    strdef bool strcls::EqualsIgnoreCase(Str other) const {
        if (this->Length() != other.Length()) return false;
        for (usize i = 0; i < this->Length(); ++i)
            if (Chr::ToUpper(At(i)) != Chr::ToUpper(other.At(i))) return false;
        return true;
    }

    strdef bool strcls::operator==(Str other) const { return Equals(other); }
    strdef bool strcls::operator==(const String& other) const { return Equals(other); }
    strdef bool strcls::operator==(const char* other) const { return Equals(other); }

    strdef Comparison strcls::Cmp(Str other) const {
        usize i = 0;
        for (; i < this->Length(); i += 8) {
            const auto cmp = Cmp::Between(Memory::ReadU64Native(this->Data() + i), Memory::ReadU64Native(other.Data() + i));
            if (cmp != Cmp::EQUAL) return cmp;
        }
        for (usize j = 0; j < (this->Length() & 7); ++j) {
            const auto cmp = Cmp::Between(At(i - 8 + j), other.At(i - 8 + j));
            if (cmp != Cmp::EQUAL) return cmp;
        }
        return Cmp::Between(this->Length(), other.Length());
    }
    strdef Comparison strcls::CmpSized(Str other) const {
        if (this->Length() != other.Length()) return Cmp::Between(this->Length(), other.Length());
        usize i = 0;
        for (; i < this->Length(); i += 8) {
            const auto cmp = Cmp::Between(Memory::ReadU64(this->Data() + i), Memory::ReadU64(other.Data() + i));
            if (cmp != Cmp::EQUAL) return cmp;
        }
        for (usize j = 0; j < (this->Length() & 7); ++j) {
            const auto cmp = Cmp::Between(At(i - 8 + j), other.At(i - 8 + j));
            if (cmp != Cmp::EQUAL) return cmp;
        }
        return Cmp::EQUAL;
    }
    strdef Comparison strcls::operator<=>(Str other) const { return Cmp(other); }

    strdef void  strcls::Reverse() requires mut { AsSpanMut().Reverse(); }

    strdef OptionUsize strcls::Find   (char c)  const { for (usize i = 0; i < this->Length(); ++i) if (At(i) == c) return i; return nullptr; }
    strdef OptionUsize strcls::RevFind(char c)  const { for (usize i = this->Length(); i --> 0; )  if (At(i) == c) return i; return nullptr; }
    strdef bool    strcls::Contains   (char c)  const { return Find   (c).HasValue(); }
    strdef bool    strcls::RevContains(char c)  const { return RevFind(c).HasValue(); }
    strdef OptionUsize strcls::Find   (Str str) const {
        for (usize i = 0; i + str.Length() < this->Length(); ++i)
            if (Substr(i, str.Length()) == str) return i;
        return nullptr;
    }
    strdef OptionUsize strcls::RevFind(Str str) const {
        for (usize i = this->Length() + 1; --i >= str.Length(); )
            if (Substr(i - str.Length(), str.Length()) == str) return i;
        return nullptr;
    }
    strdef bool  strcls::Contains   (Str str) const { return Find   (str) != -1; }
    strdef bool  strcls::RevContains(Str str) const { return RevFind(str) != -1; }
    strdef Tuple<OptionUsize, OptionUsize> strcls::FindOneOf(Span<const char> anyc) const {
        const OptionUsize i = FindIf(Chr::Set { anyc });
        return { i, i ? anyc.Find(At(*i)) : nullptr };
    }
    strdef Tuple<OptionUsize, OptionUsize> strcls::RevFindOneOf(Span<const char> anyc) const {
        const OptionUsize i = RevFindIf(Chr::Set { anyc });
        return { i, i ? anyc.Find(At(*i)) : nullptr };
    }
    strdef OptionUsize strcls::ContainsOneOf   (Span<const char> anyc) const { const auto [i, m] = FindOneOf(anyc);    return i.And(m); }
    strdef OptionUsize strcls::RevContainsOneOf(Span<const char> anyc) const { const auto [i, m] = RevFindOneOf(anyc); return i.And(m); }
    strdef Tuple<OptionUsize, OptionUsize> strcls::FindOneOf(Span<const Str> anystr) const {
        for (usize i = 0; i < this->Length(); ++i) {
            for (usize j = 0; j < anystr.Length(); ++j)
                if (Skip(i).StartsWith(anystr[j])) return { i, j };
        }
        return { nullptr, nullptr };
    }
    strdef Tuple<OptionUsize, OptionUsize> strcls::RevFindOneOf(Span<const Str> anystr) const {
        for (usize i = this->Length(); i --> 0; ) {
            for (usize j = 0; j < anystr.Length(); ++j)
                if (Skip(i).StartsWith(anystr[j])) return { i, j };
        }
        return { nullptr, nullptr };
    }
    strdef OptionUsize strcls::ContainsOneOf   (Span<const Str> anystr) const { const auto [i, m] = FindOneOf(anystr);    return i.And(m); }
    strdef OptionUsize strcls::RevContainsOneOf(Span<const Str> anystr) const { const auto [i, m] = RevFindOneOf(anystr); return i.And(m); }

    strdef bool  strcls::StartsWith(char prefix) const { return this->Length() >= 1 && First() == prefix; }
    strdef bool  strcls::EndsWith  (char suffix) const { return this->Length() >= 1 && Last()  == suffix; }
    strdef bool  strcls::StartsWith(Str prefix)  const { return this->Length() >= prefix.Length() && First(prefix.Length()) == prefix; }
    strdef bool  strcls::EndsWith  (Str suffix)  const { return this->Length() >= suffix.Length() && Last (suffix.Length()) == suffix; }
    strdef OptionUsize strcls::StartsWithOneOf(Span<const char> anyprefix) const { return this->Length() >= 1 ? anyprefix.Find(this->First()) : -1; }
    strdef OptionUsize strcls::EndsWithOneOf  (Span<const char> anysuffix) const { return this->Length() >= 1 ? anysuffix.Find(this->Last())  : -1; }
    strdef OptionUsize strcls::StartsWithOneOf(Span<const Str> anyprefix)  const { for (usize i = 0; i < anyprefix.Length(); ++i) if (StartsWith(anyprefix[i])) return i; return nullptr; }
    strdef OptionUsize strcls::EndsWithOneOf  (Span<const Str> anysuffix)  const { for (usize i = 0; i < anysuffix.Length(); ++i) if (StartsWith(anysuffix[i])) return i; return nullptr; }


    strdef Str strcls::Trim     () const { return TrimIf     (Chr::IsWhitespace); }
    strdef Str strcls::TrimStart() const { return TrimStartIf(Chr::IsWhitespace); }
    strdef Str strcls::TrimEnd  () const { return TrimEndIf  (Chr::IsWhitespace); }
    strdef Str strcls::Trim     (char c) const { return TrimIf     (Cmp::Equals { c }); }
    strdef Str strcls::TrimStart(char c) const { return TrimStartIf(Cmp::Equals { c }); }
    strdef Str strcls::TrimEnd  (char c) const { return TrimEndIf  (Cmp::Equals { c }); }
    strdef Str strcls::TrimOneOf     (Span<const char> anyc) const { return TrimIf     (Chr::Set { anyc }); }
    strdef Str strcls::TrimStartOneOf(Span<const char> anyc) const { return TrimStartIf(Chr::Set { anyc }); }
    strdef Str strcls::TrimEndOneOf  (Span<const char> anyc) const { return TrimEndIf  (Chr::Set { anyc }); }
    strdef StrMut strcls::TrimMut     () requires mut { return TrimIfMut     (Chr::IsWhitespace); }
    strdef StrMut strcls::TrimStartMut() requires mut { return TrimStartIfMut(Chr::IsWhitespace); }
    strdef StrMut strcls::TrimEndMut  () requires mut { return TrimEndIfMut  (Chr::IsWhitespace); }
    strdef StrMut strcls::TrimMut     (char c) requires mut { return TrimIfMut     (Cmp::Equals { c }); }
    strdef StrMut strcls::TrimStartMut(char c) requires mut { return TrimStartIfMut(Cmp::Equals { c }); }
    strdef StrMut strcls::TrimEndMut  (char c) requires mut { return TrimEndIfMut  (Cmp::Equals { c }); }
    strdef StrMut strcls::TrimOneOfMut     (Span<const char> anyc) requires mut { return TrimIfMut     (Chr::Set { anyc }); }
    strdef StrMut strcls::TrimStartOneOfMut(Span<const char> anyc) requires mut { return TrimStartIfMut(Chr::Set { anyc }); }
    strdef StrMut strcls::TrimEndOneOfMut  (Span<const char> anyc) requires mut { return TrimEndIfMut  (Chr::Set { anyc }); }

    strdef Str strcls::RemovePrefix(char prefix) const { return Skip (StartsWith(prefix)); }
    strdef Str strcls::RemoveSuffix(char suffix) const { return Trunc(EndsWith(suffix));   }
    strdef Str strcls::RemovePrefix(Str prefix)  const { return Skip (StartsWith(prefix) ? prefix.Length() : 0); }
    strdef Str strcls::RemoveSuffix(Str suffix)  const { return Trunc(EndsWith(suffix)   ? suffix.Length() : 0); }
    strdef Str strcls::RemovePrefixOneOf(Span<const char> prefix) const { return Skip ((bool)StartsWithOneOf(prefix)); }
    strdef Str strcls::RemoveSuffixOneOf(Span<const char> suffix) const { return Trunc((bool)EndsWithOneOf  (suffix)); }
    strdef Str strcls::RemovePrefixOneOf(Span<const Str> prefix)  const { return Skip (StartsWithOneOf(prefix) ? prefix.Length() : 0); }
    strdef Str strcls::RemoveSuffixOneOf(Span<const Str> suffix)  const { return Trunc(EndsWithOneOf  (suffix) ? suffix.Length() : 0); }
    strdef StrMut strcls::RemovePrefixMut(char prefix) requires mut { return SkipMut (StartsWith(prefix)); }
    strdef StrMut strcls::RemoveSuffixMut(char suffix) requires mut { return TruncMut(EndsWith(suffix));   }
    strdef StrMut strcls::RemovePrefixMut(Str prefix)  requires mut { return SkipMut (StartsWith(prefix) ? prefix.Length() : 0); }
    strdef StrMut strcls::RemoveSuffixMut(Str suffix)  requires mut { return TruncMut(EndsWith(suffix)   ? suffix.Length() : 0); }
    strdef StrMut strcls::RemovePrefixOneOfMut(Span<const char> prefix) requires mut { return SkipMut ((bool)StartsWithOneOf(prefix)); }
    strdef StrMut strcls::RemoveSuffixOneOfMut(Span<const char> suffix) requires mut { return TruncMut((bool)EndsWithOneOf  (suffix)); }
    strdef StrMut strcls::RemovePrefixOneOfMut(Span<const Str> prefix)  requires mut { return SkipMut (StartsWithOneOf(prefix) ? prefix.Length() : 0); }
    strdef StrMut strcls::RemoveSuffixOneOfMut(Span<const Str> suffix)  requires mut { return TruncMut(EndsWithOneOf  (suffix) ? suffix.Length() : 0); }

    strdef Iter::SplitIter<Str> strcls::Split(Str sep) {
        return Iter::SplitIter<Str>::New(AsStr(), sep);
    }

    strdef String strcls::ToString() const {
        return String::FromStr(*this);
    }

    strdef String strcls::Reversed() const {
        String rev = String::WithCap(this->Length());
        for (usize i = this->Length(); i --> 0; )
            rev.Append(At(i));
        return rev;
    }

    strdef String strcls::ToUpper() const {
        String upper = String::WithCap(this->Length());
        for (const char c : super()) upper.Append(Chr::ToUpper(c));
        return upper;
    }
    strdef String strcls::ToLower() const {
        String lower = String::WithCap(this->Length());
        for (const char c : super()) lower.Append(Chr::ToLower(c));
        return lower;
    }

    strdef void strcls::MakeUpper() requires mut {
        for (char& c : super()) c = Chr::ToUpper(c);
    }

    strdef void strcls::MakeLower() requires mut {
        for (char& c : super()) c = Chr::ToLower(c);
    }

    strdef String strcls::Repeat(usize n) const {
        String rep = String::WithCap(this->Length() * n);
        for (usize i = 0; i < n; ++i)
            for (const char c : super())
                rep.Append(c);
        return rep;
    }

    strdef String strcls::Replace(char from, Str to) const {
        return ReplaceIf([=] (Str str) { return str[0] == from ? 1 : 0; }, to);
    }

    strdef String strcls::Replace(Str from, Str to) const {
        if (from.IsEmpty()) return ToString();
        return ReplaceIf([&] (Str str) { return str.StartsWith(from) ? from.Length() : 0; }, to);
    }

    strdef String strcls::ReplaceAnyOf(Span<const char> from, Str to) const {
        if (from.IsEmpty()) return ToString();
        const Chr::Set set = { from };
        return ReplaceIf([&] (Str str) { return set(str[0]) ? 1 : 0; }, to);
    }

    strdef String strcls::ReplaceAnyOf(Span<const Str> from, Str to) const {
        if (from.IsEmpty()) return ToString();
        return ReplaceIf([&] (Str str) {
            const OptionUsize i = str.StartsWithOneOf(from);
            return i ? from[*i].Length() : 0;
        }, to);
    }

    Str& Str::Advance(usize num) {
        data += num;
        size -= num;
        return *this;
    }

    Str& Str::Shorten(usize amount) {
        size -= amount;
        return *this;
    }

    Str Str::TakeFirst(usize num) {
        const Str first = First(num);
        Advance(num);
        return first;
    }

    Str Str::TakeLast(usize num) {
        const Str last = Last(num);
        Shorten(num);
        return last;
    }

    const char& Str::TakeFirst() {
        const char& first = First();
        Advance(1);
        return first;
    }

    const char& Str::TakeLast() {
        const char& last = Last();
        Shorten(1);
        return last;
    }

    Str Str::TakeAfter(usize i) {
        const Str after = Skip(i);
        size = i;
        return after;
    }

    String Str::Escape() const {
        String ss = String::WithCap(this->Length() + 2);
        ss += '"';
        for (const char c : *this) {
            char buf[4];
            ss += Str::Slice(buf, Chr::WriteEscape(c, buf));
        }
        ss += '"';
        return ss;
    }

    usize Str::WriteEscape(Text::StringWriter output) const {
        usize len = 2;
        output.Write('"');
        for (const char c : *this) {
            char buf[4];
            len += output.Write(Str::Slice(buf, Chr::WriteEscape(c, buf)));
        }
        output.Write('"');
        return len;
    }

    Option<String> Str::Unescape() const {
        // early check, so that we never have to check again
        if (Last() == '\\') return nullptr;

        String ss = String::WithCap(this->Length());
        for (usize i = 0; i < this->Length(); ++i) {
            if (At(i) == '\\') {
                ss += Chr::UnescapeRepr(At(i + 1)).UnwrapOr(At(i + 1));
                ++i;
            } else {
                ss += At(i);
            }
        }
        return ss;
    }

    StrMut Str::AsMut() { return StrMut::Slice(Memory::AsMutPtr(data), size); }

    StrMut& StrMut::Advance(usize num) {
        data += num;
        size -= num;
        return *this;
    }

    StrMut& StrMut::Shorten(usize amount) {
        size -= amount;
        return *this;
    }

    StrMut StrMut::TakeFirstMut(usize num) {
        const StrMut first = FirstMut(num);
        Advance(num);
        return first;
    }

    StrMut StrMut::TakeLastMut(usize num) {
        const StrMut last = LastMut(num);
        Shorten(num);
        return last;
    }

    char& StrMut::TakeFirstMut() {
        char& first = FirstMut();
        Advance(1);
        return first;
    }

    char& StrMut::TakeLastMut() {
        char& last = LastMut();
        Shorten(1);
        return last;
    }

    StrMut StrMut::TakeAfterMut(usize i) {
        const StrMut after = SkipMut(i);
        size = i;
        return after;
    }

    Str StrMut::TakeFirst(usize num) {
        const Str first = First(num);
        Advance(num);
        return first;
    }

    Str StrMut::TakeLast(usize num) {
        const Str last = Last(num);
        Shorten(num);
        return last;
    }

    const char& StrMut::TakeFirst() {
        const char& first = First();
        Advance(1);
        return first;
    }

    const char& StrMut::TakeLast() {
        const char& last = Last();
        Shorten(1);
        return last;
    }

    Str StrMut::TakeAfter(usize i) {
        const Str after = Skip(i);
        size = i;
        return after;
    }

    template struct StringHolder<const char, Str>;
    template struct StringHolder<char, StrMut>;
    template struct StringHolder<char, String>;
    template struct StringHolder<const char, CStr>;
} // Quasi