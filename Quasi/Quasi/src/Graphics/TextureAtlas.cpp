#include "TextureAtlas.h"
#include "Utils/Algorithm.h"
#include "Utils/Iter/MapIter.h"

namespace Quasi::Graphics {
    TextureAtlas::TextureAtlas(Span<ImageView> sprites, bool pixelated, int padding) {
        sprites.SortByKey([] (const ImageView& sprite) { return sprite.height; });
        PackSprites(sprites, pixelated, padding);
    }

    TextureAtlas::TextureAtlas(Span<ImageView> sprites, Span<const Str> spriteNames, bool pixelated, int padding) {
        Vec<u32> indices = Vecs::Range<u32>(0, sprites.Length());
        indices.SortByKey([&] (u32 i) { return sprites[i].height; });
        Algorithm::ApplyRevPermutationInPlace(sprites.AsSpan(), indices.AsSpan());

        spriteLookup.Reserve(spriteNames.Length());
        for (usize i = 0; i < spriteNames.Length(); ++i) {
            spriteLookup.Insert(spriteNames[indices[i]], i);
        }

        PackSprites(sprites, pixelated, padding);
    }

    void TextureAtlas::PackSprites(Span<ImageView> sprites, bool pixelated, int padding) {
        // https://www.david-colson.com/2020/03/10/exploring-rect-packing.html
        // we're rect packing now; using the simplest solution: naive row packing

        // getting the max width for a singular image and multiplying by sqrt(n)
        // should be good enough of an approximation.
        int minWidth = 0;
        usize area = 0;
        for (const auto& img : sprites) {
            minWidth = std::max(minWidth, img.width);
            area += img.width * img.height;
        }
        const int width = std::max((int)std::sqrt(area), minWidth);

        Math::iv2 pen;
        // proceed to fit the next sprites, making sure to not exceed the first row
        for (usize i = 0; i < sprites.Length(); ++i) {
            // pen.x = 0;
            if (pen.x + sprites[i].width > width) {
                pen.x = 0;
                // heights are sorted in order, so we can safely add the previous
                pen.y += sprites[i - 1].height + padding;
            }
            spritesheet.Push(Math::iRect2D::FromSize(pen, sprites[i].Size()));
            pen.x += sprites[i].width + padding;
        }
        pen.y += sprites.Last().height;

        Image atlas = Image::New(width, pen.y);

        for (usize i = 0; i < sprites.Length(); ++i) {
            atlas.BlitImage(spritesheet[i].min, sprites[i]);
        }

        // atlas.ExportPNG("debug.png");
        fullTexture = Texture2D::New(atlas, { .pixelated = pixelated });
    }

    TextureAtlas TextureAtlas::FromFiles(Span<const CStr> files, Span<const Str> spriteNames, bool pixelated, int padding) {
        Vec<Image> sprites = Vec<Image>::WithCap(files.Length());
        Vec<ImageView> spriteViews = Vec<ImageView>::WithCap(files.Length());
        for (usize i = 0; i < files.Length(); ++i) {
            sprites.Push(Image::LoadPNG(files[i]));
            spriteViews.Push(sprites[i].AsView());
        }
        return { spriteViews, spriteNames, pixelated, padding };
    }

    Math::iRect2D TextureAtlas::GetPx(Str name) const {
        const Option<u32> id = spriteLookup.Get(name).Copied();
        if (!id) return Math::iRect2D::Empty();
        return GetPx(*id);
    }

    Math::iRect2D TextureAtlas::GetPx(u32 id) const {
        return spritesheet[id];
    }

    Math::fRect2D TextureAtlas::GetUV(Str name) const {
        return fullTexture.Px2UV(GetPx(name));
    }

    Math::fRect2D TextureAtlas::GetUV(u32 id) const {
        return fullTexture.Px2UV(GetPx(id));
    }
}
