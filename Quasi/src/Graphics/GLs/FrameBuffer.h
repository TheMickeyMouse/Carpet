#pragma once

#include "GLObject.h"
#include "Utils/Math/Rect.h"

namespace Quasi::Graphics {
    class RenderBuffer;
    class TextureBase;
    enum class TextureTarget : int;
    template <TextureTarget> class TextureObject;

    enum class AttachmentType {
        COLOR_0  = 0x8CE0,
        COLOR_1  = 0x8CE1,
        COLOR_2  = 0x8CE2,
        COLOR_3  = 0x8CE3,
        COLOR_4  = 0x8CE4,
        COLOR_5  = 0x8CE5,
        COLOR_6  = 0x8CE6,
        COLOR_7  = 0x8CE7,
        COLOR_8  = 0x8CE8,
        COLOR_9  = 0x8CE9,
        COLOR_10 = 0x8CEA,
        COLOR_11 = 0x8CEB,
        COLOR_12 = 0x8CEC,
        COLOR_13 = 0x8CED,
        COLOR_14 = 0x8CEE,
        COLOR_15 = 0x8CEF,
        DEPTH = 0x8D00,
        STENCIL = 0x8D20,
        DEPTH_STENCIL = 0x821A,
    };

    class FrameBuffer : public GLObject<FrameBuffer> {
    private:
        explicit FrameBuffer(GraphicsID id);
    public:
        FrameBuffer() = default;
        static FrameBuffer New();
        static void DestroyObject(GraphicsID id);
        static void BindObject(GraphicsID id);
        static void UnbindObject();

        template <TextureTarget Target>
        void Attach(const TextureObject<Target>& tex, int mipmapLvl = 0, AttachmentType type = AttachmentType::COLOR_0) const {
            Attach((const TextureBase&)tex, (int)Target, mipmapLvl, type);
        }
        void Attach(const TextureBase& tbase, int target, int mipmapLvl = 0, AttachmentType type = AttachmentType::COLOR_0) const;
        void Attach(const RenderBuffer& rbo, AttachmentType type) const;
        void Complete() const;

        void BindReadSrc() const;
        void BindDrawDest() const;
        static void UnbindDrawDest();
        static void UnbindReadSrc();
        static FrameBuffer Screen();

        static void BlitFramebuffers(const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear = true);
        void BlitTo(const FrameBuffer& dest, const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear = true) const;
        void BlitToScreen(const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear = true) const;
        void BlitFromScreen(const Math::iRect2D& srcRect, const Math::iRect2D& destRect, bool linear = true) const;

        friend class GraphicsDevice;
    };
}
