#pragma once
#include "Func.h"

namespace Quasi {
    namespace Cmp { enum Comparison : int; }

    template <class T>
    concept Comparable = requires (const T& lhs, const T& rhs) {
        { lhs.Cmp(rhs) } -> ConvTo<Cmp::Comparison>;
    } || requires (const T& lhs, const T& rhs) {
        { lhs <=> rhs };
    };

    template <class F, class T>
    concept Comparator = Fn<F, Cmp::Comparison, const T&, const T&>;
    template <class F, class T>
    concept EqualPred  = Fn<F, bool, const T&, const T&>;

    namespace Cmp {
        enum Comparison : int {
            LESS    = -1,
            EQUAL   = 0,
            GREATER = 1
        };

        inline bool operator< (Comparison cmp, int) { return cmp == LESS; }
        inline bool operator<=(Comparison cmp, int) { return cmp != GREATER; }
        inline bool operator==(Comparison cmp, int) { return cmp == EQUAL; }
        inline bool operator!=(Comparison cmp, int) { return cmp != EQUAL; }
        inline bool operator>=(Comparison cmp, int) { return cmp != LESS; }
        inline bool operator> (Comparison cmp, int) { return cmp == GREATER; }
        inline bool operator- (Comparison cmp)      { return (Comparison)(-(int)cmp); }
        Comparison IntoComparison(const auto& cmp) { return (Comparison)((cmp > 0) - (cmp < 0)); }

        template <Comparable T>
        Comparison Between(const T& left, const T& right) {
            if constexpr (requires { { left.Cmp(right) } -> ConvTo<Comparison>; }) {
                return left.Cmp(right);
            } else {
                return IntoComparison(left <=> right);
            }
        }
#pragma region Comparison Functors
        template <class T> struct LessThan { const T& obj; bool operator()(const auto& x) const { return x < obj; } };
        template <> struct LessThan<void> { bool operator()(const auto& lhs, const auto& rhs) const { return lhs < rhs; } };

        struct LessEquals    { bool operator()(const auto& left, const auto& right) const { return left <= right; } };
        struct GreaterEquals { bool operator()(const auto& left, const auto& right) const { return left >= right; } };
        struct GreaterThan   { bool operator()(const auto& left, const auto& right) const { return left <  right; } };

        template <class T> struct Equals { const T& obj; bool operator()(const auto& x) const { return x == obj; } };
        template <> struct Equals<void> { bool operator()(const auto& lhs, const auto& rhs) const { return lhs == rhs; } };

        template <class T> struct Compare { const T& obj; Comparison operator()(const auto& x) const { return IntoComparison(x <=> obj); } };
        template <> struct Compare<void> { Comparison operator()(const auto& lhs, const auto& rhs) const { return IntoComparison(lhs <=> rhs); } };

        template <class T>
        LessThan(const T&) -> LessThan<T>;
        LessThan() -> LessThan<void>;
        template <class T>
        Equals(const T&) -> Equals<T>;
        Equals() -> Equals<void>;
        template <class T>
        Compare(const T&) -> Compare<T>;
        Compare() -> Compare<void>;
#pragma endregion
    }

    using Cmp::Comparison;
}