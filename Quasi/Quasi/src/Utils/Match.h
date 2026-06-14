#pragma once
#include <algorithm>

#include "Macros.h"
#include "MacroIteration.h"
#include "Type.h"
#include "Variant.h"

#define Q_MATCH_EXPR(X, B) Q_INVOKE(Q_ARGS_AT_1, Q_MATCH_DISPATCH_TYPE X, Q_MATCH_VALUE)(Q_COUNTER(), X, B)
#define Q_MATCH_DISPATCH_TYPE(T) Q_CAT(Q_MATCH_DISPATCH_DETECT_, T)
#define Q_MATCH_DISPATCH_DETECT_typename , Q_MATCH_TYPE,
#define Q_MATCH_BRANCHES(U, N, SEQ) Q_ITERATE_W_SEQUENCE(Q_MATCH_BRANCH_MAP, (N, U), SEQ)
#define Q_MATCH_BRANCH_MAP(NU, B) Q_UNARY3(Q_DEFER(Q_INVOKE)(Q_CAT(Q_MATCH_BRANCH_, Q_UNARY B), Q_UNARY NU))
#define Q_MATCH_BRANCH_MACRO(M, B, N, U) Q_UNARY2(Q_DEFER(Q_CAT(M, N))(U, Q_SEPERATE B))

#define Q_MATCH_BRANCH_case Q_MATCH_BRANCH_MACRO, Q_MATCH_BRANCH_CASE_,
#define Q_MATCH_BRANCH_CASE_VALS(U, VAL, STMT) if (_mv_##U == VAL) { STMT goto _m_end_##U; }
#define Q_MATCH_BRANCH_CASE_TYPE(U, VAL, STMT) if constexpr (std::is_same_v<_mv_##U, Q_UNARY VAL>) { STMT } else

#define Q_MATCH_BRANCH_if Q_MATCH_BRANCH_MACRO, Q_MATCH_BRANCH_IF_,
#define Q_MATCH_BRANCH_IF_VALS(U, COND, STMT) if (_mv_##U Q_UNARY COND) { STMT goto _m_end_##U; }
#define Q_MATCH_BRANCH_IF_TYPE(U, COND, STMT) if constexpr ([] { using $ = _mv_##U; return requires Q_UNARY COND; } ()) { STMT } else

#define Q_MATCH_BRANCH_in Q_MATCH_BRANCH_MACRO, Q_MATCH_BRANCH_IN_,
#define Q_MATCH_BRANCH_IN_VALS(U, COND, STMT) if (Quasi::Matching::In(_mv_##U, Q_UNARY COND)) { STMT goto _m_end_##U; }
#define Q_MATCH_BRANCH_IN_TYPE(U, COND, STMT) Q_MATCH_BRANCH_IN_TYPE_SEQ(U, Q_TUP_TO_SEQUENCE(COND), STMT)
#define Q_MATCH_BRANCH_IN_TYPE_SEQ(U, S, STMT) if constexpr (Q_ITERATE_W_SEQUENCE_N2(Q_MATCH_BRANCH_IN_TYPE_EACH, _mv_##U, S) false) { STMT } else
#define Q_MATCH_BRANCH_IN_TYPE_EACH(T, U) std::is_same_v<T, Q_UNARY U> ||

#define Q_MATCH_BRANCH_is Q_MATCH_BRANCH_MACRO, Q_MATCH_BRANCH_IS_,
#define Q_MATCH_BRANCH_IS_VALS(U, COND, STMT) if (Q_UNARY COND (_mv_##U)) { STMT goto _m_end_##U; }
#define Q_MATCH_BRANCH_IS_TYPE(U, COND, STMT) if constexpr ([] { using $ = _mv_##U; return COND; } ()) { STMT } else

#define Q_MATCH_BRANCH_instanceof Q_MATCH_BRANCH_MACRO, Q_MATCH_BRANCH_INSTANCEOF_,
#define Q_MATCH_BRANCH_INSTANCEOF_VALS(U, COND, STMT) Q_MATCH_BRANCH_INSTANCEOF_U(U, Q_UNIQUE_ID(_mr_), COND, STMT)
#define Q_MATCH_BRANCH_INSTANCEOF_U(U, V, COND, STMT) if (auto V = Quasi::Matching::InstanceOf<std::remove_cvref_t<std::remove_pointer_t<Q_TYPEOF_VAR_DECL COND>>>(_mv_##U)) { Q_UNARY COND = V; STMT goto _m_end_##U; }
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE(U, COND, STMT) Q_UNARY(Q_DEFER(Q_MATCH_BRANCH_INSTANCEOF_TYPE_PATCH)(U, Q_CAT(Q_MATCH_BRANCH_INSTANCEOF_TYPE_, Q_UNARY COND), STMT))
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_PATCH(...) Q_OVERLOAD_FN((__VA_ARGS__), ~, ~, ~, Q_MATCH_BRANCH_INSTANCEOF_TYPE_C, ~, Q_MATCH_BRANCH_INSTANCEOF_TYPE_R)(__VA_ARGS__)
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_C(U, COND, STMT) if constexpr (COND<_mv_##U>) { STMT } else
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_R(U, COND, REM, RES, STMT) if constexpr (COND () _mv_##U>) { using RES = REM<_mv_##U>; STMT } else
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_enum       std::is_enum_v< Q_EMPTY
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_int        std::is_integral_v< Q_EMPTY
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_unsigned   std::is_unsigned_v< Q_EMPTY
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_float      std::is_floating_point_v< Q_EMPTY
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_num        std::is_arithmetic_v< Q_EMPTY
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_void       std::is_void_v< Q_EMPTY
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_const      IsConst< Q_EMPTY, RemConst,
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_ref        Quasi::IsRef< Q_EMPTY, Quasi::RemRef,
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_const_ref  Quasi::IsConstRef< Q_EMPTY, Quasi::RemConstRef,
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_ptr        Quasi::IsPtr< Q_EMPTY, Quasi::RemPtr,
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_const_ptr  Quasi::IsConstPtr< Q_EMPTY, Quasi::RemConstPtr,
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_conv(T)    Quasi::ConvTo<T Q_COMMA
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_similar(T) Quasi::SimilarTo<T Q_COMMA
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_extends(T) Quasi::Extends<T Q_COMMA
#define Q_MATCH_BRANCH_INSTANCEOF_TYPE_satisfies(T) T

#define Q_MATCH_BRANCH_has Q_MATCH_BRANCH_MACRO, Q_MATCH_BRANCH_HAS_,
#define Q_MATCH_BRANCH_HAS_TYPE(U, COND, STMT) Q_UNARY(Q_DEFER(Q_ARGS_SECOND)(Q_CAT(Q_MATCH_BRANCH_HAS_DETECT_, Q_ARGS_FIRST COND), Q_MATCH_BRANCH_HAS_TYPE_MEMBER))(U, COND, STMT)
#define Q_MATCH_BRANCH_HAS_DETECT_typename , Q_MATCH_BRANCH_HAS_TYPE_TYPEDEF,
#define Q_MATCH_BRANCH_HAS_TYPE_MEMBER(U, COND, STMT) if constexpr (requires (_mv_##U u) { { u.Q_ARGS_FIRST COND } -> Quasi::AlwaysTrue; }) { Q_UNARY(Q_DEFER(Q_MATCH_BRANCH_HAS_TYPE_TYPEDEF_A)(decltype(_mv_##U {}.Q_ARGS_FIRST COND), Q_UNARY COND)) STMT } else
#define Q_MATCH_BRANCH_HAS_TYPE_TYPEDEF(U, COND, STMT) if constexpr (requires { typename _mv_##U::Q_CAT(Q_MATCH_BRANCH_HAS_MEMB_REMOVE_TYPENAME_, Q_ARGS_FIRST COND); }) { Q_UNARY(Q_DEFER(Q_MATCH_BRANCH_HAS_TYPE_TYPEDEF_A)(typename _mv_##U::Q_CAT(Q_MATCH_BRANCH_HAS_MEMB_REMOVE_TYPENAME_, Q_ARGS_FIRST COND), Q_UNARY COND)) STMT } else
#define Q_MATCH_BRANCH_HAS_TYPE_TYPEDEF_A(T, K, ...) __VA_OPT__(using Q_CAT(Q_MATCH_BRANCH_HAS_MEMB_REMOVE_AS_, __VA_ARGS__) = T;)
#define Q_MATCH_BRANCH_HAS_MEMB_REMOVE_AS_as
#define Q_MATCH_BRANCH_HAS_MEMB_REMOVE_TYPENAME_typename

#define Q_MATCH_BRANCH_else Q_MATCH_BRANCH_ELSE, ~,
#define Q_MATCH_BRANCH_ELSE(M, B, N, U) B

#define Q_MATCH_VALUE(U, X, B) { auto& Q_CAT(_mv_, U) = X; Q_MATCH_BRANCHES(U, VALS, Q_TUP_TO_SEQUENCE(B)) Q_CAT(_m_end_, U): Q_NOOP(); }
#define Q_MATCH_TYPE(U, X, B)  { using Q_CAT(_mv_, U) = Q_EAT X; Q_MATCH_BRANCHES(U, TYPE, Q_TUP_TO_SEQUENCE(B)) Q_NOOP(); }
#define Q_MATCH_VALUE(U, X, B) { auto& Q_CAT(_mv_, U) = X; Q_MATCH_BRANCHES(U, VALS, Q_TUP_TO_SEQUENCE(B)) Q_CAT(_m_end_, U): Q_NOOP(); }

#ifdef Q_EXT_MATCH_SYNTAX
#define Qmatch$(...) Q_MATCH_EXPR(__VA_ARGS__)
#else
#warning Extended Match syntax has been disabled (define Q_EXT_MATCH_SYNTAX to enable), some syntax features wont work properly
#endif

namespace Quasi::Matching {
    template <class Fn> struct TypeOfArg {};
    template <class Res, class Arg> struct TypeOfArg<Res(*)(Arg)> { using type = Arg; };
    template <class Fn> using TypeOfVar = typename TypeOfArg<Fn>::type;

    template <class T>
    bool In(const T& value, Collection<T> auto& list) {
        if constexpr (requires { { list.Contains(value) } -> SameAs<bool>; })
            return list.Contains(value);
        else {
            const auto it = std::find(std::begin(list), std::end(list), value);
            return it == std::end(list) ? false : true;
        }
    }

    template <class T>
    bool In(const T& value, IList<T> list) {
        return In(value, Span<T> { list });
    }

    template <class T, BaseOf<T> U> requires (IsConst<T> || IsMut<U>)
    OptRef<T> InstanceOf(U& u) {
        return DerefPtr(dynamic_cast<T*>(&u));
    }

    template <class T, BaseOf<T> U> requires (IsConst<T> || IsMut<U>)
    OptRef<T> InstanceOf(U* u) {
        return DerefPtr(dynamic_cast<T*>(u));
    }

    template <class Der, BaseOf<Der> Base> requires (IsConst<Der> || IsMut<Base>)
    OptRef<Der> InstanceOf(Ref<Base> u) {
        return u.template As<Der>();
    }

    template <class Der, BaseOf<Der> Base> requires (IsConst<Der> || IsMut<Base>)
    OptRef<Der> InstanceOf(OptRef<Base> u) {
        return u.template As<Der>();
    }

    template <class T, class... Us> requires (SameAs<T, Us> || ...)
    OptRef<const T> InstanceOf(const Variant<Us...>& u) {
        return u.template As<T>();
    }

    template <class T, class... Us> requires (SameAs<T, Us> || ...)
    OptRef<T> InstanceOf(Variant<Us...>& u) {
        return u.template As<T>();
    }
}
