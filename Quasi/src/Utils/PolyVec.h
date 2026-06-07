#pragma once
#include "Vec.h"

namespace Quasi {
    // equivalent to Vec<Box<T>>, but a lot better lol
    template <class T>
    class PolyVec : public IContinuous<Ref<T>, PolyVec<T>> {
        friend ICollection<Ref<T>, PolyVec>;
        friend IContinuous<Ref<T>, PolyVec>;
        Vec<Box<T>> ptrs;
    protected:
        usize LengthImpl() const { return ptrs.Length(); }
        Ref<T>* DataImpl() { return Memory::TransmutePtr<Ref<T>>(ptrs.Data()); }
        const Ref<T>* DataImpl() const { return Memory::TransmutePtr<const Ref<T>>(ptrs.Data()); }
    public:
        T& Push(Box<T> x) { return *ptrs.Push(std::move(x)); }
        template <Extends<T> U> U& Push(U x) {
            auto boxU = Box<U>::New(x);
            U& underlying = *boxU;
            ptrs.Push(std::move(boxU));
            return underlying;
        }
    };
} // Quasi