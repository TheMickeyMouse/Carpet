#pragma once
#include "El.h"

namespace Carpet {
    class WidgetEl : public El {
    public:
        ~WidgetEl() override = default;
        void Draw(Canvas& canvas) override;
        void DrawGlass(GlassRenderer& glass) override;

        using Self = WidgetEl;
        static const ElMeta META;
        const ElMeta& GetMeta() const override { return META; }
    };
}
