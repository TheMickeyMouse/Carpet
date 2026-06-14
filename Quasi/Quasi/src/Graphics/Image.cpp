#include "Image.h"

#include "glp.h"
#include "GraphicsDevice.h"
#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "Utils/CStr.h"

namespace Quasi::Graphics {
    u8* Image::AllocImage(int w, int h) {
        return Memory::AllocateArrayUninit<u8>(w * h * 4);
    }

    Image Image::Empty() {
        return { nullptr, 0, 0 };
    }

    Image Image::New(int w, int h) {
        return { AllocImage(w, h), w, h };
    }

    Image Image::SolidColor(const Math::uColor& color, int w, int h) {
        Image solidColor = New(w, h);
        Memory::RangeSet(solidColor.PixelData(), color, w * h);
        return solidColor;
    }

    Image Image::CopyData(ImageView view) {
        u8* data = AllocImage(view.width, view.height);
        for (int y = 0; y < view.height; y++) {
            Memory::MemCopyNoOverlap(&data[y * view.width], &view.data[y * view.stride], view.width * 4);
        }
        return { data, view.width, view.height };
    }

    Image Image::LoadPNGBytes(Bytes pngbytes) {
        int w, h, BPPixel;
        stbi_set_flip_vertically_on_load(1);
        u8* localTexture = stbi_load_from_memory(pngbytes.Data(), (int)pngbytes.Length(), &w, &h, &BPPixel, 4);
        return localTexture ? FromData(localTexture, w, h) : Empty();
    }

    Image Image::LoadPNG(CStr fname) {
        int w, h, BPPixel;
        stbi_set_flip_vertically_on_load(1);
        u8* localTexture = stbi_load(fname.Data(), &w, &h, &BPPixel, 4);
        return localTexture ? FromData(localTexture, w, h) : Empty();
    }

    Image Image::CaptureScreen(bool flip) {
        const Math::iv2 size = GraphicsDevice::GetDeviceInstance().GetWindowSize();
        return CaptureScreen(0, 0, size.x, size.y, flip);
    }

    Image Image::CaptureScreen(int x, int y, int w, int h, bool flip) {
        u8* screenBuf = AllocImage(w, h);
        // note: this returns the screen but flipped horizontally
        GL::ReadPixels(x, y, w, h, GL::RGBA, GL::UNSIGNED_BYTE, screenBuf);
        Image screen = { screenBuf, w, h };
        if (flip) screen.FlipVertical();
        return screen;
    }

    Image Image::CaptureScreen(const Math::iRect2D& screenRect, bool flip) {
        return CaptureScreen(screenRect.min.x, screenRect.min.y, screenRect.Width(), screenRect.Height(), flip);
    }

    ImageView Image::AsView() const {
        return { *this };
    }

    ImageView Image::SubImage(int x, int y, int w, int h) const {
        return ImageView::FromData(Data() + 4 * (x + y * width), w, h, width);
    }

    ImageView Image::SubImage(const Math::iRect2D& subrect) const {
        return SubImage(subrect.min.x, subrect.min.y, subrect.Width(), subrect.Height());
    }

    bool Image::InBounds(const Math::iv2& coord) const {
        return 0 < coord.x && coord.x < width && 0 < coord.y && coord.y < height;
    }

    const Math::uColor& Image::GetPx(const Math::iv2& coord) const {
        return PixelData()[coord.x + coord.y * width];
    }

    Math::uColor& Image::GetPx(const Math::iv2& coord) {
        return PixelData()[coord.x + coord.y * width];
    }

    OptRef<const Math::uColor> Image::TryGetPx(const Math::iv2& coord) const {
        return InBounds(coord) ? OptRefs::SomeRef(GetPx(coord)) : nullptr;
    }

    OptRef<Math::uColor> Image::TryGetPx(const Math::iv2& coord) {
        return InBounds(coord) ? OptRefs::SomeRef(GetPx(coord)) : nullptr;
    }

    Span<const Math::uColor> Image::GetRow(int y) const {
        return Spans::Slice(PixelData() + y * width, width);
    }

    Span<Math::uColor> Image::GetRow(int y) {
        return Spans::Slice(PixelData() + y * width, width);
    }

    const Math::uColor* Image::PixelData() const {
        return Memory::TransmutePtr<const Math::uColor>(imageData.Data());
    }
    Math::uColor* Image::PixelData() {
        return Memory::TransmutePtr<Math::uColor>(imageData.Data());
    }

    Span<const Math::uColor> Image::Pixels() const {
        return Spans::Slice(PixelData(), (usize)(width * height));
    }

    Span<Math::uColor> Image::Pixels() {
        return Spans::Slice(PixelData(), (usize)(width * height));
    }

    void Image::Crop(const Math::iRect2D& rect) {
        const int oldWidth = width;
        width = rect.Width();
        height = rect.Height();
        u8* newBuf = AllocImage(width, height);
        for (int y = 0; y < height; y++) {
            Memory::MemCopyNoOverlap(&newBuf[4 * y * width], &imageData.Data()[4 * y * oldWidth], width * 4);
        }
        imageData.Replace(newBuf);
    }

    void Image::FlipHorizontal() {
        for (int y = 0; y < height; y++) {
            GetRow(y).Reverse();
        }
    }

    void Image::FlipVertical() {
        for (int y = 0; y < height / 2; y++) {
            Memory::MemSwap(&imageData.Data()[4 * y * width], &imageData.Data()[4 * (height - y) * width], width * 4);
        }
    }

    void Image::Flip180() {
        Pixels().Reverse();
    }

    void Image::SwapBytes() {
        u32* pixels = Memory::TransmutePtr<u32>(imageData.Data());
        for (usize i = 0; i < width * height; ++i) {
            // for anyone who asks: i chose the names k & u unconsciously,
            // but there is a high likely hood i just them because of K + U = E. xd

            // turns pixels in format RGBA to BGRA. a pixel is a u32.
            // k stores R0B0, k >> 16 = 00R0, k << 16 = B000.
            if constexpr (Memory::IsBigEndian()) {
                const u32 k = pixels[i] & 0xFF00FF00;
                pixels[i] += (k >> 16) + (k << 16) - k;
            } else {
                const u32 k = pixels[i] & 0x00FF00FF;
                pixels[i] += (k >> 16) + (k << 16) - k;
            }
        }
    }

    void Image::BlitImage(const Math::iv2& dest, const ImageView& image) {
        u8* begin = (u8*)&PixelData()[dest.x + dest.y * width];
        for (int y = 0; y < image.height; y++) {
            Memory::MemCopyNoOverlap(begin + 4 * y * width, &image.data[4 * y * image.stride], image.width * 4);
        }
    }

    void Image::ExportPNG(Str fdest) {
        stbi_write_png(fdest.Data(), (int)width, (int)height, 4, imageData.Data(), 0);
    }

    void Image::Free() {
        imageData.Close();
    }

    ImageView ImageView::FromData(const u8* imageData, int w, int h) {
        return { imageData, w, h, w };
    }

    ImageView ImageView::FromData(const u8* imageData, int w, int h, int stride) {
        return { imageData, w, h, stride };
    }

    ImageView ImageView::SubImage(int x, int y, int w, int h) const {
        return { data + 4 * (x + y * stride), w, h, stride };
    }

    ImageView ImageView::SubImage(const Math::iRect2D& subrect) const {
        return SubImage(subrect.min.x, subrect.min.y, subrect.Width(), subrect.Height());
    }

    bool ImageView::InBounds(const Math::iv2& coord) const {
        return 0 < coord.x && coord.x < width && 0 < coord.y && coord.y < height;
    }

    const Math::uColor& ImageView::GetPx(const Math::iv2& coord) const {
        return PixelData()[coord.x + coord.y * stride];
    }

    OptRef<const Math::uColor> ImageView::TryGetPx(const Math::iv2& coord) const {
        return InBounds(coord) ? OptRefs::SomeRef(GetPx(coord)) : nullptr;
    }

    Span<const Math::uColor> ImageView::GetRow(int y) const {
        return Spans::Slice(PixelData() + y * stride, width);
    }

    const Math::uColor* ImageView::PixelData() const {
        return Memory::TransmutePtr<const Math::uColor>(data);
    }

    void ImageView::ExportPNG(Str fdest) const {
        stbi_write_png(fdest.Data(), width, height, 4, data, stride * 4);
    }
}
