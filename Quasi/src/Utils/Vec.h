#pragma once
#include "Func.h"
#include "Comparison.h"
#include "Option.h"
#include "Span.h"

namespace Quasi {
    namespace Vecs {
        inline usize GrowCap(usize cap) { return std::max<usize>(cap * 2, 2); }
        template <class T> Vec<T> FromIList(IList<T> list) { return Vec<T>::FromIList(list); }
        template <class T, usize N> Vec<T> New(const T (&arr)[N]) { return Vec<T>::New(arr); }
        template <class T, usize N> Vec<T> New(T (&&arr)[N])      { return Vec<T>::New(std::move(arr)); }

        template <Numeric N>
        Vec<N> Range(N start, N end) {
            if (end < start) return {};

            Vec<N> range = Vec<N>::WithCap((usize)(end - start));
            for (N x = 0; x < end; x += N(1)) { range.Push(x); }
            return range;
        }

        template <Numeric N>
        Vec<N> Range(N start, N end, N step) {
            // bad range!
            if (step == 0 || (end < start) == (step < 0)) return {};

            Vec<N> range = Vec<N>::WithCap((usize)((end - start) / step));
            if (step < 0) {
                for (N x = start; x > end; x -= step) range.Push(x);
            } else {
                for (N x = start; x <= end; x += step) range.Push(x);
            }
            return range;
        }
    }

    template <class T>
    struct Vec : IContinuous<T, Vec<T>> {
        friend ICollection<T, Vec>;
        friend IContinuous<T, Vec>;
    private:
        T* data = nullptr;
        usize size = 0, capacity = 0;

        Vec(T* dat, usize s, usize cap) : data(dat), size(s), capacity(cap) {}
    public:
        Vec() = default;
        ~Vec() { Memory::RangeDestruct(data, size); /* dont destruct after size, capacity is uninit'ed */ }
        Vec(Vec&& v) noexcept : data(v.data), size(v.size), capacity(v.capacity) { v.PretendClear(); }
        Vec& operator=(Vec&& v) noexcept { this->~Vec(); data = v.data; size = v.size; capacity = v.capacity; v.PretendClear(); return *this; }
        Vec(const Vec& x) : Vec(x.Clone()) {}
        Vec& operator=(const Vec& x) { if (this == &x) return *this; *this = x.Clone(); return *this; }
    public:
        static Vec Empty() { return {}; }
        template <usize N> static Vec New(T (&&arr)[N]) { return MoveNew(Span<T>::FromArray(arr)); }
        template <usize N> static Vec New(const T (&arr)[N]) { return New(Span<const T>::FromArray(arr)); }
        static Vec New(Span<const T> elms) {
            Vec v = WithCap(elms.Length());
            Memory::RangeCopyNoOverlap(v.Data(), elms.Data(), elms.Length());
            v.SetLengthUnsafe(elms.Length());
            return v;
        }
        static Vec FromIList(IList<T> elms) { return New(Spans::FromIList(elms)); }
        static Vec MoveNew(Span<T> movElms) {
            Vec v = WithCap(movElms.Length());
            Memory::RangeConstructMove(v.Data(), movElms.Data(), movElms.Length());
            v.SetLengthUnsafe(movElms.Length());
            return v;
        }

        static Vec FromBox(ArrayBox<T>& box) { return { box.Release(), box.Length(), box.Length() }; }

        static Vec WithCap (usize cap)  { return { cap  ? AllocateBuffer(cap)  : nullptr, 0, cap }; }
        static Vec WithSize(usize size) { return { size ? AllocateBuffer(size) : nullptr, size, size }; }
        static Vec Compose(T* data, usize size, usize cap) { return { data, size, cap }; }
        [[nodiscard]] Tuple<T*, usize, usize> Decompose() { const usize prsize = size, prcap = capacity; return { Release(), prsize, prcap }; }

        Vec Clone() const { return New(AsSpan()); }
    protected:
        usize LengthImpl() const { return size; }
        T* DataImpl() { return data; }
        const T* DataImpl() const { return data; }
    private:
        void PretendClear() { data = nullptr; size = 0; capacity = 0; }

    public:
        void Clear() { Memory::RangeDestruct(data, size); size = 0; }
        [[nodiscard]] T* Release() { T* const d = data; PretendClear(); return d; }

        usize Capacity()   const { return capacity; }
        bool IsEmpty()     const { return size == 0; }
        explicit operator bool() const { return !IsEmpty(); }
    private:
        void ReserveNext() { AllocToNew(Vecs::GrowCap(capacity)); }
        void MoveBuffer(T* buffer) {
            for (usize i = 0; i < size; ++i) {
                Memory::ConstructMoveAt(&buffer[i], std::move(data[i]));
                Memory::DestructAt(&data[i]);
            }
            Memory::FreeRaw(data);
            data = buffer;
        }
        void AllocToNew(usize buffSize) { MoveBuffer(AllocateBuffer(buffSize)); capacity = buffSize; }
    public:
        static T* AllocateBuffer(usize size) { return Memory::AllocateArrayUninit<T>(size); }

        bool CanFit(usize amount) const { return size + amount <= capacity; }
        void TryGrow(usize amount) { if (!CanFit(amount)) Reserve(amount); }

        void Reserve(usize add) {
            if (size + add <= capacity) return;
            if (size + add < Vecs::GrowCap(capacity))
                ReserveNext();
            else
                ReserveExact(add);
        }
        void ReserveExact(usize add) { if (size + add > capacity) AllocToNew(size + add); }
        void Resize(usize len, const T& value = {}) {
            if (len <= size) Truncate(len);
            else { Reserve(len); Memory::RangeSet(&data[size], value, len - size); size = len; }
        }
        void ResizeWith(usize len, Fn<T> auto&& factory) {
            if (len <= size) Truncate(len);
            else { Reserve(len);
                for (usize i = size; i < len; ++i) Memory::ConstructMoveAt(&data[i], factory());
                size = len;
            }
        }
        void ResizeDefault(usize len) { return ResizeWith(len, Combinate::Constructor<T> {}); }
        void ResizeExtra(usize extra, const T& value = {}) { return Resize(size + extra, value); }
        void ResizeExtraWith(usize extra, Fn<T> auto&& factory) { return ResizeWith(size + extra, factory); }
        void ResizeExtraDefault(usize extra) { return ResizeExtraWith(extra, Combinate::Constructor<T> {}); }

        void ShrinkToFit() { AllocToNew(size); }
        void ShrinkTo(usize minimum) { AllocToNew(std::max(size, minimum)); }

        [[nodiscard]] ArrayBox<T> IntoBox()      { return ArrayBox<T>::Own(Release(), size); } // releases
        [[nodiscard]] ArrayBox<T> IntoBoxWhole() { return ArrayBox<T>::Own(Release(), capacity); } // releases
        ArrayBox<T> CloneToBox()   { return AsSpan().CollectToBox(); } // copies without extra cap

        const T& First() const { return data[0]; }
        const T& Last() const { return data[size - 1]; }
        T& First() { return data[0]; }
        T& Last() { return data[size - 1]; }

        Span<T> AsSpan()             { return Span<T>      ::Slice(data, size); }
        Span<const T> AsSpan() const { return Span<const T>::Slice(data, size); }

        Span<T> LeakSpan() { Span<T> leaked = AsSpan(); PretendClear(); return leaked; }

        Span<T> SpareCapacity() { return { data + size, capacity - size }; }
        Tuple<Span<T>, Span<T>> SplitUsedCapacity() { return { AsSpan(), SpareCapacity() }; }

        Span<T> EntireAsSpan() { return { data, capacity }; }
        Span<const T> EntireAsSpan() const { return { data, capacity }; }

        void SetLengthUnsafe(usize len) { size = len; }
        void Truncate(usize len) { if (len < size) { Memory::RangeDestruct(&data[len], size - len); size = len; } }
        void Shorten(usize amount) { amount = std::min(amount, size); Memory::RangeDestruct(data, size - amount); size -= amount; }

        void PopUnordered(usize index)  { --size; std::swap(data[index], data[size]); data[size].~T(); }
        T    TakeUnordered(usize index) { --size; std::swap(data[index], data[size]); return std::move(data[size]); }
        void Pop()                      { --size; data[size].~T(); }
        T    Take()                     { --size; return std::move(data[size]); }
        void Pop(usize index)           { --size; Memory::RangeMove(&data[index], &data[index + 1], size - index); }
        T    Take(usize index)          { T out = std::move(data[index]); Pop(index); return out; }
        bool      TryPopUnordered(usize index)  { if (IsEmpty()) return false;          PopUnordered(index);  return true; }
        Option<T> TryTakeUnordered(usize index) { if (IsEmpty()) return nullptr; return TakeUnordered(index);              }
        bool      TryPop()                      { if (IsEmpty()) return false;          Pop();                return true; }
        Option<T> TryTake()                     { if (IsEmpty()) return nullptr; return Take();                            }
        bool      TryPop(usize index)           { if (IsEmpty()) return false;          Pop(index);           return true; }
        Option<T> TryTake(usize index)          { if (IsEmpty()) return nullptr; return Take(index);                       }

        bool      PopIf (Predicate<T> auto&& pred) { if (IsEmpty() || !pred(data[size - 1])) return false; Pop(); return true; }
        Option<T> TakeIf(Predicate<T> auto&& pred) { if (IsEmpty() || !pred(data[size - 1])) return nullptr; else return Take(); }

        T&        Push(const T& obj) { TryGrow(1); Memory::ConstructCopyAt(&data[size], obj);            return data[size++]; }
        T&        Push(T&& obj)      { TryGrow(1); Memory::ConstructMoveAt(&data[size], std::move(obj)); return data[size++]; }
        OptRef<T> TryPush(const T& obj) { if (CanFit(1)) { return Push(obj);            } return nullptr; }
        OptRef<T> TryPush(T&& obj)      { if (CanFit(1)) { return Push(std::move(obj)); } return nullptr; }

        void Insert(const T& obj, usize idx) {
            TryGrow(1); Memory::RangeMoveRev(&data[idx + 1], &data[idx], size - idx);
            Memory::ConstructCopyAt(&data[idx], obj); ++size;
        }
        void Insert(T&& obj, usize idx) {
            TryGrow(1); Memory::RangeMoveRev(&data[idx + 1], &data[idx], size - idx);
            Memory::ConstructMoveAt(&data[idx], std::move(obj)); ++size;
        }
        void InsertSpan(Span<const T> vals, usize idx) {
            TryGrow(vals.Length()); Memory::RangeMoveRev(&data[idx + vals.Length()], &data[idx], size - idx);
            Memory::RangeCopy(&data[idx], vals.Data(), vals.Length());
        }
        void MoveInsertSpan(Span<T> vals, usize idx) {
            TryGrow(vals.Length()); Memory::RangeMoveRev(&data[idx + vals.Length()], &data[idx], size - idx);
            Memory::RangeMove(&data[idx], vals.Data(), vals.Length());
        }

        void Extend(Collection<T> auto&& items) {
            // if constexpr (ArrayLike<decltype(items)>) {
            //     TryGrow(items.Length());
            // }
            for (auto&& i : items) { Push(std::forward<decltype(i)>(i)); }
        }
        void ExtendMove(Span<T> items)   { TryGrow(items.Length()); for (T& i : items) Push(i); }
        void Extend(Span<const T> items) { TryGrow(items.Length()); for (const T& i : items) Push(i); }
        void ExtendFromSelf(usize start) { return ExtendFromSelf(start, size - start); }
        void ExtendFromSelf(usize start, usize count) {
            TryGrow(count);
            for (usize i = start; i < start + count; ++i) Push(data[i]);
        }
        // void ExtendFromSelf(IntegerRange inds);

        void Keep(Predicate<T> auto&& pred) {
            usize slow = -1; // this will wrap to 0 when added
            for (usize i = 0; i < size; ++i) {
                if (pred(data[i])) {
                    if (++slow == i) continue;
                    Memory::ConstructMoveAt(&data[slow], std::move(data[i]));
                }
                data[i].~T();
            }
            SetLengthUnsafe(slow + 1);
        }
        void Remove(const T& item) { OptionUsize i = this->Find(item); if (i) Pop(*i); }
        void RemoveDups() { return RemoveDupIf(Cmp::Equals {}); }
        void RemoveDupKeys(FnArgs<const T&> auto&& keyf);
        void RemoveDupIf(EqualPred<T> auto&& eq) {
            if (size <= 1) return;
            usize slow = 0;
            for (usize i = 1; i < size; ++i) {
                if (!eq(data[slow], data[i])) {
                    if (++slow == i) continue;
                    Memory::ConstructMoveAt(&data[slow], std::move(data[i]));
                }
                data[i].~T();
            }
            SetLengthUnsafe(slow + 1);
        }

        void Erase(usize begin) { return Erase(begin, size - begin); }
        void Erase(usize begin, usize num) {
            Memory::RangeMove(&data[begin], &data[begin + num], size - begin - num);
            size -= num;
        }
        // void Erase(IntegerRange r); // removes all the elements in the interger range
        // Vec Drain(IntegerRange r); // the erased values get returned as a new vecotr
        // void Replace(IntegerRange, Span) // replaced values with span values
        // ExtractIfIter ExtractIf() // see https://doc.rust-lang.org/nightly/std/vec/struct.Vec.html#method.extract_if. probably not needed

        Vec SplitOff(usize index) { Vec tail = Vec::MoveNew(this->SubspanMut(index)); SetLengthUnsafe(index); return tail; }

        /* Vec<CollectionItem<T>> */ auto Flattened() const requires CollectionAny<T> {
            Vec<CollectionItem<T>> flattened;
            for (const T& item : *this) {
                for (const auto& sub : item) flattened.Push(sub);
            }
            return flattened;
        }

        /* Vec<CollectionItem<T>> */ auto IntoFlattened() requires CollectionAny<T> {
            Vec<CollectionItem<T>> flattened;
            for (T& item : *this) {
                for (auto& sub : item.IntoIter()) flattened.Push(std::move(sub));
            }
            return flattened;
        }

        template <FnArgs<const T&> F>
        Vec<FuncResult<F, const T&>> MapEach(const F& mapper) {
            using R = FuncResult<F, const T&>;
            Vec<R> result = Vec<R>::WithCap(size);
            for (const T* beg = data; beg != data + size; ++beg) result.Push(mapper(*beg));
            return result;
        }

        // + see span iterators
    protected:
        // struct IntoIter : IIterator<T, IntoIter> {
        //
        // } IntoIterImpl() { return { data, data + size }; }
    };

    template <class T, class Super> Vec<RemConst<T>> IContinuous<T, Super>::CollectToVec() const { return Vec<RemConst<T>>::New(*this); }
    template <class T, class Super> Vec<RemConst<T>> IContinuous<T, Super>::MoveToVec() requires IsMut<T> { return Vec<RemConst<T>>::MoveNew(*this); }
    template <class T, class Super> Vec<RemConst<T>> IContinuous<T, Super>::Repeat(usize num) const {
        Vec rep = Vec<RemConst<T>>::WithCap(Length() * num);
        for (usize i = 0; i < num; ++i) rep.Extend(*this);
        return rep;
    }
}
