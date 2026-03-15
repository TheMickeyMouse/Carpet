#pragma once
#include "Hash.h"

namespace Quasi {
#pragma region Indexing
    template <usize N> struct GetTupleElement {
        template <class T, class U, class V, class W, class... Rest>
        using Result = typename GetTupleElement<N - 4>::template DeferResult<Rest...>;
        template <class T, class U, class V, class W, class... Rest>
        static Result<T, U, V, W, Rest...> GetDeferResult;
        template <class... Ts> using DeferResult = decltype(GetDeferResult<Ts...>);
    };

    template <> struct GetTupleElement<0> {
        template <class T, class...> using Result = T;
        template <class T, class... Ts> static T GetDeferResult;
        template <class... Ts> using DeferResult = decltype(GetDeferResult<Ts...>);
    };
    template <> struct GetTupleElement<1> {
        template <class T, class U, class...> using Result = U;
        template <class T, class U, class... Ts> static U GetDeferResult;
        template <class... Ts> using DeferResult = decltype(GetDeferResult<Ts...>);
    };
    template <> struct GetTupleElement<2> {
        template <class T, class U, class V, class...> using Result = V;
        template <class T, class U, class V, class... Ts> static V GetDeferResult;
        template <class... Ts> using DeferResult = decltype(GetDeferResult<Ts...>);
    };
    template <> struct GetTupleElement<3> {
        template <class T, class U, class V, class W, class...> using Result = W;
        template <class T, class U, class V, class W, class... Ts> static W GetDeferResult;
        template <class... Ts> using DeferResult = decltype(GetDeferResult<Ts...>);
    };

    template <usize N, class... Types>
    using TupleElement = typename GetTupleElement<N>::template Result<Types...>;

    namespace ComptimeInt {
        struct DigitAccum {
            usize n = 0;

            constexpr DigitAccum operator+(char x) const {
                return { '0' <= x && x <= '9' ? n * 10 + (x - '0') : n };
            }
        };

        template <char... Digits>
        static constexpr usize _ReadNum = (DigitAccum { 0 } + ... + Digits).n;
    }

    template <usize N> struct StaticIndex { static constexpr usize Index = N; };
    template <char... Digits> using ParseStaticIndex = StaticIndex<ComptimeInt::_ReadNum<Digits...> - 1>;

    template <char... Digits> ParseStaticIndex<Digits...> operator ""_th() {
        return ParseStaticIndex<Digits...> {};
    }
    // for 1_st
    template <char... Digits> ParseStaticIndex<Digits...> operator ""_st() {
        return ParseStaticIndex<Digits...> {};
    }
    // for 2_nd
    template <char... Digits> ParseStaticIndex<Digits...> operator ""_nd() {
        return ParseStaticIndex<Digits...> {};
    }
    // for 3_rd
    template <char... Digits> ParseStaticIndex<Digits...> operator ""_rd() {
        return ParseStaticIndex<Digits...> {};
    }
#pragma endregion

    template <class...> struct Tuple;

    template <class T, class... Ts> struct Tuple<T, Ts...> {
        T first;
        Tuple<Ts...> rest;

        Tuple() = default;
        Tuple(T first, Ts... rest) : first((T&&)first), rest((Ts&&)rest...) {}

        template <usize N>
        const TupleElement<N, T, Ts...>& Get() const {
            if constexpr (N == 0) return first;
            else return rest.template Get<N - 1>();
        }
        template <usize N>
        TupleElement<N, T, Ts...>& Get() {
            if constexpr (N == 0) return first;
            else return rest.template Get<N - 1>();
        }

        // structured binding support
        template <usize N> const TupleElement<N, T, Ts...>& get() const { return Get<N>(); }
        template <usize N> TupleElement<N, T, Ts...>& get() { return Get<N>(); }

        template <usize N> const TupleElement<N, T, Ts...>& operator[](StaticIndex<N>) const { return Get<N>(); }
        template <usize N>       TupleElement<N, T, Ts...>& operator[](StaticIndex<N>)       { return Get<N>(); }

        template <class U, class... Us>
        void TieTo(U& out, Us&... outs) const {
            out = first;
            rest.TieTo(outs...);
        }
        void TieMoveTo(T& out, Ts&... outs) {
            out = std::move(first);
            rest.TieMoveTo(outs...);
        }

        Hashing::Hash GetHashCode() const {
            Hashing::Hash h = Hashing::HashObject(first);
            h = Hashing::HashCombine(h, rest.GetHashCode());
            return h;
        }
    };

    template <> struct Tuple<> {
        Tuple() = default;

        template <usize> void Get() const = delete;
        template <usize> void get() const = delete;
        void operator[](auto) const = delete;
        void TieTo() const {}
        void TieMoveTo() const {}
        Hashing::Hash GetHashCode() const { return Hashing::EmptyHash(); }
    };

    template <class... Ts>
    Tuple(Ts...) -> Tuple<Ts...>;
}

// structured binding support
template <class... Ts>
struct std::tuple_size<Quasi::Tuple<Ts...>> { static constexpr Quasi::usize value = sizeof...(Ts); };
template <Quasi::usize N, class... Ts>
struct std::tuple_element<N, Quasi::Tuple<Ts...>> { using type = Quasi::TupleElement<N, Ts...>; };