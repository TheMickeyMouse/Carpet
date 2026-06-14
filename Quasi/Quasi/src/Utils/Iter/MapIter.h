#pragma once
#include "Utils/Vec.h"

namespace Quasi::Iter {
    template <class It, class F>
    struct MapIter : IIterator<FuncResult<F, CollectionItem<It>>, MapIter<It, F>> {
        using OriginalItem = CollectionItem<It>;
        using Item = FuncResult<F, OriginalItem>;
        friend IIterator<Item, MapIter>;
    private:
        It iter;
        F func;
        explicit MapIter(It it, F&& fn) : iter(std::move(it)), func(std::forward<F>(fn)) {}
    protected:
        Item CurrentImpl() const { return func((OriginalItem)(iter.Current())); }
        void AdvanceImpl() { iter.Advance(); }
        bool CanNextImpl() const { return iter.CanNext(); }

    public:
        static MapIter New(It it, F&& fn) { return MapIter { std::move(it), std::forward<F>(fn) }; }
    };

    namespace Maps {
        template <IteratorAny It, class F>
        static MapIter<It, F> Iter(It it, F&& fn) { return MapIter<It, F>::New(std::move(it), std::forward<F>(fn)); }
    }
}

namespace Quasi {
    template <class T, class Super>
    template <FnArgs<T> F> Iter::MapIter<Super, F> IIterator<T, Super>::Map(F&& fn) const& {
        return Iter::Maps::Iter(super(), std::forward<F>(fn));
    }

    template <class T, class Super>
    template <FnArgs<T> F> Iter::MapIter<Super, F> IIterator<T, Super>::Map(F&& fn) && {
        return Iter::Maps::Iter(std::move(super()), std::forward<F>(fn));
    }
}