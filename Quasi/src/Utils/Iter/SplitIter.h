#pragma once
#include "Utils/Iterator.h"

namespace Quasi::Iter {
    template <class View>
    struct SplitIter : IIterator<const View, SplitIter<View>> {
        friend IIterator<const View, SplitIter>;
        using Item = const View;
    private:
        View source, separator;
        usize i = -1;
        SplitIter(View src, View sep) : source(src), separator(sep) { AdvanceImpl(); }
    protected:
        View CurrentImpl() const { return source.First(i); }
        void AdvanceImpl() {
            if (i == source.Length()) {
                source.Advance(i);
                return;
            }
            source.Advance(i + separator.Length());
            for (i = 0; i < source.Length(); ++i) {
                if (source.Skip(i).StartsWith(separator)) return;
            }
        }
        bool CanNextImpl() const { return !source.IsEmpty(); }
    public:
        static SplitIter New(View src, View sep) { return { src, sep }; }
    };
}
