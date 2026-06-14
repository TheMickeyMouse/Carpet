#include "Font.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "GLs/GLDebug.h"
#include "Utils/Algorithm.h"

namespace Quasi::Graphics {
    void FontDeleter::operator()(FT_FaceRec_* ptr) const {
        if (ptr) FT_Done_Face(ptr);
    }

    Font Font::New(FT_FaceRec_* fHand, int fontSize) {
        Font f = { fHand, fontSize * 64 };

        // const u32 dpi = FontDevice::DPI();
        // int error = FT_Set_Char_Size(fHand, 0, fontSize, dpi, dpi);
        // GLLogger().Assert(!error, "Font Char size set with err code {}", error);
        int error = FT_Set_Pixel_Sizes(fHand, 0, fontSize);
        GLLogger().Assert(!error, "Font Char size set with err code {}", error);

        f.RenderBitmap();

        return f;
    }

    void Font::RenderBitmap() {
        using namespace Math;

        constexpr int LOAD_SDF = FT_LOAD_RENDER | FT_LOAD_TARGET_(FT_RENDER_MODE_SDF); // used for sdf rendering
        constexpr int SDF_EXTRUDE = 8;

        const FT_GlyphSlot glyphHandle = faceHandle->glyph;

        struct GlyphInfo { iv2 size; char c; };
        GlyphInfo glyphInfo[NUM_GLYPHS];
        for (char charCode = 32; charCode < 127; ++charCode) { // loop through each character
            // new method: SDFs extrude 8 pixels in all directions, so you can load normally and then add 16
            // (no need to load twice!)
            if (const int error = FT_Load_Char(faceHandle.DataMut(), charCode, FT_LOAD_DEFAULT)) {
                GLLogger().QError$("Loading char with err code {}", error);
                continue;  /* ignore errors */
            }

            glyphInfo[charCode - 32] = {
                {
                    (int)glyphHandle->bitmap.width + SDF_EXTRUDE,
                    (int)glyphHandle->bitmap.rows + SDF_EXTRUDE
                }, charCode
            };
        }

        Span(glyphInfo).SortByKey([] (const GlyphInfo& info) { return info.size.y; });

        // packing algorithm
        int minWidth = 0;
        usize area = 0;
        for (const auto [size, _] : glyphInfo) {
            minWidth = std::max(minWidth, size.x);
            area += size.x * size.y;
        }
        const int width = std::max((int)std::sqrt(area), minWidth);

        static constexpr int PADDING = 1;
        glyphs.ResizeDefault(NUM_GLYPHS);
        iv2 pen = 0;
        // proceed to fit the next glyphs, making sure to not exceed the first row
        for (usize i = 0; i < NUM_GLYPHS; ++i) {
            const auto& g = glyphInfo[i];
            if (pen.x + g.size.x > width) {
                pen.x = 0;
                // heights are sorted in order, so we can safely add the previous
                pen.y += glyphInfo[i - 1].size.y + PADDING;
            }
            // default value for now; will fix in later stages
            glyphs[g.c - 32] = { fRect2D::FromSize((fv2)pen, (fv2)g.size), 0, 0 };
            pen.x += g.size.x + PADDING;
        }
        pen.y += glyphInfo[NUM_GLYPHS - 1].size.y;

        Texture2D::SetPixelStore(PixelStoreParam::UNPACK_ALIGNMENT, 1);
        atlas = Texture2D::New(nullptr, { width, pen.y },
            { .format = TextureFormat::RED, .internalformat = TextureIFormat::R_8 }
        ); // create blank texture
        atlas.Clear(0);
        atlas.Bind(); // set this texture to the active one
        glyphs.Resize(NUM_GLYPHS); // amt of glyphs

        metrics = {
            (int)(faceHandle->size->metrics.ascender - faceHandle->size->metrics.descender),
            (int)faceHandle->size->metrics.ascender,
            (int)faceHandle->size->metrics.descender
        };

        const fv2 invTextureSize = 1.0f / (fv2)atlas.size;
        for (char charCode = 32; charCode < 127; ++charCode) { // loop through again, this time drawing textures
            if (const int error = FT_Load_Char(faceHandle.DataMut(), charCode, LOAD_SDF)) { // loads again
                GLLogger().QError$("Loading char with err code {}", error);
                continue;
            }

            Glyph& glyph = glyphs[charCode - 32]; // write rendering memory
            const iv2 size = { (int)glyphHandle->bitmap.width, (int)glyphHandle->bitmap.rows }; // construct size in pixels of the texture
            atlas.SetSubTexture(glyphHandle->bitmap.buffer, iRect2D::FromSize((iv2)glyph.rect.min, size), { .format = TextureFormat::RED }); // draw the sub texture

            glyph.rect = glyph.rect * invTextureSize; // resize
            glyph.advance = { (float)glyphHandle->advance.x / 64.0f, (float)glyphHandle->advance.y / 64.0f }; // pen move
            glyph.offset  = { glyphHandle->bitmap_left, glyphHandle->bitmap_top }; // offset from pen
        }
        Texture2D::SetPixelStore(PixelStoreParam::UNPACK_ALIGNMENT, 4);
    }

    const Glyph& Font::GetGlyphRect(char c) const {
        return glyphs[c - 32];
    }

    float Font::SpaceWidth() const {
        return GetGlyphRect(' ').advance.x;
    }

    float Font::CalcCharWidth(char c) const {
        if (Chr::IsWhitespace(c)) c = ' ';
        return GetGlyphRect(c).advance.x;
    }

    float Font::CalcTextWidth(Str text) const {
        float width = 0;
        for (const char c : text) {
            width += CalcCharWidth(c);
        }
        return width;
    }

    // Mesh<VertexTexture2D> Font::RenderText(Str string, int size, const TextAlign& align) const {
    //     TextRenderer text { *this };
    //     text.SetAlign(align);
    //     text.SetFontSize(size);
    //     text.RenderText(string);
    //
    //     Vec ind = Vec<TriIndices>::WithCap(text.textVertices.Length() / 2);
    //     for (u32 i = 0; i < ind.Capacity(); i += 2) {
    //         ind.Push(TriIndices { 0, 1, 2 } + i * 2);
    //         ind.Push(TriIndices { 1, 2, 3 } + i * 2);
    //     }
    //
    //     return Mesh { std::move(text.textVertices), std::move(ind) }; // return the text mesh
    // }

    Font Font::LoadFile(CStr filename, int fontSize) {
        FT_Face face = nullptr;
        const int error = FT_New_Face(FontDevice::Library(), filename.Data(), 0, &face);
        if (!error) {
            return New(face, fontSize);
        }
        
        if (error == FT_Err_Unknown_File_Format)
            GLLogger().QError$("Font {} doesn't have valid format", filename);
        else
            GLLogger().QError$("Font loaded with err code {}", error);
        return {};
    }

    Font Font::LoadBytes(Bytes bytes, int fontSize) {
        FT_Face face;
        const int error = FT_New_Memory_Face(FontDevice::Library(), bytes.Data(), bytes.Length(), 0, &face);
        if (!error) {
            return New(face, fontSize);
        }
        
        GLLogger().QError$("Font loaded with err code {}", error);
        return {};
    }
}
