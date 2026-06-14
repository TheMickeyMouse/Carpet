#pragma once
#include "Continuous.h"

namespace Quasi {
    template <class T, usize N> using CArray = T[N];

    template <class T>
    struct ZeroArray {
        operator T*() const { return nullptr; }
    };

    template <class T, usize N>
    struct Array : IContinuous<T, Array<T, N>> {
        friend IContinuous<T, Array>;
    private:
        using InnerRawArray = IfElse<N == 0, ZeroArray<T>, T[N]>;
        InnerRawArray array {};
    protected:
        T* DataImpl() { return array; }
        const T* DataImpl() const { return array; }
        usize LengthImpl() const { return N; }
    public:
        constexpr Array(const InnerRawArray& r) { Memory::RangeCopyNoOverlap(array, r, N); }
        constexpr Array(InnerRawArray&& r)      { Memory::RangeMoveNoOverlap(array, r, N); }
        constexpr Array(SimilarTo<T> auto&&... args) : array { args... } {}
        InnerRawArray& CArr() { return array; }
        const InnerRawArray& CArr() const { return array; }
    };

    template <class T, SimilarTo<T>... U>
    Array(T&&, U&&...) -> Array<RemQual<T>, 1 + sizeof...(U)>;
    template <class T, usize N>
    Array(T(&&)[N]) -> Array<RemQual<T>, N>;

    namespace Arrays {
        template <class T, usize N>
        Array<T, N> Of(const T (&x)[N]) { return Array<T, N> { x }; }

        template <class A>
        Array<ArrayElement<A>, ArrayLength<A>> FromCArray(A&& array) {
            return { array };
        }

        template <Numeric T, usize N>
        Array<T, N> Range(T start = 0, T step = 1) {
            Array<T, N> range;
            for (usize i = 0; i < N; ++i, start += step) {
                range[i] = start;
            }
            return range;
        }
    }
}
