#pragma once

#include "Utils/Box.h"
#include "Utils/Variant.h"
#include "GLObject.h"

#include "GLTypeID.h"
#include "Image.h"
#include "Render.h"
#include "TextureConstants.h"
#include "Utils/Math/Rect.h"

namespace Quasi::Graphics {
    struct Image;
}

namespace Quasi {
    struct CStr;
}

namespace Quasi::Graphics {
    struct TextureLoadParams {
        TextureFormat format = TextureFormat::RGBA;
        TextureIFormat internalformat = TextureIFormat::RGBA_8;
        bool pixelated = false;
        TextureBorder border = TextureBorder::CLAMP_TO_EDGE;
        TID::E type = TID::BYTE;
    };

    struct STBIImageHandler { void operator()(byte* dat) const; };
    using STBIImage = Box<byte, STBIImageHandler>;

    class TextureBase : public GLObject<TextureBase> {
    public:
        static void DestroyObject(GraphicsID id);
        static void BindObject(TextureTarget target, GraphicsID id);
        static void UnbindObject(TextureTarget target);
        static void SetSample(TextureTarget target, TextureSample sample);
        static void SetWrapping(TextureTarget target, int dim, TextureBorder border);
        static void SetParam(TextureTarget target, TextureParamName paramName, int          value);
        static void SetParam(TextureTarget target, TextureParamName paramName, float        value);
        static void SetParam(TextureTarget target, TextureParamName paramName, const int*   value);
        static void SetParam(TextureTarget target, TextureParamName paramName, const float* value);

        static void SetPixelStore(PixelStoreParam param, int val);

        void Activate(TextureTarget target, int slot) const;

        TextureBase() = default;
        TextureBase(GraphicsID id);
    };

    template <TextureTarget Target>
    class TextureObject : public TextureBase {
        using enum TextureTarget;
        static constexpr u32 DIM = Target == _1D || Target == ARRAY_1D ? 1 :
                                   Target == _2D || Target == ARRAY_2D ? 2 :
                                   Target == _3D || Target == CUBEMAP  ? 3 : 0;

        void DefaultParams(bool pixelated, TextureBorder b) const;
        void LoadTexture(const byte* img, const TextureLoadParams& loadMode = {});

        explicit TextureObject(GraphicsID id, const Math::Vector<int, DIM>& size);
    public:
        Math::Vector<int, DIM> size;

        TextureObject() = default;
        static TextureObject New(const byte* raw, const Math::Vector<int, DIM>& size, const TextureLoadParams& loadMode = {});
        static TextureObject New(const Image& image, const TextureLoadParams& loadMode = {}) requires (Target == _2D);
        void Bind() const { BindObject(Target, rendererID); }
        void Unbind() const { UnbindObject(Target); }

        static TextureObject LoadPNGBytes(Bytes pngbytes, const TextureLoadParams& loadMode = {})
            requires (Target == _2D);
        static TextureObject LoadPNG(CStr fname, const TextureLoadParams& loadMode = {})
            requires (Target == _2D);

        static TextureObject LoadCubemapPNG(IList<CStr> faces /* in order: rludfb */, const TextureLoadParams& loadMode = {})
            requires (Target == CUBEMAP);

        void Activate(int slot);
        void BindImageTexture(int slot, int mipmapLevel = 0, Access access = Access::READ_WRITE, TextureIFormat format = TextureIFormat::RGBA_32F);

        void SetSample(TextureSample s) const { TextureBase::SetSample(Target, s); }
        void SetMinifySample (TextureSample s) const { TextureBase::SetParam(Target, TextureParamName::MIN_FILTER, (int)s); }
        void SetMagnifySample(TextureSample s) const { TextureBase::SetParam(Target, TextureParamName::MIN_FILTER, (int)s); }
        void SetWrapping(TextureBorder b) const { TextureBase::SetWrapping(Target, DIM, b); }
        void SetBorderColor(const Math::fColor& color) const { TextureBase::SetParam(Target, TextureParamName::BORDER_COLOR, color.Data()); }
        void SetMinMip(int level)   const { TextureBase::SetParam(Target, TextureParamName::BASE_LEVEL, level); }
        void SetMaxMip(int level)   const { TextureBase::SetParam(Target, TextureParamName::MAX_LEVEL,  level); }
        void SetMipBias(float bias) const { TextureBase::SetParam(Target, TextureParamName::LOD_BIAS,   bias); }
        void SetParam(TextureParamName paramName, int          value) const { TextureBase::SetParam(Target, paramName, value); }
        void SetParam(TextureParamName paramName, float        value) const { TextureBase::SetParam(Target, paramName, value); }
        void SetParam(TextureParamName paramName, const int*   value) const { TextureBase::SetParam(Target, paramName, value); }
        void SetParam(TextureParamName paramName, const float* value) const { TextureBase::SetParam(Target, paramName, value); }

        void SetSubTexture(const byte* data, const Math::Rect<int, DIM>& rect, const TextureLoadParams& params = {}, int level = 0);
        void SetSubTexture(ImageView image, const Math::iv2& pos, const TextureLoadParams& params = {}, int level = 0) requires (DIM == 2);
        void SetTexture(const byte* data, const Math::Vector<int, DIM>& dim, const TextureLoadParams& params = {}, int level = 0);
        void GenerateEmptyMipmaps(const Math::Vector<int, DIM>& dim, const TextureLoadParams& params = {}, u32 levels = 0);

        const Math::Vector<int, DIM>& Size() const { return size; }
        Math::Vector<f32, DIM> Px2UV(const Math::Vector<int, DIM>& px) const {
            return px.template As<f32>().DivComps(size.template As<f32>());
        }
        Math::Vector<int, DIM> UV2Px(const Math::Vector<f32, DIM>& uv) const {
            return (uv.MulComps(size.template As<f32>())).template As<int>();
        }
        Math::Rect<f32, DIM> Px2UV(const Math::Rect<int, DIM>& pxRect) const {
            return pxRect.template As<f32>() / size.template As<f32>();
        }
        Math::Rect<int, DIM> UV2Px(const Math::Rect<f32, DIM>& uvRect) const {
            return (uvRect * size.template As<f32>()).template As<int>();
        }

        friend class FrameBuffer;
    };

    using Texture1D = TextureObject<TextureTarget::_1D>;
    using Texture2D = TextureObject<TextureTarget::_2D>;
    using Texture3D = TextureObject<TextureTarget::_3D>;
    using Texture1DArray = TextureObject<TextureTarget::ARRAY_1D>;
    using Texture2DArray = TextureObject<TextureTarget::ARRAY_2D>;
    using TextureCubemap = TextureObject<TextureTarget::CUBEMAP>;
}
