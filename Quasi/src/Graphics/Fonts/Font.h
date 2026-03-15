#pragma once
#include <freetype/freetype.h>

#include "FontDevice.h"
#include "Mesh.h"
#include "GLs/Texture.h"

#define Q_USER_FONTS R"(C:\Users\User\AppData\Local\Microsoft\Windows\Fonts\)"
#define Q_WIN_FONTS R"(C:\Windows\Fonts\)"

struct FT_FaceRec_;

namespace Quasi::Graphics {
    struct FontDeleter { void operator()(FT_FaceRec_* ptr) const; };
    using FaceHandle = Box<FT_FaceRec_, FontDeleter>;

    struct Glyph {
        // internal coords
        Math::fRect2D rect;
        // render data
        Math::fv2 advance;
        Math::iv2 offset;
    };

    class Font {
        static constexpr int DEFAULT_FONT_ID = 0, MONOSPACE_FONT_ID = 1;
        FaceHandle faceHandle = nullptr;
        int fontSize = 0;
    public:
        struct FontMetrics {
            int fontHeight = 0, ascend = 0, descend = 0;
        };
    private:
        static constexpr u32 NUM_GLYPHS = 127 - 32;
        Vec<Glyph> glyphs;
        FontMetrics metrics;
        Texture2D atlas;

        Font(FT_FaceRec_* fHand, int fontSize) : faceHandle(FaceHandle::Own(fHand)), fontSize(fontSize) {}
    public:
        Font() = default;
        static Font New(FT_FaceRec_* fHand, int fontSize);

        int FontSize() const { return fontSize; }
        void RenderBitmap();

        const Glyph& GetGlyphRect(char c) const;
        // Mesh<VertexTexture2D> RenderText(
        //     Str string, int size,
        //     const TextAlign& align = { { 0, f32s::INFINITY } }
        // ) const;

        float CalcTextWidth(Str text) const;
        
        Texture2D& GetTexture() { return atlas; }
        const Texture2D& GetTexture() const { return atlas; }
        
        static Font LoadFile (CStr filename, int fontSize);
        static Font LoadBytes(Bytes bytes, int fontSize);

        const FontMetrics& GetMetric() const { return metrics; }

        friend struct TextRenderer;
    };

    enum TextStyle {
        NONE = 0,
        BOLD          = 1 << 0,
        ITALIC        = 1 << 1,
        UNDERLINE     = 1 << 2,
        STRIKETHROUGH = 1 << 3,
        SUBSCRIPT     = 1 << 4,
        SUPERSCRIPT   = 1 << 5,
    };
}
