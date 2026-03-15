#include "RenderBuffer.h"
#include <glp.h>
#include "GLDebug.h"
#include "TextureConstants.h"

namespace Quasi::Graphics {
    RenderBuffer::RenderBuffer(GraphicsID id) : GLObject(id) {}

    RenderBuffer RenderBuffer::New(TextureIFormat format, Math::iv2 size) {
        GraphicsID id;
        QGLCall$(GL::GenRenderbuffers(1, &id));
        BindObject(id);
        QGLCall$(GL::RenderbufferStorage(GL::RENDERBUFFER, (int)format, size.x, size.y));
        UnbindObject();
        return RenderBuffer { id };
    }

    void RenderBuffer::DestroyObject(GraphicsID id) {
        QGLCall$(GL::DeleteRenderbuffers(1, &id));
    }

    void RenderBuffer::BindObject(GraphicsID id) {
        QGLCall$(GL::BindRenderbuffer(GL::RENDERBUFFER, id));
    }

    void RenderBuffer::UnbindObject() {
        QGLCall$(GL::BindRenderbuffer(GL::RENDERBUFFER, 0));
    }
}
