#pragma once
#include "El.h"
#include "Fonts/TextAlign.h"

namespace Carpet {
    class TextEl : public El {
    public:
        String text;
        float fontSize;
        TextAlign::AlignOptions alignment = (TextAlign::AlignOptions)(TextAlign::JUSTIFY | TextAlign::WORD_WRAP);
        fColor color = { 0 };

        TextEl() = default;
        ~TextEl() override = default;
        void Draw(Canvas& canvas) override;

        using Self = TextEl;
        static const ElMeta META;
        const ElMeta& GetMeta() const override { return META; }
    };
} // Carpet