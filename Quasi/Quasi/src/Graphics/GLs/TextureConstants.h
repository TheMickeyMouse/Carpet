#pragma once

namespace Quasi::Graphics {
    // * from glew.h or https://javagl.github.io/GLConstantsTranslator/GLConstantsTranslator.html
    enum class TextureFormat {
        RED = 0x1903,
        RED_GREEN = 0x8227,
        RGB = 0x1907,
        RGB_REVERSE = 0x80E0,
        BGR = RGB_REVERSE,
        RGBA = 0x1908,
        RGBA_REVERSE = 0x80E1,
        BGRA = RGBA_REVERSE,

        DEPTH = 0x1902,
    };

    enum class TextureIFormat {
        RGBA_8  = 0x8058, RGBA_8I  = 0x8D8E, RGBA_8UI  = 0x8D7C,
        RGBA_16 = 0x805B, RGBA_16I = 0x8D88, RGBA_16UI = 0x8D76, RGBA_16F  = 0x881A,
                          RGBA_32I = 0x8D82, RGBA_32UI = 0x8D70, RGBA_32F  = 0x8814,

        RGB_8   = 0x8051, RGB_8I   = 0x8D8F, RGB_8UI   = 0x8D7D,
        RGB_16  = 0x8054, RGB_16I  = 0x8D89, RGB_16UI  = 0x8D77, RGB_16F   = 0x881B,
                          RGB_32I  = 0x8D83, RGB_32UI  = 0x8D71, RGB_32F   = 0x8815,

        R_8     = 0x8229, R_8I     = 0x8231, R_8UI     = 0x8232,
        R_16    = 0x822A, R_16I    = 0x8233, R_16UI    = 0x8234, R_16F     = 0x822D,
                          R_32I    = 0x8235, R_32UI    = 0x8236, R_32F     = 0x822E,

        RG_8    = 0x822B, RG_8I    = 0x8237, RG_8UI    = 0x8238,
        RG_16   = 0x822C, RG_16I   = 0x8239, RG_16UI   = 0x823A, RG_16F    = 0x822F,
                          RG_32I   = 0x823B, RG_32UI   = 0x823C, RG_32F    = 0x8230,

        R8_SNORM  = 0x8F94, RG8_SNORM  = 0x8F95, RGB8_SNORM  = 0x8F96, RGBA8_SNORM  = 0x8F97,
        R16_SNORM = 0x8F98, RG16_SNORM = 0x8F99, RGB16_SNORM = 0x8F9A, RGBA16_SNORM = 0x8F9B,

        SRGB_8 = 0x8C41, SRGBA_8 = 0x8C43,

        RGBA_10_2 = 0x8059, RGBA_10_2UI = 0x906F,
        RGB_11_11_10F = 0x8C3A,
        RGB_9E5 = 0x8C3D,

        RGTC_COMPRESSED_RED = 0x8DBB, RGTC_COMPRESSED_SIGNED_RED = 0x8DBC,
        RGTC_COMPRESSED_RG  = 0x8DBD, RGTC_COMPRESSED_SIGNED_RG  = 0x8DBE,

        DEPTH_32F = 0x8CAC, DEPTH_32 = 0x81A7, DEPTH_24 = 0x81A6, DEPTH_16 = 0x81A5, DEPTH = 0x1902,
        DEPTH_32F_STENCIL_8 = 0x8CAD,          DEPTH_24_STENCIL_8 = 0x88F0
    };

    enum class TextureTarget : int {
        _1D      = 0xDE0,
        ARRAY_1D = 0x8C18,

        _2D      = 0x0DE1,
        ARRAY_2D = 0x8C1A,
        // TEXTURE_2D_MULTISAMPLE       = 0x9100,
        // TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9102,

        _3D = 0x806F,

        // TEXTURE_RECTANGLE = 0x84F5,

        CUBEMAP       = 0x8513,
        CUBEMAP_POS_X = 0x8515, CUBEMAP_RIGHT = CUBEMAP_POS_X,
        CUBEMAP_NEG_X = 0x8516, CUBEMAP_LEFT  = CUBEMAP_NEG_X,
        CUBEMAP_POS_Y = 0x8517, CUBEMAP_UP    = CUBEMAP_POS_Y,
        CUBEMAP_NEG_Y = 0x8518, CUBEMAP_DOWN  = CUBEMAP_NEG_Y,
        CUBEMAP_POS_Z = 0x8519, CUBEMAP_FRONT = CUBEMAP_POS_Z,
        CUBEMAP_NEG_Z = 0x851A, CUBEMAP_BACK  = CUBEMAP_NEG_Z,

        NONE = 0,
    };

    enum class TextureSample {
        NEAREST = 0x2600,
        LINEAR  = 0x2601,

        NEAREST_NEAREST_MIP = 0x2700,
        LINEAR_NEAREST_MIP,
        NEAREST_LINEAR_MIP,
        LINEAR_LINEAR_MIP,
    };

    enum class TextureParamName {
        BASE_LEVEL = 0x813C,
        BORDER_COLOR = 0x1004,
        COMPARE_FUNC = 0x884D,
        COMPARE_MODE = 0x884C,
        LOD_BIAS = 0x8501,
        MIN_FILTER = 0x2801,
        MAG_FILTER = 0x2800,
        MIN_LOD = 0x813A,
        MAX_LOD = 0x813B,
        MAX_LEVEL = 0x813D,
        SWIZZLE_R = 0x8E42,
        SWIZZLE_G = 0x8E43,
        SWIZZLE_B = 0x8E44,
        SWIZZLE_A = 0x8E45,
        SWIZZLE_RGBA = 0x8E46,
        WRAP_S = 0x2802,
        WRAP_T = 0x2803,
        WRAP_R = 0x8072,

        // custom parts
        XT_SAMPLE_FILTER = 0x10000,
        XT_WRAPPING      = 0x10001,
    };

    enum class TextureBorder {
        CLAMP_TO_EDGE = 0x812F,
        CLAMP_TO_BORDER = 0x812D,
        MIRRORED_REPEAT = 0x8370,
        REPEAT = 0x2901
    };

    enum class PixelStoreParam {
        PACK_SWAP_BYTES   = 0x0D00,
        PACK_LSB_FIRST    = 0x0D01,
        PACK_ROW_LENGTH   = 0x0D02,
        PACK_SKIP_ROWS    = 0x0D03,
        PACK_SKIP_PIXELS  = 0x0D04,
        PACK_ALIGNMENT    = 0x0D05,
        PACK_SKIP_IMAGES  = 0x806B,
        PACK_IMAGE_HEIGHT = 0x806C,

        UNPACK_SWAP_BYTES   = 0x0CF0,
        UNPACK_LSB_FIRST    = 0x0CF1,
        UNPACK_ROW_LENGTH   = 0x0CF2,
        UNPACK_SKIP_ROWS    = 0x0CF3,
        UNPACK_SKIP_PIXELS  = 0x0CF4,
        UNPACK_ALIGNMENT    = 0x0CF5,
        UNPACK_SKIP_IMAGES  = 0x806D,
        UNPACK_IMAGE_HEIGHT = 0x806E,
    };

    constexpr TextureSample MipTexFilter(TextureSample col, TextureSample mip) {
        return (TextureSample)(0x2700 + (int)col - 0x2600 + ((int)mip - 0x2600) * 2);
    }
}
