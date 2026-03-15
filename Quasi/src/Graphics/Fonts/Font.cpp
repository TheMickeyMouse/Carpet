#include "Font.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "GLs/GLDebug.h"

namespace Quasi::Graphics {
    void FontDeleter::operator()(FT_FaceRec_* ptr) const {
        if (ptr) FT_Done_Face(ptr);
    }

    Font Font::New(FT_FaceRec_* fHand, int fontSize) {
        fontSize *= 64;
        Font f = { fHand, fontSize };

        const u32 dpi = FontDevice::DPI();
        const int error = FT_Set_Char_Size(fHand, fontSize, fontSize, dpi, dpi);
        GLLogger().Assert(!error, "Font Char size set with err code {}", error);

        f.RenderBitmap();

        return f;
    }

    void Font::RenderBitmap() {
        using namespace Math;
        int pen = 0; // x value of pen

        constexpr int loadSDF = FT_LOAD_RENDER | FT_LOAD_TARGET_(FT_RENDER_MODE_SDF); // used for sdf rendering
        constexpr int sdfExtrude = 16;

        const FT_GlyphSlot glyphHandle = faceHandle->glyph;
        int x = 0, y = 0;
        for (char charCode = 32; charCode < 127; ++charCode) { // loop through each character
            // new method: SDFs extrude 8 pixels in all directions, so you can load normally and then add 16
            // (no need to load twice!)
            if (const int error = FT_Load_Char(faceHandle.DataMut(), charCode, FT_LOAD_DEFAULT)) {
                GLLogger().QError$("Loading char with err code {}", error);
                continue;  /* ignore errors */
            }

            y = std::max(y, (int)glyphHandle->bitmap.rows); // y is guaranteed to fit the sdf
            x += (int)glyphHandle->bitmap.width; // packs sdfs together on the x axis
        }
        y += sdfExtrude;
        x += (NUM_GLYPHS - 1 /* space */) * sdfExtrude;

        Texture2D::SetPixelStore(PixelStoreParam::UNPACK_ALIGNMENT, 1);
        atlas = Texture2D::New(nullptr, { x, y },
            { .format = TextureFormat::RED, .internalformat = TextureIFormat::RGBA_8 }
        ); // create blank texture
        atlas.Bind(); // set this texture to the active one
        glyphs.Resize(NUM_GLYPHS); // amt of glyphs

        metrics = {
            (int)(faceHandle->size->metrics.ascender - faceHandle->size->metrics.descender),
            (int)faceHandle->size->metrics.ascender,
            (int)faceHandle->size->metrics.descender
        };

        const fv2 invTextureSize = { 1 / (float)x, 1 / (float)y };
        for (char charCode = 32; charCode < 127; ++charCode) { // loop through again, this time drawing textures
            if (const int error = FT_Load_Char(faceHandle.DataMut(), charCode, loadSDF)) { // loads again
                GLLogger().QError$("Loading char with err code {}", error);
                continue;
            }

            const iv2 size = { (int)glyphHandle->bitmap.width, (int)glyphHandle->bitmap.rows }; // construct size in pixels of the texture
            atlas.SetSubTexture(glyphHandle->bitmap.buffer, iRect2D::FromSize({ pen, 0 }, size), { .format = TextureFormat::RED }); // draw the sub texture

            Glyph& glyph = glyphs[charCode - 32]; // write rendering memory
            glyph.rect = fRect2D::FromSize({ (float)pen, (float)0 }, (fv2)size) * invTextureSize; // rect of texture in atlas
            glyph.advance = { (float)glyphHandle->advance.x / 64.0f, (float)glyphHandle->advance.y / 64.0f }; // pen move
            glyph.offset  = { glyphHandle->bitmap_left, glyphHandle->bitmap_top }; // offset from pen

            pen += (int)size.x; // moves pen
        }
        Texture2D::SetPixelStore(PixelStoreParam::UNPACK_ALIGNMENT, 4);
    }

    const Glyph& Font::GetGlyphRect(char c) const {
        return glyphs[c - 32];
    }

    float Font::CalcTextWidth(Str text) const {
        float width = 0;
        for (const char c : text) {
            width += GetGlyphRect(c).advance.x;
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
