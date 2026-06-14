#pragma once

#include "Utils/Debug/Logger.h"

namespace Quasi::Graphics {
    // a very thin wrapper for an extern variable
    // (couldnt get them to work so here's an alternative)
    struct GLDebugContainer {
        static Debug::Logger Logger;
        static Debug::TimeDuration GpuProcessDuration;
    };

    Debug::Logger& GLLogger();

    void InitGLDebugTools();

    enum class GLErrorCode {
        // taken from https://www.khronos.org/opengl/wiki/OpenGL_Error#Catching_errors_(the_hard_way)
        // Given when an enumeration parameter is not a legal enumeration for that function.
        // This is given only for local problems; if the spec allows the enumeration in certain circumstances,
        // where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead.
        INVALID_ENUM            = 0x0500,
        // Given when a value parameter is not a legal value for that function.
        // This is only given for local problems; if the spec allows the value in certain circumstances,
        // where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead.
        INVALID_VALUE           = 0x0501,
        // Given when the set of state for a command is not legal for the parameters given to that command.
        // It is also given for commands where combinations of parameters define what the legal parameters are.
        INVALID_OPERATION       = 0x0502,
        // Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size.
        STACK_OVERFLOW          = 0x0503,
        // Given when a stack popping operation cannot be done because the stack is already at its lowest point.
        STACK_UNDERFLOW         = 0x0504,
        // Given when performing an operation that can allocate memory, and the memory cannot be allocated.
        // The results of OpenGL functions that return this error are undefined;
        // it is allowable for partial execution of an operation to happen in this circumstance.
        OUT_OF_MEMORY           = 0x0505,
        // Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete.
        // (with OpenGL 4.5 or ARB_KHR_robustness)
        INVALID_FRAMEBUFFER_OPERATION = 0x0506,
        // Given if the OpenGL context has been lost, due to a graphics card reset.
        CONTEXT_LOST            = 0x0507,
        // Part of the ARB_imaging extension.
        TABLE_TOO_LARGE         = 0x8031,
        NO_ERROR                = 0,
    };

    Str GetErrName(GLErrorCode ec);

    GLErrorCode GLGetErr();
    void GLClearErr();
    void GLReport(const Debug::SourceLoc& loc = Debug::SourceLoc::current());
    void GLReportFn(Str signature, const Debug::SourceLoc& loc = Debug::SourceLoc::current());

    template <class F>
    auto GLCall(F&& f, Str fsig, const Debug::SourceLoc& loc = Debug::SourceLoc::current()) -> decltype(f()) {
        GLClearErr();
        if constexpr (SameAs<void, decltype(f())>) {
            const auto begin = Debug::Timer::Now();
            f();
            const Debug::DateTime end = Debug::Timer::Now();
            GLDebugContainer::GpuProcessDuration += end - begin;
            GLReportFn(fsig, loc);
            return;
        } else {
            const auto begin = Debug::Timer::Now();
            const auto res = f();
            const Debug::DateTime end = Debug::Timer::Now();
            GLDebugContainer::GpuProcessDuration += end - begin;
            GLReportFn(fsig, loc);
            return res;
        }
    }
#ifdef NDEBUG
#define QGLCall$(X) (X)
#else
#define QGLCall$(X) GLCall([&]{ return X; }, #X)
#endif
}

template <>
struct Quasi::Text::Formatter<Quasi::Graphics::GLErrorCode> {
    static usize FormatTo(StringWriter output, Graphics::GLErrorCode err, Str) {
        return Text::FormatTo(output, "0x{:X04} ({})", (u32)err, GetErrName(err));
    }
};
