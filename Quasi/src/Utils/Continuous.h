#pragma once
#include "Iterator.h"
#include "Range.h"
#include "Ref.h"

namespace Quasi {
#pragma region Continuous
    template <class T> struct Ref;
    template <class T> struct ArrayBox;
    template <class T, usize N> struct Array;
    struct Str;
    struct StrMut;

    template <class T>
    struct BufferIterator : IIterator<T, BufferIterator<T>> {
        friend IIterator<T, BufferIterator>;
        using Item = T;
        using Ptr = RemRef<T>*;
        Ptr iter, end;
        BufferIterator(Ptr beg, Ptr end) : iter(beg), end(end) {}
    protected:
        T CurrentImpl() const {
            if constexpr (!IsRef<T>) return std::move(*iter);
            else return *iter;
        }
        void AdvanceImpl() { ++iter; }
        bool CanNextImpl() const { return iter != end; }
    public:
        bool operator==(const BufferIterator& it) const { return iter == it.iter; }
    };

    template <class T, class Super>
    struct IContinuous : ICollection<T&, Super> {
        friend ICollection<T&, Super>;
        using SpanCn = Span<const T>;
        using SpanMt = Span<T>;
    protected:
        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }

        T*       DataImpl() = delete;
        const T* DataImpl() const = delete;
        usize  LengthImpl() const = delete;

        BufferIterator<T&>       IterMutImpl()       { return { Data(), Data() + Length() }; }
        BufferIterator<const T&> IterImpl()    const { return { Data(), Data() + Length() }; }
        BufferIterator<T>        IntoIterImpl()      { return { Data(), Data() + Length() }; }
    public:
        T*       Data()       { return super().DataImpl(); }
        const T* Data() const { return super().DataImpl(); }
        T*       DataEnd()       { return super().DataImpl() + super().LengthImpl(); }
        const T* DataEnd() const { return super().DataImpl() + super().LengthImpl(); }
        usize Length() const { return super().LengthImpl(); }

        SpanCn AsSpan() const { return Span(super()); }
        SpanMt AsSpan() { return Span(super()); }
        SpanMt AsSpanMut() requires IsMut<T> { return Span(super()); }
        Span<const byte> AsBytes() const;
        Span<byte> AsBytesMut() requires IsMut<T>;
        usize ByteSize() const { return Length() * sizeof(T); }
        Str    AsStr() const requires (sizeof(T) == sizeof(char));
        StrMut AsStrMut() requires (sizeof(T) == sizeof(char)) && IsMut<T>;

        bool IsEmpty()   const { return Length() == 0; }
        explicit operator bool() const { return !IsEmpty(); }

        T&       Get(usize i)       { return Data()[i]; }
        const T& Get(usize i) const { return Data()[i]; }
        OptRef<T>       TryGet(usize i)       { return i < Length() ? OptRefs::SomeRef(Data()[i]) : nullptr; }
        OptRef<const T> TryGet(usize i) const { return i < Length() ? OptRefs::SomeRef(Data()[i]) : nullptr; }
        T&       GetWrap(WrappingIndex i)       { return Data()[i(Length())]; }
        const T& GetWrap(WrappingIndex i) const { return Data()[i(Length())]; }

        const T& First() const { return Data()[0]; }
        const T& Last()  const { return Data()[Length() - 1]; }
        OptRef<const T> TryFirst() const { return Length() ? OptRefs::SomeRef(First()) : nullptr; }
        OptRef<const T> TryLast()  const { return Length() ? OptRefs::SomeRef(Last())  : nullptr; }
        T& First() { return Data()[0]; }
        T& Last()  { return Data()[Length() - 1]; }
        OptRef<T> TryFirst() { return Length() ? OptRefs::SomeRef(First()) : nullptr; }
        OptRef<T> TryLast()  { return Length() ? OptRefs::SomeRef(Last())  : nullptr; }

        T&     operator[](usize i)         { return Get(i); }
        T&     operator[](WrappingIndex i) { return GetWrap(i); }
        SpanMt operator[](zRange range)    { return Subspan(range); }
        const T& operator[](usize i)         const { return Get(i); }
        const T& operator[](WrappingIndex i) const { return GetWrap(i); }
        SpanCn   operator[](zRange range)    const { return Subspan(range); }

        SpanCn First(usize num)               const { return SpanCn::Slice(Data(), num); }
        SpanCn Skip(usize len)                const { return SpanCn::Slice(Data() + len, Length() - len); }
        SpanCn Tail()                         const { return SpanCn::Slice(Data() + 1, Length() - 1); }
        SpanCn Last(usize num)                const { return SpanCn::Slice(Data() + Length() - num, num); }
        SpanCn Trunc(usize len)               const { return SpanCn::Slice(Data(), Length() - len); }
        SpanCn Init()                         const { return SpanCn::Slice(Data(), Length() - 1); }
        Tuple<const T&,  SpanCn> SplitFirst() const { return { First(), Tail() }; }
        Tuple<SpanCn, const T&>  SplitLast()  const { return { Init(),  Last() }; }
        Tuple<SpanCn, SpanCn> CutAt(usize at)   const { return { First(at), Skip(at) }; }
        Tuple<SpanCn, SpanCn> SplitAt(usize at) const { return { First(at), Skip(at + 1) }; }
        Tuple<SpanCn, const T&, SpanCn> PartitionAt(usize at) const { return { First(at), Get(at), Skip(at + 1) }; }
        Tuple<SpanCn, SpanCn> SplitOnceOn(Predicate<T> auto&& pred) const {
            const OptionUsize i = FindIf(pred);
            return i ? SplitAt(i) : Tuple { *this, Empty() };
        }
        Tuple<SpanCn, SpanCn> RevSplitOnceOn(Predicate<T> auto&& pred) const {
            const OptionUsize i = RevFindIf(pred);
            return i ? SplitAt(i) : Tuple { Empty(), *this };
        }
        Tuple<SpanCn, SpanCn> SplitOnce(const T& sep) const {
            const OptionUsize i = Find(sep);
            return i ? SplitAt(i) : Tuple { *this, Empty() };
        }
        SpanMt First(usize num)                { return SpanMt::Slice(Data(), num); }
        SpanMt Skip(usize len)                 { return SpanMt::Slice(Data() + len, Length() - len); }
        SpanMt Tail()                          { return SpanMt::Slice(Data() + 1, Length() - 1); }
        SpanMt Last(usize num)                 { return SpanMt::Slice(Data() + Length() - num, num); }
        SpanMt Trunc(usize len)                { return SpanMt::Slice(Data(), Length() - len); }
        SpanMt Init()                          { return SpanMt::Slice(Data(), Length() - 1); }
        Tuple<T&,  SpanMt>  SplitFirst()       { return { First(), Tail() }; }
        Tuple<SpanMt, T&>   SplitLast()        { return { Init(),  Last() }; }
        Tuple<SpanMt, SpanMt> CutAt(usize at)   { return { First(at), Skip(at) }; }
        Tuple<SpanMt, SpanMt> SplitAt(usize at) { return { First(at), Skip(at + 1) }; }
        Tuple<SpanMt, T&, SpanMt> PartitionAt(usize at) { return { First(at), Get(at), Skip(at + 1) }; }
        Tuple<SpanMt, SpanMt> SplitOnceOn(Predicate<T> auto&& pred) {
            const OptionUsize i = FindIf(pred);
            return i ? SplitAt(i) : Tuple { *this, Empty() };
        }
        Tuple<SpanMt, SpanMt> RevSplitOnceOn(Predicate<T> auto&& pred) {
            const OptionUsize i = RevFindIf(pred);
            return i ? SplitAt(i) : Tuple { Empty(), *this };
        }
        Tuple<SpanMt, SpanMt> SplitOnce(const T& sep) {
            const OptionUsize i = Find(sep);
            return i ? SplitAt(i) : Tuple { *this, Empty() };
        }
        SpanCn Subspan(usize start)              const { return SpanCn::Slice(Data() + start, Length() - start); }
        SpanCn Subspan(usize start, usize count) const { return SpanCn::Slice(Data() + start, count); }
        SpanCn Subspan(zRange range)             const { return SpanCn::Slice(Data() + range.min, range.max - range.min); }
        SpanMt Subspan(usize start)              { return SpanMt::Slice(Data() + start, Length() - start); }
        SpanMt Subspan(usize start, usize count) { return SpanMt::Slice(Data() + start, count); }
        SpanMt Subspan(zRange range)             { return SpanMt::Slice(Data() + range.min, range.max - range.min); }

        void Swap(usize i, usize j) requires IsMut<T> { std::swap(Get(i), Get(j)); }
        void Reverse() requires IsMut<T> {
            for (usize i = 0, j = Length() - 1; i < j; ++i, --j) Swap(i, j);
        }

        template <EqualPred<T> Eq = Cmp::Equals<void>>
        bool Equals(SpanCn other, Eq&& eq = Eq {}) const {
            if (Length() != other.Length()) return false;
            for (usize i = 0; i < Length(); ++i) if (!eq(Get(i), other[i])) return false;
            return true;
        }
        bool operator==(SpanCn other) const { return Equals(other); }

        template <Predicate<T> P>
        bool All(P&& pred = P {}) const {
            for (const T& x : *this) { if (!pred(x)) return false; }
            return true;
        }
        template <Predicate<T> P>
        bool Any(P&& pred = P {}) const {
            for (const T& x : *this) { if (pred(x)) return true; }
            return false;
        }
        template <Comparator<T> Cmpr = Cmp::Compare<void>>
        Comparison Cmp(SpanCn other, Cmpr&& cmp = Cmpr {}) const {
            for (usize i = 0; i < std::min(Length(), other.Length()); ++i) {
                const Comparison c = cmp(Get(i), other[i]);
                if (c != Cmp::EQUAL) return c;
            }
            return Cmp::Between(Length(), other.Length());
        }
        template <Comparator<T> Cmpr = Cmp::Compare<void>>
        Comparison CmpSized(Span<const T> other, Cmpr&& cmp = Cmpr {}) const { return CmpSizedBy(other, cmp); }
        Comparison operator<=>(Span<const T> other) const { return Cmp(other); }

        OptionUsize Find   (const T& target) const { return FindIf   (Cmp::Equals { target }); }
        OptionUsize RevFind(const T& target) const { return RevFindIf(Cmp::Equals { target }); }
        OptionUsize FindIf(Predicate<T> auto&& pred) const {
            for (usize i = 0; i < Length(); ++i) if (pred(Get(i))) return i; return nullptr;
        }
        OptionUsize RevFindIf(Predicate<T> auto&& pred) const {
            for (usize i = Length(); i --> 0; )  if (pred(Get(i))) return i; return nullptr;
        }
        bool Contains     (const T& target) const { return Find(target).HasValue(); }
        bool RevContains  (const T& target) const { return RevFind(target).HasValue(); }
        bool ContainsIf   (Predicate<T> auto&& pred) const { return FindIf(pred).HasValue(); }
        bool RevContainsIf(Predicate<T> auto&& pred) const { return RevFindIf(pred).HasValue(); }

        OptionUsize Find   (Span<const T> target) const {
            for (usize i = 0; i <= Length() - target.Length(); ++i)
                if (Subspan(i, target.Length()) == target) return i;
            return nullptr;
        }
        OptionUsize RevFind(Span<const T> target) const {
            for (usize i = Length() - target.Length(); i --> 0; )
                if (Subspan(i, target.Length()) == target) return i;
            return nullptr;
        }
        bool  Contains   (Span<const T> target) const { return Find   (target).HasValue(); }
        bool  RevContains(Span<const T> target) const { return RevFind(target).HasValue(); }

        template <Comparator<T> Cmpr>
        void Sort(Cmpr&& cmp = Cmpr {}) requires IsMut<T>;
        void SortByKey(FnArgs<const T&> auto&& keyf) requires IsMut<T>;

        // void SortStable() TODO i cant be bothered to do this
        // void SortStableBy(Fn<bool, const T&, const T&> auto&& cmp)
        // void SortStableByKey(auto&& keyf)

        template <Comparator<T> Cmpr>
        bool IsSorted(Cmpr&& cmp = Cmpr {}) const;

        void RotateLeft(usize num)   requires IsMut<T>;
        void RotateRight(usize num)  requires IsMut<T>;
        void RotateSigned(isize off) requires IsMut<T> { return off == 0 ? void() : off < 0 ? RotateLeft(-off) : RotateRight(off); }
        void RotateSigned(WrappingIndex off) requires IsMut<T> { return RotateRight(off(Length())); }
        void RotateSignedWrapped(isize off)  requires IsMut<T> { return RotateSigned(off % Wrap); }

        void Fill(const T& value) requires IsMut<T> { for (T& t : *this) t = value; }
        template <Fn<T> F = Combinate::Constructor<T>>
        void FillWith(F&& factory = F {}) requires IsMut<T> { for (T& t : *this) t = factory(); }
        void CloneFrom(Span<const T> span) requires IsMut<T> { Memory::RangeCopy(Data(), span.Data(), span.Length()); }
        void MoveFrom(SpanMt span) requires IsMut<T> { Memory::RangeMove(Data(), span.Data(), span.Length()); }
        void SwapWith(SpanMt span) requires IsMut<T> { Memory::RangeSwap(Data(), span.Data(), span.Length()); }
        // void CopyFromSelf(IntegerRange, usize dest)

        // Tuple<Span, Span<AddConstIf<SimdT, T>>, Span> AsSimd() const;

        /* Span<AddConstIf<ArrayElement<T>, T>> */ auto AsFlattened() const requires IsRawArray<T>;
        // {
        //     return Spans::Slice((AddConstIf<ArrayElement<T>, T>*)Data(), Length() * ArrayLength<T>());
        // }

        ArrayBox<RemConst<T>> CollectToBox() const {
            T* arr = Memory::AllocateArrayUninit<T>(Length());
            Memory::RangeConstructCopyNoOverlap(arr, Data(), Length());
            return ArrayBox<RemConst<T>>::Own(arr, Length());
        }
        ArrayBox<RemConst<T>> MoveToBox() {
            T* arr = Memory::AllocateArrayUninit<T>(Length());
            Memory::RangeConstructMoveNoOverlap(arr, Data(), Length());
            return ArrayBox<RemConst<T>>::Own(arr, Length());
        }
        Vec<RemConst<T>> CollectToVec() const;
        Vec<RemConst<T>> MoveToVec() requires IsMut<T>;
        Vec<RemConst<T>> Repeat(usize num) const;
        // Vec<ConcatResult<T>> Concat() const requires CanConcat<T>;
        // Vec<ConcatResult<T>> Join(const auto& sep) const requires CanConcat<T> && CanConcat<T, decltype(sep)>;

        Hashing::Hash GetHashCode() const {
            usize seed = Length();
            for (const T& value : *this) {
                seed ^= HashObject(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return Hashing::AsHash(seed);
        }
    };

    template <class C, class Item> concept Continuous = Implements<C, IContinuous, Item>;
    template <class C> concept ContinuousAny = Implements<C, IContinuous, RemRef<CollectionItem<C>>>;
#pragma endregion
}
