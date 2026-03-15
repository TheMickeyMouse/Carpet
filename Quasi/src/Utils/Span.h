#pragma once
#include "ArrayBox.h"
#include "Memory.h"
#include "Continuous.h"

namespace Quasi {
    namespace Algorithm {};
    template <class T> struct BufferIterator;
    template <class T, usize N> struct Array;

    template <class T>
    struct Span : IContinuous<T, Span<T>> {
        friend ICollection<T, Span>;
        friend IContinuous<T, Span>;
        template <class U> friend struct Span;
        using SpanCn = Span<const T>;
    private:
        T* data;
        usize size;

        Span(T* dat, usize len) : data(dat), size(len) {}
    public:
        Span() : data(nullptr), size(0) {}
        template <usize N>
        Span(T (&arr)[N]) : data(arr), size(N) {}
        template <Continuous<RemConst<T>> Coll>
        Span(const Coll& collection) : data(collection.Data()), size(collection.Length()) {}
        template <Continuous<T> Coll>
        Span(Coll& collection) requires IsMut<T> : data(collection.Data()), size(collection.Length()) {}

        template <usize N> static Span FromArray(T (&arr) [N]) { return { arr, N }; }
        static Span Slice(T* dat, usize len) { return { dat, len }; }
        static Span Only(T& obj) { return { &obj, 1 }; }
        static Span Empty() { return {}; }

        template <IsMut U> requires SameAs<T, byte>
        static Span BytesOf(U& memRead)       { return { (byte*)&memRead, sizeof(U) }; }
        template <class U> requires SameAs<T, const byte>
        static Span BytesOf(const U& memRead) { return { (const byte*)&memRead, sizeof(U) }; }
    protected:
        usize LengthImpl() const { return size; }
        T* DataImpl() { return data; }
        const T* DataImpl() const { return data; }
    public:
        Span<RemConst<T>> AsMut()   const { return { Memory::AsMutPtr(data),   size }; }
        Span<const T>     AsConst() const { return { Memory::AsConstPtr(data), size }; }
        operator Span<const T>() const { return AsConst(); }

        Span& Advance(usize num)    { data += num; size -= num; return *this; }
        Span& Shorten(usize amount) { size -= amount; return *this; }
        Span  TakeFirst(usize num) { Span first = this->First(num); data += num; size -= num; return first; }
        Span  TakeLast(usize num)  { Span last  = this->Last(num);  size -= num;              return last; }
        T&    TakeFirst()          { T&   first = this->First();    ++data; --size;           return first; }
        T&    TakeLast()           { T&   last  = this->Last();     --size;                   return last; }
        Span  TakeAfter(usize i)   { Span after = this->Skip(i);    size = i;                 return after; }

        template <usize N> Array<Ref<T>, N> GetMany(const Array<usize, N>& indices) {
            Array<Ref<T>, N> values;
            for (usize i = 0; i < N; ++i) { values[i].SetRef(data[indices[i]]); }
            return values;
        }

        // Option<FixedSpan<T, N>> FirstChunk<usize N>()
        // Tuple<FixedSpan<T, N>, Span> SplitFirstChunk<usize N>()
        // Option<FixedSpan<T, N>> LastChunk<usize N>()
        // Tuple<Span, FixedSpan<T, N>> SplitLastChunk<usize N>()

        // WindowIter                               Windows(usize len)
        // FixedWindowIter                          WindowsFixed(usize len)
        // ChunkIter                                Chunks(usize chunk)
        // RevChunkIter                             RevChunks(usize chunk)
        // ChunkExactIter                           ChunksExact(usize chunk)
        // RevChunkExactIter                        RevChunksExact(usize chunk)
        // FixedChunkExactIter                      FixedChunksExact<usize N>()
        // Span<Array<RemConst<T>, N>>              AsChunksExact<usize N>()
        // Tuple<Span<Array<RemConst<T>, N>>, Span> AsChunks<usize N>()
        // Tuple<Span, Span<Array<RemConst<T>, N>>> AsRevChunks<usize N>()
        // ChunkByIter           ChunkBy(Fn<bool, T&, T&> pred)

        Iter::SplitIter<Span> Split(const T& sep) const {
            return Iter::SplitIter<Span>::New(*this, Only(sep));
        }
        Iter::SplitIter<Span> Split(Span<const T> sep) const {
            return Iter::SplitIter<Span>::New(*this, sep);
        }

        // SplitIfIter           SplitIf(Fn<bool, T&> pred)
        // SplitIfInclIter       SplitIfIncl(Fn<bool, T&> pred)
        // RevSplitIter          RevSplit(const T& sep)
        // RevSplitIfIter        RevSplitIf(Fn<bool, T&> pred)
        // SplitAtmostIfIter     SplitIfAtmost(usize maxLen, Fn<bool, T&, T&> pred)
        // RevSplitAtmostIfIter  RevSplitIfAtmost(usize maxLen, Fn<bool, T&, T&> pred)

        bool RefEquals(Span<const T> other) const { return data == other.data && size == other.size; }
        bool ContainsBuffer(Span<const T> buf) const { return buf.data >= data && data + size >= buf.data + buf.size; }
        bool OverlapsBuffer(Span<const T> buf) const {
            const T* end = data + size, * bufEnd = buf.data + buf.size;
            return end >= buf.data && bufEnd >= data;
        }

        bool StartsWith(Span<const T> prefix) const { return size >= prefix.size && First(prefix.size) == prefix; }
        bool EndsWith  (Span<const T> suffix) const { return size >= suffix.size && Last(suffix.size)  == suffix; }
        Option<Span> RemovePrefix(Span<const T> prefix) const { return StartsWith(prefix) ? Options::Some(Skip(prefix.size)) : nullptr; }
        Option<Span> RemoveSuffix(Span<const T> suffix) const { return EndsWith(suffix)   ? Options::Some(Trunc(suffix.size)) : nullptr; }

        usize  Unaddress      (const T* addr) const { return addr - data; }
        bool   ContainsAddress(const T* addr) const { return data <= addr && addr < data + size; }
        zRange UnaddressSpan      (Span addr) const { return zRange::FromSize(addr.Data() - data, addr.Size()); }
        bool   ContainsAddressSpan(Span addr) const { return data <= addr.Data() && addr.DataEnd() <= this->DataEnd(); }

        // assumes ascending order
        Tuple<bool, usize> BinarySearch(const T& target) const { return BinarySearchWith(Cmp::Compare { target }); }
        // assumes ascending order
        Tuple<bool, usize> BinarySearchWith(Fn<Comparison, const T&> auto&& cmp) const;
        Tuple<bool, usize> BinarySearchByKey(const auto& key, FnArgs<const T&> auto&& keyf) const;
        usize BinaryPartitionPoint(const T& target) const { return BinaryPartitionPointBy(Cmp::LessThan { target }); }
        usize BinaryPartitionPointBy(Predicate<T> auto&& left) const;
        usize LowerBound(const T& target) const { return LowerBoundBy(Cmp::Compare { target }); }
        usize LowerBoundBy(Fn<Comparison, const T&> auto&& cmp) const { const auto [found, x] = BinarySearchWith(cmp); return found ? x : std::min<usize>(x, 1) - 1; }
        usize UpperBound(const T& target) const { return UpperBoundBy(Cmp::LessThan { target }); }
        usize UpperBoundBy(Fn<Comparison, const T&> auto&& cmp) const;
        // zRange EqualRange(const T& target) const { return LowerBoundBy(Operators::LessThanWith { target }); }
        // zRange EqualRangeBy(Predicate<T> auto&& left) const;
        // zRange EqualRangeByKey(FnArgs<const T&> auto&& keyf) const;

        bool BinaryContains(const T& target) const { const auto [found, _] = BinarySearch(target); return found; }
        bool BinaryContainsKey(const auto& key, FnArgs<const T&> auto&& keyf) const { const auto [found, _] = BinarySearchByKey(key, keyf); return found; }

        usize SortedPartitionPoint(usize idx, Comparator<T> auto&& cmp = Cmp::LessThan {}) requires IsMut<T>;
        Tuple<Span, T&, Span> SortedPartition(usize idx, Comparator<T> auto&& cmp = Cmp::LessThan {}) requires IsMut<T> {
            const usize i = SortedPartitionPoint(idx, cmp);
            return this->PartitionAt(i);
        }

        usize PartitionDupPointBy(EqualPred<T> auto&& eq = Cmp::Equals {}) requires IsMut<T>;
        Tuple<Span, Span> PartitionDupBy(EqualPred<T> auto&& eq = Cmp::Equals {}) requires IsMut<T> {
            const usize i = PartitionDupPointBy(eq);
            return this->SplitAt(i);
        }


        template <class U>
        Tuple<Span, Span<AddConstIf<U, T>>, Span> TransmuteAligned() const requires SameAs<const T, const byte> {
            const usize p = (usize)data;
            const usize prefix = -p & (alignof(U) - 1), mid = (size - prefix) / sizeof(U), suffix = size - prefix - mid * sizeof(U);
            return Tuple {
                Span { (T*)p,                               prefix }, // super cool magic, ex: 0b010 + 0b110 to sum to alignof(T)
                Span { (AddConstIf<U, T>*)(p + prefix),     mid },
                Span { (T*)(p + size * sizeof(U) - suffix), suffix }
            };
        }

        template <class U> requires (sizeof(T) % sizeof(U) == 0) || (sizeof(U) % sizeof(T) == 0)
        Span<AddConstIf<U, T>> Transmute() const { return { Memory::TransmutePtr<AddConstIf<U, T>>(data), size * sizeof(T) / sizeof(U) }; }
        template <class U> requires (sizeof(U) % sizeof(T) == 0)
        AddConstIf<U, T>& ReadFirst() const { return *Memory::TransmutePtr<AddConstIf<U, T>>(data); }
        template <class U> requires (sizeof(U) % sizeof(T) == 0)
        AddConstIf<U, T>& Read() { auto& x = *Memory::TransmutePtr<AddConstIf<U, T>>(data); data += sizeof(U) / sizeof(T); size -= sizeof(U) / sizeof(T); return x; }
    };

    template <class T> requires ContinuousAny<T>
    Span(T& collection) -> Span<AddConstIf<RemRef<CollectionItem<T>>, T>>;

    using Bytes = Span<const byte>;
    using BytesMut = Span<byte>;

    namespace Spans {
        template <class T>
        Span<T> Only(T& unit) { return Span<T>::Only(unit); }
        template <class T>
        Span<T> Slice(T* data, usize size) { return Span<T>::Slice(data, size); }
        template <class T>
        Span<const T> FromIList(IList<T> ilist) { return Span<const T>::Slice(ilist.begin(), ilist.size()); }
        template <class T, usize N>
        Span<T> Vals(T (&arr)[N])  { return Span<T>::FromArray(arr); }
        template <class T, usize N>
        Span<T> Vals(T (&&arr)[N]) { return Span<T>::FromArray(arr); }
    }

    template <class T, class S>
    Bytes IContinuous<T, S>::AsBytes() const { return Bytes::Slice((const byte*)Data(), Length() * sizeof(T)); }
    template <class T, class S>
    BytesMut IContinuous<T, S>::AsBytesMut() requires IsMut<T> { return BytesMut::Slice((byte*)Data(), Length() * sizeof(T)); }

    template <class T, class S>
    auto IContinuous<T, S>::AsFlattened() const requires IsRawArray<T> {
        return Spans::Slice((AddConstIf<ArrayElement<T>, T>*)Data(), Length() * ArrayLength<T>());
    }

    template <class T, class A> Span<const T> Box<T, A>::AsSpan() const { return data ? Span<const T>::Only(*data) : nullptr; }
    template <class T, class A> Span<T>       Box<T, A>::AsSpanMut()    { return data ? Span<T>::Only(*data)       : nullptr; }
}