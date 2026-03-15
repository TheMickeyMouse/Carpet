#pragma once
#include "Comparison.h"
#include "Type.h"
#include "Option.h"
#include "Tuple.h"

namespace Quasi {
    template <class T, class Super> struct IIterator;

    template <class C>             using   CollectionItem = typename C::Item;
    template <class I>             concept IteratorAny    = Extends<I, IIterator<CollectionItem<I>, I>>;
    template <class I, class Item> concept Iterator       = IteratorAny<I> && ConvTo<CollectionItem<I>, Item>;

    inline struct IteratorEndMarker {} IteratorEnd;

#pragma region Iter Declarations
    namespace Iter {
        template <class It>          struct EnumerateIter;
        template <class It, class F> struct MapIter;
        template <class Vw>          struct SplitIter;
    }
#pragma endregion

    template <class T, class Super>
    struct ICollection {
        using Item = T;
        friend Super;
    protected:
        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }

        Iterator<const RemRef<T>&> auto IterImpl() const = delete;
        Iterator<T&> auto IterMutImpl() = delete;
    public:
        Iterator<const RemRef<T>&> auto Iter() const { return super().IterImpl(); }
        Iterator<T&> auto IterMut() { return super().IterMutImpl(); }

        // Legacy methods:
        // CIter<Super> begin();
        // IteratorEndMarker end();
        Iterator<const RemRef<T>&> auto begin()  const { return Iter(); }
        Iterator<const RemRef<T>&> auto cbegin() const { return Iter(); }
        Iterator<T&> auto begin() { return IterMut(); }
        IteratorEndMarker end()  const { return IteratorEnd; }
        IteratorEndMarker cend() const { return IteratorEnd; }
    };

    template <class C>             concept CollectionAny = Implements<C, ICollection, CollectionItem<C>>;
    template <class C, class Item> concept Collection    = CollectionAny<C> && ConvTo<CollectionItem<C>, Item>;

    template <class T, class Super>
    struct IIterator : ICollection<T, Super> {
        using Item = T;
        friend Super;
        friend ICollection<T, Super>;
    protected:
        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }

        Super IterImpl() const { return super(); }
        Super IterMutImpl() { return super(); }

        T CurrentImpl() const = delete;
        void AdvanceImpl() = delete;
        bool CanNextImpl() const = delete;
    public:
        Super IterMut() requires IsMutRef<T> { return super(); }

        T Current() const { return super().CurrentImpl(); }
        void Advance() { return super().AdvanceImpl(); }
        bool CanNext() const { return super().CanNextImpl(); }

        T operator*() const { return Current(); }
        Super& operator++() { Advance(); return super(); }
        friend bool operator==(const Super& it, const IteratorEndMarker&) { return !it.CanNext(); }
        friend bool operator!=(const Super& it, const IteratorEndMarker&) { return  it.CanNext(); }

        usize Count() const {
            usize count = 0;
            for (; CanNext(); Advance()) ++count;
            return count;
        }
        usize CountOccurs(Predicate<Item> auto&& pred) {
            usize count = 0;
            for (; CanNext(); Advance()) {
                if (pred(Current())) ++count;
            }
            return count;
        }
        usize CountNumberOf(const Item& i) { return CountOccurs(Cmp::Equals { i }); }

        usize AdvanceBy(usize n) {
            for (usize i = 0; i < n; ++i) {
                if (!CanNext()) return i;
                Advance();
            }
            return n;
        }

        Option<Item> Last() {
            Option<Item> last = nullptr;
            while (CanNext()) {
                last = Current();
                Advance();
            }
            return last;
        }

        Option<Item> Nth(usize n) {
            if (AdvanceBy(n) < n || !CanNext()) return nullptr;
            return Current();
        }

        void ForEach(Fn<void, const Item&> auto&& fn) {
            for (Item i : super())
                fn(i);
        }

        Option<Item> Reduce(Fn<Item, Item, const Item&> auto&& reducer) {
            if (!CanNext()) return nullptr;
            Item acc = Current();
            Advance();
            for (; CanNext(); Advance()) {
                acc = reducer(std::move(acc), Current());
            }
            return acc;
        }

        template <class R> R Reduce(Fn<R, R, const Item&> auto&& reducer, R starting) {
            for (; CanNext(); Advance()) {
                starting = reducer(std::move(starting), Current());
            }
            return starting;
        }
        Option<Item> Sum() { return Reduce(Operators::Add {}); }
        Item         Sum(Item begin) { return Reduce(Operators::Add {}, begin); }
        Option<Item> Min() { return Reduce(Qfn$(std::min)); }
        Option<Item> Max() { return Reduce(Qfn$(std::max)); }

        bool All(Predicate<Item> auto&& pred = Combinate::Identity {}) {
            for (; CanNext(); Advance())
                if (!pred(Current())) return false;
            return true;
        }
        bool Any(Predicate<Item> auto&& pred = Combinate::Identity {}) {
            for (; CanNext(); Advance())
                if (pred(Current())) return true;
            return false;
        }

        Option<Item> Find(Predicate<Item> auto&& pred) {
            for (; CanNext(); Advance()) {
                const Item i = Current();
                if (pred(i)) return i;
            }
            return nullptr;
        }

        template <Collection<RemQual<T>> C> C Collect() {
            C collection;
            for (auto&& x : *this) {
                collection.Push(x);
            }
            return collection;
        }

        Iter::EnumerateIter<Super> Enumerate() const&;
        Iter::EnumerateIter<Super> Enumerate() &&;
        template <FnArgs<T> F> Iter::MapIter<Super, F> Map(F&& fn) const&;
        template <FnArgs<T> F> Iter::MapIter<Super, F> Map(F&& fn) &&;
        // TODO:
        // StepBy
        // Chain
        // Zip
        // ForEach
        // Filter
        // FilterMap
        // SkipWhile
        // TakeWhile
        // MapWhile
        // Take
        // Scan
        // FlatMap
        // Flatten
        // MapWindows
        // CollectPartitioned
        // Acc
    };


    inline struct WrapMarker {} Wrap;
    struct WrappingIndex { isize index; usize operator()(usize len) const { return (index % (isize)len + (isize)len) % (isize)len; } };

    WrappingIndex operator%(Integer auto i, WrapMarker) { return { (isize)i }; }
}
