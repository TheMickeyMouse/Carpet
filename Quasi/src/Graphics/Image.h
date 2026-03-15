#pragma once

#include "Utils/Math/Vector.h"
#include "Utils/Math/Rect.h"
#include "Utils/Math/Color.h"

namespace Quasi::Graphics {
    struct ImageView;

    struct Image {
        Box<u8> imageData = nullptr;
        int width = 0, height = 0;

        Image() = default;
    private:
        Image(u8* imageData, int w, int h) : imageData(Box<u8>::Own(imageData)), width(w), height(h) {}

        static u8* AllocImage(int w, int h);
    public:
        static Image Empty();
        static Image New(int w, int h);
        static Image SolidColor(const Math::uColor& color, int w, int h);
        static Image FromData(u8* imageData, int w, int h) { return { imageData, w, h }; }
        static Image CopyData(ImageView view);
        static Image LoadPNGBytes(Bytes pngbytes);
        static Image LoadPNG(CStr fname);

        static Image CaptureScreen(bool flip = true);
        static Image CaptureScreen(int x, int y, int w, int h, bool flip = true);
        static Image CaptureScreen(const Math::iRect2D& screenRect, bool flip = true);

        ImageView AsView() const;
        ImageView SubImage(int x, int y, int w, int h) const;
        ImageView SubImage(const Math::iRect2D& subrect) const;

        bool InBounds(const Math::iv2& coord) const;
        const Math::uColor& GetPx(const Math::iv2& coord) const;
        Math::uColor& GetPx(const Math::iv2& coord);
        OptRef<const Math::uColor> TryGetPx(const Math::iv2& coord) const;
        OptRef<Math::uColor> TryGetPx(const Math::iv2& coord);

        Span<const Math::uColor> GetRow(int y) const;
        Span<Math::uColor> GetRow(int y);

        const Math::uColor& operator[](const Math::iv2& coord) const { return GetPx(coord); }
        Math::uColor& operator[](const Math::iv2& coord) { return GetPx(coord); }
        Span<const Math::uColor> operator[](int y) const { return GetRow(y); }
        Span<Math::uColor> operator[](int y) { return GetRow(y); }

        u8* ReleaseData() { return imageData.Release(); }
        const u8* Data() const { return imageData.Data(); }
        u8* Data() { return imageData.Data(); }
        const Math::uColor* PixelData() const;
        Math::uColor* PixelData();
        Span<const Math::uColor> Pixels() const;
        Span<Math::uColor> Pixels();
        Math::iv2 Size() const { return { width, height }; }

        void Crop(const Math::iRect2D& rect);
        void FlipHorizontal();
        void FlipVertical();
        void Flip180();
        // converts RGB to BGR pixel format or vice-versa; useful for alternative pixel sources like winapi.
        // note this could also be avoided by just uploading to gpu using GL_BGRA.
        void SwapBytes();

        void BlitImage(const Math::iv2& dest, const ImageView& image);

        void ExportPNG(Str fdest);

        void Free();
    };

    struct ImageView {
        const u8* data = nullptr;
        int width = 0, height = 0;
        // stride is the amount to advance to the next row
        int stride = 0;

        ImageView() = default;
    private:
        ImageView(const u8* data, int w, int h, int stride) : data(data), width(w), height(h), stride(stride) {}
    public:
        ImageView(const Image& img) : data(img.imageData.Data()), width(img.width), height(img.height), stride(img.width) {}

        static ImageView FromData(const u8* imageData, int w, int h);
        static ImageView FromData(const u8* imageData, int w, int h, int stride);

        ImageView SubImage(int x, int y, int w, int h) const;
        ImageView SubImage(const Math::iRect2D& subrect) const;

        bool InBounds(const Math::iv2& coord) const;
        const Math::uColor& GetPx(const Math::iv2& coord) const;
        OptRef<const Math::uColor> TryGetPx(const Math::iv2& coord) const;

        Span<const Math::uColor> GetRow(int y) const;

        const Math::uColor& operator[](const Math::iv2& coord) const { return GetPx(coord); }
        Span<const Math::uColor> operator[](int y) const { return GetRow(y); }

        const u8* Data() const { return data; }
        const Math::uColor* PixelData() const;
        Math::iv2 Size() const { return { width, height }; }

        void ExportPNG(Str fdest) const;
    };
}
