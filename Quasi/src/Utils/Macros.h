#pragma once

#pragma region Common
#define Q_EAT(...)
#define Q_UNARY(...) __VA_ARGS__
#define Q_UNARY2(...) __VA_ARGS__
#define Q_UNARY3(...) __VA_ARGS__

#define Q_INTERNAL_CAT(A, B) A##B
#define Q_CAT(A, B) Q_INTERNAL_CAT(A, B)
#define Q_INTERNAL_TOSTR(...) #__VA_ARGS__
#define Q_TOSTR(...) Q_INTERNAL_TOSTR(__VA_ARGS__)

#define Q_COMMA() ,
#define Q_LPAREN() (
#define Q_RPAREN() )
#define Q_EMPTY()
#define Q_DEFER(...) __VA_ARGS__ Q_EMPTY()
#define Q_INVOKE(M, ...) M(__VA_ARGS__)
#define Q_DEFERED_INVOKE(M, ...) Q_UNARY(Q_DEFER(M)(__VA_ARGS__))
#define Q_REMOVE_SCOPE(X) Q_UNARY X
#define Q_SEPERATE(...) (__VA_ARGS__),

#define Q_REMOVE_BRACKETS_INNER(...) Q_REMOVE_BRACKETS_INNER __VA_ARGS__
#define Q_END_Q_REMOVE_BRACKETS_INNER
#define Q_REMOVE_BRACKETS(...) Q_CAT(Q_END_, Q_REMOVE_BRACKETS_INNER __VA_ARGS__)

#define Q_EXPAND(...)   Q_EXPAND1_(Q_EXPAND1_(Q_EXPAND1_(Q_EXPAND1_(__VA_ARGS__))))
#define Q_EXPAND1_(...) Q_EXPAND2_(Q_EXPAND2_(Q_EXPAND2_(Q_EXPAND2_(__VA_ARGS__))))
#define Q_EXPAND2_(...) Q_EXPAND3_(Q_EXPAND3_(Q_EXPAND3_(Q_EXPAND3_(__VA_ARGS__))))
#define Q_EXPAND3_(...) Q_EXPAND4_(Q_EXPAND4_(Q_EXPAND4_(Q_EXPAND4_(__VA_ARGS__))))
#define Q_EXPAND4_(...) __VA_ARGS__

#define Q_DETECT(...)     Q_ARGS_SECOND(__VA_ARGS__ 1, 0)
#define Q_DETECT_NOT(...) Q_ARGS_SECOND(__VA_ARGS__ 0, 1)
#pragma endregion

#pragma region Conditionals
#define Q_NOT_0 1
#define Q_NOT_1 0
#define Q_NOT(CONDITION) Q_CAT(Q_NOT_, CONDITION)

#define Q_OR(A, B)  Q_IF_ELSE(A, (1), (B))
#define Q_AND(A, B) Q_IF_ELSE(A, (B), (0))

#define Q_IF_0(...)
#define Q_IF_1(...) __VA_ARGS__
#define Q_IF(CONDITION, ...) Q_CAT(Q_IF_, CONDITION)(__VA_ARGS__)
#define Q_IF_NOT(CONDITION, ...) Q_IF(Q_NOT(CONDITION), __VA_ARGS__)
#define Q_IF_ELSE_0(A, B) Q_UNARY B
#define Q_IF_ELSE_1(A, B) Q_UNARY A
// side note: A, B are assumed to be wrapped in parens
#define Q_IF_ELSE(CONDITION, A, B) Q_CAT(Q_IF_ELSE_, CONDITION)(A, B)
#pragma endregion

#pragma region Arguments & Tuples

// Tuple - (a, b, c)
// + easy concat, random access, subranges
// - slow iteration

#define Q_ARGS_SKIP(FIRST, ...)                      __VA_ARGS__
#define Q_ARGS_FIRST(FIRST, ...)                     FIRST
#define Q_ARGS_SKIP_SECOND(FIRST, SECOND, ...)       __VA_ARGS__
#define Q_ARGS_SECOND(FIRST, SECOND, ...)            SECOND
#define Q_ARGS_SKIP_THIRD(FIRST, SECOND, THIRD, ...) __VA_ARGS__
#define Q_ARGS_THIRD(FIRST, SECOND, THIRD, ...)      THIRD
#define Q_ARGS_PARTITION_0(X0, ...)                                                                       ((), X0, (__VA_ARGS__))
#define Q_ARGS_PARTITION_1(X0, X1, ...)                                                                 ((X0), X1, (__VA_ARGS__))
#define Q_ARGS_PARTITION_2(X0, X1, X2, ...)                                                         ((X0, X1), X2, (__VA_ARGS__))
#define Q_ARGS_PARTITION_3(X0, X1, X2, X3, ...)                                                 ((X0, X1, X2), X3, (__VA_ARGS__))
#define Q_ARGS_PARTITION_4(X0, X1, X2, X3, X4, ...)                                         ((X0, X1, X2, X3), X4, (__VA_ARGS__))
#define Q_ARGS_PARTITION_5(X0, X1, X2, X3, X4, X5, ...)                                 ((X0, X1, X2, X3, X4), X5, (__VA_ARGS__))
#define Q_ARGS_PARTITION_6(X0, X1, X2, X3, X4, X5, X6, ...)                         ((X0, X1, X2, X3, X4, X5), X6, (__VA_ARGS__))
#define Q_ARGS_PARTITION_7(X0, X1, X2, X3, X4, X5, X6, X7, ...)                 ((X0, X1, X2, X3, X4, X5, X6), X7, (__VA_ARGS__))
#define Q_ARGS_PARTITION_8(X0, X1, X2, X3, X4, X5, X6, X7, X8, ...)         ((X0, X1, X2, X3, X4, X5, X6, X7), X8, (__VA_ARGS__))
#define Q_ARGS_PARTITION_9(X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, ...) ((X0, X1, X2, X3, X4, X5, X6, X7, X8), X9, (__VA_ARGS__))
#define Q_ARGS_AT_0(X0, ...)                                     X0
#define Q_ARGS_AT_1(X0, X1, ...)                                 X1
#define Q_ARGS_AT_2(X0, X1, X2, ...)                             X2
#define Q_ARGS_AT_3(X0, X1, X2, X3, ...)                         X3
#define Q_ARGS_AT_4(X0, X1, X2, X3, X4, ...)                     X4
#define Q_ARGS_AT_5(X0, X1, X2, X3, X4, X5, ...)                 X5
#define Q_ARGS_AT_6(X0, X1, X2, X3, X4, X5, X6, ...)             X6
#define Q_ARGS_AT_7(X0, X1, X2, X3, X4, X5, X6, X7, ...)         X7
#define Q_ARGS_AT_8(X0, X1, X2, X3, X4, X5, X6, X7, X8, ...)     X8
#define Q_ARGS_AT_9(X0, X1, X2, X3, X4, X5, X6, X7, X8, X9, ...) X9
#define Q_ARGS_PARITION_NTH(TUP, N) Q_CAT(Q_ARGS_PARTITION_, N) TUP
#define Q_ARGS_AT_NTH(TUP, N)       Q_CAT(Q_ARGS_AT_,        N) TUP
#define Q_ARGS_FIRST_N(TUP, N)   Q_ARGS_FIRST(Q_ARGS_PARITION_NTH(TUP, N))
#define Q_ARGS_UPTO_N(TUP, N)    (Q_UNARY Q_ARGS_FIRST(Q_ARGS_PARITION_NTH(TUP, N)), Q_ARGS_AT_NTH(TUP, N))
#define Q_ARGS_SKIP_N(TUP, N)    (Q_ARGS_AT_NTH(TUP, N), Q_UNARY Q_ARGS_THIRD(Q_ARGS_PARITION_NTH(TUP, N)))
#define Q_ARGS_AFTER_N(TUP, N)   Q_ARGS_THIRD(Q_ARGS_PARITION_NTH(TUP, N))
#define Q_ARGS_LAST(...) Q_ARGS_AT_NTH((, __VA_ARGS__), Q_COUNT_ARGS(__VA_ARGS__))

#define Q_COUNT_ARGS(...) Q_ARGS_64TH(__VA_ARGS__, \
63, 62, 61, 60,                         \
59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
9,  8,  7,  6,  5,  4,  3,  2,  1,  0)
#define Q_ARGS_64TH( \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
    _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
    _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
    _61,_62,_63,N,...) N

#define Q_DUMMY_TUPLE_0() ()
#define Q_DUMMY_TUPLE_1() (~)
#define Q_DUMMY_TUPLE_2() (~, ~)
#define Q_DUMMY_TUPLE_3() (~, ~, ~)
#define Q_DUMMY_TUPLE_4() (~, ~, ~, ~)
#define Q_DUMMY_TUPLE_5() (~, ~, ~, ~, ~)
#define Q_DUMMY_TUPLE_6() (~, ~, ~, ~, ~, ~)
#define Q_DUMMY_TUPLE_7() (~, ~, ~, ~, ~, ~, ~)
#define Q_DUMMY_TUPLE_8() (~, ~, ~, ~, ~, ~, ~, ~)
#define Q_DUMMY_TUPLE_9() (~, ~, ~, ~, ~, ~, ~, ~, ~)
#define Q_DUMMY_TUPLE_N(N) Q_CAT(Q_DUMMY_TUPLE_, N)()

#define Q_OPT_IF_ARGS(M, ...) __VA_OPT__(M)
#define Q_COMMA_IF_ARGS(...)  __VA_OPT__(,)

#define Q_HAS_ARGS(...)       Q_DETECT(__VA_OPT__(,))
#define Q_NO_ARGS(...)        Q_DETECT_NOT(__VA_OPT__(,))
#define Q_INVERT_ARGS(...)    Q_REMOVE_SCOPE(Q_ARGS_AT_1(__VA_OPT__(,) (), (~)))

#define Q_IF_ARGS(ARGS, ...)    Q_OPT_IF_ARGS(Q_DEFER(Q_UNARY)(__VA_ARGS__), Q_UNARY ARGS)
#define Q_IF_NO_ARGS(ARGS, ...) Q_OPT_IF_ARGS(Q_DEFER(Q_UNARY)(__VA_ARGS__), Q_INVERT_ARGS ARGS)
#define Q_IF_ARGS_ELSE(ARGS, IF, ELSE) Q_REMOVE_SCOPE(Q_INVOKE(Q_ARGS_AT_1, Q_COMMA_IF_ARGS ARGS IF, ELSE))

#define Q_CONCAT_TUPLE_COMMA(ATUP, BTUP) Q_IF_ARGS_ELSE(ATUP, (Q_IF_ARGS_ELSE(BTUP, (Q_COMMA), (Q_EMPTY))), (Q_EMPTY))()
#define Q_CONCAT_TUPLE(ATUP, BTUP) (Q_UNARY ATUP Q_CONCAT_TUPLE_COMMA(ATUP, BTUP) Q_UNARY BTUP)

#define Q_OVERLOAD_FN(ARGS, ... /* FUNCTION OVERLOADS */) Q_ARGS_AT_NTH((__VA_ARGS__), Q_COUNT_ARGS ARGS)
#pragma endregion

#pragma region Language Utilities
#define Q_DO(...) do { __VA_ARGS__ } while (false)
#define Q_IGNORE(...) (void)(__VA_ARGS__)
#define Q_NOOP() Q_IGNORE(0)

#define Q_TYPEOF_VAR_DECL(V) Quasi::Matching::TypeOfVar<void(*)(V)>

#define Q_STRLIT_LEN(STR) (sizeof(STR) - 1)
#define Q_ARRAY_LEN(ARR) (sizeof(ARR) / sizeof(ARR[0]))

#ifdef __COUNTER__
#define Q_COUNTER() __COUNTER__
#else
#error "__COUNTER__" Macro Not Supported!
#endif

#define Q_UNIQUE_ID(NAME) Q_CAT(NAME, Q_COUNTER())

#if defined(__GNUC__) || defined(__clang__)
#define Q_FUNC_NAME() __PRETTY_FUNCTION__
#else
#ifdef _MSVC
#define Q_FUNC_NAME() __FUNCSIG__
#else
#error "Function Signature macro not supported"
#endif
#endif
#pragma endregion