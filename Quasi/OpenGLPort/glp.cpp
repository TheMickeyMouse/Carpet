#include "glp.h"

namespace GL {
#define COMMA() ,
#define EMPTY()
#define WAIT(X) X EMPTY() ()
#define RUN(...) __VA_ARGS__
#define CAT(A, B) A##B
#define CAT2(A, B) CAT(A, B)
#define DEL_FIRST(X, ...) __VA_ARGS__
#define ARGS_1(T) WAIT(COMMA) T ARGS_2
#define ARGS_2(V) V ARGS_1
#define ARGS_1END
#define ARGS_2END
#define SEND_1(T) WAIT(COMMA) /* (RMCONST(T, CAST_IF_ENUM)) */ SEND_2
#define SEND_2(V) V SEND_1
#define SEND_1END
#define SEND_2END

// #define PROBER(X1, X2, X3, ...) X3
// #define CHECK_ENUM_Enum ,
// #define PROBE_ENUM(X) RUN(PROBER EMPTY() (RUN(CAT2(CHECK_ENUM_, X), 1, 0)))
// #define CHECK_CONST_const ,
// #define PROBE_CONST(X) RUN(PROBER EMPTY() (RUN(CAT2(CHECK_CONST_, X), 1, 0)))
// #define RM_const
// #define RM_CONST_1(X, M) const M(CAT2(RM_, X))
// #define RM_CONST_0(X, M) M(X)
// #define RMCONST(X, M) CAT2(RM_CONST_, PROBE_CONST(X))(X, M)
// #define INTO_Enum unsigned int
// #define INTO_UINT_1(X) CAT2(INTO_, X)
// #define INTO_UINT_0(X) X
// #define CAST_IF_ENUM(X) CAT2(INTO_UINT_, PROBE_ENUM(X))(X)

#define IMPL_FN(NAME, RET, ARGS) \
    RET NAME(RUN(DEL_FIRST EMPTY() (CAT2(ARGS_1 ARGS, END)))) \
    { return gl##NAME(RUN(DEL_FIRST EMPTY() (CAT2(SEND_1 ARGS, END)))); }

    GLPORT_ON_FUNCTIONS(IMPL_FN)

    bool Supports(const char* name) {
        return glewIsExtensionSupported(name);
    }

    Enum InitGLEW() {
        return glewInit();
    }
}