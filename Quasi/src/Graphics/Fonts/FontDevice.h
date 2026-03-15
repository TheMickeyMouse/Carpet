#pragma once

#include "Utils/Ref.h"
#include "Utils/Type.h"

struct FT_LibraryRec_;

namespace Quasi::Graphics {
    class Font;

    class FontDevice {
        FT_LibraryRec_* libHandle = nullptr;
        u32 dpi = 96; // default value
    public:
        FontDevice();
        ~FontDevice();

        FontDevice(const FontDevice&) = delete;
        FontDevice& operator=(const FontDevice&) = delete;
        static void Transfer(FontDevice& dest, FontDevice&& from);
        FontDevice(FontDevice&& fd) noexcept { Transfer(*this, std::move(fd)); }
        FontDevice& operator=(FontDevice&& fd) noexcept { Transfer(*this, std::move(fd)); return *this; }

        void SetDPI(uint newDpi) { dpi = newDpi; }
        
        static OptRef<FontDevice> Instance;
        static FT_LibraryRec_* Library();
        static u32 DPI();

        friend Font;
    };
}
