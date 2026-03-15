#pragma once
#include "Image.h"
#include "GLs/Texture.h"

namespace Quasi::Graphics {
    struct SubTexture {
        OptRef<const Texture2D> tex = nullptr;
        Math::fRect2D rect;
    };

    class TextureAtlas {
        Texture2D fullTexture;
        Vec<Math::iRect2D> spritesheet;
        HashMap<String, u32> spriteLookup;
    public:
        TextureAtlas() = default;
        TextureAtlas(Span<ImageView> sprites, bool pixelated = false, int padding = 1);
        TextureAtlas(Span<ImageView> sprites, Span<const Str> spriteNames, bool pixelated = false, int padding = 1);
    private:
        void PackSprites(Span<ImageView> sprites, bool pixelated, int padding);
    public:
        static TextureAtlas FromFiles(Span<const CStr> files, Span<const Str> spriteNames, bool pixelated = false, int padding = 1);

        Texture2D& GetTexture() { return fullTexture; }
        const Texture2D& GetTexture() const { return fullTexture; }

        Math::iRect2D GetPx(Str name) const;
        Math::iRect2D GetPx(u32 id)   const;
        Math::fRect2D GetUV(Str name) const;
        Math::fRect2D GetUV(u32 id)   const;

        SubTexture operator[](Str name) const { return { fullTexture, GetUV(name) }; }
        SubTexture operator[](u32 id)   const { return { fullTexture, GetUV(id) }; }
    };
}
