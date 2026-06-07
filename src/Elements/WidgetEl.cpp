#include "WidgetEl.h"

#include "../GlassRenderer.h"

namespace Carpet {
    void WidgetEl::Draw(Canvas& canvas) {}

    void WidgetEl::DrawGlass(GlassRenderer& glass) {
        El::DrawGlass(glass);
        glass.DrawBox(fRect2D::FromSize(computedPosition, computedLayout.Size()), borderRadius);
    }

    const ElMeta WidgetEl::META = [] {
        ElMeta meta = ElMeta::NewClass<WidgetEl, El>("Widget", &META);
        return meta;
    } ();
}