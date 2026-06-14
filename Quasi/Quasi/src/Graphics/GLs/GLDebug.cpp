#include "GLDebug.h"

#include <glp.h>

namespace Quasi::Graphics {
    Debug::Logger GLDebugContainer::Logger { Text::StringWriter::WriteToConsole() };
    Debug::TimeDuration GLDebugContainer::GpuProcessDuration { 0 };

    Debug::Logger& GLLogger() {
        return GLDebugContainer::Logger;
    }

    void InitGLDebugTools() {
        GLLogger().SetName("OpenGL");
        GLLogger().SetNameColor(Text::ConsoleColor::FG_GREEN);
        GLLogger().SetBreakLevel(Debug::Severity::ERROR);
        GLLogger().SetShortenFile(true);
        GLLogger().SetIncludeFunc(false);
        GLLogger().SetLocPad(0);
    }

    Str GetErrName(GLErrorCode ec) {
        using enum GLErrorCode;
        switch (ec) {
            case INVALID_ENUM:                  return "INVALID_ENUM"_str;
            case INVALID_VALUE:                 return "INVALID_VALUE"_str;
            case INVALID_OPERATION:             return "INVALID_OPERATION"_str;
            case STACK_OVERFLOW:                return "STACK_OVERFLOW"_str;
            case STACK_UNDERFLOW:               return "STACK_UNDERFLOW"_str;
            case OUT_OF_MEMORY:                 return "OUT_OF_MEMORY"_str;
            case INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION"_str;
            case CONTEXT_LOST:                  return "CONTEXT_LOST"_str;
            case TABLE_TOO_LARGE:               return "TABLE_TOO_LARGE"_str;
            default:                            return "NO_ERROR"_str;
        }
    }

    GLErrorCode GLGetErr() {
        return (GLErrorCode)GL::GetError();
    }

    void GLClearErr() {
        while (GL::GetError()) {}
    }

    void GLReport(const Debug::SourceLoc& loc) {
        GLErrorCode err;
        while ((err = GLGetErr()) != GLErrorCode::NO_ERROR) {
            GLLogger().QError$({ "GL Error code {} was uncaught.", loc }, err);
        }
    }

    void GLReportFn(Str signature, const Debug::SourceLoc& loc) {
        GLErrorCode err;
        while ((err = GLGetErr()) != GLErrorCode::NO_ERROR) {
            Str funcCall = signature.SplitOnce("::")[2_nd];
            GLLogger().QError$(
                { "GL Error code {} was uncaught when calling gl{} (see https://docs.gl/gl4/gl{}).", loc },
                err, funcCall, funcCall.SplitOnce('(')[1_st]);
        }
    }
}
