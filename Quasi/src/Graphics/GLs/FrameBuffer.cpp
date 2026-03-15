#include "FrameBuffer.h"

#include <glp.h>

#include "RenderBuffer.h"
#include "GLDebug.h"
#include "Texture.h"

namespace Quasi::Graphics {
    FrameBuffer::FrameBuffer(GraphicsID id) : GLObject(id) {}

    FrameBuffer FrameBuffer::New() {
        GraphicsID id;
        QGLCall$(GL::GenFramebuffers(1, &id));
        return FrameBuffer { id };
    }

    void FrameBuffer::DestroyObject(GraphicsID id) {
        QGLCall$(GL::DeleteFramebuffers(1, &id));
    }

    void FrameBuffer::BindObject(GraphicsID id) {
        QGLCall$(GL::BindFramebuffer(GL::FRAMEBUFFER, id));
    }

    void FrameBuffer::UnbindObject() {
        QGLCall$(GL::BindFramebuffer(GL::FRAMEBUFFER, 0));
    }

    void FrameBuffer::Attach(const TextureBase& tbase, int target, int mipmapLvl, AttachmentType type) const {
        QGLCall$(GL::FramebufferTexture2D(GL::FRAMEBUFFER, (int)type, target, tbase.rendererID, mipmapLvl));
    }

    void FrameBuffer::Attach(const RenderBuffer& rbo, AttachmentType type) const {
        QGLCall$(GL::FramebufferRenderbuffer(GL::FRAMEBUFFER, (int)type, GL::RENDERBUFFER, rbo.rendererID));
    }

    void FrameBuffer::Complete() const {
        const int status = GL::CheckFramebufferStatus(GL::FRAMEBUFFER);
        if (status != GL::FRAMEBUFFER_COMPLETE) {
            GLLogger().QError$("Framebuffer was incomplete with code 0x{:04X}.", status);
        }
    }

    void FrameBuffer::BindReadSrc() const {
        QGLCall$(GL::BindFramebuffer(GL::READ_FRAMEBUFFER, rendererID));
    }

    void FrameBuffer::BindDrawDest() const {
        QGLCall$(GL::BindFramebuffer(GL::DRAW_FRAMEBUFFER, rendererID));
    }

    void FrameBuffer::UnbindDrawDest() {
        QGLCall$(GL::BindFramebuffer(GL::DRAW_FRAMEBUFFER, 0));
    }

    void FrameBuffer::UnbindReadSrc() {
        QGLCall$(GL::BindFramebuffer(GL::READ_FRAMEBUFFER, 0));
    }

    FrameBuffer FrameBuffer::Screen() {
        return {};
    }

    void FrameBuffer::BlitFramebuffers(const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear) {
        QGLCall$(GL::BlitFramebuffer(srcRect.min.x, srcRect.min.y, srcRect.max.x, srcRect.max.y,
                                     destRect.min.x, destRect.min.y, destRect.max.x, destRect.max.y, GL::COLOR_BUFFER_BIT, linear ? GL::LINEAR : GL::NEAREST));
    }

    void FrameBuffer::BlitTo(const FrameBuffer& dest, const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear) const {
        BindReadSrc();
        dest.BindDrawDest();
        BlitFramebuffers(srcRect, destRect, linear);
    }

    void FrameBuffer::BlitToScreen(const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear) const {
        BindReadSrc();
        UnbindDrawDest();
        BlitFramebuffers(srcRect, destRect, linear);
    }

    void FrameBuffer::BlitFromScreen(const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear) const {
        BindDrawDest();
        UnbindReadSrc();
        BlitFramebuffers(srcRect, destRect, linear);
    }
}
