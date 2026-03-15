#pragma once
#include "Utils/Str.h"

namespace Quasi::Iter {
    struct LinesIter : IIterator<const Str, LinesIter> {
        using Item = const Str;
        friend IIterator;
    private:
        Str source;
        usize i = -1;
        LinesIter(Str src) : source(src) { AdvanceImpl(); }
    protected:
        Str CurrentImpl() const;
        void AdvanceImpl();
        bool CanNextImpl() const;
    public:
        static LinesIter New(Str s) { return { s }; }
    };
}
