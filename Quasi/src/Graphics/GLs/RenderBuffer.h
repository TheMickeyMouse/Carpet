#pragma once
#include "GLObject.h"
#include "TextureConstants.h"
#include "Utils/Math/Vector.h"

namespace Quasi::Graphics {
    enum class TextureIFormat;

    class RenderBuffer : public GLObject<RenderBuffer> {
        explicit RenderBuffer(GraphicsID id);
    public:
        RenderBuffer() = default;
        static RenderBuffer New(TextureIFormat format, Math::iv2 size);
        static void DestroyObject(GraphicsID id);
        static void BindObject(GraphicsID id);
        static void UnbindObject();

        friend class FrameBuffer;
        friend class GraphicsDevice;
    };
}
