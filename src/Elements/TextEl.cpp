#include "TextEl.h"

#include "GUI/Canvas.h"

namespace Carpet {
    void TextEl::Draw(Canvas& canvas) {
        El::Draw(canvas);
        canvas.Stroke(color);
        const fv2 pos = computedPosition + computedLayout.padding.TopLeft(), size = computedLayout.InnerSize();

        canvas.DrawText(text, fontSize, pos, {
            alignment, size
        });

        canvas.StrokeWeight(1);
        canvas.NoFill();
        canvas.DrawRect(fRect2D::FromSize(pos, size));
    }

    const ElMeta TextEl::META = [] {
        ElMeta meta = ElMeta::NewClass<TextEl, El>("Text", &META);
        meta.AddField("text",     META_FSET(text));
        meta.AddField("color",    META_FSET(color));
        meta.AddField("fontSize", META_FSET(fontSize));
        meta.AddField("textAlign", META_FSET(alignment));
        return meta;
    } ();
} // Carpet