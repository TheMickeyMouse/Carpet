#pragma once

#include <GL/glew.h>

namespace GL {
    using Int      = GLint;
    using Int64    = GLint64;
    using Uint     = GLuint;
    using Uint64   = GLuint64;
    using Short    = GLshort;
    using Ushort   = GLushort;
    using Enum     = GLenum;
    using Isize    = GLsizei;
    using Fixed    = GLfixed;
    using IntPtr   = GLintptr;
    using IsizePtr = GLsizeiptr;
    using Float    = GLfloat;
    using FClamp   = GLclampf;
    using Double   = GLdouble;
    using DClamp   = GLclampd;
    using IClamp   = GLint;
    using Byte     = GLbyte;
    using Ubyte    = GLubyte;
    using Bitfield = GLbitfield; 
    using Bool     = GLboolean;

    using Handle       = GLhandleARB;
    using ClientBuffer = void*;
    using Sync         = GLsync;
    using CLContext    = struct _cl_context*;
    using CLEvent      = struct _cl_event*;
    using VulkanProc   = void (*)();
    using LogFuncREGAL = void (*)(Enum stream, Isize length, const char* message, void* context);
    using LogFuncAMD   = void (*)(Uint id, Enum category, Enum severity, Isize length, const char* message, void* userParam);
    using LogFunc      = void (*)(Enum source, Enum type, Uint id, Enum severity, Isize length, const char* message, const void* userParam);

#pragma region GL Constants
    enum {
        LOGIC_OP                                                              = 0xBF1,
        TEXTURE_COMPONENTS                                                    = 0x1003,
        POINTS                                                                = 0x0,
        CURRENT_BIT                                                           = 0x1,
        CLIENT_PIXEL_STORE_BIT                                                = 0x1,
        LINES                                                                 = 0x1,
        LINE_LOOP                                                             = 0x2,
        POINT_BIT                                                             = 0x2,
        CLIENT_VERTEX_ARRAY_BIT                                               = 0x2,
        LINE_STRIP                                                            = 0x3,
        LINE_BIT                                                              = 0x4,
        TRIANGLES                                                             = 0x4,
        TRIANGLE_STRIP                                                        = 0x5,
        TRIANGLE_FAN                                                          = 0x6,
        QUADS                                                                 = 0x7,
        QUAD_STRIP                                                            = 0x8,
        POLYGON_BIT                                                           = 0x8,
        POLYGON                                                               = 0x9,
        POLYGON_STIPPLE_BIT                                                   = 0x10,
        PIXEL_MODE_BIT                                                        = 0x20,
        LIGHTING_BIT                                                          = 0x40,
        FOG_BIT                                                               = 0x80,
        DEPTH_BUFFER_BIT                                                      = 0x100,
        ACCUM                                                                 = 0x100,
        LOAD                                                                  = 0x101,
        RETURN                                                                = 0x102,
        MULT                                                                  = 0x103,
        ADD                                                                   = 0x104,
        NEVER                                                                 = 0x200,
        ACCUM_BUFFER_BIT                                                      = 0x200,
        LESS                                                                  = 0x201,
        EQUAL                                                                 = 0x202,
        LEQUAL                                                                = 0x203,
        GREATER                                                               = 0x204,
        NOTEQUAL                                                              = 0x205,
        GEQUAL                                                                = 0x206,
        ALWAYS                                                                = 0x207,
        SRC_COLOR                                                             = 0x300,
        ONE_MINUS_SRC_COLOR                                                   = 0x301,
        SRC_ALPHA                                                             = 0x302,
        ONE_MINUS_SRC_ALPHA                                                   = 0x303,
        DST_ALPHA                                                             = 0x304,
        ONE_MINUS_DST_ALPHA                                                   = 0x305,
        DST_COLOR                                                             = 0x306,
        ONE_MINUS_DST_COLOR                                                   = 0x307,
        SRC_ALPHA_SATURATE                                                    = 0x308,
        STENCIL_BUFFER_BIT                                                    = 0x400,
        FRONT_LEFT                                                            = 0x400,
        FRONT_RIGHT                                                           = 0x401,
        BACK_LEFT                                                             = 0x402,
        BACK_RIGHT                                                            = 0x403,
        FRONT                                                                 = 0x404,
        BACK                                                                  = 0x405,
        LEFT                                                                  = 0x406,
        RIGHT                                                                 = 0x407,
        FRONT_AND_BACK                                                        = 0x408,
        AUX0                                                                  = 0x409,
        AUX1                                                                  = 0x40A,
        AUX2                                                                  = 0x40B,
        AUX3                                                                  = 0x40C,
        INVALID_ENUM                                                          = 0x500,
        INVALID_VALUE                                                         = 0x501,
        INVALID_OPERATION                                                     = 0x502,
        STACK_OVERFLOW                                                        = 0x503,
        STACK_UNDERFLOW                                                       = 0x504,
        OUT_OF_MEMORY                                                         = 0x505,
        N2D                                                                   = 0x600,
        N3D                                                                   = 0x601,
        N3D_COLOR                                                             = 0x602,
        N3D_COLOR_TEXTURE                                                     = 0x603,
        N4D_COLOR_TEXTURE                                                     = 0x604,
        PASS_THROUGH_TOKEN                                                    = 0x700,
        POINT_TOKEN                                                           = 0x701,
        LINE_TOKEN                                                            = 0x702,
        POLYGON_TOKEN                                                         = 0x703,
        BITMAP_TOKEN                                                          = 0x704,
        DRAW_PIXEL_TOKEN                                                      = 0x705,
        COPY_PIXEL_TOKEN                                                      = 0x706,
        LINE_RESET_TOKEN                                                      = 0x707,
        EXP                                                                   = 0x800,
        VIEWPORT_BIT                                                          = 0x800,
        EXP2                                                                  = 0x801,
        CW                                                                    = 0x900,
        CCW                                                                   = 0x901,
        COEFF                                                                 = 0xA00,
        ORDER                                                                 = 0xA01,
        NDOMAIN                                                               = 0xA02,
        CURRENT_COLOR                                                         = 0xB00,
        CURRENT_INDEX                                                         = 0xB01,
        CURRENT_NORMAL                                                        = 0xB02,
        CURRENT_TEXTURE_COORDS                                                = 0xB03,
        CURRENT_RASTER_COLOR                                                  = 0xB04,
        CURRENT_RASTER_INDEX                                                  = 0xB05,
        CURRENT_RASTER_TEXTURE_COORDS                                         = 0xB06,
        CURRENT_RASTER_POSITION                                               = 0xB07,
        CURRENT_RASTER_POSITION_VALID                                         = 0xB08,
        CURRENT_RASTER_DISTANCE                                               = 0xB09,
        POINT_SMOOTH                                                          = 0xB10,
        POINT_SIZE                                                            = 0xB11,
        POINT_SIZE_RANGE                                                      = 0xB12,
        POINT_SIZE_GRANULARITY                                                = 0xB13,
        LINE_SMOOTH                                                           = 0xB20,
        LINE_WIDTH                                                            = 0xB21,
        LINE_WIDTH_RANGE                                                      = 0xB22,
        LINE_WIDTH_GRANULARITY                                                = 0xB23,
        LINE_STIPPLE                                                          = 0xB24,
        LINE_STIPPLE_PATTERN                                                  = 0xB25,
        LINE_STIPPLE_REPEAT                                                   = 0xB26,
        LIST_MODE                                                             = 0xB30,
        MAX_LIST_NESTING                                                      = 0xB31,
        LIST_BASE                                                             = 0xB32,
        LIST_INDEX                                                            = 0xB33,
        POLYGON_MODE                                                          = 0xB40,
        POLYGON_SMOOTH                                                        = 0xB41,
        POLYGON_STIPPLE                                                       = 0xB42,
        EDGE_FLAG                                                             = 0xB43,
        CULL_FACE                                                             = 0xB44,
        CULL_FACE_MODE                                                        = 0xB45,
        FRONT_FACE                                                            = 0xB46,
        LIGHTING                                                              = 0xB50,
        LIGHT_MODEL_LOCAL_VIEWER                                              = 0xB51,
        LIGHT_MODEL_TWO_SIDE                                                  = 0xB52,
        LIGHT_MODEL_AMBIENT                                                   = 0xB53,
        SHADE_MODEL                                                           = 0xB54,
        COLOR_MATERIAL_FACE                                                   = 0xB55,
        COLOR_MATERIAL_PARAMETER                                              = 0xB56,
        COLOR_MATERIAL                                                        = 0xB57,
        FOG                                                                   = 0xB60,
        FOG_INDEX                                                             = 0xB61,
        FOG_DENSITY                                                           = 0xB62,
        FOG_START                                                             = 0xB63,
        FOG_END                                                               = 0xB64,
        FOG_MODE                                                              = 0xB65,
        FOG_COLOR                                                             = 0xB66,
        DEPTH_RANGE                                                           = 0xB70,
        DEPTH_TEST                                                            = 0xB71,
        DEPTH_WRITEMASK                                                       = 0xB72,
        DEPTH_CLEAR_VALUE                                                     = 0xB73,
        DEPTH_FUNC                                                            = 0xB74,
        ACCUM_CLEAR_VALUE                                                     = 0xB80,
        STENCIL_TEST                                                          = 0xB90,
        STENCIL_CLEAR_VALUE                                                   = 0xB91,
        STENCIL_FUNC                                                          = 0xB92,
        STENCIL_VALUE_MASK                                                    = 0xB93,
        STENCIL_FAIL                                                          = 0xB94,
        STENCIL_PASS_DEPTH_FAIL                                               = 0xB95,
        STENCIL_PASS_DEPTH_PASS                                               = 0xB96,
        STENCIL_REF                                                           = 0xB97,
        STENCIL_WRITEMASK                                                     = 0xB98,
        MATRIX_MODE                                                           = 0xBA0,
        NORMALIZE                                                             = 0xBA1,
        VIEWPORT                                                              = 0xBA2,
        MODELVIEW_STACK_DEPTH                                                 = 0xBA3,
        PROJECTION_STACK_DEPTH                                                = 0xBA4,
        TEXTURE_STACK_DEPTH                                                   = 0xBA5,
        MODELVIEW_MATRIX                                                      = 0xBA6,
        PROJECTION_MATRIX                                                     = 0xBA7,
        TEXTURE_MATRIX                                                        = 0xBA8,
        ATTRIB_STACK_DEPTH                                                    = 0xBB0,
        CLIENT_ATTRIB_STACK_DEPTH                                             = 0xBB1,
        ALPHA_TEST                                                            = 0xBC0,
        ALPHA_TEST_FUNC                                                       = 0xBC1,
        ALPHA_TEST_REF                                                        = 0xBC2,
        DITHER                                                                = 0xBD0,
        BLEND_DST                                                             = 0xBE0,
        BLEND_SRC                                                             = 0xBE1,
        BLEND                                                                 = 0xBE2,
        LOGIC_OP_MODE                                                         = 0xBF0,
        INDEX_LOGIC_OP                                                        = 0xBF1,
        COLOR_LOGIC_OP                                                        = 0xBF2,
        AUX_BUFFERS                                                           = 0xC00,
        DRAW_BUFFER                                                           = 0xC01,
        READ_BUFFER                                                           = 0xC02,
        SCISSOR_BOX                                                           = 0xC10,
        SCISSOR_TEST                                                          = 0xC11,
        INDEX_CLEAR_VALUE                                                     = 0xC20,
        INDEX_WRITEMASK                                                       = 0xC21,
        COLOR_CLEAR_VALUE                                                     = 0xC22,
        COLOR_WRITEMASK                                                       = 0xC23,
        INDEX_MODE                                                            = 0xC30,
        RGBA_MODE                                                             = 0xC31,
        DOUBLEBUFFER                                                          = 0xC32,
        STEREO                                                                = 0xC33,
        RENDER_MODE                                                           = 0xC40,
        PERSPECTIVE_CORRECTION_HINT                                           = 0xC50,
        POINT_SMOOTH_HINT                                                     = 0xC51,
        LINE_SMOOTH_HINT                                                      = 0xC52,
        POLYGON_SMOOTH_HINT                                                   = 0xC53,
        FOG_HINT                                                              = 0xC54,
        TEXTURE_GEN_S                                                         = 0xC60,
        TEXTURE_GEN_T                                                         = 0xC61,
        TEXTURE_GEN_R                                                         = 0xC62,
        TEXTURE_GEN_Q                                                         = 0xC63,
        PIXEL_MAP_I_TO_I                                                      = 0xC70,
        PIXEL_MAP_S_TO_S                                                      = 0xC71,
        PIXEL_MAP_I_TO_R                                                      = 0xC72,
        PIXEL_MAP_I_TO_G                                                      = 0xC73,
        PIXEL_MAP_I_TO_B                                                      = 0xC74,
        PIXEL_MAP_I_TO_A                                                      = 0xC75,
        PIXEL_MAP_R_TO_R                                                      = 0xC76,
        PIXEL_MAP_G_TO_G                                                      = 0xC77,
        PIXEL_MAP_B_TO_B                                                      = 0xC78,
        PIXEL_MAP_A_TO_A                                                      = 0xC79,
        PIXEL_MAP_I_TO_I_SIZE                                                 = 0xCB0,
        PIXEL_MAP_S_TO_S_SIZE                                                 = 0xCB1,
        PIXEL_MAP_I_TO_R_SIZE                                                 = 0xCB2,
        PIXEL_MAP_I_TO_G_SIZE                                                 = 0xCB3,
        PIXEL_MAP_I_TO_B_SIZE                                                 = 0xCB4,
        PIXEL_MAP_I_TO_A_SIZE                                                 = 0xCB5,
        PIXEL_MAP_R_TO_R_SIZE                                                 = 0xCB6,
        PIXEL_MAP_G_TO_G_SIZE                                                 = 0xCB7,
        PIXEL_MAP_B_TO_B_SIZE                                                 = 0xCB8,
        PIXEL_MAP_A_TO_A_SIZE                                                 = 0xCB9,
        UNPACK_SWAP_BYTES                                                     = 0xCF0,
        UNPACK_LSB_FIRST                                                      = 0xCF1,
        UNPACK_ROW_LENGTH                                                     = 0xCF2,
        UNPACK_SKIP_ROWS                                                      = 0xCF3,
        UNPACK_SKIP_PIXELS                                                    = 0xCF4,
        UNPACK_ALIGNMENT                                                      = 0xCF5,
        PACK_SWAP_BYTES                                                       = 0xD00,
        PACK_LSB_FIRST                                                        = 0xD01,
        PACK_ROW_LENGTH                                                       = 0xD02,
        PACK_SKIP_ROWS                                                        = 0xD03,
        PACK_SKIP_PIXELS                                                      = 0xD04,
        PACK_ALIGNMENT                                                        = 0xD05,
        MAP_COLOR                                                             = 0xD10,
        MAP_STENCIL                                                           = 0xD11,
        INDEX_SHIFT                                                           = 0xD12,
        INDEX_OFFSET                                                          = 0xD13,
        RED_SCALE                                                             = 0xD14,
        RED_BIAS                                                              = 0xD15,
        ZOOM_X                                                                = 0xD16,
        ZOOM_Y                                                                = 0xD17,
        GREEN_SCALE                                                           = 0xD18,
        GREEN_BIAS                                                            = 0xD19,
        BLUE_SCALE                                                            = 0xD1A,
        BLUE_BIAS                                                             = 0xD1B,
        ALPHA_SCALE                                                           = 0xD1C,
        ALPHA_BIAS                                                            = 0xD1D,
        DEPTH_SCALE                                                           = 0xD1E,
        DEPTH_BIAS                                                            = 0xD1F,
        MAX_EVAL_ORDER                                                        = 0xD30,
        MAX_LIGHTS                                                            = 0xD31,
        MAX_CLIP_PLANES                                                       = 0xD32,
        MAX_TEXTURE_SIZE                                                      = 0xD33,
        MAX_PIXEL_MAP_TABLE                                                   = 0xD34,
        MAX_ATTRIB_STACK_DEPTH                                                = 0xD35,
        MAX_MODELVIEW_STACK_DEPTH                                             = 0xD36,
        MAX_NAME_STACK_DEPTH                                                  = 0xD37,
        MAX_PROJECTION_STACK_DEPTH                                            = 0xD38,
        MAX_TEXTURE_STACK_DEPTH                                               = 0xD39,
        MAX_VIEWPORT_DIMS                                                     = 0xD3A,
        MAX_CLIENT_ATTRIB_STACK_DEPTH                                         = 0xD3B,
        SUBPIXEL_BITS                                                         = 0xD50,
        INDEX_BITS                                                            = 0xD51,
        RED_BITS                                                              = 0xD52,
        GREEN_BITS                                                            = 0xD53,
        BLUE_BITS                                                             = 0xD54,
        ALPHA_BITS                                                            = 0xD55,
        DEPTH_BITS                                                            = 0xD56,
        STENCIL_BITS                                                          = 0xD57,
        ACCUM_RED_BITS                                                        = 0xD58,
        ACCUM_GREEN_BITS                                                      = 0xD59,
        ACCUM_BLUE_BITS                                                       = 0xD5A,
        ACCUM_ALPHA_BITS                                                      = 0xD5B,
        NAME_STACK_DEPTH                                                      = 0xD70,
        AUTO_NORMAL                                                           = 0xD80,
        MAP1_COLOR_4                                                          = 0xD90,
        MAP1_INDEX                                                            = 0xD91,
        MAP1_NORMAL                                                           = 0xD92,
        MAP1_TEXTURE_COORD_1                                                  = 0xD93,
        MAP1_TEXTURE_COORD_2                                                  = 0xD94,
        MAP1_TEXTURE_COORD_3                                                  = 0xD95,
        MAP1_TEXTURE_COORD_4                                                  = 0xD96,
        MAP1_VERTEX_3                                                         = 0xD97,
        MAP1_VERTEX_4                                                         = 0xD98,
        MAP2_COLOR_4                                                          = 0xDB0,
        MAP2_INDEX                                                            = 0xDB1,
        MAP2_NORMAL                                                           = 0xDB2,
        MAP2_TEXTURE_COORD_1                                                  = 0xDB3,
        MAP2_TEXTURE_COORD_2                                                  = 0xDB4,
        MAP2_TEXTURE_COORD_3                                                  = 0xDB5,
        MAP2_TEXTURE_COORD_4                                                  = 0xDB6,
        MAP2_VERTEX_3                                                         = 0xDB7,
        MAP2_VERTEX_4                                                         = 0xDB8,
        MAP1_GRID_DOMAIN                                                      = 0xDD0,
        MAP1_GRID_SEGMENTS                                                    = 0xDD1,
        MAP2_GRID_DOMAIN                                                      = 0xDD2,
        MAP2_GRID_SEGMENTS                                                    = 0xDD3,
        TEXTURE_1D                                                            = 0xDE0,
        TEXTURE_2D                                                            = 0xDE1,
        FEEDBACK_BUFFER_POINTER                                               = 0xDF0,
        FEEDBACK_BUFFER_SIZE                                                  = 0xDF1,
        FEEDBACK_BUFFER_TYPE                                                  = 0xDF2,
        SELECTION_BUFFER_POINTER                                              = 0xDF3,
        SELECTION_BUFFER_SIZE                                                 = 0xDF4,
        TEXTURE_WIDTH                                                         = 0x1000,
        TRANSFORM_BIT                                                         = 0x1000,
        TEXTURE_HEIGHT                                                        = 0x1001,
        TEXTURE_INTERNAL_FORMAT                                               = 0x1003,
        TEXTURE_BORDER_COLOR                                                  = 0x1004,
        TEXTURE_BORDER                                                        = 0x1005,
        DONT_CARE                                                             = 0x1100,
        FASTEST                                                               = 0x1101,
        NICEST                                                                = 0x1102,
        AMBIENT                                                               = 0x1200,
        DIFFUSE                                                               = 0x1201,
        SPECULAR                                                              = 0x1202,
        POSITION                                                              = 0x1203,
        SPOT_DIRECTION                                                        = 0x1204,
        SPOT_EXPONENT                                                         = 0x1205,
        SPOT_CUTOFF                                                           = 0x1206,
        CONSTANT_ATTENUATION                                                  = 0x1207,
        LINEAR_ATTENUATION                                                    = 0x1208,
        QUADRATIC_ATTENUATION                                                 = 0x1209,
        COMPILE                                                               = 0x1300,
        COMPILE_AND_EXECUTE                                                   = 0x1301,
        BYTE                                                                  = 0x1400,
        UNSIGNED_BYTE                                                         = 0x1401,
        SHORT                                                                 = 0x1402,
        UNSIGNED_SHORT                                                        = 0x1403,
        INT                                                                   = 0x1404,
        UNSIGNED_INT                                                          = 0x1405,
        FLOAT                                                                 = 0x1406,
        N2_BYTES                                                              = 0x1407,
        N3_BYTES                                                              = 0x1408,
        N4_BYTES                                                              = 0x1409,
        DOUBLE                                                                = 0x140A,
        CLEAR                                                                 = 0x1500,
        AND                                                                   = 0x1501,
        AND_REVERSE                                                           = 0x1502,
        COPY                                                                  = 0x1503,
        AND_INVERTED                                                          = 0x1504,
        NOOP                                                                  = 0x1505,
        XOR                                                                   = 0x1506,
        OR                                                                    = 0x1507,
        NOR                                                                   = 0x1508,
        EQUIV                                                                 = 0x1509,
        INVERT                                                                = 0x150A,
        OR_REVERSE                                                            = 0x150B,
        COPY_INVERTED                                                         = 0x150C,
        OR_INVERTED                                                           = 0x150D,
        NAND                                                                  = 0x150E,
        SET                                                                   = 0x150F,
        EMISSION                                                              = 0x1600,
        SHININESS                                                             = 0x1601,
        AMBIENT_AND_DIFFUSE                                                   = 0x1602,
        COLOR_INDEXES                                                         = 0x1603,
        MODELVIEW                                                             = 0x1700,
        PROJECTION                                                            = 0x1701,
        TEXTURE                                                               = 0x1702,
        COLOR                                                                 = 0x1800,
        DEPTH                                                                 = 0x1801,
        STENCIL                                                               = 0x1802,
        COLOR_INDEX                                                           = 0x1900,
        STENCIL_INDEX                                                         = 0x1901,
        DEPTH_COMPONENT                                                       = 0x1902,
        RED                                                                   = 0x1903,
        GREEN                                                                 = 0x1904,
        BLUE                                                                  = 0x1905,
        ALPHA                                                                 = 0x1906,
        RGB                                                                   = 0x1907,
        RGBA                                                                  = 0x1908,
        LUMINANCE                                                             = 0x1909,
        LUMINANCE_ALPHA                                                       = 0x190A,
        BITMAP                                                                = 0x1A00,
        POINT                                                                 = 0x1B00,
        LINE                                                                  = 0x1B01,
        FILL                                                                  = 0x1B02,
        RENDER                                                                = 0x1C00,
        FEEDBACK                                                              = 0x1C01,
        SELECT                                                                = 0x1C02,
        FLAT                                                                  = 0x1D00,
        SMOOTH                                                                = 0x1D01,
        KEEP                                                                  = 0x1E00,
        REPLACE                                                               = 0x1E01,
        INCR                                                                  = 0x1E02,
        DECR                                                                  = 0x1E03,
        VENDOR                                                                = 0x1F00,
        RENDERER                                                              = 0x1F01,
        VERSION                                                               = 0x1F02,
        EXTENSIONS                                                            = 0x1F03,
        S                                                                     = 0x2000,
        ENABLE_BIT                                                            = 0x2000,
        T                                                                     = 0x2001,
        R                                                                     = 0x2002,
        Q                                                                     = 0x2003,
        MODULATE                                                              = 0x2100,
        DECAL                                                                 = 0x2101,
        TEXTURE_ENV_MODE                                                      = 0x2200,
        TEXTURE_ENV_COLOR                                                     = 0x2201,
        TEXTURE_ENV                                                           = 0x2300,
        EYE_LINEAR                                                            = 0x2400,
        OBJECT_LINEAR                                                         = 0x2401,
        SPHERE_MAP                                                            = 0x2402,
        TEXTURE_GEN_MODE                                                      = 0x2500,
        OBJECT_PLANE                                                          = 0x2501,
        EYE_PLANE                                                             = 0x2502,
        NEAREST                                                               = 0x2600,
        LINEAR                                                                = 0x2601,
        NEAREST_MIPMAP_NEAREST                                                = 0x2700,
        LINEAR_MIPMAP_NEAREST                                                 = 0x2701,
        NEAREST_MIPMAP_LINEAR                                                 = 0x2702,
        LINEAR_MIPMAP_LINEAR                                                  = 0x2703,
        TEXTURE_MAG_FILTER                                                    = 0x2800,
        TEXTURE_MIN_FILTER                                                    = 0x2801,
        TEXTURE_WRAP_S                                                        = 0x2802,
        TEXTURE_WRAP_T                                                        = 0x2803,
        CLAMP                                                                 = 0x2900,
        REPEAT                                                                = 0x2901,
        POLYGON_OFFSET_UNITS                                                  = 0x2A00,
        POLYGON_OFFSET_POINT                                                  = 0x2A01,
        POLYGON_OFFSET_LINE                                                   = 0x2A02,
        R3_G3_B2                                                              = 0x2A10,
        V2F                                                                   = 0x2A20,
        V3F                                                                   = 0x2A21,
        C4UB_V2F                                                              = 0x2A22,
        C4UB_V3F                                                              = 0x2A23,
        C3F_V3F                                                               = 0x2A24,
        N3F_V3F                                                               = 0x2A25,
        C4F_N3F_V3F                                                           = 0x2A26,
        T2F_V3F                                                               = 0x2A27,
        T4F_V4F                                                               = 0x2A28,
        T2F_C4UB_V3F                                                          = 0x2A29,
        T2F_C3F_V3F                                                           = 0x2A2A,
        T2F_N3F_V3F                                                           = 0x2A2B,
        T2F_C4F_N3F_V3F                                                       = 0x2A2C,
        T4F_C4F_N3F_V4F                                                       = 0x2A2D,
        CLIP_PLANE0                                                           = 0x3000,
        CLIP_PLANE1                                                           = 0x3001,
        CLIP_PLANE2                                                           = 0x3002,
        CLIP_PLANE3                                                           = 0x3003,
        CLIP_PLANE4                                                           = 0x3004,
        CLIP_PLANE5                                                           = 0x3005,
        LIGHT0                                                                = 0x4000,
        COLOR_BUFFER_BIT                                                      = 0x4000,
        LIGHT1                                                                = 0x4001,
        LIGHT2                                                                = 0x4002,
        LIGHT3                                                                = 0x4003,
        LIGHT4                                                                = 0x4004,
        LIGHT5                                                                = 0x4005,
        LIGHT6                                                                = 0x4006,
        LIGHT7                                                                = 0x4007,
        HINT_BIT                                                              = 0x8000,
        POLYGON_OFFSET_FILL                                                   = 0x8037,
        POLYGON_OFFSET_FACTOR                                                 = 0x8038,
        ALPHA4                                                                = 0x803B,
        ALPHA8                                                                = 0x803C,
        ALPHA12                                                               = 0x803D,
        ALPHA16                                                               = 0x803E,
        LUMINANCE4                                                            = 0x803F,
        LUMINANCE8                                                            = 0x8040,
        LUMINANCE12                                                           = 0x8041,
        LUMINANCE16                                                           = 0x8042,
        LUMINANCE4_ALPHA4                                                     = 0x8043,
        LUMINANCE6_ALPHA2                                                     = 0x8044,
        LUMINANCE8_ALPHA8                                                     = 0x8045,
        LUMINANCE12_ALPHA4                                                    = 0x8046,
        LUMINANCE12_ALPHA12                                                   = 0x8047,
        LUMINANCE16_ALPHA16                                                   = 0x8048,
        INTENSITY                                                             = 0x8049,
        INTENSITY4                                                            = 0x804A,
        INTENSITY8                                                            = 0x804B,
        INTENSITY12                                                           = 0x804C,
        INTENSITY16                                                           = 0x804D,
        RGB4                                                                  = 0x804F,
        RGB5                                                                  = 0x8050,
        RGB8                                                                  = 0x8051,
        RGB10                                                                 = 0x8052,
        RGB12                                                                 = 0x8053,
        RGB16                                                                 = 0x8054,
        RGBA2                                                                 = 0x8055,
        RGBA4                                                                 = 0x8056,
        RGB5_A1                                                               = 0x8057,
        RGBA8                                                                 = 0x8058,
        RGB10_A2                                                              = 0x8059,
        RGBA12                                                                = 0x805A,
        RGBA16                                                                = 0x805B,
        TEXTURE_RED_SIZE                                                      = 0x805C,
        TEXTURE_GREEN_SIZE                                                    = 0x805D,
        TEXTURE_BLUE_SIZE                                                     = 0x805E,
        TEXTURE_ALPHA_SIZE                                                    = 0x805F,
        TEXTURE_LUMINANCE_SIZE                                                = 0x8060,
        TEXTURE_INTENSITY_SIZE                                                = 0x8061,
        PROXY_TEXTURE_1D                                                      = 0x8063,
        PROXY_TEXTURE_2D                                                      = 0x8064,
        TEXTURE_PRIORITY                                                      = 0x8066,
        TEXTURE_RESIDENT                                                      = 0x8067,
        TEXTURE_BINDING_1D                                                    = 0x8068,
        TEXTURE_BINDING_2D                                                    = 0x8069,
        VERTEX_ARRAY                                                          = 0x8074,
        NORMAL_ARRAY                                                          = 0x8075,
        COLOR_ARRAY                                                           = 0x8076,
        INDEX_ARRAY                                                           = 0x8077,
        TEXTURE_COORD_ARRAY                                                   = 0x8078,
        EDGE_FLAG_ARRAY                                                       = 0x8079,
        VERTEX_ARRAY_SIZE                                                     = 0x807A,
        VERTEX_ARRAY_TYPE                                                     = 0x807B,
        VERTEX_ARRAY_STRIDE                                                   = 0x807C,
        NORMAL_ARRAY_TYPE                                                     = 0x807E,
        NORMAL_ARRAY_STRIDE                                                   = 0x807F,
        COLOR_ARRAY_SIZE                                                      = 0x8081,
        COLOR_ARRAY_TYPE                                                      = 0x8082,
        COLOR_ARRAY_STRIDE                                                    = 0x8083,
        INDEX_ARRAY_TYPE                                                      = 0x8085,
        INDEX_ARRAY_STRIDE                                                    = 0x8086,
        TEXTURE_COORD_ARRAY_SIZE                                              = 0x8088,
        TEXTURE_COORD_ARRAY_TYPE                                              = 0x8089,
        TEXTURE_COORD_ARRAY_STRIDE                                            = 0x808A,
        EDGE_FLAG_ARRAY_STRIDE                                                = 0x808C,
        VERTEX_ARRAY_POINTER                                                  = 0x808E,
        NORMAL_ARRAY_POINTER                                                  = 0x808F,
        COLOR_ARRAY_POINTER                                                   = 0x8090,
        INDEX_ARRAY_POINTER                                                   = 0x8091,
        TEXTURE_COORD_ARRAY_POINTER                                           = 0x8092,
        EDGE_FLAG_ARRAY_POINTER                                               = 0x8093,
        COLOR_INDEX1_EXT                                                      = 0x80E2,
        COLOR_INDEX2_EXT                                                      = 0x80E3,
        COLOR_INDEX4_EXT                                                      = 0x80E4,
        COLOR_INDEX8_EXT                                                      = 0x80E5,
        COLOR_INDEX12_EXT                                                     = 0x80E6,
        COLOR_INDEX16_EXT                                                     = 0x80E7,
        EVAL_BIT                                                              = 0x10000,
        LIST_BIT                                                              = 0x20000,
        TEXTURE_BIT                                                           = 0x40000,
        SCISSOR_BIT                                                           = 0x80000,
        ALL_ATTRIB_BITS                                                       = 0xFFFFF,
        CLIENT_ALL_ATTRIB_BITS                                                = 0xFFFFFFFF,
        SMOOTH_POINT_SIZE_RANGE                                               = 0xB12,
        SMOOTH_POINT_SIZE_GRANULARITY                                         = 0xB13,
        SMOOTH_LINE_WIDTH_RANGE                                               = 0xB22,
        SMOOTH_LINE_WIDTH_GRANULARITY                                         = 0xB23,
        UNSIGNED_BYTE_3_3_2                                                   = 0x8032,
        UNSIGNED_SHORT_4_4_4_4                                                = 0x8033,
        UNSIGNED_SHORT_5_5_5_1                                                = 0x8034,
        UNSIGNED_INT_8_8_8_8                                                  = 0x8035,
        UNSIGNED_INT_10_10_10_2                                               = 0x8036,
        RESCALE_NORMAL                                                        = 0x803A,
        TEXTURE_BINDING_3D                                                    = 0x806A,
        PACK_SKIP_IMAGES                                                      = 0x806B,
        PACK_IMAGE_HEIGHT                                                     = 0x806C,
        UNPACK_SKIP_IMAGES                                                    = 0x806D,
        UNPACK_IMAGE_HEIGHT                                                   = 0x806E,
        TEXTURE_3D                                                            = 0x806F,
        PROXY_TEXTURE_3D                                                      = 0x8070,
        TEXTURE_DEPTH                                                         = 0x8071,
        TEXTURE_WRAP_R                                                        = 0x8072,
        MAX_3D_TEXTURE_SIZE                                                   = 0x8073,
        BGR                                                                   = 0x80E0,
        BGRA                                                                  = 0x80E1,
        MAX_ELEMENTS_VERTICES                                                 = 0x80E8,
        MAX_ELEMENTS_INDICES                                                  = 0x80E9,
        CLAMP_TO_EDGE                                                         = 0x812F,
        TEXTURE_MIN_LOD                                                       = 0x813A,
        TEXTURE_MAX_LOD                                                       = 0x813B,
        TEXTURE_BASE_LEVEL                                                    = 0x813C,
        TEXTURE_MAX_LEVEL                                                     = 0x813D,
        LIGHT_MODEL_COLOR_CONTROL                                             = 0x81F8,
        SINGLE_COLOR                                                          = 0x81F9,
        SEPARATE_SPECULAR_COLOR                                               = 0x81FA,
        UNSIGNED_BYTE_2_3_3_REV                                               = 0x8362,
        UNSIGNED_SHORT_5_6_5                                                  = 0x8363,
        UNSIGNED_SHORT_5_6_5_REV                                              = 0x8364,
        UNSIGNED_SHORT_4_4_4_4_REV                                            = 0x8365,
        UNSIGNED_SHORT_1_5_5_5_REV                                            = 0x8366,
        UNSIGNED_INT_8_8_8_8_REV                                              = 0x8367,
        ALIASED_POINT_SIZE_RANGE                                              = 0x846D,
        ALIASED_LINE_WIDTH_RANGE                                              = 0x846E,
        MULTISAMPLE                                                           = 0x809D,
        SAMPLE_ALPHA_TO_COVERAGE                                              = 0x809E,
        SAMPLE_ALPHA_TO_ONE                                                   = 0x809F,
        SAMPLE_COVERAGE                                                       = 0x80A0,
        SAMPLE_BUFFERS                                                        = 0x80A8,
        SAMPLES                                                               = 0x80A9,
        SAMPLE_COVERAGE_VALUE                                                 = 0x80AA,
        SAMPLE_COVERAGE_INVERT                                                = 0x80AB,
        CLAMP_TO_BORDER                                                       = 0x812D,
        TEXTURE0                                                              = 0x84C0,
        TEXTURE1                                                              = 0x84C1,
        TEXTURE2                                                              = 0x84C2,
        TEXTURE3                                                              = 0x84C3,
        TEXTURE4                                                              = 0x84C4,
        TEXTURE5                                                              = 0x84C5,
        TEXTURE6                                                              = 0x84C6,
        TEXTURE7                                                              = 0x84C7,
        TEXTURE8                                                              = 0x84C8,
        TEXTURE9                                                              = 0x84C9,
        TEXTURE10                                                             = 0x84CA,
        TEXTURE11                                                             = 0x84CB,
        TEXTURE12                                                             = 0x84CC,
        TEXTURE13                                                             = 0x84CD,
        TEXTURE14                                                             = 0x84CE,
        TEXTURE15                                                             = 0x84CF,
        TEXTURE16                                                             = 0x84D0,
        TEXTURE17                                                             = 0x84D1,
        TEXTURE18                                                             = 0x84D2,
        TEXTURE19                                                             = 0x84D3,
        TEXTURE20                                                             = 0x84D4,
        TEXTURE21                                                             = 0x84D5,
        TEXTURE22                                                             = 0x84D6,
        TEXTURE23                                                             = 0x84D7,
        TEXTURE24                                                             = 0x84D8,
        TEXTURE25                                                             = 0x84D9,
        TEXTURE26                                                             = 0x84DA,
        TEXTURE27                                                             = 0x84DB,
        TEXTURE28                                                             = 0x84DC,
        TEXTURE29                                                             = 0x84DD,
        TEXTURE30                                                             = 0x84DE,
        TEXTURE31                                                             = 0x84DF,
        ACTIVE_TEXTURE                                                        = 0x84E0,
        CLIENT_ACTIVE_TEXTURE                                                 = 0x84E1,
        MAX_TEXTURE_UNITS                                                     = 0x84E2,
        TRANSPOSE_MODELVIEW_MATRIX                                            = 0x84E3,
        TRANSPOSE_PROJECTION_MATRIX                                           = 0x84E4,
        TRANSPOSE_TEXTURE_MATRIX                                              = 0x84E5,
        TRANSPOSE_COLOR_MATRIX                                                = 0x84E6,
        SUBTRACT                                                              = 0x84E7,
        COMPRESSED_ALPHA                                                      = 0x84E9,
        COMPRESSED_LUMINANCE                                                  = 0x84EA,
        COMPRESSED_LUMINANCE_ALPHA                                            = 0x84EB,
        COMPRESSED_INTENSITY                                                  = 0x84EC,
        COMPRESSED_RGB                                                        = 0x84ED,
        COMPRESSED_RGBA                                                       = 0x84EE,
        TEXTURE_COMPRESSION_HINT                                              = 0x84EF,
        NORMAL_MAP                                                            = 0x8511,
        REFLECTION_MAP                                                        = 0x8512,
        TEXTURE_CUBE_MAP                                                      = 0x8513,
        TEXTURE_BINDING_CUBE_MAP                                              = 0x8514,
        TEXTURE_CUBE_MAP_POSITIVE_X                                           = 0x8515,
        TEXTURE_CUBE_MAP_NEGATIVE_X                                           = 0x8516,
        TEXTURE_CUBE_MAP_POSITIVE_Y                                           = 0x8517,
        TEXTURE_CUBE_MAP_NEGATIVE_Y                                           = 0x8518,
        TEXTURE_CUBE_MAP_POSITIVE_Z                                           = 0x8519,
        TEXTURE_CUBE_MAP_NEGATIVE_Z                                           = 0x851A,
        PROXY_TEXTURE_CUBE_MAP                                                = 0x851B,
        MAX_CUBE_MAP_TEXTURE_SIZE                                             = 0x851C,
        COMBINE                                                               = 0x8570,
        COMBINE_RGB                                                           = 0x8571,
        COMBINE_ALPHA                                                         = 0x8572,
        RGB_SCALE                                                             = 0x8573,
        ADD_SIGNED                                                            = 0x8574,
        INTERPOLATE                                                           = 0x8575,
        CONSTANT                                                              = 0x8576,
        PRIMARY_COLOR                                                         = 0x8577,
        PREVIOUS                                                              = 0x8578,
        SOURCE0_RGB                                                           = 0x8580,
        SOURCE1_RGB                                                           = 0x8581,
        SOURCE2_RGB                                                           = 0x8582,
        SOURCE0_ALPHA                                                         = 0x8588,
        SOURCE1_ALPHA                                                         = 0x8589,
        SOURCE2_ALPHA                                                         = 0x858A,
        OPERAND0_RGB                                                          = 0x8590,
        OPERAND1_RGB                                                          = 0x8591,
        OPERAND2_RGB                                                          = 0x8592,
        OPERAND0_ALPHA                                                        = 0x8598,
        OPERAND1_ALPHA                                                        = 0x8599,
        OPERAND2_ALPHA                                                        = 0x859A,
        TEXTURE_COMPRESSED_IMAGE_SIZE                                         = 0x86A0,
        TEXTURE_COMPRESSED                                                    = 0x86A1,
        NUM_COMPRESSED_TEXTURE_FORMATS                                        = 0x86A2,
        COMPRESSED_TEXTURE_FORMATS                                            = 0x86A3,
        DOT3_RGB                                                              = 0x86AE,
        DOT3_RGBA                                                             = 0x86AF,
        MULTISAMPLE_BIT                                                       = 0x20000000,
        BLEND_DST_RGB                                                         = 0x80C8,
        BLEND_SRC_RGB                                                         = 0x80C9,
        BLEND_DST_ALPHA                                                       = 0x80CA,
        BLEND_SRC_ALPHA                                                       = 0x80CB,
        POINT_SIZE_MIN                                                        = 0x8126,
        POINT_SIZE_MAX                                                        = 0x8127,
        POINT_FADE_THRESHOLD_SIZE                                             = 0x8128,
        POINT_DISTANCE_ATTENUATION                                            = 0x8129,
        GENERATE_MIPMAP                                                       = 0x8191,
        GENERATE_MIPMAP_HINT                                                  = 0x8192,
        DEPTH_COMPONENT16                                                     = 0x81A5,
        DEPTH_COMPONENT24                                                     = 0x81A6,
        DEPTH_COMPONENT32                                                     = 0x81A7,
        MIRRORED_REPEAT                                                       = 0x8370,
        FOG_COORDINATE_SOURCE                                                 = 0x8450,
        FOG_COORDINATE                                                        = 0x8451,
        FRAGMENT_DEPTH                                                        = 0x8452,
        CURRENT_FOG_COORDINATE                                                = 0x8453,
        FOG_COORDINATE_ARRAY_TYPE                                             = 0x8454,
        FOG_COORDINATE_ARRAY_STRIDE                                           = 0x8455,
        FOG_COORDINATE_ARRAY_POINTER                                          = 0x8456,
        FOG_COORDINATE_ARRAY                                                  = 0x8457,
        COLOR_SUM                                                             = 0x8458,
        CURRENT_SECONDARY_COLOR                                               = 0x8459,
        SECONDARY_COLOR_ARRAY_SIZE                                            = 0x845A,
        SECONDARY_COLOR_ARRAY_TYPE                                            = 0x845B,
        SECONDARY_COLOR_ARRAY_STRIDE                                          = 0x845C,
        SECONDARY_COLOR_ARRAY_POINTER                                         = 0x845D,
        SECONDARY_COLOR_ARRAY                                                 = 0x845E,
        MAX_TEXTURE_LOD_BIAS                                                  = 0x84FD,
        TEXTURE_FILTER_CONTROL                                                = 0x8500,
        TEXTURE_LOD_BIAS                                                      = 0x8501,
        INCR_WRAP                                                             = 0x8507,
        DECR_WRAP                                                             = 0x8508,
        TEXTURE_DEPTH_SIZE                                                    = 0x884A,
        DEPTH_TEXTURE_MODE                                                    = 0x884B,
        TEXTURE_COMPARE_MODE                                                  = 0x884C,
        TEXTURE_COMPARE_FUNC                                                  = 0x884D,
        COMPARE_R_TO_TEXTURE                                                  = 0x884E,
        BUFFER_SIZE                                                           = 0x8764,
        BUFFER_USAGE                                                          = 0x8765,
        QUERY_COUNTER_BITS                                                    = 0x8864,
        CURRENT_QUERY                                                         = 0x8865,
        QUERY_RESULT                                                          = 0x8866,
        QUERY_RESULT_AVAILABLE                                                = 0x8867,
        ARRAY_BUFFER                                                          = 0x8892,
        ELEMENT_ARRAY_BUFFER                                                  = 0x8893,
        ARRAY_BUFFER_BINDING                                                  = 0x8894,
        ELEMENT_ARRAY_BUFFER_BINDING                                          = 0x8895,
        VERTEX_ARRAY_BUFFER_BINDING                                           = 0x8896,
        NORMAL_ARRAY_BUFFER_BINDING                                           = 0x8897,
        COLOR_ARRAY_BUFFER_BINDING                                            = 0x8898,
        INDEX_ARRAY_BUFFER_BINDING                                            = 0x8899,
        TEXTURE_COORD_ARRAY_BUFFER_BINDING                                    = 0x889A,
        EDGE_FLAG_ARRAY_BUFFER_BINDING                                        = 0x889B,
        SECONDARY_COLOR_ARRAY_BUFFER_BINDING                                  = 0x889C,
        FOG_COORDINATE_ARRAY_BUFFER_BINDING                                   = 0x889D,
        WEIGHT_ARRAY_BUFFER_BINDING                                           = 0x889E,
        VERTEX_ATTRIB_ARRAY_BUFFER_BINDING                                    = 0x889F,
        READ_ONLY                                                             = 0x88B8,
        WRITE_ONLY                                                            = 0x88B9,
        READ_WRITE                                                            = 0x88BA,
        BUFFER_ACCESS                                                         = 0x88BB,
        BUFFER_MAPPED                                                         = 0x88BC,
        BUFFER_MAP_POINTER                                                    = 0x88BD,
        STREAM_DRAW                                                           = 0x88E0,
        STREAM_READ                                                           = 0x88E1,
        STREAM_COPY                                                           = 0x88E2,
        STATIC_DRAW                                                           = 0x88E4,
        STATIC_READ                                                           = 0x88E5,
        STATIC_COPY                                                           = 0x88E6,
        DYNAMIC_DRAW                                                          = 0x88E8,
        DYNAMIC_READ                                                          = 0x88E9,
        DYNAMIC_COPY                                                          = 0x88EA,
        SAMPLES_PASSED                                                        = 0x8914,
        VERTEX_ATTRIB_ARRAY_ENABLED                                           = 0x8622,
        VERTEX_ATTRIB_ARRAY_SIZE                                              = 0x8623,
        VERTEX_ATTRIB_ARRAY_STRIDE                                            = 0x8624,
        VERTEX_ATTRIB_ARRAY_TYPE                                              = 0x8625,
        CURRENT_VERTEX_ATTRIB                                                 = 0x8626,
        VERTEX_PROGRAM_POINT_SIZE                                             = 0x8642,
        VERTEX_PROGRAM_TWO_SIDE                                               = 0x8643,
        VERTEX_ATTRIB_ARRAY_POINTER                                           = 0x8645,
        STENCIL_BACK_FUNC                                                     = 0x8800,
        STENCIL_BACK_FAIL                                                     = 0x8801,
        STENCIL_BACK_PASS_DEPTH_FAIL                                          = 0x8802,
        STENCIL_BACK_PASS_DEPTH_PASS                                          = 0x8803,
        MAX_DRAW_BUFFERS                                                      = 0x8824,
        DRAW_BUFFER0                                                          = 0x8825,
        DRAW_BUFFER1                                                          = 0x8826,
        DRAW_BUFFER2                                                          = 0x8827,
        DRAW_BUFFER3                                                          = 0x8828,
        DRAW_BUFFER4                                                          = 0x8829,
        DRAW_BUFFER5                                                          = 0x882A,
        DRAW_BUFFER6                                                          = 0x882B,
        DRAW_BUFFER7                                                          = 0x882C,
        DRAW_BUFFER8                                                          = 0x882D,
        DRAW_BUFFER9                                                          = 0x882E,
        DRAW_BUFFER10                                                         = 0x882F,
        DRAW_BUFFER11                                                         = 0x8830,
        DRAW_BUFFER12                                                         = 0x8831,
        DRAW_BUFFER13                                                         = 0x8832,
        DRAW_BUFFER14                                                         = 0x8833,
        DRAW_BUFFER15                                                         = 0x8834,
        BLEND_EQUATION_ALPHA                                                  = 0x883D,
        POINT_SPRITE                                                          = 0x8861,
        COORD_REPLACE                                                         = 0x8862,
        MAX_VERTEX_ATTRIBS                                                    = 0x8869,
        VERTEX_ATTRIB_ARRAY_NORMALIZED                                        = 0x886A,
        MAX_TEXTURE_COORDS                                                    = 0x8871,
        MAX_TEXTURE_IMAGE_UNITS                                               = 0x8872,
        FRAGMENT_SHADER                                                       = 0x8B30,
        VERTEX_SHADER                                                         = 0x8B31,
        MAX_FRAGMENT_UNIFORM_COMPONENTS                                       = 0x8B49,
        MAX_VERTEX_UNIFORM_COMPONENTS                                         = 0x8B4A,
        MAX_VARYING_FLOATS                                                    = 0x8B4B,
        MAX_VERTEX_TEXTURE_IMAGE_UNITS                                        = 0x8B4C,
        MAX_COMBINED_TEXTURE_IMAGE_UNITS                                      = 0x8B4D,
        SHADER_TYPE                                                           = 0x8B4F,
        FLOAT_VEC2                                                            = 0x8B50,
        FLOAT_VEC3                                                            = 0x8B51,
        FLOAT_VEC4                                                            = 0x8B52,
        INT_VEC2                                                              = 0x8B53,
        INT_VEC3                                                              = 0x8B54,
        INT_VEC4                                                              = 0x8B55,
        BOOL                                                                  = 0x8B56,
        BOOL_VEC2                                                             = 0x8B57,
        BOOL_VEC3                                                             = 0x8B58,
        BOOL_VEC4                                                             = 0x8B59,
        FLOAT_MAT2                                                            = 0x8B5A,
        FLOAT_MAT3                                                            = 0x8B5B,
        FLOAT_MAT4                                                            = 0x8B5C,
        SAMPLER_1D                                                            = 0x8B5D,
        SAMPLER_2D                                                            = 0x8B5E,
        SAMPLER_3D                                                            = 0x8B5F,
        SAMPLER_CUBE                                                          = 0x8B60,
        SAMPLER_1D_SHADOW                                                     = 0x8B61,
        SAMPLER_2D_SHADOW                                                     = 0x8B62,
        DELETE_STATUS                                                         = 0x8B80,
        COMPILE_STATUS                                                        = 0x8B81,
        LINK_STATUS                                                           = 0x8B82,
        VALIDATE_STATUS                                                       = 0x8B83,
        INFO_LOG_LENGTH                                                       = 0x8B84,
        ATTACHED_SHADERS                                                      = 0x8B85,
        ACTIVE_UNIFORMS                                                       = 0x8B86,
        ACTIVE_UNIFORM_MAX_LENGTH                                             = 0x8B87,
        SHADER_SOURCE_LENGTH                                                  = 0x8B88,
        ACTIVE_ATTRIBUTES                                                     = 0x8B89,
        ACTIVE_ATTRIBUTE_MAX_LENGTH                                           = 0x8B8A,
        FRAGMENT_SHADER_DERIVATIVE_HINT                                       = 0x8B8B,
        SHADING_LANGUAGE_VERSION                                              = 0x8B8C,
        CURRENT_PROGRAM                                                       = 0x8B8D,
        POINT_SPRITE_COORD_ORIGIN                                             = 0x8CA0,
        LOWER_LEFT                                                            = 0x8CA1,
        UPPER_LEFT                                                            = 0x8CA2,
        STENCIL_BACK_REF                                                      = 0x8CA3,
        STENCIL_BACK_VALUE_MASK                                               = 0x8CA4,
        STENCIL_BACK_WRITEMASK                                                = 0x8CA5,
        CURRENT_RASTER_SECONDARY_COLOR                                        = 0x845F,
        PIXEL_PACK_BUFFER                                                     = 0x88EB,
        PIXEL_UNPACK_BUFFER                                                   = 0x88EC,
        PIXEL_PACK_BUFFER_BINDING                                             = 0x88ED,
        PIXEL_UNPACK_BUFFER_BINDING                                           = 0x88EF,
        FLOAT_MAT2x3                                                          = 0x8B65,
        FLOAT_MAT2x4                                                          = 0x8B66,
        FLOAT_MAT3x2                                                          = 0x8B67,
        FLOAT_MAT3x4                                                          = 0x8B68,
        FLOAT_MAT4x2                                                          = 0x8B69,
        FLOAT_MAT4x3                                                          = 0x8B6A,
        SRGB                                                                  = 0x8C40,
        SRGB8                                                                 = 0x8C41,
        SRGB_ALPHA                                                            = 0x8C42,
        SRGB8_ALPHA8                                                          = 0x8C43,
        SLUMINANCE_ALPHA                                                      = 0x8C44,
        SLUMINANCE8_ALPHA8                                                    = 0x8C45,
        SLUMINANCE                                                            = 0x8C46,
        SLUMINANCE8                                                           = 0x8C47,
        COMPRESSED_SRGB                                                       = 0x8C48,
        COMPRESSED_SRGB_ALPHA                                                 = 0x8C49,
        COMPRESSED_SLUMINANCE                                                 = 0x8C4A,
        COMPRESSED_SLUMINANCE_ALPHA                                           = 0x8C4B,
        CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT                                   = 0x1,
        MAJOR_VERSION                                                         = 0x821B,
        MINOR_VERSION                                                         = 0x821C,
        NUM_EXTENSIONS                                                        = 0x821D,
        CONTEXT_FLAGS                                                         = 0x821E,
        DEPTH_BUFFER                                                          = 0x8223,
        STENCIL_BUFFER                                                        = 0x8224,
        RGBA32F                                                               = 0x8814,
        RGB32F                                                                = 0x8815,
        RGBA16F                                                               = 0x881A,
        RGB16F                                                                = 0x881B,
        VERTEX_ATTRIB_ARRAY_INTEGER                                           = 0x88FD,
        MAX_ARRAY_TEXTURE_LAYERS                                              = 0x88FF,
        MIN_PROGRAM_TEXEL_OFFSET                                              = 0x8904,
        MAX_PROGRAM_TEXEL_OFFSET                                              = 0x8905,
        CLAMP_VERTEX_COLOR                                                    = 0x891A,
        CLAMP_FRAGMENT_COLOR                                                  = 0x891B,
        CLAMP_READ_COLOR                                                      = 0x891C,
        FIXED_ONLY                                                            = 0x891D,
        TEXTURE_RED_TYPE                                                      = 0x8C10,
        TEXTURE_GREEN_TYPE                                                    = 0x8C11,
        TEXTURE_BLUE_TYPE                                                     = 0x8C12,
        TEXTURE_ALPHA_TYPE                                                    = 0x8C13,
        TEXTURE_LUMINANCE_TYPE                                                = 0x8C14,
        TEXTURE_INTENSITY_TYPE                                                = 0x8C15,
        TEXTURE_DEPTH_TYPE                                                    = 0x8C16,
        TEXTURE_1D_ARRAY                                                      = 0x8C18,
        PROXY_TEXTURE_1D_ARRAY                                                = 0x8C19,
        TEXTURE_2D_ARRAY                                                      = 0x8C1A,
        PROXY_TEXTURE_2D_ARRAY                                                = 0x8C1B,
        TEXTURE_BINDING_1D_ARRAY                                              = 0x8C1C,
        TEXTURE_BINDING_2D_ARRAY                                              = 0x8C1D,
        R11F_G11F_B10F                                                        = 0x8C3A,
        UNSIGNED_INT_10F_11F_11F_REV                                          = 0x8C3B,
        RGB9_E5                                                               = 0x8C3D,
        UNSIGNED_INT_5_9_9_9_REV                                              = 0x8C3E,
        TEXTURE_SHARED_SIZE                                                   = 0x8C3F,
        TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH                                 = 0x8C76,
        TRANSFORM_FEEDBACK_BUFFER_MODE                                        = 0x8C7F,
        MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS                            = 0x8C80,
        TRANSFORM_FEEDBACK_VARYINGS                                           = 0x8C83,
        TRANSFORM_FEEDBACK_BUFFER_START                                       = 0x8C84,
        TRANSFORM_FEEDBACK_BUFFER_SIZE                                        = 0x8C85,
        PRIMITIVES_GENERATED                                                  = 0x8C87,
        TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN                                 = 0x8C88,
        RASTERIZER_DISCARD                                                    = 0x8C89,
        MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS                         = 0x8C8A,
        MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS                               = 0x8C8B,
        INTERLEAVED_ATTRIBS                                                   = 0x8C8C,
        SEPARATE_ATTRIBS                                                      = 0x8C8D,
        TRANSFORM_FEEDBACK_BUFFER                                             = 0x8C8E,
        TRANSFORM_FEEDBACK_BUFFER_BINDING                                     = 0x8C8F,
        RGBA32UI                                                              = 0x8D70,
        RGB32UI                                                               = 0x8D71,
        RGBA16UI                                                              = 0x8D76,
        RGB16UI                                                               = 0x8D77,
        RGBA8UI                                                               = 0x8D7C,
        RGB8UI                                                                = 0x8D7D,
        RGBA32I                                                               = 0x8D82,
        RGB32I                                                                = 0x8D83,
        RGBA16I                                                               = 0x8D88,
        RGB16I                                                                = 0x8D89,
        RGBA8I                                                                = 0x8D8E,
        RGB8I                                                                 = 0x8D8F,
        RED_INTEGER                                                           = 0x8D94,
        GREEN_INTEGER                                                         = 0x8D95,
        BLUE_INTEGER                                                          = 0x8D96,
        ALPHA_INTEGER                                                         = 0x8D97,
        RGB_INTEGER                                                           = 0x8D98,
        RGBA_INTEGER                                                          = 0x8D99,
        BGR_INTEGER                                                           = 0x8D9A,
        BGRA_INTEGER                                                          = 0x8D9B,
        SAMPLER_1D_ARRAY                                                      = 0x8DC0,
        SAMPLER_2D_ARRAY                                                      = 0x8DC1,
        SAMPLER_1D_ARRAY_SHADOW                                               = 0x8DC3,
        SAMPLER_2D_ARRAY_SHADOW                                               = 0x8DC4,
        SAMPLER_CUBE_SHADOW                                                   = 0x8DC5,
        UNSIGNED_INT_VEC2                                                     = 0x8DC6,
        UNSIGNED_INT_VEC3                                                     = 0x8DC7,
        UNSIGNED_INT_VEC4                                                     = 0x8DC8,
        INT_SAMPLER_1D                                                        = 0x8DC9,
        INT_SAMPLER_2D                                                        = 0x8DCA,
        INT_SAMPLER_3D                                                        = 0x8DCB,
        INT_SAMPLER_CUBE                                                      = 0x8DCC,
        INT_SAMPLER_1D_ARRAY                                                  = 0x8DCE,
        INT_SAMPLER_2D_ARRAY                                                  = 0x8DCF,
        UNSIGNED_INT_SAMPLER_1D                                               = 0x8DD1,
        UNSIGNED_INT_SAMPLER_2D                                               = 0x8DD2,
        UNSIGNED_INT_SAMPLER_3D                                               = 0x8DD3,
        UNSIGNED_INT_SAMPLER_CUBE                                             = 0x8DD4,
        UNSIGNED_INT_SAMPLER_1D_ARRAY                                         = 0x8DD6,
        UNSIGNED_INT_SAMPLER_2D_ARRAY                                         = 0x8DD7,
        QUERY_WAIT                                                            = 0x8E13,
        QUERY_NO_WAIT                                                         = 0x8E14,
        QUERY_BY_REGION_WAIT                                                  = 0x8E15,
        QUERY_BY_REGION_NO_WAIT                                               = 0x8E16,
        TEXTURE_RECTANGLE                                                     = 0x84F5,
        TEXTURE_BINDING_RECTANGLE                                             = 0x84F6,
        PROXY_TEXTURE_RECTANGLE                                               = 0x84F7,
        MAX_RECTANGLE_TEXTURE_SIZE                                            = 0x84F8,
        SAMPLER_2D_RECT                                                       = 0x8B63,
        SAMPLER_2D_RECT_SHADOW                                                = 0x8B64,
        TEXTURE_BUFFER                                                        = 0x8C2A,
        MAX_TEXTURE_BUFFER_SIZE                                               = 0x8C2B,
        TEXTURE_BINDING_BUFFER                                                = 0x8C2C,
        TEXTURE_BUFFER_DATA_STORE_BINDING                                     = 0x8C2D,
        TEXTURE_BUFFER_FORMAT                                                 = 0x8C2E,
        SAMPLER_BUFFER                                                        = 0x8DC2,
        INT_SAMPLER_2D_RECT                                                   = 0x8DCD,
        INT_SAMPLER_BUFFER                                                    = 0x8DD0,
        UNSIGNED_INT_SAMPLER_2D_RECT                                          = 0x8DD5,
        UNSIGNED_INT_SAMPLER_BUFFER                                           = 0x8DD8,
        RED_SNORM                                                             = 0x8F90,
        RG_SNORM                                                              = 0x8F91,
        RGB_SNORM                                                             = 0x8F92,
        RGBA_SNORM                                                            = 0x8F93,
        R8_SNORM                                                              = 0x8F94,
        RG8_SNORM                                                             = 0x8F95,
        RGB8_SNORM                                                            = 0x8F96,
        RGBA8_SNORM                                                           = 0x8F97,
        R16_SNORM                                                             = 0x8F98,
        RG16_SNORM                                                            = 0x8F99,
        RGB16_SNORM                                                           = 0x8F9A,
        RGBA16_SNORM                                                          = 0x8F9B,
        SIGNED_NORMALIZED                                                     = 0x8F9C,
        PRIMITIVE_RESTART                                                     = 0x8F9D,
        PRIMITIVE_RESTART_INDEX                                               = 0x8F9E,
        BUFFER_ACCESS_FLAGS                                                   = 0x911F,
        BUFFER_MAP_LENGTH                                                     = 0x9120,
        BUFFER_MAP_OFFSET                                                     = 0x9121,
        CONTEXT_CORE_PROFILE_BIT                                              = 0x1,
        CONTEXT_COMPATIBILITY_PROFILE_BIT                                     = 0x2,
        LINES_ADJACENCY                                                       = 0xA,
        LINE_STRIP_ADJACENCY                                                  = 0xB,
        TRIANGLES_ADJACENCY                                                   = 0xC,
        TRIANGLE_STRIP_ADJACENCY                                              = 0xD,
        PROGRAM_POINT_SIZE                                                    = 0x8642,
        GEOMETRY_VERTICES_OUT                                                 = 0x8916,
        GEOMETRY_INPUT_TYPE                                                   = 0x8917,
        GEOMETRY_OUTPUT_TYPE                                                  = 0x8918,
        MAX_GEOMETRY_TEXTURE_IMAGE_UNITS                                      = 0x8C29,
        FRAMEBUFFER_ATTACHMENT_LAYERED                                        = 0x8DA7,
        FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS                                  = 0x8DA8,
        GEOMETRY_SHADER                                                       = 0x8DD9,
        MAX_GEOMETRY_UNIFORM_COMPONENTS                                       = 0x8DDF,
        MAX_GEOMETRY_OUTPUT_VERTICES                                          = 0x8DE0,
        MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS                                  = 0x8DE1,
        MAX_VERTEX_OUTPUT_COMPONENTS                                          = 0x9122,
        MAX_GEOMETRY_INPUT_COMPONENTS                                         = 0x9123,
        MAX_GEOMETRY_OUTPUT_COMPONENTS                                        = 0x9124,
        MAX_FRAGMENT_INPUT_COMPONENTS                                         = 0x9125,
        CONTEXT_PROFILE_MASK                                                  = 0x9126,
        VERTEX_ATTRIB_ARRAY_DIVISOR                                           = 0x88FE,
        RGB10_A2UI                                                            = 0x906F,
        SAMPLE_SHADING                                                        = 0x8C36,
        MIN_SAMPLE_SHADING_VALUE                                              = 0x8C37,
        MIN_PROGRAM_TEXTURE_GATHER_OFFSET                                     = 0x8E5E,
        MAX_PROGRAM_TEXTURE_GATHER_OFFSET                                     = 0x8E5F,
        MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS                                 = 0x8F9F,
        TEXTURE_CUBE_MAP_ARRAY                                                = 0x9009,
        TEXTURE_BINDING_CUBE_MAP_ARRAY                                        = 0x900A,
        PROXY_TEXTURE_CUBE_MAP_ARRAY                                          = 0x900B,
        SAMPLER_CUBE_MAP_ARRAY                                                = 0x900C,
        SAMPLER_CUBE_MAP_ARRAY_SHADOW                                         = 0x900D,
        INT_SAMPLER_CUBE_MAP_ARRAY                                            = 0x900E,
        UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY                                   = 0x900F,
        TRANSFORM_FEEDBACK_PAUSED                                             = 0x8E23,
        TRANSFORM_FEEDBACK_ACTIVE                                             = 0x8E24,
        COMPRESSED_RGBA_BPTC_UNORM                                            = 0x8E8C,
        COMPRESSED_SRGB_ALPHA_BPTC_UNORM                                      = 0x8E8D,
        COMPRESSED_RGB_BPTC_SIGNED_FLOAT                                      = 0x8E8E,
        COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT                                    = 0x8E8F,
        COPY_READ_BUFFER_BINDING                                              = 0x8F36,
        COPY_WRITE_BUFFER_BINDING                                             = 0x8F37,
        NUM_SHADING_LANGUAGE_VERSIONS                                         = 0x82E9,
        VERTEX_ATTRIB_ARRAY_LONG                                              = 0x874E,
        PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED                               = 0x8221,
        MAX_VERTEX_ATTRIB_STRIDE                                              = 0x82E5,
        TEXTURE_BUFFER_BINDING                                                = 0x8C2A,
        CONTEXT_FLAG_ROBUST_ACCESS_BIT                                        = 0x4,
        CONTEXT_FLAG_NO_ERROR_BIT                                             = 0x8,
        PARAMETER_BUFFER                                                      = 0x80EE,
        PARAMETER_BUFFER_BINDING                                              = 0x80EF,
        TRANSFORM_FEEDBACK_OVERFLOW                                           = 0x82EC,
        TRANSFORM_FEEDBACK_STREAM_OVERFLOW                                    = 0x82ED,
        VERTICES_SUBMITTED                                                    = 0x82EE,
        PRIMITIVES_SUBMITTED                                                  = 0x82EF,
        VERTEX_SHADER_INVOCATIONS                                             = 0x82F0,
        TESS_CONTROL_SHADER_PATCHES                                           = 0x82F1,
        TESS_EVALUATION_SHADER_INVOCATIONS                                    = 0x82F2,
        GEOMETRY_SHADER_PRIMITIVES_EMITTED                                    = 0x82F3,
        FRAGMENT_SHADER_INVOCATIONS                                           = 0x82F4,
        COMPUTE_SHADER_INVOCATIONS                                            = 0x82F5,
        CLIPPING_INPUT_PRIMITIVES                                             = 0x82F6,
        CLIPPING_OUTPUT_PRIMITIVES                                            = 0x82F7,
        TEXTURE_MAX_ANISOTROPY                                                = 0x84FE,
        MAX_TEXTURE_MAX_ANISOTROPY                                            = 0x84FF,
        POLYGON_OFFSET_CLAMP                                                  = 0x8E1B,
        SHADER_BINARY_FORMAT_SPIR_V                                           = 0x9551,
        SPIR_V_BINARY                                                         = 0x9552,
        SPIR_V_EXTENSIONS                                                     = 0x9553,
        NUM_SPIR_V_EXTENSIONS                                                 = 0x9554,
        MULTISAMPLE_3DFX                                                      = 0x86B2,
        SAMPLE_BUFFERS_3DFX                                                   = 0x86B3,
        SAMPLES_3DFX                                                          = 0x86B4,
        MULTISAMPLE_BIT_3DFX                                                  = 0x20000000,
        COMPRESSED_RGB_FXT1_3DFX                                              = 0x86B0,
        COMPRESSED_RGBA_FXT1_3DFX                                             = 0x86B1,
        FACTOR_MIN_AMD                                                        = 0x901C,
        FACTOR_MAX_AMD                                                        = 0x901D,
        N3DC_X_AMD                                                            = 0x87F9,
        N3DC_XY_AMD                                                           = 0x87FA,
        ATC_RGBA_INTERPOLATED_ALPHA_AMD                                       = 0x87EE,
        ATC_RGB_AMD                                                           = 0x8C92,
        ATC_RGBA_EXPLICIT_ALPHA_AMD                                           = 0x8C93,
        MAX_DEBUG_MESSAGE_LENGTH_AMD                                          = 0x9143,
        MAX_DEBUG_LOGGED_MESSAGES_AMD                                         = 0x9144,
        DEBUG_LOGGED_MESSAGES_AMD                                             = 0x9145,
        DEBUG_SEVERITY_HIGH_AMD                                               = 0x9146,
        DEBUG_SEVERITY_MEDIUM_AMD                                             = 0x9147,
        DEBUG_SEVERITY_LOW_AMD                                                = 0x9148,
        DEBUG_CATEGORY_API_ERROR_AMD                                          = 0x9149,
        DEBUG_CATEGORY_WINDOW_SYSTEM_AMD                                      = 0x914A,
        DEBUG_CATEGORY_DEPRECATION_AMD                                        = 0x914B,
        DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD                                 = 0x914C,
        DEBUG_CATEGORY_PERFORMANCE_AMD                                        = 0x914D,
        DEBUG_CATEGORY_SHADER_COMPILER_AMD                                    = 0x914E,
        DEBUG_CATEGORY_APPLICATION_AMD                                        = 0x914F,
        DEBUG_CATEGORY_OTHER_AMD                                              = 0x9150,
        DEPTH_CLAMP_NEAR_AMD                                                  = 0x901E,
        DEPTH_CLAMP_FAR_AMD                                                   = 0x901F,
        SUBSAMPLE_DISTANCE_AMD                                                = 0x883F,
        PIXELS_PER_SAMPLE_PATTERN_X_AMD                                       = 0x91AE,
        PIXELS_PER_SAMPLE_PATTERN_Y_AMD                                       = 0x91AF,
        ALL_PIXELS_AMD                                                        = 0xFFFFFFFF,
        FLOAT16_NV                                                            = 0x8FF8,
        FLOAT16_VEC2_NV                                                       = 0x8FF9,
        FLOAT16_VEC3_NV                                                       = 0x8FFA,
        FLOAT16_VEC4_NV                                                       = 0x8FFB,
        FLOAT16_MAT2_AMD                                                      = 0x91C5,
        FLOAT16_MAT3_AMD                                                      = 0x91C6,
        FLOAT16_MAT4_AMD                                                      = 0x91C7,
        FLOAT16_MAT2x3_AMD                                                    = 0x91C8,
        FLOAT16_MAT2x4_AMD                                                    = 0x91C9,
        FLOAT16_MAT3x2_AMD                                                    = 0x91CA,
        FLOAT16_MAT3x4_AMD                                                    = 0x91CB,
        FLOAT16_MAT4x2_AMD                                                    = 0x91CC,
        FLOAT16_MAT4x3_AMD                                                    = 0x91CD,
        RG8UI                                                                 = 0x8238,
        RG16UI                                                                = 0x823A,
        VERTEX_ELEMENT_SWIZZLE_AMD                                            = 0x91A4,
        VERTEX_ID_SWIZZLE_AMD                                                 = 0x91A5,
        DATA_BUFFER_AMD                                                       = 0x9151,
        PERFORMANCE_MONITOR_AMD                                               = 0x9152,
        QUERY_OBJECT_AMD                                                      = 0x9153,
        VERTEX_ARRAY_OBJECT_AMD                                               = 0x9154,
        SAMPLER_OBJECT_AMD                                                    = 0x9155,
        QUERY_DEPTH_PASS_EVENT_BIT_AMD                                        = 0x1,
        QUERY_DEPTH_FAIL_EVENT_BIT_AMD                                        = 0x2,
        QUERY_STENCIL_FAIL_EVENT_BIT_AMD                                      = 0x4,
        QUERY_DEPTH_BOUNDS_FAIL_EVENT_BIT_AMD                                 = 0x8,
        OCCLUSION_QUERY_EVENT_MASK_AMD                                        = 0x874F,
        QUERY_ALL_EVENT_BITS_AMD                                              = 0xFFFFFFFF,
        COUNTER_TYPE_AMD                                                      = 0x8BC0,
        COUNTER_RANGE_AMD                                                     = 0x8BC1,
        UNSIGNED_INT64_AMD                                                    = 0x8BC2,
        PERCENTAGE_AMD                                                        = 0x8BC3,
        PERFMON_RESULT_AVAILABLE_AMD                                          = 0x8BC4,
        PERFMON_RESULT_SIZE_AMD                                               = 0x8BC5,
        PERFMON_RESULT_AMD                                                    = 0x8BC6,
        EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD                                    = 0x9160,
        Z400_BINARY_AMD                                                       = 0x8740,
        QUERY_BUFFER_AMD                                                      = 0x9192,
        QUERY_BUFFER_BINDING_AMD                                              = 0x9193,
        QUERY_RESULT_NO_WAIT_AMD                                              = 0x9194,
        TEXTURE_CUBE_MAP_SEAMLESS                                             = 0x884F,
        TEXTURE_STORAGE_SPARSE_BIT_AMD                                        = 0x1,
        VIRTUAL_PAGE_SIZE_X_AMD                                               = 0x9195,
        VIRTUAL_PAGE_SIZE_Y_AMD                                               = 0x9196,
        VIRTUAL_PAGE_SIZE_Z_AMD                                               = 0x9197,
        MAX_SPARSE_TEXTURE_SIZE_AMD                                           = 0x9198,
        MAX_SPARSE_3D_TEXTURE_SIZE_AMD                                        = 0x9199,
        MAX_SPARSE_ARRAY_TEXTURE_LAYERS                                       = 0x919A,
        MIN_SPARSE_LEVEL_AMD                                                  = 0x919B,
        MIN_LOD_WARNING_AMD                                                   = 0x919C,
        SET_AMD                                                               = 0x874A,
        REPLACE_VALUE_AMD                                                     = 0x874B,
        STENCIL_OP_VALUE_AMD                                                  = 0x874C,
        STENCIL_BACK_OP_VALUE_AMD                                             = 0x874D,
        STREAM_RASTERIZATION_AMD                                              = 0x91A0,
        SAMPLER_BUFFER_AMD                                                    = 0x9001,
        INT_SAMPLER_BUFFER_AMD                                                = 0x9002,
        UNSIGNED_INT_SAMPLER_BUFFER_AMD                                       = 0x9003,
        TESSELLATION_MODE_AMD                                                 = 0x9004,
        TESSELLATION_FACTOR_AMD                                               = 0x9005,
        DISCRETE_AMD                                                          = 0x9006,
        CONTINUOUS_AMD                                                        = 0x9007,
        DRAW_FRAMEBUFFER_BINDING_ANGLE                                        = 0x8CA6,
        READ_FRAMEBUFFER_ANGLE                                                = 0x8CA8,
        DRAW_FRAMEBUFFER_ANGLE                                                = 0x8CA9,
        READ_FRAMEBUFFER_BINDING_ANGLE                                        = 0x8CAA,
        RENDERBUFFER_SAMPLES_ANGLE                                            = 0x8CAB,
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE                              = 0x8D56,
        MAX_SAMPLES_ANGLE                                                     = 0x8D57,
        VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE                                     = 0x88FE,
        PACK_REVERSE_ROW_ORDER_ANGLE                                          = 0x93A4,
        PROGRAM_BINARY_ANGLE                                                  = 0x93A6,
        COMPRESSED_RGB_S3TC_DXT1_ANGLE                                        = 0x83F0,
        COMPRESSED_RGBA_S3TC_DXT1_ANGLE                                       = 0x83F1,
        COMPRESSED_RGBA_S3TC_DXT3_ANGLE                                       = 0x83F2,
        COMPRESSED_RGBA_S3TC_DXT5_ANGLE                                       = 0x83F3,
        TEXTURE_USAGE_ANGLE                                                   = 0x93A2,
        FRAMEBUFFER_ATTACHMENT_ANGLE                                          = 0x93A3,
        QUERY_COUNTER_BITS_ANGLE                                              = 0x8864,
        CURRENT_QUERY_ANGLE                                                   = 0x8865,
        QUERY_RESULT_ANGLE                                                    = 0x8866,
        QUERY_RESULT_AVAILABLE_ANGLE                                          = 0x8867,
        TIME_ELAPSED_ANGLE                                                    = 0x88BF,
        TIMESTAMP_ANGLE                                                       = 0x8E28,
        TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE                                 = 0x93A0,
        AUX_DEPTH_STENCIL_APPLE                                               = 0x8A14,
        UNPACK_CLIENT_STORAGE_APPLE                                           = 0x85B2,
        MAX_CLIP_DISTANCES_APPLE                                              = 0xD32,
        CLIP_DISTANCE0_APPLE                                                  = 0x3000,
        CLIP_DISTANCE1_APPLE                                                  = 0x3001,
        CLIP_DISTANCE2_APPLE                                                  = 0x3002,
        CLIP_DISTANCE3_APPLE                                                  = 0x3003,
        CLIP_DISTANCE4_APPLE                                                  = 0x3004,
        CLIP_DISTANCE5_APPLE                                                  = 0x3005,
        CLIP_DISTANCE6_APPLE                                                  = 0x3006,
        CLIP_DISTANCE7_APPLE                                                  = 0x3007,
        ELEMENT_ARRAY_APPLE                                                   = 0x8A0C,
        ELEMENT_ARRAY_TYPE_APPLE                                              = 0x8A0D,
        ELEMENT_ARRAY_POINTER_APPLE                                           = 0x8A0E,
        DRAW_PIXELS_APPLE                                                     = 0x8A0A,
        FENCE_APPLE                                                           = 0x8A0B,
        HALF_APPLE                                                            = 0x140B,
        RGBA_FLOAT32_APPLE                                                    = 0x8814,
        RGB_FLOAT32_APPLE                                                     = 0x8815,
        ALPHA_FLOAT32_APPLE                                                   = 0x8816,
        INTENSITY_FLOAT32_APPLE                                               = 0x8817,
        LUMINANCE_FLOAT32_APPLE                                               = 0x8818,
        LUMINANCE_ALPHA_FLOAT32_APPLE                                         = 0x8819,
        RGBA_FLOAT16_APPLE                                                    = 0x881A,
        RGB_FLOAT16_APPLE                                                     = 0x881B,
        ALPHA_FLOAT16_APPLE                                                   = 0x881C,
        INTENSITY_FLOAT16_APPLE                                               = 0x881D,
        LUMINANCE_FLOAT16_APPLE                                               = 0x881E,
        LUMINANCE_ALPHA_FLOAT16_APPLE                                         = 0x881F,
        COLOR_FLOAT_APPLE                                                     = 0x8A0F,
        BUFFER_SERIALIZED_MODIFY_APPLE                                        = 0x8A12,
        BUFFER_FLUSHING_UNMAP_APPLE                                           = 0x8A13,
        DRAW_FRAMEBUFFER_BINDING_APPLE                                        = 0x8CA6,
        READ_FRAMEBUFFER_APPLE                                                = 0x8CA8,
        DRAW_FRAMEBUFFER_APPLE                                                = 0x8CA9,
        READ_FRAMEBUFFER_BINDING_APPLE                                        = 0x8CAA,
        RENDERBUFFER_SAMPLES_APPLE                                            = 0x8CAB,
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE                              = 0x8D56,
        MAX_SAMPLES_APPLE                                                     = 0x8D57,
        BUFFER_OBJECT_APPLE                                                   = 0x85B3,
        RELEASED_APPLE                                                        = 0x8A19,
        VOLATILE_APPLE                                                        = 0x8A1A,
        RETAINED_APPLE                                                        = 0x8A1B,
        UNDEFINED_APPLE                                                       = 0x8A1C,
        PURGEABLE_APPLE                                                       = 0x8A1D,
        MIN_PBUFFER_VIEWPORT_DIMS_APPLE                                       = 0x8A10,
        UNSIGNED_SHORT_8_8_APPLE                                              = 0x85BA,
        UNSIGNED_SHORT_8_8_REV_APPLE                                          = 0x85BB,
        RGB_422_APPLE                                                         = 0x8A1F,
        RGB_RAW_422_APPLE                                                     = 0x8A51,
        PACK_ROW_BYTES_APPLE                                                  = 0x8A15,
        UNPACK_ROW_BYTES_APPLE                                                = 0x8A16,
        LIGHT_MODEL_SPECULAR_VECTOR_APPLE                                     = 0x85B0,
        SYNC_FLUSH_COMMANDS_BIT_APPLE                                         = 0x1,
        SYNC_OBJECT_APPLE                                                     = 0x8A53,
        MAX_SERVER_WAIT_TIMEOUT_APPLE                                         = 0x9111,
        OBJECT_TYPE_APPLE                                                     = 0x9112,
        SYNC_CONDITION_APPLE                                                  = 0x9113,
        SYNC_STATUS_APPLE                                                     = 0x9114,
        SYNC_FLAGS_APPLE                                                      = 0x9115,
        SYNC_FENCE_APPLE                                                      = 0x9116,
        SYNC_GPU_COMMANDS_COMPLETE_APPLE                                      = 0x9117,
        UNSIGNALED_APPLE                                                      = 0x9118,
        SIGNALED_APPLE                                                        = 0x9119,
        ALREADY_SIGNALED_APPLE                                                = 0x911A,
        TIMEOUT_EXPIRED_APPLE                                                 = 0x911B,
        CONDITION_SATISFIED_APPLE                                             = 0x911C,
        WAIT_FAILED_APPLE                                                     = 0x911D,
        TIMEOUT_IGNORED_APPLE                                                 = 0xFFFFFFFFFFFFFFFF,
        BGRA_EXT                                                              = 0x80E1,
        BGRA8_EXT                                                             = 0x93A1,
        TEXTURE_MAX_LEVEL_APPLE                                               = 0x813D,
        R11F_G11F_B10F_APPLE                                                  = 0x8C3A,
        UNSIGNED_INT_10F_11F_11F_REV_APPLE                                    = 0x8C3B,
        RGB9_E5_APPLE                                                         = 0x8C3D,
        UNSIGNED_INT_5_9_9_9_REV_APPLE                                        = 0x8C3E,
        TEXTURE_RANGE_LENGTH_APPLE                                            = 0x85B7,
        TEXTURE_RANGE_POINTER_APPLE                                           = 0x85B8,
        TEXTURE_STORAGE_HINT_APPLE                                            = 0x85BC,
        STORAGE_PRIVATE_APPLE                                                 = 0x85BD,
        STORAGE_CACHED_APPLE                                                  = 0x85BE,
        STORAGE_SHARED_APPLE                                                  = 0x85BF,
        TRANSFORM_HINT_APPLE                                                  = 0x85B1,
        VERTEX_ARRAY_BINDING_APPLE                                            = 0x85B5,
        VERTEX_ARRAY_RANGE_APPLE                                              = 0x851D,
        VERTEX_ARRAY_RANGE_LENGTH_APPLE                                       = 0x851E,
        VERTEX_ARRAY_STORAGE_HINT_APPLE                                       = 0x851F,
        MAX_VERTEX_ARRAY_RANGE_ELEMENT_APPLE                                  = 0x8520,
        VERTEX_ARRAY_RANGE_POINTER_APPLE                                      = 0x8521,
        STORAGE_CLIENT_APPLE                                                  = 0x85B4,
        VERTEX_ATTRIB_MAP1_APPLE                                              = 0x8A00,
        VERTEX_ATTRIB_MAP2_APPLE                                              = 0x8A01,
        VERTEX_ATTRIB_MAP1_SIZE_APPLE                                         = 0x8A02,
        VERTEX_ATTRIB_MAP1_COEFF_APPLE                                        = 0x8A03,
        VERTEX_ATTRIB_MAP1_ORDER_APPLE                                        = 0x8A04,
        VERTEX_ATTRIB_MAP1_DOMAIN_APPLE                                       = 0x8A05,
        VERTEX_ATTRIB_MAP2_SIZE_APPLE                                         = 0x8A06,
        VERTEX_ATTRIB_MAP2_COEFF_APPLE                                        = 0x8A07,
        VERTEX_ATTRIB_MAP2_ORDER_APPLE                                        = 0x8A08,
        VERTEX_ATTRIB_MAP2_DOMAIN_APPLE                                       = 0x8A09,
        YCBCR_422_APPLE                                                       = 0x85B9,
        FIXED                                                                 = 0x140C,
        IMPLEMENTATION_COLOR_READ_TYPE                                        = 0x8B9A,
        IMPLEMENTATION_COLOR_READ_FORMAT                                      = 0x8B9B,
        RGB565                                                                = 0x8D62,
        LOW_FLOAT                                                             = 0x8DF0,
        MEDIUM_FLOAT                                                          = 0x8DF1,
        HIGH_FLOAT                                                            = 0x8DF2,
        LOW_INT                                                               = 0x8DF3,
        MEDIUM_INT                                                            = 0x8DF4,
        HIGH_INT                                                              = 0x8DF5,
        SHADER_BINARY_FORMATS                                                 = 0x8DF8,
        NUM_SHADER_BINARY_FORMATS                                             = 0x8DF9,
        SHADER_COMPILER                                                       = 0x8DFA,
        MAX_VERTEX_UNIFORM_VECTORS                                            = 0x8DFB,
        MAX_VARYING_VECTORS                                                   = 0x8DFC,
        MAX_FRAGMENT_UNIFORM_VECTORS                                          = 0x8DFD,
        PRIMITIVE_BOUNDING_BOX_ARB                                            = 0x92BE,
        MULTISAMPLE_LINE_WIDTH_RANGE_ARB                                      = 0x9381,
        MULTISAMPLE_LINE_WIDTH_GRANULARITY_ARB                                = 0x9382,
        TEXTURE_IMMUTABLE_LEVELS                                              = 0x82DF,
        PRIMITIVE_RESTART_FIXED_INDEX                                         = 0x8D69,
        ANY_SAMPLES_PASSED_CONSERVATIVE                                       = 0x8D6A,
        MAX_ELEMENT_INDEX                                                     = 0x8D6B,
        COMPRESSED_R11_EAC                                                    = 0x9270,
        COMPRESSED_SIGNED_R11_EAC                                             = 0x9271,
        COMPRESSED_RG11_EAC                                                   = 0x9272,
        COMPRESSED_SIGNED_RG11_EAC                                            = 0x9273,
        COMPRESSED_RGB8_ETC2                                                  = 0x9274,
        COMPRESSED_SRGB8_ETC2                                                 = 0x9275,
        COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2                              = 0x9276,
        COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2                             = 0x9277,
        COMPRESSED_RGBA8_ETC2_EAC                                             = 0x9278,
        COMPRESSED_SRGB8_ALPHA8_ETC2_EAC                                      = 0x9279,
        UNSIGNED_INT64_ARB                                                    = 0x140F,
        SRC1_COLOR                                                            = 0x88F9,
        ONE_MINUS_SRC1_COLOR                                                  = 0x88FA,
        ONE_MINUS_SRC1_ALPHA                                                  = 0x88FB,
        MAX_DUAL_SOURCE_DRAW_BUFFERS                                          = 0x88FC,
        MAP_READ_BIT                                                          = 0x1,
        MAP_WRITE_BIT                                                         = 0x2,
        MAP_PERSISTENT_BIT                                                    = 0x40,
        MAP_COHERENT_BIT                                                      = 0x80,
        DYNAMIC_STORAGE_BIT                                                   = 0x100,
        CLIENT_STORAGE_BIT                                                    = 0x200,
        CLIENT_MAPPED_BUFFER_BARRIER_BIT                                      = 0x4000,
        BUFFER_IMMUTABLE_STORAGE                                              = 0x821F,
        BUFFER_STORAGE_FLAGS                                                  = 0x8220,
        SYNC_CL_EVENT_ARB                                                     = 0x8240,
        SYNC_CL_EVENT_COMPLETE_ARB                                            = 0x8241,
        CLEAR_TEXTURE                                                         = 0x9365,
        CLIP_ORIGIN                                                           = 0x935C,
        CLIP_DEPTH_MODE                                                       = 0x935D,
        NEGATIVE_ONE_TO_ONE                                                   = 0x935E,
        ZERO_TO_ONE                                                           = 0x935F,
        RGBA_FLOAT_MODE_ARB                                                   = 0x8820,
        CLAMP_VERTEX_COLOR_ARB                                                = 0x891A,
        CLAMP_FRAGMENT_COLOR_ARB                                              = 0x891B,
        CLAMP_READ_COLOR_ARB                                                  = 0x891C,
        FIXED_ONLY_ARB                                                        = 0x891D,
        UNPACK_COMPRESSED_BLOCK_WIDTH                                         = 0x9127,
        UNPACK_COMPRESSED_BLOCK_HEIGHT                                        = 0x9128,
        UNPACK_COMPRESSED_BLOCK_DEPTH                                         = 0x9129,
        UNPACK_COMPRESSED_BLOCK_SIZE                                          = 0x912A,
        PACK_COMPRESSED_BLOCK_WIDTH                                           = 0x912B,
        PACK_COMPRESSED_BLOCK_HEIGHT                                          = 0x912C,
        PACK_COMPRESSED_BLOCK_DEPTH                                           = 0x912D,
        PACK_COMPRESSED_BLOCK_SIZE                                            = 0x912E,
        COMPUTE_SHADER_BIT                                                    = 0x20,
        MAX_COMPUTE_SHARED_MEMORY_SIZE                                        = 0x8262,
        MAX_COMPUTE_UNIFORM_COMPONENTS                                        = 0x8263,
        MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS                                    = 0x8264,
        MAX_COMPUTE_ATOMIC_COUNTERS                                           = 0x8265,
        MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS                               = 0x8266,
        COMPUTE_WORK_GROUP_SIZE                                               = 0x8267,
        MAX_COMPUTE_WORK_GROUP_INVOCATIONS                                    = 0x90EB,
        UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER                            = 0x90EC,
        ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER                    = 0x90ED,
        DISPATCH_INDIRECT_BUFFER                                              = 0x90EE,
        DISPATCH_INDIRECT_BUFFER_BINDING                                      = 0x90EF,
        COMPUTE_SHADER                                                        = 0x91B9,
        MAX_COMPUTE_UNIFORM_BLOCKS                                            = 0x91BB,
        MAX_COMPUTE_TEXTURE_IMAGE_UNITS                                       = 0x91BC,
        MAX_COMPUTE_IMAGE_UNIFORMS                                            = 0x91BD,
        MAX_COMPUTE_WORK_GROUP_COUNT                                          = 0x91BE,
        MAX_COMPUTE_WORK_GROUP_SIZE                                           = 0x91BF,
        MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB                               = 0x90EB,
        MAX_COMPUTE_FIXED_GROUP_SIZE_ARB                                      = 0x91BF,
        MAX_COMPUTE_VARIABLE_GROUP_INVOCATIONS_ARB                            = 0x9344,
        MAX_COMPUTE_VARIABLE_GROUP_SIZE_ARB                                   = 0x9345,
        QUERY_WAIT_INVERTED                                                   = 0x8E17,
        QUERY_NO_WAIT_INVERTED                                                = 0x8E18,
        QUERY_BY_REGION_WAIT_INVERTED                                         = 0x8E19,
        QUERY_BY_REGION_NO_WAIT_INVERTED                                      = 0x8E1A,
        COPY_READ_BUFFER                                                      = 0x8F36,
        COPY_WRITE_BUFFER                                                     = 0x8F37,
        MAX_CULL_DISTANCES                                                    = 0x82F9,
        MAX_COMBINED_CLIP_AND_CULL_DISTANCES                                  = 0x82FA,
        DEBUG_OUTPUT_SYNCHRONOUS_ARB                                          = 0x8242,
        DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB                                  = 0x8243,
        DEBUG_CALLBACK_FUNCTION_ARB                                           = 0x8244,
        DEBUG_CALLBACK_USER_PARAM_ARB                                         = 0x8245,
        DEBUG_SOURCE_API_ARB                                                  = 0x8246,
        DEBUG_SOURCE_WINDOW_SYSTEM_ARB                                        = 0x8247,
        DEBUG_SOURCE_SHADER_COMPILER_ARB                                      = 0x8248,
        DEBUG_SOURCE_THIRD_PARTY_ARB                                          = 0x8249,
        DEBUG_SOURCE_APPLICATION_ARB                                          = 0x824A,
        DEBUG_SOURCE_OTHER_ARB                                                = 0x824B,
        DEBUG_TYPE_ERROR_ARB                                                  = 0x824C,
        DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB                                    = 0x824D,
        DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB                                     = 0x824E,
        DEBUG_TYPE_PORTABILITY_ARB                                            = 0x824F,
        DEBUG_TYPE_PERFORMANCE_ARB                                            = 0x8250,
        DEBUG_TYPE_OTHER_ARB                                                  = 0x8251,
        MAX_DEBUG_MESSAGE_LENGTH_ARB                                          = 0x9143,
        MAX_DEBUG_LOGGED_MESSAGES_ARB                                         = 0x9144,
        DEBUG_LOGGED_MESSAGES_ARB                                             = 0x9145,
        DEBUG_SEVERITY_HIGH_ARB                                               = 0x9146,
        DEBUG_SEVERITY_MEDIUM_ARB                                             = 0x9147,
        DEBUG_SEVERITY_LOW_ARB                                                = 0x9148,
        DEPTH_COMPONENT32F                                                    = 0x8CAC,
        DEPTH32F_STENCIL8                                                     = 0x8CAD,
        FLOAT_32_UNSIGNED_INT_24_8_REV                                        = 0x8DAD,
        DEPTH_CLAMP                                                           = 0x864F,
        DEPTH_COMPONENT16_ARB                                                 = 0x81A5,
        DEPTH_COMPONENT24_ARB                                                 = 0x81A6,
        DEPTH_COMPONENT32_ARB                                                 = 0x81A7,
        TEXTURE_DEPTH_SIZE_ARB                                                = 0x884A,
        DEPTH_TEXTURE_MODE_ARB                                                = 0x884B,
        TEXTURE_TARGET                                                        = 0x1006,
        QUERY_TARGET                                                          = 0x82EA,
        MAX_DRAW_BUFFERS_ARB                                                  = 0x8824,
        DRAW_BUFFER0_ARB                                                      = 0x8825,
        DRAW_BUFFER1_ARB                                                      = 0x8826,
        DRAW_BUFFER2_ARB                                                      = 0x8827,
        DRAW_BUFFER3_ARB                                                      = 0x8828,
        DRAW_BUFFER4_ARB                                                      = 0x8829,
        DRAW_BUFFER5_ARB                                                      = 0x882A,
        DRAW_BUFFER6_ARB                                                      = 0x882B,
        DRAW_BUFFER7_ARB                                                      = 0x882C,
        DRAW_BUFFER8_ARB                                                      = 0x882D,
        DRAW_BUFFER9_ARB                                                      = 0x882E,
        DRAW_BUFFER10_ARB                                                     = 0x882F,
        DRAW_BUFFER11_ARB                                                     = 0x8830,
        DRAW_BUFFER12_ARB                                                     = 0x8831,
        DRAW_BUFFER13_ARB                                                     = 0x8832,
        DRAW_BUFFER14_ARB                                                     = 0x8833,
        DRAW_BUFFER15_ARB                                                     = 0x8834,
        DRAW_INDIRECT_BUFFER                                                  = 0x8F3F,
        DRAW_INDIRECT_BUFFER_BINDING                                          = 0x8F43,
        LOCATION_COMPONENT                                                    = 0x934A,
        TRANSFORM_FEEDBACK_BUFFER_INDEX                                       = 0x934B,
        TRANSFORM_FEEDBACK_BUFFER_STRIDE                                      = 0x934C,
        MAX_UNIFORM_LOCATIONS                                                 = 0x826E,
        FRAGMENT_PROGRAM_ARB                                                  = 0x8804,
        PROGRAM_ALU_INSTRUCTIONS_ARB                                          = 0x8805,
        PROGRAM_TEX_INSTRUCTIONS_ARB                                          = 0x8806,
        PROGRAM_TEX_INDIRECTIONS_ARB                                          = 0x8807,
        PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB                                   = 0x8808,
        PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB                                   = 0x8809,
        PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB                                   = 0x880A,
        MAX_PROGRAM_ALU_INSTRUCTIONS_ARB                                      = 0x880B,
        MAX_PROGRAM_TEX_INSTRUCTIONS_ARB                                      = 0x880C,
        MAX_PROGRAM_TEX_INDIRECTIONS_ARB                                      = 0x880D,
        MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB                               = 0x880E,
        MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB                               = 0x880F,
        MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB                               = 0x8810,
        MAX_TEXTURE_COORDS_ARB                                                = 0x8871,
        MAX_TEXTURE_IMAGE_UNITS_ARB                                           = 0x8872,
        FRAGMENT_SHADER_ARB                                                   = 0x8B30,
        MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB                                   = 0x8B49,
        FRAGMENT_SHADER_DERIVATIVE_HINT_ARB                                   = 0x8B8B,
        FRAMEBUFFER_DEFAULT_WIDTH                                             = 0x9310,
        FRAMEBUFFER_DEFAULT_HEIGHT                                            = 0x9311,
        FRAMEBUFFER_DEFAULT_LAYERS                                            = 0x9312,
        FRAMEBUFFER_DEFAULT_SAMPLES                                           = 0x9313,
        FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS                            = 0x9314,
        MAX_FRAMEBUFFER_WIDTH                                                 = 0x9315,
        MAX_FRAMEBUFFER_HEIGHT                                                = 0x9316,
        MAX_FRAMEBUFFER_LAYERS                                                = 0x9317,
        MAX_FRAMEBUFFER_SAMPLES                                               = 0x9318,
        INVALID_FRAMEBUFFER_OPERATION                                         = 0x506,
        FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING                                 = 0x8210,
        FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE                                 = 0x8211,
        FRAMEBUFFER_ATTACHMENT_RED_SIZE                                       = 0x8212,
        FRAMEBUFFER_ATTACHMENT_GREEN_SIZE                                     = 0x8213,
        FRAMEBUFFER_ATTACHMENT_BLUE_SIZE                                      = 0x8214,
        FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE                                     = 0x8215,
        FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE                                     = 0x8216,
        FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE                                   = 0x8217,
        FRAMEBUFFER_DEFAULT                                                   = 0x8218,
        FRAMEBUFFER_UNDEFINED                                                 = 0x8219,
        DEPTH_STENCIL_ATTACHMENT                                              = 0x821A,
        INDEX                                                                 = 0x8222,
        MAX_RENDERBUFFER_SIZE                                                 = 0x84E8,
        DEPTH_STENCIL                                                         = 0x84F9,
        UNSIGNED_INT_24_8                                                     = 0x84FA,
        DEPTH24_STENCIL8                                                      = 0x88F0,
        TEXTURE_STENCIL_SIZE                                                  = 0x88F1,
        UNSIGNED_NORMALIZED                                                   = 0x8C17,
        DRAW_FRAMEBUFFER_BINDING                                              = 0x8CA6,
        FRAMEBUFFER_BINDING                                                   = 0x8CA6,
        RENDERBUFFER_BINDING                                                  = 0x8CA7,
        READ_FRAMEBUFFER                                                      = 0x8CA8,
        DRAW_FRAMEBUFFER                                                      = 0x8CA9,
        READ_FRAMEBUFFER_BINDING                                              = 0x8CAA,
        RENDERBUFFER_SAMPLES                                                  = 0x8CAB,
        FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE                                    = 0x8CD0,
        FRAMEBUFFER_ATTACHMENT_OBJECT_NAME                                    = 0x8CD1,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL                                  = 0x8CD2,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE                          = 0x8CD3,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER                                  = 0x8CD4,
        FRAMEBUFFER_COMPLETE                                                  = 0x8CD5,
        FRAMEBUFFER_INCOMPLETE_ATTACHMENT                                     = 0x8CD6,
        FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT                             = 0x8CD7,
        FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER                                    = 0x8CDB,
        FRAMEBUFFER_INCOMPLETE_READ_BUFFER                                    = 0x8CDC,
        FRAMEBUFFER_UNSUPPORTED                                               = 0x8CDD,
        MAX_COLOR_ATTACHMENTS                                                 = 0x8CDF,
        COLOR_ATTACHMENT0                                                     = 0x8CE0,
        COLOR_ATTACHMENT1                                                     = 0x8CE1,
        COLOR_ATTACHMENT2                                                     = 0x8CE2,
        COLOR_ATTACHMENT3                                                     = 0x8CE3,
        COLOR_ATTACHMENT4                                                     = 0x8CE4,
        COLOR_ATTACHMENT5                                                     = 0x8CE5,
        COLOR_ATTACHMENT6                                                     = 0x8CE6,
        COLOR_ATTACHMENT7                                                     = 0x8CE7,
        COLOR_ATTACHMENT8                                                     = 0x8CE8,
        COLOR_ATTACHMENT9                                                     = 0x8CE9,
        COLOR_ATTACHMENT10                                                    = 0x8CEA,
        COLOR_ATTACHMENT11                                                    = 0x8CEB,
        COLOR_ATTACHMENT12                                                    = 0x8CEC,
        COLOR_ATTACHMENT13                                                    = 0x8CED,
        COLOR_ATTACHMENT14                                                    = 0x8CEE,
        COLOR_ATTACHMENT15                                                    = 0x8CEF,
        DEPTH_ATTACHMENT                                                      = 0x8D00,
        STENCIL_ATTACHMENT                                                    = 0x8D20,
        FRAMEBUFFER                                                           = 0x8D40,
        RENDERBUFFER                                                          = 0x8D41,
        RENDERBUFFER_WIDTH                                                    = 0x8D42,
        RENDERBUFFER_HEIGHT                                                   = 0x8D43,
        RENDERBUFFER_INTERNAL_FORMAT                                          = 0x8D44,
        STENCIL_INDEX1                                                        = 0x8D46,
        STENCIL_INDEX4                                                        = 0x8D47,
        STENCIL_INDEX8                                                        = 0x8D48,
        STENCIL_INDEX16                                                       = 0x8D49,
        RENDERBUFFER_RED_SIZE                                                 = 0x8D50,
        RENDERBUFFER_GREEN_SIZE                                               = 0x8D51,
        RENDERBUFFER_BLUE_SIZE                                                = 0x8D52,
        RENDERBUFFER_ALPHA_SIZE                                               = 0x8D53,
        RENDERBUFFER_DEPTH_SIZE                                               = 0x8D54,
        RENDERBUFFER_STENCIL_SIZE                                             = 0x8D55,
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE                                    = 0x8D56,
        MAX_SAMPLES                                                           = 0x8D57,
        FRAMEBUFFER_SRGB                                                      = 0x8DB9,
        LINES_ADJACENCY_ARB                                                   = 0xA,
        LINE_STRIP_ADJACENCY_ARB                                              = 0xB,
        TRIANGLES_ADJACENCY_ARB                                               = 0xC,
        TRIANGLE_STRIP_ADJACENCY_ARB                                          = 0xD,
        PROGRAM_POINT_SIZE_ARB                                                = 0x8642,
        MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB                                  = 0x8C29,
        FRAMEBUFFER_ATTACHMENT_LAYERED_ARB                                    = 0x8DA7,
        FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB                              = 0x8DA8,
        FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB                                = 0x8DA9,
        GEOMETRY_SHADER_ARB                                                   = 0x8DD9,
        GEOMETRY_VERTICES_OUT_ARB                                             = 0x8DDA,
        GEOMETRY_INPUT_TYPE_ARB                                               = 0x8DDB,
        GEOMETRY_OUTPUT_TYPE_ARB                                              = 0x8DDC,
        MAX_GEOMETRY_VARYING_COMPONENTS_ARB                                   = 0x8DDD,
        MAX_VERTEX_VARYING_COMPONENTS_ARB                                     = 0x8DDE,
        MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB                                   = 0x8DDF,
        MAX_GEOMETRY_OUTPUT_VERTICES_ARB                                      = 0x8DE0,
        MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB                              = 0x8DE1,
        PROGRAM_BINARY_RETRIEVABLE_HINT                                       = 0x8257,
        PROGRAM_BINARY_LENGTH                                                 = 0x8741,
        NUM_PROGRAM_BINARY_FORMATS                                            = 0x87FE,
        PROGRAM_BINARY_FORMATS                                                = 0x87FF,
        SHADER_BINARY_FORMAT_SPIR_V_ARB                                       = 0x9551,
        SPIR_V_BINARY_ARB                                                     = 0x9552,
        GEOMETRY_SHADER_INVOCATIONS                                           = 0x887F,
        MAX_GEOMETRY_SHADER_INVOCATIONS                                       = 0x8E5A,
        MIN_FRAGMENT_INTERPOLATION_OFFSET                                     = 0x8E5B,
        MAX_FRAGMENT_INTERPOLATION_OFFSET                                     = 0x8E5C,
        FRAGMENT_INTERPOLATION_OFFSET_BITS                                    = 0x8E5D,
        MAX_VERTEX_STREAMS                                                    = 0x8E71,
        DOUBLE_MAT2                                                           = 0x8F46,
        DOUBLE_MAT3                                                           = 0x8F47,
        DOUBLE_MAT4                                                           = 0x8F48,
        DOUBLE_MAT2x3                                                         = 0x8F49,
        DOUBLE_MAT2x4                                                         = 0x8F4A,
        DOUBLE_MAT3x2                                                         = 0x8F4B,
        DOUBLE_MAT3x4                                                         = 0x8F4C,
        DOUBLE_MAT4x2                                                         = 0x8F4D,
        DOUBLE_MAT4x3                                                         = 0x8F4E,
        DOUBLE_VEC2                                                           = 0x8FFC,
        DOUBLE_VEC3                                                           = 0x8FFD,
        DOUBLE_VEC4                                                           = 0x8FFE,
        INT64_ARB                                                             = 0x140E,
        INT64_VEC2_ARB                                                        = 0x8FE9,
        INT64_VEC3_ARB                                                        = 0x8FEA,
        INT64_VEC4_ARB                                                        = 0x8FEB,
        UNSIGNED_INT64_VEC2_ARB                                               = 0x8FF5,
        UNSIGNED_INT64_VEC3_ARB                                               = 0x8FF6,
        UNSIGNED_INT64_VEC4_ARB                                               = 0x8FF7,
        HALF_FLOAT_ARB                                                        = 0x140B,
        HALF_FLOAT                                                            = 0x140B,
        CONSTANT_COLOR                                                        = 0x8001,
        ONE_MINUS_CONSTANT_COLOR                                              = 0x8002,
        CONSTANT_ALPHA                                                        = 0x8003,
        ONE_MINUS_CONSTANT_ALPHA                                              = 0x8004,
        BLEND_COLOR                                                           = 0x8005,
        FUNC_ADD                                                              = 0x8006,
        MIN                                                                   = 0x8007,
        MAX                                                                   = 0x8008,
        BLEND_EQUATION                                                        = 0x8009,
        FUNC_SUBTRACT                                                         = 0x800A,
        FUNC_REVERSE_SUBTRACT                                                 = 0x800B,
        CONVOLUTION_1D                                                        = 0x8010,
        CONVOLUTION_2D                                                        = 0x8011,
        SEPARABLE_2D                                                          = 0x8012,
        CONVOLUTION_BORDER_MODE                                               = 0x8013,
        CONVOLUTION_FILTER_SCALE                                              = 0x8014,
        CONVOLUTION_FILTER_BIAS                                               = 0x8015,
        REDUCE                                                                = 0x8016,
        CONVOLUTION_FORMAT                                                    = 0x8017,
        CONVOLUTION_WIDTH                                                     = 0x8018,
        CONVOLUTION_HEIGHT                                                    = 0x8019,
        MAX_CONVOLUTION_WIDTH                                                 = 0x801A,
        MAX_CONVOLUTION_HEIGHT                                                = 0x801B,
        POST_CONVOLUTION_RED_SCALE                                            = 0x801C,
        POST_CONVOLUTION_GREEN_SCALE                                          = 0x801D,
        POST_CONVOLUTION_BLUE_SCALE                                           = 0x801E,
        POST_CONVOLUTION_ALPHA_SCALE                                          = 0x801F,
        POST_CONVOLUTION_RED_BIAS                                             = 0x8020,
        POST_CONVOLUTION_GREEN_BIAS                                           = 0x8021,
        POST_CONVOLUTION_BLUE_BIAS                                            = 0x8022,
        POST_CONVOLUTION_ALPHA_BIAS                                           = 0x8023,
        HISTOGRAM                                                             = 0x8024,
        PROXY_HISTOGRAM                                                       = 0x8025,
        HISTOGRAM_WIDTH                                                       = 0x8026,
        HISTOGRAM_FORMAT                                                      = 0x8027,
        HISTOGRAM_RED_SIZE                                                    = 0x8028,
        HISTOGRAM_GREEN_SIZE                                                  = 0x8029,
        HISTOGRAM_BLUE_SIZE                                                   = 0x802A,
        HISTOGRAM_ALPHA_SIZE                                                  = 0x802B,
        HISTOGRAM_LUMINANCE_SIZE                                              = 0x802C,
        HISTOGRAM_SINK                                                        = 0x802D,
        MINMAX                                                                = 0x802E,
        MINMAX_FORMAT                                                         = 0x802F,
        MINMAX_SINK                                                           = 0x8030,
        TABLE_TOO_LARGE                                                       = 0x8031,
        COLOR_MATRIX                                                          = 0x80B1,
        COLOR_MATRIX_STACK_DEPTH                                              = 0x80B2,
        MAX_COLOR_MATRIX_STACK_DEPTH                                          = 0x80B3,
        POST_COLOR_MATRIX_RED_SCALE                                           = 0x80B4,
        POST_COLOR_MATRIX_GREEN_SCALE                                         = 0x80B5,
        POST_COLOR_MATRIX_BLUE_SCALE                                          = 0x80B6,
        POST_COLOR_MATRIX_ALPHA_SCALE                                         = 0x80B7,
        POST_COLOR_MATRIX_RED_BIAS                                            = 0x80B8,
        POST_COLOR_MATRIX_GREEN_BIAS                                          = 0x80B9,
        POST_COLOR_MATRIX_BLUE_BIAS                                           = 0x80BA,
        POST_COLOR_MATRIX_ALPHA_BIAS                                          = 0x80BB,
        COLOR_TABLE                                                           = 0x80D0,
        POST_CONVOLUTION_COLOR_TABLE                                          = 0x80D1,
        POST_COLOR_MATRIX_COLOR_TABLE                                         = 0x80D2,
        PROXY_COLOR_TABLE                                                     = 0x80D3,
        PROXY_POST_CONVOLUTION_COLOR_TABLE                                    = 0x80D4,
        PROXY_POST_COLOR_MATRIX_COLOR_TABLE                                   = 0x80D5,
        COLOR_TABLE_SCALE                                                     = 0x80D6,
        COLOR_TABLE_BIAS                                                      = 0x80D7,
        COLOR_TABLE_FORMAT                                                    = 0x80D8,
        COLOR_TABLE_WIDTH                                                     = 0x80D9,
        COLOR_TABLE_RED_SIZE                                                  = 0x80DA,
        COLOR_TABLE_GREEN_SIZE                                                = 0x80DB,
        COLOR_TABLE_BLUE_SIZE                                                 = 0x80DC,
        COLOR_TABLE_ALPHA_SIZE                                                = 0x80DD,
        COLOR_TABLE_LUMINANCE_SIZE                                            = 0x80DE,
        COLOR_TABLE_INTENSITY_SIZE                                            = 0x80DF,
        IGNORE_BORDER                                                         = 0x8150,
        CONSTANT_BORDER                                                       = 0x8151,
        WRAP_BORDER                                                           = 0x8152,
        REPLICATE_BORDER                                                      = 0x8153,
        CONVOLUTION_BORDER_COLOR                                              = 0x8154,
        PARAMETER_BUFFER_ARB                                                  = 0x80EE,
        PARAMETER_BUFFER_BINDING_ARB                                          = 0x80EF,
        VERTEX_ATTRIB_ARRAY_DIVISOR_ARB                                       = 0x88FE,
        NUM_SAMPLE_COUNTS                                                     = 0x9380,
        INTERNALFORMAT_SUPPORTED                                              = 0x826F,
        INTERNALFORMAT_PREFERRED                                              = 0x8270,
        INTERNALFORMAT_RED_SIZE                                               = 0x8271,
        INTERNALFORMAT_GREEN_SIZE                                             = 0x8272,
        INTERNALFORMAT_BLUE_SIZE                                              = 0x8273,
        INTERNALFORMAT_ALPHA_SIZE                                             = 0x8274,
        INTERNALFORMAT_DEPTH_SIZE                                             = 0x8275,
        INTERNALFORMAT_STENCIL_SIZE                                           = 0x8276,
        INTERNALFORMAT_SHARED_SIZE                                            = 0x8277,
        INTERNALFORMAT_RED_TYPE                                               = 0x8278,
        INTERNALFORMAT_GREEN_TYPE                                             = 0x8279,
        INTERNALFORMAT_BLUE_TYPE                                              = 0x827A,
        INTERNALFORMAT_ALPHA_TYPE                                             = 0x827B,
        INTERNALFORMAT_DEPTH_TYPE                                             = 0x827C,
        INTERNALFORMAT_STENCIL_TYPE                                           = 0x827D,
        MAX_WIDTH                                                             = 0x827E,
        MAX_HEIGHT                                                            = 0x827F,
        MAX_DEPTH                                                             = 0x8280,
        MAX_LAYERS                                                            = 0x8281,
        MAX_COMBINED_DIMENSIONS                                               = 0x8282,
        COLOR_COMPONENTS                                                      = 0x8283,
        DEPTH_COMPONENTS                                                      = 0x8284,
        STENCIL_COMPONENTS                                                    = 0x8285,
        COLOR_RENDERABLE                                                      = 0x8286,
        DEPTH_RENDERABLE                                                      = 0x8287,
        STENCIL_RENDERABLE                                                    = 0x8288,
        FRAMEBUFFER_RENDERABLE                                                = 0x8289,
        FRAMEBUFFER_RENDERABLE_LAYERED                                        = 0x828A,
        FRAMEBUFFER_BLEND                                                     = 0x828B,
        READ_PIXELS                                                           = 0x828C,
        READ_PIXELS_FORMAT                                                    = 0x828D,
        READ_PIXELS_TYPE                                                      = 0x828E,
        TEXTURE_IMAGE_FORMAT                                                  = 0x828F,
        TEXTURE_IMAGE_TYPE                                                    = 0x8290,
        GET_TEXTURE_IMAGE_FORMAT                                              = 0x8291,
        GET_TEXTURE_IMAGE_TYPE                                                = 0x8292,
        MIPMAP                                                                = 0x8293,
        MANUAL_GENERATE_MIPMAP                                                = 0x8294,
        AUTO_GENERATE_MIPMAP                                                  = 0x8295,
        COLOR_ENCODING                                                        = 0x8296,
        SRGB_READ                                                             = 0x8297,
        SRGB_WRITE                                                            = 0x8298,
        SRGB_DECODE_ARB                                                       = 0x8299,
        FILTER                                                                = 0x829A,
        VERTEX_TEXTURE                                                        = 0x829B,
        TESS_CONTROL_TEXTURE                                                  = 0x829C,
        TESS_EVALUATION_TEXTURE                                               = 0x829D,
        GEOMETRY_TEXTURE                                                      = 0x829E,
        FRAGMENT_TEXTURE                                                      = 0x829F,
        COMPUTE_TEXTURE                                                       = 0x82A0,
        TEXTURE_SHADOW                                                        = 0x82A1,
        TEXTURE_GATHER                                                        = 0x82A2,
        TEXTURE_GATHER_SHADOW                                                 = 0x82A3,
        SHADER_IMAGE_LOAD                                                     = 0x82A4,
        SHADER_IMAGE_STORE                                                    = 0x82A5,
        SHADER_IMAGE_ATOMIC                                                   = 0x82A6,
        IMAGE_TEXEL_SIZE                                                      = 0x82A7,
        IMAGE_COMPATIBILITY_CLASS                                             = 0x82A8,
        IMAGE_PIXEL_FORMAT                                                    = 0x82A9,
        IMAGE_PIXEL_TYPE                                                      = 0x82AA,
        SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST                                   = 0x82AC,
        SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST                                 = 0x82AD,
        SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE                                  = 0x82AE,
        SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE                                = 0x82AF,
        TEXTURE_COMPRESSED_BLOCK_WIDTH                                        = 0x82B1,
        TEXTURE_COMPRESSED_BLOCK_HEIGHT                                       = 0x82B2,
        TEXTURE_COMPRESSED_BLOCK_SIZE                                         = 0x82B3,
        CLEAR_BUFFER                                                          = 0x82B4,
        TEXTURE_VIEW                                                          = 0x82B5,
        VIEW_COMPATIBILITY_CLASS                                              = 0x82B6,
        FULL_SUPPORT                                                          = 0x82B7,
        CAVEAT_SUPPORT                                                        = 0x82B8,
        IMAGE_CLASS_4_X_32                                                    = 0x82B9,
        IMAGE_CLASS_2_X_32                                                    = 0x82BA,
        IMAGE_CLASS_1_X_32                                                    = 0x82BB,
        IMAGE_CLASS_4_X_16                                                    = 0x82BC,
        IMAGE_CLASS_2_X_16                                                    = 0x82BD,
        IMAGE_CLASS_1_X_16                                                    = 0x82BE,
        IMAGE_CLASS_4_X_8                                                     = 0x82BF,
        IMAGE_CLASS_2_X_8                                                     = 0x82C0,
        IMAGE_CLASS_1_X_8                                                     = 0x82C1,
        IMAGE_CLASS_11_11_10                                                  = 0x82C2,
        IMAGE_CLASS_10_10_10_2                                                = 0x82C3,
        VIEW_CLASS_128_BITS                                                   = 0x82C4,
        VIEW_CLASS_96_BITS                                                    = 0x82C5,
        VIEW_CLASS_64_BITS                                                    = 0x82C6,
        VIEW_CLASS_48_BITS                                                    = 0x82C7,
        VIEW_CLASS_32_BITS                                                    = 0x82C8,
        VIEW_CLASS_24_BITS                                                    = 0x82C9,
        VIEW_CLASS_16_BITS                                                    = 0x82CA,
        VIEW_CLASS_8_BITS                                                     = 0x82CB,
        VIEW_CLASS_S3TC_DXT1_RGB                                              = 0x82CC,
        VIEW_CLASS_S3TC_DXT1_RGBA                                             = 0x82CD,
        VIEW_CLASS_S3TC_DXT3_RGBA                                             = 0x82CE,
        VIEW_CLASS_S3TC_DXT5_RGBA                                             = 0x82CF,
        VIEW_CLASS_RGTC1_RED                                                  = 0x82D0,
        VIEW_CLASS_RGTC2_RG                                                   = 0x82D1,
        VIEW_CLASS_BPTC_UNORM                                                 = 0x82D2,
        VIEW_CLASS_BPTC_FLOAT                                                 = 0x82D3,
        MIN_MAP_BUFFER_ALIGNMENT                                              = 0x90BC,
        MAP_INVALIDATE_RANGE_BIT                                              = 0x4,
        MAP_INVALIDATE_BUFFER_BIT                                             = 0x8,
        MAP_FLUSH_EXPLICIT_BIT                                                = 0x10,
        MAP_UNSYNCHRONIZED_BIT                                                = 0x20,
        MATRIX_PALETTE_ARB                                                    = 0x8840,
        MAX_MATRIX_PALETTE_STACK_DEPTH_ARB                                    = 0x8841,
        MAX_PALETTE_MATRICES_ARB                                              = 0x8842,
        CURRENT_PALETTE_MATRIX_ARB                                            = 0x8843,
        MATRIX_INDEX_ARRAY_ARB                                                = 0x8844,
        CURRENT_MATRIX_INDEX_ARB                                              = 0x8845,
        MATRIX_INDEX_ARRAY_SIZE_ARB                                           = 0x8846,
        MATRIX_INDEX_ARRAY_TYPE_ARB                                           = 0x8847,
        MATRIX_INDEX_ARRAY_STRIDE_ARB                                         = 0x8848,
        MATRIX_INDEX_ARRAY_POINTER_ARB                                        = 0x8849,
        MULTISAMPLE_ARB                                                       = 0x809D,
        SAMPLE_ALPHA_TO_COVERAGE_ARB                                          = 0x809E,
        SAMPLE_ALPHA_TO_ONE_ARB                                               = 0x809F,
        SAMPLE_COVERAGE_ARB                                                   = 0x80A0,
        SAMPLE_BUFFERS_ARB                                                    = 0x80A8,
        SAMPLES_ARB                                                           = 0x80A9,
        SAMPLE_COVERAGE_VALUE_ARB                                             = 0x80AA,
        SAMPLE_COVERAGE_INVERT_ARB                                            = 0x80AB,
        MULTISAMPLE_BIT_ARB                                                   = 0x20000000,
        TEXTURE0_ARB                                                          = 0x84C0,
        TEXTURE1_ARB                                                          = 0x84C1,
        TEXTURE2_ARB                                                          = 0x84C2,
        TEXTURE3_ARB                                                          = 0x84C3,
        TEXTURE4_ARB                                                          = 0x84C4,
        TEXTURE5_ARB                                                          = 0x84C5,
        TEXTURE6_ARB                                                          = 0x84C6,
        TEXTURE7_ARB                                                          = 0x84C7,
        TEXTURE8_ARB                                                          = 0x84C8,
        TEXTURE9_ARB                                                          = 0x84C9,
        TEXTURE10_ARB                                                         = 0x84CA,
        TEXTURE11_ARB                                                         = 0x84CB,
        TEXTURE12_ARB                                                         = 0x84CC,
        TEXTURE13_ARB                                                         = 0x84CD,
        TEXTURE14_ARB                                                         = 0x84CE,
        TEXTURE15_ARB                                                         = 0x84CF,
        TEXTURE16_ARB                                                         = 0x84D0,
        TEXTURE17_ARB                                                         = 0x84D1,
        TEXTURE18_ARB                                                         = 0x84D2,
        TEXTURE19_ARB                                                         = 0x84D3,
        TEXTURE20_ARB                                                         = 0x84D4,
        TEXTURE21_ARB                                                         = 0x84D5,
        TEXTURE22_ARB                                                         = 0x84D6,
        TEXTURE23_ARB                                                         = 0x84D7,
        TEXTURE24_ARB                                                         = 0x84D8,
        TEXTURE25_ARB                                                         = 0x84D9,
        TEXTURE26_ARB                                                         = 0x84DA,
        TEXTURE27_ARB                                                         = 0x84DB,
        TEXTURE28_ARB                                                         = 0x84DC,
        TEXTURE29_ARB                                                         = 0x84DD,
        TEXTURE30_ARB                                                         = 0x84DE,
        TEXTURE31_ARB                                                         = 0x84DF,
        ACTIVE_TEXTURE_ARB                                                    = 0x84E0,
        CLIENT_ACTIVE_TEXTURE_ARB                                             = 0x84E1,
        MAX_TEXTURE_UNITS_ARB                                                 = 0x84E2,
        QUERY_COUNTER_BITS_ARB                                                = 0x8864,
        CURRENT_QUERY_ARB                                                     = 0x8865,
        QUERY_RESULT_ARB                                                      = 0x8866,
        QUERY_RESULT_AVAILABLE_ARB                                            = 0x8867,
        SAMPLES_PASSED_ARB                                                    = 0x8914,
        ANY_SAMPLES_PASSED                                                    = 0x8C2F,
        MAX_SHADER_COMPILER_THREADS_ARB                                       = 0x91B0,
        COMPLETION_STATUS_ARB                                                 = 0x91B1,
        VERTICES_SUBMITTED_ARB                                                = 0x82EE,
        PRIMITIVES_SUBMITTED_ARB                                              = 0x82EF,
        VERTEX_SHADER_INVOCATIONS_ARB                                         = 0x82F0,
        TESS_CONTROL_SHADER_PATCHES_ARB                                       = 0x82F1,
        TESS_EVALUATION_SHADER_INVOCATIONS_ARB                                = 0x82F2,
        GEOMETRY_SHADER_PRIMITIVES_EMITTED_ARB                                = 0x82F3,
        FRAGMENT_SHADER_INVOCATIONS_ARB                                       = 0x82F4,
        COMPUTE_SHADER_INVOCATIONS_ARB                                        = 0x82F5,
        CLIPPING_INPUT_PRIMITIVES_ARB                                         = 0x82F6,
        CLIPPING_OUTPUT_PRIMITIVES_ARB                                        = 0x82F7,
        PIXEL_PACK_BUFFER_ARB                                                 = 0x88EB,
        PIXEL_UNPACK_BUFFER_ARB                                               = 0x88EC,
        PIXEL_PACK_BUFFER_BINDING_ARB                                         = 0x88ED,
        PIXEL_UNPACK_BUFFER_BINDING_ARB                                       = 0x88EF,
        POINT_SIZE_MIN_ARB                                                    = 0x8126,
        POINT_SIZE_MAX_ARB                                                    = 0x8127,
        POINT_FADE_THRESHOLD_SIZE_ARB                                         = 0x8128,
        POINT_DISTANCE_ATTENUATION_ARB                                        = 0x8129,
        POINT_SPRITE_ARB                                                      = 0x8861,
        COORD_REPLACE_ARB                                                     = 0x8862,
        UNIFORM                                                               = 0x92E1,
        UNIFORM_BLOCK                                                         = 0x92E2,
        PROGRAM_INPUT                                                         = 0x92E3,
        PROGRAM_OUTPUT                                                        = 0x92E4,
        BUFFER_VARIABLE                                                       = 0x92E5,
        SHADER_STORAGE_BLOCK                                                  = 0x92E6,
        IS_PER_PATCH                                                          = 0x92E7,
        VERTEX_SUBROUTINE                                                     = 0x92E8,
        TESS_CONTROL_SUBROUTINE                                               = 0x92E9,
        TESS_EVALUATION_SUBROUTINE                                            = 0x92EA,
        GEOMETRY_SUBROUTINE                                                   = 0x92EB,
        FRAGMENT_SUBROUTINE                                                   = 0x92EC,
        COMPUTE_SUBROUTINE                                                    = 0x92ED,
        VERTEX_SUBROUTINE_UNIFORM                                             = 0x92EE,
        TESS_CONTROL_SUBROUTINE_UNIFORM                                       = 0x92EF,
        TESS_EVALUATION_SUBROUTINE_UNIFORM                                    = 0x92F0,
        GEOMETRY_SUBROUTINE_UNIFORM                                           = 0x92F1,
        FRAGMENT_SUBROUTINE_UNIFORM                                           = 0x92F2,
        COMPUTE_SUBROUTINE_UNIFORM                                            = 0x92F3,
        TRANSFORM_FEEDBACK_VARYING                                            = 0x92F4,
        ACTIVE_RESOURCES                                                      = 0x92F5,
        MAX_NAME_LENGTH                                                       = 0x92F6,
        MAX_NUM_ACTIVE_VARIABLES                                              = 0x92F7,
        MAX_NUM_COMPATIBLE_SUBROUTINES                                        = 0x92F8,
        NAME_LENGTH                                                           = 0x92F9,
        TYPE                                                                  = 0x92FA,
        ARRAY_SIZE                                                            = 0x92FB,
        OFFSET                                                                = 0x92FC,
        BLOCK_INDEX                                                           = 0x92FD,
        ARRAY_STRIDE                                                          = 0x92FE,
        MATRIX_STRIDE                                                         = 0x92FF,
        IS_ROW_MAJOR                                                          = 0x9300,
        ATOMIC_COUNTER_BUFFER_INDEX                                           = 0x9301,
        BUFFER_BINDING                                                        = 0x9302,
        BUFFER_DATA_SIZE                                                      = 0x9303,
        NUM_ACTIVE_VARIABLES                                                  = 0x9304,
        ACTIVE_VARIABLES                                                      = 0x9305,
        REFERENCED_BY_VERTEX_SHADER                                           = 0x9306,
        REFERENCED_BY_TESS_CONTROL_SHADER                                     = 0x9307,
        REFERENCED_BY_TESS_EVALUATION_SHADER                                  = 0x9308,
        REFERENCED_BY_GEOMETRY_SHADER                                         = 0x9309,
        REFERENCED_BY_FRAGMENT_SHADER                                         = 0x930A,
        REFERENCED_BY_COMPUTE_SHADER                                          = 0x930B,
        TOP_LEVEL_ARRAY_SIZE                                                  = 0x930C,
        TOP_LEVEL_ARRAY_STRIDE                                                = 0x930D,
        LOCATION                                                              = 0x930E,
        LOCATION_INDEX                                                        = 0x930F,
        QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION                              = 0x8E4C,
        FIRST_VERTEX_CONVENTION                                               = 0x8E4D,
        LAST_VERTEX_CONVENTION                                                = 0x8E4E,
        PROVOKING_VERTEX                                                      = 0x8E4F,
        QUERY_BUFFER_BARRIER_BIT                                              = 0x8000,
        QUERY_BUFFER                                                          = 0x9192,
        QUERY_BUFFER_BINDING                                                  = 0x9193,
        QUERY_RESULT_NO_WAIT                                                  = 0x9194,
        CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB                                    = 0x4,
        LOSE_CONTEXT_ON_RESET_ARB                                             = 0x8252,
        GUILTY_CONTEXT_RESET_ARB                                              = 0x8253,
        INNOCENT_CONTEXT_RESET_ARB                                            = 0x8254,
        UNKNOWN_CONTEXT_RESET_ARB                                             = 0x8255,
        RESET_NOTIFICATION_STRATEGY_ARB                                       = 0x8256,
        NO_RESET_NOTIFICATION_ARB                                             = 0x8261,
        SAMPLE_LOCATION_ARB                                                   = 0x8E50,
        SAMPLE_LOCATION_SUBPIXEL_BITS_ARB                                     = 0x933D,
        SAMPLE_LOCATION_PIXEL_GRID_WIDTH_ARB                                  = 0x933E,
        SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_ARB                                 = 0x933F,
        PROGRAMMABLE_SAMPLE_LOCATION_TABLE_SIZE_ARB                           = 0x9340,
        PROGRAMMABLE_SAMPLE_LOCATION_ARB                                      = 0x9341,
        FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_ARB                         = 0x9342,
        FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_ARB                            = 0x9343,
        SAMPLE_SHADING_ARB                                                    = 0x8C36,
        MIN_SAMPLE_SHADING_VALUE_ARB                                          = 0x8C37,
        SAMPLER_BINDING                                                       = 0x8919,
        VERTEX_SHADER_BIT                                                     = 0x1,
        FRAGMENT_SHADER_BIT                                                   = 0x2,
        GEOMETRY_SHADER_BIT                                                   = 0x4,
        TESS_CONTROL_SHADER_BIT                                               = 0x8,
        TESS_EVALUATION_SHADER_BIT                                            = 0x10,
        PROGRAM_SEPARABLE                                                     = 0x8258,
        ACTIVE_PROGRAM                                                        = 0x8259,
        PROGRAM_PIPELINE_BINDING                                              = 0x825A,
        ALL_SHADER_BITS                                                       = 0xFFFFFFFF,
        ATOMIC_COUNTER_BUFFER                                                 = 0x92C0,
        ATOMIC_COUNTER_BUFFER_BINDING                                         = 0x92C1,
        ATOMIC_COUNTER_BUFFER_START                                           = 0x92C2,
        ATOMIC_COUNTER_BUFFER_SIZE                                            = 0x92C3,
        ATOMIC_COUNTER_BUFFER_DATA_SIZE                                       = 0x92C4,
        ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS                          = 0x92C5,
        ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES                   = 0x92C6,
        ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER                     = 0x92C7,
        ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER               = 0x92C8,
        ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER            = 0x92C9,
        ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER                   = 0x92CA,
        ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER                   = 0x92CB,
        MAX_VERTEX_ATOMIC_COUNTER_BUFFERS                                     = 0x92CC,
        MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS                               = 0x92CD,
        MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS                            = 0x92CE,
        MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS                                   = 0x92CF,
        MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS                                   = 0x92D0,
        MAX_COMBINED_ATOMIC_COUNTER_BUFFERS                                   = 0x92D1,
        MAX_VERTEX_ATOMIC_COUNTERS                                            = 0x92D2,
        MAX_TESS_CONTROL_ATOMIC_COUNTERS                                      = 0x92D3,
        MAX_TESS_EVALUATION_ATOMIC_COUNTERS                                   = 0x92D4,
        MAX_GEOMETRY_ATOMIC_COUNTERS                                          = 0x92D5,
        MAX_FRAGMENT_ATOMIC_COUNTERS                                          = 0x92D6,
        MAX_COMBINED_ATOMIC_COUNTERS                                          = 0x92D7,
        MAX_ATOMIC_COUNTER_BUFFER_SIZE                                        = 0x92D8,
        ACTIVE_ATOMIC_COUNTER_BUFFERS                                         = 0x92D9,
        UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX                                   = 0x92DA,
        UNSIGNED_INT_ATOMIC_COUNTER                                           = 0x92DB,
        MAX_ATOMIC_COUNTER_BUFFER_BINDINGS                                    = 0x92DC,
        VERTEX_ATTRIB_ARRAY_BARRIER_BIT                                       = 0x1,
        ELEMENT_ARRAY_BARRIER_BIT                                             = 0x2,
        UNIFORM_BARRIER_BIT                                                   = 0x4,
        TEXTURE_FETCH_BARRIER_BIT                                             = 0x8,
        SHADER_IMAGE_ACCESS_BARRIER_BIT                                       = 0x20,
        COMMAND_BARRIER_BIT                                                   = 0x40,
        PIXEL_BUFFER_BARRIER_BIT                                              = 0x80,
        TEXTURE_UPDATE_BARRIER_BIT                                            = 0x100,
        BUFFER_UPDATE_BARRIER_BIT                                             = 0x200,
        FRAMEBUFFER_BARRIER_BIT                                               = 0x400,
        TRANSFORM_FEEDBACK_BARRIER_BIT                                        = 0x800,
        ATOMIC_COUNTER_BARRIER_BIT                                            = 0x1000,
        MAX_IMAGE_UNITS                                                       = 0x8F38,
        MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS                         = 0x8F39,
        IMAGE_BINDING_NAME                                                    = 0x8F3A,
        IMAGE_BINDING_LEVEL                                                   = 0x8F3B,
        IMAGE_BINDING_LAYERED                                                 = 0x8F3C,
        IMAGE_BINDING_LAYER                                                   = 0x8F3D,
        IMAGE_BINDING_ACCESS                                                  = 0x8F3E,
        IMAGE_1D                                                              = 0x904C,
        IMAGE_2D                                                              = 0x904D,
        IMAGE_3D                                                              = 0x904E,
        IMAGE_2D_RECT                                                         = 0x904F,
        IMAGE_CUBE                                                            = 0x9050,
        IMAGE_BUFFER                                                          = 0x9051,
        IMAGE_1D_ARRAY                                                        = 0x9052,
        IMAGE_2D_ARRAY                                                        = 0x9053,
        IMAGE_CUBE_MAP_ARRAY                                                  = 0x9054,
        IMAGE_2D_MULTISAMPLE                                                  = 0x9055,
        IMAGE_2D_MULTISAMPLE_ARRAY                                            = 0x9056,
        INT_IMAGE_1D                                                          = 0x9057,
        INT_IMAGE_2D                                                          = 0x9058,
        INT_IMAGE_3D                                                          = 0x9059,
        INT_IMAGE_2D_RECT                                                     = 0x905A,
        INT_IMAGE_CUBE                                                        = 0x905B,
        INT_IMAGE_BUFFER                                                      = 0x905C,
        INT_IMAGE_1D_ARRAY                                                    = 0x905D,
        INT_IMAGE_2D_ARRAY                                                    = 0x905E,
        INT_IMAGE_CUBE_MAP_ARRAY                                              = 0x905F,
        INT_IMAGE_2D_MULTISAMPLE                                              = 0x9060,
        INT_IMAGE_2D_MULTISAMPLE_ARRAY                                        = 0x9061,
        UNSIGNED_INT_IMAGE_1D                                                 = 0x9062,
        UNSIGNED_INT_IMAGE_2D                                                 = 0x9063,
        UNSIGNED_INT_IMAGE_3D                                                 = 0x9064,
        UNSIGNED_INT_IMAGE_2D_RECT                                            = 0x9065,
        UNSIGNED_INT_IMAGE_CUBE                                               = 0x9066,
        UNSIGNED_INT_IMAGE_BUFFER                                             = 0x9067,
        UNSIGNED_INT_IMAGE_1D_ARRAY                                           = 0x9068,
        UNSIGNED_INT_IMAGE_2D_ARRAY                                           = 0x9069,
        UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY                                     = 0x906A,
        UNSIGNED_INT_IMAGE_2D_MULTISAMPLE                                     = 0x906B,
        UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY                               = 0x906C,
        MAX_IMAGE_SAMPLES                                                     = 0x906D,
        IMAGE_BINDING_FORMAT                                                  = 0x906E,
        IMAGE_FORMAT_COMPATIBILITY_TYPE                                       = 0x90C7,
        IMAGE_FORMAT_COMPATIBILITY_BY_SIZE                                    = 0x90C8,
        IMAGE_FORMAT_COMPATIBILITY_BY_CLASS                                   = 0x90C9,
        MAX_VERTEX_IMAGE_UNIFORMS                                             = 0x90CA,
        MAX_TESS_CONTROL_IMAGE_UNIFORMS                                       = 0x90CB,
        MAX_TESS_EVALUATION_IMAGE_UNIFORMS                                    = 0x90CC,
        MAX_GEOMETRY_IMAGE_UNIFORMS                                           = 0x90CD,
        MAX_FRAGMENT_IMAGE_UNIFORMS                                           = 0x90CE,
        MAX_COMBINED_IMAGE_UNIFORMS                                           = 0x90CF,
        ALL_BARRIER_BITS                                                      = 0xFFFFFFFF,
        PROGRAM_OBJECT_ARB                                                    = 0x8B40,
        SHADER_OBJECT_ARB                                                     = 0x8B48,
        OBJECT_TYPE_ARB                                                       = 0x8B4E,
        OBJECT_SUBTYPE_ARB                                                    = 0x8B4F,
        FLOAT_VEC2_ARB                                                        = 0x8B50,
        FLOAT_VEC3_ARB                                                        = 0x8B51,
        FLOAT_VEC4_ARB                                                        = 0x8B52,
        INT_VEC2_ARB                                                          = 0x8B53,
        INT_VEC3_ARB                                                          = 0x8B54,
        INT_VEC4_ARB                                                          = 0x8B55,
        BOOL_ARB                                                              = 0x8B56,
        BOOL_VEC2_ARB                                                         = 0x8B57,
        BOOL_VEC3_ARB                                                         = 0x8B58,
        BOOL_VEC4_ARB                                                         = 0x8B59,
        FLOAT_MAT2_ARB                                                        = 0x8B5A,
        FLOAT_MAT3_ARB                                                        = 0x8B5B,
        FLOAT_MAT4_ARB                                                        = 0x8B5C,
        SAMPLER_1D_ARB                                                        = 0x8B5D,
        SAMPLER_2D_ARB                                                        = 0x8B5E,
        SAMPLER_3D_ARB                                                        = 0x8B5F,
        SAMPLER_CUBE_ARB                                                      = 0x8B60,
        SAMPLER_1D_SHADOW_ARB                                                 = 0x8B61,
        SAMPLER_2D_SHADOW_ARB                                                 = 0x8B62,
        SAMPLER_2D_RECT_ARB                                                   = 0x8B63,
        SAMPLER_2D_RECT_SHADOW_ARB                                            = 0x8B64,
        OBJECT_DELETE_STATUS_ARB                                              = 0x8B80,
        OBJECT_COMPILE_STATUS_ARB                                             = 0x8B81,
        OBJECT_LINK_STATUS_ARB                                                = 0x8B82,
        OBJECT_VALIDATE_STATUS_ARB                                            = 0x8B83,
        OBJECT_INFO_LOG_LENGTH_ARB                                            = 0x8B84,
        OBJECT_ATTACHED_OBJECTS_ARB                                           = 0x8B85,
        OBJECT_ACTIVE_UNIFORMS_ARB                                            = 0x8B86,
        OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB                                  = 0x8B87,
        OBJECT_SHADER_SOURCE_LENGTH_ARB                                       = 0x8B88,
        SHADER_STORAGE_BARRIER_BIT                                            = 0x2000,
        MAX_COMBINED_SHADER_OUTPUT_RESOURCES                                  = 0x8F39,
        SHADER_STORAGE_BUFFER                                                 = 0x90D2,
        SHADER_STORAGE_BUFFER_BINDING                                         = 0x90D3,
        SHADER_STORAGE_BUFFER_START                                           = 0x90D4,
        SHADER_STORAGE_BUFFER_SIZE                                            = 0x90D5,
        MAX_VERTEX_SHADER_STORAGE_BLOCKS                                      = 0x90D6,
        MAX_GEOMETRY_SHADER_STORAGE_BLOCKS                                    = 0x90D7,
        MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS                                = 0x90D8,
        MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS                             = 0x90D9,
        MAX_FRAGMENT_SHADER_STORAGE_BLOCKS                                    = 0x90DA,
        MAX_COMPUTE_SHADER_STORAGE_BLOCKS                                     = 0x90DB,
        MAX_COMBINED_SHADER_STORAGE_BLOCKS                                    = 0x90DC,
        MAX_SHADER_STORAGE_BUFFER_BINDINGS                                    = 0x90DD,
        MAX_SHADER_STORAGE_BLOCK_SIZE                                         = 0x90DE,
        SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT                                = 0x90DF,
        ACTIVE_SUBROUTINES                                                    = 0x8DE5,
        ACTIVE_SUBROUTINE_UNIFORMS                                            = 0x8DE6,
        MAX_SUBROUTINES                                                       = 0x8DE7,
        MAX_SUBROUTINE_UNIFORM_LOCATIONS                                      = 0x8DE8,
        ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS                                   = 0x8E47,
        ACTIVE_SUBROUTINE_MAX_LENGTH                                          = 0x8E48,
        ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH                                  = 0x8E49,
        NUM_COMPATIBLE_SUBROUTINES                                            = 0x8E4A,
        COMPATIBLE_SUBROUTINES                                                = 0x8E4B,
        SHADING_LANGUAGE_VERSION_ARB                                          = 0x8B8C,
        SHADER_INCLUDE_ARB                                                    = 0x8DAE,
        NAMED_STRING_LENGTH_ARB                                               = 0x8DE9,
        NAMED_STRING_TYPE_ARB                                                 = 0x8DEA,
        TEXTURE_COMPARE_MODE_ARB                                              = 0x884C,
        TEXTURE_COMPARE_FUNC_ARB                                              = 0x884D,
        COMPARE_R_TO_TEXTURE_ARB                                              = 0x884E,
        TEXTURE_COMPARE_FAIL_VALUE_ARB                                        = 0x80BF,
        SPARSE_STORAGE_BIT_ARB                                                = 0x400,
        SPARSE_BUFFER_PAGE_SIZE_ARB                                           = 0x82F8,
        VIRTUAL_PAGE_SIZE_X_ARB                                               = 0x9195,
        VIRTUAL_PAGE_SIZE_Y_ARB                                               = 0x9196,
        VIRTUAL_PAGE_SIZE_Z_ARB                                               = 0x9197,
        MAX_SPARSE_TEXTURE_SIZE_ARB                                           = 0x9198,
        MAX_SPARSE_3D_TEXTURE_SIZE_ARB                                        = 0x9199,
        MAX_SPARSE_ARRAY_TEXTURE_LAYERS_ARB                                   = 0x919A,
        TEXTURE_SPARSE_ARB                                                    = 0x91A6,
        VIRTUAL_PAGE_SIZE_INDEX_ARB                                           = 0x91A7,
        NUM_VIRTUAL_PAGE_SIZES_ARB                                            = 0x91A8,
        SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_ARB                            = 0x91A9,
        NUM_SPARSE_LEVELS_ARB                                                 = 0x91AA,
        DEPTH_STENCIL_TEXTURE_MODE                                            = 0x90EA,
        SYNC_FLUSH_COMMANDS_BIT                                               = 0x1,
        MAX_SERVER_WAIT_TIMEOUT                                               = 0x9111,
        OBJECT_TYPE                                                           = 0x9112,
        SYNC_CONDITION                                                        = 0x9113,
        SYNC_STATUS                                                           = 0x9114,
        SYNC_FLAGS                                                            = 0x9115,
        SYNC_FENCE                                                            = 0x9116,
        SYNC_GPU_COMMANDS_COMPLETE                                            = 0x9117,
        UNSIGNALED                                                            = 0x9118,
        SIGNALED                                                              = 0x9119,
        ALREADY_SIGNALED                                                      = 0x911A,
        TIMEOUT_EXPIRED                                                       = 0x911B,
        CONDITION_SATISFIED                                                   = 0x911C,
        WAIT_FAILED                                                           = 0x911D,
        TIMEOUT_IGNORED                                                       = 0xFFFFFFFFFFFFFFFF,
        PATCHES                                                               = 0xE,
        UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER                       = 0x84F0,
        UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER                    = 0x84F1,
        MAX_TESS_CONTROL_INPUT_COMPONENTS                                     = 0x886C,
        MAX_TESS_EVALUATION_INPUT_COMPONENTS                                  = 0x886D,
        MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS                          = 0x8E1E,
        MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS                       = 0x8E1F,
        PATCH_VERTICES                                                        = 0x8E72,
        PATCH_DEFAULT_INNER_LEVEL                                             = 0x8E73,
        PATCH_DEFAULT_OUTER_LEVEL                                             = 0x8E74,
        TESS_CONTROL_OUTPUT_VERTICES                                          = 0x8E75,
        TESS_GEN_MODE                                                         = 0x8E76,
        TESS_GEN_SPACING                                                      = 0x8E77,
        TESS_GEN_VERTEX_ORDER                                                 = 0x8E78,
        TESS_GEN_POINT_MODE                                                   = 0x8E79,
        ISOLINES                                                              = 0x8E7A,
        FRACTIONAL_ODD                                                        = 0x8E7B,
        FRACTIONAL_EVEN                                                       = 0x8E7C,
        MAX_PATCH_VERTICES                                                    = 0x8E7D,
        MAX_TESS_GEN_LEVEL                                                    = 0x8E7E,
        MAX_TESS_CONTROL_UNIFORM_COMPONENTS                                   = 0x8E7F,
        MAX_TESS_EVALUATION_UNIFORM_COMPONENTS                                = 0x8E80,
        MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS                                  = 0x8E81,
        MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS                               = 0x8E82,
        MAX_TESS_CONTROL_OUTPUT_COMPONENTS                                    = 0x8E83,
        MAX_TESS_PATCH_COMPONENTS                                             = 0x8E84,
        MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS                              = 0x8E85,
        MAX_TESS_EVALUATION_OUTPUT_COMPONENTS                                 = 0x8E86,
        TESS_EVALUATION_SHADER                                                = 0x8E87,
        TESS_CONTROL_SHADER                                                   = 0x8E88,
        MAX_TESS_CONTROL_UNIFORM_BLOCKS                                       = 0x8E89,
        MAX_TESS_EVALUATION_UNIFORM_BLOCKS                                    = 0x8E8A,
        CLAMP_TO_BORDER_ARB                                                   = 0x812D,
        TEXTURE_BUFFER_ARB                                                    = 0x8C2A,
        MAX_TEXTURE_BUFFER_SIZE_ARB                                           = 0x8C2B,
        TEXTURE_BINDING_BUFFER_ARB                                            = 0x8C2C,
        TEXTURE_BUFFER_DATA_STORE_BINDING_ARB                                 = 0x8C2D,
        TEXTURE_BUFFER_FORMAT_ARB                                             = 0x8C2E,
        TEXTURE_BUFFER_OFFSET                                                 = 0x919D,
        TEXTURE_BUFFER_SIZE                                                   = 0x919E,
        TEXTURE_BUFFER_OFFSET_ALIGNMENT                                       = 0x919F,
        COMPRESSED_ALPHA_ARB                                                  = 0x84E9,
        COMPRESSED_LUMINANCE_ARB                                              = 0x84EA,
        COMPRESSED_LUMINANCE_ALPHA_ARB                                        = 0x84EB,
        COMPRESSED_INTENSITY_ARB                                              = 0x84EC,
        COMPRESSED_RGB_ARB                                                    = 0x84ED,
        COMPRESSED_RGBA_ARB                                                   = 0x84EE,
        TEXTURE_COMPRESSION_HINT_ARB                                          = 0x84EF,
        TEXTURE_COMPRESSED_IMAGE_SIZE_ARB                                     = 0x86A0,
        TEXTURE_COMPRESSED_ARB                                                = 0x86A1,
        NUM_COMPRESSED_TEXTURE_FORMATS_ARB                                    = 0x86A2,
        COMPRESSED_TEXTURE_FORMATS_ARB                                        = 0x86A3,
        COMPRESSED_RGBA_BPTC_UNORM_ARB                                        = 0x8E8C,
        COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB                                  = 0x8E8D,
        COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB                                  = 0x8E8E,
        COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB                                = 0x8E8F,
        COMPRESSED_RED_RGTC1                                                  = 0x8DBB,
        COMPRESSED_SIGNED_RED_RGTC1                                           = 0x8DBC,
        COMPRESSED_RG_RGTC2                                                   = 0x8DBD,
        COMPRESSED_SIGNED_RG_RGTC2                                            = 0x8DBE,
        NORMAL_MAP_ARB                                                        = 0x8511,
        REFLECTION_MAP_ARB                                                    = 0x8512,
        TEXTURE_CUBE_MAP_ARB                                                  = 0x8513,
        TEXTURE_BINDING_CUBE_MAP_ARB                                          = 0x8514,
        TEXTURE_CUBE_MAP_POSITIVE_X_ARB                                       = 0x8515,
        TEXTURE_CUBE_MAP_NEGATIVE_X_ARB                                       = 0x8516,
        TEXTURE_CUBE_MAP_POSITIVE_Y_ARB                                       = 0x8517,
        TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB                                       = 0x8518,
        TEXTURE_CUBE_MAP_POSITIVE_Z_ARB                                       = 0x8519,
        TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB                                       = 0x851A,
        PROXY_TEXTURE_CUBE_MAP_ARB                                            = 0x851B,
        MAX_CUBE_MAP_TEXTURE_SIZE_ARB                                         = 0x851C,
        TEXTURE_CUBE_MAP_ARRAY_ARB                                            = 0x9009,
        TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB                                    = 0x900A,
        PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB                                      = 0x900B,
        SAMPLER_CUBE_MAP_ARRAY_ARB                                            = 0x900C,
        SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB                                     = 0x900D,
        INT_SAMPLER_CUBE_MAP_ARRAY_ARB                                        = 0x900E,
        UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB                               = 0x900F,
        SUBTRACT_ARB                                                          = 0x84E7,
        COMBINE_ARB                                                           = 0x8570,
        COMBINE_RGB_ARB                                                       = 0x8571,
        COMBINE_ALPHA_ARB                                                     = 0x8572,
        RGB_SCALE_ARB                                                         = 0x8573,
        ADD_SIGNED_ARB                                                        = 0x8574,
        INTERPOLATE_ARB                                                       = 0x8575,
        CONSTANT_ARB                                                          = 0x8576,
        PRIMARY_COLOR_ARB                                                     = 0x8577,
        PREVIOUS_ARB                                                          = 0x8578,
        SOURCE0_RGB_ARB                                                       = 0x8580,
        SOURCE1_RGB_ARB                                                       = 0x8581,
        SOURCE2_RGB_ARB                                                       = 0x8582,
        SOURCE0_ALPHA_ARB                                                     = 0x8588,
        SOURCE1_ALPHA_ARB                                                     = 0x8589,
        SOURCE2_ALPHA_ARB                                                     = 0x858A,
        OPERAND0_RGB_ARB                                                      = 0x8590,
        OPERAND1_RGB_ARB                                                      = 0x8591,
        OPERAND2_RGB_ARB                                                      = 0x8592,
        OPERAND0_ALPHA_ARB                                                    = 0x8598,
        OPERAND1_ALPHA_ARB                                                    = 0x8599,
        OPERAND2_ALPHA_ARB                                                    = 0x859A,
        DOT3_RGB_ARB                                                          = 0x86AE,
        DOT3_RGBA_ARB                                                         = 0x86AF,
        TEXTURE_REDUCTION_MODE_ARB                                            = 0x9366,
        WEIGHTED_AVERAGE_ARB                                                  = 0x9367,
        RGBA32F_ARB                                                           = 0x8814,
        RGB32F_ARB                                                            = 0x8815,
        ALPHA32F_ARB                                                          = 0x8816,
        INTENSITY32F_ARB                                                      = 0x8817,
        LUMINANCE32F_ARB                                                      = 0x8818,
        LUMINANCE_ALPHA32F_ARB                                                = 0x8819,
        RGBA16F_ARB                                                           = 0x881A,
        RGB16F_ARB                                                            = 0x881B,
        ALPHA16F_ARB                                                          = 0x881C,
        INTENSITY16F_ARB                                                      = 0x881D,
        LUMINANCE16F_ARB                                                      = 0x881E,
        LUMINANCE_ALPHA16F_ARB                                                = 0x881F,
        TEXTURE_RED_TYPE_ARB                                                  = 0x8C10,
        TEXTURE_GREEN_TYPE_ARB                                                = 0x8C11,
        TEXTURE_BLUE_TYPE_ARB                                                 = 0x8C12,
        TEXTURE_ALPHA_TYPE_ARB                                                = 0x8C13,
        TEXTURE_LUMINANCE_TYPE_ARB                                            = 0x8C14,
        TEXTURE_INTENSITY_TYPE_ARB                                            = 0x8C15,
        TEXTURE_DEPTH_TYPE_ARB                                                = 0x8C16,
        UNSIGNED_NORMALIZED_ARB                                               = 0x8C17,
        MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB                                 = 0x8E5E,
        MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB                                 = 0x8E5F,
        MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS_ARB                             = 0x8F9F,
        MIRROR_CLAMP_TO_EDGE                                                  = 0x8743,
        MIRRORED_REPEAT_ARB                                                   = 0x8370,
        SAMPLE_POSITION                                                       = 0x8E50,
        SAMPLE_MASK                                                           = 0x8E51,
        SAMPLE_MASK_VALUE                                                     = 0x8E52,
        MAX_SAMPLE_MASK_WORDS                                                 = 0x8E59,
        TEXTURE_2D_MULTISAMPLE                                                = 0x9100,
        PROXY_TEXTURE_2D_MULTISAMPLE                                          = 0x9101,
        TEXTURE_2D_MULTISAMPLE_ARRAY                                          = 0x9102,
        PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY                                    = 0x9103,
        TEXTURE_BINDING_2D_MULTISAMPLE                                        = 0x9104,
        TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY                                  = 0x9105,
        TEXTURE_SAMPLES                                                       = 0x9106,
        TEXTURE_FIXED_SAMPLE_LOCATIONS                                        = 0x9107,
        SAMPLER_2D_MULTISAMPLE                                                = 0x9108,
        INT_SAMPLER_2D_MULTISAMPLE                                            = 0x9109,
        UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE                                   = 0x910A,
        SAMPLER_2D_MULTISAMPLE_ARRAY                                          = 0x910B,
        INT_SAMPLER_2D_MULTISAMPLE_ARRAY                                      = 0x910C,
        UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY                             = 0x910D,
        MAX_COLOR_TEXTURE_SAMPLES                                             = 0x910E,
        MAX_DEPTH_TEXTURE_SAMPLES                                             = 0x910F,
        MAX_INTEGER_SAMPLES                                                   = 0x9110,
        TEXTURE_RECTANGLE_ARB                                                 = 0x84F5,
        TEXTURE_BINDING_RECTANGLE_ARB                                         = 0x84F6,
        PROXY_TEXTURE_RECTANGLE_ARB                                           = 0x84F7,
        MAX_RECTANGLE_TEXTURE_SIZE_ARB                                        = 0x84F8,
        COMPRESSED_RED                                                        = 0x8225,
        COMPRESSED_RG                                                         = 0x8226,
        RG                                                                    = 0x8227,
        RG_INTEGER                                                            = 0x8228,
        R8                                                                    = 0x8229,
        R16                                                                   = 0x822A,
        RG8                                                                   = 0x822B,
        RG16                                                                  = 0x822C,
        R16F                                                                  = 0x822D,
        R32F                                                                  = 0x822E,
        RG16F                                                                 = 0x822F,
        RG32F                                                                 = 0x8230,
        R8I                                                                   = 0x8231,
        R8UI                                                                  = 0x8232,
        R16I                                                                  = 0x8233,
        R16UI                                                                 = 0x8234,
        R32I                                                                  = 0x8235,
        R32UI                                                                 = 0x8236,
        RG8I                                                                  = 0x8237,
        RG16I                                                                 = 0x8239,
        RG32I                                                                 = 0x823B,
        RG32UI                                                                = 0x823C,
        TEXTURE_IMMUTABLE_FORMAT                                              = 0x912F,
        TEXTURE_SWIZZLE_R                                                     = 0x8E42,
        TEXTURE_SWIZZLE_G                                                     = 0x8E43,
        TEXTURE_SWIZZLE_B                                                     = 0x8E44,
        TEXTURE_SWIZZLE_A                                                     = 0x8E45,
        TEXTURE_SWIZZLE_RGBA                                                  = 0x8E46,
        TEXTURE_VIEW_MIN_LEVEL                                                = 0x82DB,
        TEXTURE_VIEW_NUM_LEVELS                                               = 0x82DC,
        TEXTURE_VIEW_MIN_LAYER                                                = 0x82DD,
        TEXTURE_VIEW_NUM_LAYERS                                               = 0x82DE,
        TIME_ELAPSED                                                          = 0x88BF,
        TIMESTAMP                                                             = 0x8E28,
        TRANSFORM_FEEDBACK                                                    = 0x8E22,
        TRANSFORM_FEEDBACK_BUFFER_PAUSED                                      = 0x8E23,
        TRANSFORM_FEEDBACK_BUFFER_ACTIVE                                      = 0x8E24,
        TRANSFORM_FEEDBACK_BINDING                                            = 0x8E25,
        MAX_TRANSFORM_FEEDBACK_BUFFERS                                        = 0x8E70,
        TRANSFORM_FEEDBACK_OVERFLOW_ARB                                       = 0x82EC,
        TRANSFORM_FEEDBACK_STREAM_OVERFLOW_ARB                                = 0x82ED,
        TRANSPOSE_MODELVIEW_MATRIX_ARB                                        = 0x84E3,
        TRANSPOSE_PROJECTION_MATRIX_ARB                                       = 0x84E4,
        TRANSPOSE_TEXTURE_MATRIX_ARB                                          = 0x84E5,
        TRANSPOSE_COLOR_MATRIX_ARB                                            = 0x84E6,
        UNIFORM_BUFFER                                                        = 0x8A11,
        UNIFORM_BUFFER_BINDING                                                = 0x8A28,
        UNIFORM_BUFFER_START                                                  = 0x8A29,
        UNIFORM_BUFFER_SIZE                                                   = 0x8A2A,
        MAX_VERTEX_UNIFORM_BLOCKS                                             = 0x8A2B,
        MAX_GEOMETRY_UNIFORM_BLOCKS                                           = 0x8A2C,
        MAX_FRAGMENT_UNIFORM_BLOCKS                                           = 0x8A2D,
        MAX_COMBINED_UNIFORM_BLOCKS                                           = 0x8A2E,
        MAX_UNIFORM_BUFFER_BINDINGS                                           = 0x8A2F,
        MAX_UNIFORM_BLOCK_SIZE                                                = 0x8A30,
        MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS                                = 0x8A31,
        MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS                              = 0x8A32,
        MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS                              = 0x8A33,
        UNIFORM_BUFFER_OFFSET_ALIGNMENT                                       = 0x8A34,
        ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH                                  = 0x8A35,
        ACTIVE_UNIFORM_BLOCKS                                                 = 0x8A36,
        UNIFORM_TYPE                                                          = 0x8A37,
        UNIFORM_SIZE                                                          = 0x8A38,
        UNIFORM_NAME_LENGTH                                                   = 0x8A39,
        UNIFORM_BLOCK_INDEX                                                   = 0x8A3A,
        UNIFORM_OFFSET                                                        = 0x8A3B,
        UNIFORM_ARRAY_STRIDE                                                  = 0x8A3C,
        UNIFORM_MATRIX_STRIDE                                                 = 0x8A3D,
        UNIFORM_IS_ROW_MAJOR                                                  = 0x8A3E,
        UNIFORM_BLOCK_BINDING                                                 = 0x8A3F,
        UNIFORM_BLOCK_DATA_SIZE                                               = 0x8A40,
        UNIFORM_BLOCK_NAME_LENGTH                                             = 0x8A41,
        UNIFORM_BLOCK_ACTIVE_UNIFORMS                                         = 0x8A42,
        UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES                                  = 0x8A43,
        UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER                             = 0x8A44,
        UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER                           = 0x8A45,
        UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER                           = 0x8A46,
        INVALID_INDEX                                                         = 0xFFFFFFFF,
        VERTEX_ARRAY_BINDING                                                  = 0x85B5,
        VERTEX_ATTRIB_BINDING                                                 = 0x82D4,
        VERTEX_ATTRIB_RELATIVE_OFFSET                                         = 0x82D5,
        VERTEX_BINDING_DIVISOR                                                = 0x82D6,
        VERTEX_BINDING_OFFSET                                                 = 0x82D7,
        VERTEX_BINDING_STRIDE                                                 = 0x82D8,
        MAX_VERTEX_ATTRIB_RELATIVE_OFFSET                                     = 0x82D9,
        MAX_VERTEX_ATTRIB_BINDINGS                                            = 0x82DA,
        VERTEX_BINDING_BUFFER                                                 = 0x8F4F,
        MODELVIEW0_ARB                                                        = 0x1700,
        MODELVIEW1_ARB                                                        = 0x850A,
        MAX_VERTEX_UNITS_ARB                                                  = 0x86A4,
        ACTIVE_VERTEX_UNITS_ARB                                               = 0x86A5,
        WEIGHT_SUM_UNITY_ARB                                                  = 0x86A6,
        VERTEX_BLEND_ARB                                                      = 0x86A7,
        CURRENT_WEIGHT_ARB                                                    = 0x86A8,
        WEIGHT_ARRAY_TYPE_ARB                                                 = 0x86A9,
        WEIGHT_ARRAY_STRIDE_ARB                                               = 0x86AA,
        WEIGHT_ARRAY_SIZE_ARB                                                 = 0x86AB,
        WEIGHT_ARRAY_POINTER_ARB                                              = 0x86AC,
        WEIGHT_ARRAY_ARB                                                      = 0x86AD,
        MODELVIEW2_ARB                                                        = 0x8722,
        MODELVIEW3_ARB                                                        = 0x8723,
        MODELVIEW4_ARB                                                        = 0x8724,
        MODELVIEW5_ARB                                                        = 0x8725,
        MODELVIEW6_ARB                                                        = 0x8726,
        MODELVIEW7_ARB                                                        = 0x8727,
        MODELVIEW8_ARB                                                        = 0x8728,
        MODELVIEW9_ARB                                                        = 0x8729,
        MODELVIEW10_ARB                                                       = 0x872A,
        MODELVIEW11_ARB                                                       = 0x872B,
        MODELVIEW12_ARB                                                       = 0x872C,
        MODELVIEW13_ARB                                                       = 0x872D,
        MODELVIEW14_ARB                                                       = 0x872E,
        MODELVIEW15_ARB                                                       = 0x872F,
        MODELVIEW16_ARB                                                       = 0x8730,
        MODELVIEW17_ARB                                                       = 0x8731,
        MODELVIEW18_ARB                                                       = 0x8732,
        MODELVIEW19_ARB                                                       = 0x8733,
        MODELVIEW20_ARB                                                       = 0x8734,
        MODELVIEW21_ARB                                                       = 0x8735,
        MODELVIEW22_ARB                                                       = 0x8736,
        MODELVIEW23_ARB                                                       = 0x8737,
        MODELVIEW24_ARB                                                       = 0x8738,
        MODELVIEW25_ARB                                                       = 0x8739,
        MODELVIEW26_ARB                                                       = 0x873A,
        MODELVIEW27_ARB                                                       = 0x873B,
        MODELVIEW28_ARB                                                       = 0x873C,
        MODELVIEW29_ARB                                                       = 0x873D,
        MODELVIEW30_ARB                                                       = 0x873E,
        MODELVIEW31_ARB                                                       = 0x873F,
        BUFFER_SIZE_ARB                                                       = 0x8764,
        BUFFER_USAGE_ARB                                                      = 0x8765,
        ARRAY_BUFFER_ARB                                                      = 0x8892,
        ELEMENT_ARRAY_BUFFER_ARB                                              = 0x8893,
        ARRAY_BUFFER_BINDING_ARB                                              = 0x8894,
        ELEMENT_ARRAY_BUFFER_BINDING_ARB                                      = 0x8895,
        VERTEX_ARRAY_BUFFER_BINDING_ARB                                       = 0x8896,
        NORMAL_ARRAY_BUFFER_BINDING_ARB                                       = 0x8897,
        COLOR_ARRAY_BUFFER_BINDING_ARB                                        = 0x8898,
        INDEX_ARRAY_BUFFER_BINDING_ARB                                        = 0x8899,
        TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB                                = 0x889A,
        EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB                                    = 0x889B,
        SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB                              = 0x889C,
        FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB                               = 0x889D,
        WEIGHT_ARRAY_BUFFER_BINDING_ARB                                       = 0x889E,
        VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB                                = 0x889F,
        READ_ONLY_ARB                                                         = 0x88B8,
        WRITE_ONLY_ARB                                                        = 0x88B9,
        READ_WRITE_ARB                                                        = 0x88BA,
        BUFFER_ACCESS_ARB                                                     = 0x88BB,
        BUFFER_MAPPED_ARB                                                     = 0x88BC,
        BUFFER_MAP_POINTER_ARB                                                = 0x88BD,
        STREAM_DRAW_ARB                                                       = 0x88E0,
        STREAM_READ_ARB                                                       = 0x88E1,
        STREAM_COPY_ARB                                                       = 0x88E2,
        STATIC_DRAW_ARB                                                       = 0x88E4,
        STATIC_READ_ARB                                                       = 0x88E5,
        STATIC_COPY_ARB                                                       = 0x88E6,
        DYNAMIC_DRAW_ARB                                                      = 0x88E8,
        DYNAMIC_READ_ARB                                                      = 0x88E9,
        DYNAMIC_COPY_ARB                                                      = 0x88EA,
        COLOR_SUM_ARB                                                         = 0x8458,
        VERTEX_PROGRAM_ARB                                                    = 0x8620,
        VERTEX_ATTRIB_ARRAY_ENABLED_ARB                                       = 0x8622,
        VERTEX_ATTRIB_ARRAY_SIZE_ARB                                          = 0x8623,
        VERTEX_ATTRIB_ARRAY_STRIDE_ARB                                        = 0x8624,
        VERTEX_ATTRIB_ARRAY_TYPE_ARB                                          = 0x8625,
        CURRENT_VERTEX_ATTRIB_ARB                                             = 0x8626,
        PROGRAM_LENGTH_ARB                                                    = 0x8627,
        PROGRAM_STRING_ARB                                                    = 0x8628,
        MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB                                    = 0x862E,
        MAX_PROGRAM_MATRICES_ARB                                              = 0x862F,
        CURRENT_MATRIX_STACK_DEPTH_ARB                                        = 0x8640,
        CURRENT_MATRIX_ARB                                                    = 0x8641,
        VERTEX_PROGRAM_POINT_SIZE_ARB                                         = 0x8642,
        VERTEX_PROGRAM_TWO_SIDE_ARB                                           = 0x8643,
        VERTEX_ATTRIB_ARRAY_POINTER_ARB                                       = 0x8645,
        PROGRAM_ERROR_POSITION_ARB                                            = 0x864B,
        PROGRAM_BINDING_ARB                                                   = 0x8677,
        MAX_VERTEX_ATTRIBS_ARB                                                = 0x8869,
        VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB                                    = 0x886A,
        PROGRAM_ERROR_STRING_ARB                                              = 0x8874,
        PROGRAM_FORMAT_ASCII_ARB                                              = 0x8875,
        PROGRAM_FORMAT_ARB                                                    = 0x8876,
        PROGRAM_INSTRUCTIONS_ARB                                              = 0x88A0,
        MAX_PROGRAM_INSTRUCTIONS_ARB                                          = 0x88A1,
        PROGRAM_NATIVE_INSTRUCTIONS_ARB                                       = 0x88A2,
        MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB                                   = 0x88A3,
        PROGRAM_TEMPORARIES_ARB                                               = 0x88A4,
        MAX_PROGRAM_TEMPORARIES_ARB                                           = 0x88A5,
        PROGRAM_NATIVE_TEMPORARIES_ARB                                        = 0x88A6,
        MAX_PROGRAM_NATIVE_TEMPORARIES_ARB                                    = 0x88A7,
        PROGRAM_PARAMETERS_ARB                                                = 0x88A8,
        MAX_PROGRAM_PARAMETERS_ARB                                            = 0x88A9,
        PROGRAM_NATIVE_PARAMETERS_ARB                                         = 0x88AA,
        MAX_PROGRAM_NATIVE_PARAMETERS_ARB                                     = 0x88AB,
        PROGRAM_ATTRIBS_ARB                                                   = 0x88AC,
        MAX_PROGRAM_ATTRIBS_ARB                                               = 0x88AD,
        PROGRAM_NATIVE_ATTRIBS_ARB                                            = 0x88AE,
        MAX_PROGRAM_NATIVE_ATTRIBS_ARB                                        = 0x88AF,
        PROGRAM_ADDRESS_REGISTERS_ARB                                         = 0x88B0,
        MAX_PROGRAM_ADDRESS_REGISTERS_ARB                                     = 0x88B1,
        PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB                                  = 0x88B2,
        MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB                              = 0x88B3,
        MAX_PROGRAM_LOCAL_PARAMETERS_ARB                                      = 0x88B4,
        MAX_PROGRAM_ENV_PARAMETERS_ARB                                        = 0x88B5,
        PROGRAM_UNDER_NATIVE_LIMITS_ARB                                       = 0x88B6,
        TRANSPOSE_CURRENT_MATRIX_ARB                                          = 0x88B7,
        MATRIX0_ARB                                                           = 0x88C0,
        MATRIX1_ARB                                                           = 0x88C1,
        MATRIX2_ARB                                                           = 0x88C2,
        MATRIX3_ARB                                                           = 0x88C3,
        MATRIX4_ARB                                                           = 0x88C4,
        MATRIX5_ARB                                                           = 0x88C5,
        MATRIX6_ARB                                                           = 0x88C6,
        MATRIX7_ARB                                                           = 0x88C7,
        MATRIX8_ARB                                                           = 0x88C8,
        MATRIX9_ARB                                                           = 0x88C9,
        MATRIX10_ARB                                                          = 0x88CA,
        MATRIX11_ARB                                                          = 0x88CB,
        MATRIX12_ARB                                                          = 0x88CC,
        MATRIX13_ARB                                                          = 0x88CD,
        MATRIX14_ARB                                                          = 0x88CE,
        MATRIX15_ARB                                                          = 0x88CF,
        MATRIX16_ARB                                                          = 0x88D0,
        MATRIX17_ARB                                                          = 0x88D1,
        MATRIX18_ARB                                                          = 0x88D2,
        MATRIX19_ARB                                                          = 0x88D3,
        MATRIX20_ARB                                                          = 0x88D4,
        MATRIX21_ARB                                                          = 0x88D5,
        MATRIX22_ARB                                                          = 0x88D6,
        MATRIX23_ARB                                                          = 0x88D7,
        MATRIX24_ARB                                                          = 0x88D8,
        MATRIX25_ARB                                                          = 0x88D9,
        MATRIX26_ARB                                                          = 0x88DA,
        MATRIX27_ARB                                                          = 0x88DB,
        MATRIX28_ARB                                                          = 0x88DC,
        MATRIX29_ARB                                                          = 0x88DD,
        MATRIX30_ARB                                                          = 0x88DE,
        MATRIX31_ARB                                                          = 0x88DF,
        VERTEX_SHADER_ARB                                                     = 0x8B31,
        MAX_VERTEX_UNIFORM_COMPONENTS_ARB                                     = 0x8B4A,
        MAX_VARYING_FLOATS_ARB                                                = 0x8B4B,
        MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB                                  = 0x8B4D,
        OBJECT_ACTIVE_ATTRIBUTES_ARB                                          = 0x8B89,
        OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB                                = 0x8B8A,
        UNSIGNED_INT_2_10_10_10_REV                                           = 0x8368,
        INT_2_10_10_10_REV                                                    = 0x8D9F,
        MAX_VIEWPORTS                                                         = 0x825B,
        VIEWPORT_SUBPIXEL_BITS                                                = 0x825C,
        VIEWPORT_BOUNDS_RANGE                                                 = 0x825D,
        LAYER_PROVOKING_VERTEX                                                = 0x825E,
        VIEWPORT_INDEX_PROVOKING_VERTEX                                       = 0x825F,
        UNDEFINED_VERTEX                                                      = 0x8260,
        MALI_PROGRAM_BINARY_ARM                                               = 0x8F61,
        MALI_SHADER_BINARY_ARM                                                = 0x8F60,
        RGBA8_OES                                                             = 0x8058,
        FETCH_PER_SAMPLE_ARM                                                  = 0x8F65,
        FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM                             = 0x8F66,
        TEXTURE_POINT_MODE_ATIX                                               = 0x60B0,
        TEXTURE_POINT_ONE_COORD_ATIX                                          = 0x60B1,
        TEXTURE_POINT_SPRITE_ATIX                                             = 0x60B2,
        POINT_SPRITE_CULL_MODE_ATIX                                           = 0x60B3,
        POINT_SPRITE_CULL_CENTER_ATIX                                         = 0x60B4,
        POINT_SPRITE_CULL_CLIP_ATIX                                           = 0x60B5,
        MODULATE_ADD_ATIX                                                     = 0x8744,
        MODULATE_SIGNED_ADD_ATIX                                              = 0x8745,
        MODULATE_SUBTRACT_ATIX                                                = 0x8746,
        SECONDARY_COLOR_ATIX                                                  = 0x8747,
        TEXTURE_OUTPUT_RGB_ATIX                                               = 0x8748,
        TEXTURE_OUTPUT_ALPHA_ATIX                                             = 0x8749,
        OUTPUT_POINT_SIZE_ATIX                                                = 0x610E,
        MAX_DRAW_BUFFERS_ATI                                                  = 0x8824,
        DRAW_BUFFER0_ATI                                                      = 0x8825,
        DRAW_BUFFER1_ATI                                                      = 0x8826,
        DRAW_BUFFER2_ATI                                                      = 0x8827,
        DRAW_BUFFER3_ATI                                                      = 0x8828,
        DRAW_BUFFER4_ATI                                                      = 0x8829,
        DRAW_BUFFER5_ATI                                                      = 0x882A,
        DRAW_BUFFER6_ATI                                                      = 0x882B,
        DRAW_BUFFER7_ATI                                                      = 0x882C,
        DRAW_BUFFER8_ATI                                                      = 0x882D,
        DRAW_BUFFER9_ATI                                                      = 0x882E,
        DRAW_BUFFER10_ATI                                                     = 0x882F,
        DRAW_BUFFER11_ATI                                                     = 0x8830,
        DRAW_BUFFER12_ATI                                                     = 0x8831,
        DRAW_BUFFER13_ATI                                                     = 0x8832,
        DRAW_BUFFER14_ATI                                                     = 0x8833,
        DRAW_BUFFER15_ATI                                                     = 0x8834,
        ELEMENT_ARRAY_ATI                                                     = 0x8768,
        ELEMENT_ARRAY_TYPE_ATI                                                = 0x8769,
        ELEMENT_ARRAY_POINTER_ATI                                             = 0x876A,
        BUMP_ROT_MATRIX_ATI                                                   = 0x8775,
        BUMP_ROT_MATRIX_SIZE_ATI                                              = 0x8776,
        BUMP_NUM_TEX_UNITS_ATI                                                = 0x8777,
        BUMP_TEX_UNITS_ATI                                                    = 0x8778,
        DUDV_ATI                                                              = 0x8779,
        DU8DV8_ATI                                                            = 0x877A,
        BUMP_ENVMAP_ATI                                                       = 0x877B,
        BUMP_TARGET_ATI                                                       = 0x877C,
        N2X_BIT_ATI                                                           = 0x1,
        RED_BIT_ATI                                                           = 0x1,
        N4X_BIT_ATI                                                           = 0x2,
        COMP_BIT_ATI                                                          = 0x2,
        GREEN_BIT_ATI                                                         = 0x2,
        N8X_BIT_ATI                                                           = 0x4,
        BLUE_BIT_ATI                                                          = 0x4,
        NEGATE_BIT_ATI                                                        = 0x4,
        BIAS_BIT_ATI                                                          = 0x8,
        HALF_BIT_ATI                                                          = 0x8,
        QUARTER_BIT_ATI                                                       = 0x10,
        EIGHTH_BIT_ATI                                                        = 0x20,
        SATURATE_BIT_ATI                                                      = 0x40,
        FRAGMENT_SHADER_ATI                                                   = 0x8920,
        REG_0_ATI                                                             = 0x8921,
        REG_1_ATI                                                             = 0x8922,
        REG_2_ATI                                                             = 0x8923,
        REG_3_ATI                                                             = 0x8924,
        REG_4_ATI                                                             = 0x8925,
        REG_5_ATI                                                             = 0x8926,
        CON_0_ATI                                                             = 0x8941,
        CON_1_ATI                                                             = 0x8942,
        CON_2_ATI                                                             = 0x8943,
        CON_3_ATI                                                             = 0x8944,
        CON_4_ATI                                                             = 0x8945,
        CON_5_ATI                                                             = 0x8946,
        CON_6_ATI                                                             = 0x8947,
        CON_7_ATI                                                             = 0x8948,
        MOV_ATI                                                               = 0x8961,
        ADD_ATI                                                               = 0x8963,
        MUL_ATI                                                               = 0x8964,
        SUB_ATI                                                               = 0x8965,
        DOT3_ATI                                                              = 0x8966,
        DOT4_ATI                                                              = 0x8967,
        MAD_ATI                                                               = 0x8968,
        LERP_ATI                                                              = 0x8969,
        CND_ATI                                                               = 0x896A,
        CND0_ATI                                                              = 0x896B,
        DOT2_ADD_ATI                                                          = 0x896C,
        SECONDARY_INTERPOLATOR_ATI                                            = 0x896D,
        NUM_FRAGMENT_REGISTERS_ATI                                            = 0x896E,
        NUM_FRAGMENT_CONSTANTS_ATI                                            = 0x896F,
        NUM_PASSES_ATI                                                        = 0x8970,
        NUM_INSTRUCTIONS_PER_PASS_ATI                                         = 0x8971,
        NUM_INSTRUCTIONS_TOTAL_ATI                                            = 0x8972,
        NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI                                 = 0x8973,
        NUM_LOOPBACK_COMPONENTS_ATI                                           = 0x8974,
        COLOR_ALPHA_PAIRING_ATI                                               = 0x8975,
        SWIZZLE_STR_ATI                                                       = 0x8976,
        SWIZZLE_STQ_ATI                                                       = 0x8977,
        SWIZZLE_STR_DR_ATI                                                    = 0x8978,
        SWIZZLE_STQ_DQ_ATI                                                    = 0x8979,
        SWIZZLE_STRQ_ATI                                                      = 0x897A,
        SWIZZLE_STRQ_DQ_ATI                                                   = 0x897B,
        VBO_FREE_MEMORY_ATI                                                   = 0x87FB,
        TEXTURE_FREE_MEMORY_ATI                                               = 0x87FC,
        RENDERBUFFER_FREE_MEMORY_ATI                                          = 0x87FD,
        PN_TRIANGLES_ATI                                                      = 0x87F0,
        MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI                                = 0x87F1,
        PN_TRIANGLES_POINT_MODE_ATI                                           = 0x87F2,
        PN_TRIANGLES_NORMAL_MODE_ATI                                          = 0x87F3,
        PN_TRIANGLES_TESSELATION_LEVEL_ATI                                    = 0x87F4,
        PN_TRIANGLES_POINT_MODE_LINEAR_ATI                                    = 0x87F5,
        PN_TRIANGLES_POINT_MODE_CUBIC_ATI                                     = 0x87F6,
        PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI                                   = 0x87F7,
        PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI                                = 0x87F8,
        STENCIL_BACK_FUNC_ATI                                                 = 0x8800,
        STENCIL_BACK_FAIL_ATI                                                 = 0x8801,
        STENCIL_BACK_PASS_DEPTH_FAIL_ATI                                      = 0x8802,
        STENCIL_BACK_PASS_DEPTH_PASS_ATI                                      = 0x8803,
        TEXT_FRAGMENT_SHADER_ATI                                              = 0x8200,
        COMPRESSED_LUMINANCE_ALPHA_3DC_ATI                                    = 0x8837,
        MODULATE_ADD_ATI                                                      = 0x8744,
        MODULATE_SIGNED_ADD_ATI                                               = 0x8745,
        MODULATE_SUBTRACT_ATI                                                 = 0x8746,
        RGBA_FLOAT32_ATI                                                      = 0x8814,
        RGB_FLOAT32_ATI                                                       = 0x8815,
        ALPHA_FLOAT32_ATI                                                     = 0x8816,
        INTENSITY_FLOAT32_ATI                                                 = 0x8817,
        LUMINANCE_FLOAT32_ATI                                                 = 0x8818,
        LUMINANCE_ALPHA_FLOAT32_ATI                                           = 0x8819,
        RGBA_FLOAT16_ATI                                                      = 0x881A,
        RGB_FLOAT16_ATI                                                       = 0x881B,
        ALPHA_FLOAT16_ATI                                                     = 0x881C,
        INTENSITY_FLOAT16_ATI                                                 = 0x881D,
        LUMINANCE_FLOAT16_ATI                                                 = 0x881E,
        LUMINANCE_ALPHA_FLOAT16_ATI                                           = 0x881F,
        MIRROR_CLAMP_ATI                                                      = 0x8742,
        MIRROR_CLAMP_TO_EDGE_ATI                                              = 0x8743,
        STATIC_ATI                                                            = 0x8760,
        DYNAMIC_ATI                                                           = 0x8761,
        PRESERVE_ATI                                                          = 0x8762,
        DISCARD_ATI                                                           = 0x8763,
        OBJECT_BUFFER_SIZE_ATI                                                = 0x8764,
        OBJECT_BUFFER_USAGE_ATI                                               = 0x8765,
        ARRAY_OBJECT_BUFFER_ATI                                               = 0x8766,
        ARRAY_OBJECT_OFFSET_ATI                                               = 0x8767,
        MAX_VERTEX_STREAMS_ATI                                                = 0x876B,
        VERTEX_SOURCE_ATI                                                     = 0x876C,
        VERTEX_STREAM0_ATI                                                    = 0x876D,
        VERTEX_STREAM1_ATI                                                    = 0x876E,
        VERTEX_STREAM2_ATI                                                    = 0x876F,
        VERTEX_STREAM3_ATI                                                    = 0x8770,
        VERTEX_STREAM4_ATI                                                    = 0x8771,
        VERTEX_STREAM5_ATI                                                    = 0x8772,
        VERTEX_STREAM6_ATI                                                    = 0x8773,
        VERTEX_STREAM7_ATI                                                    = 0x8774,
        EGL_GENERATE_RESET_ON_VIDEO_MEMORY_PURGE_NV                           = 0x334C,
        PURGED_CONTEXT_RESET_NV                                               = 0x92BB,
        N422_EXT                                                              = 0x80CC,
        N422_REV_EXT                                                          = 0x80CD,
        N422_AVERAGE_EXT                                                      = 0x80CE,
        N422_REV_AVERAGE_EXT                                                  = 0x80CF,
        CG_VERTEX_SHADER_EXT                                                  = 0x890E,
        CG_FRAGMENT_SHADER_EXT                                                = 0x890F,
        SAMPLER_EXTERNAL_2D_Y2Y_EXT                                           = 0x8BE7,
        ABGR_EXT                                                              = 0x8000,
        BGR_EXT                                                               = 0x80E0,
        MAX_VERTEX_BINDABLE_UNIFORMS_EXT                                      = 0x8DE2,
        MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT                                    = 0x8DE3,
        MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT                                    = 0x8DE4,
        MAX_BINDABLE_UNIFORM_SIZE_EXT                                         = 0x8DED,
        UNIFORM_BUFFER_EXT                                                    = 0x8DEE,
        UNIFORM_BUFFER_BINDING_EXT                                            = 0x8DEF,
        CONSTANT_COLOR_EXT                                                    = 0x8001,
        ONE_MINUS_CONSTANT_COLOR_EXT                                          = 0x8002,
        CONSTANT_ALPHA_EXT                                                    = 0x8003,
        ONE_MINUS_CONSTANT_ALPHA_EXT                                          = 0x8004,
        BLEND_COLOR_EXT                                                       = 0x8005,
        BLEND_EQUATION_RGB_EXT                                                = 0x8009,
        BLEND_EQUATION_ALPHA_EXT                                              = 0x883D,
        SRC_ALPHA_SATURATE_EXT                                                = 0x308,
        SRC1_ALPHA_EXT                                                        = 0x8589,
        SRC1_COLOR_EXT                                                        = 0x88F9,
        ONE_MINUS_SRC1_COLOR_EXT                                              = 0x88FA,
        ONE_MINUS_SRC1_ALPHA_EXT                                              = 0x88FB,
        MAX_DUAL_SOURCE_DRAW_BUFFERS_EXT                                      = 0x88FC,
        LOCATION_INDEX_EXT                                                    = 0x930F,
        BLEND_DST_RGB_EXT                                                     = 0x80C8,
        BLEND_SRC_RGB_EXT                                                     = 0x80C9,
        BLEND_DST_ALPHA_EXT                                                   = 0x80CA,
        BLEND_SRC_ALPHA_EXT                                                   = 0x80CB,
        FUNC_ADD_EXT                                                          = 0x8006,
        MIN_EXT                                                               = 0x8007,
        MAX_EXT                                                               = 0x8008,
        BLEND_EQUATION_EXT                                                    = 0x8009,
        FUNC_SUBTRACT_EXT                                                     = 0x800A,
        FUNC_REVERSE_SUBTRACT_EXT                                             = 0x800B,
        MAP_PERSISTENT_BIT_EXT                                                = 0x40,
        MAP_COHERENT_BIT_EXT                                                  = 0x80,
        DYNAMIC_STORAGE_BIT_EXT                                               = 0x100,
        CLIENT_STORAGE_BIT_EXT                                                = 0x200,
        CLIENT_MAPPED_BUFFER_BARRIER_BIT_EXT                                  = 0x4000,
        BUFFER_IMMUTABLE_STORAGE_EXT                                          = 0x821F,
        BUFFER_STORAGE_FLAGS_EXT                                              = 0x8220,
        MAX_CLIP_DISTANCES_EXT                                                = 0xD32,
        CLIP_DISTANCE0_EXT                                                    = 0x3000,
        CLIP_DISTANCE1_EXT                                                    = 0x3001,
        CLIP_DISTANCE2_EXT                                                    = 0x3002,
        CLIP_DISTANCE3_EXT                                                    = 0x3003,
        CLIP_DISTANCE4_EXT                                                    = 0x3004,
        CLIP_DISTANCE5_EXT                                                    = 0x3005,
        CLIP_DISTANCE6_EXT                                                    = 0x3006,
        CLIP_DISTANCE7_EXT                                                    = 0x3007,
        MAX_CULL_DISTANCES_EXT                                                = 0x82F9,
        MAX_COMBINED_CLIP_AND_CULL_DISTANCES_EXT                              = 0x82FA,
        CLIP_VOLUME_CLIPPING_HINT_EXT                                         = 0x80F0,
        CMYK_EXT                                                              = 0x800C,
        CMYKA_EXT                                                             = 0x800D,
        PACK_CMYK_HINT_EXT                                                    = 0x800E,
        UNPACK_CMYK_HINT_EXT                                                  = 0x800F,
        FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT                             = 0x8211,
        R16F_EXT                                                              = 0x822D,
        RG16F_EXT                                                             = 0x822F,
        RGBA16F_EXT                                                           = 0x881A,
        RGB16F_EXT                                                            = 0x881B,
        UNSIGNED_NORMALIZED_EXT                                               = 0x8C17,
        ARRAY_ELEMENT_LOCK_FIRST_EXT                                          = 0x81A8,
        ARRAY_ELEMENT_LOCK_COUNT_EXT                                          = 0x81A9,
        CONVOLUTION_1D_EXT                                                    = 0x8010,
        CONVOLUTION_2D_EXT                                                    = 0x8011,
        SEPARABLE_2D_EXT                                                      = 0x8012,
        CONVOLUTION_BORDER_MODE_EXT                                           = 0x8013,
        CONVOLUTION_FILTER_SCALE_EXT                                          = 0x8014,
        CONVOLUTION_FILTER_BIAS_EXT                                           = 0x8015,
        REDUCE_EXT                                                            = 0x8016,
        CONVOLUTION_FORMAT_EXT                                                = 0x8017,
        CONVOLUTION_WIDTH_EXT                                                 = 0x8018,
        CONVOLUTION_HEIGHT_EXT                                                = 0x8019,
        MAX_CONVOLUTION_WIDTH_EXT                                             = 0x801A,
        MAX_CONVOLUTION_HEIGHT_EXT                                            = 0x801B,
        POST_CONVOLUTION_RED_SCALE_EXT                                        = 0x801C,
        POST_CONVOLUTION_GREEN_SCALE_EXT                                      = 0x801D,
        POST_CONVOLUTION_BLUE_SCALE_EXT                                       = 0x801E,
        POST_CONVOLUTION_ALPHA_SCALE_EXT                                      = 0x801F,
        POST_CONVOLUTION_RED_BIAS_EXT                                         = 0x8020,
        POST_CONVOLUTION_GREEN_BIAS_EXT                                       = 0x8021,
        POST_CONVOLUTION_BLUE_BIAS_EXT                                        = 0x8022,
        POST_CONVOLUTION_ALPHA_BIAS_EXT                                       = 0x8023,
        TANGENT_ARRAY_EXT                                                     = 0x8439,
        BINORMAL_ARRAY_EXT                                                    = 0x843A,
        CURRENT_TANGENT_EXT                                                   = 0x843B,
        CURRENT_BINORMAL_EXT                                                  = 0x843C,
        TANGENT_ARRAY_TYPE_EXT                                                = 0x843E,
        TANGENT_ARRAY_STRIDE_EXT                                              = 0x843F,
        BINORMAL_ARRAY_TYPE_EXT                                               = 0x8440,
        BINORMAL_ARRAY_STRIDE_EXT                                             = 0x8441,
        TANGENT_ARRAY_POINTER_EXT                                             = 0x8442,
        BINORMAL_ARRAY_POINTER_EXT                                            = 0x8443,
        MAP1_TANGENT_EXT                                                      = 0x8444,
        MAP2_TANGENT_EXT                                                      = 0x8445,
        MAP1_BINORMAL_EXT                                                     = 0x8446,
        MAP2_BINORMAL_EXT                                                     = 0x8447,
        CULL_VERTEX_EXT                                                       = 0x81AA,
        CULL_VERTEX_EYE_POSITION_EXT                                          = 0x81AB,
        CULL_VERTEX_OBJECT_POSITION_EXT                                       = 0x81AC,
        PROGRAM_PIPELINE_OBJECT_EXT                                           = 0x8A4F,
        PROGRAM_OBJECT_EXT                                                    = 0x8B40,
        SHADER_OBJECT_EXT                                                     = 0x8B48,
        BUFFER_OBJECT_EXT                                                     = 0x9151,
        QUERY_OBJECT_EXT                                                      = 0x9153,
        VERTEX_ARRAY_OBJECT_EXT                                               = 0x9154,
        DEPTH_BOUNDS_TEST_EXT                                                 = 0x8890,
        DEPTH_BOUNDS_EXT                                                      = 0x8891,
        PROGRAM_MATRIX_EXT                                                    = 0x8E2D,
        TRANSPOSE_PROGRAM_MATRIX_EXT                                          = 0x8E2E,
        PROGRAM_MATRIX_STACK_DEPTH_EXT                                        = 0x8E2F,
        COLOR_EXT                                                             = 0x1800,
        DEPTH_EXT                                                             = 0x1801,
        STENCIL_EXT                                                           = 0x1802,
        MAX_DRAW_BUFFERS_EXT                                                  = 0x8824,
        DRAW_BUFFER0_EXT                                                      = 0x8825,
        DRAW_BUFFER1_EXT                                                      = 0x8826,
        DRAW_BUFFER2_EXT                                                      = 0x8827,
        DRAW_BUFFER3_EXT                                                      = 0x8828,
        DRAW_BUFFER4_EXT                                                      = 0x8829,
        DRAW_BUFFER5_EXT                                                      = 0x882A,
        DRAW_BUFFER6_EXT                                                      = 0x882B,
        DRAW_BUFFER7_EXT                                                      = 0x882C,
        DRAW_BUFFER8_EXT                                                      = 0x882D,
        DRAW_BUFFER9_EXT                                                      = 0x882E,
        DRAW_BUFFER10_EXT                                                     = 0x882F,
        DRAW_BUFFER11_EXT                                                     = 0x8830,
        DRAW_BUFFER12_EXT                                                     = 0x8831,
        DRAW_BUFFER13_EXT                                                     = 0x8832,
        DRAW_BUFFER14_EXT                                                     = 0x8833,
        DRAW_BUFFER15_EXT                                                     = 0x8834,
        MAX_COLOR_ATTACHMENTS_EXT                                             = 0x8CDF,
        COLOR_ATTACHMENT0_EXT                                                 = 0x8CE0,
        COLOR_ATTACHMENT1_EXT                                                 = 0x8CE1,
        COLOR_ATTACHMENT2_EXT                                                 = 0x8CE2,
        COLOR_ATTACHMENT3_EXT                                                 = 0x8CE3,
        COLOR_ATTACHMENT4_EXT                                                 = 0x8CE4,
        COLOR_ATTACHMENT5_EXT                                                 = 0x8CE5,
        COLOR_ATTACHMENT6_EXT                                                 = 0x8CE6,
        COLOR_ATTACHMENT7_EXT                                                 = 0x8CE7,
        COLOR_ATTACHMENT8_EXT                                                 = 0x8CE8,
        COLOR_ATTACHMENT9_EXT                                                 = 0x8CE9,
        COLOR_ATTACHMENT10_EXT                                                = 0x8CEA,
        COLOR_ATTACHMENT11_EXT                                                = 0x8CEB,
        COLOR_ATTACHMENT12_EXT                                                = 0x8CEC,
        COLOR_ATTACHMENT13_EXT                                                = 0x8CED,
        COLOR_ATTACHMENT14_EXT                                                = 0x8CEE,
        COLOR_ATTACHMENT15_EXT                                                = 0x8CEF,
        MAX_ELEMENTS_VERTICES_EXT                                             = 0x80E8,
        MAX_ELEMENTS_INDICES_EXT                                              = 0x80E9,
        FOG_COORDINATE_SOURCE_EXT                                             = 0x8450,
        FOG_COORDINATE_EXT                                                    = 0x8451,
        FRAGMENT_DEPTH_EXT                                                    = 0x8452,
        CURRENT_FOG_COORDINATE_EXT                                            = 0x8453,
        FOG_COORDINATE_ARRAY_TYPE_EXT                                         = 0x8454,
        FOG_COORDINATE_ARRAY_STRIDE_EXT                                       = 0x8455,
        FOG_COORDINATE_ARRAY_POINTER_EXT                                      = 0x8456,
        FOG_COORDINATE_ARRAY_EXT                                              = 0x8457,
        FRAGMENT_LIGHTING_EXT                                                 = 0x8400,
        FRAGMENT_COLOR_MATERIAL_EXT                                           = 0x8401,
        FRAGMENT_COLOR_MATERIAL_FACE_EXT                                      = 0x8402,
        FRAGMENT_COLOR_MATERIAL_PARAMETER_EXT                                 = 0x8403,
        MAX_FRAGMENT_LIGHTS_EXT                                               = 0x8404,
        MAX_ACTIVE_LIGHTS_EXT                                                 = 0x8405,
        CURRENT_RASTER_NORMAL_EXT                                             = 0x8406,
        LIGHT_ENV_MODE_EXT                                                    = 0x8407,
        FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_EXT                                 = 0x8408,
        FRAGMENT_LIGHT_MODEL_TWO_SIDE_EXT                                     = 0x8409,
        FRAGMENT_LIGHT_MODEL_AMBIENT_EXT                                      = 0x840A,
        FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_EXT                         = 0x840B,
        FRAGMENT_LIGHT0_EXT                                                   = 0x840C,
        FRAGMENT_LIGHT7_EXT                                                   = 0x8413,
        DRAW_FRAMEBUFFER_BINDING_EXT                                          = 0x8CA6,
        READ_FRAMEBUFFER_EXT                                                  = 0x8CA8,
        DRAW_FRAMEBUFFER_EXT                                                  = 0x8CA9,
        READ_FRAMEBUFFER_BINDING_EXT                                          = 0x8CAA,
        RENDERBUFFER_SAMPLES_EXT                                              = 0x8CAB,
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT                                = 0x8D56,
        MAX_SAMPLES_EXT                                                       = 0x8D57,
        SCALED_RESOLVE_FASTEST_EXT                                            = 0x90BA,
        SCALED_RESOLVE_NICEST_EXT                                             = 0x90BB,
        INVALID_FRAMEBUFFER_OPERATION_EXT                                     = 0x506,
        MAX_RENDERBUFFER_SIZE_EXT                                             = 0x84E8,
        FRAMEBUFFER_BINDING_EXT                                               = 0x8CA6,
        RENDERBUFFER_BINDING_EXT                                              = 0x8CA7,
        FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT                                = 0x8CD0,
        FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT                                = 0x8CD1,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT                              = 0x8CD2,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT                      = 0x8CD3,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT                         = 0x8CD4,
        FRAMEBUFFER_COMPLETE_EXT                                              = 0x8CD5,
        FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT                                 = 0x8CD6,
        FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT                         = 0x8CD7,
        FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT                                 = 0x8CD9,
        FRAMEBUFFER_INCOMPLETE_FORMATS_EXT                                    = 0x8CDA,
        FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT                                = 0x8CDB,
        FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT                                = 0x8CDC,
        FRAMEBUFFER_UNSUPPORTED_EXT                                           = 0x8CDD,
        DEPTH_ATTACHMENT_EXT                                                  = 0x8D00,
        STENCIL_ATTACHMENT_EXT                                                = 0x8D20,
        FRAMEBUFFER_EXT                                                       = 0x8D40,
        RENDERBUFFER_EXT                                                      = 0x8D41,
        RENDERBUFFER_WIDTH_EXT                                                = 0x8D42,
        RENDERBUFFER_HEIGHT_EXT                                               = 0x8D43,
        RENDERBUFFER_INTERNAL_FORMAT_EXT                                      = 0x8D44,
        STENCIL_INDEX1_EXT                                                    = 0x8D46,
        STENCIL_INDEX4_EXT                                                    = 0x8D47,
        STENCIL_INDEX8_EXT                                                    = 0x8D48,
        STENCIL_INDEX16_EXT                                                   = 0x8D49,
        RENDERBUFFER_RED_SIZE_EXT                                             = 0x8D50,
        RENDERBUFFER_GREEN_SIZE_EXT                                           = 0x8D51,
        RENDERBUFFER_BLUE_SIZE_EXT                                            = 0x8D52,
        RENDERBUFFER_ALPHA_SIZE_EXT                                           = 0x8D53,
        RENDERBUFFER_DEPTH_SIZE_EXT                                           = 0x8D54,
        RENDERBUFFER_STENCIL_SIZE_EXT                                         = 0x8D55,
        FRAMEBUFFER_SRGB_EXT                                                  = 0x8DB9,
        FRAMEBUFFER_SRGB_CAPABLE_EXT                                          = 0x8DBA,
        GEOMETRY_SHADER_BIT_EXT                                               = 0x4,
        LINES_ADJACENCY_EXT                                                   = 0xA,
        LINE_STRIP_ADJACENCY_EXT                                              = 0xB,
        TRIANGLES_ADJACENCY_EXT                                               = 0xC,
        TRIANGLE_STRIP_ADJACENCY_EXT                                          = 0xD,
        LAYER_PROVOKING_VERTEX_EXT                                            = 0x825E,
        UNDEFINED_VERTEX_EXT                                                  = 0x8260,
        GEOMETRY_SHADER_INVOCATIONS_EXT                                       = 0x887F,
        GEOMETRY_LINKED_VERTICES_OUT_EXT                                      = 0x8916,
        GEOMETRY_LINKED_INPUT_TYPE_EXT                                        = 0x8917,
        GEOMETRY_LINKED_OUTPUT_TYPE_EXT                                       = 0x8918,
        MAX_GEOMETRY_UNIFORM_BLOCKS_EXT                                       = 0x8A2C,
        MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT                          = 0x8A32,
        MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT                                  = 0x8C29,
        PRIMITIVES_GENERATED_EXT                                              = 0x8C87,
        FRAMEBUFFER_ATTACHMENT_LAYERED_EXT                                    = 0x8DA7,
        FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT                              = 0x8DA8,
        GEOMETRY_SHADER_EXT                                                   = 0x8DD9,
        MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT                                   = 0x8DDF,
        MAX_GEOMETRY_OUTPUT_VERTICES_EXT                                      = 0x8DE0,
        MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT                              = 0x8DE1,
        FIRST_VERTEX_CONVENTION_EXT                                           = 0x8E4D,
        LAST_VERTEX_CONVENTION_EXT                                            = 0x8E4E,
        MAX_GEOMETRY_SHADER_INVOCATIONS_EXT                                   = 0x8E5A,
        MAX_GEOMETRY_IMAGE_UNIFORMS_EXT                                       = 0x90CD,
        MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT                                = 0x90D7,
        MAX_GEOMETRY_INPUT_COMPONENTS_EXT                                     = 0x9123,
        MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT                                    = 0x9124,
        MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT                               = 0x92CF,
        MAX_GEOMETRY_ATOMIC_COUNTERS_EXT                                      = 0x92D5,
        REFERENCED_BY_GEOMETRY_SHADER_EXT                                     = 0x9309,
        FRAMEBUFFER_DEFAULT_LAYERS_EXT                                        = 0x9312,
        MAX_FRAMEBUFFER_LAYERS_EXT                                            = 0x9317,
        PROGRAM_POINT_SIZE_EXT                                                = 0x8642,
        MAX_VARYING_COMPONENTS_EXT                                            = 0x8B4B,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT                              = 0x8CD4,
        FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_EXT                                = 0x8DA9,
        GEOMETRY_VERTICES_OUT_EXT                                             = 0x8DDA,
        GEOMETRY_INPUT_TYPE_EXT                                               = 0x8DDB,
        GEOMETRY_OUTPUT_TYPE_EXT                                              = 0x8DDC,
        MAX_GEOMETRY_VARYING_COMPONENTS_EXT                                   = 0x8DDD,
        MAX_VERTEX_VARYING_COMPONENTS_EXT                                     = 0x8DDE,
        VERTEX_ATTRIB_ARRAY_INTEGER_EXT                                       = 0x88FD,
        SAMPLER_1D_ARRAY_EXT                                                  = 0x8DC0,
        SAMPLER_2D_ARRAY_EXT                                                  = 0x8DC1,
        SAMPLER_BUFFER_EXT                                                    = 0x8DC2,
        SAMPLER_1D_ARRAY_SHADOW_EXT                                           = 0x8DC3,
        SAMPLER_2D_ARRAY_SHADOW_EXT                                           = 0x8DC4,
        SAMPLER_CUBE_SHADOW_EXT                                               = 0x8DC5,
        UNSIGNED_INT_VEC2_EXT                                                 = 0x8DC6,
        UNSIGNED_INT_VEC3_EXT                                                 = 0x8DC7,
        UNSIGNED_INT_VEC4_EXT                                                 = 0x8DC8,
        INT_SAMPLER_1D_EXT                                                    = 0x8DC9,
        INT_SAMPLER_2D_EXT                                                    = 0x8DCA,
        INT_SAMPLER_3D_EXT                                                    = 0x8DCB,
        INT_SAMPLER_CUBE_EXT                                                  = 0x8DCC,
        INT_SAMPLER_2D_RECT_EXT                                               = 0x8DCD,
        INT_SAMPLER_1D_ARRAY_EXT                                              = 0x8DCE,
        INT_SAMPLER_2D_ARRAY_EXT                                              = 0x8DCF,
        INT_SAMPLER_BUFFER_EXT                                                = 0x8DD0,
        UNSIGNED_INT_SAMPLER_1D_EXT                                           = 0x8DD1,
        UNSIGNED_INT_SAMPLER_2D_EXT                                           = 0x8DD2,
        UNSIGNED_INT_SAMPLER_3D_EXT                                           = 0x8DD3,
        UNSIGNED_INT_SAMPLER_CUBE_EXT                                         = 0x8DD4,
        UNSIGNED_INT_SAMPLER_2D_RECT_EXT                                      = 0x8DD5,
        UNSIGNED_INT_SAMPLER_1D_ARRAY_EXT                                     = 0x8DD6,
        UNSIGNED_INT_SAMPLER_2D_ARRAY_EXT                                     = 0x8DD7,
        UNSIGNED_INT_SAMPLER_BUFFER_EXT                                       = 0x8DD8,
        HISTOGRAM_EXT                                                         = 0x8024,
        PROXY_HISTOGRAM_EXT                                                   = 0x8025,
        HISTOGRAM_WIDTH_EXT                                                   = 0x8026,
        HISTOGRAM_FORMAT_EXT                                                  = 0x8027,
        HISTOGRAM_RED_SIZE_EXT                                                = 0x8028,
        HISTOGRAM_GREEN_SIZE_EXT                                              = 0x8029,
        HISTOGRAM_BLUE_SIZE_EXT                                               = 0x802A,
        HISTOGRAM_ALPHA_SIZE_EXT                                              = 0x802B,
        HISTOGRAM_LUMINANCE_SIZE_EXT                                          = 0x802C,
        HISTOGRAM_SINK_EXT                                                    = 0x802D,
        MINMAX_EXT                                                            = 0x802E,
        MINMAX_FORMAT_EXT                                                     = 0x802F,
        MINMAX_SINK_EXT                                                       = 0x8030,
        VERTEX_ATTRIB_ARRAY_DIVISOR_EXT                                       = 0x88FE,
        FRAGMENT_MATERIAL_EXT                                                 = 0x8349,
        FRAGMENT_NORMAL_EXT                                                   = 0x834A,
        FRAGMENT_COLOR_EXT                                                    = 0x834C,
        ATTENUATION_EXT                                                       = 0x834D,
        SHADOW_ATTENUATION_EXT                                                = 0x834E,
        TEXTURE_APPLICATION_MODE_EXT                                          = 0x834F,
        TEXTURE_LIGHT_EXT                                                     = 0x8350,
        TEXTURE_MATERIAL_FACE_EXT                                             = 0x8351,
        TEXTURE_MATERIAL_PARAMETER_EXT                                        = 0x8352,
        MAP_READ_BIT_EXT                                                      = 0x1,
        MAP_WRITE_BIT_EXT                                                     = 0x2,
        MAP_INVALIDATE_RANGE_BIT_EXT                                          = 0x4,
        MAP_INVALIDATE_BUFFER_BIT_EXT                                         = 0x8,
        MAP_FLUSH_EXPLICIT_BIT_EXT                                            = 0x10,
        MAP_UNSYNCHRONIZED_BIT_EXT                                            = 0x20,
        TEXTURE_TILING_EXT                                                    = 0x9580,
        DEDICATED_MEMORY_OBJECT_EXT                                           = 0x9581,
        NUM_TILING_TYPES_EXT                                                  = 0x9582,
        TILING_TYPES_EXT                                                      = 0x9583,
        OPTIMAL_TILING_EXT                                                    = 0x9584,
        LINEAR_TILING_EXT                                                     = 0x9585,
        LAYOUT_GENERAL_EXT                                                    = 0x958D,
        LAYOUT_COLOR_ATTACHMENT_EXT                                           = 0x958E,
        LAYOUT_DEPTH_STENCIL_ATTACHMENT_EXT                                   = 0x958F,
        LAYOUT_DEPTH_STENCIL_READ_ONLY_EXT                                    = 0x9590,
        LAYOUT_SHADER_READ_ONLY_EXT                                           = 0x9591,
        LAYOUT_TRANSFER_SRC_EXT                                               = 0x9592,
        LAYOUT_TRANSFER_DST_EXT                                               = 0x9593,
        NUM_DEVICE_UUIDS_EXT                                                  = 0x9596,
        DEVICE_UUID_EXT                                                       = 0x9597,
        DRIVER_UUID_EXT                                                       = 0x9598,
        PROTECTED_MEMORY_OBJECT_EXT                                           = 0x959B,
        HANDLE_TYPE_OPAQUE_FD_EXT                                             = 0x9586,
        HANDLE_TYPE_OPAQUE_WIN32_EXT                                          = 0x9587,
        HANDLE_TYPE_OPAQUE_WIN32_KMT_EXT                                      = 0x9588,
        HANDLE_TYPE_D3D12_TILEPOOL_EXT                                        = 0x9589,
        HANDLE_TYPE_D3D12_RESOURCE_EXT                                        = 0x958A,
        HANDLE_TYPE_D3D11_IMAGE_EXT                                           = 0x958B,
        HANDLE_TYPE_D3D11_IMAGE_KMT_EXT                                       = 0x958C,
        HANDLE_TYPE_D3D12_FENCE_EXT                                           = 0x9594,
        D3D12_FENCE_VALUE_EXT                                                 = 0x9595,
        DEVICE_LUID_EXT                                                       = 0x9599,
        DEVICE_NODE_MASK_EXT                                                  = 0x959A,
        MULTISAMPLE_EXT                                                       = 0x809D,
        SAMPLE_ALPHA_TO_MASK_EXT                                              = 0x809E,
        SAMPLE_ALPHA_TO_ONE_EXT                                               = 0x809F,
        SAMPLE_MASK_EXT                                                       = 0x80A0,
        N1PASS_EXT                                                            = 0x80A1,
        N2PASS_0_EXT                                                          = 0x80A2,
        N2PASS_1_EXT                                                          = 0x80A3,
        N4PASS_0_EXT                                                          = 0x80A4,
        N4PASS_1_EXT                                                          = 0x80A5,
        N4PASS_2_EXT                                                          = 0x80A6,
        N4PASS_3_EXT                                                          = 0x80A7,
        SAMPLE_BUFFERS_EXT                                                    = 0x80A8,
        SAMPLES_EXT                                                           = 0x80A9,
        SAMPLE_MASK_VALUE_EXT                                                 = 0x80AA,
        SAMPLE_MASK_INVERT_EXT                                                = 0x80AB,
        SAMPLE_PATTERN_EXT                                                    = 0x80AC,
        MULTISAMPLE_BIT_EXT                                                   = 0x20000000,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT                            = 0x8D6C,
        DRAW_BUFFER_EXT                                                       = 0xC01,
        READ_BUFFER_EXT                                                       = 0xC02,
        COLOR_ATTACHMENT_EXT                                                  = 0x90F0,
        MULTIVIEW_EXT                                                         = 0x90F1,
        MAX_MULTIVIEW_BUFFERS_EXT                                             = 0x90F2,
        DEPTH_STENCIL_EXT                                                     = 0x84F9,
        UNSIGNED_INT_24_8_EXT                                                 = 0x84FA,
        DEPTH24_STENCIL8_EXT                                                  = 0x88F0,
        TEXTURE_STENCIL_SIZE_EXT                                              = 0x88F1,
        R11F_G11F_B10F_EXT                                                    = 0x8C3A,
        UNSIGNED_INT_10F_11F_11F_REV_EXT                                      = 0x8C3B,
        RGBA_SIGNED_COMPONENTS_EXT                                            = 0x8C3C,
        UNSIGNED_BYTE_3_3_2_EXT                                               = 0x8032,
        UNSIGNED_SHORT_4_4_4_4_EXT                                            = 0x8033,
        UNSIGNED_SHORT_5_5_5_1_EXT                                            = 0x8034,
        UNSIGNED_INT_8_8_8_8_EXT                                              = 0x8035,
        UNSIGNED_INT_10_10_10_2_EXT                                           = 0x8036,
        COLOR_TABLE_FORMAT_EXT                                                = 0x80D8,
        COLOR_TABLE_WIDTH_EXT                                                 = 0x80D9,
        COLOR_TABLE_RED_SIZE_EXT                                              = 0x80DA,
        COLOR_TABLE_GREEN_SIZE_EXT                                            = 0x80DB,
        COLOR_TABLE_BLUE_SIZE_EXT                                             = 0x80DC,
        COLOR_TABLE_ALPHA_SIZE_EXT                                            = 0x80DD,
        COLOR_TABLE_LUMINANCE_SIZE_EXT                                        = 0x80DE,
        COLOR_TABLE_INTENSITY_SIZE_EXT                                        = 0x80DF,
        TEXTURE_INDEX_SIZE_EXT                                                = 0x80ED,
        PIXEL_PACK_BUFFER_EXT                                                 = 0x88EB,
        PIXEL_UNPACK_BUFFER_EXT                                               = 0x88EC,
        PIXEL_PACK_BUFFER_BINDING_EXT                                         = 0x88ED,
        PIXEL_UNPACK_BUFFER_BINDING_EXT                                       = 0x88EF,
        PIXEL_TRANSFORM_2D_EXT                                                = 0x8330,
        PIXEL_MAG_FILTER_EXT                                                  = 0x8331,
        PIXEL_MIN_FILTER_EXT                                                  = 0x8332,
        PIXEL_CUBIC_WEIGHT_EXT                                                = 0x8333,
        CUBIC_EXT                                                             = 0x8334,
        AVERAGE_EXT                                                           = 0x8335,
        PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT                                    = 0x8336,
        MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT                                = 0x8337,
        PIXEL_TRANSFORM_2D_MATRIX_EXT                                         = 0x8338,
        POINT_SIZE_MIN_EXT                                                    = 0x8126,
        POINT_SIZE_MAX_EXT                                                    = 0x8127,
        POINT_FADE_THRESHOLD_SIZE_EXT                                         = 0x8128,
        DISTANCE_ATTENUATION_EXT                                              = 0x8129,
        POLYGON_OFFSET_EXT                                                    = 0x8037,
        POLYGON_OFFSET_FACTOR_EXT                                             = 0x8038,
        POLYGON_OFFSET_BIAS_EXT                                               = 0x8039,
        POLYGON_OFFSET_CLAMP_EXT                                              = 0x8E1B,
        QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION_EXT                          = 0x8E4C,
        PROVOKING_VERTEX_EXT                                                  = 0x8E4F,
        COMPRESSED_SRGB_PVRTC_2BPPV1_EXT                                      = 0x8A54,
        COMPRESSED_SRGB_PVRTC_4BPPV1_EXT                                      = 0x8A55,
        COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT                                = 0x8A56,
        COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT                                = 0x8A57,
        COLOR_SAMPLES_NV                                                      = 0x8E20,
        RASTER_MULTISAMPLE_EXT                                                = 0x9327,
        RASTER_SAMPLES_EXT                                                    = 0x9328,
        MAX_RASTER_SAMPLES_EXT                                                = 0x9329,
        RASTER_FIXED_SAMPLE_LOCATIONS_EXT                                     = 0x932A,
        MULTISAMPLE_RASTERIZATION_ALLOWED_EXT                                 = 0x932B,
        EFFECTIVE_RASTER_SAMPLES_EXT                                          = 0x932C,
        DEPTH_SAMPLES_NV                                                      = 0x932D,
        STENCIL_SAMPLES_NV                                                    = 0x932E,
        MIXED_DEPTH_SAMPLES_SUPPORTED_NV                                      = 0x932F,
        MIXED_STENCIL_SAMPLES_SUPPORTED_NV                                    = 0x9330,
        COVERAGE_MODULATION_TABLE_NV                                          = 0x9331,
        COVERAGE_MODULATION_NV                                                = 0x9332,
        COVERAGE_MODULATION_TABLE_SIZE_NV                                     = 0x9333,
        UNSIGNED_SHORT_4_4_4_4_REV_EXT                                        = 0x8365,
        UNSIGNED_SHORT_1_5_5_5_REV_EXT                                        = 0x8366,
        R16_SNORM_EXT                                                         = 0x8F98,
        RG16_SNORM_EXT                                                        = 0x8F99,
        RGBA16_SNORM_EXT                                                      = 0x8F9B,
        RESCALE_NORMAL_EXT                                                    = 0x803A,
        FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT                             = 0x8210,
        SRGB_EXT                                                              = 0x8C40,
        SRGB_ALPHA_EXT                                                        = 0x8C42,
        SRGB8_ALPHA8_EXT                                                      = 0x8C43,
        COLOR_SUM_EXT                                                         = 0x8458,
        CURRENT_SECONDARY_COLOR_EXT                                           = 0x8459,
        SECONDARY_COLOR_ARRAY_SIZE_EXT                                        = 0x845A,
        SECONDARY_COLOR_ARRAY_TYPE_EXT                                        = 0x845B,
        SECONDARY_COLOR_ARRAY_STRIDE_EXT                                      = 0x845C,
        SECONDARY_COLOR_ARRAY_POINTER_EXT                                     = 0x845D,
        SECONDARY_COLOR_ARRAY_EXT                                             = 0x845E,
        ACTIVE_PROGRAM_EXT                                                    = 0x8B8D,
        LIGHT_MODEL_COLOR_CONTROL_EXT                                         = 0x81F8,
        SINGLE_COLOR_EXT                                                      = 0x81F9,
        SEPARATE_SPECULAR_COLOR_EXT                                           = 0x81FA,
        FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT                                  = 0x8A52,
        VERTEX_ATTRIB_ARRAY_BARRIER_BIT_EXT                                   = 0x1,
        ELEMENT_ARRAY_BARRIER_BIT_EXT                                         = 0x2,
        UNIFORM_BARRIER_BIT_EXT                                               = 0x4,
        TEXTURE_FETCH_BARRIER_BIT_EXT                                         = 0x8,
        SHADER_IMAGE_ACCESS_BARRIER_BIT_EXT                                   = 0x20,
        COMMAND_BARRIER_BIT_EXT                                               = 0x40,
        PIXEL_BUFFER_BARRIER_BIT_EXT                                          = 0x80,
        TEXTURE_UPDATE_BARRIER_BIT_EXT                                        = 0x100,
        BUFFER_UPDATE_BARRIER_BIT_EXT                                         = 0x200,
        FRAMEBUFFER_BARRIER_BIT_EXT                                           = 0x400,
        TRANSFORM_FEEDBACK_BARRIER_BIT_EXT                                    = 0x800,
        ATOMIC_COUNTER_BARRIER_BIT_EXT                                        = 0x1000,
        MAX_IMAGE_UNITS_EXT                                                   = 0x8F38,
        MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS_EXT                     = 0x8F39,
        IMAGE_BINDING_NAME_EXT                                                = 0x8F3A,
        IMAGE_BINDING_LEVEL_EXT                                               = 0x8F3B,
        IMAGE_BINDING_LAYERED_EXT                                             = 0x8F3C,
        IMAGE_BINDING_LAYER_EXT                                               = 0x8F3D,
        IMAGE_BINDING_ACCESS_EXT                                              = 0x8F3E,
        IMAGE_1D_EXT                                                          = 0x904C,
        IMAGE_2D_EXT                                                          = 0x904D,
        IMAGE_3D_EXT                                                          = 0x904E,
        IMAGE_2D_RECT_EXT                                                     = 0x904F,
        IMAGE_CUBE_EXT                                                        = 0x9050,
        IMAGE_BUFFER_EXT                                                      = 0x9051,
        IMAGE_1D_ARRAY_EXT                                                    = 0x9052,
        IMAGE_2D_ARRAY_EXT                                                    = 0x9053,
        IMAGE_CUBE_MAP_ARRAY_EXT                                              = 0x9054,
        IMAGE_2D_MULTISAMPLE_EXT                                              = 0x9055,
        IMAGE_2D_MULTISAMPLE_ARRAY_EXT                                        = 0x9056,
        INT_IMAGE_1D_EXT                                                      = 0x9057,
        INT_IMAGE_2D_EXT                                                      = 0x9058,
        INT_IMAGE_3D_EXT                                                      = 0x9059,
        INT_IMAGE_2D_RECT_EXT                                                 = 0x905A,
        INT_IMAGE_CUBE_EXT                                                    = 0x905B,
        INT_IMAGE_BUFFER_EXT                                                  = 0x905C,
        INT_IMAGE_1D_ARRAY_EXT                                                = 0x905D,
        INT_IMAGE_2D_ARRAY_EXT                                                = 0x905E,
        INT_IMAGE_CUBE_MAP_ARRAY_EXT                                          = 0x905F,
        INT_IMAGE_2D_MULTISAMPLE_EXT                                          = 0x9060,
        INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT                                    = 0x9061,
        UNSIGNED_INT_IMAGE_1D_EXT                                             = 0x9062,
        UNSIGNED_INT_IMAGE_2D_EXT                                             = 0x9063,
        UNSIGNED_INT_IMAGE_3D_EXT                                             = 0x9064,
        UNSIGNED_INT_IMAGE_2D_RECT_EXT                                        = 0x9065,
        UNSIGNED_INT_IMAGE_CUBE_EXT                                           = 0x9066,
        UNSIGNED_INT_IMAGE_BUFFER_EXT                                         = 0x9067,
        UNSIGNED_INT_IMAGE_1D_ARRAY_EXT                                       = 0x9068,
        UNSIGNED_INT_IMAGE_2D_ARRAY_EXT                                       = 0x9069,
        UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT                                 = 0x906A,
        UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_EXT                                 = 0x906B,
        UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY_EXT                           = 0x906C,
        MAX_IMAGE_SAMPLES_EXT                                                 = 0x906D,
        IMAGE_BINDING_FORMAT_EXT                                              = 0x906E,
        ALL_BARRIER_BITS_EXT                                                  = 0xFFFFFFFF,
        MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT                          = 0x8F63,
        SHADER_PIXEL_LOCAL_STORAGE_EXT                                        = 0x8F64,
        MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT                               = 0x8F67,
        MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_SIZE_EXT                       = 0x9650,
        MAX_SHADER_COMBINED_LOCAL_STORAGE_SIZE_EXT                            = 0x9651,
        FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT = 0x9652,
        TEXTURE_COMPARE_MODE_EXT                                              = 0x884C,
        TEXTURE_COMPARE_FUNC_EXT                                              = 0x884D,
        COMPARE_REF_TO_TEXTURE_EXT                                            = 0x884E,
        SAMPLER_2D_SHADOW_EXT                                                 = 0x8B62,
        SHARED_TEXTURE_PALETTE_EXT                                            = 0x81FB,
        TEXTURE_CUBE_MAP_ARRAY_OES                                            = 0x9009,
        VIRTUAL_PAGE_SIZE_X_EXT                                               = 0x9195,
        VIRTUAL_PAGE_SIZE_Y_EXT                                               = 0x9196,
        VIRTUAL_PAGE_SIZE_Z_EXT                                               = 0x9197,
        MAX_SPARSE_TEXTURE_SIZE_EXT                                           = 0x9198,
        MAX_SPARSE_3D_TEXTURE_SIZE_EXT                                        = 0x9199,
        MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT                                   = 0x919A,
        TEXTURE_SPARSE_EXT                                                    = 0x91A6,
        VIRTUAL_PAGE_SIZE_INDEX_EXT                                           = 0x91A7,
        NUM_VIRTUAL_PAGE_SIZES_EXT                                            = 0x91A8,
        SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_EXT                            = 0x91A9,
        NUM_SPARSE_LEVELS_EXT                                                 = 0x91AA,
        STENCIL_TAG_BITS_EXT                                                  = 0x88F2,
        STENCIL_CLEAR_TAG_VALUE_EXT                                           = 0x88F3,
        STENCIL_TEST_TWO_SIDE_EXT                                             = 0x8910,
        ACTIVE_STENCIL_FACE_EXT                                               = 0x8911,
        INCR_WRAP_EXT                                                         = 0x8507,
        DECR_WRAP_EXT                                                         = 0x8508,
        ALPHA4_EXT                                                            = 0x803B,
        ALPHA8_EXT                                                            = 0x803C,
        ALPHA12_EXT                                                           = 0x803D,
        ALPHA16_EXT                                                           = 0x803E,
        LUMINANCE4_EXT                                                        = 0x803F,
        LUMINANCE8_EXT                                                        = 0x8040,
        LUMINANCE12_EXT                                                       = 0x8041,
        LUMINANCE16_EXT                                                       = 0x8042,
        LUMINANCE4_ALPHA4_EXT                                                 = 0x8043,
        LUMINANCE6_ALPHA2_EXT                                                 = 0x8044,
        LUMINANCE8_ALPHA8_EXT                                                 = 0x8045,
        LUMINANCE12_ALPHA4_EXT                                                = 0x8046,
        LUMINANCE12_ALPHA12_EXT                                               = 0x8047,
        LUMINANCE16_ALPHA16_EXT                                               = 0x8048,
        INTENSITY_EXT                                                         = 0x8049,
        INTENSITY4_EXT                                                        = 0x804A,
        INTENSITY8_EXT                                                        = 0x804B,
        INTENSITY12_EXT                                                       = 0x804C,
        INTENSITY16_EXT                                                       = 0x804D,
        RGB2_EXT                                                              = 0x804E,
        RGB4_EXT                                                              = 0x804F,
        RGB5_EXT                                                              = 0x8050,
        RGB8_EXT                                                              = 0x8051,
        RGB10_EXT                                                             = 0x8052,
        RGB12_EXT                                                             = 0x8053,
        RGB16_EXT                                                             = 0x8054,
        RGBA2_EXT                                                             = 0x8055,
        RGBA4_EXT                                                             = 0x8056,
        RGB5_A1_EXT                                                           = 0x8057,
        RGBA8_EXT                                                             = 0x8058,
        RGB10_A2_EXT                                                          = 0x8059,
        RGBA12_EXT                                                            = 0x805A,
        RGBA16_EXT                                                            = 0x805B,
        TEXTURE_RED_SIZE_EXT                                                  = 0x805C,
        TEXTURE_GREEN_SIZE_EXT                                                = 0x805D,
        TEXTURE_BLUE_SIZE_EXT                                                 = 0x805E,
        TEXTURE_ALPHA_SIZE_EXT                                                = 0x805F,
        TEXTURE_LUMINANCE_SIZE_EXT                                            = 0x8060,
        TEXTURE_INTENSITY_SIZE_EXT                                            = 0x8061,
        REPLACE_EXT                                                           = 0x8062,
        PROXY_TEXTURE_1D_EXT                                                  = 0x8063,
        PROXY_TEXTURE_2D_EXT                                                  = 0x8064,
        PACK_SKIP_IMAGES_EXT                                                  = 0x806B,
        PACK_IMAGE_HEIGHT_EXT                                                 = 0x806C,
        UNPACK_SKIP_IMAGES_EXT                                                = 0x806D,
        UNPACK_IMAGE_HEIGHT_EXT                                               = 0x806E,
        TEXTURE_3D_EXT                                                        = 0x806F,
        PROXY_TEXTURE_3D_EXT                                                  = 0x8070,
        TEXTURE_DEPTH_EXT                                                     = 0x8071,
        TEXTURE_WRAP_R_EXT                                                    = 0x8072,
        MAX_3D_TEXTURE_SIZE_EXT                                               = 0x8073,
        COMPARE_REF_DEPTH_TO_TEXTURE_EXT                                      = 0x884E,
        MAX_ARRAY_TEXTURE_LAYERS_EXT                                          = 0x88FF,
        TEXTURE_1D_ARRAY_EXT                                                  = 0x8C18,
        PROXY_TEXTURE_1D_ARRAY_EXT                                            = 0x8C19,
        TEXTURE_2D_ARRAY_EXT                                                  = 0x8C1A,
        PROXY_TEXTURE_2D_ARRAY_EXT                                            = 0x8C1B,
        TEXTURE_BINDING_1D_ARRAY_EXT                                          = 0x8C1C,
        TEXTURE_BINDING_2D_ARRAY_EXT                                          = 0x8C1D,
        TEXTURE_BUFFER_EXT                                                    = 0x8C2A,
        MAX_TEXTURE_BUFFER_SIZE_EXT                                           = 0x8C2B,
        TEXTURE_BINDING_BUFFER_EXT                                            = 0x8C2C,
        TEXTURE_BUFFER_DATA_STORE_BINDING_EXT                                 = 0x8C2D,
        TEXTURE_BUFFER_FORMAT_EXT                                             = 0x8C2E,
        TEXTURE_ASTC_DECODE_PRECISION_EXT                                     = 0x8F69,
        COMPRESSED_RGBA_BPTC_UNORM_EXT                                        = 0x8E8C,
        COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT                                  = 0x8E8D,
        COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT                                  = 0x8E8E,
        COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT                                = 0x8E8F,
        COMPRESSED_LUMINANCE_LATC1_EXT                                        = 0x8C70,
        COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT                                 = 0x8C71,
        COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT                                  = 0x8C72,
        COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT                           = 0x8C73,
        COMPRESSED_RED_RGTC1_EXT                                              = 0x8DBB,
        COMPRESSED_SIGNED_RED_RGTC1_EXT                                       = 0x8DBC,
        COMPRESSED_RED_GREEN_RGTC2_EXT                                        = 0x8DBD,
        COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT                                 = 0x8DBE,
        COMPRESSED_RGB_S3TC_DXT1_EXT                                          = 0x83F0,
        COMPRESSED_RGBA_S3TC_DXT1_EXT                                         = 0x83F1,
        COMPRESSED_RGBA_S3TC_DXT3_EXT                                         = 0x83F2,
        COMPRESSED_RGBA_S3TC_DXT5_EXT                                         = 0x83F3,
        NORMAL_MAP_EXT                                                        = 0x8511,
        REFLECTION_MAP_EXT                                                    = 0x8512,
        TEXTURE_CUBE_MAP_EXT                                                  = 0x8513,
        TEXTURE_BINDING_CUBE_MAP_EXT                                          = 0x8514,
        TEXTURE_CUBE_MAP_POSITIVE_X_EXT                                       = 0x8515,
        TEXTURE_CUBE_MAP_NEGATIVE_X_EXT                                       = 0x8516,
        TEXTURE_CUBE_MAP_POSITIVE_Y_EXT                                       = 0x8517,
        TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT                                       = 0x8518,
        TEXTURE_CUBE_MAP_POSITIVE_Z_EXT                                       = 0x8519,
        TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT                                       = 0x851A,
        PROXY_TEXTURE_CUBE_MAP_EXT                                            = 0x851B,
        MAX_CUBE_MAP_TEXTURE_SIZE_EXT                                         = 0x851C,
        TEXTURE_CUBE_MAP_ARRAY_EXT                                            = 0x9009,
        TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT                                    = 0x900A,
        SAMPLER_CUBE_MAP_ARRAY_EXT                                            = 0x900C,
        SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT                                     = 0x900D,
        INT_SAMPLER_CUBE_MAP_ARRAY_EXT                                        = 0x900E,
        UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT                               = 0x900F,
        CLAMP_TO_EDGE_EXT                                                     = 0x812F,
        COMBINE_EXT                                                           = 0x8570,
        COMBINE_RGB_EXT                                                       = 0x8571,
        COMBINE_ALPHA_EXT                                                     = 0x8572,
        RGB_SCALE_EXT                                                         = 0x8573,
        ADD_SIGNED_EXT                                                        = 0x8574,
        INTERPOLATE_EXT                                                       = 0x8575,
        CONSTANT_EXT                                                          = 0x8576,
        PRIMARY_COLOR_EXT                                                     = 0x8577,
        PREVIOUS_EXT                                                          = 0x8578,
        SOURCE0_RGB_EXT                                                       = 0x8580,
        SOURCE1_RGB_EXT                                                       = 0x8581,
        SOURCE2_RGB_EXT                                                       = 0x8582,
        SOURCE0_ALPHA_EXT                                                     = 0x8588,
        SOURCE1_ALPHA_EXT                                                     = 0x8589,
        SOURCE2_ALPHA_EXT                                                     = 0x858A,
        OPERAND0_RGB_EXT                                                      = 0x8590,
        OPERAND1_RGB_EXT                                                      = 0x8591,
        OPERAND2_RGB_EXT                                                      = 0x8592,
        OPERAND0_ALPHA_EXT                                                    = 0x8598,
        OPERAND1_ALPHA_EXT                                                    = 0x8599,
        OPERAND2_ALPHA_EXT                                                    = 0x859A,
        DOT3_RGB_EXT                                                          = 0x8740,
        DOT3_RGBA_EXT                                                         = 0x8741,
        TEXTURE_MAX_ANISOTROPY_EXT                                            = 0x84FE,
        MAX_TEXTURE_MAX_ANISOTROPY_EXT                                        = 0x84FF,
        TEXTURE_REDUCTION_MODE_EXT                                            = 0x9366,
        WEIGHTED_AVERAGE_EXT                                                  = 0x9367,
        RGBA32UI_EXT                                                          = 0x8D70,
        RGB32UI_EXT                                                           = 0x8D71,
        ALPHA32UI_EXT                                                         = 0x8D72,
        INTENSITY32UI_EXT                                                     = 0x8D73,
        LUMINANCE32UI_EXT                                                     = 0x8D74,
        LUMINANCE_ALPHA32UI_EXT                                               = 0x8D75,
        RGBA16UI_EXT                                                          = 0x8D76,
        RGB16UI_EXT                                                           = 0x8D77,
        ALPHA16UI_EXT                                                         = 0x8D78,
        INTENSITY16UI_EXT                                                     = 0x8D79,
        LUMINANCE16UI_EXT                                                     = 0x8D7A,
        LUMINANCE_ALPHA16UI_EXT                                               = 0x8D7B,
        RGBA8UI_EXT                                                           = 0x8D7C,
        RGB8UI_EXT                                                            = 0x8D7D,
        ALPHA8UI_EXT                                                          = 0x8D7E,
        INTENSITY8UI_EXT                                                      = 0x8D7F,
        LUMINANCE8UI_EXT                                                      = 0x8D80,
        LUMINANCE_ALPHA8UI_EXT                                                = 0x8D81,
        RGBA32I_EXT                                                           = 0x8D82,
        RGB32I_EXT                                                            = 0x8D83,
        ALPHA32I_EXT                                                          = 0x8D84,
        INTENSITY32I_EXT                                                      = 0x8D85,
        LUMINANCE32I_EXT                                                      = 0x8D86,
        LUMINANCE_ALPHA32I_EXT                                                = 0x8D87,
        RGBA16I_EXT                                                           = 0x8D88,
        RGB16I_EXT                                                            = 0x8D89,
        ALPHA16I_EXT                                                          = 0x8D8A,
        INTENSITY16I_EXT                                                      = 0x8D8B,
        LUMINANCE16I_EXT                                                      = 0x8D8C,
        LUMINANCE_ALPHA16I_EXT                                                = 0x8D8D,
        RGBA8I_EXT                                                            = 0x8D8E,
        RGB8I_EXT                                                             = 0x8D8F,
        ALPHA8I_EXT                                                           = 0x8D90,
        INTENSITY8I_EXT                                                       = 0x8D91,
        LUMINANCE8I_EXT                                                       = 0x8D92,
        LUMINANCE_ALPHA8I_EXT                                                 = 0x8D93,
        RED_INTEGER_EXT                                                       = 0x8D94,
        GREEN_INTEGER_EXT                                                     = 0x8D95,
        BLUE_INTEGER_EXT                                                      = 0x8D96,
        ALPHA_INTEGER_EXT                                                     = 0x8D97,
        RGB_INTEGER_EXT                                                       = 0x8D98,
        RGBA_INTEGER_EXT                                                      = 0x8D99,
        BGR_INTEGER_EXT                                                       = 0x8D9A,
        BGRA_INTEGER_EXT                                                      = 0x8D9B,
        LUMINANCE_INTEGER_EXT                                                 = 0x8D9C,
        LUMINANCE_ALPHA_INTEGER_EXT                                           = 0x8D9D,
        RGBA_INTEGER_MODE_EXT                                                 = 0x8D9E,
        MAX_TEXTURE_LOD_BIAS_EXT                                              = 0x84FD,
        TEXTURE_FILTER_CONTROL_EXT                                            = 0x8500,
        TEXTURE_LOD_BIAS_EXT                                                  = 0x8501,
        MIRROR_CLAMP_EXT                                                      = 0x8742,
        MIRROR_CLAMP_TO_EDGE_EXT                                              = 0x8743,
        MIRROR_CLAMP_TO_BORDER_EXT                                            = 0x8912,
        R16_EXT                                                               = 0x822A,
        RG16_EXT                                                              = 0x822C,
        RGB16_SNORM_EXT                                                       = 0x8F9A,
        TEXTURE_PRIORITY_EXT                                                  = 0x8066,
        TEXTURE_RESIDENT_EXT                                                  = 0x8067,
        TEXTURE_1D_BINDING_EXT                                                = 0x8068,
        TEXTURE_2D_BINDING_EXT                                                = 0x8069,
        TEXTURE_3D_BINDING_EXT                                                = 0x806A,
        PERTURB_EXT                                                           = 0x85AE,
        TEXTURE_NORMAL_EXT                                                    = 0x85AF,
        TEXTURE_RECTANGLE_EXT                                                 = 0x84F5,
        TEXTURE_BINDING_RECTANGLE_EXT                                         = 0x84F6,
        PROXY_TEXTURE_RECTANGLE_EXT                                           = 0x84F7,
        MAX_RECTANGLE_TEXTURE_SIZE_EXT                                        = 0x84F8,
        RED_EXT                                                               = 0x1903,
        RG_EXT                                                                = 0x8227,
        R8_EXT                                                                = 0x8229,
        RG8_EXT                                                               = 0x822B,
        SRGB8_EXT                                                             = 0x8C41,
        SLUMINANCE_ALPHA_EXT                                                  = 0x8C44,
        SLUMINANCE8_ALPHA8_EXT                                                = 0x8C45,
        SLUMINANCE_EXT                                                        = 0x8C46,
        SLUMINANCE8_EXT                                                       = 0x8C47,
        COMPRESSED_SRGB_EXT                                                   = 0x8C48,
        COMPRESSED_SRGB_ALPHA_EXT                                             = 0x8C49,
        COMPRESSED_SLUMINANCE_EXT                                             = 0x8C4A,
        COMPRESSED_SLUMINANCE_ALPHA_EXT                                       = 0x8C4B,
        COMPRESSED_SRGB_S3TC_DXT1_EXT                                         = 0x8C4C,
        COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT                                   = 0x8C4D,
        COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT                                   = 0x8C4E,
        COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT                                   = 0x8C4F,
        SR8_EXT                                                               = 0x8FBD,
        SRG8_EXT                                                              = 0x8FBE,
        TEXTURE_SRGB_DECODE_EXT                                               = 0x8A48,
        DECODE_EXT                                                            = 0x8A49,
        SKIP_DECODE_EXT                                                       = 0x8A4A,
        RGB9_E5_EXT                                                           = 0x8C3D,
        UNSIGNED_INT_5_9_9_9_REV_EXT                                          = 0x8C3E,
        TEXTURE_SHARED_SIZE_EXT                                               = 0x8C3F,
        ALPHA_SNORM                                                           = 0x9010,
        LUMINANCE_SNORM                                                       = 0x9011,
        LUMINANCE_ALPHA_SNORM                                                 = 0x9012,
        INTENSITY_SNORM                                                       = 0x9013,
        ALPHA8_SNORM                                                          = 0x9014,
        LUMINANCE8_SNORM                                                      = 0x9015,
        LUMINANCE8_ALPHA8_SNORM                                               = 0x9016,
        INTENSITY8_SNORM                                                      = 0x9017,
        ALPHA16_SNORM                                                         = 0x9018,
        LUMINANCE16_SNORM                                                     = 0x9019,
        LUMINANCE16_ALPHA16_SNORM                                             = 0x901A,
        INTENSITY16_SNORM                                                     = 0x901B,
        R32F_EXT                                                              = 0x822E,
        RG32F_EXT                                                             = 0x8230,
        RGBA32F_EXT                                                           = 0x8814,
        RGB32F_EXT                                                            = 0x8815,
        ALPHA32F_EXT                                                          = 0x8816,
        LUMINANCE32F_EXT                                                      = 0x8818,
        LUMINANCE_ALPHA32F_EXT                                                = 0x8819,
        ALPHA16F_EXT                                                          = 0x881C,
        LUMINANCE16F_EXT                                                      = 0x881E,
        LUMINANCE_ALPHA16F_EXT                                                = 0x881F,
        TEXTURE_IMMUTABLE_FORMAT_EXT                                          = 0x912F,
        TEXTURE_SWIZZLE_R_EXT                                                 = 0x8E42,
        TEXTURE_SWIZZLE_G_EXT                                                 = 0x8E43,
        TEXTURE_SWIZZLE_B_EXT                                                 = 0x8E44,
        TEXTURE_SWIZZLE_A_EXT                                                 = 0x8E45,
        TEXTURE_SWIZZLE_RGBA_EXT                                              = 0x8E46,
        UNSIGNED_INT_2_10_10_10_REV_EXT                                       = 0x8368,
        TEXTURE_VIEW_MIN_LEVEL_EXT                                            = 0x82DB,
        TEXTURE_VIEW_NUM_LEVELS_EXT                                           = 0x82DC,
        TEXTURE_VIEW_MIN_LAYER_EXT                                            = 0x82DD,
        TEXTURE_VIEW_NUM_LAYERS_EXT                                           = 0x82DE,
        TIME_ELAPSED_EXT                                                      = 0x88BF,
        TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH_EXT                             = 0x8C76,
        TRANSFORM_FEEDBACK_BUFFER_MODE_EXT                                    = 0x8C7F,
        MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT                        = 0x8C80,
        TRANSFORM_FEEDBACK_VARYINGS_EXT                                       = 0x8C83,
        TRANSFORM_FEEDBACK_BUFFER_START_EXT                                   = 0x8C84,
        TRANSFORM_FEEDBACK_BUFFER_SIZE_EXT                                    = 0x8C85,
        TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT                             = 0x8C88,
        RASTERIZER_DISCARD_EXT                                                = 0x8C89,
        MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT                     = 0x8C8A,
        MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_EXT                           = 0x8C8B,
        INTERLEAVED_ATTRIBS_EXT                                               = 0x8C8C,
        SEPARATE_ATTRIBS_EXT                                                  = 0x8C8D,
        TRANSFORM_FEEDBACK_BUFFER_EXT                                         = 0x8C8E,
        TRANSFORM_FEEDBACK_BUFFER_BINDING_EXT                                 = 0x8C8F,
        UNPACK_ROW_LENGTH_EXT                                                 = 0xCF2,
        UNPACK_SKIP_ROWS_EXT                                                  = 0xCF3,
        UNPACK_SKIP_PIXELS_EXT                                                = 0xCF4,
        DOUBLE_EXT                                                            = 0x140A,
        VERTEX_ARRAY_EXT                                                      = 0x8074,
        NORMAL_ARRAY_EXT                                                      = 0x8075,
        COLOR_ARRAY_EXT                                                       = 0x8076,
        INDEX_ARRAY_EXT                                                       = 0x8077,
        TEXTURE_COORD_ARRAY_EXT                                               = 0x8078,
        EDGE_FLAG_ARRAY_EXT                                                   = 0x8079,
        VERTEX_ARRAY_SIZE_EXT                                                 = 0x807A,
        VERTEX_ARRAY_TYPE_EXT                                                 = 0x807B,
        VERTEX_ARRAY_STRIDE_EXT                                               = 0x807C,
        VERTEX_ARRAY_COUNT_EXT                                                = 0x807D,
        NORMAL_ARRAY_TYPE_EXT                                                 = 0x807E,
        NORMAL_ARRAY_STRIDE_EXT                                               = 0x807F,
        NORMAL_ARRAY_COUNT_EXT                                                = 0x8080,
        COLOR_ARRAY_SIZE_EXT                                                  = 0x8081,
        COLOR_ARRAY_TYPE_EXT                                                  = 0x8082,
        COLOR_ARRAY_STRIDE_EXT                                                = 0x8083,
        COLOR_ARRAY_COUNT_EXT                                                 = 0x8084,
        INDEX_ARRAY_TYPE_EXT                                                  = 0x8085,
        INDEX_ARRAY_STRIDE_EXT                                                = 0x8086,
        INDEX_ARRAY_COUNT_EXT                                                 = 0x8087,
        TEXTURE_COORD_ARRAY_SIZE_EXT                                          = 0x8088,
        TEXTURE_COORD_ARRAY_TYPE_EXT                                          = 0x8089,
        TEXTURE_COORD_ARRAY_STRIDE_EXT                                        = 0x808A,
        TEXTURE_COORD_ARRAY_COUNT_EXT                                         = 0x808B,
        EDGE_FLAG_ARRAY_STRIDE_EXT                                            = 0x808C,
        EDGE_FLAG_ARRAY_COUNT_EXT                                             = 0x808D,
        VERTEX_ARRAY_POINTER_EXT                                              = 0x808E,
        NORMAL_ARRAY_POINTER_EXT                                              = 0x808F,
        COLOR_ARRAY_POINTER_EXT                                               = 0x8090,
        INDEX_ARRAY_POINTER_EXT                                               = 0x8091,
        TEXTURE_COORD_ARRAY_POINTER_EXT                                       = 0x8092,
        EDGE_FLAG_ARRAY_POINTER_EXT                                           = 0x8093,
        DOUBLE_MAT2_EXT                                                       = 0x8F46,
        DOUBLE_MAT3_EXT                                                       = 0x8F47,
        DOUBLE_MAT4_EXT                                                       = 0x8F48,
        DOUBLE_MAT2x3_EXT                                                     = 0x8F49,
        DOUBLE_MAT2x4_EXT                                                     = 0x8F4A,
        DOUBLE_MAT3x2_EXT                                                     = 0x8F4B,
        DOUBLE_MAT3x4_EXT                                                     = 0x8F4C,
        DOUBLE_MAT4x2_EXT                                                     = 0x8F4D,
        DOUBLE_MAT4x3_EXT                                                     = 0x8F4E,
        DOUBLE_VEC2_EXT                                                       = 0x8FFC,
        DOUBLE_VEC3_EXT                                                       = 0x8FFD,
        DOUBLE_VEC4_EXT                                                       = 0x8FFE,
        VERTEX_SHADER_EXT                                                     = 0x8780,
        VERTEX_SHADER_BINDING_EXT                                             = 0x8781,
        OP_INDEX_EXT                                                          = 0x8782,
        OP_NEGATE_EXT                                                         = 0x8783,
        OP_DOT3_EXT                                                           = 0x8784,
        OP_DOT4_EXT                                                           = 0x8785,
        OP_MUL_EXT                                                            = 0x8786,
        OP_ADD_EXT                                                            = 0x8787,
        OP_MADD_EXT                                                           = 0x8788,
        OP_FRAC_EXT                                                           = 0x8789,
        OP_MAX_EXT                                                            = 0x878A,
        OP_MIN_EXT                                                            = 0x878B,
        OP_SET_GE_EXT                                                         = 0x878C,
        OP_SET_LT_EXT                                                         = 0x878D,
        OP_CLAMP_EXT                                                          = 0x878E,
        OP_FLOOR_EXT                                                          = 0x878F,
        OP_ROUND_EXT                                                          = 0x8790,
        OP_EXP_BASE_2_EXT                                                     = 0x8791,
        OP_LOG_BASE_2_EXT                                                     = 0x8792,
        OP_POWER_EXT                                                          = 0x8793,
        OP_RECIP_EXT                                                          = 0x8794,
        OP_RECIP_SQRT_EXT                                                     = 0x8795,
        OP_SUB_EXT                                                            = 0x8796,
        OP_CROSS_PRODUCT_EXT                                                  = 0x8797,
        OP_MULTIPLY_MATRIX_EXT                                                = 0x8798,
        OP_MOV_EXT                                                            = 0x8799,
        OUTPUT_VERTEX_EXT                                                     = 0x879A,
        OUTPUT_COLOR0_EXT                                                     = 0x879B,
        OUTPUT_COLOR1_EXT                                                     = 0x879C,
        OUTPUT_TEXTURE_COORD0_EXT                                             = 0x879D,
        OUTPUT_TEXTURE_COORD1_EXT                                             = 0x879E,
        OUTPUT_TEXTURE_COORD2_EXT                                             = 0x879F,
        OUTPUT_TEXTURE_COORD3_EXT                                             = 0x87A0,
        OUTPUT_TEXTURE_COORD4_EXT                                             = 0x87A1,
        OUTPUT_TEXTURE_COORD5_EXT                                             = 0x87A2,
        OUTPUT_TEXTURE_COORD6_EXT                                             = 0x87A3,
        OUTPUT_TEXTURE_COORD7_EXT                                             = 0x87A4,
        OUTPUT_TEXTURE_COORD8_EXT                                             = 0x87A5,
        OUTPUT_TEXTURE_COORD9_EXT                                             = 0x87A6,
        OUTPUT_TEXTURE_COORD10_EXT                                            = 0x87A7,
        OUTPUT_TEXTURE_COORD11_EXT                                            = 0x87A8,
        OUTPUT_TEXTURE_COORD12_EXT                                            = 0x87A9,
        OUTPUT_TEXTURE_COORD13_EXT                                            = 0x87AA,
        OUTPUT_TEXTURE_COORD14_EXT                                            = 0x87AB,
        OUTPUT_TEXTURE_COORD15_EXT                                            = 0x87AC,
        OUTPUT_TEXTURE_COORD16_EXT                                            = 0x87AD,
        OUTPUT_TEXTURE_COORD17_EXT                                            = 0x87AE,
        OUTPUT_TEXTURE_COORD18_EXT                                            = 0x87AF,
        OUTPUT_TEXTURE_COORD19_EXT                                            = 0x87B0,
        OUTPUT_TEXTURE_COORD20_EXT                                            = 0x87B1,
        OUTPUT_TEXTURE_COORD21_EXT                                            = 0x87B2,
        OUTPUT_TEXTURE_COORD22_EXT                                            = 0x87B3,
        OUTPUT_TEXTURE_COORD23_EXT                                            = 0x87B4,
        OUTPUT_TEXTURE_COORD24_EXT                                            = 0x87B5,
        OUTPUT_TEXTURE_COORD25_EXT                                            = 0x87B6,
        OUTPUT_TEXTURE_COORD26_EXT                                            = 0x87B7,
        OUTPUT_TEXTURE_COORD27_EXT                                            = 0x87B8,
        OUTPUT_TEXTURE_COORD28_EXT                                            = 0x87B9,
        OUTPUT_TEXTURE_COORD29_EXT                                            = 0x87BA,
        OUTPUT_TEXTURE_COORD30_EXT                                            = 0x87BB,
        OUTPUT_TEXTURE_COORD31_EXT                                            = 0x87BC,
        OUTPUT_FOG_EXT                                                        = 0x87BD,
        SCALAR_EXT                                                            = 0x87BE,
        VECTOR_EXT                                                            = 0x87BF,
        MATRIX_EXT                                                            = 0x87C0,
        VARIANT_EXT                                                           = 0x87C1,
        INVARIANT_EXT                                                         = 0x87C2,
        LOCAL_CONSTANT_EXT                                                    = 0x87C3,
        LOCAL_EXT                                                             = 0x87C4,
        MAX_VERTEX_SHADER_INSTRUCTIONS_EXT                                    = 0x87C5,
        MAX_VERTEX_SHADER_VARIANTS_EXT                                        = 0x87C6,
        MAX_VERTEX_SHADER_INVARIANTS_EXT                                      = 0x87C7,
        MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT                                 = 0x87C8,
        MAX_VERTEX_SHADER_LOCALS_EXT                                          = 0x87C9,
        MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT                          = 0x87CA,
        MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT                              = 0x87CB,
        MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT                            = 0x87CC,
        MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT                       = 0x87CD,
        MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT                                = 0x87CE,
        VERTEX_SHADER_INSTRUCTIONS_EXT                                        = 0x87CF,
        VERTEX_SHADER_VARIANTS_EXT                                            = 0x87D0,
        VERTEX_SHADER_INVARIANTS_EXT                                          = 0x87D1,
        VERTEX_SHADER_LOCAL_CONSTANTS_EXT                                     = 0x87D2,
        VERTEX_SHADER_LOCALS_EXT                                              = 0x87D3,
        VERTEX_SHADER_OPTIMIZED_EXT                                           = 0x87D4,
        X_EXT                                                                 = 0x87D5,
        Y_EXT                                                                 = 0x87D6,
        Z_EXT                                                                 = 0x87D7,
        W_EXT                                                                 = 0x87D8,
        NEGATIVE_X_EXT                                                        = 0x87D9,
        NEGATIVE_Y_EXT                                                        = 0x87DA,
        NEGATIVE_Z_EXT                                                        = 0x87DB,
        NEGATIVE_W_EXT                                                        = 0x87DC,
        ZERO_EXT                                                              = 0x87DD,
        ONE_EXT                                                               = 0x87DE,
        NEGATIVE_ONE_EXT                                                      = 0x87DF,
        NORMALIZED_RANGE_EXT                                                  = 0x87E0,
        FULL_RANGE_EXT                                                        = 0x87E1,
        CURRENT_VERTEX_EXT                                                    = 0x87E2,
        MVP_MATRIX_EXT                                                        = 0x87E3,
        VARIANT_VALUE_EXT                                                     = 0x87E4,
        VARIANT_DATATYPE_EXT                                                  = 0x87E5,
        VARIANT_ARRAY_STRIDE_EXT                                              = 0x87E6,
        VARIANT_ARRAY_TYPE_EXT                                                = 0x87E7,
        VARIANT_ARRAY_EXT                                                     = 0x87E8,
        VARIANT_ARRAY_POINTER_EXT                                             = 0x87E9,
        INVARIANT_VALUE_EXT                                                   = 0x87EA,
        INVARIANT_DATATYPE_EXT                                                = 0x87EB,
        LOCAL_CONSTANT_VALUE_EXT                                              = 0x87EC,
        LOCAL_CONSTANT_DATATYPE_EXT                                           = 0x87ED,
        MODELVIEW0_STACK_DEPTH_EXT                                            = 0xBA3,
        MODELVIEW0_MATRIX_EXT                                                 = 0xBA6,
        MODELVIEW0_EXT                                                        = 0x1700,
        MODELVIEW1_STACK_DEPTH_EXT                                            = 0x8502,
        MODELVIEW1_MATRIX_EXT                                                 = 0x8506,
        VERTEX_WEIGHTING_EXT                                                  = 0x8509,
        MODELVIEW1_EXT                                                        = 0x850A,
        CURRENT_VERTEX_WEIGHT_EXT                                             = 0x850B,
        VERTEX_WEIGHT_ARRAY_EXT                                               = 0x850C,
        VERTEX_WEIGHT_ARRAY_SIZE_EXT                                          = 0x850D,
        VERTEX_WEIGHT_ARRAY_TYPE_EXT                                          = 0x850E,
        VERTEX_WEIGHT_ARRAY_STRIDE_EXT                                        = 0x850F,
        VERTEX_WEIGHT_ARRAY_POINTER_EXT                                       = 0x8510,
        INCLUSIVE_EXT                                                         = 0x8F10,
        EXCLUSIVE_EXT                                                         = 0x8F11,
        WINDOW_RECTANGLE_EXT                                                  = 0x8F12,
        WINDOW_RECTANGLE_MODE_EXT                                             = 0x8F13,
        MAX_WINDOW_RECTANGLES_EXT                                             = 0x8F14,
        NUM_WINDOW_RECTANGLES_EXT                                             = 0x8F15,
        SYNC_X11_FENCE_EXT                                                    = 0x90E1,
        MIRRORED_REPEAT_IBM                                                   = 0x8370,
        RED_MIN_CLAMP_INGR                                                    = 0x8560,
        GREEN_MIN_CLAMP_INGR                                                  = 0x8561,
        BLUE_MIN_CLAMP_INGR                                                   = 0x8562,
        ALPHA_MIN_CLAMP_INGR                                                  = 0x8563,
        RED_MAX_CLAMP_INGR                                                    = 0x8564,
        GREEN_MAX_CLAMP_INGR                                                  = 0x8565,
        BLUE_MAX_CLAMP_INGR                                                   = 0x8566,
        ALPHA_MAX_CLAMP_INGR                                                  = 0x8567,
        INTERLACE_READ_INGR                                                   = 0x8568,
        CONSERVATIVE_RASTERIZATION_INTEL                                      = 0x83FE,
        TEXTURE_MEMORY_LAYOUT_INTEL                                           = 0x83FF,
        PARALLEL_ARRAYS_INTEL                                                 = 0x83F4,
        VERTEX_ARRAY_PARALLEL_POINTERS_INTEL                                  = 0x83F5,
        NORMAL_ARRAY_PARALLEL_POINTERS_INTEL                                  = 0x83F6,
        COLOR_ARRAY_PARALLEL_POINTERS_INTEL                                   = 0x83F7,
        TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL                           = 0x83F8,
        PERFQUERY_SINGLE_CONTEXT_INTEL                                        = 0x0,
        PERFQUERY_GLOBAL_CONTEXT_INTEL                                        = 0x1,
        PERFQUERY_DONOT_FLUSH_INTEL                                           = 0x83F9,
        PERFQUERY_FLUSH_INTEL                                                 = 0x83FA,
        PERFQUERY_WAIT_INTEL                                                  = 0x83FB,
        PERFQUERY_COUNTER_EVENT_INTEL                                         = 0x94F0,
        PERFQUERY_COUNTER_DURATION_NORM_INTEL                                 = 0x94F1,
        PERFQUERY_COUNTER_DURATION_RAW_INTEL                                  = 0x94F2,
        PERFQUERY_COUNTER_THROUGHPUT_INTEL                                    = 0x94F3,
        PERFQUERY_COUNTER_RAW_INTEL                                           = 0x94F4,
        PERFQUERY_COUNTER_TIMESTAMP_INTEL                                     = 0x94F5,
        PERFQUERY_COUNTER_DATA_UINT32_INTEL                                   = 0x94F8,
        PERFQUERY_COUNTER_DATA_UINT64_INTEL                                   = 0x94F9,
        PERFQUERY_COUNTER_DATA_FLOAT_INTEL                                    = 0x94FA,
        PERFQUERY_COUNTER_DATA_DOUBLE_INTEL                                   = 0x94FB,
        PERFQUERY_COUNTER_DATA_BOOL32_INTEL                                   = 0x94FC,
        PERFQUERY_QUERY_NAME_LENGTH_MAX_INTEL                                 = 0x94FD,
        PERFQUERY_COUNTER_NAME_LENGTH_MAX_INTEL                               = 0x94FE,
        PERFQUERY_COUNTER_DESC_LENGTH_MAX_INTEL                               = 0x94FF,
        PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL                                 = 0x9500,
        BLEND_ADVANCED_COHERENT_KHR                                           = 0x9285,
        MULTIPLY_KHR                                                          = 0x9294,
        SCREEN_KHR                                                            = 0x9295,
        OVERLAY_KHR                                                           = 0x9296,
        DARKEN_KHR                                                            = 0x9297,
        LIGHTEN_KHR                                                           = 0x9298,
        COLORDODGE_KHR                                                        = 0x9299,
        COLORBURN_KHR                                                         = 0x929A,
        HARDLIGHT_KHR                                                         = 0x929B,
        SOFTLIGHT_KHR                                                         = 0x929C,
        DIFFERENCE_KHR                                                        = 0x929E,
        EXCLUSION_KHR                                                         = 0x92A0,
        HSL_HUE_KHR                                                           = 0x92AD,
        HSL_SATURATION_KHR                                                    = 0x92AE,
        HSL_COLOR_KHR                                                         = 0x92AF,
        HSL_LUMINOSITY_KHR                                                    = 0x92B0,
        CONTEXT_FLAG_DEBUG_BIT                                                = 0x2,
        DEBUG_OUTPUT_SYNCHRONOUS                                              = 0x8242,
        DEBUG_NEXT_LOGGED_MESSAGE_LENGTH                                      = 0x8243,
        DEBUG_CALLBACK_FUNCTION                                               = 0x8244,
        DEBUG_CALLBACK_USER_PARAM                                             = 0x8245,
        DEBUG_SOURCE_API                                                      = 0x8246,
        DEBUG_SOURCE_WINDOW_SYSTEM                                            = 0x8247,
        DEBUG_SOURCE_SHADER_COMPILER                                          = 0x8248,
        DEBUG_SOURCE_THIRD_PARTY                                              = 0x8249,
        DEBUG_SOURCE_APPLICATION                                              = 0x824A,
        DEBUG_SOURCE_OTHER                                                    = 0x824B,
        DEBUG_TYPE_ERROR                                                      = 0x824C,
        DEBUG_TYPE_DEPRECATED_BEHAVIOR                                        = 0x824D,
        DEBUG_TYPE_UNDEFINED_BEHAVIOR                                         = 0x824E,
        DEBUG_TYPE_PORTABILITY                                                = 0x824F,
        DEBUG_TYPE_PERFORMANCE                                                = 0x8250,
        DEBUG_TYPE_OTHER                                                      = 0x8251,
        DEBUG_TYPE_MARKER                                                     = 0x8268,
        DEBUG_TYPE_PUSH_GROUP                                                 = 0x8269,
        DEBUG_TYPE_POP_GROUP                                                  = 0x826A,
        DEBUG_SEVERITY_NOTIFICATION                                           = 0x826B,
        MAX_DEBUG_GROUP_STACK_DEPTH                                           = 0x826C,
        DEBUG_GROUP_STACK_DEPTH                                               = 0x826D,
        BUFFER                                                                = 0x82E0,
        SHADER                                                                = 0x82E1,
        PROGRAM                                                               = 0x82E2,
        QUERY                                                                 = 0x82E3,
        PROGRAM_PIPELINE                                                      = 0x82E4,
        SAMPLER                                                               = 0x82E6,
        DISPLAY_LIST                                                          = 0x82E7,
        MAX_LABEL_LENGTH                                                      = 0x82E8,
        MAX_DEBUG_MESSAGE_LENGTH                                              = 0x9143,
        MAX_DEBUG_LOGGED_MESSAGES                                             = 0x9144,
        DEBUG_LOGGED_MESSAGES                                                 = 0x9145,
        DEBUG_SEVERITY_HIGH                                                   = 0x9146,
        DEBUG_SEVERITY_MEDIUM                                                 = 0x9147,
        DEBUG_SEVERITY_LOW                                                    = 0x9148,
        DEBUG_OUTPUT                                                          = 0x92E0,
        CONTEXT_FLAG_NO_ERROR_BIT_KHR                                         = 0x8,
        MAX_SHADER_COMPILER_THREADS_KHR                                       = 0x91B0,
        COMPLETION_STATUS_KHR                                                 = 0x91B1,
        CONTEXT_LOST                                                          = 0x507,
        LOSE_CONTEXT_ON_RESET                                                 = 0x8252,
        GUILTY_CONTEXT_RESET                                                  = 0x8253,
        INNOCENT_CONTEXT_RESET                                                = 0x8254,
        UNKNOWN_CONTEXT_RESET                                                 = 0x8255,
        RESET_NOTIFICATION_STRATEGY                                           = 0x8256,
        NO_RESET_NOTIFICATION                                                 = 0x8261,
        CONTEXT_ROBUST_ACCESS                                                 = 0x90F3,
        COMPRESSED_RGBA_ASTC_4x4_KHR                                          = 0x93B0,
        COMPRESSED_RGBA_ASTC_5x4_KHR                                          = 0x93B1,
        COMPRESSED_RGBA_ASTC_5x5_KHR                                          = 0x93B2,
        COMPRESSED_RGBA_ASTC_6x5_KHR                                          = 0x93B3,
        COMPRESSED_RGBA_ASTC_6x6_KHR                                          = 0x93B4,
        COMPRESSED_RGBA_ASTC_8x5_KHR                                          = 0x93B5,
        COMPRESSED_RGBA_ASTC_8x6_KHR                                          = 0x93B6,
        COMPRESSED_RGBA_ASTC_8x8_KHR                                          = 0x93B7,
        COMPRESSED_RGBA_ASTC_10x5_KHR                                         = 0x93B8,
        COMPRESSED_RGBA_ASTC_10x6_KHR                                         = 0x93B9,
        COMPRESSED_RGBA_ASTC_10x8_KHR                                         = 0x93BA,
        COMPRESSED_RGBA_ASTC_10x10_KHR                                        = 0x93BB,
        COMPRESSED_RGBA_ASTC_12x10_KHR                                        = 0x93BC,
        COMPRESSED_RGBA_ASTC_12x12_KHR                                        = 0x93BD,
        COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR                                  = 0x93D0,
        COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR                                  = 0x93D1,
        COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR                                  = 0x93D2,
        COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR                                  = 0x93D3,
        COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR                                  = 0x93D4,
        COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR                                  = 0x93D5,
        COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR                                  = 0x93D6,
        COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR                                  = 0x93D7,
        COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR                                 = 0x93D8,
        COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR                                 = 0x93D9,
        COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR                                 = 0x93DA,
        COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR                                = 0x93DB,
        COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR                                = 0x93DC,
        COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR                                = 0x93DD,
        KTX_FRONT_REGION                                                      = 0x0,
        KTX_BACK_REGION                                                       = 0x1,
        KTX_Z_REGION                                                          = 0x2,
        KTX_STENCIL_REGION                                                    = 0x3,
        TEXTURE_1D_STACK_MESAX                                                = 0x8759,
        TEXTURE_2D_STACK_MESAX                                                = 0x875A,
        PROXY_TEXTURE_1D_STACK_MESAX                                          = 0x875B,
        PROXY_TEXTURE_2D_STACK_MESAX                                          = 0x875C,
        TEXTURE_1D_STACK_BINDING_MESAX                                        = 0x875D,
        TEXTURE_2D_STACK_BINDING_MESAX                                        = 0x875E,
        PACK_INVERT_MESA                                                      = 0x8758,
        UNSIGNED_SHORT_8_8_MESA                                               = 0x85BA,
        UNSIGNED_SHORT_8_8_REV_MESA                                           = 0x85BB,
        YCBCR_MESA                                                            = 0x8757,
        GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX                                  = 0x9047,
        GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX                            = 0x9048,
        GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX                          = 0x9049,
        GPU_MEMORY_INFO_EVICTION_COUNT_NVX                                    = 0x904A,
        GPU_MEMORY_INFO_EVICTED_MEMORY_NVX                                    = 0x904B,
        LGPU_SEPARATE_STORAGE_BIT_NVX                                         = 0x800,
        MAX_LGPU_GPUS_NVX                                                     = 0x92BA,
        N3DVISION_STEREO_NV                                                   = 0x90F4,
        STEREO_SEPARATION_NV                                                  = 0x90F5,
        STEREO_CONVERGENCE_NV                                                 = 0x90F6,
        STEREO_CUTOFF_NV                                                      = 0x90F7,
        STEREO_PROJECTION_NV                                                  = 0x90F8,
        STEREO_PROJECTION_PERSPECTIVE_NV                                      = 0x90F9,
        STEREO_PROJECTION_ORTHO_NV                                            = 0x90FA,
        TEXTURE_EXTERNAL_OES                                                  = 0x8D65,
        SAMPLER_EXTERNAL_OES                                                  = 0x8D66,
        TEXTURE_BINDING_EXTERNAL_OES                                          = 0x8D67,
        REQUIRED_TEXTURE_IMAGE_UNITS_OES                                      = 0x8D68,
        ALPHA_TO_COVERAGE_DITHER_MODE_NV                                      = 0x92BF,
        ALPHA_TO_COVERAGE_DITHER_DEFAULT_NV                                   = 0x934D,
        ALPHA_TO_COVERAGE_DITHER_ENABLE_NV                                    = 0x934E,
        ALPHA_TO_COVERAGE_DITHER_DISABLE_NV                                   = 0x934F,
        BGR_NV                                                                = 0x80E0,
        XOR_NV                                                                = 0x1506,
        RED_NV                                                                = 0x1903,
        GREEN_NV                                                              = 0x1904,
        BLUE_NV                                                               = 0x1905,
        BLEND_PREMULTIPLIED_SRC_NV                                            = 0x9280,
        BLEND_OVERLAP_NV                                                      = 0x9281,
        UNCORRELATED_NV                                                       = 0x9282,
        DISJOINT_NV                                                           = 0x9283,
        CONJOINT_NV                                                           = 0x9284,
        BLEND_ADVANCED_COHERENT_NV                                            = 0x9285,
        SRC_NV                                                                = 0x9286,
        DST_NV                                                                = 0x9287,
        SRC_OVER_NV                                                           = 0x9288,
        DST_OVER_NV                                                           = 0x9289,
        SRC_IN_NV                                                             = 0x928A,
        DST_IN_NV                                                             = 0x928B,
        SRC_OUT_NV                                                            = 0x928C,
        DST_OUT_NV                                                            = 0x928D,
        SRC_ATOP_NV                                                           = 0x928E,
        DST_ATOP_NV                                                           = 0x928F,
        PLUS_NV                                                               = 0x9291,
        PLUS_DARKER_NV                                                        = 0x9292,
        MULTIPLY_NV                                                           = 0x9294,
        SCREEN_NV                                                             = 0x9295,
        OVERLAY_NV                                                            = 0x9296,
        DARKEN_NV                                                             = 0x9297,
        LIGHTEN_NV                                                            = 0x9298,
        COLORDODGE_NV                                                         = 0x9299,
        COLORBURN_NV                                                          = 0x929A,
        HARDLIGHT_NV                                                          = 0x929B,
        SOFTLIGHT_NV                                                          = 0x929C,
        DIFFERENCE_NV                                                         = 0x929E,
        MINUS_NV                                                              = 0x929F,
        EXCLUSION_NV                                                          = 0x92A0,
        CONTRAST_NV                                                           = 0x92A1,
        INVERT_RGB_NV                                                         = 0x92A3,
        LINEARDODGE_NV                                                        = 0x92A4,
        LINEARBURN_NV                                                         = 0x92A5,
        VIVIDLIGHT_NV                                                         = 0x92A6,
        LINEARLIGHT_NV                                                        = 0x92A7,
        PINLIGHT_NV                                                           = 0x92A8,
        HARDMIX_NV                                                            = 0x92A9,
        HSL_HUE_NV                                                            = 0x92AD,
        HSL_SATURATION_NV                                                     = 0x92AE,
        HSL_COLOR_NV                                                          = 0x92AF,
        HSL_LUMINOSITY_NV                                                     = 0x92B0,
        PLUS_CLAMPED_NV                                                       = 0x92B1,
        PLUS_CLAMPED_ALPHA_NV                                                 = 0x92B2,
        MINUS_CLAMPED_NV                                                      = 0x92B3,
        INVERT_OVG_NV                                                         = 0x92B4,
        VIEWPORT_POSITION_W_SCALE_NV                                          = 0x937C,
        VIEWPORT_POSITION_W_SCALE_X_COEFF_NV                                  = 0x937D,
        VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV                                  = 0x937E,
        TERMINATE_SEQUENCE_COMMAND_NV                                         = 0x0,
        NOP_COMMAND_NV                                                        = 0x1,
        DRAW_ELEMENTS_COMMAND_NV                                              = 0x2,
        DRAW_ARRAYS_COMMAND_NV                                                = 0x3,
        DRAW_ELEMENTS_STRIP_COMMAND_NV                                        = 0x4,
        DRAW_ARRAYS_STRIP_COMMAND_NV                                          = 0x5,
        DRAW_ELEMENTS_INSTANCED_COMMAND_NV                                    = 0x6,
        DRAW_ARRAYS_INSTANCED_COMMAND_NV                                      = 0x7,
        ELEMENT_ADDRESS_COMMAND_NV                                            = 0x8,
        ATTRIBUTE_ADDRESS_COMMAND_NV                                          = 0x9,
        UNIFORM_ADDRESS_COMMAND_NV                                            = 0xA,
        BLEND_COLOR_COMMAND_NV                                                = 0xB,
        STENCIL_REF_COMMAND_NV                                                = 0xC,
        LINE_WIDTH_COMMAND_NV                                                 = 0xD,
        POLYGON_OFFSET_COMMAND_NV                                             = 0xE,
        ALPHA_REF_COMMAND_NV                                                  = 0xF,
        VIEWPORT_COMMAND_NV                                                   = 0x10,
        SCISSOR_COMMAND_NV                                                    = 0x11,
        FRONT_FACE_COMMAND_NV                                                 = 0x12,
        COMPUTE_PROGRAM_NV                                                    = 0x90FB,
        COMPUTE_PROGRAM_PARAMETER_BUFFER_NV                                   = 0x90FC,
        QUERY_WAIT_NV                                                         = 0x8E13,
        QUERY_NO_WAIT_NV                                                      = 0x8E14,
        QUERY_BY_REGION_WAIT_NV                                               = 0x8E15,
        QUERY_BY_REGION_NO_WAIT_NV                                            = 0x8E16,
        CONSERVATIVE_RASTERIZATION_NV                                         = 0x9346,
        SUBPIXEL_PRECISION_BIAS_X_BITS_NV                                     = 0x9347,
        SUBPIXEL_PRECISION_BIAS_Y_BITS_NV                                     = 0x9348,
        MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV                                   = 0x9349,
        CONSERVATIVE_RASTER_DILATE_NV                                         = 0x9379,
        CONSERVATIVE_RASTER_DILATE_RANGE_NV                                   = 0x937A,
        CONSERVATIVE_RASTER_DILATE_GRANULARITY_NV                             = 0x937B,
        CONSERVATIVE_RASTER_MODE_NV                                           = 0x954D,
        CONSERVATIVE_RASTER_MODE_POST_SNAP_NV                                 = 0x954E,
        CONSERVATIVE_RASTER_MODE_PRE_SNAP_TRIANGLES_NV                        = 0x954F,
        COPY_READ_BUFFER_NV                                                   = 0x8F36,
        COPY_WRITE_BUFFER_NV                                                  = 0x8F37,
        DEPTH_STENCIL_TO_RGBA_NV                                              = 0x886E,
        DEPTH_STENCIL_TO_BGRA_NV                                              = 0x886F,
        MAX_DEEP_3D_TEXTURE_WIDTH_HEIGHT_NV                                   = 0x90D0,
        MAX_DEEP_3D_TEXTURE_DEPTH_NV                                          = 0x90D1,
        DEPTH_COMPONENT32F_NV                                                 = 0x8DAB,
        DEPTH32F_STENCIL8_NV                                                  = 0x8DAC,
        FLOAT_32_UNSIGNED_INT_24_8_REV_NV                                     = 0x8DAD,
        DEPTH_BUFFER_FLOAT_MODE_NV                                            = 0x8DAF,
        DEPTH_CLAMP_NV                                                        = 0x864F,
        SAMPLE_COUNT_BITS_NV                                                  = 0x8864,
        CURRENT_SAMPLE_COUNT_QUERY_NV                                         = 0x8865,
        QUERY_RESULT_NV                                                       = 0x8866,
        QUERY_RESULT_AVAILABLE_NV                                             = 0x8867,
        SAMPLE_COUNT_NV                                                       = 0x8914,
        MAX_DRAW_BUFFERS_NV                                                   = 0x8824,
        DRAW_BUFFER0_NV                                                       = 0x8825,
        DRAW_BUFFER1_NV                                                       = 0x8826,
        DRAW_BUFFER2_NV                                                       = 0x8827,
        DRAW_BUFFER3_NV                                                       = 0x8828,
        DRAW_BUFFER4_NV                                                       = 0x8829,
        DRAW_BUFFER5_NV                                                       = 0x882A,
        DRAW_BUFFER6_NV                                                       = 0x882B,
        DRAW_BUFFER7_NV                                                       = 0x882C,
        DRAW_BUFFER8_NV                                                       = 0x882D,
        DRAW_BUFFER9_NV                                                       = 0x882E,
        DRAW_BUFFER10_NV                                                      = 0x882F,
        DRAW_BUFFER11_NV                                                      = 0x8830,
        DRAW_BUFFER12_NV                                                      = 0x8831,
        DRAW_BUFFER13_NV                                                      = 0x8832,
        DRAW_BUFFER14_NV                                                      = 0x8833,
        DRAW_BUFFER15_NV                                                      = 0x8834,
        COLOR_ATTACHMENT0_NV                                                  = 0x8CE0,
        COLOR_ATTACHMENT1_NV                                                  = 0x8CE1,
        COLOR_ATTACHMENT2_NV                                                  = 0x8CE2,
        COLOR_ATTACHMENT3_NV                                                  = 0x8CE3,
        COLOR_ATTACHMENT4_NV                                                  = 0x8CE4,
        COLOR_ATTACHMENT5_NV                                                  = 0x8CE5,
        COLOR_ATTACHMENT6_NV                                                  = 0x8CE6,
        COLOR_ATTACHMENT7_NV                                                  = 0x8CE7,
        COLOR_ATTACHMENT8_NV                                                  = 0x8CE8,
        COLOR_ATTACHMENT9_NV                                                  = 0x8CE9,
        COLOR_ATTACHMENT10_NV                                                 = 0x8CEA,
        COLOR_ATTACHMENT11_NV                                                 = 0x8CEB,
        COLOR_ATTACHMENT12_NV                                                 = 0x8CEC,
        COLOR_ATTACHMENT13_NV                                                 = 0x8CED,
        COLOR_ATTACHMENT14_NV                                                 = 0x8CEE,
        COLOR_ATTACHMENT15_NV                                                 = 0x8CEF,
        EVAL_2D_NV                                                            = 0x86C0,
        EVAL_TRIANGULAR_2D_NV                                                 = 0x86C1,
        MAP_TESSELLATION_NV                                                   = 0x86C2,
        MAP_ATTRIB_U_ORDER_NV                                                 = 0x86C3,
        MAP_ATTRIB_V_ORDER_NV                                                 = 0x86C4,
        EVAL_FRACTIONAL_TESSELLATION_NV                                       = 0x86C5,
        EVAL_VERTEX_ATTRIB0_NV                                                = 0x86C6,
        EVAL_VERTEX_ATTRIB1_NV                                                = 0x86C7,
        EVAL_VERTEX_ATTRIB2_NV                                                = 0x86C8,
        EVAL_VERTEX_ATTRIB3_NV                                                = 0x86C9,
        EVAL_VERTEX_ATTRIB4_NV                                                = 0x86CA,
        EVAL_VERTEX_ATTRIB5_NV                                                = 0x86CB,
        EVAL_VERTEX_ATTRIB6_NV                                                = 0x86CC,
        EVAL_VERTEX_ATTRIB7_NV                                                = 0x86CD,
        EVAL_VERTEX_ATTRIB8_NV                                                = 0x86CE,
        EVAL_VERTEX_ATTRIB9_NV                                                = 0x86CF,
        EVAL_VERTEX_ATTRIB10_NV                                               = 0x86D0,
        EVAL_VERTEX_ATTRIB11_NV                                               = 0x86D1,
        EVAL_VERTEX_ATTRIB12_NV                                               = 0x86D2,
        EVAL_VERTEX_ATTRIB13_NV                                               = 0x86D3,
        EVAL_VERTEX_ATTRIB14_NV                                               = 0x86D4,
        EVAL_VERTEX_ATTRIB15_NV                                               = 0x86D5,
        MAX_MAP_TESSELLATION_NV                                               = 0x86D6,
        MAX_RATIONAL_EVAL_ORDER_NV                                            = 0x86D7,
        SAMPLE_POSITION_NV                                                    = 0x8E50,
        SAMPLE_MASK_NV                                                        = 0x8E51,
        SAMPLE_MASK_VALUE_NV                                                  = 0x8E52,
        TEXTURE_BINDING_RENDERBUFFER_NV                                       = 0x8E53,
        TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV                            = 0x8E54,
        TEXTURE_RENDERBUFFER_NV                                               = 0x8E55,
        SAMPLER_RENDERBUFFER_NV                                               = 0x8E56,
        INT_SAMPLER_RENDERBUFFER_NV                                           = 0x8E57,
        UNSIGNED_INT_SAMPLER_RENDERBUFFER_NV                                  = 0x8E58,
        MAX_SAMPLE_MASK_WORDS_NV                                              = 0x8E59,
        MAX_COLOR_ATTACHMENTS_NV                                              = 0x8CDF,
        ALL_COMPLETED_NV                                                      = 0x84F2,
        FENCE_STATUS_NV                                                       = 0x84F3,
        FENCE_CONDITION_NV                                                    = 0x84F4,
        FILL_RECTANGLE_NV                                                     = 0x933C,
        FLOAT_R_NV                                                            = 0x8880,
        FLOAT_RG_NV                                                           = 0x8881,
        FLOAT_RGB_NV                                                          = 0x8882,
        FLOAT_RGBA_NV                                                         = 0x8883,
        FLOAT_R16_NV                                                          = 0x8884,
        FLOAT_R32_NV                                                          = 0x8885,
        FLOAT_RG16_NV                                                         = 0x8886,
        FLOAT_RG32_NV                                                         = 0x8887,
        FLOAT_RGB16_NV                                                        = 0x8888,
        FLOAT_RGB32_NV                                                        = 0x8889,
        FLOAT_RGBA16_NV                                                       = 0x888A,
        FLOAT_RGBA32_NV                                                       = 0x888B,
        TEXTURE_FLOAT_COMPONENTS_NV                                           = 0x888C,
        FLOAT_CLEAR_COLOR_VALUE_NV                                            = 0x888D,
        FLOAT_RGBA_MODE_NV                                                    = 0x888E,
        FOG_DISTANCE_MODE_NV                                                  = 0x855A,
        EYE_RADIAL_NV                                                         = 0x855B,
        EYE_PLANE_ABSOLUTE_NV                                                 = 0x855C,
        FRAGMENT_COVERAGE_TO_COLOR_NV                                         = 0x92DD,
        FRAGMENT_COVERAGE_COLOR_NV                                            = 0x92DE,
        MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV                              = 0x8868,
        FRAGMENT_PROGRAM_NV                                                   = 0x8870,
        MAX_TEXTURE_COORDS_NV                                                 = 0x8871,
        MAX_TEXTURE_IMAGE_UNITS_NV                                            = 0x8872,
        FRAGMENT_PROGRAM_BINDING_NV                                           = 0x8873,
        PROGRAM_ERROR_STRING_NV                                               = 0x8874,
        MAX_PROGRAM_EXEC_INSTRUCTIONS_NV                                      = 0x88F4,
        MAX_PROGRAM_CALL_DEPTH_NV                                             = 0x88F5,
        MAX_PROGRAM_IF_DEPTH_NV                                               = 0x88F6,
        MAX_PROGRAM_LOOP_DEPTH_NV                                             = 0x88F7,
        MAX_PROGRAM_LOOP_COUNT_NV                                             = 0x88F8,
        DRAW_FRAMEBUFFER_BINDING_NV                                           = 0x8CA6,
        READ_FRAMEBUFFER_NV                                                   = 0x8CA8,
        DRAW_FRAMEBUFFER_NV                                                   = 0x8CA9,
        READ_FRAMEBUFFER_BINDING_NV                                           = 0x8CAA,
        RENDERBUFFER_SAMPLES_NV                                               = 0x8CAB,
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_NV                                 = 0x8D56,
        MAX_SAMPLES_NV                                                        = 0x8D57,
        RENDERBUFFER_COVERAGE_SAMPLES_NV                                      = 0x8CAB,
        RENDERBUFFER_COLOR_SAMPLES_NV                                         = 0x8E10,
        MAX_MULTISAMPLE_COVERAGE_MODES_NV                                     = 0x8E11,
        MULTISAMPLE_COVERAGE_MODES_NV                                         = 0x8E12,
        GEOMETRY_PROGRAM_NV                                                   = 0x8C26,
        MAX_PROGRAM_OUTPUT_VERTICES_NV                                        = 0x8C27,
        MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV                                = 0x8C28,
        PER_GPU_STORAGE_BIT_NV                                                = 0x800,
        MULTICAST_GPUS_NV                                                     = 0x92BA,
        PER_GPU_STORAGE_NV                                                    = 0x9548,
        MULTICAST_PROGRAMMABLE_SAMPLE_LOCATION_NV                             = 0x9549,
        RENDER_GPU_MASK_NV                                                    = 0x9558,
        MIN_PROGRAM_TEXEL_OFFSET_NV                                           = 0x8904,
        MAX_PROGRAM_TEXEL_OFFSET_NV                                           = 0x8905,
        PROGRAM_ATTRIB_COMPONENTS_NV                                          = 0x8906,
        PROGRAM_RESULT_COMPONENTS_NV                                          = 0x8907,
        MAX_PROGRAM_ATTRIB_COMPONENTS_NV                                      = 0x8908,
        MAX_PROGRAM_RESULT_COMPONENTS_NV                                      = 0x8909,
        MAX_PROGRAM_GENERIC_ATTRIBS_NV                                        = 0x8DA5,
        MAX_PROGRAM_GENERIC_RESULTS_NV                                        = 0x8DA6,
        MAX_GEOMETRY_PROGRAM_INVOCATIONS_NV                                   = 0x8E5A,
        MIN_FRAGMENT_INTERPOLATION_OFFSET_NV                                  = 0x8E5B,
        MAX_FRAGMENT_INTERPOLATION_OFFSET_NV                                  = 0x8E5C,
        FRAGMENT_PROGRAM_INTERPOLATION_OFFSET_BITS_NV                         = 0x8E5D,
        MIN_PROGRAM_TEXTURE_GATHER_OFFSET_NV                                  = 0x8E5E,
        MAX_PROGRAM_TEXTURE_GATHER_OFFSET_NV                                  = 0x8E5F,
        INT64_NV                                                              = 0x140E,
        UNSIGNED_INT64_NV                                                     = 0x140F,
        INT8_NV                                                               = 0x8FE0,
        INT8_VEC2_NV                                                          = 0x8FE1,
        INT8_VEC3_NV                                                          = 0x8FE2,
        INT8_VEC4_NV                                                          = 0x8FE3,
        INT16_NV                                                              = 0x8FE4,
        INT16_VEC2_NV                                                         = 0x8FE5,
        INT16_VEC3_NV                                                         = 0x8FE6,
        INT16_VEC4_NV                                                         = 0x8FE7,
        INT64_VEC2_NV                                                         = 0x8FE9,
        INT64_VEC3_NV                                                         = 0x8FEA,
        INT64_VEC4_NV                                                         = 0x8FEB,
        UNSIGNED_INT8_NV                                                      = 0x8FEC,
        UNSIGNED_INT8_VEC2_NV                                                 = 0x8FED,
        UNSIGNED_INT8_VEC3_NV                                                 = 0x8FEE,
        UNSIGNED_INT8_VEC4_NV                                                 = 0x8FEF,
        UNSIGNED_INT16_NV                                                     = 0x8FF0,
        UNSIGNED_INT16_VEC2_NV                                                = 0x8FF1,
        UNSIGNED_INT16_VEC3_NV                                                = 0x8FF2,
        UNSIGNED_INT16_VEC4_NV                                                = 0x8FF3,
        UNSIGNED_INT64_VEC2_NV                                                = 0x8FF5,
        UNSIGNED_INT64_VEC3_NV                                                = 0x8FF6,
        UNSIGNED_INT64_VEC4_NV                                                = 0x8FF7,
        HALF_FLOAT_NV                                                         = 0x140B,
        VERTEX_ATTRIB_ARRAY_DIVISOR_NV                                        = 0x88FE,
        MULTISAMPLES_NV                                                       = 0x9371,
        SUPERSAMPLE_SCALE_X_NV                                                = 0x9372,
        SUPERSAMPLE_SCALE_Y_NV                                                = 0x9373,
        CONFORMANT_NV                                                         = 0x9374,
        MAX_SHININESS_NV                                                      = 0x8504,
        MAX_SPOT_EXPONENT_NV                                                  = 0x8505,
        MULTISAMPLE_FILTER_HINT_NV                                            = 0x8534,
        FLOAT_MAT2x3_NV                                                       = 0x8B65,
        FLOAT_MAT2x4_NV                                                       = 0x8B66,
        FLOAT_MAT3x2_NV                                                       = 0x8B67,
        FLOAT_MAT3x4_NV                                                       = 0x8B68,
        FLOAT_MAT4x2_NV                                                       = 0x8B69,
        FLOAT_MAT4x3_NV                                                       = 0x8B6A,
        PIXEL_COUNTER_BITS_NV                                                 = 0x8864,
        CURRENT_OCCLUSION_QUERY_ID_NV                                         = 0x8865,
        PIXEL_COUNT_NV                                                        = 0x8866,
        PIXEL_COUNT_AVAILABLE_NV                                              = 0x8867,
        PACK_ROW_LENGTH_NV                                                    = 0xD02,
        PACK_SKIP_ROWS_NV                                                     = 0xD03,
        PACK_SKIP_PIXELS_NV                                                   = 0xD04,
        DEPTH_STENCIL_NV                                                      = 0x84F9,
        UNSIGNED_INT_24_8_NV                                                  = 0x84FA,
        R11F_G11F_B10F_NV                                                     = 0x8C3A,
        UNSIGNED_INT_10F_11F_11F_REV_NV                                       = 0x8C3B,
        MAX_PROGRAM_PARAMETER_BUFFER_BINDINGS_NV                              = 0x8DA0,
        MAX_PROGRAM_PARAMETER_BUFFER_SIZE_NV                                  = 0x8DA1,
        VERTEX_PROGRAM_PARAMETER_BUFFER_NV                                    = 0x8DA2,
        GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV                                  = 0x8DA3,
        FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV                                  = 0x8DA4,
        CLOSE_PATH_NV                                                         = 0x0,
        BOLD_BIT_NV                                                           = 0x1,
        GLYPH_WIDTH_BIT_NV                                                    = 0x1,
        GLYPH_HEIGHT_BIT_NV                                                   = 0x2,
        ITALIC_BIT_NV                                                         = 0x2,
        MOVE_TO_NV                                                            = 0x2,
        RELATIVE_MOVE_TO_NV                                                   = 0x3,
        GLYPH_HORIZONTAL_BEARING_X_BIT_NV                                     = 0x4,
        LINE_TO_NV                                                            = 0x4,
        RELATIVE_LINE_TO_NV                                                   = 0x5,
        HORIZONTAL_LINE_TO_NV                                                 = 0x6,
        RELATIVE_HORIZONTAL_LINE_TO_NV                                        = 0x7,
        GLYPH_HORIZONTAL_BEARING_Y_BIT_NV                                     = 0x8,
        VERTICAL_LINE_TO_NV                                                   = 0x8,
        RELATIVE_VERTICAL_LINE_TO_NV                                          = 0x9,
        QUADRATIC_CURVE_TO_NV                                                 = 0xA,
        RELATIVE_QUADRATIC_CURVE_TO_NV                                        = 0xB,
        CUBIC_CURVE_TO_NV                                                     = 0xC,
        RELATIVE_CUBIC_CURVE_TO_NV                                            = 0xD,
        SMOOTH_QUADRATIC_CURVE_TO_NV                                          = 0xE,
        RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV                                 = 0xF,
        GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV                               = 0x10,
        SMOOTH_CUBIC_CURVE_TO_NV                                              = 0x10,
        RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV                                     = 0x11,
        SMALL_CCW_ARC_TO_NV                                                   = 0x12,
        RELATIVE_SMALL_CCW_ARC_TO_NV                                          = 0x13,
        SMALL_CW_ARC_TO_NV                                                    = 0x14,
        RELATIVE_SMALL_CW_ARC_TO_NV                                           = 0x15,
        LARGE_CCW_ARC_TO_NV                                                   = 0x16,
        RELATIVE_LARGE_CCW_ARC_TO_NV                                          = 0x17,
        LARGE_CW_ARC_TO_NV                                                    = 0x18,
        RELATIVE_LARGE_CW_ARC_TO_NV                                           = 0x19,
        CONIC_CURVE_TO_NV                                                     = 0x1A,
        RELATIVE_CONIC_CURVE_TO_NV                                            = 0x1B,
        GLYPH_VERTICAL_BEARING_X_BIT_NV                                       = 0x20,
        GLYPH_VERTICAL_BEARING_Y_BIT_NV                                       = 0x40,
        GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV                                 = 0x80,
        ROUNDED_RECT_NV                                                       = 0xE8,
        RELATIVE_ROUNDED_RECT_NV                                              = 0xE9,
        ROUNDED_RECT2_NV                                                      = 0xEA,
        RELATIVE_ROUNDED_RECT2_NV                                             = 0xEB,
        ROUNDED_RECT4_NV                                                      = 0xEC,
        RELATIVE_ROUNDED_RECT4_NV                                             = 0xED,
        ROUNDED_RECT8_NV                                                      = 0xEE,
        RELATIVE_ROUNDED_RECT8_NV                                             = 0xEF,
        RESTART_PATH_NV                                                       = 0xF0,
        DUP_FIRST_CUBIC_CURVE_TO_NV                                           = 0xF2,
        DUP_LAST_CUBIC_CURVE_TO_NV                                            = 0xF4,
        RECT_NV                                                               = 0xF6,
        RELATIVE_RECT_NV                                                      = 0xF7,
        CIRCULAR_CCW_ARC_TO_NV                                                = 0xF8,
        CIRCULAR_CW_ARC_TO_NV                                                 = 0xFA,
        CIRCULAR_TANGENT_ARC_TO_NV                                            = 0xFC,
        ARC_TO_NV                                                             = 0xFE,
        RELATIVE_ARC_TO_NV                                                    = 0xFF,
        GLYPH_HAS_KERNING_BIT_NV                                              = 0x100,
        PRIMARY_COLOR_NV                                                      = 0x852C,
        SECONDARY_COLOR_NV                                                    = 0x852D,
        PATH_FORMAT_SVG_NV                                                    = 0x9070,
        PATH_FORMAT_PS_NV                                                     = 0x9071,
        STANDARD_FONT_NAME_NV                                                 = 0x9072,
        SYSTEM_FONT_NAME_NV                                                   = 0x9073,
        FILE_NAME_NV                                                          = 0x9074,
        PATH_STROKE_WIDTH_NV                                                  = 0x9075,
        PATH_END_CAPS_NV                                                      = 0x9076,
        PATH_INITIAL_END_CAP_NV                                               = 0x9077,
        PATH_TERMINAL_END_CAP_NV                                              = 0x9078,
        PATH_JOIN_STYLE_NV                                                    = 0x9079,
        PATH_MITER_LIMIT_NV                                                   = 0x907A,
        PATH_DASH_CAPS_NV                                                     = 0x907B,
        PATH_INITIAL_DASH_CAP_NV                                              = 0x907C,
        PATH_TERMINAL_DASH_CAP_NV                                             = 0x907D,
        PATH_DASH_OFFSET_NV                                                   = 0x907E,
        PATH_CLIENT_LENGTH_NV                                                 = 0x907F,
        PATH_FILL_MODE_NV                                                     = 0x9080,
        PATH_FILL_MASK_NV                                                     = 0x9081,
        PATH_FILL_COVER_MODE_NV                                               = 0x9082,
        PATH_STROKE_COVER_MODE_NV                                             = 0x9083,
        PATH_STROKE_MASK_NV                                                   = 0x9084,
        PATH_STROKE_BOUND_NV                                                  = 0x9086,
        COUNT_UP_NV                                                           = 0x9088,
        COUNT_DOWN_NV                                                         = 0x9089,
        PATH_OBJECT_BOUNDING_BOX_NV                                           = 0x908A,
        CONVEX_HULL_NV                                                        = 0x908B,
        BOUNDING_BOX_NV                                                       = 0x908D,
        TRANSLATE_X_NV                                                        = 0x908E,
        TRANSLATE_Y_NV                                                        = 0x908F,
        TRANSLATE_2D_NV                                                       = 0x9090,
        TRANSLATE_3D_NV                                                       = 0x9091,
        AFFINE_2D_NV                                                          = 0x9092,
        AFFINE_3D_NV                                                          = 0x9094,
        TRANSPOSE_AFFINE_2D_NV                                                = 0x9096,
        TRANSPOSE_AFFINE_3D_NV                                                = 0x9098,
        UTF8_NV                                                               = 0x909A,
        UTF16_NV                                                              = 0x909B,
        BOUNDING_BOX_OF_BOUNDING_BOXES_NV                                     = 0x909C,
        PATH_COMMAND_COUNT_NV                                                 = 0x909D,
        PATH_COORD_COUNT_NV                                                   = 0x909E,
        PATH_DASH_ARRAY_COUNT_NV                                              = 0x909F,
        PATH_COMPUTED_LENGTH_NV                                               = 0x90A0,
        PATH_FILL_BOUNDING_BOX_NV                                             = 0x90A1,
        PATH_STROKE_BOUNDING_BOX_NV                                           = 0x90A2,
        SQUARE_NV                                                             = 0x90A3,
        ROUND_NV                                                              = 0x90A4,
        TRIANGULAR_NV                                                         = 0x90A5,
        BEVEL_NV                                                              = 0x90A6,
        MITER_REVERT_NV                                                       = 0x90A7,
        MITER_TRUNCATE_NV                                                     = 0x90A8,
        SKIP_MISSING_GLYPH_NV                                                 = 0x90A9,
        USE_MISSING_GLYPH_NV                                                  = 0x90AA,
        PATH_ERROR_POSITION_NV                                                = 0x90AB,
        PATH_FOG_GEN_MODE_NV                                                  = 0x90AC,
        ACCUM_ADJACENT_PAIRS_NV                                               = 0x90AD,
        ADJACENT_PAIRS_NV                                                     = 0x90AE,
        FIRST_TO_REST_NV                                                      = 0x90AF,
        PATH_GEN_MODE_NV                                                      = 0x90B0,
        PATH_GEN_COEFF_NV                                                     = 0x90B1,
        PATH_GEN_COLOR_FORMAT_NV                                              = 0x90B2,
        PATH_GEN_COMPONENTS_NV                                                = 0x90B3,
        PATH_DASH_OFFSET_RESET_NV                                             = 0x90B4,
        MOVE_TO_RESETS_NV                                                     = 0x90B5,
        MOVE_TO_CONTINUES_NV                                                  = 0x90B6,
        PATH_STENCIL_FUNC_NV                                                  = 0x90B7,
        PATH_STENCIL_REF_NV                                                   = 0x90B8,
        PATH_STENCIL_VALUE_MASK_NV                                            = 0x90B9,
        PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV                                   = 0x90BD,
        PATH_STENCIL_DEPTH_OFFSET_UNITS_NV                                    = 0x90BE,
        PATH_COVER_DEPTH_FUNC_NV                                              = 0x90BF,
        FONT_GLYPHS_AVAILABLE_NV                                              = 0x9368,
        FONT_TARGET_UNAVAILABLE_NV                                            = 0x9369,
        FONT_UNAVAILABLE_NV                                                   = 0x936A,
        FONT_UNINTELLIGIBLE_NV                                                = 0x936B,
        STANDARD_FONT_FORMAT_NV                                               = 0x936C,
        FRAGMENT_INPUT_NV                                                     = 0x936D,
        FONT_X_MIN_BOUNDS_BIT_NV                                              = 0x10000,
        FONT_Y_MIN_BOUNDS_BIT_NV                                              = 0x20000,
        FONT_X_MAX_BOUNDS_BIT_NV                                              = 0x40000,
        FONT_Y_MAX_BOUNDS_BIT_NV                                              = 0x80000,
        FONT_UNITS_PER_EM_BIT_NV                                              = 0x100000,
        FONT_ASCENDER_BIT_NV                                                  = 0x200000,
        FONT_DESCENDER_BIT_NV                                                 = 0x400000,
        FONT_HEIGHT_BIT_NV                                                    = 0x800000,
        FONT_MAX_ADVANCE_WIDTH_BIT_NV                                         = 0x1000000,
        FONT_MAX_ADVANCE_HEIGHT_BIT_NV                                        = 0x2000000,
        FONT_UNDERLINE_POSITION_BIT_NV                                        = 0x4000000,
        FONT_UNDERLINE_THICKNESS_BIT_NV                                       = 0x8000000,
        FONT_HAS_KERNING_BIT_NV                                               = 0x10000000,
        FONT_NUM_GLYPH_INDICES_BIT_NV                                         = 0x20000000,
        SHARED_EDGE_NV                                                        = 0xC0,
        PIXEL_PACK_BUFFER_NV                                                  = 0x88EB,
        PIXEL_UNPACK_BUFFER_NV                                                = 0x88EC,
        PIXEL_PACK_BUFFER_BINDING_NV                                          = 0x88ED,
        PIXEL_UNPACK_BUFFER_BINDING_NV                                        = 0x88EF,
        WRITE_PIXEL_DATA_RANGE_NV                                             = 0x8878,
        READ_PIXEL_DATA_RANGE_NV                                              = 0x8879,
        WRITE_PIXEL_DATA_RANGE_LENGTH_NV                                      = 0x887A,
        READ_PIXEL_DATA_RANGE_LENGTH_NV                                       = 0x887B,
        WRITE_PIXEL_DATA_RANGE_POINTER_NV                                     = 0x887C,
        READ_PIXEL_DATA_RANGE_POINTER_NV                                      = 0x887D,
        NVIDIA_PLATFORM_BINARY_NV                                             = 0x890B,
        POINT_SPRITE_NV                                                       = 0x8861,
        COORD_REPLACE_NV                                                      = 0x8862,
        POINT_SPRITE_R_MODE_NV                                                = 0x8863,
        POLYGON_MODE_NV                                                       = 0xB40,
        POINT_NV                                                              = 0x1B00,
        LINE_NV                                                               = 0x1B01,
        FILL_NV                                                               = 0x1B02,
        POLYGON_OFFSET_POINT_NV                                               = 0x2A01,
        POLYGON_OFFSET_LINE_NV                                                = 0x2A02,
        FRAME_NV                                                              = 0x8E26,
        FIELDS_NV                                                             = 0x8E27,
        CURRENT_TIME_NV                                                       = 0x8E28,
        NUM_FILL_STREAMS_NV                                                   = 0x8E29,
        PRESENT_TIME_NV                                                       = 0x8E2A,
        PRESENT_DURATION_NV                                                   = 0x8E2B,
        PRIMITIVE_RESTART_NV                                                  = 0x8558,
        PRIMITIVE_RESTART_INDEX_NV                                            = 0x8559,
        REGISTER_COMBINERS_NV                                                 = 0x8522,
        VARIABLE_A_NV                                                         = 0x8523,
        VARIABLE_B_NV                                                         = 0x8524,
        VARIABLE_C_NV                                                         = 0x8525,
        VARIABLE_D_NV                                                         = 0x8526,
        VARIABLE_E_NV                                                         = 0x8527,
        VARIABLE_F_NV                                                         = 0x8528,
        VARIABLE_G_NV                                                         = 0x8529,
        CONSTANT_COLOR0_NV                                                    = 0x852A,
        CONSTANT_COLOR1_NV                                                    = 0x852B,
        SPARE0_NV                                                             = 0x852E,
        SPARE1_NV                                                             = 0x852F,
        DISCARD_NV                                                            = 0x8530,
        E_TIMES_F_NV                                                          = 0x8531,
        SPARE0_PLUS_SECONDARY_COLOR_NV                                        = 0x8532,
        UNSIGNED_IDENTITY_NV                                                  = 0x8536,
        UNSIGNED_INVERT_NV                                                    = 0x8537,
        EXPAND_NORMAL_NV                                                      = 0x8538,
        EXPAND_NEGATE_NV                                                      = 0x8539,
        HALF_BIAS_NORMAL_NV                                                   = 0x853A,
        HALF_BIAS_NEGATE_NV                                                   = 0x853B,
        SIGNED_IDENTITY_NV                                                    = 0x853C,
        SIGNED_NEGATE_NV                                                      = 0x853D,
        SCALE_BY_TWO_NV                                                       = 0x853E,
        SCALE_BY_FOUR_NV                                                      = 0x853F,
        SCALE_BY_ONE_HALF_NV                                                  = 0x8540,
        BIAS_BY_NEGATIVE_ONE_HALF_NV                                          = 0x8541,
        COMBINER_INPUT_NV                                                     = 0x8542,
        COMBINER_MAPPING_NV                                                   = 0x8543,
        COMBINER_COMPONENT_USAGE_NV                                           = 0x8544,
        COMBINER_AB_DOT_PRODUCT_NV                                            = 0x8545,
        COMBINER_CD_DOT_PRODUCT_NV                                            = 0x8546,
        COMBINER_MUX_SUM_NV                                                   = 0x8547,
        COMBINER_SCALE_NV                                                     = 0x8548,
        COMBINER_BIAS_NV                                                      = 0x8549,
        COMBINER_AB_OUTPUT_NV                                                 = 0x854A,
        COMBINER_CD_OUTPUT_NV                                                 = 0x854B,
        COMBINER_SUM_OUTPUT_NV                                                = 0x854C,
        MAX_GENERAL_COMBINERS_NV                                              = 0x854D,
        NUM_GENERAL_COMBINERS_NV                                              = 0x854E,
        COLOR_SUM_CLAMP_NV                                                    = 0x854F,
        COMBINER0_NV                                                          = 0x8550,
        COMBINER1_NV                                                          = 0x8551,
        COMBINER2_NV                                                          = 0x8552,
        COMBINER3_NV                                                          = 0x8553,
        COMBINER4_NV                                                          = 0x8554,
        COMBINER5_NV                                                          = 0x8555,
        COMBINER6_NV                                                          = 0x8556,
        COMBINER7_NV                                                          = 0x8557,
        PER_STAGE_CONSTANTS_NV                                                = 0x8535,
        ETC1_SRGB8_NV                                                         = 0x88EE,
        SRGB8_NV                                                              = 0x8C41,
        SLUMINANCE_ALPHA_NV                                                   = 0x8C44,
        SLUMINANCE8_ALPHA8_NV                                                 = 0x8C45,
        SLUMINANCE_NV                                                         = 0x8C46,
        SLUMINANCE8_NV                                                        = 0x8C47,
        COMPRESSED_SRGB_S3TC_DXT1_NV                                          = 0x8C4C,
        COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV                                    = 0x8C4D,
        COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV                                    = 0x8C4E,
        COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV                                    = 0x8C4F,
        SAMPLE_LOCATION_NV                                                    = 0x8E50,
        SAMPLE_LOCATION_SUBPIXEL_BITS_NV                                      = 0x933D,
        SAMPLE_LOCATION_PIXEL_GRID_WIDTH_NV                                   = 0x933E,
        SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_NV                                  = 0x933F,
        PROGRAMMABLE_SAMPLE_LOCATION_TABLE_SIZE_NV                            = 0x9340,
        PROGRAMMABLE_SAMPLE_LOCATION_NV                                       = 0x9341,
        FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV                          = 0x9342,
        FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV                             = 0x9343,
        BUFFER_GPU_ADDRESS_NV                                                 = 0x8F1D,
        GPU_ADDRESS_NV                                                        = 0x8F34,
        MAX_SHADER_BUFFER_ADDRESS_NV                                          = 0x8F35,
        WARP_SIZE_NV                                                          = 0x9339,
        WARPS_PER_SM_NV                                                       = 0x933A,
        SM_COUNT_NV                                                           = 0x933B,
        SAMPLER_2D_ARRAY_SHADOW_NV                                            = 0x8DC4,
        SAMPLER_CUBE_SHADOW_NV                                                = 0x8DC5,
        MAX_PROGRAM_PATCH_ATTRIBS_NV                                          = 0x86D8,
        TESS_CONTROL_PROGRAM_NV                                               = 0x891E,
        TESS_EVALUATION_PROGRAM_NV                                            = 0x891F,
        TESS_CONTROL_PROGRAM_PARAMETER_BUFFER_NV                              = 0x8C74,
        TESS_EVALUATION_PROGRAM_PARAMETER_BUFFER_NV                           = 0x8C75,
        EMBOSS_LIGHT_NV                                                       = 0x855D,
        EMBOSS_CONSTANT_NV                                                    = 0x855E,
        EMBOSS_MAP_NV                                                         = 0x855F,
        NORMAL_MAP_NV                                                         = 0x8511,
        REFLECTION_MAP_NV                                                     = 0x8512,
        UNPACK_SKIP_IMAGES_NV                                                 = 0x806D,
        UNPACK_IMAGE_HEIGHT_NV                                                = 0x806E,
        MAX_ARRAY_TEXTURE_LAYERS_NV                                           = 0x88FF,
        TEXTURE_2D_ARRAY_NV                                                   = 0x8C1A,
        TEXTURE_BINDING_2D_ARRAY_NV                                           = 0x8C1D,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_NV                               = 0x8CD4,
        SAMPLER_2D_ARRAY_NV                                                   = 0x8DC1,
        TEXTURE_BORDER_COLOR_NV                                               = 0x1004,
        CLAMP_TO_BORDER_NV                                                    = 0x812D,
        COMPRESSED_LUMINANCE_LATC1_NV                                         = 0x8C70,
        COMPRESSED_SIGNED_LUMINANCE_LATC1_NV                                  = 0x8C71,
        COMPRESSED_LUMINANCE_ALPHA_LATC2_NV                                   = 0x8C72,
        COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_NV                            = 0x8C73,
        COMPRESSED_RGB_S3TC_DXT1_NV                                           = 0x83F0,
        COMPRESSED_RGBA_S3TC_DXT1_NV                                          = 0x83F1,
        COMPRESSED_RGBA_S3TC_DXT3_NV                                          = 0x83F2,
        COMPRESSED_RGBA_S3TC_DXT5_NV                                          = 0x83F3,
        COMBINE4_NV                                                           = 0x8503,
        SOURCE3_RGB_NV                                                        = 0x8583,
        SOURCE3_ALPHA_NV                                                      = 0x858B,
        OPERAND3_RGB_NV                                                       = 0x8593,
        OPERAND3_ALPHA_NV                                                     = 0x859B,
        TEXTURE_UNSIGNED_REMAP_MODE_NV                                        = 0x888F,
        TEXTURE_COVERAGE_SAMPLES_NV                                           = 0x9045,
        TEXTURE_COLOR_SAMPLES_NV                                              = 0x9046,
        TEXTURE_RECTANGLE_NV                                                  = 0x84F5,
        TEXTURE_BINDING_RECTANGLE_NV                                          = 0x84F6,
        PROXY_TEXTURE_RECTANGLE_NV                                            = 0x84F7,
        MAX_RECTANGLE_TEXTURE_SIZE_NV                                         = 0x84F8,
        OFFSET_TEXTURE_RECTANGLE_NV                                           = 0x864C,
        OFFSET_TEXTURE_RECTANGLE_SCALE_NV                                     = 0x864D,
        DOT_PRODUCT_TEXTURE_RECTANGLE_NV                                      = 0x864E,
        RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV                                  = 0x86D9,
        UNSIGNED_INT_S8_S8_8_8_NV                                             = 0x86DA,
        UNSIGNED_INT_8_8_S8_S8_REV_NV                                         = 0x86DB,
        DSDT_MAG_INTENSITY_NV                                                 = 0x86DC,
        SHADER_CONSISTENT_NV                                                  = 0x86DD,
        TEXTURE_SHADER_NV                                                     = 0x86DE,
        SHADER_OPERATION_NV                                                   = 0x86DF,
        CULL_MODES_NV                                                         = 0x86E0,
        OFFSET_TEXTURE_2D_MATRIX_NV                                           = 0x86E1,
        OFFSET_TEXTURE_MATRIX_NV                                              = 0x86E1,
        OFFSET_TEXTURE_2D_SCALE_NV                                            = 0x86E2,
        OFFSET_TEXTURE_SCALE_NV                                               = 0x86E2,
        OFFSET_TEXTURE_2D_BIAS_NV                                             = 0x86E3,
        OFFSET_TEXTURE_BIAS_NV                                                = 0x86E3,
        PREVIOUS_TEXTURE_INPUT_NV                                             = 0x86E4,
        CONST_EYE_NV                                                          = 0x86E5,
        PASS_THROUGH_NV                                                       = 0x86E6,
        CULL_FRAGMENT_NV                                                      = 0x86E7,
        OFFSET_TEXTURE_2D_NV                                                  = 0x86E8,
        DEPENDENT_AR_TEXTURE_2D_NV                                            = 0x86E9,
        DEPENDENT_GB_TEXTURE_2D_NV                                            = 0x86EA,
        DOT_PRODUCT_NV                                                        = 0x86EC,
        DOT_PRODUCT_DEPTH_REPLACE_NV                                          = 0x86ED,
        DOT_PRODUCT_TEXTURE_2D_NV                                             = 0x86EE,
        DOT_PRODUCT_TEXTURE_CUBE_MAP_NV                                       = 0x86F0,
        DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV                                       = 0x86F1,
        DOT_PRODUCT_REFLECT_CUBE_MAP_NV                                       = 0x86F2,
        DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV                             = 0x86F3,
        HILO_NV                                                               = 0x86F4,
        DSDT_NV                                                               = 0x86F5,
        DSDT_MAG_NV                                                           = 0x86F6,
        DSDT_MAG_VIB_NV                                                       = 0x86F7,
        HILO16_NV                                                             = 0x86F8,
        SIGNED_HILO_NV                                                        = 0x86F9,
        SIGNED_HILO16_NV                                                      = 0x86FA,
        SIGNED_RGBA_NV                                                        = 0x86FB,
        SIGNED_RGBA8_NV                                                       = 0x86FC,
        SIGNED_RGB_NV                                                         = 0x86FE,
        SIGNED_RGB8_NV                                                        = 0x86FF,
        SIGNED_LUMINANCE_NV                                                   = 0x8701,
        SIGNED_LUMINANCE8_NV                                                  = 0x8702,
        SIGNED_LUMINANCE_ALPHA_NV                                             = 0x8703,
        SIGNED_LUMINANCE8_ALPHA8_NV                                           = 0x8704,
        SIGNED_ALPHA_NV                                                       = 0x8705,
        SIGNED_ALPHA8_NV                                                      = 0x8706,
        SIGNED_INTENSITY_NV                                                   = 0x8707,
        SIGNED_INTENSITY8_NV                                                  = 0x8708,
        DSDT8_NV                                                              = 0x8709,
        DSDT8_MAG8_NV                                                         = 0x870A,
        DSDT8_MAG8_INTENSITY8_NV                                              = 0x870B,
        SIGNED_RGB_UNSIGNED_ALPHA_NV                                          = 0x870C,
        SIGNED_RGB8_UNSIGNED_ALPHA8_NV                                        = 0x870D,
        HI_SCALE_NV                                                           = 0x870E,
        LO_SCALE_NV                                                           = 0x870F,
        DS_SCALE_NV                                                           = 0x8710,
        DT_SCALE_NV                                                           = 0x8711,
        MAGNITUDE_SCALE_NV                                                    = 0x8712,
        VIBRANCE_SCALE_NV                                                     = 0x8713,
        HI_BIAS_NV                                                            = 0x8714,
        LO_BIAS_NV                                                            = 0x8715,
        DS_BIAS_NV                                                            = 0x8716,
        DT_BIAS_NV                                                            = 0x8717,
        MAGNITUDE_BIAS_NV                                                     = 0x8718,
        VIBRANCE_BIAS_NV                                                      = 0x8719,
        TEXTURE_BORDER_VALUES_NV                                              = 0x871A,
        TEXTURE_HI_SIZE_NV                                                    = 0x871B,
        TEXTURE_LO_SIZE_NV                                                    = 0x871C,
        TEXTURE_DS_SIZE_NV                                                    = 0x871D,
        TEXTURE_DT_SIZE_NV                                                    = 0x871E,
        TEXTURE_MAG_SIZE_NV                                                   = 0x871F,
        DOT_PRODUCT_TEXTURE_3D_NV                                             = 0x86EF,
        OFFSET_PROJECTIVE_TEXTURE_2D_NV                                       = 0x8850,
        OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV                                 = 0x8851,
        OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV                                = 0x8852,
        OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV                          = 0x8853,
        OFFSET_HILO_TEXTURE_2D_NV                                             = 0x8854,
        OFFSET_HILO_TEXTURE_RECTANGLE_NV                                      = 0x8855,
        OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV                                  = 0x8856,
        OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV                           = 0x8857,
        DEPENDENT_HILO_TEXTURE_2D_NV                                          = 0x8858,
        DEPENDENT_RGB_TEXTURE_3D_NV                                           = 0x8859,
        DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV                                     = 0x885A,
        DOT_PRODUCT_PASS_THROUGH_NV                                           = 0x885B,
        DOT_PRODUCT_TEXTURE_1D_NV                                             = 0x885C,
        DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV                                   = 0x885D,
        HILO8_NV                                                              = 0x885E,
        SIGNED_HILO8_NV                                                       = 0x885F,
        FORCE_BLUE_TO_ONE_NV                                                  = 0x8860,
        BACK_PRIMARY_COLOR_NV                                                 = 0x8C77,
        BACK_SECONDARY_COLOR_NV                                               = 0x8C78,
        TEXTURE_COORD_NV                                                      = 0x8C79,
        CLIP_DISTANCE_NV                                                      = 0x8C7A,
        VERTEX_ID_NV                                                          = 0x8C7B,
        PRIMITIVE_ID_NV                                                       = 0x8C7C,
        GENERIC_ATTRIB_NV                                                     = 0x8C7D,
        TRANSFORM_FEEDBACK_ATTRIBS_NV                                         = 0x8C7E,
        TRANSFORM_FEEDBACK_BUFFER_MODE_NV                                     = 0x8C7F,
        MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_NV                         = 0x8C80,
        ACTIVE_VARYINGS_NV                                                    = 0x8C81,
        ACTIVE_VARYING_MAX_LENGTH_NV                                          = 0x8C82,
        TRANSFORM_FEEDBACK_VARYINGS_NV                                        = 0x8C83,
        TRANSFORM_FEEDBACK_BUFFER_START_NV                                    = 0x8C84,
        TRANSFORM_FEEDBACK_BUFFER_SIZE_NV                                     = 0x8C85,
        TRANSFORM_FEEDBACK_RECORD_NV                                          = 0x8C86,
        PRIMITIVES_GENERATED_NV                                               = 0x8C87,
        TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV                              = 0x8C88,
        RASTERIZER_DISCARD_NV                                                 = 0x8C89,
        MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_NV                      = 0x8C8A,
        MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_NV                            = 0x8C8B,
        INTERLEAVED_ATTRIBS_NV                                                = 0x8C8C,
        SEPARATE_ATTRIBS_NV                                                   = 0x8C8D,
        TRANSFORM_FEEDBACK_BUFFER_NV                                          = 0x8C8E,
        TRANSFORM_FEEDBACK_BUFFER_BINDING_NV                                  = 0x8C8F,
        TRANSFORM_FEEDBACK_NV                                                 = 0x8E22,
        TRANSFORM_FEEDBACK_BUFFER_PAUSED_NV                                   = 0x8E23,
        TRANSFORM_FEEDBACK_BUFFER_ACTIVE_NV                                   = 0x8E24,
        TRANSFORM_FEEDBACK_BINDING_NV                                         = 0x8E25,
        UNIFORM_BUFFER_UNIFIED_NV                                             = 0x936E,
        UNIFORM_BUFFER_ADDRESS_NV                                             = 0x936F,
        UNIFORM_BUFFER_LENGTH_NV                                              = 0x9370,
        SURFACE_STATE_NV                                                      = 0x86EB,
        SURFACE_REGISTERED_NV                                                 = 0x86FD,
        SURFACE_MAPPED_NV                                                     = 0x8700,
        WRITE_DISCARD_NV                                                      = 0x88BE,
        VERTEX_ARRAY_RANGE_NV                                                 = 0x851D,
        VERTEX_ARRAY_RANGE_LENGTH_NV                                          = 0x851E,
        VERTEX_ARRAY_RANGE_VALID_NV                                           = 0x851F,
        MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV                                     = 0x8520,
        VERTEX_ARRAY_RANGE_POINTER_NV                                         = 0x8521,
        VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV                                   = 0x8533,
        VERTEX_ATTRIB_ARRAY_UNIFIED_NV                                        = 0x8F1E,
        ELEMENT_ARRAY_UNIFIED_NV                                              = 0x8F1F,
        VERTEX_ATTRIB_ARRAY_ADDRESS_NV                                        = 0x8F20,
        VERTEX_ARRAY_ADDRESS_NV                                               = 0x8F21,
        NORMAL_ARRAY_ADDRESS_NV                                               = 0x8F22,
        COLOR_ARRAY_ADDRESS_NV                                                = 0x8F23,
        INDEX_ARRAY_ADDRESS_NV                                                = 0x8F24,
        TEXTURE_COORD_ARRAY_ADDRESS_NV                                        = 0x8F25,
        EDGE_FLAG_ARRAY_ADDRESS_NV                                            = 0x8F26,
        SECONDARY_COLOR_ARRAY_ADDRESS_NV                                      = 0x8F27,
        FOG_COORD_ARRAY_ADDRESS_NV                                            = 0x8F28,
        ELEMENT_ARRAY_ADDRESS_NV                                              = 0x8F29,
        VERTEX_ATTRIB_ARRAY_LENGTH_NV                                         = 0x8F2A,
        VERTEX_ARRAY_LENGTH_NV                                                = 0x8F2B,
        NORMAL_ARRAY_LENGTH_NV                                                = 0x8F2C,
        COLOR_ARRAY_LENGTH_NV                                                 = 0x8F2D,
        INDEX_ARRAY_LENGTH_NV                                                 = 0x8F2E,
        TEXTURE_COORD_ARRAY_LENGTH_NV                                         = 0x8F2F,
        EDGE_FLAG_ARRAY_LENGTH_NV                                             = 0x8F30,
        SECONDARY_COLOR_ARRAY_LENGTH_NV                                       = 0x8F31,
        FOG_COORD_ARRAY_LENGTH_NV                                             = 0x8F32,
        ELEMENT_ARRAY_LENGTH_NV                                               = 0x8F33,
        DRAW_INDIRECT_UNIFIED_NV                                              = 0x8F40,
        DRAW_INDIRECT_ADDRESS_NV                                              = 0x8F41,
        DRAW_INDIRECT_LENGTH_NV                                               = 0x8F42,
        VERTEX_PROGRAM_NV                                                     = 0x8620,
        VERTEX_STATE_PROGRAM_NV                                               = 0x8621,
        ATTRIB_ARRAY_SIZE_NV                                                  = 0x8623,
        ATTRIB_ARRAY_STRIDE_NV                                                = 0x8624,
        ATTRIB_ARRAY_TYPE_NV                                                  = 0x8625,
        CURRENT_ATTRIB_NV                                                     = 0x8626,
        PROGRAM_LENGTH_NV                                                     = 0x8627,
        PROGRAM_STRING_NV                                                     = 0x8628,
        MODELVIEW_PROJECTION_NV                                               = 0x8629,
        IDENTITY_NV                                                           = 0x862A,
        INVERSE_NV                                                            = 0x862B,
        TRANSPOSE_NV                                                          = 0x862C,
        INVERSE_TRANSPOSE_NV                                                  = 0x862D,
        MAX_TRACK_MATRIX_STACK_DEPTH_NV                                       = 0x862E,
        MAX_TRACK_MATRICES_NV                                                 = 0x862F,
        MATRIX0_NV                                                            = 0x8630,
        MATRIX1_NV                                                            = 0x8631,
        MATRIX2_NV                                                            = 0x8632,
        MATRIX3_NV                                                            = 0x8633,
        MATRIX4_NV                                                            = 0x8634,
        MATRIX5_NV                                                            = 0x8635,
        MATRIX6_NV                                                            = 0x8636,
        MATRIX7_NV                                                            = 0x8637,
        CURRENT_MATRIX_STACK_DEPTH_NV                                         = 0x8640,
        CURRENT_MATRIX_NV                                                     = 0x8641,
        VERTEX_PROGRAM_POINT_SIZE_NV                                          = 0x8642,
        VERTEX_PROGRAM_TWO_SIDE_NV                                            = 0x8643,
        PROGRAM_PARAMETER_NV                                                  = 0x8644,
        ATTRIB_ARRAY_POINTER_NV                                               = 0x8645,
        PROGRAM_TARGET_NV                                                     = 0x8646,
        PROGRAM_RESIDENT_NV                                                   = 0x8647,
        TRACK_MATRIX_NV                                                       = 0x8648,
        TRACK_MATRIX_TRANSFORM_NV                                             = 0x8649,
        VERTEX_PROGRAM_BINDING_NV                                             = 0x864A,
        PROGRAM_ERROR_POSITION_NV                                             = 0x864B,
        VERTEX_ATTRIB_ARRAY0_NV                                               = 0x8650,
        VERTEX_ATTRIB_ARRAY1_NV                                               = 0x8651,
        VERTEX_ATTRIB_ARRAY2_NV                                               = 0x8652,
        VERTEX_ATTRIB_ARRAY3_NV                                               = 0x8653,
        VERTEX_ATTRIB_ARRAY4_NV                                               = 0x8654,
        VERTEX_ATTRIB_ARRAY5_NV                                               = 0x8655,
        VERTEX_ATTRIB_ARRAY6_NV                                               = 0x8656,
        VERTEX_ATTRIB_ARRAY7_NV                                               = 0x8657,
        VERTEX_ATTRIB_ARRAY8_NV                                               = 0x8658,
        VERTEX_ATTRIB_ARRAY9_NV                                               = 0x8659,
        VERTEX_ATTRIB_ARRAY10_NV                                              = 0x865A,
        VERTEX_ATTRIB_ARRAY11_NV                                              = 0x865B,
        VERTEX_ATTRIB_ARRAY12_NV                                              = 0x865C,
        VERTEX_ATTRIB_ARRAY13_NV                                              = 0x865D,
        VERTEX_ATTRIB_ARRAY14_NV                                              = 0x865E,
        VERTEX_ATTRIB_ARRAY15_NV                                              = 0x865F,
        MAP1_VERTEX_ATTRIB0_4_NV                                              = 0x8660,
        MAP1_VERTEX_ATTRIB1_4_NV                                              = 0x8661,
        MAP1_VERTEX_ATTRIB2_4_NV                                              = 0x8662,
        MAP1_VERTEX_ATTRIB3_4_NV                                              = 0x8663,
        MAP1_VERTEX_ATTRIB4_4_NV                                              = 0x8664,
        MAP1_VERTEX_ATTRIB5_4_NV                                              = 0x8665,
        MAP1_VERTEX_ATTRIB6_4_NV                                              = 0x8666,
        MAP1_VERTEX_ATTRIB7_4_NV                                              = 0x8667,
        MAP1_VERTEX_ATTRIB8_4_NV                                              = 0x8668,
        MAP1_VERTEX_ATTRIB9_4_NV                                              = 0x8669,
        MAP1_VERTEX_ATTRIB10_4_NV                                             = 0x866A,
        MAP1_VERTEX_ATTRIB11_4_NV                                             = 0x866B,
        MAP1_VERTEX_ATTRIB12_4_NV                                             = 0x866C,
        MAP1_VERTEX_ATTRIB13_4_NV                                             = 0x866D,
        MAP1_VERTEX_ATTRIB14_4_NV                                             = 0x866E,
        MAP1_VERTEX_ATTRIB15_4_NV                                             = 0x866F,
        MAP2_VERTEX_ATTRIB0_4_NV                                              = 0x8670,
        MAP2_VERTEX_ATTRIB1_4_NV                                              = 0x8671,
        MAP2_VERTEX_ATTRIB2_4_NV                                              = 0x8672,
        MAP2_VERTEX_ATTRIB3_4_NV                                              = 0x8673,
        MAP2_VERTEX_ATTRIB4_4_NV                                              = 0x8674,
        MAP2_VERTEX_ATTRIB5_4_NV                                              = 0x8675,
        MAP2_VERTEX_ATTRIB6_4_NV                                              = 0x8676,
        MAP2_VERTEX_ATTRIB7_4_NV                                              = 0x8677,
        MAP2_VERTEX_ATTRIB8_4_NV                                              = 0x8678,
        MAP2_VERTEX_ATTRIB9_4_NV                                              = 0x8679,
        MAP2_VERTEX_ATTRIB10_4_NV                                             = 0x867A,
        MAP2_VERTEX_ATTRIB11_4_NV                                             = 0x867B,
        MAP2_VERTEX_ATTRIB12_4_NV                                             = 0x867C,
        MAP2_VERTEX_ATTRIB13_4_NV                                             = 0x867D,
        MAP2_VERTEX_ATTRIB14_4_NV                                             = 0x867E,
        MAP2_VERTEX_ATTRIB15_4_NV                                             = 0x867F,
        VERTEX_ATTRIB_ARRAY_INTEGER_NV                                        = 0x88FD,
        VIDEO_BUFFER_NV                                                       = 0x9020,
        VIDEO_BUFFER_BINDING_NV                                               = 0x9021,
        FIELD_UPPER_NV                                                        = 0x9022,
        FIELD_LOWER_NV                                                        = 0x9023,
        NUM_VIDEO_CAPTURE_STREAMS_NV                                          = 0x9024,
        NEXT_VIDEO_CAPTURE_BUFFER_STATUS_NV                                   = 0x9025,
        VIDEO_CAPTURE_TO_422_SUPPORTED_NV                                     = 0x9026,
        LAST_VIDEO_CAPTURE_STATUS_NV                                          = 0x9027,
        VIDEO_BUFFER_PITCH_NV                                                 = 0x9028,
        VIDEO_COLOR_CONVERSION_MATRIX_NV                                      = 0x9029,
        VIDEO_COLOR_CONVERSION_MAX_NV                                         = 0x902A,
        VIDEO_COLOR_CONVERSION_MIN_NV                                         = 0x902B,
        VIDEO_COLOR_CONVERSION_OFFSET_NV                                      = 0x902C,
        VIDEO_BUFFER_INTERNAL_FORMAT_NV                                       = 0x902D,
        PARTIAL_SUCCESS_NV                                                    = 0x902E,
        SUCCESS_NV                                                            = 0x902F,
        FAILURE_NV                                                            = 0x9030,
        YCBYCR8_422_NV                                                        = 0x9031,
        YCBAYCR8A_4224_NV                                                     = 0x9032,
        Z6Y10Z6CB10Z6Y10Z6CR10_422_NV                                         = 0x9033,
        Z6Y10Z6CB10Z6A10Z6Y10Z6CR10Z6A10_4224_NV                              = 0x9034,
        Z4Y12Z4CB12Z4Y12Z4CR12_422_NV                                         = 0x9035,
        Z4Y12Z4CB12Z4A12Z4Y12Z4CR12Z4A12_4224_NV                              = 0x9036,
        Z4Y12Z4CB12Z4CR12_444_NV                                              = 0x9037,
        VIDEO_CAPTURE_FRAME_WIDTH_NV                                          = 0x9038,
        VIDEO_CAPTURE_FRAME_HEIGHT_NV                                         = 0x9039,
        VIDEO_CAPTURE_FIELD_UPPER_HEIGHT_NV                                   = 0x903A,
        VIDEO_CAPTURE_FIELD_LOWER_HEIGHT_NV                                   = 0x903B,
        VIDEO_CAPTURE_SURFACE_ORIGIN_NV                                       = 0x903C,
        MAX_VIEWPORTS_NV                                                      = 0x825B,
        VIEWPORT_SUBPIXEL_BITS_NV                                             = 0x825C,
        VIEWPORT_BOUNDS_RANGE_NV                                              = 0x825D,
        VIEWPORT_INDEX_PROVOKING_VERTEX_NV                                    = 0x825F,
        VIEWPORT_SWIZZLE_POSITIVE_X_NV                                        = 0x9350,
        VIEWPORT_SWIZZLE_NEGATIVE_X_NV                                        = 0x9351,
        VIEWPORT_SWIZZLE_POSITIVE_Y_NV                                        = 0x9352,
        VIEWPORT_SWIZZLE_NEGATIVE_Y_NV                                        = 0x9353,
        VIEWPORT_SWIZZLE_POSITIVE_Z_NV                                        = 0x9354,
        VIEWPORT_SWIZZLE_NEGATIVE_Z_NV                                        = 0x9355,
        VIEWPORT_SWIZZLE_POSITIVE_W_NV                                        = 0x9356,
        VIEWPORT_SWIZZLE_NEGATIVE_W_NV                                        = 0x9357,
        VIEWPORT_SWIZZLE_X_NV                                                 = 0x9358,
        VIEWPORT_SWIZZLE_Y_NV                                                 = 0x9359,
        VIEWPORT_SWIZZLE_Z_NV                                                 = 0x935A,
        VIEWPORT_SWIZZLE_W_NV                                                 = 0x935B,
        INTERLACE_OML                                                         = 0x8980,
        INTERLACE_READ_OML                                                    = 0x8981,
        PACK_RESAMPLE_OML                                                     = 0x8984,
        UNPACK_RESAMPLE_OML                                                   = 0x8985,
        RESAMPLE_REPLICATE_OML                                                = 0x8986,
        RESAMPLE_ZERO_FILL_OML                                                = 0x8987,
        RESAMPLE_AVERAGE_OML                                                  = 0x8988,
        RESAMPLE_DECIMATE_OML                                                 = 0x8989,
        FORMAT_SUBSAMPLE_24_24_OML                                            = 0x8982,
        FORMAT_SUBSAMPLE_244_244_OML                                          = 0x8983,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_NUM_VIEWS_OVR                          = 0x9630,
        MAX_VIEWS_OVR                                                         = 0x9631,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_INDEX_OVR                    = 0x9632,
        FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR                               = 0x9633,
        VERTEX23_BIT_PGI                                                      = 0x4,
        VERTEX4_BIT_PGI                                                       = 0x8,
        COLOR3_BIT_PGI                                                        = 0x10000,
        COLOR4_BIT_PGI                                                        = 0x20000,
        EDGEFLAG_BIT_PGI                                                      = 0x40000,
        INDEX_BIT_PGI                                                         = 0x80000,
        MAT_AMBIENT_BIT_PGI                                                   = 0x100000,
        MAT_AMBIENT_AND_DIFFUSE_BIT_PGI                                       = 0x200000,
        MAT_DIFFUSE_BIT_PGI                                                   = 0x400000,
        MAT_EMISSION_BIT_PGI                                                  = 0x800000,
        MAT_COLOR_INDEXES_BIT_PGI                                             = 0x1000000,
        MAT_SHININESS_BIT_PGI                                                 = 0x2000000,
        MAT_SPECULAR_BIT_PGI                                                  = 0x4000000,
        NORMAL_BIT_PGI                                                        = 0x8000000,
        TEXCOORD1_BIT_PGI                                                     = 0x10000000,
        TEXCOORD2_BIT_PGI                                                     = 0x20000000,
        TEXCOORD3_BIT_PGI                                                     = 0x40000000,
        TEXCOORD4_BIT_PGI                                                     = 0x80000000,
        ALPHA_TEST_QCOM                                                       = 0xBC0,
        ALPHA_TEST_FUNC_QCOM                                                  = 0xBC1,
        ALPHA_TEST_REF_QCOM                                                   = 0xBC2,
        BINNING_CONTROL_HINT_QCOM                                             = 0x8FB0,
        CPU_OPTIMIZED_QCOM                                                    = 0x8FB1,
        GPU_OPTIMIZED_QCOM                                                    = 0x8FB2,
        RENDER_DIRECT_TO_FRAMEBUFFER_QCOM                                     = 0x8FB3,
        TEXTURE_WIDTH_QCOM                                                    = 0x8BD2,
        TEXTURE_HEIGHT_QCOM                                                   = 0x8BD3,
        TEXTURE_DEPTH_QCOM                                                    = 0x8BD4,
        TEXTURE_INTERNAL_FORMAT_QCOM                                          = 0x8BD5,
        TEXTURE_FORMAT_QCOM                                                   = 0x8BD6,
        TEXTURE_TYPE_QCOM                                                     = 0x8BD7,
        TEXTURE_IMAGE_VALID_QCOM                                              = 0x8BD8,
        TEXTURE_NUM_LEVELS_QCOM                                               = 0x8BD9,
        TEXTURE_TARGET_QCOM                                                   = 0x8BDA,
        TEXTURE_OBJECT_VALID_QCOM                                             = 0x8BDB,
        STATE_RESTORE                                                         = 0x8BDC,
        FOVEATION_ENABLE_BIT_QCOM                                             = 0x1,
        FOVEATION_SCALED_BIN_METHOD_BIT_QCOM                                  = 0x2,
        PERFMON_GLOBAL_MODE_QCOM                                              = 0x8FA0,
        FRAMEBUFFER_FETCH_NONCOHERENT_QCOM                                    = 0x96A2,
        COLOR_BUFFER_BIT0_QCOM                                                = 0x1,
        COLOR_BUFFER_BIT1_QCOM                                                = 0x2,
        COLOR_BUFFER_BIT2_QCOM                                                = 0x4,
        COLOR_BUFFER_BIT3_QCOM                                                = 0x8,
        COLOR_BUFFER_BIT4_QCOM                                                = 0x10,
        COLOR_BUFFER_BIT5_QCOM                                                = 0x20,
        COLOR_BUFFER_BIT6_QCOM                                                = 0x40,
        COLOR_BUFFER_BIT7_QCOM                                                = 0x80,
        DEPTH_BUFFER_BIT0_QCOM                                                = 0x100,
        DEPTH_BUFFER_BIT1_QCOM                                                = 0x200,
        DEPTH_BUFFER_BIT2_QCOM                                                = 0x400,
        DEPTH_BUFFER_BIT3_QCOM                                                = 0x800,
        DEPTH_BUFFER_BIT4_QCOM                                                = 0x1000,
        DEPTH_BUFFER_BIT5_QCOM                                                = 0x2000,
        DEPTH_BUFFER_BIT6_QCOM                                                = 0x4000,
        DEPTH_BUFFER_BIT7_QCOM                                                = 0x8000,
        STENCIL_BUFFER_BIT0_QCOM                                              = 0x10000,
        STENCIL_BUFFER_BIT1_QCOM                                              = 0x20000,
        STENCIL_BUFFER_BIT2_QCOM                                              = 0x40000,
        STENCIL_BUFFER_BIT3_QCOM                                              = 0x80000,
        STENCIL_BUFFER_BIT4_QCOM                                              = 0x100000,
        STENCIL_BUFFER_BIT5_QCOM                                              = 0x200000,
        STENCIL_BUFFER_BIT6_QCOM                                              = 0x400000,
        STENCIL_BUFFER_BIT7_QCOM                                              = 0x800000,
        MULTISAMPLE_BUFFER_BIT0_QCOM                                          = 0x1000000,
        MULTISAMPLE_BUFFER_BIT1_QCOM                                          = 0x2000000,
        MULTISAMPLE_BUFFER_BIT2_QCOM                                          = 0x4000000,
        MULTISAMPLE_BUFFER_BIT3_QCOM                                          = 0x8000000,
        MULTISAMPLE_BUFFER_BIT4_QCOM                                          = 0x10000000,
        MULTISAMPLE_BUFFER_BIT5_QCOM                                          = 0x20000000,
        MULTISAMPLE_BUFFER_BIT6_QCOM                                          = 0x40000000,
        MULTISAMPLE_BUFFER_BIT7_QCOM                                          = 0x80000000,
        WRITEONLY_RENDERING_QCOM                                              = 0x8823,
        ERROR_REGAL                                                           = 0x9322,
        DEBUG_REGAL                                                           = 0x9323,
        LOG_REGAL                                                             = 0x9324,
        EMULATION_REGAL                                                       = 0x9325,
        DRIVER_REGAL                                                          = 0x9326,
        MISSING_REGAL                                                         = 0x9360,
        TRACE_REGAL                                                           = 0x9361,
        CACHE_REGAL                                                           = 0x9362,
        CODE_REGAL                                                            = 0x9363,
        STATISTICS_REGAL                                                      = 0x9364,
        LOG_ERROR_REGAL                                                       = 0x9319,
        LOG_WARNING_REGAL                                                     = 0x931A,
        LOG_INFO_REGAL                                                        = 0x931B,
        LOG_APP_REGAL                                                         = 0x931C,
        LOG_DRIVER_REGAL                                                      = 0x931D,
        LOG_INTERNAL_REGAL                                                    = 0x931E,
        LOG_DEBUG_REGAL                                                       = 0x931F,
        LOG_STATUS_REGAL                                                      = 0x9320,
        LOG_HTTP_REGAL                                                        = 0x9321,
        SCREEN_COORDINATES_REND                                               = 0x8490,
        INVERTED_SCREEN_W_REND                                                = 0x8491,
        RGB_S3TC                                                              = 0x83A0,
        RGB4_S3TC                                                             = 0x83A1,
        RGBA_S3TC                                                             = 0x83A2,
        RGBA4_S3TC                                                            = 0x83A3,
        RGBA_DXT5_S3TC                                                        = 0x83A4,
        RGBA4_DXT5_S3TC                                                       = 0x83A5,
        EXTENDED_RANGE_SGIS                                                   = 0x85A5,
        MIN_RED_SGIS                                                          = 0x85A6,
        MAX_RED_SGIS                                                          = 0x85A7,
        MIN_GREEN_SGIS                                                        = 0x85A8,
        MAX_GREEN_SGIS                                                        = 0x85A9,
        MIN_BLUE_SGIS                                                         = 0x85AA,
        MAX_BLUE_SGIS                                                         = 0x85AB,
        MIN_ALPHA_SGIS                                                        = 0x85AC,
        MAX_ALPHA_SGIS                                                        = 0x85AD,
        GENERATE_MIPMAP_SGIS                                                  = 0x8191,
        GENERATE_MIPMAP_HINT_SGIS                                             = 0x8192,
        MULTISAMPLE_SGIS                                                      = 0x809D,
        SAMPLE_ALPHA_TO_MASK_SGIS                                             = 0x809E,
        SAMPLE_ALPHA_TO_ONE_SGIS                                              = 0x809F,
        SAMPLE_MASK_SGIS                                                      = 0x80A0,
        N1PASS_SGIS                                                           = 0x80A1,
        N2PASS_0_SGIS                                                         = 0x80A2,
        N2PASS_1_SGIS                                                         = 0x80A3,
        N4PASS_0_SGIS                                                         = 0x80A4,
        N4PASS_1_SGIS                                                         = 0x80A5,
        N4PASS_2_SGIS                                                         = 0x80A6,
        N4PASS_3_SGIS                                                         = 0x80A7,
        SAMPLE_BUFFERS_SGIS                                                   = 0x80A8,
        SAMPLES_SGIS                                                          = 0x80A9,
        SAMPLE_MASK_VALUE_SGIS                                                = 0x80AA,
        SAMPLE_MASK_INVERT_SGIS                                               = 0x80AB,
        SAMPLE_PATTERN_SGIS                                                   = 0x80AC,
        SELECTED_TEXTURE_SGIS                                                 = 0x83C0,
        SELECTED_TEXTURE_COORD_SET_SGIS                                       = 0x83C1,
        SELECTED_TEXTURE_TRANSFORM_SGIS                                       = 0x83C2,
        MAX_TEXTURES_SGIS                                                     = 0x83C3,
        MAX_TEXTURE_COORD_SETS_SGIS                                           = 0x83C4,
        TEXTURE_COORD_SET_INTERLEAVE_FACTOR_SGIS                              = 0x83C5,
        TEXTURE_ENV_COORD_SET_SGIS                                            = 0x83C6,
        TEXTURE0_SGIS                                                         = 0x83C7,
        TEXTURE1_SGIS                                                         = 0x83C8,
        TEXTURE2_SGIS                                                         = 0x83C9,
        TEXTURE3_SGIS                                                         = 0x83CA,
        EYE_DISTANCE_TO_POINT_SGIS                                            = 0x81F0,
        OBJECT_DISTANCE_TO_POINT_SGIS                                         = 0x81F1,
        EYE_DISTANCE_TO_LINE_SGIS                                             = 0x81F2,
        OBJECT_DISTANCE_TO_LINE_SGIS                                          = 0x81F3,
        EYE_POINT_SGIS                                                        = 0x81F4,
        OBJECT_POINT_SGIS                                                     = 0x81F5,
        EYE_LINE_SGIS                                                         = 0x81F6,
        OBJECT_LINE_SGIS                                                      = 0x81F7,
        CLAMP_TO_BORDER_SGIS                                                  = 0x812D,
        CLAMP_TO_EDGE_SGIS                                                    = 0x812F,
        TEXTURE_MIN_LOD_SGIS                                                  = 0x813A,
        TEXTURE_MAX_LOD_SGIS                                                  = 0x813B,
        TEXTURE_BASE_LEVEL_SGIS                                               = 0x813C,
        TEXTURE_MAX_LEVEL_SGIS                                                = 0x813D,
        ASYNC_MARKER_SGIX                                                     = 0x8329,
        ASYNC_HISTOGRAM_SGIX                                                  = 0x832C,
        MAX_ASYNC_HISTOGRAM_SGIX                                              = 0x832D,
        ASYNC_TEX_IMAGE_SGIX                                                  = 0x835C,
        ASYNC_DRAW_PIXELS_SGIX                                                = 0x835D,
        ASYNC_READ_PIXELS_SGIX                                                = 0x835E,
        MAX_ASYNC_TEX_IMAGE_SGIX                                              = 0x835F,
        MAX_ASYNC_DRAW_PIXELS_SGIX                                            = 0x8360,
        MAX_ASYNC_READ_PIXELS_SGIX                                            = 0x8361,
        BALI_NUM_TRIS_CULLED_INSTRUMENT                                       = 0x6080,
        BALI_NUM_PRIMS_CLIPPED_INSTRUMENT                                     = 0x6081,
        BALI_NUM_PRIMS_REJECT_INSTRUMENT                                      = 0x6082,
        BALI_NUM_PRIMS_CLIP_RESULT_INSTRUMENT                                 = 0x6083,
        BALI_FRAGMENTS_GENERATED_INSTRUMENT                                   = 0x6090,
        BALI_DEPTH_PASS_INSTRUMENT                                            = 0x6091,
        BALI_R_CHIP_COUNT                                                     = 0x6092,
        ALPHA_MIN_SGIX                                                        = 0x8320,
        ALPHA_MAX_SGIX                                                        = 0x8321,
        FUNC_COMPLEX_ADD_EXT                                                  = 0x601C,
        FUNC_COMPLEX_MULTIPLY_EXT                                             = 0x601B,
        COLOR_MATRIX_HINT                                                     = 0x8317,
        CONVOLUTION_HINT_SGIX                                                 = 0x8316,
        ENV_MAP_SGIX                                                          = 0x8340,
        CUBE_MAP_SGIX                                                         = 0x8341,
        CUBE_MAP_ZP_SGIX                                                      = 0x8342,
        CUBE_MAP_ZN_SGIX                                                      = 0x8343,
        CUBE_MAP_XN_SGIX                                                      = 0x8344,
        CUBE_MAP_XP_SGIX                                                      = 0x8345,
        CUBE_MAP_YN_SGIX                                                      = 0x8346,
        CUBE_MAP_YP_SGIX                                                      = 0x8347,
        CUBE_MAP_BINDING_SGIX                                                 = 0x8348,
        GEOMETRY_BIT                                                          = 0x1,
        IMAGE_BIT                                                             = 0x2,
        DEPTH_PASS_INSTRUMENT_SGIX                                            = 0x8310,
        DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX                                   = 0x8311,
        DEPTH_PASS_INSTRUMENT_MAX_SGIX                                        = 0x8312,
        DEPTH_COMPONENT16_SGIX                                                = 0x81A5,
        DEPTH_COMPONENT24_SGIX                                                = 0x81A6,
        DEPTH_COMPONENT32_SGIX                                                = 0x81A7,
        FOG_BLEND_ALPHA_SGIX                                                  = 0x81FE,
        FOG_BLEND_COLOR_SGIX                                                  = 0x81FF,
        FOG_TYPE_SGIX                                                         = 0x8323,
        UNIFORM_SGIX                                                          = 0x8324,
        LAYERED_SGIX                                                          = 0x8325,
        FOG_GROUND_PLANE_SGIX                                                 = 0x8326,
        FOG_LAYERS_POINTS_SGIX                                                = 0x8327,
        MAX_FOG_LAYERS_POINTS_SGIX                                            = 0x8328,
        FOG_OFFSET_SGIX                                                       = 0x8198,
        FOG_OFFSET_VALUE_SGIX                                                 = 0x8199,
        FOG_SCALE_SGIX                                                        = 0x81FC,
        FOG_SCALE_VALUE_SGIX                                                  = 0x81FD,
        EYE_SPACE_SGIX                                                        = 0x8436,
        TANGENT_SPACE_SGIX                                                    = 0x8437,
        OBJECT_SPACE_SGIX                                                     = 0x8438,
        FRAGMENT_LIGHT_SPACE_SGIX                                             = 0x843D,
        FRAGMENTS_INSTRUMENT_SGIX                                             = 0x8313,
        FRAGMENTS_INSTRUMENT_COUNTERS_SGIX                                    = 0x8314,
        FRAGMENTS_INSTRUMENT_MAX_SGIX                                         = 0x8315,
        RGB_ICC_SGIX                                                          = 0x8460,
        RGBA_ICC_SGIX                                                         = 0x8461,
        ALPHA_ICC_SGIX                                                        = 0x8462,
        LUMINANCE_ICC_SGIX                                                    = 0x8463,
        INTENSITY_ICC_SGIX                                                    = 0x8464,
        LUMINANCE_ALPHA_ICC_SGIX                                              = 0x8465,
        R5_G6_B5_ICC_SGIX                                                     = 0x8466,
        R5_G6_B5_A8_ICC_SGIX                                                  = 0x8467,
        ALPHA16_ICC_SGIX                                                      = 0x8468,
        LUMINANCE16_ICC_SGIX                                                  = 0x8469,
        INTENSITY16_ICC_SGIX                                                  = 0x846A,
        LUMINANCE16_ALPHA8_ICC_SGIX                                           = 0x846B,
        IGLOO_FULLSCREEN_SGIX                                                 = 0x819E,
        IGLOO_VIEWPORT_OFFSET_SGIX                                            = 0x819F,
        IGLOO_SWAPTMESH_SGIX                                                  = 0x81A0,
        IGLOO_COLORNORMAL_SGIX                                                = 0x81A1,
        IGLOO_IRISGL_MODE_SGIX                                                = 0x81A2,
        IGLOO_LMC_COLOR_SGIX                                                  = 0x81A3,
        IGLOO_TMESHMODE_SGIX                                                  = 0x81A4,
        LIGHT31                                                               = 0xBEAD,
        INTERLACE_SGIX                                                        = 0x8094,
        LINE_QUALITY_HINT_SGIX                                                = 0x835B,
        MAP1_VERTEX_3_NURBS_SGIX                                              = 0x81CB,
        MAP1_VERTEX_4_NURBS_SGIX                                              = 0x81CC,
        MAP1_INDEX_NURBS_SGIX                                                 = 0x81CD,
        MAP1_COLOR_4_NURBS_SGIX                                               = 0x81CE,
        MAP1_NORMAL_NURBS_SGIX                                                = 0x81CF,
        MAP1_TEXTURE_COORD_1_NURBS_SGIX                                       = 0x81E0,
        MAP1_TEXTURE_COORD_2_NURBS_SGIX                                       = 0x81E1,
        MAP1_TEXTURE_COORD_3_NURBS_SGIX                                       = 0x81E2,
        MAP1_TEXTURE_COORD_4_NURBS_SGIX                                       = 0x81E3,
        MAP2_VERTEX_3_NURBS_SGIX                                              = 0x81E4,
        MAP2_VERTEX_4_NURBS_SGIX                                              = 0x81E5,
        MAP2_INDEX_NURBS_SGIX                                                 = 0x81E6,
        MAP2_COLOR_4_NURBS_SGIX                                               = 0x81E7,
        MAP2_NORMAL_NURBS_SGIX                                                = 0x81E8,
        MAP2_TEXTURE_COORD_1_NURBS_SGIX                                       = 0x81E9,
        MAP2_TEXTURE_COORD_2_NURBS_SGIX                                       = 0x81EA,
        MAP2_TEXTURE_COORD_3_NURBS_SGIX                                       = 0x81EB,
        MAP2_TEXTURE_COORD_4_NURBS_SGIX                                       = 0x81EC,
        NURBS_KNOT_COUNT_SGIX                                                 = 0x81ED,
        NURBS_KNOT_VECTOR_SGIX                                                = 0x81EE,
        OCCLUSION_INSTRUMENT_SGIX                                             = 0x6060,
        TEXTURE_DEFORMATION_BIT_SGIX                                          = 0x1,
        GEOMETRY_DEFORMATION_BIT_SGIX                                         = 0x2,
        PACK_RESAMPLE_SGIX                                                    = 0x842E,
        UNPACK_RESAMPLE_SGIX                                                  = 0x842F,
        RESAMPLE_DECIMATE_SGIX                                                = 0x8430,
        RESAMPLE_REPLICATE_SGIX                                               = 0x8433,
        RESAMPLE_ZERO_FILL_SGIX                                               = 0x8434,
        SCALEBIAS_HINT_SGIX                                                   = 0x8322,
        TEXTURE_COMPARE_SGIX                                                  = 0x819A,
        TEXTURE_COMPARE_OPERATOR_SGIX                                         = 0x819B,
        TEXTURE_LEQUAL_R_SGIX                                                 = 0x819C,
        TEXTURE_GEQUAL_R_SGIX                                                 = 0x819D,
        SHADOW_AMBIENT_SGIX                                                   = 0x80BF,
        PACK_MAX_COMPRESSED_SIZE_SGIX                                         = 0x831B,
        SLIM8U_SGIX                                                           = 0x831D,
        SLIM10U_SGIX                                                          = 0x831E,
        SLIM12S_SGIX                                                          = 0x831F,
        SPOT_CUTOFF_DELTA_SGIX                                                = 0x8193,
        PACK_SUBSAMPLE_RATE_SGIX                                              = 0x85A0,
        UNPACK_SUBSAMPLE_RATE_SGIX                                            = 0x85A1,
        PIXEL_SUBSAMPLE_4444_SGIX                                             = 0x85A2,
        PIXEL_SUBSAMPLE_2424_SGIX                                             = 0x85A3,
        PIXEL_SUBSAMPLE_4242_SGIX                                             = 0x85A4,
        TEXTURE_MAX_CLAMP_S_SGIX                                              = 0x8369,
        TEXTURE_MAX_CLAMP_T_SGIX                                              = 0x836A,
        TEXTURE_MAX_CLAMP_R_SGIX                                              = 0x836B,
        TEXTURE_MIPMAP_ANISOTROPY_SGIX                                        = 0x832E,
        MAX_MIPMAP_ANISOTROPY_SGIX                                            = 0x832F,
        TEXTURE_MULTI_BUFFER_HINT_SGIX                                        = 0x812E,
        PHASE_SGIX                                                            = 0x832A,
        RGB_SIGNED_SGIX                                                       = 0x85E0,
        RGBA_SIGNED_SGIX                                                      = 0x85E1,
        ALPHA_SIGNED_SGIX                                                     = 0x85E2,
        LUMINANCE_SIGNED_SGIX                                                 = 0x85E3,
        INTENSITY_SIGNED_SGIX                                                 = 0x85E4,
        LUMINANCE_ALPHA_SIGNED_SGIX                                           = 0x85E5,
        RGB16_SIGNED_SGIX                                                     = 0x85E6,
        RGBA16_SIGNED_SGIX                                                    = 0x85E7,
        ALPHA16_SIGNED_SGIX                                                   = 0x85E8,
        LUMINANCE16_SIGNED_SGIX                                               = 0x85E9,
        INTENSITY16_SIGNED_SGIX                                               = 0x85EA,
        LUMINANCE16_ALPHA16_SIGNED_SGIX                                       = 0x85EB,
        RGB_EXTENDED_RANGE_SGIX                                               = 0x85EC,
        RGBA_EXTENDED_RANGE_SGIX                                              = 0x85ED,
        ALPHA_EXTENDED_RANGE_SGIX                                             = 0x85EE,
        LUMINANCE_EXTENDED_RANGE_SGIX                                         = 0x85EF,
        INTENSITY_EXTENDED_RANGE_SGIX                                         = 0x85F0,
        LUMINANCE_ALPHA_EXTENDED_RANGE_SGIX                                   = 0x85F1,
        RGB16_EXTENDED_RANGE_SGIX                                             = 0x85F2,
        RGBA16_EXTENDED_RANGE_SGIX                                            = 0x85F3,
        ALPHA16_EXTENDED_RANGE_SGIX                                           = 0x85F4,
        LUMINANCE16_EXTENDED_RANGE_SGIX                                       = 0x85F5,
        INTENSITY16_EXTENDED_RANGE_SGIX                                       = 0x85F6,
        LUMINANCE16_ALPHA16_EXTENDED_RANGE_SGIX                               = 0x85F7,
        MIN_LUMINANCE_SGIS                                                    = 0x85F8,
        MAX_LUMINANCE_SGIS                                                    = 0x85F9,
        MIN_INTENSITY_SGIS                                                    = 0x85FA,
        MAX_INTENSITY_SGIS                                                    = 0x85FB,
        POST_TEXTURE_FILTER_BIAS_SGIX                                         = 0x8179,
        POST_TEXTURE_FILTER_SCALE_SGIX                                        = 0x817A,
        POST_TEXTURE_FILTER_BIAS_RANGE_SGIX                                   = 0x817B,
        POST_TEXTURE_FILTER_SCALE_RANGE_SGIX                                  = 0x817C,
        VERTEX_PRECLIP_SGIX                                                   = 0x83EE,
        VERTEX_PRECLIP_HINT_SGIX                                              = 0x83EF,
        YCRCB_SGIX                                                            = 0x8318,
        YCRCBA_SGIX                                                           = 0x8319,
        COLOR_MATRIX_SGI                                                      = 0x80B1,
        COLOR_MATRIX_STACK_DEPTH_SGI                                          = 0x80B2,
        MAX_COLOR_MATRIX_STACK_DEPTH_SGI                                      = 0x80B3,
        POST_COLOR_MATRIX_RED_SCALE_SGI                                       = 0x80B4,
        POST_COLOR_MATRIX_GREEN_SCALE_SGI                                     = 0x80B5,
        POST_COLOR_MATRIX_BLUE_SCALE_SGI                                      = 0x80B6,
        POST_COLOR_MATRIX_ALPHA_SCALE_SGI                                     = 0x80B7,
        POST_COLOR_MATRIX_RED_BIAS_SGI                                        = 0x80B8,
        POST_COLOR_MATRIX_GREEN_BIAS_SGI                                      = 0x80B9,
        POST_COLOR_MATRIX_BLUE_BIAS_SGI                                       = 0x80BA,
        POST_COLOR_MATRIX_ALPHA_BIAS_SGI                                      = 0x80BB,
        COLOR_TABLE_SGI                                                       = 0x80D0,
        POST_CONVOLUTION_COLOR_TABLE_SGI                                      = 0x80D1,
        POST_COLOR_MATRIX_COLOR_TABLE_SGI                                     = 0x80D2,
        PROXY_COLOR_TABLE_SGI                                                 = 0x80D3,
        PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI                                = 0x80D4,
        PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI                               = 0x80D5,
        COLOR_TABLE_SCALE_SGI                                                 = 0x80D6,
        COLOR_TABLE_BIAS_SGI                                                  = 0x80D7,
        COLOR_TABLE_FORMAT_SGI                                                = 0x80D8,
        COLOR_TABLE_WIDTH_SGI                                                 = 0x80D9,
        COLOR_TABLE_RED_SIZE_SGI                                              = 0x80DA,
        COLOR_TABLE_GREEN_SIZE_SGI                                            = 0x80DB,
        COLOR_TABLE_BLUE_SIZE_SGI                                             = 0x80DC,
        COLOR_TABLE_ALPHA_SIZE_SGI                                            = 0x80DD,
        COLOR_TABLE_LUMINANCE_SIZE_SGI                                        = 0x80DE,
        COLOR_TABLE_INTENSITY_SIZE_SGI                                        = 0x80DF,
        COMPLEX_UNSIGNED_BYTE_SGI                                             = 0x81BD,
        COMPLEX_BYTE_SGI                                                      = 0x81BE,
        COMPLEX_UNSIGNED_SHORT_SGI                                            = 0x81BF,
        COMPLEX_SHORT_SGI                                                     = 0x81C0,
        COMPLEX_UNSIGNED_INT_SGI                                              = 0x81C1,
        COMPLEX_INT_SGI                                                       = 0x81C2,
        COMPLEX_FLOAT_SGI                                                     = 0x81C3,
        PIXEL_TRANSFORM_OPERATOR_SGI                                          = 0x81C4,
        CONVOLUTION_SGI                                                       = 0x81C5,
        FFT_1D_SGI                                                            = 0x81C6,
        PIXEL_TRANSFORM_SGI                                                   = 0x81C7,
        MAX_FFT_WIDTH_SGI                                                     = 0x81C8,
        TEXTURE_COLOR_TABLE_SGI                                               = 0x80BC,
        PROXY_TEXTURE_COLOR_TABLE_SGI                                         = 0x80BD,
        UNPACK_CONSTANT_DATA_SUNX                                             = 0x81D5,
        TEXTURE_CONSTANT_DATA_SUNX                                            = 0x81D6,
        WRAP_BORDER_SUN                                                       = 0x81D4,
        GLOBAL_ALPHA_SUN                                                      = 0x81D9,
        GLOBAL_ALPHA_FACTOR_SUN                                               = 0x81DA,
        QUAD_MESH_SUN                                                         = 0x8614,
        TRIANGLE_MESH_SUN                                                     = 0x8615,
        SLICE_ACCUM_SUN                                                       = 0x85CC,
        RESTART_SUN                                                           = 0x1,
        REPLACE_MIDDLE_SUN                                                    = 0x2,
        REPLACE_OLDEST_SUN                                                    = 0x3,
        TRIANGLE_LIST_SUN                                                     = 0x81D7,
        REPLACEMENT_CODE_SUN                                                  = 0x81D8,
        REPLACEMENT_CODE_ARRAY_SUN                                            = 0x85C0,
        REPLACEMENT_CODE_ARRAY_TYPE_SUN                                       = 0x85C1,
        REPLACEMENT_CODE_ARRAY_STRIDE_SUN                                     = 0x85C2,
        REPLACEMENT_CODE_ARRAY_POINTER_SUN                                    = 0x85C3,
        R1UI_V3F_SUN                                                          = 0x85C4,
        R1UI_C4UB_V3F_SUN                                                     = 0x85C5,
        R1UI_C3F_V3F_SUN                                                      = 0x85C6,
        R1UI_N3F_V3F_SUN                                                      = 0x85C7,
        R1UI_C4F_N3F_V3F_SUN                                                  = 0x85C8,
        R1UI_T2F_V3F_SUN                                                      = 0x85C9,
        R1UI_T2F_N3F_V3F_SUN                                                  = 0x85CA,
        R1UI_T2F_C4F_N3F_V3F_SUN                                              = 0x85CB,
        PHONG_WIN                                                             = 0x80EA,
        PHONG_HINT_WIN                                                        = 0x80EB,
        FOG_SPECULAR_TEXTURE_WIN                                              = 0x80EC,
    };
#pragma endregion

#pragma region GL Functions
#define GLPORT_ON_FUNCTIONS(M) \
    M(Accum,                                                 void,          (Enum)(op)(Float)(value)) \
    M(AlphaFunc,                                             void,          (Enum)(func)(FClamp)(ref)) \
    M(AreTexturesResident,                                   Bool,          (Isize)(n)(const Uint*)(textures)(Bool*)(residences)) \
    M(ArrayElement,                                          void,          (Int)(i)) \
    M(Begin,                                                 void,          (Enum)(mode)) \
    M(BindTexture,                                           void,          (Enum)(target)(Uint)(texture)) \
    M(Bitmap,                                                void,          (Isize)(width)(Isize)(height)(Float)(xorig)(Float)(yorig)(Float)(xmove)(Float)(ymove)(const Ubyte*)(bitmap)) \
    M(BlendFunc,                                             void,          (Enum)(sfactor)(Enum)(dfactor)) \
    M(CallList,                                              void,          (Uint)(list)) \
    M(CallLists,                                             void,          (Isize)(n)(Enum)(type)(const void*)(lists)) \
    M(Clear,                                                 void,          (Bitfield)(mask)) \
    M(ClearAccum,                                            void,          (Float)(red)(Float)(green)(Float)(blue)(Float)(alpha)) \
    M(ClearColor,                                            void,          (FClamp)(red)(FClamp)(green)(FClamp)(blue)(FClamp)(alpha)) \
    M(ClearDepth,                                            void,          (DClamp)(depth)) \
    M(ClearIndex,                                            void,          (Float)(c)) \
    M(ClearStencil,                                          void,          (Int)(s)) \
    M(ClipPlane,                                             void,          (Enum)(plane)(const Double*)(equation)) \
    M(Color3b,                                               void,          (Byte)(red)(Byte)(green)(Byte)(blue)) \
    M(Color3bv,                                              void,          (const Byte*)(v)) \
    M(Color3d,                                               void,          (Double)(red)(Double)(green)(Double)(blue)) \
    M(Color3dv,                                              void,          (const Double*)(v)) \
    M(Color3f,                                               void,          (Float)(red)(Float)(green)(Float)(blue)) \
    M(Color3fv,                                              void,          (const Float*)(v)) \
    M(Color3i,                                               void,          (Int)(red)(Int)(green)(Int)(blue)) \
    M(Color3iv,                                              void,          (const Int*)(v)) \
    M(Color3s,                                               void,          (Short)(red)(Short)(green)(Short)(blue)) \
    M(Color3sv,                                              void,          (const Short*)(v)) \
    M(Color3ub,                                              void,          (Ubyte)(red)(Ubyte)(green)(Ubyte)(blue)) \
    M(Color3ubv,                                             void,          (const Ubyte*)(v)) \
    M(Color3ui,                                              void,          (Uint)(red)(Uint)(green)(Uint)(blue)) \
    M(Color3uiv,                                             void,          (const Uint*)(v)) \
    M(Color3us,                                              void,          (Ushort)(red)(Ushort)(green)(Ushort)(blue)) \
    M(Color3usv,                                             void,          (const Ushort*)(v)) \
    M(Color4b,                                               void,          (Byte)(red)(Byte)(green)(Byte)(blue)(Byte)(alpha)) \
    M(Color4bv,                                              void,          (const Byte*)(v)) \
    M(Color4d,                                               void,          (Double)(red)(Double)(green)(Double)(blue)(Double)(alpha)) \
    M(Color4dv,                                              void,          (const Double*)(v)) \
    M(Color4f,                                               void,          (Float)(red)(Float)(green)(Float)(blue)(Float)(alpha)) \
    M(Color4fv,                                              void,          (const Float*)(v)) \
    M(Color4i,                                               void,          (Int)(red)(Int)(green)(Int)(blue)(Int)(alpha)) \
    M(Color4iv,                                              void,          (const Int*)(v)) \
    M(Color4s,                                               void,          (Short)(red)(Short)(green)(Short)(blue)(Short)(alpha)) \
    M(Color4sv,                                              void,          (const Short*)(v)) \
    M(Color4ub,                                              void,          (Ubyte)(red)(Ubyte)(green)(Ubyte)(blue)(Ubyte)(alpha)) \
    M(Color4ubv,                                             void,          (const Ubyte*)(v)) \
    M(Color4ui,                                              void,          (Uint)(red)(Uint)(green)(Uint)(blue)(Uint)(alpha)) \
    M(Color4uiv,                                             void,          (const Uint*)(v)) \
    M(Color4us,                                              void,          (Ushort)(red)(Ushort)(green)(Ushort)(blue)(Ushort)(alpha)) \
    M(Color4usv,                                             void,          (const Ushort*)(v)) \
    M(ColorMask,                                             void,          (Bool)(red)(Bool)(green)(Bool)(blue)(Bool)(alpha)) \
    M(ColorMaterial,                                         void,          (Enum)(face)(Enum)(mode)) \
    M(ColorPointer,                                          void,          (Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(CopyPixels,                                            void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Enum)(type)) \
    M(CopyTexImage1D,                                        void,          (Enum)(target)(Int)(level)(Enum)(internalFormat)(Int)(x)(Int)(y)(Isize)(width)(Int)(border)) \
    M(CopyTexImage2D,                                        void,          (Enum)(target)(Int)(level)(Enum)(internalFormat)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Int)(border)) \
    M(CopyTexSubImage1D,                                     void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyTexSubImage2D,                                     void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CullFace,                                              void,          (Enum)(mode)) \
    M(DeleteLists,                                           void,          (Uint)(list)(Isize)(range)) \
    M(DeleteTextures,                                        void,          (Isize)(n)(const Uint*)(textures)) \
    M(DepthFunc,                                             void,          (Enum)(func)) \
    M(DepthMask,                                             void,          (Bool)(flag)) \
    M(DepthRange,                                            void,          (DClamp)(zNear)(DClamp)(zFar)) \
    M(Disable,                                               void,          (Enum)(cap)) \
    M(DisableClientState,                                    void,          (Enum)(array)) \
    M(DrawArrays,                                            void,          (Enum)(mode)(Int)(first)(Isize)(count)) \
    M(DrawBuffer,                                            void,          (Enum)(mode)) \
    M(DrawElements,                                          void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)) \
    M(DrawPixels,                                            void,          (Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(EdgeFlag,                                              void,          (Bool)(flag)) \
    M(EdgeFlagPointer,                                       void,          (Isize)(stride)(const void*)(pointer)) \
    M(EdgeFlagv,                                             void,          (const Bool*)(flag)) \
    M(Enable,                                                void,          (Enum)(cap)) \
    M(EnableClientState,                                     void,          (Enum)(array)) \
    M(End,                                                   void,          ) \
    M(EndList,                                               void,          ) \
    M(EvalCoord1d,                                           void,          (Double)(u)) \
    M(EvalCoord1dv,                                          void,          (const Double*)(u)) \
    M(EvalCoord1f,                                           void,          (Float)(u)) \
    M(EvalCoord1fv,                                          void,          (const Float*)(u)) \
    M(EvalCoord2d,                                           void,          (Double)(u)(Double)(v)) \
    M(EvalCoord2dv,                                          void,          (const Double*)(u)) \
    M(EvalCoord2f,                                           void,          (Float)(u)(Float)(v)) \
    M(EvalCoord2fv,                                          void,          (const Float*)(u)) \
    M(EvalMesh1,                                             void,          (Enum)(mode)(Int)(i1)(Int)(i2)) \
    M(EvalMesh2,                                             void,          (Enum)(mode)(Int)(i1)(Int)(i2)(Int)(j1)(Int)(j2)) \
    M(EvalPoint1,                                            void,          (Int)(i)) \
    M(EvalPoint2,                                            void,          (Int)(i)(Int)(j)) \
    M(FeedbackBuffer,                                        void,          (Isize)(size)(Enum)(type)(Float*)(buffer)) \
    M(Finish,                                                void,          ) \
    M(Flush,                                                 void,          ) \
    M(Fogf,                                                  void,          (Enum)(pname)(Float)(param)) \
    M(Fogfv,                                                 void,          (Enum)(pname)(const Float*)(params)) \
    M(Fogi,                                                  void,          (Enum)(pname)(Int)(param)) \
    M(Fogiv,                                                 void,          (Enum)(pname)(const Int*)(params)) \
    M(FrontFace,                                             void,          (Enum)(mode)) \
    M(Frustum,                                               void,          (Double)(left)(Double)(right)(Double)(bottom)(Double)(top)(Double)(zNear)(Double)(zFar)) \
    M(GenLists,                                              Uint,          (Isize)(range)) \
    M(GenTextures,                                           void,          (Isize)(n)(Uint*)(textures)) \
    M(GetBooleanv,                                           void,          (Enum)(pname)(Bool*)(params)) \
    M(GetClipPlane,                                          void,          (Enum)(plane)(Double*)(equation)) \
    M(GetDoublev,                                            void,          (Enum)(pname)(Double*)(params)) \
    M(GetError,                                              Enum,          ) \
    M(GetFloatv,                                             void,          (Enum)(pname)(Float*)(params)) \
    M(GetIntegerv,                                           void,          (Enum)(pname)(Int*)(params)) \
    M(GetLightfv,                                            void,          (Enum)(light)(Enum)(pname)(Float*)(params)) \
    M(GetLightiv,                                            void,          (Enum)(light)(Enum)(pname)(Int*)(params)) \
    M(GetMapdv,                                              void,          (Enum)(target)(Enum)(query)(Double*)(v)) \
    M(GetMapfv,                                              void,          (Enum)(target)(Enum)(query)(Float*)(v)) \
    M(GetMapiv,                                              void,          (Enum)(target)(Enum)(query)(Int*)(v)) \
    M(GetMaterialfv,                                         void,          (Enum)(face)(Enum)(pname)(Float*)(params)) \
    M(GetMaterialiv,                                         void,          (Enum)(face)(Enum)(pname)(Int*)(params)) \
    M(GetPixelMapfv,                                         void,          (Enum)(map)(Float*)(values)) \
    M(GetPixelMapuiv,                                        void,          (Enum)(map)(Uint*)(values)) \
    M(GetPixelMapusv,                                        void,          (Enum)(map)(Ushort*)(values)) \
    M(GetPointerv,                                           void,          (Enum)(pname)(void**)(params)) \
    M(GetPolygonStipple,                                     void,          (Ubyte*)(mask)) \
    M(GetString,                                             const Ubyte *, (Enum)(name)) \
    M(GetTexEnvfv,                                           void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetTexEnviv,                                           void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetTexGendv,                                           void,          (Enum)(coord)(Enum)(pname)(Double*)(params)) \
    M(GetTexGenfv,                                           void,          (Enum)(coord)(Enum)(pname)(Float*)(params)) \
    M(GetTexGeniv,                                           void,          (Enum)(coord)(Enum)(pname)(Int*)(params)) \
    M(GetTexImage,                                           void,          (Enum)(target)(Int)(level)(Enum)(format)(Enum)(type)(void*)(pixels)) \
    M(GetTexLevelParameterfv,                                void,          (Enum)(target)(Int)(level)(Enum)(pname)(Float*)(params)) \
    M(GetTexLevelParameteriv,                                void,          (Enum)(target)(Int)(level)(Enum)(pname)(Int*)(params)) \
    M(GetTexParameterfv,                                     void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetTexParameteriv,                                     void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(Hint,                                                  void,          (Enum)(target)(Enum)(mode)) \
    M(IndexMask,                                             void,          (Uint)(mask)) \
    M(IndexPointer,                                          void,          (Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(Indexd,                                                void,          (Double)(c)) \
    M(Indexdv,                                               void,          (const Double*)(c)) \
    M(Indexf,                                                void,          (Float)(c)) \
    M(Indexfv,                                               void,          (const Float*)(c)) \
    M(Indexi,                                                void,          (Int)(c)) \
    M(Indexiv,                                               void,          (const Int*)(c)) \
    M(Indexs,                                                void,          (Short)(c)) \
    M(Indexsv,                                               void,          (const Short*)(c)) \
    M(Indexub,                                               void,          (Ubyte)(c)) \
    M(Indexubv,                                              void,          (const Ubyte*)(c)) \
    M(InitNames,                                             void,          ) \
    M(InterleavedArrays,                                     void,          (Enum)(format)(Isize)(stride)(const void*)(pointer)) \
    M(IsEnabled,                                             Bool,          (Enum)(cap)) \
    M(IsList,                                                Bool,          (Uint)(list)) \
    M(IsTexture,                                             Bool,          (Uint)(texture)) \
    M(LightModelf,                                           void,          (Enum)(pname)(Float)(param)) \
    M(LightModelfv,                                          void,          (Enum)(pname)(const Float*)(params)) \
    M(LightModeli,                                           void,          (Enum)(pname)(Int)(param)) \
    M(LightModeliv,                                          void,          (Enum)(pname)(const Int*)(params)) \
    M(Lightf,                                                void,          (Enum)(light)(Enum)(pname)(Float)(param)) \
    M(Lightfv,                                               void,          (Enum)(light)(Enum)(pname)(const Float*)(params)) \
    M(Lighti,                                                void,          (Enum)(light)(Enum)(pname)(Int)(param)) \
    M(Lightiv,                                               void,          (Enum)(light)(Enum)(pname)(const Int*)(params)) \
    M(LineStipple,                                           void,          (Int)(factor)(Ushort)(pattern)) \
    M(LineWidth,                                             void,          (Float)(width)) \
    M(ListBase,                                              void,          (Uint)(base)) \
    M(LoadIdentity,                                          void,          ) \
    M(LoadMatrixd,                                           void,          (const Double*)(m)) \
    M(LoadMatrixf,                                           void,          (const Float*)(m)) \
    M(LoadName,                                              void,          (Uint)(name)) \
    M(LogicOp,                                               void,          (Enum)(opcode)) \
    M(Map1d,                                                 void,          (Enum)(target)(Double)(u1)(Double)(u2)(Int)(stride)(Int)(order)(const Double*)(points)) \
    M(Map1f,                                                 void,          (Enum)(target)(Float)(u1)(Float)(u2)(Int)(stride)(Int)(order)(const Float*)(points)) \
    M(Map2d,                                                 void,          (Enum)(target)(Double)(u1)(Double)(u2)(Int)(ustride)(Int)(uorder)(Double)(v1)(Double)(v2)(Int)(vstride)(Int)(vorder)(const Double*)(points)) \
    M(Map2f,                                                 void,          (Enum)(target)(Float)(u1)(Float)(u2)(Int)(ustride)(Int)(uorder)(Float)(v1)(Float)(v2)(Int)(vstride)(Int)(vorder)(const Float*)(points)) \
    M(MapGrid1d,                                             void,          (Int)(un)(Double)(u1)(Double)(u2)) \
    M(MapGrid1f,                                             void,          (Int)(un)(Float)(u1)(Float)(u2)) \
    M(MapGrid2d,                                             void,          (Int)(un)(Double)(u1)(Double)(u2)(Int)(vn)(Double)(v1)(Double)(v2)) \
    M(MapGrid2f,                                             void,          (Int)(un)(Float)(u1)(Float)(u2)(Int)(vn)(Float)(v1)(Float)(v2)) \
    M(Materialf,                                             void,          (Enum)(face)(Enum)(pname)(Float)(param)) \
    M(Materialfv,                                            void,          (Enum)(face)(Enum)(pname)(const Float*)(params)) \
    M(Materiali,                                             void,          (Enum)(face)(Enum)(pname)(Int)(param)) \
    M(Materialiv,                                            void,          (Enum)(face)(Enum)(pname)(const Int*)(params)) \
    M(MatrixMode,                                            void,          (Enum)(mode)) \
    M(MultMatrixd,                                           void,          (const Double*)(m)) \
    M(MultMatrixf,                                           void,          (const Float*)(m)) \
    M(NewList,                                               void,          (Uint)(list)(Enum)(mode)) \
    M(Normal3b,                                              void,          (Byte)(nx)(Byte)(ny)(Byte)(nz)) \
    M(Normal3bv,                                             void,          (const Byte*)(v)) \
    M(Normal3d,                                              void,          (Double)(nx)(Double)(ny)(Double)(nz)) \
    M(Normal3dv,                                             void,          (const Double*)(v)) \
    M(Normal3f,                                              void,          (Float)(nx)(Float)(ny)(Float)(nz)) \
    M(Normal3fv,                                             void,          (const Float*)(v)) \
    M(Normal3i,                                              void,          (Int)(nx)(Int)(ny)(Int)(nz)) \
    M(Normal3iv,                                             void,          (const Int*)(v)) \
    M(Normal3s,                                              void,          (Short)(nx)(Short)(ny)(Short)(nz)) \
    M(Normal3sv,                                             void,          (const Short*)(v)) \
    M(NormalPointer,                                         void,          (Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(Ortho,                                                 void,          (Double)(left)(Double)(right)(Double)(bottom)(Double)(top)(Double)(zNear)(Double)(zFar)) \
    M(PassThrough,                                           void,          (Float)(token)) \
    M(PixelMapfv,                                            void,          (Enum)(map)(Isize)(mapsize)(const Float*)(values)) \
    M(PixelMapuiv,                                           void,          (Enum)(map)(Isize)(mapsize)(const Uint*)(values)) \
    M(PixelMapusv,                                           void,          (Enum)(map)(Isize)(mapsize)(const Ushort*)(values)) \
    M(PixelStoref,                                           void,          (Enum)(pname)(Float)(param)) \
    M(PixelStorei,                                           void,          (Enum)(pname)(Int)(param)) \
    M(PixelTransferf,                                        void,          (Enum)(pname)(Float)(param)) \
    M(PixelTransferi,                                        void,          (Enum)(pname)(Int)(param)) \
    M(PixelZoom,                                             void,          (Float)(xfactor)(Float)(yfactor)) \
    M(PointSize,                                             void,          (Float)(size)) \
    M(PolygonMode,                                           void,          (Enum)(face)(Enum)(mode)) \
    M(PolygonOffset,                                         void,          (Float)(factor)(Float)(units)) \
    M(PolygonStipple,                                        void,          (const Ubyte*)(mask)) \
    M(PopAttrib,                                             void,          ) \
    M(PopClientAttrib,                                       void,          ) \
    M(PopMatrix,                                             void,          ) \
    M(PopName,                                               void,          ) \
    M(PrioritizeTextures,                                    void,          (Isize)(n)(const Uint*)(textures)(const FClamp*)(priorities)) \
    M(PushAttrib,                                            void,          (Bitfield)(mask)) \
    M(PushClientAttrib,                                      void,          (Bitfield)(mask)) \
    M(PushMatrix,                                            void,          ) \
    M(PushName,                                              void,          (Uint)(name)) \
    M(RasterPos2d,                                           void,          (Double)(x)(Double)(y)) \
    M(RasterPos2dv,                                          void,          (const Double*)(v)) \
    M(RasterPos2f,                                           void,          (Float)(x)(Float)(y)) \
    M(RasterPos2fv,                                          void,          (const Float*)(v)) \
    M(RasterPos2i,                                           void,          (Int)(x)(Int)(y)) \
    M(RasterPos2iv,                                          void,          (const Int*)(v)) \
    M(RasterPos2s,                                           void,          (Short)(x)(Short)(y)) \
    M(RasterPos2sv,                                          void,          (const Short*)(v)) \
    M(RasterPos3d,                                           void,          (Double)(x)(Double)(y)(Double)(z)) \
    M(RasterPos3dv,                                          void,          (const Double*)(v)) \
    M(RasterPos3f,                                           void,          (Float)(x)(Float)(y)(Float)(z)) \
    M(RasterPos3fv,                                          void,          (const Float*)(v)) \
    M(RasterPos3i,                                           void,          (Int)(x)(Int)(y)(Int)(z)) \
    M(RasterPos3iv,                                          void,          (const Int*)(v)) \
    M(RasterPos3s,                                           void,          (Short)(x)(Short)(y)(Short)(z)) \
    M(RasterPos3sv,                                          void,          (const Short*)(v)) \
    M(RasterPos4d,                                           void,          (Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(RasterPos4dv,                                          void,          (const Double*)(v)) \
    M(RasterPos4f,                                           void,          (Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(RasterPos4fv,                                          void,          (const Float*)(v)) \
    M(RasterPos4i,                                           void,          (Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(RasterPos4iv,                                          void,          (const Int*)(v)) \
    M(RasterPos4s,                                           void,          (Short)(x)(Short)(y)(Short)(z)(Short)(w)) \
    M(RasterPos4sv,                                          void,          (const Short*)(v)) \
    M(ReadBuffer,                                            void,          (Enum)(mode)) \
    M(ReadPixels,                                            void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(void*)(pixels)) \
    M(Rectd,                                                 void,          (Double)(x1)(Double)(y1)(Double)(x2)(Double)(y2)) \
    M(Rectdv,                                                void,          (const Double*)(v1)(const Double*)(v2)) \
    M(Rectf,                                                 void,          (Float)(x1)(Float)(y1)(Float)(x2)(Float)(y2)) \
    M(Rectfv,                                                void,          (const Float*)(v1)(const Float*)(v2)) \
    M(Recti,                                                 void,          (Int)(x1)(Int)(y1)(Int)(x2)(Int)(y2)) \
    M(Rectiv,                                                void,          (const Int*)(v1)(const Int*)(v2)) \
    M(Rects,                                                 void,          (Short)(x1)(Short)(y1)(Short)(x2)(Short)(y2)) \
    M(Rectsv,                                                void,          (const Short*)(v1)(const Short*)(v2)) \
    M(RenderMode,                                            Int,           (Enum)(mode)) \
    M(Rotated,                                               void,          (Double)(angle)(Double)(x)(Double)(y)(Double)(z)) \
    M(Rotatef,                                               void,          (Float)(angle)(Float)(x)(Float)(y)(Float)(z)) \
    M(Scaled,                                                void,          (Double)(x)(Double)(y)(Double)(z)) \
    M(Scalef,                                                void,          (Float)(x)(Float)(y)(Float)(z)) \
    M(Scissor,                                               void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(SelectBuffer,                                          void,          (Isize)(size)(Uint*)(buffer)) \
    M(ShadeModel,                                            void,          (Enum)(mode)) \
    M(StencilFunc,                                           void,          (Enum)(func)(Int)(ref)(Uint)(mask)) \
    M(StencilMask,                                           void,          (Uint)(mask)) \
    M(StencilOp,                                             void,          (Enum)(fail)(Enum)(zfail)(Enum)(zpass)) \
    M(TexCoord1d,                                            void,          (Double)(s)) \
    M(TexCoord1dv,                                           void,          (const Double*)(v)) \
    M(TexCoord1f,                                            void,          (Float)(s)) \
    M(TexCoord1fv,                                           void,          (const Float*)(v)) \
    M(TexCoord1i,                                            void,          (Int)(s)) \
    M(TexCoord1iv,                                           void,          (const Int*)(v)) \
    M(TexCoord1s,                                            void,          (Short)(s)) \
    M(TexCoord1sv,                                           void,          (const Short*)(v)) \
    M(TexCoord2d,                                            void,          (Double)(s)(Double)(t)) \
    M(TexCoord2dv,                                           void,          (const Double*)(v)) \
    M(TexCoord2f,                                            void,          (Float)(s)(Float)(t)) \
    M(TexCoord2fv,                                           void,          (const Float*)(v)) \
    M(TexCoord2i,                                            void,          (Int)(s)(Int)(t)) \
    M(TexCoord2iv,                                           void,          (const Int*)(v)) \
    M(TexCoord2s,                                            void,          (Short)(s)(Short)(t)) \
    M(TexCoord2sv,                                           void,          (const Short*)(v)) \
    M(TexCoord3d,                                            void,          (Double)(s)(Double)(t)(Double)(r)) \
    M(TexCoord3dv,                                           void,          (const Double*)(v)) \
    M(TexCoord3f,                                            void,          (Float)(s)(Float)(t)(Float)(r)) \
    M(TexCoord3fv,                                           void,          (const Float*)(v)) \
    M(TexCoord3i,                                            void,          (Int)(s)(Int)(t)(Int)(r)) \
    M(TexCoord3iv,                                           void,          (const Int*)(v)) \
    M(TexCoord3s,                                            void,          (Short)(s)(Short)(t)(Short)(r)) \
    M(TexCoord3sv,                                           void,          (const Short*)(v)) \
    M(TexCoord4d,                                            void,          (Double)(s)(Double)(t)(Double)(r)(Double)(q)) \
    M(TexCoord4dv,                                           void,          (const Double*)(v)) \
    M(TexCoord4f,                                            void,          (Float)(s)(Float)(t)(Float)(r)(Float)(q)) \
    M(TexCoord4fv,                                           void,          (const Float*)(v)) \
    M(TexCoord4i,                                            void,          (Int)(s)(Int)(t)(Int)(r)(Int)(q)) \
    M(TexCoord4iv,                                           void,          (const Int*)(v)) \
    M(TexCoord4s,                                            void,          (Short)(s)(Short)(t)(Short)(r)(Short)(q)) \
    M(TexCoord4sv,                                           void,          (const Short*)(v)) \
    M(TexCoordPointer,                                       void,          (Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(TexEnvf,                                               void,          (Enum)(target)(Enum)(pname)(Float)(param)) \
    M(TexEnvfv,                                              void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(TexEnvi,                                               void,          (Enum)(target)(Enum)(pname)(Int)(param)) \
    M(TexEnviv,                                              void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(TexGend,                                               void,          (Enum)(coord)(Enum)(pname)(Double)(param)) \
    M(TexGendv,                                              void,          (Enum)(coord)(Enum)(pname)(const Double*)(params)) \
    M(TexGenf,                                               void,          (Enum)(coord)(Enum)(pname)(Float)(param)) \
    M(TexGenfv,                                              void,          (Enum)(coord)(Enum)(pname)(const Float*)(params)) \
    M(TexGeni,                                               void,          (Enum)(coord)(Enum)(pname)(Int)(param)) \
    M(TexGeniv,                                              void,          (Enum)(coord)(Enum)(pname)(const Int*)(params)) \
    M(TexImage1D,                                            void,          (Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexImage2D,                                            void,          (Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Isize)(height)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexParameterf,                                         void,          (Enum)(target)(Enum)(pname)(Float)(param)) \
    M(TexParameterfv,                                        void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(TexParameteri,                                         void,          (Enum)(target)(Enum)(pname)(Int)(param)) \
    M(TexParameteriv,                                        void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(TexSubImage1D,                                         void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexSubImage2D,                                         void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(Translated,                                            void,          (Double)(x)(Double)(y)(Double)(z)) \
    M(Translatef,                                            void,          (Float)(x)(Float)(y)(Float)(z)) \
    M(Vertex2d,                                              void,          (Double)(x)(Double)(y)) \
    M(Vertex2dv,                                             void,          (const Double*)(v)) \
    M(Vertex2f,                                              void,          (Float)(x)(Float)(y)) \
    M(Vertex2fv,                                             void,          (const Float*)(v)) \
    M(Vertex2i,                                              void,          (Int)(x)(Int)(y)) \
    M(Vertex2iv,                                             void,          (const Int*)(v)) \
    M(Vertex2s,                                              void,          (Short)(x)(Short)(y)) \
    M(Vertex2sv,                                             void,          (const Short*)(v)) \
    M(Vertex3d,                                              void,          (Double)(x)(Double)(y)(Double)(z)) \
    M(Vertex3dv,                                             void,          (const Double*)(v)) \
    M(Vertex3f,                                              void,          (Float)(x)(Float)(y)(Float)(z)) \
    M(Vertex3fv,                                             void,          (const Float*)(v)) \
    M(Vertex3i,                                              void,          (Int)(x)(Int)(y)(Int)(z)) \
    M(Vertex3iv,                                             void,          (const Int*)(v)) \
    M(Vertex3s,                                              void,          (Short)(x)(Short)(y)(Short)(z)) \
    M(Vertex3sv,                                             void,          (const Short*)(v)) \
    M(Vertex4d,                                              void,          (Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(Vertex4dv,                                             void,          (const Double*)(v)) \
    M(Vertex4f,                                              void,          (Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(Vertex4fv,                                             void,          (const Float*)(v)) \
    M(Vertex4i,                                              void,          (Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(Vertex4iv,                                             void,          (const Int*)(v)) \
    M(Vertex4s,                                              void,          (Short)(x)(Short)(y)(Short)(z)(Short)(w)) \
    M(Vertex4sv,                                             void,          (const Short*)(v)) \
    M(VertexPointer,                                         void,          (Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(Viewport,                                              void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CopyTexSubImage3D,                                     void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(DrawRangeElements,                                     void,          (Enum)(mode)(Uint)(start)(Uint)(end)(Isize)(count)(Enum)(type)(const void*)(indices)) \
    M(TexImage3D,                                            void,          (Enum)(target)(Int)(level)(Int)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexSubImage3D,                                         void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(ActiveTexture,                                         void,          (Enum)(texture)) \
    M(ClientActiveTexture,                                   void,          (Enum)(texture)) \
    M(CompressedTexImage1D,                                  void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexImage2D,                                  void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexImage3D,                                  void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexSubImage1D,                               void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexSubImage2D,                               void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexSubImage3D,                               void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(GetCompressedTexImage,                                 void,          (Enum)(target)(Int)(lod)(void*)(img)) \
    M(LoadTransposeMatrixd,                                  void,          (const Double*)(m)) \
    M(LoadTransposeMatrixf,                                  void,          (const Float*)(m)) \
    M(MultTransposeMatrixd,                                  void,          (const Double*)(m)) \
    M(MultTransposeMatrixf,                                  void,          (const Float*)(m)) \
    M(MultiTexCoord1d,                                       void,          (Enum)(target)(Double)(s)) \
    M(MultiTexCoord1dv,                                      void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord1f,                                       void,          (Enum)(target)(Float)(s)) \
    M(MultiTexCoord1fv,                                      void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord1i,                                       void,          (Enum)(target)(Int)(s)) \
    M(MultiTexCoord1iv,                                      void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord1s,                                       void,          (Enum)(target)(Short)(s)) \
    M(MultiTexCoord1sv,                                      void,          (Enum)(target)(const Short*)(v)) \
    M(MultiTexCoord2d,                                       void,          (Enum)(target)(Double)(s)(Double)(t)) \
    M(MultiTexCoord2dv,                                      void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord2f,                                       void,          (Enum)(target)(Float)(s)(Float)(t)) \
    M(MultiTexCoord2fv,                                      void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord2i,                                       void,          (Enum)(target)(Int)(s)(Int)(t)) \
    M(MultiTexCoord2iv,                                      void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord2s,                                       void,          (Enum)(target)(Short)(s)(Short)(t)) \
    M(MultiTexCoord2sv,                                      void,          (Enum)(target)(const Short*)(v)) \
    M(MultiTexCoord3d,                                       void,          (Enum)(target)(Double)(s)(Double)(t)(Double)(r)) \
    M(MultiTexCoord3dv,                                      void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord3f,                                       void,          (Enum)(target)(Float)(s)(Float)(t)(Float)(r)) \
    M(MultiTexCoord3fv,                                      void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord3i,                                       void,          (Enum)(target)(Int)(s)(Int)(t)(Int)(r)) \
    M(MultiTexCoord3iv,                                      void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord3s,                                       void,          (Enum)(target)(Short)(s)(Short)(t)(Short)(r)) \
    M(MultiTexCoord3sv,                                      void,          (Enum)(target)(const Short*)(v)) \
    M(MultiTexCoord4d,                                       void,          (Enum)(target)(Double)(s)(Double)(t)(Double)(r)(Double)(q)) \
    M(MultiTexCoord4dv,                                      void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord4f,                                       void,          (Enum)(target)(Float)(s)(Float)(t)(Float)(r)(Float)(q)) \
    M(MultiTexCoord4fv,                                      void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord4i,                                       void,          (Enum)(target)(Int)(s)(Int)(t)(Int)(r)(Int)(q)) \
    M(MultiTexCoord4iv,                                      void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord4s,                                       void,          (Enum)(target)(Short)(s)(Short)(t)(Short)(r)(Short)(q)) \
    M(MultiTexCoord4sv,                                      void,          (Enum)(target)(const Short*)(v)) \
    M(SampleCoverage,                                        void,          (FClamp)(value)(Bool)(invert)) \
    M(BlendColor,                                            void,          (FClamp)(red)(FClamp)(green)(FClamp)(blue)(FClamp)(alpha)) \
    M(BlendEquation,                                         void,          (Enum)(mode)) \
    M(BlendFuncSeparate,                                     void,          (Enum)(sfactorRGB)(Enum)(dfactorRGB)(Enum)(sfactorAlpha)(Enum)(dfactorAlpha)) \
    M(FogCoordPointer,                                       void,          (Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(FogCoordd,                                             void,          (Double)(coord)) \
    M(FogCoorddv,                                            void,          (const Double*)(coord)) \
    M(FogCoordf,                                             void,          (Float)(coord)) \
    M(FogCoordfv,                                            void,          (const Float*)(coord)) \
    M(MultiDrawArrays,                                       void,          (Enum)(mode)(const Int*)(first)(const Isize*)(count)(Isize)(drawcount)) \
    M(MultiDrawElements,                                     void,          (Enum)(mode)(const Isize*)(count)(Enum)(type)(const void *const*)(indices)(Isize)(drawcount)) \
    M(PointParameterf,                                       void,          (Enum)(pname)(Float)(param)) \
    M(PointParameterfv,                                      void,          (Enum)(pname)(const Float*)(params)) \
    M(PointParameteri,                                       void,          (Enum)(pname)(Int)(param)) \
    M(PointParameteriv,                                      void,          (Enum)(pname)(const Int*)(params)) \
    M(SecondaryColor3b,                                      void,          (Byte)(red)(Byte)(green)(Byte)(blue)) \
    M(SecondaryColor3bv,                                     void,          (const Byte*)(v)) \
    M(SecondaryColor3d,                                      void,          (Double)(red)(Double)(green)(Double)(blue)) \
    M(SecondaryColor3dv,                                     void,          (const Double*)(v)) \
    M(SecondaryColor3f,                                      void,          (Float)(red)(Float)(green)(Float)(blue)) \
    M(SecondaryColor3fv,                                     void,          (const Float*)(v)) \
    M(SecondaryColor3i,                                      void,          (Int)(red)(Int)(green)(Int)(blue)) \
    M(SecondaryColor3iv,                                     void,          (const Int*)(v)) \
    M(SecondaryColor3s,                                      void,          (Short)(red)(Short)(green)(Short)(blue)) \
    M(SecondaryColor3sv,                                     void,          (const Short*)(v)) \
    M(SecondaryColor3ub,                                     void,          (Ubyte)(red)(Ubyte)(green)(Ubyte)(blue)) \
    M(SecondaryColor3ubv,                                    void,          (const Ubyte*)(v)) \
    M(SecondaryColor3ui,                                     void,          (Uint)(red)(Uint)(green)(Uint)(blue)) \
    M(SecondaryColor3uiv,                                    void,          (const Uint*)(v)) \
    M(SecondaryColor3us,                                     void,          (Ushort)(red)(Ushort)(green)(Ushort)(blue)) \
    M(SecondaryColor3usv,                                    void,          (const Ushort*)(v)) \
    M(SecondaryColorPointer,                                 void,          (Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(WindowPos2d,                                           void,          (Double)(x)(Double)(y)) \
    M(WindowPos2dv,                                          void,          (const Double*)(p)) \
    M(WindowPos2f,                                           void,          (Float)(x)(Float)(y)) \
    M(WindowPos2fv,                                          void,          (const Float*)(p)) \
    M(WindowPos2i,                                           void,          (Int)(x)(Int)(y)) \
    M(WindowPos2iv,                                          void,          (const Int*)(p)) \
    M(WindowPos2s,                                           void,          (Short)(x)(Short)(y)) \
    M(WindowPos2sv,                                          void,          (const Short*)(p)) \
    M(WindowPos3d,                                           void,          (Double)(x)(Double)(y)(Double)(z)) \
    M(WindowPos3dv,                                          void,          (const Double*)(p)) \
    M(WindowPos3f,                                           void,          (Float)(x)(Float)(y)(Float)(z)) \
    M(WindowPos3fv,                                          void,          (const Float*)(p)) \
    M(WindowPos3i,                                           void,          (Int)(x)(Int)(y)(Int)(z)) \
    M(WindowPos3iv,                                          void,          (const Int*)(p)) \
    M(WindowPos3s,                                           void,          (Short)(x)(Short)(y)(Short)(z)) \
    M(WindowPos3sv,                                          void,          (const Short*)(p)) \
    M(BeginQuery,                                            void,          (Enum)(target)(Uint)(id)) \
    M(BindBuffer,                                            void,          (Enum)(target)(Uint)(buffer)) \
    M(BufferData,                                            void,          (Enum)(target)(IsizePtr)(size)(const void*)(data)(Enum)(usage)) \
    M(BufferSubData,                                         void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(size)(const void*)(data)) \
    M(DeleteBuffers,                                         void,          (Isize)(n)(const Uint*)(buffers)) \
    M(DeleteQueries,                                         void,          (Isize)(n)(const Uint*)(ids)) \
    M(EndQuery,                                              void,          (Enum)(target)) \
    M(GenBuffers,                                            void,          (Isize)(n)(Uint*)(buffers)) \
    M(GenQueries,                                            void,          (Isize)(n)(Uint*)(ids)) \
    M(GetBufferParameteriv,                                  void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetBufferPointerv,                                     void,          (Enum)(target)(Enum)(pname)(void**)(params)) \
    M(GetBufferSubData,                                      void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(size)(void*)(data)) \
    M(GetQueryObjectiv,                                      void,          (Uint)(id)(Enum)(pname)(Int*)(params)) \
    M(GetQueryObjectuiv,                                     void,          (Uint)(id)(Enum)(pname)(Uint*)(params)) \
    M(GetQueryiv,                                            void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(IsBuffer,                                              Bool,          (Uint)(buffer)) \
    M(IsQuery,                                               Bool,          (Uint)(id)) \
    M(MapBuffer,                                             void*,         (Enum)(target)(Enum)(access)) \
    M(UnmapBuffer,                                           Bool,          (Enum)(target)) \
    M(AttachShader,                                          void,          (Uint)(program)(Uint)(shader)) \
    M(BindAttribLocation,                                    void,          (Uint)(program)(Uint)(index)(const char*)(name)) \
    M(BlendEquationSeparate,                                 void,          (Enum)(modeRGB)(Enum)(modeAlpha)) \
    M(CompileShader,                                         void,          (Uint)(shader)) \
    M(CreateProgram,                                         Uint,          ) \
    M(CreateShader,                                          Uint,          (Enum)(type)) \
    M(DeleteProgram,                                         void,          (Uint)(program)) \
    M(DeleteShader,                                          void,          (Uint)(shader)) \
    M(DetachShader,                                          void,          (Uint)(program)(Uint)(shader)) \
    M(DisableVertexAttribArray,                              void,          (Uint)(index)) \
    M(DrawBuffers,                                           void,          (Isize)(n)(const Enum*)(bufs)) \
    M(EnableVertexAttribArray,                               void,          (Uint)(index)) \
    M(GetActiveAttrib,                                       void,          (Uint)(program)(Uint)(index)(Isize)(maxLength)(Isize*)(length)(Int*)(size)(Enum*)(type)(char*)(name)) \
    M(GetActiveUniform,                                      void,          (Uint)(program)(Uint)(index)(Isize)(maxLength)(Isize*)(length)(Int*)(size)(Enum*)(type)(char*)(name)) \
    M(GetAttachedShaders,                                    void,          (Uint)(program)(Isize)(maxCount)(Isize*)(count)(Uint*)(shaders)) \
    M(GetAttribLocation,                                     Int,           (Uint)(program)(const char*)(name)) \
    M(GetProgramInfoLog,                                     void,          (Uint)(program)(Isize)(bufSize)(Isize*)(length)(char*)(infoLog)) \
    M(GetProgramiv,                                          void,          (Uint)(program)(Enum)(pname)(Int*)(param)) \
    M(GetShaderInfoLog,                                      void,          (Uint)(shader)(Isize)(bufSize)(Isize*)(length)(char*)(infoLog)) \
    M(GetShaderSource,                                       void,          (Uint)(obj)(Isize)(maxLength)(Isize*)(length)(char*)(source)) \
    M(GetShaderiv,                                           void,          (Uint)(shader)(Enum)(pname)(Int*)(param)) \
    M(GetUniformLocation,                                    Int,           (Uint)(program)(const char*)(name)) \
    M(GetUniformfv,                                          void,          (Uint)(program)(Int)(location)(Float*)(params)) \
    M(GetUniformiv,                                          void,          (Uint)(program)(Int)(location)(Int*)(params)) \
    M(GetVertexAttribPointerv,                               void,          (Uint)(index)(Enum)(pname)(void**)(pointer)) \
    M(GetVertexAttribdv,                                     void,          (Uint)(index)(Enum)(pname)(Double*)(params)) \
    M(GetVertexAttribfv,                                     void,          (Uint)(index)(Enum)(pname)(Float*)(params)) \
    M(GetVertexAttribiv,                                     void,          (Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(IsProgram,                                             Bool,          (Uint)(program)) \
    M(IsShader,                                              Bool,          (Uint)(shader)) \
    M(LinkProgram,                                           void,          (Uint)(program)) \
    M(ShaderSource,                                          void,          (Uint)(shader)(Isize)(count)(const char *const*)(string)(const Int*)(length)) \
    M(StencilFuncSeparate,                                   void,          (Enum)(frontfunc)(Enum)(backfunc)(Int)(ref)(Uint)(mask)) \
    M(StencilMaskSeparate,                                   void,          (Enum)(face)(Uint)(mask)) \
    M(StencilOpSeparate,                                     void,          (Enum)(face)(Enum)(sfail)(Enum)(dpfail)(Enum)(dppass)) \
    M(Uniform1f,                                             void,          (Int)(location)(Float)(v0)) \
    M(Uniform1fv,                                            void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform1i,                                             void,          (Int)(location)(Int)(v0)) \
    M(Uniform1iv,                                            void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(Uniform2f,                                             void,          (Int)(location)(Float)(v0)(Float)(v1)) \
    M(Uniform2fv,                                            void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform2i,                                             void,          (Int)(location)(Int)(v0)(Int)(v1)) \
    M(Uniform2iv,                                            void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(Uniform3f,                                             void,          (Int)(location)(Float)(v0)(Float)(v1)(Float)(v2)) \
    M(Uniform3fv,                                            void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform3i,                                             void,          (Int)(location)(Int)(v0)(Int)(v1)(Int)(v2)) \
    M(Uniform3iv,                                            void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(Uniform4f,                                             void,          (Int)(location)(Float)(v0)(Float)(v1)(Float)(v2)(Float)(v3)) \
    M(Uniform4fv,                                            void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform4i,                                             void,          (Int)(location)(Int)(v0)(Int)(v1)(Int)(v2)(Int)(v3)) \
    M(Uniform4iv,                                            void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(UniformMatrix2fv,                                      void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix3fv,                                      void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix4fv,                                      void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UseProgram,                                            void,          (Uint)(program)) \
    M(ValidateProgram,                                       void,          (Uint)(program)) \
    M(VertexAttrib1d,                                        void,          (Uint)(index)(Double)(x)) \
    M(VertexAttrib1dv,                                       void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib1f,                                        void,          (Uint)(index)(Float)(x)) \
    M(VertexAttrib1fv,                                       void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib1s,                                        void,          (Uint)(index)(Short)(x)) \
    M(VertexAttrib1sv,                                       void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib2d,                                        void,          (Uint)(index)(Double)(x)(Double)(y)) \
    M(VertexAttrib2dv,                                       void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib2f,                                        void,          (Uint)(index)(Float)(x)(Float)(y)) \
    M(VertexAttrib2fv,                                       void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib2s,                                        void,          (Uint)(index)(Short)(x)(Short)(y)) \
    M(VertexAttrib2sv,                                       void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib3d,                                        void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)) \
    M(VertexAttrib3dv,                                       void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib3f,                                        void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(z)) \
    M(VertexAttrib3fv,                                       void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib3s,                                        void,          (Uint)(index)(Short)(x)(Short)(y)(Short)(z)) \
    M(VertexAttrib3sv,                                       void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4Nbv,                                      void,          (Uint)(index)(const Byte*)(v)) \
    M(VertexAttrib4Niv,                                      void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttrib4Nsv,                                      void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4Nub,                                      void,          (Uint)(index)(Ubyte)(x)(Ubyte)(y)(Ubyte)(z)(Ubyte)(w)) \
    M(VertexAttrib4Nubv,                                     void,          (Uint)(index)(const Ubyte*)(v)) \
    M(VertexAttrib4Nuiv,                                     void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttrib4Nusv,                                     void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttrib4bv,                                       void,          (Uint)(index)(const Byte*)(v)) \
    M(VertexAttrib4d,                                        void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(VertexAttrib4dv,                                       void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib4f,                                        void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(VertexAttrib4fv,                                       void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib4iv,                                       void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttrib4s,                                        void,          (Uint)(index)(Short)(x)(Short)(y)(Short)(z)(Short)(w)) \
    M(VertexAttrib4sv,                                       void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4ubv,                                      void,          (Uint)(index)(const Ubyte*)(v)) \
    M(VertexAttrib4uiv,                                      void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttrib4usv,                                      void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttribPointer,                                   void,          (Uint)(index)(Int)(size)(Enum)(type)(Bool)(normalized)(Isize)(stride)(const void*)(pointer)) \
    M(UniformMatrix2x3fv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix2x4fv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix3x2fv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix3x4fv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix4x2fv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix4x3fv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(BeginConditionalRender,                                void,          (Uint)(id)(Enum)(mode)) \
    M(BeginTransformFeedback,                                void,          (Enum)(primitiveMode)) \
    M(BindFragDataLocation,                                  void,          (Uint)(program)(Uint)(colorNumber)(const char*)(name)) \
    M(ClampColor,                                            void,          (Enum)(target)(Enum)(clamp)) \
    M(ClearBufferfi,                                         void,          (Enum)(buffer)(Int)(drawBuffer)(Float)(depth)(Int)(stencil)) \
    M(ClearBufferfv,                                         void,          (Enum)(buffer)(Int)(drawBuffer)(const Float*)(value)) \
    M(ClearBufferiv,                                         void,          (Enum)(buffer)(Int)(drawBuffer)(const Int*)(value)) \
    M(ClearBufferuiv,                                        void,          (Enum)(buffer)(Int)(drawBuffer)(const Uint*)(value)) \
    M(ColorMaski,                                            void,          (Uint)(buf)(Bool)(red)(Bool)(green)(Bool)(blue)(Bool)(alpha)) \
    M(Disablei,                                              void,          (Enum)(cap)(Uint)(index)) \
    M(Enablei,                                               void,          (Enum)(cap)(Uint)(index)) \
    M(EndConditionalRender,                                  void,          ) \
    M(EndTransformFeedback,                                  void,          ) \
    M(GetBooleani_v,                                         void,          (Enum)(pname)(Uint)(index)(Bool*)(data)) \
    M(GetFragDataLocation,                                   Int,           (Uint)(program)(const char*)(name)) \
    M(GetStringi,                                            const Ubyte*,  (Enum)(name)(Uint)(index)) \
    M(GetTexParameterIiv,                                    void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetTexParameterIuiv,                                   void,          (Enum)(target)(Enum)(pname)(Uint*)(params)) \
    M(GetTransformFeedbackVarying,                           void,          (Uint)(program)(Uint)(index)(Isize)(bufSize)(Isize *)(length)(Isize *)(size)(Enum *)(type)(char *)(name)) \
    M(GetUniformuiv,                                         void,          (Uint)(program)(Int)(location)(Uint*)(params)) \
    M(GetVertexAttribIiv,                                    void,          (Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(GetVertexAttribIuiv,                                   void,          (Uint)(index)(Enum)(pname)(Uint*)(params)) \
    M(IsEnabledi,                                            Bool,          (Enum)(cap)(Uint)(index)) \
    M(TexParameterIiv,                                       void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(TexParameterIuiv,                                      void,          (Enum)(target)(Enum)(pname)(const Uint*)(params)) \
    M(TransformFeedbackVaryings,                             void,          (Uint)(program)(Isize)(count)(const char *const*)(varyings)(Enum)(bufferMode)) \
    M(Uniform1ui,                                            void,          (Int)(location)(Uint)(v0)) \
    M(Uniform1uiv,                                           void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(Uniform2ui,                                            void,          (Int)(location)(Uint)(v0)(Uint)(v1)) \
    M(Uniform2uiv,                                           void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(Uniform3ui,                                            void,          (Int)(location)(Uint)(v0)(Uint)(v1)(Uint)(v2)) \
    M(Uniform3uiv,                                           void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(Uniform4ui,                                            void,          (Int)(location)(Uint)(v0)(Uint)(v1)(Uint)(v2)(Uint)(v3)) \
    M(Uniform4uiv,                                           void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(VertexAttribI1i,                                       void,          (Uint)(index)(Int)(v0)) \
    M(VertexAttribI1iv,                                      void,          (Uint)(index)(const Int*)(v0)) \
    M(VertexAttribI1ui,                                      void,          (Uint)(index)(Uint)(v0)) \
    M(VertexAttribI1uiv,                                     void,          (Uint)(index)(const Uint*)(v0)) \
    M(VertexAttribI2i,                                       void,          (Uint)(index)(Int)(v0)(Int)(v1)) \
    M(VertexAttribI2iv,                                      void,          (Uint)(index)(const Int*)(v0)) \
    M(VertexAttribI2ui,                                      void,          (Uint)(index)(Uint)(v0)(Uint)(v1)) \
    M(VertexAttribI2uiv,                                     void,          (Uint)(index)(const Uint*)(v0)) \
    M(VertexAttribI3i,                                       void,          (Uint)(index)(Int)(v0)(Int)(v1)(Int)(v2)) \
    M(VertexAttribI3iv,                                      void,          (Uint)(index)(const Int*)(v0)) \
    M(VertexAttribI3ui,                                      void,          (Uint)(index)(Uint)(v0)(Uint)(v1)(Uint)(v2)) \
    M(VertexAttribI3uiv,                                     void,          (Uint)(index)(const Uint*)(v0)) \
    M(VertexAttribI4bv,                                      void,          (Uint)(index)(const Byte*)(v0)) \
    M(VertexAttribI4i,                                       void,          (Uint)(index)(Int)(v0)(Int)(v1)(Int)(v2)(Int)(v3)) \
    M(VertexAttribI4iv,                                      void,          (Uint)(index)(const Int*)(v0)) \
    M(VertexAttribI4sv,                                      void,          (Uint)(index)(const Short*)(v0)) \
    M(VertexAttribI4ubv,                                     void,          (Uint)(index)(const Ubyte*)(v0)) \
    M(VertexAttribI4ui,                                      void,          (Uint)(index)(Uint)(v0)(Uint)(v1)(Uint)(v2)(Uint)(v3)) \
    M(VertexAttribI4uiv,                                     void,          (Uint)(index)(const Uint*)(v0)) \
    M(VertexAttribI4usv,                                     void,          (Uint)(index)(const Ushort*)(v0)) \
    M(VertexAttribIPointer,                                  void,          (Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(DrawArraysInstanced,                                   void,          (Enum)(mode)(Int)(first)(Isize)(count)(Isize)(primcount)) \
    M(DrawElementsInstanced,                                 void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)) \
    M(PrimitiveRestartIndex,                                 void,          (Uint)(buffer)) \
    M(TexBuffer,                                             void,          (Enum)(target)(Enum)(internalFormat)(Uint)(buffer)) \
    M(FramebufferTexture,                                    void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)) \
    M(GetBufferParameteri64v,                                void,          (Enum)(target)(Enum)(value)(Int64 *)(data)) \
    M(GetInteger64i_v,                                       void,          (Enum)(pname)(Uint)(index)(Int64 *)(data)) \
    M(VertexAttribDivisor,                                   void,          (Uint)(index)(Uint)(divisor)) \
    M(BlendEquationSeparatei,                                void,          (Uint)(buf)(Enum)(modeRGB)(Enum)(modeAlpha)) \
    M(BlendEquationi,                                        void,          (Uint)(buf)(Enum)(mode)) \
    M(BlendFuncSeparatei,                                    void,          (Uint)(buf)(Enum)(srcRGB)(Enum)(dstRGB)(Enum)(srcAlpha)(Enum)(dstAlpha)) \
    M(BlendFunci,                                            void,          (Uint)(buf)(Enum)(src)(Enum)(dst)) \
    M(MinSampleShading,                                      void,          (FClamp)(value)) \
    M(GetGraphicsResetStatus,                                Enum,          ) \
    M(GetnCompressedTexImage,                                void,          (Enum)(target)(Int)(lod)(Isize)(bufSize)(void*)(pixels)) \
    M(GetnTexImage,                                          void,          (Enum)(tex)(Int)(level)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(pixels)) \
    M(GetnUniformdv,                                         void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Double*)(params)) \
    M(MultiDrawArraysIndirectCount,                          void,          (Enum)(mode)(const void*)(indirect)(IntPtr)(drawcount)(Isize)(maxdrawcount)(Isize)(stride)) \
    M(MultiDrawElementsIndirectCount,                        void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)(IntPtr)(drawcount)(Isize)(maxdrawcount)(Isize)(stride)) \
    M(SpecializeShader,                                      void,          (Uint)(shader)(const char*)(pEntryPoint)(Uint)(numSpecializationConstants)(const Uint*)(pConstantIndex)(const Uint*)(pConstantValue)) \
    M(TbufferMask3DFX,                                       void,          (Uint)(mask)) \
    M(DebugMessageCallbackAMD,                               void,          (LogFuncAMD)(callback)(void*)(userParam)) \
    M(DebugMessageEnableAMD,                                 void,          (Enum)(category)(Enum)(severity)(Isize)(count)(const Uint*)(ids)(Bool)(enabled)) \
    M(DebugMessageInsertAMD,                                 void,          (Enum)(category)(Enum)(severity)(Uint)(id)(Isize)(length)(const char*)(buf)) \
    M(GetDebugMessageLogAMD,                                 Uint,          (Uint)(count)(Isize)(bufsize)(Enum*)(categories)(Uint*)(severities)(Uint*)(ids)(Isize*)(lengths)(char*)(message)) \
    M(BlendEquationIndexedAMD,                               void,          (Uint)(buf)(Enum)(mode)) \
    M(BlendEquationSeparateIndexedAMD,                       void,          (Uint)(buf)(Enum)(modeRGB)(Enum)(modeAlpha)) \
    M(BlendFuncIndexedAMD,                                   void,          (Uint)(buf)(Enum)(src)(Enum)(dst)) \
    M(BlendFuncSeparateIndexedAMD,                           void,          (Uint)(buf)(Enum)(srcRGB)(Enum)(dstRGB)(Enum)(srcAlpha)(Enum)(dstAlpha)) \
    M(FramebufferSamplePositionsfvAMD,                       void,          (Enum)(target)(Uint)(numsamples)(Uint)(pixelindex)(const Float*)(values)) \
    M(GetFramebufferParameterfvAMD,                          void,          (Enum)(target)(Enum)(pname)(Uint)(numsamples)(Uint)(pixelindex)(Isize)(size)(Float*)(values)) \
    M(GetNamedFramebufferParameterfvAMD,                     void,          (Uint)(framebuffer)(Enum)(pname)(Uint)(numsamples)(Uint)(pixelindex)(Isize)(size)(Float*)(values)) \
    M(NamedFramebufferSamplePositionsfvAMD,                  void,          (Uint)(framebuffer)(Uint)(numsamples)(Uint)(pixelindex)(const Float*)(values)) \
    M(VertexAttribParameteriAMD,                             void,          (Uint)(index)(Enum)(pname)(Int)(param)) \
    M(MultiDrawArraysIndirectAMD,                            void,          (Enum)(mode)(const void*)(indirect)(Isize)(primcount)(Isize)(stride)) \
    M(MultiDrawElementsIndirectAMD,                          void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)(Isize)(primcount)(Isize)(stride)) \
    M(DeleteNamesAMD,                                        void,          (Enum)(identifier)(Uint)(num)(const Uint*)(names)) \
    M(GenNamesAMD,                                           void,          (Enum)(identifier)(Uint)(num)(Uint*)(names)) \
    M(IsNameAMD,                                             Bool,          (Enum)(identifier)(Uint)(name)) \
    M(QueryObjectParameteruiAMD,                             void,          (Enum)(target)(Uint)(id)(Enum)(pname)(Uint)(param)) \
    M(BeginPerfMonitorAMD,                                   void,          (Uint)(monitor)) \
    M(DeletePerfMonitorsAMD,                                 void,          (Isize)(n)(Uint*)(monitors)) \
    M(EndPerfMonitorAMD,                                     void,          (Uint)(monitor)) \
    M(GenPerfMonitorsAMD,                                    void,          (Isize)(n)(Uint*)(monitors)) \
    M(GetPerfMonitorCounterDataAMD,                          void,          (Uint)(monitor)(Enum)(pname)(Isize)(dataSize)(Uint*)(data)(Int*)(bytesWritten)) \
    M(GetPerfMonitorCounterInfoAMD,                          void,          (Uint)(group)(Uint)(counter)(Enum)(pname)(void*)(data)) \
    M(GetPerfMonitorCounterStringAMD,                        void,          (Uint)(group)(Uint)(counter)(Isize)(bufSize)(Isize*)(length)(char*)(counterString)) \
    M(GetPerfMonitorCountersAMD,                             void,          (Uint)(group)(Int*)(numCounters)(Int*)(maxActiveCounters)(Isize)(countersSize)(Uint*)(counters)) \
    M(GetPerfMonitorGroupStringAMD,                          void,          (Uint)(group)(Isize)(bufSize)(Isize*)(length)(char*)(groupString)) \
    M(GetPerfMonitorGroupsAMD,                               void,          (Int*)(numGroups)(Isize)(groupsSize)(Uint*)(groups)) \
    M(SelectPerfMonitorCountersAMD,                          void,          (Uint)(monitor)(Bool)(enable)(Uint)(group)(Int)(numCounters)(Uint*)(counterList)) \
    M(SetMultisamplefvAMD,                                   void,          (Enum)(pname)(Uint)(index)(const Float*)(val)) \
    M(TexStorageSparseAMD,                                   void,          (Enum)(target)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Isize)(layers)(Bitfield)(flags)) \
    M(TextureStorageSparseAMD,                               void,          (Uint)(texture)(Enum)(target)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Isize)(layers)(Bitfield)(flags)) \
    M(StencilOpValueAMD,                                     void,          (Enum)(face)(Uint)(value)) \
    M(TessellationFactorAMD,                                 void,          (Float)(factor)) \
    M(TessellationModeAMD,                                   void,          (Enum)(mode)) \
    M(BlitFramebufferANGLE,                                  void,          (Int)(srcX0)(Int)(srcY0)(Int)(srcX1)(Int)(srcY1)(Int)(dstX0)(Int)(dstY0)(Int)(dstX1)(Int)(dstY1)(Bitfield)(mask)(Enum)(filter)) \
    M(RenderbufferStorageMultisampleANGLE,                   void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(DrawArraysInstancedANGLE,                              void,          (Enum)(mode)(Int)(first)(Isize)(count)(Isize)(primcount)) \
    M(DrawElementsInstancedANGLE,                            void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)) \
    M(VertexAttribDivisorANGLE,                              void,          (Uint)(index)(Uint)(divisor)) \
    M(BeginQueryANGLE,                                       void,          (Enum)(target)(Uint)(id)) \
    M(DeleteQueriesANGLE,                                    void,          (Isize)(n)(const Uint*)(ids)) \
    M(EndQueryANGLE,                                         void,          (Enum)(target)) \
    M(GenQueriesANGLE,                                       void,          (Isize)(n)(Uint*)(ids)) \
    M(GetQueryObjecti64vANGLE,                               void,          (Uint)(id)(Enum)(pname)(Int64*)(params)) \
    M(GetQueryObjectivANGLE,                                 void,          (Uint)(id)(Enum)(pname)(Int*)(params)) \
    M(GetQueryObjectui64vANGLE,                              void,          (Uint)(id)(Enum)(pname)(Uint64*)(params)) \
    M(GetQueryObjectuivANGLE,                                void,          (Uint)(id)(Enum)(pname)(Uint*)(params)) \
    M(GetQueryivANGLE,                                       void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(IsQueryANGLE,                                          Bool,          (Uint)(id)) \
    M(QueryCounterANGLE,                                     void,          (Uint)(id)(Enum)(target)) \
    M(GetTranslatedShaderSourceANGLE,                        void,          (Uint)(shader)(Isize)(bufsize)(Isize*)(length)(char*)(source)) \
    M(CopyTextureLevelsAPPLE,                                void,          (Uint)(destinationTexture)(Uint)(sourceTexture)(Int)(sourceBaseLevel)(Isize)(sourceLevelCount)) \
    M(DrawElementArrayAPPLE,                                 void,          (Enum)(mode)(Int)(first)(Isize)(count)) \
    M(DrawRangeElementArrayAPPLE,                            void,          (Enum)(mode)(Uint)(start)(Uint)(end)(Int)(first)(Isize)(count)) \
    M(ElementPointerAPPLE,                                   void,          (Enum)(type)(const void*)(pointer)) \
    M(MultiDrawElementArrayAPPLE,                            void,          (Enum)(mode)(const Int*)(first)(const Isize*)(count)(Isize)(primcount)) \
    M(MultiDrawRangeElementArrayAPPLE,                       void,          (Enum)(mode)(Uint)(start)(Uint)(end)(const Int*)(first)(const Isize*)(count)(Isize)(primcount)) \
    M(DeleteFencesAPPLE,                                     void,          (Isize)(n)(const Uint*)(fences)) \
    M(FinishFenceAPPLE,                                      void,          (Uint)(fence)) \
    M(FinishObjectAPPLE,                                     void,          (Enum)(object)(Int)(name)) \
    M(GenFencesAPPLE,                                        void,          (Isize)(n)(Uint*)(fences)) \
    M(IsFenceAPPLE,                                          Bool,          (Uint)(fence)) \
    M(SetFenceAPPLE,                                         void,          (Uint)(fence)) \
    M(TestFenceAPPLE,                                        Bool,          (Uint)(fence)) \
    M(TestObjectAPPLE,                                       Bool,          (Enum)(object)(Uint)(name)) \
    M(BufferParameteriAPPLE,                                 void,          (Enum)(target)(Enum)(pname)(Int)(param)) \
    M(FlushMappedBufferRangeAPPLE,                           void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(size)) \
    M(RenderbufferStorageMultisampleAPPLE,                   void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(ResolveMultisampleFramebufferAPPLE,                    void,          ) \
    M(GetObjectParameterivAPPLE,                             void,          (Enum)(objectType)(Uint)(name)(Enum)(pname)(Int*)(params)) \
    M(ObjectPurgeableAPPLE,                                  Enum,          (Enum)(objectType)(Uint)(name)(Enum)(option)) \
    M(ObjectUnpurgeableAPPLE,                                Enum,          (Enum)(objectType)(Uint)(name)(Enum)(option)) \
    M(ClientWaitSyncAPPLE,                                   Enum,          (Sync)(sync)(Bitfield)(flags)(Uint64)(timeout)) \
    M(DeleteSyncAPPLE,                                       void,          (Sync)(sync)) \
    M(FenceSyncAPPLE,                                        Sync,          (Enum)(condition)(Bitfield)(flags)) \
    M(GetInteger64vAPPLE,                                    void,          (Enum)(pname)(Int64*)(params)) \
    M(GetSyncivAPPLE,                                        void,          (Sync)(sync)(Enum)(pname)(Isize)(bufSize)(Isize*)(length)(Int*)(values)) \
    M(IsSyncAPPLE,                                           Bool,          (Sync)(sync)) \
    M(WaitSyncAPPLE,                                         void,          (Sync)(sync)(Bitfield)(flags)(Uint64)(timeout)) \
    M(GetTexParameterPointervAPPLE,                          void,          (Enum)(target)(Enum)(pname)(void**)(params)) \
    M(TextureRangeAPPLE,                                     void,          (Enum)(target)(Isize)(length)(void*)(pointer)) \
    M(BindVertexArrayAPPLE,                                  void,          (Uint)(array)) \
    M(DeleteVertexArraysAPPLE,                               void,          (Isize)(n)(const Uint*)(arrays)) \
    M(GenVertexArraysAPPLE,                                  void,          (Isize)(n)(const Uint*)(arrays)) \
    M(IsVertexArrayAPPLE,                                    Bool,          (Uint)(array)) \
    M(FlushVertexArrayRangeAPPLE,                            void,          (Isize)(length)(void*)(pointer)) \
    M(VertexArrayParameteriAPPLE,                            void,          (Enum)(pname)(Int)(param)) \
    M(VertexArrayRangeAPPLE,                                 void,          (Isize)(length)(void*)(pointer)) \
    M(DisableVertexAttribAPPLE,                              void,          (Uint)(index)(Enum)(pname)) \
    M(EnableVertexAttribAPPLE,                               void,          (Uint)(index)(Enum)(pname)) \
    M(IsVertexAttribEnabledAPPLE,                            Bool,          (Uint)(index)(Enum)(pname)) \
    M(MapVertexAttrib1dAPPLE,                                void,          (Uint)(index)(Uint)(size)(Double)(u1)(Double)(u2)(Int)(stride)(Int)(order)(const Double*)(points)) \
    M(MapVertexAttrib1fAPPLE,                                void,          (Uint)(index)(Uint)(size)(Float)(u1)(Float)(u2)(Int)(stride)(Int)(order)(const Float*)(points)) \
    M(MapVertexAttrib2dAPPLE,                                void,          (Uint)(index)(Uint)(size)(Double)(u1)(Double)(u2)(Int)(ustride)(Int)(uorder)(Double)(v1)(Double)(v2)(Int)(vstride)(Int)(vorder)(const Double*)(points)) \
    M(MapVertexAttrib2fAPPLE,                                void,          (Uint)(index)(Uint)(size)(Float)(u1)(Float)(u2)(Int)(ustride)(Int)(uorder)(Float)(v1)(Float)(v2)(Int)(vstride)(Int)(vorder)(const Float*)(points)) \
    M(ClearDepthf,                                           void,          (FClamp)(d)) \
    M(DepthRangef,                                           void,          (FClamp)(n)(FClamp)(f)) \
    M(GetShaderPrecisionFormat,                              void,          (Enum)(shadertype)(Enum)(precisiontype)(Int*)(range)(Int*)(precision)) \
    M(ReleaseShaderCompiler,                                 void,          ) \
    M(ShaderBinary,                                          void,          (Isize)(count)(const Uint*)(shaders)(Enum)(binaryformat)(const void*)(binary)(Isize)(length)) \
    M(MemoryBarrierByRegion,                                 void,          (Bitfield)(barriers)) \
    M(PrimitiveBoundingBoxARB,                               void,          (Float)(minX)(Float)(minY)(Float)(minZ)(Float)(minW)(Float)(maxX)(Float)(maxY)(Float)(maxZ)(Float)(maxW)) \
    M(DrawArraysInstancedBaseInstance,                       void,          (Enum)(mode)(Int)(first)(Isize)(count)(Isize)(primcount)(Uint)(baseinstance)) \
    M(DrawElementsInstancedBaseInstance,                     void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)(Uint)(baseinstance)) \
    M(DrawElementsInstancedBaseVertexBaseInstance,           void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)(Int)(basevertex)(Uint)(baseinstance)) \
    M(GetImageHandleARB,                                     Uint64,        (Uint)(texture)(Int)(level)(Bool)(layered)(Int)(layer)(Enum)(format)) \
    M(GetTextureHandleARB,                                   Uint64,        (Uint)(texture)) \
    M(GetTextureSamplerHandleARB,                            Uint64,        (Uint)(texture)(Uint)(sampler)) \
    M(GetVertexAttribLui64vARB,                              void,          (Uint)(index)(Enum)(pname)(Uint64*)(params)) \
    M(IsImageHandleResidentARB,                              Bool,          (Uint64)(handle)) \
    M(IsTextureHandleResidentARB,                            Bool,          (Uint64)(handle)) \
    M(MakeImageHandleNonResidentARB,                         void,          (Uint64)(handle)) \
    M(MakeImageHandleResidentARB,                            void,          (Uint64)(handle)(Enum)(access)) \
    M(MakeTextureHandleNonResidentARB,                       void,          (Uint64)(handle)) \
    M(MakeTextureHandleResidentARB,                          void,          (Uint64)(handle)) \
    M(ProgramUniformHandleui64ARB,                           void,          (Uint)(program)(Int)(location)(Uint64)(value)) \
    M(ProgramUniformHandleui64vARB,                          void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(values)) \
    M(UniformHandleui64ARB,                                  void,          (Int)(location)(Uint64)(value)) \
    M(UniformHandleui64vARB,                                 void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(VertexAttribL1ui64ARB,                                 void,          (Uint)(index)(Uint64)(x)) \
    M(VertexAttribL1ui64vARB,                                void,          (Uint)(index)(const Uint64*)(v)) \
    M(BindFragDataLocationIndexed,                           void,          (Uint)(program)(Uint)(colorNumber)(Uint)(index)(const char *)(name)) \
    M(GetFragDataIndex,                                      Int,           (Uint)(program)(const char *)(name)) \
    M(BufferStorage,                                         void,          (Enum)(target)(IsizePtr)(size)(const void*)(data)(Bitfield)(flags)) \
    M(CreateSyncFromCLeventARB,                              Sync,          (CLContext)(context)(CLEvent)(event)(Bitfield)(flags)) \
    M(ClearBufferData,                                       void,          (Enum)(target)(Enum)(internalformat)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearBufferSubData,                                    void,          (Enum)(target)(Enum)(internalformat)(IntPtr)(offset)(IsizePtr)(size)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearNamedBufferDataEXT,                               void,          (Uint)(buffer)(Enum)(internalformat)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearNamedBufferSubDataEXT,                            void,          (Uint)(buffer)(Enum)(internalformat)(IntPtr)(offset)(IsizePtr)(size)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearTexImage,                                         void,          (Uint)(texture)(Int)(level)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearTexSubImage,                                      void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClipControl,                                           void,          (Enum)(origin)(Enum)(depth)) \
    M(ClampColorARB,                                         void,          (Enum)(target)(Enum)(clamp)) \
    M(DispatchCompute,                                       void,          (Uint)(num_groups_x)(Uint)(num_groups_y)(Uint)(num_groups_z)) \
    M(DispatchComputeIndirect,                               void,          (IntPtr)(indirect)) \
    M(DispatchComputeGroupSizeARB,                           void,          (Uint)(num_groups_x)(Uint)(num_groups_y)(Uint)(num_groups_z)(Uint)(group_size_x)(Uint)(group_size_y)(Uint)(group_size_z)) \
    M(CopyBufferSubData,                                     void,          (Enum)(readtarget)(Enum)(writetarget)(IntPtr)(readoffset)(IntPtr)(writeoffset)(IsizePtr)(size)) \
    M(CopyImageSubData,                                      void,          (Uint)(srcName)(Enum)(srcTarget)(Int)(srcLevel)(Int)(srcX)(Int)(srcY)(Int)(srcZ)(Uint)(dstName)(Enum)(dstTarget)(Int)(dstLevel)(Int)(dstX)(Int)(dstY)(Int)(dstZ)(Isize)(srcWidth)(Isize)(srcHeight)(Isize)(srcDepth)) \
    M(DebugMessageCallbackARB,                               void,          (LogFunc)(callback)(const void*)(userParam)) \
    M(DebugMessageControlARB,                                void,          (Enum)(source)(Enum)(type)(Enum)(severity)(Isize)(count)(const Uint*)(ids)(Bool)(enabled)) \
    M(DebugMessageInsertARB,                                 void,          (Enum)(source)(Enum)(type)(Uint)(id)(Enum)(severity)(Isize)(length)(const char*)(buf)) \
    M(GetDebugMessageLogARB,                                 Uint,          (Uint)(count)(Isize)(bufSize)(Enum*)(sources)(Enum*)(types)(Uint*)(ids)(Enum*)(severities)(Isize*)(lengths)(char*)(messageLog)) \
    M(BindTextureUnit,                                       void,          (Uint)(unit)(Uint)(texture)) \
    M(BlitNamedFramebuffer,                                  void,          (Uint)(readFramebuffer)(Uint)(drawFramebuffer)(Int)(srcX0)(Int)(srcY0)(Int)(srcX1)(Int)(srcY1)(Int)(dstX0)(Int)(dstY0)(Int)(dstX1)(Int)(dstY1)(Bitfield)(mask)(Enum)(filter)) \
    M(CheckNamedFramebufferStatus,                           Enum,          (Uint)(framebuffer)(Enum)(target)) \
    M(ClearNamedBufferData,                                  void,          (Uint)(buffer)(Enum)(internalformat)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearNamedBufferSubData,                               void,          (Uint)(buffer)(Enum)(internalformat)(IntPtr)(offset)(IsizePtr)(size)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearNamedFramebufferfi,                               void,          (Uint)(framebuffer)(Enum)(buffer)(Int)(drawbuffer)(Float)(depth)(Int)(stencil)) \
    M(ClearNamedFramebufferfv,                               void,          (Uint)(framebuffer)(Enum)(buffer)(Int)(drawbuffer)(Float*)(value)) \
    M(ClearNamedFramebufferiv,                               void,          (Uint)(framebuffer)(Enum)(buffer)(Int)(drawbuffer)(const Int*)(value)) \
    M(ClearNamedFramebufferuiv,                              void,          (Uint)(framebuffer)(Enum)(buffer)(Int)(drawbuffer)(const Uint*)(value)) \
    M(CompressedTextureSubImage1D,                           void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureSubImage2D,                           void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureSubImage3D,                           void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CopyNamedBufferSubData,                                void,          (Uint)(readBuffer)(Uint)(writeBuffer)(IntPtr)(readOffset)(IntPtr)(writeOffset)(IsizePtr)(size)) \
    M(CopyTextureSubImage1D,                                 void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyTextureSubImage2D,                                 void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CopyTextureSubImage3D,                                 void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CreateBuffers,                                         void,          (Isize)(n)(Uint*)(buffers)) \
    M(CreateFramebuffers,                                    void,          (Isize)(n)(Uint*)(framebuffers)) \
    M(CreateProgramPipelines,                                void,          (Isize)(n)(Uint*)(pipelines)) \
    M(CreateQueries,                                         void,          (Enum)(target)(Isize)(n)(Uint*)(ids)) \
    M(CreateRenderbuffers,                                   void,          (Isize)(n)(Uint*)(renderbuffers)) \
    M(CreateSamplers,                                        void,          (Isize)(n)(Uint*)(samplers)) \
    M(CreateTextures,                                        void,          (Enum)(target)(Isize)(n)(Uint*)(textures)) \
    M(CreateTransformFeedbacks,                              void,          (Isize)(n)(Uint*)(ids)) \
    M(CreateVertexArrays,                                    void,          (Isize)(n)(Uint*)(arrays)) \
    M(DisableVertexArrayAttrib,                              void,          (Uint)(vaobj)(Uint)(index)) \
    M(EnableVertexArrayAttrib,                               void,          (Uint)(vaobj)(Uint)(index)) \
    M(FlushMappedNamedBufferRange,                           void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(length)) \
    M(GenerateTextureMipmap,                                 void,          (Uint)(texture)) \
    M(GetCompressedTextureImage,                             void,          (Uint)(texture)(Int)(level)(Isize)(bufSize)(void*)(pixels)) \
    M(GetNamedBufferParameteri64v,                           void,          (Uint)(buffer)(Enum)(pname)(Int64*)(params)) \
    M(GetNamedBufferParameteriv,                             void,          (Uint)(buffer)(Enum)(pname)(Int*)(params)) \
    M(GetNamedBufferPointerv,                                void,          (Uint)(buffer)(Enum)(pname)(void**)(params)) \
    M(GetNamedBufferSubData,                                 void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)(void*)(data)) \
    M(GetNamedFramebufferAttachmentParameteriv,              void,          (Uint)(framebuffer)(Enum)(attachment)(Enum)(pname)(Int*)(params)) \
    M(GetNamedFramebufferParameteriv,                        void,          (Uint)(framebuffer)(Enum)(pname)(Int*)(param)) \
    M(GetNamedRenderbufferParameteriv,                       void,          (Uint)(renderbuffer)(Enum)(pname)(Int*)(params)) \
    M(GetQueryBufferObjecti64v,                              void,          (Uint)(id)(Uint)(buffer)(Enum)(pname)(IntPtr)(offset)) \
    M(GetQueryBufferObjectiv,                                void,          (Uint)(id)(Uint)(buffer)(Enum)(pname)(IntPtr)(offset)) \
    M(GetQueryBufferObjectui64v,                             void,          (Uint)(id)(Uint)(buffer)(Enum)(pname)(IntPtr)(offset)) \
    M(GetQueryBufferObjectuiv,                               void,          (Uint)(id)(Uint)(buffer)(Enum)(pname)(IntPtr)(offset)) \
    M(GetTextureImage,                                       void,          (Uint)(texture)(Int)(level)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(pixels)) \
    M(GetTextureLevelParameterfv,                            void,          (Uint)(texture)(Int)(level)(Enum)(pname)(Float*)(params)) \
    M(GetTextureLevelParameteriv,                            void,          (Uint)(texture)(Int)(level)(Enum)(pname)(Int*)(params)) \
    M(GetTextureParameterIiv,                                void,          (Uint)(texture)(Enum)(pname)(Int*)(params)) \
    M(GetTextureParameterIuiv,                               void,          (Uint)(texture)(Enum)(pname)(Uint*)(params)) \
    M(GetTextureParameterfv,                                 void,          (Uint)(texture)(Enum)(pname)(Float*)(params)) \
    M(GetTextureParameteriv,                                 void,          (Uint)(texture)(Enum)(pname)(Int*)(params)) \
    M(GetTransformFeedbacki64_v,                             void,          (Uint)(xfb)(Enum)(pname)(Uint)(index)(Int64*)(param)) \
    M(GetTransformFeedbacki_v,                               void,          (Uint)(xfb)(Enum)(pname)(Uint)(index)(Int*)(param)) \
    M(GetTransformFeedbackiv,                                void,          (Uint)(xfb)(Enum)(pname)(Int*)(param)) \
    M(GetVertexArrayIndexed64iv,                             void,          (Uint)(vaobj)(Uint)(index)(Enum)(pname)(Int64*)(param)) \
    M(GetVertexArrayIndexediv,                               void,          (Uint)(vaobj)(Uint)(index)(Enum)(pname)(Int*)(param)) \
    M(GetVertexArrayiv,                                      void,          (Uint)(vaobj)(Enum)(pname)(Int*)(param)) \
    M(InvalidateNamedFramebufferData,                        void,          (Uint)(framebuffer)(Isize)(numAttachments)(const Enum*)(attachments)) \
    M(InvalidateNamedFramebufferSubData,                     void,          (Uint)(framebuffer)(Isize)(numAttachments)(const Enum*)(attachments)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(MapNamedBuffer,                                        void *,        (Uint)(buffer)(Enum)(access)) \
    M(MapNamedBufferRange,                                   void *,        (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(length)(Bitfield)(access)) \
    M(NamedBufferData,                                       void,          (Uint)(buffer)(IsizePtr)(size)(const void*)(data)(Enum)(usage)) \
    M(NamedBufferStorage,                                    void,          (Uint)(buffer)(IsizePtr)(size)(const void*)(data)(Bitfield)(flags)) \
    M(NamedBufferSubData,                                    void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)(const void*)(data)) \
    M(NamedFramebufferDrawBuffer,                            void,          (Uint)(framebuffer)(Enum)(mode)) \
    M(NamedFramebufferDrawBuffers,                           void,          (Uint)(framebuffer)(Isize)(n)(const Enum*)(bufs)) \
    M(NamedFramebufferParameteri,                            void,          (Uint)(framebuffer)(Enum)(pname)(Int)(param)) \
    M(NamedFramebufferReadBuffer,                            void,          (Uint)(framebuffer)(Enum)(mode)) \
    M(NamedFramebufferRenderbuffer,                          void,          (Uint)(framebuffer)(Enum)(attachment)(Enum)(renderbuffertarget)(Uint)(renderbuffer)) \
    M(NamedFramebufferTexture,                               void,          (Uint)(framebuffer)(Enum)(attachment)(Uint)(texture)(Int)(level)) \
    M(NamedFramebufferTextureLayer,                          void,          (Uint)(framebuffer)(Enum)(attachment)(Uint)(texture)(Int)(level)(Int)(layer)) \
    M(NamedRenderbufferStorage,                              void,          (Uint)(renderbuffer)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(NamedRenderbufferStorageMultisample,                   void,          (Uint)(renderbuffer)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(TextureBuffer,                                         void,          (Uint)(texture)(Enum)(internalformat)(Uint)(buffer)) \
    M(TextureBufferRange,                                    void,          (Uint)(texture)(Enum)(internalformat)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)) \
    M(TextureParameterIiv,                                   void,          (Uint)(texture)(Enum)(pname)(const Int*)(params)) \
    M(TextureParameterIuiv,                                  void,          (Uint)(texture)(Enum)(pname)(const Uint*)(params)) \
    M(TextureParameterf,                                     void,          (Uint)(texture)(Enum)(pname)(Float)(param)) \
    M(TextureParameterfv,                                    void,          (Uint)(texture)(Enum)(pname)(const Float*)(param)) \
    M(TextureParameteri,                                     void,          (Uint)(texture)(Enum)(pname)(Int)(param)) \
    M(TextureParameteriv,                                    void,          (Uint)(texture)(Enum)(pname)(const Int*)(param)) \
    M(TextureStorage1D,                                      void,          (Uint)(texture)(Isize)(levels)(Enum)(internalformat)(Isize)(width)) \
    M(TextureStorage2D,                                      void,          (Uint)(texture)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(TextureStorage2DMultisample,                           void,          (Uint)(texture)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Bool)(fixedsamplelocations)) \
    M(TextureStorage3D,                                      void,          (Uint)(texture)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)) \
    M(TextureStorage3DMultisample,                           void,          (Uint)(texture)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedsamplelocations)) \
    M(TextureSubImage1D,                                     void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureSubImage2D,                                     void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureSubImage3D,                                     void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TransformFeedbackBufferBase,                           void,          (Uint)(xfb)(Uint)(index)(Uint)(buffer)) \
    M(TransformFeedbackBufferRange,                          void,          (Uint)(xfb)(Uint)(index)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)) \
    M(UnmapNamedBuffer,                                      Bool,          (Uint)(buffer)) \
    M(VertexArrayAttribBinding,                              void,          (Uint)(vaobj)(Uint)(attribindex)(Uint)(bindingindex)) \
    M(VertexArrayAttribFormat,                               void,          (Uint)(vaobj)(Uint)(attribindex)(Int)(size)(Enum)(type)(Bool)(normalized)(Uint)(relativeoffset)) \
    M(VertexArrayAttribIFormat,                              void,          (Uint)(vaobj)(Uint)(attribindex)(Int)(size)(Enum)(type)(Uint)(relativeoffset)) \
    M(VertexArrayAttribLFormat,                              void,          (Uint)(vaobj)(Uint)(attribindex)(Int)(size)(Enum)(type)(Uint)(relativeoffset)) \
    M(VertexArrayBindingDivisor,                             void,          (Uint)(vaobj)(Uint)(bindingindex)(Uint)(divisor)) \
    M(VertexArrayElementBuffer,                              void,          (Uint)(vaobj)(Uint)(buffer)) \
    M(VertexArrayVertexBuffer,                               void,          (Uint)(vaobj)(Uint)(bindingindex)(Uint)(buffer)(IntPtr)(offset)(Isize)(stride)) \
    M(VertexArrayVertexBuffers,                              void,          (Uint)(vaobj)(Uint)(first)(Isize)(count)(const Uint*)(buffers)(const IntPtr*)(offsets)(const Isize*)(strides)) \
    M(DrawBuffersARB,                                        void,          (Isize)(n)(const Enum*)(bufs)) \
    M(BlendEquationSeparateiARB,                             void,          (Uint)(buf)(Enum)(modeRGB)(Enum)(modeAlpha)) \
    M(BlendEquationiARB,                                     void,          (Uint)(buf)(Enum)(mode)) \
    M(BlendFuncSeparateiARB,                                 void,          (Uint)(buf)(Enum)(srcRGB)(Enum)(dstRGB)(Enum)(srcAlpha)(Enum)(dstAlpha)) \
    M(BlendFunciARB,                                         void,          (Uint)(buf)(Enum)(src)(Enum)(dst)) \
    M(DrawElementsBaseVertex,                                void,          (Enum)(mode)(Isize)(count)(Enum)(type)(void*)(indices)(Int)(basevertex)) \
    M(DrawElementsInstancedBaseVertex,                       void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)(Int)(basevertex)) \
    M(DrawRangeElementsBaseVertex,                           void,          (Enum)(mode)(Uint)(start)(Uint)(end)(Isize)(count)(Enum)(type)(void*)(indices)(Int)(basevertex)) \
    M(MultiDrawElementsBaseVertex,                           void,          (Enum)(mode)(Isize*)(count)(Enum)(type)(void**)(indices)(Isize)(primcount)(Int*)(basevertex)) \
    M(DrawArraysIndirect,                                    void,          (Enum)(mode)(const void*)(indirect)) \
    M(DrawElementsIndirect,                                  void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)) \
    M(FramebufferParameteri,                                 void,          (Enum)(target)(Enum)(pname)(Int)(param)) \
    M(GetFramebufferParameteriv,                             void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetNamedFramebufferParameterivEXT,                     void,          (Uint)(framebuffer)(Enum)(pname)(Int*)(params)) \
    M(NamedFramebufferParameteriEXT,                         void,          (Uint)(framebuffer)(Enum)(pname)(Int)(param)) \
    M(BindFramebuffer,                                       void,          (Enum)(target)(Uint)(framebuffer)) \
    M(BindRenderbuffer,                                      void,          (Enum)(target)(Uint)(renderbuffer)) \
    M(BlitFramebuffer,                                       void,          (Int)(srcX0)(Int)(srcY0)(Int)(srcX1)(Int)(srcY1)(Int)(dstX0)(Int)(dstY0)(Int)(dstX1)(Int)(dstY1)(Bitfield)(mask)(Enum)(filter)) \
    M(CheckFramebufferStatus,                                Enum,          (Enum)(target)) \
    M(DeleteFramebuffers,                                    void,          (Isize)(n)(const Uint*)(framebuffers)) \
    M(DeleteRenderbuffers,                                   void,          (Isize)(n)(const Uint*)(renderbuffers)) \
    M(FramebufferRenderbuffer,                               void,          (Enum)(target)(Enum)(attachment)(Enum)(renderbuffertarget)(Uint)(renderbuffer)) \
    M(FramebufferTexture1D,                                  void,          (Enum)(target)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)) \
    M(FramebufferTexture2D,                                  void,          (Enum)(target)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)) \
    M(FramebufferTexture3D,                                  void,          (Enum)(target)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)(Int)(layer)) \
    M(FramebufferTextureLayer,                               void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Int)(layer)) \
    M(GenFramebuffers,                                       void,          (Isize)(n)(Uint*)(framebuffers)) \
    M(GenRenderbuffers,                                      void,          (Isize)(n)(Uint*)(renderbuffers)) \
    M(GenerateMipmap,                                        void,          (Enum)(target)) \
    M(GetFramebufferAttachmentParameteriv,                   void,          (Enum)(target)(Enum)(attachment)(Enum)(pname)(Int*)(params)) \
    M(GetRenderbufferParameteriv,                            void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(IsFramebuffer,                                         Bool,          (Uint)(framebuffer)) \
    M(IsRenderbuffer,                                        Bool,          (Uint)(renderbuffer)) \
    M(RenderbufferStorage,                                   void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(RenderbufferStorageMultisample,                        void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(FramebufferTextureARB,                                 void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)) \
    M(FramebufferTextureFaceARB,                             void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Enum)(face)) \
    M(FramebufferTextureLayerARB,                            void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Int)(layer)) \
    M(ProgramParameteriARB,                                  void,          (Uint)(program)(Enum)(pname)(Int)(value)) \
    M(GetProgramBinary,                                      void,          (Uint)(program)(Isize)(bufSize)(Isize*)(length)(Enum*)(binaryFormat)(void*)(binary)) \
    M(ProgramBinary,                                         void,          (Uint)(program)(Enum)(binaryFormat)(const void*)(binary)(Isize)(length)) \
    M(ProgramParameteri,                                     void,          (Uint)(program)(Enum)(pname)(Int)(value)) \
    M(GetCompressedTextureSubImage,                          void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Isize)(bufSize)(void*)(pixels)) \
    M(GetTextureSubImage,                                    void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(pixels)) \
    M(SpecializeShaderARB,                                   void,          (Uint)(shader)(const char*)(pEntryPoint)(Uint)(numSpecializationConstants)(const Uint*)(pConstantIndex)(const Uint*)(pConstantValue)) \
    M(GetUniformdv,                                          void,          (Uint)(program)(Int)(location)(Double*)(params)) \
    M(Uniform1d,                                             void,          (Int)(location)(Double)(x)) \
    M(Uniform1dv,                                            void,          (Int)(location)(Isize)(count)(const Double*)(value)) \
    M(Uniform2d,                                             void,          (Int)(location)(Double)(x)(Double)(y)) \
    M(Uniform2dv,                                            void,          (Int)(location)(Isize)(count)(const Double*)(value)) \
    M(Uniform3d,                                             void,          (Int)(location)(Double)(x)(Double)(y)(Double)(z)) \
    M(Uniform3dv,                                            void,          (Int)(location)(Isize)(count)(const Double*)(value)) \
    M(Uniform4d,                                             void,          (Int)(location)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(Uniform4dv,                                            void,          (Int)(location)(Isize)(count)(const Double*)(value)) \
    M(UniformMatrix2dv,                                      void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix2x3dv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix2x4dv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix3dv,                                      void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix3x2dv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix3x4dv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix4dv,                                      void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix4x2dv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(UniformMatrix4x3dv,                                    void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(GetUniformi64vARB,                                     void,          (Uint)(program)(Int)(location)(Int64*)(params)) \
    M(GetUniformui64vARB,                                    void,          (Uint)(program)(Int)(location)(Uint64*)(params)) \
    M(GetnUniformi64vARB,                                    void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Int64*)(params)) \
    M(GetnUniformui64vARB,                                   void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Uint64*)(params)) \
    M(ProgramUniform1i64ARB,                                 void,          (Uint)(program)(Int)(location)(Int64)(x)) \
    M(ProgramUniform1i64vARB,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform1ui64ARB,                                void,          (Uint)(program)(Int)(location)(Uint64)(x)) \
    M(ProgramUniform1ui64vARB,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(ProgramUniform2i64ARB,                                 void,          (Uint)(program)(Int)(location)(Int64)(x)(Int64)(y)) \
    M(ProgramUniform2i64vARB,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform2ui64ARB,                                void,          (Uint)(program)(Int)(location)(Uint64)(x)(Uint64)(y)) \
    M(ProgramUniform2ui64vARB,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(ProgramUniform3i64ARB,                                 void,          (Uint)(program)(Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)) \
    M(ProgramUniform3i64vARB,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform3ui64ARB,                                void,          (Uint)(program)(Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)) \
    M(ProgramUniform3ui64vARB,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(ProgramUniform4i64ARB,                                 void,          (Uint)(program)(Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)(Int64)(w)) \
    M(ProgramUniform4i64vARB,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform4ui64ARB,                                void,          (Uint)(program)(Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)(Uint64)(w)) \
    M(ProgramUniform4ui64vARB,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform1i64ARB,                                        void,          (Int)(location)(Int64)(x)) \
    M(Uniform1i64vARB,                                       void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform1ui64ARB,                                       void,          (Int)(location)(Uint64)(x)) \
    M(Uniform1ui64vARB,                                      void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform2i64ARB,                                        void,          (Int)(location)(Int64)(x)(Int64)(y)) \
    M(Uniform2i64vARB,                                       void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform2ui64ARB,                                       void,          (Int)(location)(Uint64)(x)(Uint64)(y)) \
    M(Uniform2ui64vARB,                                      void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform3i64ARB,                                        void,          (Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)) \
    M(Uniform3i64vARB,                                       void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform3ui64ARB,                                       void,          (Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)) \
    M(Uniform3ui64vARB,                                      void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform4i64ARB,                                        void,          (Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)(Int64)(w)) \
    M(Uniform4i64vARB,                                       void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform4ui64ARB,                                       void,          (Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)(Uint64)(w)) \
    M(Uniform4ui64vARB,                                      void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(ColorSubTable,                                         void,          (Enum)(target)(Isize)(start)(Isize)(count)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ColorTable,                                            void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(table)) \
    M(ColorTableParameterfv,                                 void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(ColorTableParameteriv,                                 void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(ConvolutionFilter1D,                                   void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(image)) \
    M(ConvolutionFilter2D,                                   void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(image)) \
    M(ConvolutionParameterf,                                 void,          (Enum)(target)(Enum)(pname)(Float)(params)) \
    M(ConvolutionParameterfv,                                void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(ConvolutionParameteri,                                 void,          (Enum)(target)(Enum)(pname)(Int)(params)) \
    M(ConvolutionParameteriv,                                void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(CopyColorSubTable,                                     void,          (Enum)(target)(Isize)(start)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyColorTable,                                        void,          (Enum)(target)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyConvolutionFilter1D,                               void,          (Enum)(target)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyConvolutionFilter2D,                               void,          (Enum)(target)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(GetColorTable,                                         void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(table)) \
    M(GetColorTableParameterfv,                              void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetColorTableParameteriv,                              void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetConvolutionFilter,                                  void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(image)) \
    M(GetConvolutionParameterfv,                             void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetConvolutionParameteriv,                             void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetHistogram,                                          void,          (Enum)(target)(Bool)(reset)(Enum)(format)(Enum)(type)(void*)(values)) \
    M(GetHistogramParameterfv,                               void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetHistogramParameteriv,                               void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetMinmax,                                             void,          (Enum)(target)(Bool)(reset)(Enum)(format)(Enum)(types)(void*)(values)) \
    M(GetMinmaxParameterfv,                                  void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetMinmaxParameteriv,                                  void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetSeparableFilter,                                    void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(row)(void*)(column)(void*)(span)) \
    M(Histogram,                                             void,          (Enum)(target)(Isize)(width)(Enum)(internalformat)(Bool)(sink)) \
    M(Minmax,                                                void,          (Enum)(target)(Enum)(internalformat)(Bool)(sink)) \
    M(ResetHistogram,                                        void,          (Enum)(target)) \
    M(ResetMinmax,                                           void,          (Enum)(target)) \
    M(SeparableFilter2D,                                     void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(row)(const void*)(column)) \
    M(MultiDrawArraysIndirectCountARB,                       void,          (Enum)(mode)(const void*)(indirect)(IntPtr)(drawcount)(Isize)(maxdrawcount)(Isize)(stride)) \
    M(MultiDrawElementsIndirectCountARB,                     void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)(IntPtr)(drawcount)(Isize)(maxdrawcount)(Isize)(stride)) \
    M(DrawArraysInstancedARB,                                void,          (Enum)(mode)(Int)(first)(Isize)(count)(Isize)(primcount)) \
    M(DrawElementsInstancedARB,                              void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)) \
    M(VertexAttribDivisorARB,                                void,          (Uint)(index)(Uint)(divisor)) \
    M(GetInternalformativ,                                   void,          (Enum)(target)(Enum)(internalformat)(Enum)(pname)(Isize)(bufSize)(Int*)(params)) \
    M(GetInternalformati64v,                                 void,          (Enum)(target)(Enum)(internalformat)(Enum)(pname)(Isize)(bufSize)(Int64*)(params)) \
    M(InvalidateBufferData,                                  void,          (Uint)(buffer)) \
    M(InvalidateBufferSubData,                               void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(length)) \
    M(InvalidateFramebuffer,                                 void,          (Enum)(target)(Isize)(numAttachments)(const Enum*)(attachments)) \
    M(InvalidateSubFramebuffer,                              void,          (Enum)(target)(Isize)(numAttachments)(const Enum*)(attachments)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(InvalidateTexImage,                                    void,          (Uint)(texture)(Int)(level)) \
    M(InvalidateTexSubImage,                                 void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)) \
    M(FlushMappedBufferRange,                                void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(length)) \
    M(MapBufferRange,                                        void *,        (Enum)(target)(IntPtr)(offset)(IsizePtr)(length)(Bitfield)(access)) \
    M(CurrentPaletteMatrixARB,                               void,          (Int)(index)) \
    M(MatrixIndexPointerARB,                                 void,          (Int)(size)(Enum)(type)(Isize)(stride)(void*)(pointer)) \
    M(MatrixIndexubvARB,                                     void,          (Int)(size)(Ubyte*)(indices)) \
    M(MatrixIndexuivARB,                                     void,          (Int)(size)(Uint*)(indices)) \
    M(MatrixIndexusvARB,                                     void,          (Int)(size)(Ushort*)(indices)) \
    M(BindBuffersBase,                                       void,          (Enum)(target)(Uint)(first)(Isize)(count)(const Uint*)(buffers)) \
    M(BindBuffersRange,                                      void,          (Enum)(target)(Uint)(first)(Isize)(count)(const Uint*)(buffers)(const IntPtr*)(offsets)(const IsizePtr*)(sizes)) \
    M(BindImageTextures,                                     void,          (Uint)(first)(Isize)(count)(const Uint*)(textures)) \
    M(BindSamplers,                                          void,          (Uint)(first)(Isize)(count)(const Uint*)(samplers)) \
    M(BindTextures,                                          void,          (Uint)(first)(Isize)(count)(const Uint*)(textures)) \
    M(BindVertexBuffers,                                     void,          (Uint)(first)(Isize)(count)(const Uint*)(buffers)(const IntPtr*)(offsets)(const Isize*)(strides)) \
    M(MultiDrawArraysIndirect,                               void,          (Enum)(mode)(const void*)(indirect)(Isize)(primcount)(Isize)(stride)) \
    M(MultiDrawElementsIndirect,                             void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)(Isize)(primcount)(Isize)(stride)) \
    M(SampleCoverageARB,                                     void,          (FClamp)(value)(Bool)(invert)) \
    M(ActiveTextureARB,                                      void,          (Enum)(texture)) \
    M(ClientActiveTextureARB,                                void,          (Enum)(texture)) \
    M(MultiTexCoord1dARB,                                    void,          (Enum)(target)(Double)(s)) \
    M(MultiTexCoord1dvARB,                                   void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord1fARB,                                    void,          (Enum)(target)(Float)(s)) \
    M(MultiTexCoord1fvARB,                                   void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord1iARB,                                    void,          (Enum)(target)(Int)(s)) \
    M(MultiTexCoord1ivARB,                                   void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord1sARB,                                    void,          (Enum)(target)(Short)(s)) \
    M(MultiTexCoord1svARB,                                   void,          (Enum)(target)(const Short*)(v)) \
    M(MultiTexCoord2dARB,                                    void,          (Enum)(target)(Double)(s)(Double)(t)) \
    M(MultiTexCoord2dvARB,                                   void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord2fARB,                                    void,          (Enum)(target)(Float)(s)(Float)(t)) \
    M(MultiTexCoord2fvARB,                                   void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord2iARB,                                    void,          (Enum)(target)(Int)(s)(Int)(t)) \
    M(MultiTexCoord2ivARB,                                   void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord2sARB,                                    void,          (Enum)(target)(Short)(s)(Short)(t)) \
    M(MultiTexCoord2svARB,                                   void,          (Enum)(target)(const Short*)(v)) \
    M(MultiTexCoord3dARB,                                    void,          (Enum)(target)(Double)(s)(Double)(t)(Double)(r)) \
    M(MultiTexCoord3dvARB,                                   void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord3fARB,                                    void,          (Enum)(target)(Float)(s)(Float)(t)(Float)(r)) \
    M(MultiTexCoord3fvARB,                                   void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord3iARB,                                    void,          (Enum)(target)(Int)(s)(Int)(t)(Int)(r)) \
    M(MultiTexCoord3ivARB,                                   void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord3sARB,                                    void,          (Enum)(target)(Short)(s)(Short)(t)(Short)(r)) \
    M(MultiTexCoord3svARB,                                   void,          (Enum)(target)(const Short*)(v)) \
    M(MultiTexCoord4dARB,                                    void,          (Enum)(target)(Double)(s)(Double)(t)(Double)(r)(Double)(q)) \
    M(MultiTexCoord4dvARB,                                   void,          (Enum)(target)(const Double*)(v)) \
    M(MultiTexCoord4fARB,                                    void,          (Enum)(target)(Float)(s)(Float)(t)(Float)(r)(Float)(q)) \
    M(MultiTexCoord4fvARB,                                   void,          (Enum)(target)(const Float*)(v)) \
    M(MultiTexCoord4iARB,                                    void,          (Enum)(target)(Int)(s)(Int)(t)(Int)(r)(Int)(q)) \
    M(MultiTexCoord4ivARB,                                   void,          (Enum)(target)(const Int*)(v)) \
    M(MultiTexCoord4sARB,                                    void,          (Enum)(target)(Short)(s)(Short)(t)(Short)(r)(Short)(q)) \
    M(MultiTexCoord4svARB,                                   void,          (Enum)(target)(const Short*)(v)) \
    M(BeginQueryARB,                                         void,          (Enum)(target)(Uint)(id)) \
    M(DeleteQueriesARB,                                      void,          (Isize)(n)(const Uint*)(ids)) \
    M(EndQueryARB,                                           void,          (Enum)(target)) \
    M(GenQueriesARB,                                         void,          (Isize)(n)(Uint*)(ids)) \
    M(GetQueryObjectivARB,                                   void,          (Uint)(id)(Enum)(pname)(Int*)(params)) \
    M(GetQueryObjectuivARB,                                  void,          (Uint)(id)(Enum)(pname)(Uint*)(params)) \
    M(GetQueryivARB,                                         void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(IsQueryARB,                                            Bool,          (Uint)(id)) \
    M(MaxShaderCompilerThreadsARB,                           void,          (Uint)(count)) \
    M(PointParameterfARB,                                    void,          (Enum)(pname)(Float)(param)) \
    M(PointParameterfvARB,                                   void,          (Enum)(pname)(const Float*)(params)) \
    M(PolygonOffsetClamp,                                    void,          (Float)(factor)(Float)(units)(Float)(clamp)) \
    M(GetProgramInterfaceiv,                                 void,          (Uint)(program)(Enum)(programInterface)(Enum)(pname)(Int*)(params)) \
    M(GetProgramResourceIndex,                               Uint,          (Uint)(program)(Enum)(programInterface)(const char*)(name)) \
    M(GetProgramResourceLocation,                            Int,           (Uint)(program)(Enum)(programInterface)(const char*)(name)) \
    M(GetProgramResourceLocationIndex,                       Int,           (Uint)(program)(Enum)(programInterface)(const char*)(name)) \
    M(GetProgramResourceName,                                void,          (Uint)(program)(Enum)(programInterface)(Uint)(index)(Isize)(bufSize)(Isize*)(length)(char*)(name)) \
    M(GetProgramResourceiv,                                  void,          (Uint)(program)(Enum)(programInterface)(Uint)(index)(Isize)(propCount)(const Enum*)(props)(Isize)(bufSize)(Isize*)(length)(Int*)(params)) \
    M(ProvokingVertex,                                       void,          (Enum)(mode)) \
    M(GetGraphicsResetStatusARB,                             Enum,          ) \
    M(GetnColorTableARB,                                     void,          (Enum)(target)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(table)) \
    M(GetnCompressedTexImageARB,                             void,          (Enum)(target)(Int)(lod)(Isize)(bufSize)(void*)(img)) \
    M(GetnConvolutionFilterARB,                              void,          (Enum)(target)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(image)) \
    M(GetnHistogramARB,                                      void,          (Enum)(target)(Bool)(reset)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(values)) \
    M(GetnMapdvARB,                                          void,          (Enum)(target)(Enum)(query)(Isize)(bufSize)(Double*)(v)) \
    M(GetnMapfvARB,                                          void,          (Enum)(target)(Enum)(query)(Isize)(bufSize)(Float*)(v)) \
    M(GetnMapivARB,                                          void,          (Enum)(target)(Enum)(query)(Isize)(bufSize)(Int*)(v)) \
    M(GetnMinmaxARB,                                         void,          (Enum)(target)(Bool)(reset)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(values)) \
    M(GetnPixelMapfvARB,                                     void,          (Enum)(map)(Isize)(bufSize)(Float*)(values)) \
    M(GetnPixelMapuivARB,                                    void,          (Enum)(map)(Isize)(bufSize)(Uint*)(values)) \
    M(GetnPixelMapusvARB,                                    void,          (Enum)(map)(Isize)(bufSize)(Ushort*)(values)) \
    M(GetnPolygonStippleARB,                                 void,          (Isize)(bufSize)(Ubyte*)(pattern)) \
    M(GetnSeparableFilterARB,                                void,          (Enum)(target)(Enum)(format)(Enum)(type)(Isize)(rowBufSize)(void*)(row)(Isize)(columnBufSize)(void*)(column)(void*)(span)) \
    M(GetnTexImageARB,                                       void,          (Enum)(target)(Int)(level)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(img)) \
    M(GetnUniformdvARB,                                      void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Double*)(params)) \
    M(GetnUniformfvARB,                                      void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Float*)(params)) \
    M(GetnUniformivARB,                                      void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Int*)(params)) \
    M(GetnUniformuivARB,                                     void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Uint*)(params)) \
    M(ReadnPixelsARB,                                        void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(data)) \
    M(FramebufferSampleLocationsfvARB,                       void,          (Enum)(target)(Uint)(start)(Isize)(count)(const Float*)(v)) \
    M(NamedFramebufferSampleLocationsfvARB,                  void,          (Uint)(framebuffer)(Uint)(start)(Isize)(count)(const Float*)(v)) \
    M(MinSampleShadingARB,                                   void,          (FClamp)(value)) \
    M(BindSampler,                                           void,          (Uint)(unit)(Uint)(sampler)) \
    M(DeleteSamplers,                                        void,          (Isize)(count)(const Uint *)(samplers)) \
    M(GenSamplers,                                           void,          (Isize)(count)(Uint*)(samplers)) \
    M(GetSamplerParameterIiv,                                void,          (Uint)(sampler)(Enum)(pname)(Int*)(params)) \
    M(GetSamplerParameterIuiv,                               void,          (Uint)(sampler)(Enum)(pname)(Uint*)(params)) \
    M(GetSamplerParameterfv,                                 void,          (Uint)(sampler)(Enum)(pname)(Float*)(params)) \
    M(GetSamplerParameteriv,                                 void,          (Uint)(sampler)(Enum)(pname)(Int*)(params)) \
    M(IsSampler,                                             Bool,          (Uint)(sampler)) \
    M(SamplerParameterIiv,                                   void,          (Uint)(sampler)(Enum)(pname)(const Int*)(params)) \
    M(SamplerParameterIuiv,                                  void,          (Uint)(sampler)(Enum)(pname)(const Uint*)(params)) \
    M(SamplerParameterf,                                     void,          (Uint)(sampler)(Enum)(pname)(Float)(param)) \
    M(SamplerParameterfv,                                    void,          (Uint)(sampler)(Enum)(pname)(const Float*)(params)) \
    M(SamplerParameteri,                                     void,          (Uint)(sampler)(Enum)(pname)(Int)(param)) \
    M(SamplerParameteriv,                                    void,          (Uint)(sampler)(Enum)(pname)(const Int*)(params)) \
    M(ActiveShaderProgram,                                   void,          (Uint)(pipeline)(Uint)(program)) \
    M(BindProgramPipeline,                                   void,          (Uint)(pipeline)) \
    M(CreateShaderProgramv,                                  Uint,          (Enum)(type)(Isize)(count)(const char * const *)(strings)) \
    M(DeleteProgramPipelines,                                void,          (Isize)(n)(const Uint*)(pipelines)) \
    M(GenProgramPipelines,                                   void,          (Isize)(n)(Uint*)(pipelines)) \
    M(GetProgramPipelineInfoLog,                             void,          (Uint)(pipeline)(Isize)(bufSize)(Isize*)(length)(char*)(infoLog)) \
    M(GetProgramPipelineiv,                                  void,          (Uint)(pipeline)(Enum)(pname)(Int*)(params)) \
    M(IsProgramPipeline,                                     Bool,          (Uint)(pipeline)) \
    M(ProgramUniform1d,                                      void,          (Uint)(program)(Int)(location)(Double)(x)) \
    M(ProgramUniform1dv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Double*)(value)) \
    M(ProgramUniform1f,                                      void,          (Uint)(program)(Int)(location)(Float)(x)) \
    M(ProgramUniform1fv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform1i,                                      void,          (Uint)(program)(Int)(location)(Int)(x)) \
    M(ProgramUniform1iv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform1ui,                                     void,          (Uint)(program)(Int)(location)(Uint)(x)) \
    M(ProgramUniform1uiv,                                    void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniform2d,                                      void,          (Uint)(program)(Int)(location)(Double)(x)(Double)(y)) \
    M(ProgramUniform2dv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Double*)(value)) \
    M(ProgramUniform2f,                                      void,          (Uint)(program)(Int)(location)(Float)(x)(Float)(y)) \
    M(ProgramUniform2fv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform2i,                                      void,          (Uint)(program)(Int)(location)(Int)(x)(Int)(y)) \
    M(ProgramUniform2iv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform2ui,                                     void,          (Uint)(program)(Int)(location)(Uint)(x)(Uint)(y)) \
    M(ProgramUniform2uiv,                                    void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniform3d,                                      void,          (Uint)(program)(Int)(location)(Double)(x)(Double)(y)(Double)(z)) \
    M(ProgramUniform3dv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Double*)(value)) \
    M(ProgramUniform3f,                                      void,          (Uint)(program)(Int)(location)(Float)(x)(Float)(y)(Float)(z)) \
    M(ProgramUniform3fv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform3i,                                      void,          (Uint)(program)(Int)(location)(Int)(x)(Int)(y)(Int)(z)) \
    M(ProgramUniform3iv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform3ui,                                     void,          (Uint)(program)(Int)(location)(Uint)(x)(Uint)(y)(Uint)(z)) \
    M(ProgramUniform3uiv,                                    void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniform4d,                                      void,          (Uint)(program)(Int)(location)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(ProgramUniform4dv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Double*)(value)) \
    M(ProgramUniform4f,                                      void,          (Uint)(program)(Int)(location)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(ProgramUniform4fv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform4i,                                      void,          (Uint)(program)(Int)(location)(Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(ProgramUniform4iv,                                     void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform4ui,                                     void,          (Uint)(program)(Int)(location)(Uint)(x)(Uint)(y)(Uint)(z)(Uint)(w)) \
    M(ProgramUniform4uiv,                                    void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniformMatrix2dv,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix2fv,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix2x3dv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix2x3fv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix2x4dv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix2x4fv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix3dv,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix3fv,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix3x2dv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix3x2fv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix3x4dv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix3x4fv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix4dv,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix4fv,                               void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix4x2dv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix4x2fv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix4x3dv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Double*)(value)) \
    M(ProgramUniformMatrix4x3fv,                             void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UseProgramStages,                                      void,          (Uint)(pipeline)(Bitfield)(stages)(Uint)(program)) \
    M(ValidateProgramPipeline,                               void,          (Uint)(pipeline)) \
    M(GetActiveAtomicCounterBufferiv,                        void,          (Uint)(program)(Uint)(bufferIndex)(Enum)(pname)(Int*)(params)) \
    M(BindImageTexture,                                      void,          (Uint)(unit)(Uint)(texture)(Int)(level)(Bool)(layered)(Int)(layer)(Enum)(access)(Enum)(format)) \
    M(MemoryBarrier,                                         void,          (Bitfield)(barriers)) \
    M(AttachObjectARB,                                       void,          (Handle)(containerObj)(Handle)(obj)) \
    M(CompileShaderARB,                                      void,          (Handle)(shaderObj)) \
    M(CreateProgramObjectARB,                                Handle,        ) \
    M(CreateShaderObjectARB,                                 Handle,        (Enum)(shaderType)) \
    M(DeleteObjectARB,                                       void,          (Handle)(obj)) \
    M(DetachObjectARB,                                       void,          (Handle)(containerObj)(Handle)(attachedObj)) \
    M(GetActiveUniformARB,                                   void,          (Handle)(programObj)(Uint)(index)(Isize)(maxLength)(Isize*)(length)(Int*)(size)(Enum*)(type)(char*)(name)) \
    M(GetAttachedObjectsARB,                                 void,          (Handle)(containerObj)(Isize)(maxCount)(Isize*)(count)(Handle*)(obj)) \
    M(GetHandleARB,                                          Handle,        (Enum)(pname)) \
    M(GetInfoLogARB,                                         void,          (Handle)(obj)(Isize)(maxLength)(Isize*)(length)(char*)(infoLog)) \
    M(GetObjectParameterfvARB,                               void,          (Handle)(obj)(Enum)(pname)(Float*)(params)) \
    M(GetObjectParameterivARB,                               void,          (Handle)(obj)(Enum)(pname)(Int*)(params)) \
    M(GetShaderSourceARB,                                    void,          (Handle)(obj)(Isize)(maxLength)(Isize*)(length)(char*)(source)) \
    M(GetUniformLocationARB,                                 Int,           (Handle)(programObj)(const char*)(name)) \
    M(GetUniformfvARB,                                       void,          (Handle)(programObj)(Int)(location)(Float*)(params)) \
    M(GetUniformivARB,                                       void,          (Handle)(programObj)(Int)(location)(Int*)(params)) \
    M(LinkProgramARB,                                        void,          (Handle)(programObj)) \
    M(ShaderSourceARB,                                       void,          (Handle)(shaderObj)(Isize)(count)(const char**)(string)(const Int*)(length)) \
    M(Uniform1fARB,                                          void,          (Int)(location)(Float)(v0)) \
    M(Uniform1fvARB,                                         void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform1iARB,                                          void,          (Int)(location)(Int)(v0)) \
    M(Uniform1ivARB,                                         void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(Uniform2fARB,                                          void,          (Int)(location)(Float)(v0)(Float)(v1)) \
    M(Uniform2fvARB,                                         void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform2iARB,                                          void,          (Int)(location)(Int)(v0)(Int)(v1)) \
    M(Uniform2ivARB,                                         void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(Uniform3fARB,                                          void,          (Int)(location)(Float)(v0)(Float)(v1)(Float)(v2)) \
    M(Uniform3fvARB,                                         void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform3iARB,                                          void,          (Int)(location)(Int)(v0)(Int)(v1)(Int)(v2)) \
    M(Uniform3ivARB,                                         void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(Uniform4fARB,                                          void,          (Int)(location)(Float)(v0)(Float)(v1)(Float)(v2)(Float)(v3)) \
    M(Uniform4fvARB,                                         void,          (Int)(location)(Isize)(count)(const Float*)(value)) \
    M(Uniform4iARB,                                          void,          (Int)(location)(Int)(v0)(Int)(v1)(Int)(v2)(Int)(v3)) \
    M(Uniform4ivARB,                                         void,          (Int)(location)(Isize)(count)(const Int*)(value)) \
    M(UniformMatrix2fvARB,                                   void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix3fvARB,                                   void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix4fvARB,                                   void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UseProgramObjectARB,                                   void,          (Handle)(programObj)) \
    M(ValidateProgramARB,                                    void,          (Handle)(programObj)) \
    M(ShaderStorageBlockBinding,                             void,          (Uint)(program)(Uint)(storageBlockIndex)(Uint)(storageBlockBinding)) \
    M(GetActiveSubroutineName,                               void,          (Uint)(program)(Enum)(shadertype)(Uint)(index)(Isize)(bufsize)(Isize*)(length)(char*)(name)) \
    M(GetActiveSubroutineUniformName,                        void,          (Uint)(program)(Enum)(shadertype)(Uint)(index)(Isize)(bufsize)(Isize*)(length)(char*)(name)) \
    M(GetActiveSubroutineUniformiv,                          void,          (Uint)(program)(Enum)(shadertype)(Uint)(index)(Enum)(pname)(Int*)(values)) \
    M(GetProgramStageiv,                                     void,          (Uint)(program)(Enum)(shadertype)(Enum)(pname)(Int*)(values)) \
    M(GetSubroutineIndex,                                    Uint,          (Uint)(program)(Enum)(shadertype)(const char*)(name)) \
    M(GetSubroutineUniformLocation,                          Int,           (Uint)(program)(Enum)(shadertype)(const char*)(name)) \
    M(GetUniformSubroutineuiv,                               void,          (Enum)(shadertype)(Int)(location)(Uint*)(params)) \
    M(UniformSubroutinesuiv,                                 void,          (Enum)(shadertype)(Isize)(count)(const Uint*)(indices)) \
    M(CompileShaderIncludeARB,                               void,          (Uint)(shader)(Isize)(count)(const char* const*)(path)(const Int*)(length)) \
    M(DeleteNamedStringARB,                                  void,          (Int)(namelen)(const char*)(name)) \
    M(GetNamedStringARB,                                     void,          (Int)(namelen)(const char*)(name)(Isize)(bufSize)(Int*)(stringlen)(char*)(string)) \
    M(GetNamedStringivARB,                                   void,          (Int)(namelen)(const char*)(name)(Enum)(pname)(Int*)(params)) \
    M(IsNamedStringARB,                                      Bool,          (Int)(namelen)(const char*)(name)) \
    M(NamedStringARB,                                        void,          (Enum)(type)(Int)(namelen)(const char*)(name)(Int)(stringlen)(const char*)(string)) \
    M(BufferPageCommitmentARB,                               void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(size)(Bool)(commit)) \
    M(TexPageCommitmentARB,                                  void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(commit)) \
    M(ClientWaitSync,                                        Enum,          (Sync)(sync)(Bitfield)(flags)(Uint64)(timeout)) \
    M(DeleteSync,                                            void,          (Sync)(sync)) \
    M(FenceSync,                                             Sync,          (Enum)(condition)(Bitfield)(flags)) \
    M(GetInteger64v,                                         void,          (Enum)(pname)(Int64*)(params)) \
    M(GetSynciv,                                             void,          (Sync)(sync)(Enum)(pname)(Isize)(bufSize)(Isize*)(length)(Int*)(values)) \
    M(IsSync,                                                Bool,          (Sync)(sync)) \
    M(WaitSync,                                              void,          (Sync)(sync)(Bitfield)(flags)(Uint64)(timeout)) \
    M(PatchParameterfv,                                      void,          (Enum)(pname)(const Float*)(values)) \
    M(PatchParameteri,                                       void,          (Enum)(pname)(Int)(value)) \
    M(TextureBarrier,                                        void,          ) \
    M(TexBufferARB,                                          void,          (Enum)(target)(Enum)(internalformat)(Uint)(buffer)) \
    M(TexBufferRange,                                        void,          (Enum)(target)(Enum)(internalformat)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)) \
    M(TextureBufferRangeEXT,                                 void,          (Uint)(texture)(Enum)(target)(Enum)(internalformat)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)) \
    M(CompressedTexImage1DARB,                               void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexImage2DARB,                               void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexImage3DARB,                               void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexSubImage1DARB,                            void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexSubImage2DARB,                            void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexSubImage3DARB,                            void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(GetCompressedTexImageARB,                              void,          (Enum)(target)(Int)(lod)(void*)(img)) \
    M(GetMultisamplefv,                                      void,          (Enum)(pname)(Uint)(index)(Float*)(val)) \
    M(SampleMaski,                                           void,          (Uint)(index)(Bitfield)(mask)) \
    M(TexImage2DMultisample,                                 void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Bool)(fixedsamplelocations)) \
    M(TexImage3DMultisample,                                 void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedsamplelocations)) \
    M(TexStorage1D,                                          void,          (Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)) \
    M(TexStorage2D,                                          void,          (Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(TexStorage3D,                                          void,          (Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)) \
    M(TexStorage2DMultisample,                               void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Bool)(fixedsamplelocations)) \
    M(TexStorage3DMultisample,                               void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedsamplelocations)) \
    M(TextureStorage2DMultisampleEXT,                        void,          (Uint)(texture)(Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Bool)(fixedsamplelocations)) \
    M(TextureStorage3DMultisampleEXT,                        void,          (Uint)(texture)(Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedsamplelocations)) \
    M(TextureView,                                           void,          (Uint)(texture)(Enum)(target)(Uint)(origtexture)(Enum)(internalformat)(Uint)(minlevel)(Uint)(numlevels)(Uint)(minlayer)(Uint)(numlayers)) \
    M(GetQueryObjecti64v,                                    void,          (Uint)(id)(Enum)(pname)(Int64*)(params)) \
    M(GetQueryObjectui64v,                                   void,          (Uint)(id)(Enum)(pname)(Uint64*)(params)) \
    M(QueryCounter,                                          void,          (Uint)(id)(Enum)(target)) \
    M(BindTransformFeedback,                                 void,          (Enum)(target)(Uint)(id)) \
    M(DeleteTransformFeedbacks,                              void,          (Isize)(n)(const Uint*)(ids)) \
    M(DrawTransformFeedback,                                 void,          (Enum)(mode)(Uint)(id)) \
    M(GenTransformFeedbacks,                                 void,          (Isize)(n)(Uint*)(ids)) \
    M(IsTransformFeedback,                                   Bool,          (Uint)(id)) \
    M(PauseTransformFeedback,                                void,          ) \
    M(ResumeTransformFeedback,                               void,          ) \
    M(BeginQueryIndexed,                                     void,          (Enum)(target)(Uint)(index)(Uint)(id)) \
    M(DrawTransformFeedbackStream,                           void,          (Enum)(mode)(Uint)(id)(Uint)(stream)) \
    M(EndQueryIndexed,                                       void,          (Enum)(target)(Uint)(index)) \
    M(GetQueryIndexediv,                                     void,          (Enum)(target)(Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(DrawTransformFeedbackInstanced,                        void,          (Enum)(mode)(Uint)(id)(Isize)(primcount)) \
    M(DrawTransformFeedbackStreamInstanced,                  void,          (Enum)(mode)(Uint)(id)(Uint)(stream)(Isize)(primcount)) \
    M(LoadTransposeMatrixdARB,                               void,          (Double*)(m)) \
    M(LoadTransposeMatrixfARB,                               void,          (Float*)(m)) \
    M(MultTransposeMatrixdARB,                               void,          (Double*)(m)) \
    M(MultTransposeMatrixfARB,                               void,          (Float*)(m)) \
    M(BindBufferBase,                                        void,          (Enum)(target)(Uint)(index)(Uint)(buffer)) \
    M(BindBufferRange,                                       void,          (Enum)(target)(Uint)(index)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)) \
    M(GetActiveUniformBlockName,                             void,          (Uint)(program)(Uint)(uniformBlockIndex)(Isize)(bufSize)(Isize*)(length)(char*)(uniformBlockName)) \
    M(GetActiveUniformBlockiv,                               void,          (Uint)(program)(Uint)(uniformBlockIndex)(Enum)(pname)(Int*)(params)) \
    M(GetActiveUniformName,                                  void,          (Uint)(program)(Uint)(uniformIndex)(Isize)(bufSize)(Isize*)(length)(char*)(uniformName)) \
    M(GetActiveUniformsiv,                                   void,          (Uint)(program)(Isize)(uniformCount)(const Uint*)(uniformIndices)(Enum)(pname)(Int*)(params)) \
    M(GetIntegeri_v,                                         void,          (Enum)(target)(Uint)(index)(Int*)(data)) \
    M(GetUniformBlockIndex,                                  Uint,          (Uint)(program)(const char*)(uniformBlockName)) \
    M(GetUniformIndices,                                     void,          (Uint)(program)(Isize)(uniformCount)(const char* const *)(uniformNames)(Uint*)(uniformIndices)) \
    M(UniformBlockBinding,                                   void,          (Uint)(program)(Uint)(uniformBlockIndex)(Uint)(uniformBlockBinding)) \
    M(BindVertexArray,                                       void,          (Uint)(array)) \
    M(DeleteVertexArrays,                                    void,          (Isize)(n)(const Uint*)(arrays)) \
    M(GenVertexArrays,                                       void,          (Isize)(n)(Uint*)(arrays)) \
    M(IsVertexArray,                                         Bool,          (Uint)(array)) \
    M(GetVertexAttribLdv,                                    void,          (Uint)(index)(Enum)(pname)(Double*)(params)) \
    M(VertexAttribL1d,                                       void,          (Uint)(index)(Double)(x)) \
    M(VertexAttribL1dv,                                      void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribL2d,                                       void,          (Uint)(index)(Double)(x)(Double)(y)) \
    M(VertexAttribL2dv,                                      void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribL3d,                                       void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)) \
    M(VertexAttribL3dv,                                      void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribL4d,                                       void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(VertexAttribL4dv,                                      void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribLPointer,                                  void,          (Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(BindVertexBuffer,                                      void,          (Uint)(bindingindex)(Uint)(buffer)(IntPtr)(offset)(Isize)(stride)) \
    M(VertexArrayBindVertexBufferEXT,                        void,          (Uint)(vaobj)(Uint)(bindingindex)(Uint)(buffer)(IntPtr)(offset)(Isize)(stride)) \
    M(VertexArrayVertexAttribBindingEXT,                     void,          (Uint)(vaobj)(Uint)(attribindex)(Uint)(bindingindex)) \
    M(VertexArrayVertexAttribFormatEXT,                      void,          (Uint)(vaobj)(Uint)(attribindex)(Int)(size)(Enum)(type)(Bool)(normalized)(Uint)(relativeoffset)) \
    M(VertexArrayVertexAttribIFormatEXT,                     void,          (Uint)(vaobj)(Uint)(attribindex)(Int)(size)(Enum)(type)(Uint)(relativeoffset)) \
    M(VertexArrayVertexAttribLFormatEXT,                     void,          (Uint)(vaobj)(Uint)(attribindex)(Int)(size)(Enum)(type)(Uint)(relativeoffset)) \
    M(VertexArrayVertexBindingDivisorEXT,                    void,          (Uint)(vaobj)(Uint)(bindingindex)(Uint)(divisor)) \
    M(VertexAttribBinding,                                   void,          (Uint)(attribindex)(Uint)(bindingindex)) \
    M(VertexAttribFormat,                                    void,          (Uint)(attribindex)(Int)(size)(Enum)(type)(Bool)(normalized)(Uint)(relativeoffset)) \
    M(VertexAttribIFormat,                                   void,          (Uint)(attribindex)(Int)(size)(Enum)(type)(Uint)(relativeoffset)) \
    M(VertexAttribLFormat,                                   void,          (Uint)(attribindex)(Int)(size)(Enum)(type)(Uint)(relativeoffset)) \
    M(VertexBindingDivisor,                                  void,          (Uint)(bindingindex)(Uint)(divisor)) \
    M(VertexBlendARB,                                        void,          (Int)(count)) \
    M(WeightPointerARB,                                      void,          (Int)(size)(Enum)(type)(Isize)(stride)(void*)(pointer)) \
    M(WeightbvARB,                                           void,          (Int)(size)(Byte*)(weights)) \
    M(WeightdvARB,                                           void,          (Int)(size)(Double*)(weights)) \
    M(WeightfvARB,                                           void,          (Int)(size)(Float*)(weights)) \
    M(WeightivARB,                                           void,          (Int)(size)(Int*)(weights)) \
    M(WeightsvARB,                                           void,          (Int)(size)(Short*)(weights)) \
    M(WeightubvARB,                                          void,          (Int)(size)(Ubyte*)(weights)) \
    M(WeightuivARB,                                          void,          (Int)(size)(Uint*)(weights)) \
    M(WeightusvARB,                                          void,          (Int)(size)(Ushort*)(weights)) \
    M(BindBufferARB,                                         void,          (Enum)(target)(Uint)(buffer)) \
    M(BufferDataARB,                                         void,          (Enum)(target)(IsizePtr)(size)(const void*)(data)(Enum)(usage)) \
    M(BufferSubDataARB,                                      void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(size)(const void*)(data)) \
    M(DeleteBuffersARB,                                      void,          (Isize)(n)(const Uint*)(buffers)) \
    M(GenBuffersARB,                                         void,          (Isize)(n)(Uint*)(buffers)) \
    M(GetBufferParameterivARB,                               void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetBufferPointervARB,                                  void,          (Enum)(target)(Enum)(pname)(void**)(params)) \
    M(GetBufferSubDataARB,                                   void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(size)(void*)(data)) \
    M(IsBufferARB,                                           Bool,          (Uint)(buffer)) \
    M(MapBufferARB,                                          void *,        (Enum)(target)(Enum)(access)) \
    M(UnmapBufferARB,                                        Bool,          (Enum)(target)) \
    M(BindProgramARB,                                        void,          (Enum)(target)(Uint)(program)) \
    M(DeleteProgramsARB,                                     void,          (Isize)(n)(const Uint*)(programs)) \
    M(DisableVertexAttribArrayARB,                           void,          (Uint)(index)) \
    M(EnableVertexAttribArrayARB,                            void,          (Uint)(index)) \
    M(GenProgramsARB,                                        void,          (Isize)(n)(Uint*)(programs)) \
    M(GetProgramEnvParameterdvARB,                           void,          (Enum)(target)(Uint)(index)(Double*)(params)) \
    M(GetProgramEnvParameterfvARB,                           void,          (Enum)(target)(Uint)(index)(Float*)(params)) \
    M(GetProgramLocalParameterdvARB,                         void,          (Enum)(target)(Uint)(index)(Double*)(params)) \
    M(GetProgramLocalParameterfvARB,                         void,          (Enum)(target)(Uint)(index)(Float*)(params)) \
    M(GetProgramStringARB,                                   void,          (Enum)(target)(Enum)(pname)(void*)(string)) \
    M(GetProgramivARB,                                       void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetVertexAttribPointervARB,                            void,          (Uint)(index)(Enum)(pname)(void**)(pointer)) \
    M(GetVertexAttribdvARB,                                  void,          (Uint)(index)(Enum)(pname)(Double*)(params)) \
    M(GetVertexAttribfvARB,                                  void,          (Uint)(index)(Enum)(pname)(Float*)(params)) \
    M(GetVertexAttribivARB,                                  void,          (Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(IsProgramARB,                                          Bool,          (Uint)(program)) \
    M(ProgramEnvParameter4dARB,                              void,          (Enum)(target)(Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(ProgramEnvParameter4dvARB,                             void,          (Enum)(target)(Uint)(index)(const Double*)(params)) \
    M(ProgramEnvParameter4fARB,                              void,          (Enum)(target)(Uint)(index)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(ProgramEnvParameter4fvARB,                             void,          (Enum)(target)(Uint)(index)(const Float*)(params)) \
    M(ProgramLocalParameter4dARB,                            void,          (Enum)(target)(Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(ProgramLocalParameter4dvARB,                           void,          (Enum)(target)(Uint)(index)(const Double*)(params)) \
    M(ProgramLocalParameter4fARB,                            void,          (Enum)(target)(Uint)(index)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(ProgramLocalParameter4fvARB,                           void,          (Enum)(target)(Uint)(index)(const Float*)(params)) \
    M(ProgramStringARB,                                      void,          (Enum)(target)(Enum)(format)(Isize)(len)(const void*)(string)) \
    M(VertexAttrib1dARB,                                     void,          (Uint)(index)(Double)(x)) \
    M(VertexAttrib1dvARB,                                    void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib1fARB,                                     void,          (Uint)(index)(Float)(x)) \
    M(VertexAttrib1fvARB,                                    void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib1sARB,                                     void,          (Uint)(index)(Short)(x)) \
    M(VertexAttrib1svARB,                                    void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib2dARB,                                     void,          (Uint)(index)(Double)(x)(Double)(y)) \
    M(VertexAttrib2dvARB,                                    void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib2fARB,                                     void,          (Uint)(index)(Float)(x)(Float)(y)) \
    M(VertexAttrib2fvARB,                                    void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib2sARB,                                     void,          (Uint)(index)(Short)(x)(Short)(y)) \
    M(VertexAttrib2svARB,                                    void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib3dARB,                                     void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)) \
    M(VertexAttrib3dvARB,                                    void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib3fARB,                                     void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(z)) \
    M(VertexAttrib3fvARB,                                    void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib3sARB,                                     void,          (Uint)(index)(Short)(x)(Short)(y)(Short)(z)) \
    M(VertexAttrib3svARB,                                    void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4NbvARB,                                   void,          (Uint)(index)(const Byte*)(v)) \
    M(VertexAttrib4NivARB,                                   void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttrib4NsvARB,                                   void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4NubARB,                                   void,          (Uint)(index)(Ubyte)(x)(Ubyte)(y)(Ubyte)(z)(Ubyte)(w)) \
    M(VertexAttrib4NubvARB,                                  void,          (Uint)(index)(const Ubyte*)(v)) \
    M(VertexAttrib4NuivARB,                                  void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttrib4NusvARB,                                  void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttrib4bvARB,                                    void,          (Uint)(index)(const Byte*)(v)) \
    M(VertexAttrib4dARB,                                     void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(VertexAttrib4dvARB,                                    void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib4fARB,                                     void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(VertexAttrib4fvARB,                                    void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib4ivARB,                                    void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttrib4sARB,                                     void,          (Uint)(index)(Short)(x)(Short)(y)(Short)(z)(Short)(w)) \
    M(VertexAttrib4svARB,                                    void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4ubvARB,                                   void,          (Uint)(index)(const Ubyte*)(v)) \
    M(VertexAttrib4uivARB,                                   void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttrib4usvARB,                                   void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttribPointerARB,                                void,          (Uint)(index)(Int)(size)(Enum)(type)(Bool)(normalized)(Isize)(stride)(const void*)(pointer)) \
    M(BindAttribLocationARB,                                 void,          (Handle)(programObj)(Uint)(index)(const char*)(name)) \
    M(GetActiveAttribARB,                                    void,          (Handle)(programObj)(Uint)(index)(Isize)(maxLength)(Isize*)(length)(Int*)(size)(Enum*)(type)(char*)(name)) \
    M(GetAttribLocationARB,                                  Int,           (Handle)(programObj)(const char*)(name)) \
    M(ColorP3ui,                                             void,          (Enum)(type)(Uint)(color)) \
    M(ColorP3uiv,                                            void,          (Enum)(type)(const Uint*)(color)) \
    M(ColorP4ui,                                             void,          (Enum)(type)(Uint)(color)) \
    M(ColorP4uiv,                                            void,          (Enum)(type)(const Uint*)(color)) \
    M(MultiTexCoordP1ui,                                     void,          (Enum)(texture)(Enum)(type)(Uint)(coords)) \
    M(MultiTexCoordP1uiv,                                    void,          (Enum)(texture)(Enum)(type)(const Uint*)(coords)) \
    M(MultiTexCoordP2ui,                                     void,          (Enum)(texture)(Enum)(type)(Uint)(coords)) \
    M(MultiTexCoordP2uiv,                                    void,          (Enum)(texture)(Enum)(type)(const Uint*)(coords)) \
    M(MultiTexCoordP3ui,                                     void,          (Enum)(texture)(Enum)(type)(Uint)(coords)) \
    M(MultiTexCoordP3uiv,                                    void,          (Enum)(texture)(Enum)(type)(const Uint*)(coords)) \
    M(MultiTexCoordP4ui,                                     void,          (Enum)(texture)(Enum)(type)(Uint)(coords)) \
    M(MultiTexCoordP4uiv,                                    void,          (Enum)(texture)(Enum)(type)(const Uint*)(coords)) \
    M(NormalP3ui,                                            void,          (Enum)(type)(Uint)(coords)) \
    M(NormalP3uiv,                                           void,          (Enum)(type)(const Uint*)(coords)) \
    M(SecondaryColorP3ui,                                    void,          (Enum)(type)(Uint)(color)) \
    M(SecondaryColorP3uiv,                                   void,          (Enum)(type)(const Uint*)(color)) \
    M(TexCoordP1ui,                                          void,          (Enum)(type)(Uint)(coords)) \
    M(TexCoordP1uiv,                                         void,          (Enum)(type)(const Uint*)(coords)) \
    M(TexCoordP2ui,                                          void,          (Enum)(type)(Uint)(coords)) \
    M(TexCoordP2uiv,                                         void,          (Enum)(type)(const Uint*)(coords)) \
    M(TexCoordP3ui,                                          void,          (Enum)(type)(Uint)(coords)) \
    M(TexCoordP3uiv,                                         void,          (Enum)(type)(const Uint*)(coords)) \
    M(TexCoordP4ui,                                          void,          (Enum)(type)(Uint)(coords)) \
    M(TexCoordP4uiv,                                         void,          (Enum)(type)(const Uint*)(coords)) \
    M(VertexAttribP1ui,                                      void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(Uint)(value)) \
    M(VertexAttribP1uiv,                                     void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(const Uint*)(value)) \
    M(VertexAttribP2ui,                                      void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(Uint)(value)) \
    M(VertexAttribP2uiv,                                     void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(const Uint*)(value)) \
    M(VertexAttribP3ui,                                      void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(Uint)(value)) \
    M(VertexAttribP3uiv,                                     void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(const Uint*)(value)) \
    M(VertexAttribP4ui,                                      void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(Uint)(value)) \
    M(VertexAttribP4uiv,                                     void,          (Uint)(index)(Enum)(type)(Bool)(normalized)(const Uint*)(value)) \
    M(VertexP2ui,                                            void,          (Enum)(type)(Uint)(value)) \
    M(VertexP2uiv,                                           void,          (Enum)(type)(const Uint*)(value)) \
    M(VertexP3ui,                                            void,          (Enum)(type)(Uint)(value)) \
    M(VertexP3uiv,                                           void,          (Enum)(type)(const Uint*)(value)) \
    M(VertexP4ui,                                            void,          (Enum)(type)(Uint)(value)) \
    M(VertexP4uiv,                                           void,          (Enum)(type)(const Uint*)(value)) \
    M(DepthRangeArrayv,                                      void,          (Uint)(first)(Isize)(count)(const DClamp *)(v)) \
    M(DepthRangeIndexed,                                     void,          (Uint)(index)(DClamp)(n)(DClamp)(f)) \
    M(GetDoublei_v,                                          void,          (Enum)(target)(Uint)(index)(Double*)(data)) \
    M(GetFloati_v,                                           void,          (Enum)(target)(Uint)(index)(Float*)(data)) \
    M(ScissorArrayv,                                         void,          (Uint)(first)(Isize)(count)(const Int *)(v)) \
    M(ScissorIndexed,                                        void,          (Uint)(index)(Int)(left)(Int)(bottom)(Isize)(width)(Isize)(height)) \
    M(ScissorIndexedv,                                       void,          (Uint)(index)(const Int *)(v)) \
    M(ViewportArrayv,                                        void,          (Uint)(first)(Isize)(count)(const Float *)(v)) \
    M(ViewportIndexedf,                                      void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(w)(Float)(h)) \
    M(ViewportIndexedfv,                                     void,          (Uint)(index)(const Float *)(v)) \
    M(WindowPos2dARB,                                        void,          (Double)(x)(Double)(y)) \
    M(WindowPos2dvARB,                                       void,          (const Double*)(p)) \
    M(WindowPos2fARB,                                        void,          (Float)(x)(Float)(y)) \
    M(WindowPos2fvARB,                                       void,          (const Float*)(p)) \
    M(WindowPos2iARB,                                        void,          (Int)(x)(Int)(y)) \
    M(WindowPos2ivARB,                                       void,          (const Int*)(p)) \
    M(WindowPos2sARB,                                        void,          (Short)(x)(Short)(y)) \
    M(WindowPos2svARB,                                       void,          (const Short*)(p)) \
    M(WindowPos3dARB,                                        void,          (Double)(x)(Double)(y)(Double)(z)) \
    M(WindowPos3dvARB,                                       void,          (const Double*)(p)) \
    M(WindowPos3fARB,                                        void,          (Float)(x)(Float)(y)(Float)(z)) \
    M(WindowPos3fvARB,                                       void,          (const Float*)(p)) \
    M(WindowPos3iARB,                                        void,          (Int)(x)(Int)(y)(Int)(z)) \
    M(WindowPos3ivARB,                                       void,          (const Int*)(p)) \
    M(WindowPos3sARB,                                        void,          (Short)(x)(Short)(y)(Short)(z)) \
    M(WindowPos3svARB,                                       void,          (const Short*)(p)) \
    M(DrawBuffersATI,                                        void,          (Isize)(n)(const Enum*)(bufs)) \
    M(DrawElementArrayATI,                                   void,          (Enum)(mode)(Isize)(count)) \
    M(DrawRangeElementArrayATI,                              void,          (Enum)(mode)(Uint)(start)(Uint)(end)(Isize)(count)) \
    M(ElementPointerATI,                                     void,          (Enum)(type)(const void*)(pointer)) \
    M(GetTexBumpParameterfvATI,                              void,          (Enum)(pname)(Float*)(param)) \
    M(GetTexBumpParameterivATI,                              void,          (Enum)(pname)(Int*)(param)) \
    M(TexBumpParameterfvATI,                                 void,          (Enum)(pname)(Float*)(param)) \
    M(TexBumpParameterivATI,                                 void,          (Enum)(pname)(Int*)(param)) \
    M(AlphaFragmentOp1ATI,                                   void,          (Enum)(op)(Uint)(dst)(Uint)(dstMod)(Uint)(arg1)(Uint)(arg1Rep)(Uint)(arg1Mod)) \
    M(AlphaFragmentOp2ATI,                                   void,          (Enum)(op)(Uint)(dst)(Uint)(dstMod)(Uint)(arg1)(Uint)(arg1Rep)(Uint)(arg1Mod)(Uint)(arg2)(Uint)(arg2Rep)(Uint)(arg2Mod)) \
    M(AlphaFragmentOp3ATI,                                   void,          (Enum)(op)(Uint)(dst)(Uint)(dstMod)(Uint)(arg1)(Uint)(arg1Rep)(Uint)(arg1Mod)(Uint)(arg2)(Uint)(arg2Rep)(Uint)(arg2Mod)(Uint)(arg3)(Uint)(arg3Rep)(Uint)(arg3Mod)) \
    M(BeginFragmentShaderATI,                                void,          ) \
    M(BindFragmentShaderATI,                                 void,          (Uint)(id)) \
    M(ColorFragmentOp1ATI,                                   void,          (Enum)(op)(Uint)(dst)(Uint)(dstMask)(Uint)(dstMod)(Uint)(arg1)(Uint)(arg1Rep)(Uint)(arg1Mod)) \
    M(ColorFragmentOp2ATI,                                   void,          (Enum)(op)(Uint)(dst)(Uint)(dstMask)(Uint)(dstMod)(Uint)(arg1)(Uint)(arg1Rep)(Uint)(arg1Mod)(Uint)(arg2)(Uint)(arg2Rep)(Uint)(arg2Mod)) \
    M(ColorFragmentOp3ATI,                                   void,          (Enum)(op)(Uint)(dst)(Uint)(dstMask)(Uint)(dstMod)(Uint)(arg1)(Uint)(arg1Rep)(Uint)(arg1Mod)(Uint)(arg2)(Uint)(arg2Rep)(Uint)(arg2Mod)(Uint)(arg3)(Uint)(arg3Rep)(Uint)(arg3Mod)) \
    M(DeleteFragmentShaderATI,                               void,          (Uint)(id)) \
    M(EndFragmentShaderATI,                                  void,          ) \
    M(GenFragmentShadersATI,                                 Uint,          (Uint)(range)) \
    M(PassTexCoordATI,                                       void,          (Uint)(dst)(Uint)(coord)(Enum)(swizzle)) \
    M(SampleMapATI,                                          void,          (Uint)(dst)(Uint)(interp)(Enum)(swizzle)) \
    M(SetFragmentShaderConstantATI,                          void,          (Uint)(dst)(const Float*)(value)) \
    M(MapObjectBufferATI,                                    void *,        (Uint)(buffer)) \
    M(UnmapObjectBufferATI,                                  void,          (Uint)(buffer)) \
    M(PNTrianglesfATI,                                       void,          (Enum)(pname)(Float)(param)) \
    M(PNTrianglesiATI,                                       void,          (Enum)(pname)(Int)(param)) \
    M(StencilFuncSeparateATI,                                void,          (Enum)(frontfunc)(Enum)(backfunc)(Int)(ref)(Uint)(mask)) \
    M(StencilOpSeparateATI,                                  void,          (Enum)(face)(Enum)(sfail)(Enum)(dpfail)(Enum)(dppass)) \
    M(ArrayObjectATI,                                        void,          (Enum)(array)(Int)(size)(Enum)(type)(Isize)(stride)(Uint)(buffer)(Uint)(offset)) \
    M(FreeObjectBufferATI,                                   void,          (Uint)(buffer)) \
    M(GetArrayObjectfvATI,                                   void,          (Enum)(array)(Enum)(pname)(Float*)(params)) \
    M(GetArrayObjectivATI,                                   void,          (Enum)(array)(Enum)(pname)(Int*)(params)) \
    M(GetObjectBufferfvATI,                                  void,          (Uint)(buffer)(Enum)(pname)(Float*)(params)) \
    M(GetObjectBufferivATI,                                  void,          (Uint)(buffer)(Enum)(pname)(Int*)(params)) \
    M(GetVariantArrayObjectfvATI,                            void,          (Uint)(id)(Enum)(pname)(Float*)(params)) \
    M(GetVariantArrayObjectivATI,                            void,          (Uint)(id)(Enum)(pname)(Int*)(params)) \
    M(IsObjectBufferATI,                                     Bool,          (Uint)(buffer)) \
    M(NewObjectBufferATI,                                    Uint,          (Isize)(size)(const void*)(pointer)(Enum)(usage)) \
    M(UpdateObjectBufferATI,                                 void,          (Uint)(buffer)(Uint)(offset)(Isize)(size)(const void*)(pointer)(Enum)(preserve)) \
    M(VariantArrayObjectATI,                                 void,          (Uint)(id)(Enum)(type)(Isize)(stride)(Uint)(buffer)(Uint)(offset)) \
    M(GetVertexAttribArrayObjectfvATI,                       void,          (Uint)(index)(Enum)(pname)(Float*)(params)) \
    M(GetVertexAttribArrayObjectivATI,                       void,          (Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(VertexAttribArrayObjectATI,                            void,          (Uint)(index)(Int)(size)(Enum)(type)(Bool)(normalized)(Isize)(stride)(Uint)(buffer)(Uint)(offset)) \
    M(ClientActiveVertexStreamATI,                           void,          (Enum)(stream)) \
    M(NormalStream3bATI,                                     void,          (Enum)(stream)(Byte)(x)(Byte)(y)(Byte)(z)) \
    M(NormalStream3bvATI,                                    void,          (Enum)(stream)(const Byte*)(coords)) \
    M(NormalStream3dATI,                                     void,          (Enum)(stream)(Double)(x)(Double)(y)(Double)(z)) \
    M(NormalStream3dvATI,                                    void,          (Enum)(stream)(const Double*)(coords)) \
    M(NormalStream3fATI,                                     void,          (Enum)(stream)(Float)(x)(Float)(y)(Float)(z)) \
    M(NormalStream3fvATI,                                    void,          (Enum)(stream)(const Float*)(coords)) \
    M(NormalStream3iATI,                                     void,          (Enum)(stream)(Int)(x)(Int)(y)(Int)(z)) \
    M(NormalStream3ivATI,                                    void,          (Enum)(stream)(const Int*)(coords)) \
    M(NormalStream3sATI,                                     void,          (Enum)(stream)(Short)(x)(Short)(y)(Short)(z)) \
    M(NormalStream3svATI,                                    void,          (Enum)(stream)(const Short*)(coords)) \
    M(VertexBlendEnvfATI,                                    void,          (Enum)(pname)(Float)(param)) \
    M(VertexBlendEnviATI,                                    void,          (Enum)(pname)(Int)(param)) \
    M(VertexStream1dATI,                                     void,          (Enum)(stream)(Double)(x)) \
    M(VertexStream1dvATI,                                    void,          (Enum)(stream)(const Double*)(coords)) \
    M(VertexStream1fATI,                                     void,          (Enum)(stream)(Float)(x)) \
    M(VertexStream1fvATI,                                    void,          (Enum)(stream)(const Float*)(coords)) \
    M(VertexStream1iATI,                                     void,          (Enum)(stream)(Int)(x)) \
    M(VertexStream1ivATI,                                    void,          (Enum)(stream)(const Int*)(coords)) \
    M(VertexStream1sATI,                                     void,          (Enum)(stream)(Short)(x)) \
    M(VertexStream1svATI,                                    void,          (Enum)(stream)(const Short*)(coords)) \
    M(VertexStream2dATI,                                     void,          (Enum)(stream)(Double)(x)(Double)(y)) \
    M(VertexStream2dvATI,                                    void,          (Enum)(stream)(const Double*)(coords)) \
    M(VertexStream2fATI,                                     void,          (Enum)(stream)(Float)(x)(Float)(y)) \
    M(VertexStream2fvATI,                                    void,          (Enum)(stream)(const Float*)(coords)) \
    M(VertexStream2iATI,                                     void,          (Enum)(stream)(Int)(x)(Int)(y)) \
    M(VertexStream2ivATI,                                    void,          (Enum)(stream)(const Int*)(coords)) \
    M(VertexStream2sATI,                                     void,          (Enum)(stream)(Short)(x)(Short)(y)) \
    M(VertexStream2svATI,                                    void,          (Enum)(stream)(const Short*)(coords)) \
    M(VertexStream3dATI,                                     void,          (Enum)(stream)(Double)(x)(Double)(y)(Double)(z)) \
    M(VertexStream3dvATI,                                    void,          (Enum)(stream)(const Double*)(coords)) \
    M(VertexStream3fATI,                                     void,          (Enum)(stream)(Float)(x)(Float)(y)(Float)(z)) \
    M(VertexStream3fvATI,                                    void,          (Enum)(stream)(const Float*)(coords)) \
    M(VertexStream3iATI,                                     void,          (Enum)(stream)(Int)(x)(Int)(y)(Int)(z)) \
    M(VertexStream3ivATI,                                    void,          (Enum)(stream)(const Int*)(coords)) \
    M(VertexStream3sATI,                                     void,          (Enum)(stream)(Short)(x)(Short)(y)(Short)(z)) \
    M(VertexStream3svATI,                                    void,          (Enum)(stream)(const Short*)(coords)) \
    M(VertexStream4dATI,                                     void,          (Enum)(stream)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(VertexStream4dvATI,                                    void,          (Enum)(stream)(const Double*)(coords)) \
    M(VertexStream4fATI,                                     void,          (Enum)(stream)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(VertexStream4fvATI,                                    void,          (Enum)(stream)(const Float*)(coords)) \
    M(VertexStream4iATI,                                     void,          (Enum)(stream)(Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(VertexStream4ivATI,                                    void,          (Enum)(stream)(const Int*)(coords)) \
    M(VertexStream4sATI,                                     void,          (Enum)(stream)(Short)(x)(Short)(y)(Short)(z)(Short)(w)) \
    M(VertexStream4svATI,                                    void,          (Enum)(stream)(const Short*)(coords)) \
    M(DrawArraysInstancedBaseInstanceEXT,                    void,          (Enum)(mode)(Int)(first)(Isize)(count)(Isize)(instancecount)(Uint)(baseinstance)) \
    M(DrawElementsInstancedBaseInstanceEXT,                  void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(instancecount)(Uint)(baseinstance)) \
    M(DrawElementsInstancedBaseVertexBaseInstanceEXT,        void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(instancecount)(Int)(basevertex)(Uint)(baseinstance)) \
    M(GetUniformBufferSizeEXT,                               Int,           (Uint)(program)(Int)(location)) \
    M(GetUniformOffsetEXT,                                   IntPtr,        (Uint)(program)(Int)(location)) \
    M(UniformBufferEXT,                                      void,          (Uint)(program)(Int)(location)(Uint)(buffer)) \
    M(BlendColorEXT,                                         void,          (FClamp)(red)(FClamp)(green)(FClamp)(blue)(FClamp)(alpha)) \
    M(BlendEquationSeparateEXT,                              void,          (Enum)(modeRGB)(Enum)(modeAlpha)) \
    M(BindFragDataLocationIndexedEXT,                        void,          (Uint)(program)(Uint)(colorNumber)(Uint)(index)(const char *)(name)) \
    M(GetFragDataIndexEXT,                                   Int,           (Uint)(program)(const char *)(name)) \
    M(GetProgramResourceLocationIndexEXT,                    Int,           (Uint)(program)(Enum)(programInterface)(const char*)(name)) \
    M(BlendFuncSeparateEXT,                                  void,          (Enum)(sfactorRGB)(Enum)(dfactorRGB)(Enum)(sfactorAlpha)(Enum)(dfactorAlpha)) \
    M(BlendEquationEXT,                                      void,          (Enum)(mode)) \
    M(BufferStorageEXT,                                      void,          (Enum)(target)(IsizePtr)(size)(const void*)(data)(Bitfield)(flags)) \
    M(NamedBufferStorageEXT,                                 void,          (Uint)(buffer)(IsizePtr)(size)(const void*)(data)(Bitfield)(flags)) \
    M(ClearTexImageEXT,                                      void,          (Uint)(texture)(Int)(level)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ClearTexSubImageEXT,                                   void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(ColorSubTableEXT,                                      void,          (Enum)(target)(Isize)(start)(Isize)(count)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(CopyColorSubTableEXT,                                  void,          (Enum)(target)(Isize)(start)(Int)(x)(Int)(y)(Isize)(width)) \
    M(LockArraysEXT,                                         void,          (Int)(first)(Isize)(count)) \
    M(UnlockArraysEXT,                                       void,          ) \
    M(ConvolutionFilter1DEXT,                                void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(image)) \
    M(ConvolutionFilter2DEXT,                                void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(image)) \
    M(ConvolutionParameterfEXT,                              void,          (Enum)(target)(Enum)(pname)(Float)(param)) \
    M(ConvolutionParameterfvEXT,                             void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(ConvolutionParameteriEXT,                              void,          (Enum)(target)(Enum)(pname)(Int)(param)) \
    M(ConvolutionParameterivEXT,                             void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(CopyConvolutionFilter1DEXT,                            void,          (Enum)(target)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyConvolutionFilter2DEXT,                            void,          (Enum)(target)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(GetConvolutionFilterEXT,                               void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(image)) \
    M(GetConvolutionParameterfvEXT,                          void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetConvolutionParameterivEXT,                          void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetSeparableFilterEXT,                                 void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(row)(void*)(column)(void*)(span)) \
    M(SeparableFilter2DEXT,                                  void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(row)(const void*)(column)) \
    M(BinormalPointerEXT,                                    void,          (Enum)(type)(Isize)(stride)(void*)(pointer)) \
    M(TangentPointerEXT,                                     void,          (Enum)(type)(Isize)(stride)(void*)(pointer)) \
    M(CopyImageSubDataEXT,                                   void,          (Uint)(srcName)(Enum)(srcTarget)(Int)(srcLevel)(Int)(srcX)(Int)(srcY)(Int)(srcZ)(Uint)(dstName)(Enum)(dstTarget)(Int)(dstLevel)(Int)(dstX)(Int)(dstY)(Int)(dstZ)(Isize)(srcWidth)(Isize)(srcHeight)(Isize)(srcDepth)) \
    M(CopyTexImage1DEXT,                                     void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Int)(border)) \
    M(CopyTexImage2DEXT,                                     void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Int)(border)) \
    M(CopyTexSubImage1DEXT,                                  void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyTexSubImage2DEXT,                                  void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CopyTexSubImage3DEXT,                                  void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CullParameterdvEXT,                                    void,          (Enum)(pname)(Double*)(params)) \
    M(CullParameterfvEXT,                                    void,          (Enum)(pname)(Float*)(params)) \
    M(GetObjectLabelEXT,                                     void,          (Enum)(type)(Uint)(object)(Isize)(bufSize)(Isize*)(length)(char*)(label)) \
    M(LabelObjectEXT,                                        void,          (Enum)(type)(Uint)(object)(Isize)(length)(const char*)(label)) \
    M(InsertEventMarkerEXT,                                  void,          (Isize)(length)(const char*)(marker)) \
    M(PopGroupMarkerEXT,                                     void,          ) \
    M(PushGroupMarkerEXT,                                    void,          (Isize)(length)(const char*)(marker)) \
    M(DepthBoundsEXT,                                        void,          (DClamp)(zmin)(DClamp)(zmax)) \
    M(BindMultiTextureEXT,                                   void,          (Enum)(texunit)(Enum)(target)(Uint)(texture)) \
    M(CheckNamedFramebufferStatusEXT,                        Enum,          (Uint)(framebuffer)(Enum)(target)) \
    M(ClientAttribDefaultEXT,                                void,          (Bitfield)(mask)) \
    M(CompressedMultiTexImage1DEXT,                          void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedMultiTexImage2DEXT,                          void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedMultiTexImage3DEXT,                          void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedMultiTexSubImage1DEXT,                       void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedMultiTexSubImage2DEXT,                       void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedMultiTexSubImage3DEXT,                       void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureImage1DEXT,                           void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureImage2DEXT,                           void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureImage3DEXT,                           void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureSubImage1DEXT,                        void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureSubImage2DEXT,                        void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTextureSubImage3DEXT,                        void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CopyMultiTexImage1DEXT,                                void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Int)(border)) \
    M(CopyMultiTexImage2DEXT,                                void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Int)(border)) \
    M(CopyMultiTexSubImage1DEXT,                             void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyMultiTexSubImage2DEXT,                             void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CopyMultiTexSubImage3DEXT,                             void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CopyTextureImage1DEXT,                                 void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Int)(border)) \
    M(CopyTextureImage2DEXT,                                 void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Int)(border)) \
    M(CopyTextureSubImage1DEXT,                              void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(x)(Int)(y)(Isize)(width)) \
    M(CopyTextureSubImage2DEXT,                              void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(CopyTextureSubImage3DEXT,                              void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(DisableClientStateIndexedEXT,                          void,          (Enum)(array)(Uint)(index)) \
    M(DisableClientStateiEXT,                                void,          (Enum)(array)(Uint)(index)) \
    M(DisableVertexArrayAttribEXT,                           void,          (Uint)(vaobj)(Uint)(index)) \
    M(DisableVertexArrayEXT,                                 void,          (Uint)(vaobj)(Enum)(array)) \
    M(EnableClientStateIndexedEXT,                           void,          (Enum)(array)(Uint)(index)) \
    M(EnableClientStateiEXT,                                 void,          (Enum)(array)(Uint)(index)) \
    M(EnableVertexArrayAttribEXT,                            void,          (Uint)(vaobj)(Uint)(index)) \
    M(EnableVertexArrayEXT,                                  void,          (Uint)(vaobj)(Enum)(array)) \
    M(FlushMappedNamedBufferRangeEXT,                        void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(length)) \
    M(FramebufferDrawBufferEXT,                              void,          (Uint)(framebuffer)(Enum)(mode)) \
    M(FramebufferDrawBuffersEXT,                             void,          (Uint)(framebuffer)(Isize)(n)(const Enum*)(bufs)) \
    M(FramebufferReadBufferEXT,                              void,          (Uint)(framebuffer)(Enum)(mode)) \
    M(GenerateMultiTexMipmapEXT,                             void,          (Enum)(texunit)(Enum)(target)) \
    M(GenerateTextureMipmapEXT,                              void,          (Uint)(texture)(Enum)(target)) \
    M(GetCompressedMultiTexImageEXT,                         void,          (Enum)(texunit)(Enum)(target)(Int)(level)(void*)(img)) \
    M(GetCompressedTextureImageEXT,                          void,          (Uint)(texture)(Enum)(target)(Int)(level)(void*)(img)) \
    M(GetDoubleIndexedvEXT,                                  void,          (Enum)(target)(Uint)(index)(Double*)(params)) \
    M(GetDoublei_vEXT,                                       void,          (Enum)(pname)(Uint)(index)(Double*)(params)) \
    M(GetFloatIndexedvEXT,                                   void,          (Enum)(target)(Uint)(index)(Float*)(params)) \
    M(GetFloati_vEXT,                                        void,          (Enum)(pname)(Uint)(index)(Float*)(params)) \
    M(GetFramebufferParameterivEXT,                          void,          (Uint)(framebuffer)(Enum)(pname)(Int*)(param)) \
    M(GetMultiTexEnvfvEXT,                                   void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetMultiTexEnvivEXT,                                   void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetMultiTexGendvEXT,                                   void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(Double*)(params)) \
    M(GetMultiTexGenfvEXT,                                   void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(Float*)(params)) \
    M(GetMultiTexGenivEXT,                                   void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(Int*)(params)) \
    M(GetMultiTexImageEXT,                                   void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(format)(Enum)(type)(void*)(pixels)) \
    M(GetMultiTexLevelParameterfvEXT,                        void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(pname)(Float*)(params)) \
    M(GetMultiTexLevelParameterivEXT,                        void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Enum)(pname)(Int*)(params)) \
    M(GetMultiTexParameterIivEXT,                            void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetMultiTexParameterIuivEXT,                           void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Uint*)(params)) \
    M(GetMultiTexParameterfvEXT,                             void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetMultiTexParameterivEXT,                             void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetNamedBufferParameterivEXT,                          void,          (Uint)(buffer)(Enum)(pname)(Int*)(params)) \
    M(GetNamedBufferPointervEXT,                             void,          (Uint)(buffer)(Enum)(pname)(void**)(params)) \
    M(GetNamedBufferSubDataEXT,                              void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)(void*)(data)) \
    M(GetNamedFramebufferAttachmentParameterivEXT,           void,          (Uint)(framebuffer)(Enum)(attachment)(Enum)(pname)(Int*)(params)) \
    M(GetNamedProgramLocalParameterIivEXT,                   void,          (Uint)(program)(Enum)(target)(Uint)(index)(Int*)(params)) \
    M(GetNamedProgramLocalParameterIuivEXT,                  void,          (Uint)(program)(Enum)(target)(Uint)(index)(Uint*)(params)) \
    M(GetNamedProgramLocalParameterdvEXT,                    void,          (Uint)(program)(Enum)(target)(Uint)(index)(Double*)(params)) \
    M(GetNamedProgramLocalParameterfvEXT,                    void,          (Uint)(program)(Enum)(target)(Uint)(index)(Float*)(params)) \
    M(GetNamedProgramStringEXT,                              void,          (Uint)(program)(Enum)(target)(Enum)(pname)(void*)(string)) \
    M(GetNamedProgramivEXT,                                  void,          (Uint)(program)(Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetNamedRenderbufferParameterivEXT,                    void,          (Uint)(renderbuffer)(Enum)(pname)(Int*)(params)) \
    M(GetPointerIndexedvEXT,                                 void,          (Enum)(target)(Uint)(index)(void**)(params)) \
    M(GetPointeri_vEXT,                                      void,          (Enum)(pname)(Uint)(index)(void**)(params)) \
    M(GetTextureImageEXT,                                    void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(format)(Enum)(type)(void*)(pixels)) \
    M(GetTextureLevelParameterfvEXT,                         void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(pname)(Float*)(params)) \
    M(GetTextureLevelParameterivEXT,                         void,          (Uint)(texture)(Enum)(target)(Int)(level)(Enum)(pname)(Int*)(params)) \
    M(GetTextureParameterIivEXT,                             void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetTextureParameterIuivEXT,                            void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(Uint*)(params)) \
    M(GetTextureParameterfvEXT,                              void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetTextureParameterivEXT,                              void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetVertexArrayIntegeri_vEXT,                           void,          (Uint)(vaobj)(Uint)(index)(Enum)(pname)(Int*)(param)) \
    M(GetVertexArrayIntegervEXT,                             void,          (Uint)(vaobj)(Enum)(pname)(Int*)(param)) \
    M(GetVertexArrayPointeri_vEXT,                           void,          (Uint)(vaobj)(Uint)(index)(Enum)(pname)(void**)(param)) \
    M(GetVertexArrayPointervEXT,                             void,          (Uint)(vaobj)(Enum)(pname)(void**)(param)) \
    M(MapNamedBufferEXT,                                     void *,        (Uint)(buffer)(Enum)(access)) \
    M(MapNamedBufferRangeEXT,                                void *,        (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(length)(Bitfield)(access)) \
    M(MatrixFrustumEXT,                                      void,          (Enum)(matrixMode)(Double)(l)(Double)(r)(Double)(b)(Double)(t)(Double)(n)(Double)(f)) \
    M(MatrixLoadIdentityEXT,                                 void,          (Enum)(matrixMode)) \
    M(MatrixLoadTransposedEXT,                               void,          (Enum)(matrixMode)(const Double*)(m)) \
    M(MatrixLoadTransposefEXT,                               void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixLoaddEXT,                                        void,          (Enum)(matrixMode)(const Double*)(m)) \
    M(MatrixLoadfEXT,                                        void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixMultTransposedEXT,                               void,          (Enum)(matrixMode)(const Double*)(m)) \
    M(MatrixMultTransposefEXT,                               void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixMultdEXT,                                        void,          (Enum)(matrixMode)(const Double*)(m)) \
    M(MatrixMultfEXT,                                        void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixOrthoEXT,                                        void,          (Enum)(matrixMode)(Double)(l)(Double)(r)(Double)(b)(Double)(t)(Double)(n)(Double)(f)) \
    M(MatrixPopEXT,                                          void,          (Enum)(matrixMode)) \
    M(MatrixPushEXT,                                         void,          (Enum)(matrixMode)) \
    M(MatrixRotatedEXT,                                      void,          (Enum)(matrixMode)(Double)(angle)(Double)(x)(Double)(y)(Double)(z)) \
    M(MatrixRotatefEXT,                                      void,          (Enum)(matrixMode)(Float)(angle)(Float)(x)(Float)(y)(Float)(z)) \
    M(MatrixScaledEXT,                                       void,          (Enum)(matrixMode)(Double)(x)(Double)(y)(Double)(z)) \
    M(MatrixScalefEXT,                                       void,          (Enum)(matrixMode)(Float)(x)(Float)(y)(Float)(z)) \
    M(MatrixTranslatedEXT,                                   void,          (Enum)(matrixMode)(Double)(x)(Double)(y)(Double)(z)) \
    M(MatrixTranslatefEXT,                                   void,          (Enum)(matrixMode)(Float)(x)(Float)(y)(Float)(z)) \
    M(MultiTexBufferEXT,                                     void,          (Enum)(texunit)(Enum)(target)(Enum)(internalformat)(Uint)(buffer)) \
    M(MultiTexCoordPointerEXT,                               void,          (Enum)(texunit)(Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(MultiTexEnvfEXT,                                       void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Float)(param)) \
    M(MultiTexEnvfvEXT,                                      void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(MultiTexEnviEXT,                                       void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Int)(param)) \
    M(MultiTexEnvivEXT,                                      void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(MultiTexGendEXT,                                       void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(Double)(param)) \
    M(MultiTexGendvEXT,                                      void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(const Double*)(params)) \
    M(MultiTexGenfEXT,                                       void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(Float)(param)) \
    M(MultiTexGenfvEXT,                                      void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(const Float*)(params)) \
    M(MultiTexGeniEXT,                                       void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(Int)(param)) \
    M(MultiTexGenivEXT,                                      void,          (Enum)(texunit)(Enum)(coord)(Enum)(pname)(const Int*)(params)) \
    M(MultiTexImage1DEXT,                                    void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(MultiTexImage2DEXT,                                    void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Isize)(height)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(MultiTexImage3DEXT,                                    void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(MultiTexParameterIivEXT,                               void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(MultiTexParameterIuivEXT,                              void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(const Uint*)(params)) \
    M(MultiTexParameterfEXT,                                 void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Float)(param)) \
    M(MultiTexParameterfvEXT,                                void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(const Float*)(param)) \
    M(MultiTexParameteriEXT,                                 void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(Int)(param)) \
    M(MultiTexParameterivEXT,                                void,          (Enum)(texunit)(Enum)(target)(Enum)(pname)(const Int*)(param)) \
    M(MultiTexRenderbufferEXT,                               void,          (Enum)(texunit)(Enum)(target)(Uint)(renderbuffer)) \
    M(MultiTexSubImage1DEXT,                                 void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(MultiTexSubImage2DEXT,                                 void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(MultiTexSubImage3DEXT,                                 void,          (Enum)(texunit)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(NamedBufferDataEXT,                                    void,          (Uint)(buffer)(IsizePtr)(size)(const void*)(data)(Enum)(usage)) \
    M(NamedBufferSubDataEXT,                                 void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)(const void*)(data)) \
    M(NamedCopyBufferSubDataEXT,                             void,          (Uint)(readBuffer)(Uint)(writeBuffer)(IntPtr)(readOffset)(IntPtr)(writeOffset)(IsizePtr)(size)) \
    M(NamedFramebufferRenderbufferEXT,                       void,          (Uint)(framebuffer)(Enum)(attachment)(Enum)(renderbuffertarget)(Uint)(renderbuffer)) \
    M(NamedFramebufferTexture1DEXT,                          void,          (Uint)(framebuffer)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)) \
    M(NamedFramebufferTexture2DEXT,                          void,          (Uint)(framebuffer)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)) \
    M(NamedFramebufferTexture3DEXT,                          void,          (Uint)(framebuffer)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)(Int)(zoffset)) \
    M(NamedFramebufferTextureEXT,                            void,          (Uint)(framebuffer)(Enum)(attachment)(Uint)(texture)(Int)(level)) \
    M(NamedFramebufferTextureFaceEXT,                        void,          (Uint)(framebuffer)(Enum)(attachment)(Uint)(texture)(Int)(level)(Enum)(face)) \
    M(NamedFramebufferTextureLayerEXT,                       void,          (Uint)(framebuffer)(Enum)(attachment)(Uint)(texture)(Int)(level)(Int)(layer)) \
    M(NamedProgramLocalParameter4dEXT,                       void,          (Uint)(program)(Enum)(target)(Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(NamedProgramLocalParameter4dvEXT,                      void,          (Uint)(program)(Enum)(target)(Uint)(index)(const Double*)(params)) \
    M(NamedProgramLocalParameter4fEXT,                       void,          (Uint)(program)(Enum)(target)(Uint)(index)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(NamedProgramLocalParameter4fvEXT,                      void,          (Uint)(program)(Enum)(target)(Uint)(index)(const Float*)(params)) \
    M(NamedProgramLocalParameterI4iEXT,                      void,          (Uint)(program)(Enum)(target)(Uint)(index)(Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(NamedProgramLocalParameterI4ivEXT,                     void,          (Uint)(program)(Enum)(target)(Uint)(index)(const Int*)(params)) \
    M(NamedProgramLocalParameterI4uiEXT,                     void,          (Uint)(program)(Enum)(target)(Uint)(index)(Uint)(x)(Uint)(y)(Uint)(z)(Uint)(w)) \
    M(NamedProgramLocalParameterI4uivEXT,                    void,          (Uint)(program)(Enum)(target)(Uint)(index)(const Uint*)(params)) \
    M(NamedProgramLocalParameters4fvEXT,                     void,          (Uint)(program)(Enum)(target)(Uint)(index)(Isize)(count)(const Float*)(params)) \
    M(NamedProgramLocalParametersI4ivEXT,                    void,          (Uint)(program)(Enum)(target)(Uint)(index)(Isize)(count)(const Int*)(params)) \
    M(NamedProgramLocalParametersI4uivEXT,                   void,          (Uint)(program)(Enum)(target)(Uint)(index)(Isize)(count)(const Uint*)(params)) \
    M(NamedProgramStringEXT,                                 void,          (Uint)(program)(Enum)(target)(Enum)(format)(Isize)(len)(const void*)(string)) \
    M(NamedRenderbufferStorageEXT,                           void,          (Uint)(renderbuffer)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(NamedRenderbufferStorageMultisampleCoverageEXT,        void,          (Uint)(renderbuffer)(Isize)(coverageSamples)(Isize)(colorSamples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(NamedRenderbufferStorageMultisampleEXT,                void,          (Uint)(renderbuffer)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(ProgramUniform1fEXT,                                   void,          (Uint)(program)(Int)(location)(Float)(v0)) \
    M(ProgramUniform1fvEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform1iEXT,                                   void,          (Uint)(program)(Int)(location)(Int)(v0)) \
    M(ProgramUniform1ivEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform1uiEXT,                                  void,          (Uint)(program)(Int)(location)(Uint)(v0)) \
    M(ProgramUniform1uivEXT,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniform2fEXT,                                   void,          (Uint)(program)(Int)(location)(Float)(v0)(Float)(v1)) \
    M(ProgramUniform2fvEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform2iEXT,                                   void,          (Uint)(program)(Int)(location)(Int)(v0)(Int)(v1)) \
    M(ProgramUniform2ivEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform2uiEXT,                                  void,          (Uint)(program)(Int)(location)(Uint)(v0)(Uint)(v1)) \
    M(ProgramUniform2uivEXT,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniform3fEXT,                                   void,          (Uint)(program)(Int)(location)(Float)(v0)(Float)(v1)(Float)(v2)) \
    M(ProgramUniform3fvEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform3iEXT,                                   void,          (Uint)(program)(Int)(location)(Int)(v0)(Int)(v1)(Int)(v2)) \
    M(ProgramUniform3ivEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform3uiEXT,                                  void,          (Uint)(program)(Int)(location)(Uint)(v0)(Uint)(v1)(Uint)(v2)) \
    M(ProgramUniform3uivEXT,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniform4fEXT,                                   void,          (Uint)(program)(Int)(location)(Float)(v0)(Float)(v1)(Float)(v2)(Float)(v3)) \
    M(ProgramUniform4fvEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Float*)(value)) \
    M(ProgramUniform4iEXT,                                   void,          (Uint)(program)(Int)(location)(Int)(v0)(Int)(v1)(Int)(v2)(Int)(v3)) \
    M(ProgramUniform4ivEXT,                                  void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int*)(value)) \
    M(ProgramUniform4uiEXT,                                  void,          (Uint)(program)(Int)(location)(Uint)(v0)(Uint)(v1)(Uint)(v2)(Uint)(v3)) \
    M(ProgramUniform4uivEXT,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(ProgramUniformMatrix2fvEXT,                            void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix2x3fvEXT,                          void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix2x4fvEXT,                          void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix3fvEXT,                            void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix3x2fvEXT,                          void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix3x4fvEXT,                          void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix4fvEXT,                            void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix4x2fvEXT,                          void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(ProgramUniformMatrix4x3fvEXT,                          void,          (Uint)(program)(Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(PushClientAttribDefaultEXT,                            void,          (Bitfield)(mask)) \
    M(TextureBufferEXT,                                      void,          (Uint)(texture)(Enum)(target)(Enum)(internalformat)(Uint)(buffer)) \
    M(TextureImage1DEXT,                                     void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureImage2DEXT,                                     void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Isize)(height)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureImage3DEXT,                                     void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureParameterIivEXT,                                void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(TextureParameterIuivEXT,                               void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(const Uint*)(params)) \
    M(TextureParameterfEXT,                                  void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(Float)(param)) \
    M(TextureParameterfvEXT,                                 void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(const Float*)(param)) \
    M(TextureParameteriEXT,                                  void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(Int)(param)) \
    M(TextureParameterivEXT,                                 void,          (Uint)(texture)(Enum)(target)(Enum)(pname)(const Int*)(param)) \
    M(TextureRenderbufferEXT,                                void,          (Uint)(texture)(Enum)(target)(Uint)(renderbuffer)) \
    M(TextureSubImage1DEXT,                                  void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureSubImage2DEXT,                                  void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureSubImage3DEXT,                                  void,          (Uint)(texture)(Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(UnmapNamedBufferEXT,                                   Bool,          (Uint)(buffer)) \
    M(VertexArrayColorOffsetEXT,                             void,          (Uint)(vaobj)(Uint)(buffer)(Int)(size)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayEdgeFlagOffsetEXT,                          void,          (Uint)(vaobj)(Uint)(buffer)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayFogCoordOffsetEXT,                          void,          (Uint)(vaobj)(Uint)(buffer)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayIndexOffsetEXT,                             void,          (Uint)(vaobj)(Uint)(buffer)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayMultiTexCoordOffsetEXT,                     void,          (Uint)(vaobj)(Uint)(buffer)(Enum)(texunit)(Int)(size)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayNormalOffsetEXT,                            void,          (Uint)(vaobj)(Uint)(buffer)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArraySecondaryColorOffsetEXT,                    void,          (Uint)(vaobj)(Uint)(buffer)(Int)(size)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayTexCoordOffsetEXT,                          void,          (Uint)(vaobj)(Uint)(buffer)(Int)(size)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayVertexAttribDivisorEXT,                     void,          (Uint)(vaobj)(Uint)(index)(Uint)(divisor)) \
    M(VertexArrayVertexAttribIOffsetEXT,                     void,          (Uint)(vaobj)(Uint)(buffer)(Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayVertexAttribOffsetEXT,                      void,          (Uint)(vaobj)(Uint)(buffer)(Uint)(index)(Int)(size)(Enum)(type)(Bool)(normalized)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexArrayVertexOffsetEXT,                            void,          (Uint)(vaobj)(Uint)(buffer)(Int)(size)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(DiscardFramebufferEXT,                                 void,          (Enum)(target)(Isize)(numAttachments)(const Enum*)(attachments)) \
    M(DrawBuffersEXT,                                        void,          (Isize)(n)(const Enum*)(bufs)) \
    M(ColorMaskIndexedEXT,                                   void,          (Uint)(buf)(Bool)(r)(Bool)(g)(Bool)(b)(Bool)(a)) \
    M(DisableIndexedEXT,                                     void,          (Enum)(target)(Uint)(index)) \
    M(EnableIndexedEXT,                                      void,          (Enum)(target)(Uint)(index)) \
    M(GetBooleanIndexedvEXT,                                 void,          (Enum)(value)(Uint)(index)(Bool*)(data)) \
    M(GetIntegerIndexedvEXT,                                 void,          (Enum)(value)(Uint)(index)(Int*)(data)) \
    M(IsEnabledIndexedEXT,                                   Bool,          (Enum)(target)(Uint)(index)) \
    M(BlendEquationSeparateiEXT,                             void,          (Uint)(buf)(Enum)(modeRGB)(Enum)(modeAlpha)) \
    M(BlendEquationiEXT,                                     void,          (Uint)(buf)(Enum)(mode)) \
    M(BlendFuncSeparateiEXT,                                 void,          (Uint)(buf)(Enum)(srcRGB)(Enum)(dstRGB)(Enum)(srcAlpha)(Enum)(dstAlpha)) \
    M(BlendFunciEXT,                                         void,          (Uint)(buf)(Enum)(src)(Enum)(dst)) \
    M(ColorMaskiEXT,                                         void,          (Uint)(buf)(Bool)(r)(Bool)(g)(Bool)(b)(Bool)(a)) \
    M(DisableiEXT,                                           void,          (Enum)(target)(Uint)(index)) \
    M(EnableiEXT,                                            void,          (Enum)(target)(Uint)(index)) \
    M(IsEnablediEXT,                                         Bool,          (Enum)(target)(Uint)(index)) \
    M(DrawElementsBaseVertexEXT,                             void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Int)(basevertex)) \
    M(DrawElementsInstancedBaseVertexEXT,                    void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(instancecount)(Int)(basevertex)) \
    M(DrawRangeElementsBaseVertexEXT,                        void,          (Enum)(mode)(Uint)(start)(Uint)(end)(Isize)(count)(Enum)(type)(const void*)(indices)(Int)(basevertex)) \
    M(MultiDrawElementsBaseVertexEXT,                        void,          (Enum)(mode)(const Isize*)(count)(Enum)(type)(const void *const*)(indices)(Isize)(primcount)(const Int*)(basevertex)) \
    M(DrawArraysInstancedEXT,                                void,          (Enum)(mode)(Int)(start)(Isize)(count)(Isize)(primcount)) \
    M(DrawElementsInstancedEXT,                              void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)) \
    M(DrawRangeElementsEXT,                                  void,          (Enum)(mode)(Uint)(start)(Uint)(end)(Isize)(count)(Enum)(type)(const void*)(indices)) \
    M(BufferStorageExternalEXT,                              void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(size)(ClientBuffer)(clientBuffer)(Bitfield)(flags)) \
    M(NamedBufferStorageExternalEXT,                         void,          (Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)(ClientBuffer)(clientBuffer)(Bitfield)(flags)) \
    M(FogCoordPointerEXT,                                    void,          (Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(FogCoorddEXT,                                          void,          (Double)(coord)) \
    M(FogCoorddvEXT,                                         void,          (const Double*)(coord)) \
    M(FogCoordfEXT,                                          void,          (Float)(coord)) \
    M(FogCoordfvEXT,                                         void,          (const Float*)(coord)) \
    M(FragmentColorMaterialEXT,                              void,          (Enum)(face)(Enum)(mode)) \
    M(FragmentLightModelfEXT,                                void,          (Enum)(pname)(Float)(param)) \
    M(FragmentLightModelfvEXT,                               void,          (Enum)(pname)(Float*)(params)) \
    M(FragmentLightModeliEXT,                                void,          (Enum)(pname)(Int)(param)) \
    M(FragmentLightModelivEXT,                               void,          (Enum)(pname)(Int*)(params)) \
    M(FragmentLightfEXT,                                     void,          (Enum)(light)(Enum)(pname)(Float)(param)) \
    M(FragmentLightfvEXT,                                    void,          (Enum)(light)(Enum)(pname)(Float*)(params)) \
    M(FragmentLightiEXT,                                     void,          (Enum)(light)(Enum)(pname)(Int)(param)) \
    M(FragmentLightivEXT,                                    void,          (Enum)(light)(Enum)(pname)(Int*)(params)) \
    M(FragmentMaterialfEXT,                                  void,          (Enum)(face)(Enum)(pname)(const Float)(param)) \
    M(FragmentMaterialfvEXT,                                 void,          (Enum)(face)(Enum)(pname)(const Float*)(params)) \
    M(FragmentMaterialiEXT,                                  void,          (Enum)(face)(Enum)(pname)(const Int)(param)) \
    M(FragmentMaterialivEXT,                                 void,          (Enum)(face)(Enum)(pname)(const Int*)(params)) \
    M(GetFragmentLightfvEXT,                                 void,          (Enum)(light)(Enum)(pname)(Float*)(params)) \
    M(GetFragmentLightivEXT,                                 void,          (Enum)(light)(Enum)(pname)(Int*)(params)) \
    M(GetFragmentMaterialfvEXT,                              void,          (Enum)(face)(Enum)(pname)(const Float*)(params)) \
    M(GetFragmentMaterialivEXT,                              void,          (Enum)(face)(Enum)(pname)(const Int*)(params)) \
    M(LightEnviEXT,                                          void,          (Enum)(pname)(Int)(param)) \
    M(BlitFramebufferEXT,                                    void,          (Int)(srcX0)(Int)(srcY0)(Int)(srcX1)(Int)(srcY1)(Int)(dstX0)(Int)(dstY0)(Int)(dstX1)(Int)(dstY1)(Bitfield)(mask)(Enum)(filter)) \
    M(RenderbufferStorageMultisampleEXT,                     void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(BindFramebufferEXT,                                    void,          (Enum)(target)(Uint)(framebuffer)) \
    M(BindRenderbufferEXT,                                   void,          (Enum)(target)(Uint)(renderbuffer)) \
    M(CheckFramebufferStatusEXT,                             Enum,          (Enum)(target)) \
    M(DeleteFramebuffersEXT,                                 void,          (Isize)(n)(const Uint*)(framebuffers)) \
    M(DeleteRenderbuffersEXT,                                void,          (Isize)(n)(const Uint*)(renderbuffers)) \
    M(FramebufferRenderbufferEXT,                            void,          (Enum)(target)(Enum)(attachment)(Enum)(renderbuffertarget)(Uint)(renderbuffer)) \
    M(FramebufferTexture1DEXT,                               void,          (Enum)(target)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)) \
    M(FramebufferTexture2DEXT,                               void,          (Enum)(target)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)) \
    M(FramebufferTexture3DEXT,                               void,          (Enum)(target)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)(Int)(zoffset)) \
    M(GenFramebuffersEXT,                                    void,          (Isize)(n)(Uint*)(framebuffers)) \
    M(GenRenderbuffersEXT,                                   void,          (Isize)(n)(Uint*)(renderbuffers)) \
    M(GenerateMipmapEXT,                                     void,          (Enum)(target)) \
    M(GetFramebufferAttachmentParameterivEXT,                void,          (Enum)(target)(Enum)(attachment)(Enum)(pname)(Int*)(params)) \
    M(GetRenderbufferParameterivEXT,                         void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(IsFramebufferEXT,                                      Bool,          (Uint)(framebuffer)) \
    M(IsRenderbufferEXT,                                     Bool,          (Uint)(renderbuffer)) \
    M(RenderbufferStorageEXT,                                void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(FramebufferTextureEXT,                                 void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)) \
    M(FramebufferTextureFaceEXT,                             void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Enum)(face)) \
    M(ProgramParameteriEXT,                                  void,          (Uint)(program)(Enum)(pname)(Int)(value)) \
    M(ProgramEnvParameters4fvEXT,                            void,          (Enum)(target)(Uint)(index)(Isize)(count)(const Float*)(params)) \
    M(ProgramLocalParameters4fvEXT,                          void,          (Enum)(target)(Uint)(index)(Isize)(count)(const Float*)(params)) \
    M(BindFragDataLocationEXT,                               void,          (Uint)(program)(Uint)(color)(const char*)(name)) \
    M(GetFragDataLocationEXT,                                Int,           (Uint)(program)(const char*)(name)) \
    M(GetUniformuivEXT,                                      void,          (Uint)(program)(Int)(location)(Uint*)(params)) \
    M(GetVertexAttribIivEXT,                                 void,          (Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(GetVertexAttribIuivEXT,                                void,          (Uint)(index)(Enum)(pname)(Uint*)(params)) \
    M(Uniform1uiEXT,                                         void,          (Int)(location)(Uint)(v0)) \
    M(Uniform1uivEXT,                                        void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(Uniform2uiEXT,                                         void,          (Int)(location)(Uint)(v0)(Uint)(v1)) \
    M(Uniform2uivEXT,                                        void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(Uniform3uiEXT,                                         void,          (Int)(location)(Uint)(v0)(Uint)(v1)(Uint)(v2)) \
    M(Uniform3uivEXT,                                        void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(Uniform4uiEXT,                                         void,          (Int)(location)(Uint)(v0)(Uint)(v1)(Uint)(v2)(Uint)(v3)) \
    M(Uniform4uivEXT,                                        void,          (Int)(location)(Isize)(count)(const Uint*)(value)) \
    M(VertexAttribI1iEXT,                                    void,          (Uint)(index)(Int)(x)) \
    M(VertexAttribI1ivEXT,                                   void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttribI1uiEXT,                                   void,          (Uint)(index)(Uint)(x)) \
    M(VertexAttribI1uivEXT,                                  void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttribI2iEXT,                                    void,          (Uint)(index)(Int)(x)(Int)(y)) \
    M(VertexAttribI2ivEXT,                                   void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttribI2uiEXT,                                   void,          (Uint)(index)(Uint)(x)(Uint)(y)) \
    M(VertexAttribI2uivEXT,                                  void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttribI3iEXT,                                    void,          (Uint)(index)(Int)(x)(Int)(y)(Int)(z)) \
    M(VertexAttribI3ivEXT,                                   void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttribI3uiEXT,                                   void,          (Uint)(index)(Uint)(x)(Uint)(y)(Uint)(z)) \
    M(VertexAttribI3uivEXT,                                  void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttribI4bvEXT,                                   void,          (Uint)(index)(const Byte*)(v)) \
    M(VertexAttribI4iEXT,                                    void,          (Uint)(index)(Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(VertexAttribI4ivEXT,                                   void,          (Uint)(index)(const Int*)(v)) \
    M(VertexAttribI4svEXT,                                   void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttribI4ubvEXT,                                  void,          (Uint)(index)(const Ubyte*)(v)) \
    M(VertexAttribI4uiEXT,                                   void,          (Uint)(index)(Uint)(x)(Uint)(y)(Uint)(z)(Uint)(w)) \
    M(VertexAttribI4uivEXT,                                  void,          (Uint)(index)(const Uint*)(v)) \
    M(VertexAttribI4usvEXT,                                  void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttribIPointerEXT,                               void,          (Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(GetHistogramEXT,                                       void,          (Enum)(target)(Bool)(reset)(Enum)(format)(Enum)(type)(void*)(values)) \
    M(GetHistogramParameterfvEXT,                            void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetHistogramParameterivEXT,                            void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetMinmaxEXT,                                          void,          (Enum)(target)(Bool)(reset)(Enum)(format)(Enum)(type)(void*)(values)) \
    M(GetMinmaxParameterfvEXT,                               void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetMinmaxParameterivEXT,                               void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(HistogramEXT,                                          void,          (Enum)(target)(Isize)(width)(Enum)(internalformat)(Bool)(sink)) \
    M(MinmaxEXT,                                             void,          (Enum)(target)(Enum)(internalformat)(Bool)(sink)) \
    M(ResetHistogramEXT,                                     void,          (Enum)(target)) \
    M(ResetMinmaxEXT,                                        void,          (Enum)(target)) \
    M(IndexFuncEXT,                                          void,          (Enum)(func)(Float)(ref)) \
    M(IndexMaterialEXT,                                      void,          (Enum)(face)(Enum)(mode)) \
    M(VertexAttribDivisorEXT,                                void,          (Uint)(index)(Uint)(divisor)) \
    M(ApplyTextureEXT,                                       void,          (Enum)(mode)) \
    M(TextureLightEXT,                                       void,          (Enum)(pname)) \
    M(TextureMaterialEXT,                                    void,          (Enum)(face)(Enum)(mode)) \
    M(FlushMappedBufferRangeEXT,                             void,          (Enum)(target)(IntPtr)(offset)(IsizePtr)(length)) \
    M(MapBufferRangeEXT,                                     void *,        (Enum)(target)(IntPtr)(offset)(IsizePtr)(length)(Bitfield)(access)) \
    M(BufferStorageMemEXT,                                   void,          (Enum)(target)(IsizePtr)(size)(Uint)(memory)(Uint64)(offset)) \
    M(CreateMemoryObjectsEXT,                                void,          (Isize)(n)(Uint*)(memoryObjects)) \
    M(DeleteMemoryObjectsEXT,                                void,          (Isize)(n)(const Uint*)(memoryObjects)) \
    M(GetMemoryObjectParameterivEXT,                         void,          (Uint)(memoryObject)(Enum)(pname)(Int*)(params)) \
    M(GetUnsignedBytei_vEXT,                                 void,          (Enum)(target)(Uint)(index)(Ubyte*)(data)) \
    M(GetUnsignedBytevEXT,                                   void,          (Enum)(pname)(Ubyte*)(data)) \
    M(IsMemoryObjectEXT,                                     Bool,          (Uint)(memoryObject)) \
    M(MemoryObjectParameterivEXT,                            void,          (Uint)(memoryObject)(Enum)(pname)(const Int*)(params)) \
    M(NamedBufferStorageMemEXT,                              void,          (Uint)(buffer)(IsizePtr)(size)(Uint)(memory)(Uint64)(offset)) \
    M(TexStorageMem1DEXT,                                    void,          (Enum)(target)(Isize)(levels)(Enum)(internalFormat)(Isize)(width)(Uint)(memory)(Uint64)(offset)) \
    M(TexStorageMem2DEXT,                                    void,          (Enum)(target)(Isize)(levels)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Uint)(memory)(Uint64)(offset)) \
    M(TexStorageMem2DMultisampleEXT,                         void,          (Enum)(target)(Isize)(samples)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Bool)(fixedSampleLocations)(Uint)(memory)(Uint64)(offset)) \
    M(TexStorageMem3DEXT,                                    void,          (Enum)(target)(Isize)(levels)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Uint)(memory)(Uint64)(offset)) \
    M(TexStorageMem3DMultisampleEXT,                         void,          (Enum)(target)(Isize)(samples)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedSampleLocations)(Uint)(memory)(Uint64)(offset)) \
    M(TextureStorageMem1DEXT,                                void,          (Uint)(texture)(Isize)(levels)(Enum)(internalFormat)(Isize)(width)(Uint)(memory)(Uint64)(offset)) \
    M(TextureStorageMem2DEXT,                                void,          (Uint)(texture)(Isize)(levels)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Uint)(memory)(Uint64)(offset)) \
    M(TextureStorageMem2DMultisampleEXT,                     void,          (Uint)(texture)(Isize)(samples)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Bool)(fixedSampleLocations)(Uint)(memory)(Uint64)(offset)) \
    M(TextureStorageMem3DEXT,                                void,          (Uint)(texture)(Isize)(levels)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Uint)(memory)(Uint64)(offset)) \
    M(TextureStorageMem3DMultisampleEXT,                     void,          (Uint)(texture)(Isize)(samples)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedSampleLocations)(Uint)(memory)(Uint64)(offset)) \
    M(ImportMemoryFdEXT,                                     void,          (Uint)(memory)(Uint64)(size)(Enum)(handleType)(Int)(fd)) \
    M(ImportMemoryWin32HandleEXT,                            void,          (Uint)(memory)(Uint64)(size)(Enum)(handleType)(void*)(handle)) \
    M(ImportMemoryWin32NameEXT,                              void,          (Uint)(memory)(Uint64)(size)(Enum)(handleType)(const void*)(name)) \
    M(MultiDrawArraysEXT,                                    void,          (Enum)(mode)(const Int*)(first)(const Isize*)(count)(Isize)(primcount)) \
    M(MultiDrawElementsEXT,                                  void,          (Enum)(mode)(Isize*)(count)(Enum)(type)(const void *const*)(indices)(Isize)(primcount)) \
    M(MultiDrawArraysIndirectEXT,                            void,          (Enum)(mode)(const void*)(indirect)(Isize)(drawcount)(Isize)(stride)) \
    M(MultiDrawElementsIndirectEXT,                          void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)(Isize)(drawcount)(Isize)(stride)) \
    M(SampleMaskEXT,                                         void,          (FClamp)(value)(Bool)(invert)) \
    M(SamplePatternEXT,                                      void,          (Enum)(pattern)) \
    M(FramebufferTexture2DMultisampleEXT,                    void,          (Enum)(target)(Enum)(attachment)(Enum)(textarget)(Uint)(texture)(Int)(level)(Isize)(samples)) \
    M(DrawBuffersIndexedEXT,                                 void,          (Int)(n)(const Enum*)(location)(const Int*)(indices)) \
    M(GetIntegeri_vEXT,                                      void,          (Enum)(target)(Uint)(index)(Int*)(data)) \
    M(ReadBufferIndexedEXT,                                  void,          (Enum)(src)(Int)(index)) \
    M(ColorTableEXT,                                         void,          (Enum)(target)(Enum)(internalFormat)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(data)) \
    M(GetColorTableEXT,                                      void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(data)) \
    M(GetColorTableParameterfvEXT,                           void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetColorTableParameterivEXT,                           void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetPixelTransformParameterfvEXT,                       void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(GetPixelTransformParameterivEXT,                       void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(PixelTransformParameterfEXT,                           void,          (Enum)(target)(Enum)(pname)(const Float)(param)) \
    M(PixelTransformParameterfvEXT,                          void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(PixelTransformParameteriEXT,                           void,          (Enum)(target)(Enum)(pname)(const Int)(param)) \
    M(PixelTransformParameterivEXT,                          void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(PointParameterfEXT,                                    void,          (Enum)(pname)(Float)(param)) \
    M(PointParameterfvEXT,                                   void,          (Enum)(pname)(const Float*)(params)) \
    M(PolygonOffsetEXT,                                      void,          (Float)(factor)(Float)(bias)) \
    M(PolygonOffsetClampEXT,                                 void,          (Float)(factor)(Float)(units)(Float)(clamp)) \
    M(ProvokingVertexEXT,                                    void,          (Enum)(mode)) \
    M(CoverageModulationNV,                                  void,          (Enum)(components)) \
    M(CoverageModulationTableNV,                             void,          (Isize)(n)(const Float*)(v)) \
    M(GetCoverageModulationTableNV,                          void,          (Isize)(bufsize)(Float*)(v)) \
    M(RasterSamplesEXT,                                      void,          (Uint)(samples)(Bool)(fixedsamplelocations)) \
    M(BeginSceneEXT,                                         void,          ) \
    M(EndSceneEXT,                                           void,          ) \
    M(SecondaryColor3bEXT,                                   void,          (Byte)(red)(Byte)(green)(Byte)(blue)) \
    M(SecondaryColor3bvEXT,                                  void,          (const Byte*)(v)) \
    M(SecondaryColor3dEXT,                                   void,          (Double)(red)(Double)(green)(Double)(blue)) \
    M(SecondaryColor3dvEXT,                                  void,          (const Double*)(v)) \
    M(SecondaryColor3fEXT,                                   void,          (Float)(red)(Float)(green)(Float)(blue)) \
    M(SecondaryColor3fvEXT,                                  void,          (const Float*)(v)) \
    M(SecondaryColor3iEXT,                                   void,          (Int)(red)(Int)(green)(Int)(blue)) \
    M(SecondaryColor3ivEXT,                                  void,          (const Int*)(v)) \
    M(SecondaryColor3sEXT,                                   void,          (Short)(red)(Short)(green)(Short)(blue)) \
    M(SecondaryColor3svEXT,                                  void,          (const Short*)(v)) \
    M(SecondaryColor3ubEXT,                                  void,          (Ubyte)(red)(Ubyte)(green)(Ubyte)(blue)) \
    M(SecondaryColor3ubvEXT,                                 void,          (const Ubyte*)(v)) \
    M(SecondaryColor3uiEXT,                                  void,          (Uint)(red)(Uint)(green)(Uint)(blue)) \
    M(SecondaryColor3uivEXT,                                 void,          (const Uint*)(v)) \
    M(SecondaryColor3usEXT,                                  void,          (Ushort)(red)(Ushort)(green)(Ushort)(blue)) \
    M(SecondaryColor3usvEXT,                                 void,          (const Ushort*)(v)) \
    M(SecondaryColorPointerEXT,                              void,          (Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(DeleteSemaphoresEXT,                                   void,          (Isize)(n)(const Uint*)(semaphores)) \
    M(GenSemaphoresEXT,                                      void,          (Isize)(n)(Uint*)(semaphores)) \
    M(GetSemaphoreParameterui64vEXT,                         void,          (Uint)(semaphore)(Enum)(pname)(Uint64*)(params)) \
    M(IsSemaphoreEXT,                                        Bool,          (Uint)(semaphore)) \
    M(SemaphoreParameterui64vEXT,                            void,          (Uint)(semaphore)(Enum)(pname)(const Uint64*)(params)) \
    M(SignalSemaphoreEXT,                                    void,          (Uint)(semaphore)(Uint)(numBufferBarriers)(const Uint*)(buffers)(Uint)(numTextureBarriers)(const Uint*)(textures)(const Enum*)(dstLayouts)) \
    M(WaitSemaphoreEXT,                                      void,          (Uint)(semaphore)(Uint)(numBufferBarriers)(const Uint*)(buffers)(Uint)(numTextureBarriers)(const Uint*)(textures)(const Enum*)(srcLayouts)) \
    M(ImportSemaphoreFdEXT,                                  void,          (Uint)(semaphore)(Enum)(handleType)(Int)(fd)) \
    M(ImportSemaphoreWin32HandleEXT,                         void,          (Uint)(semaphore)(Enum)(handleType)(void*)(handle)) \
    M(ImportSemaphoreWin32NameEXT,                           void,          (Uint)(semaphore)(Enum)(handleType)(const void*)(name)) \
    M(ActiveProgramEXT,                                      void,          (Uint)(program)) \
    M(CreateShaderProgramEXT,                                Uint,          (Enum)(type)(const char*)(string)) \
    M(UseShaderProgramEXT,                                   void,          (Enum)(type)(Uint)(program)) \
    M(BindImageTextureEXT,                                   void,          (Uint)(index)(Uint)(texture)(Int)(level)(Bool)(layered)(Int)(layer)(Enum)(access)(Int)(format)) \
    M(MemoryBarrierEXT,                                      void,          (Bitfield)(barriers)) \
    M(ClearPixelLocalStorageuiEXT,                           void,          (Isize)(offset)(Isize)(n)(const Uint*)(values)) \
    M(FramebufferPixelLocalStorageSizeEXT,                   void,          (Uint)(target)(Isize)(size)) \
    M(GetFramebufferPixelLocalStorageSizeEXT,                Isize,         (Uint)(target)) \
    M(TexPageCommitmentEXT,                                  void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(commit)) \
    M(TexturePageCommitmentEXT,                              void,          (Uint)(texture)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(commit)) \
    M(ActiveStencilFaceEXT,                                  void,          (Enum)(face)) \
    M(TexSubImage1DEXT,                                      void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexSubImage2DEXT,                                      void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexSubImage3DEXT,                                      void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexImage3DEXT,                                         void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(FramebufferTextureLayerEXT,                            void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Int)(layer)) \
    M(TexBufferEXT,                                          void,          (Enum)(target)(Enum)(internalformat)(Uint)(buffer)) \
    M(ClearColorIiEXT,                                       void,          (Int)(red)(Int)(green)(Int)(blue)(Int)(alpha)) \
    M(ClearColorIuiEXT,                                      void,          (Uint)(red)(Uint)(green)(Uint)(blue)(Uint)(alpha)) \
    M(GetTexParameterIivEXT,                                 void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetTexParameterIuivEXT,                                void,          (Enum)(target)(Enum)(pname)(Uint*)(params)) \
    M(TexParameterIivEXT,                                    void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(TexParameterIuivEXT,                                   void,          (Enum)(target)(Enum)(pname)(const Uint*)(params)) \
    M(AreTexturesResidentEXT,                                Bool,          (Isize)(n)(const Uint*)(textures)(Bool*)(residences)) \
    M(BindTextureEXT,                                        void,          (Enum)(target)(Uint)(texture)) \
    M(DeleteTexturesEXT,                                     void,          (Isize)(n)(const Uint*)(textures)) \
    M(GenTexturesEXT,                                        void,          (Isize)(n)(Uint*)(textures)) \
    M(IsTextureEXT,                                          Bool,          (Uint)(texture)) \
    M(PrioritizeTexturesEXT,                                 void,          (Isize)(n)(const Uint*)(textures)(const FClamp*)(priorities)) \
    M(TextureNormalEXT,                                      void,          (Enum)(mode)) \
    M(TexStorage1DEXT,                                       void,          (Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)) \
    M(TexStorage2DEXT,                                       void,          (Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(TexStorage3DEXT,                                       void,          (Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)) \
    M(TextureStorage1DEXT,                                   void,          (Uint)(texture)(Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)) \
    M(TextureStorage2DEXT,                                   void,          (Uint)(texture)(Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(TextureStorage3DEXT,                                   void,          (Uint)(texture)(Enum)(target)(Isize)(levels)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)) \
    M(TextureViewEXT,                                        void,          (Uint)(texture)(Enum)(target)(Uint)(origtexture)(Enum)(internalformat)(Uint)(minlevel)(Uint)(numlevels)(Uint)(minlayer)(Uint)(numlayers)) \
    M(GetQueryObjecti64vEXT,                                 void,          (Uint)(id)(Enum)(pname)(Int64*)(params)) \
    M(GetQueryObjectui64vEXT,                                void,          (Uint)(id)(Enum)(pname)(Uint64*)(params)) \
    M(BeginTransformFeedbackEXT,                             void,          (Enum)(primitiveMode)) \
    M(BindBufferBaseEXT,                                     void,          (Enum)(target)(Uint)(index)(Uint)(buffer)) \
    M(BindBufferOffsetEXT,                                   void,          (Enum)(target)(Uint)(index)(Uint)(buffer)(IntPtr)(offset)) \
    M(BindBufferRangeEXT,                                    void,          (Enum)(target)(Uint)(index)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)) \
    M(EndTransformFeedbackEXT,                               void,          ) \
    M(GetTransformFeedbackVaryingEXT,                        void,          (Uint)(program)(Uint)(index)(Isize)(bufSize)(Isize*)(length)(Isize*)(size)(Enum*)(type)(char*)(name)) \
    M(TransformFeedbackVaryingsEXT,                          void,          (Uint)(program)(Isize)(count)(const char * const*)(varyings)(Enum)(bufferMode)) \
    M(ArrayElementEXT,                                       void,          (Int)(i)) \
    M(ColorPointerEXT,                                       void,          (Int)(size)(Enum)(type)(Isize)(stride)(Isize)(count)(const void*)(pointer)) \
    M(DrawArraysEXT,                                         void,          (Enum)(mode)(Int)(first)(Isize)(count)) \
    M(EdgeFlagPointerEXT,                                    void,          (Isize)(stride)(Isize)(count)(const Bool*)(pointer)) \
    M(IndexPointerEXT,                                       void,          (Enum)(type)(Isize)(stride)(Isize)(count)(const void*)(pointer)) \
    M(NormalPointerEXT,                                      void,          (Enum)(type)(Isize)(stride)(Isize)(count)(const void*)(pointer)) \
    M(TexCoordPointerEXT,                                    void,          (Int)(size)(Enum)(type)(Isize)(stride)(Isize)(count)(const void*)(pointer)) \
    M(VertexPointerEXT,                                      void,          (Int)(size)(Enum)(type)(Isize)(stride)(Isize)(count)(const void*)(pointer)) \
    M(BindArraySetEXT,                                       void,          (const void*)(arrayset)) \
    M(CreateArraySetExt,                                     const void *,  ) \
    M(DeleteArraySetsEXT,                                    void,          (Isize)(n)(const void**)(arrayset)) \
    M(GetVertexAttribLdvEXT,                                 void,          (Uint)(index)(Enum)(pname)(Double*)(params)) \
    M(VertexArrayVertexAttribLOffsetEXT,                     void,          (Uint)(vaobj)(Uint)(buffer)(Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)(IntPtr)(offset)) \
    M(VertexAttribL1dEXT,                                    void,          (Uint)(index)(Double)(x)) \
    M(VertexAttribL1dvEXT,                                   void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribL2dEXT,                                    void,          (Uint)(index)(Double)(x)(Double)(y)) \
    M(VertexAttribL2dvEXT,                                   void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribL3dEXT,                                    void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)) \
    M(VertexAttribL3dvEXT,                                   void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribL4dEXT,                                    void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(VertexAttribL4dvEXT,                                   void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttribLPointerEXT,                               void,          (Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(BeginVertexShaderEXT,                                  void,          ) \
    M(BindLightParameterEXT,                                 Uint,          (Enum)(light)(Enum)(value)) \
    M(BindMaterialParameterEXT,                              Uint,          (Enum)(face)(Enum)(value)) \
    M(BindParameterEXT,                                      Uint,          (Enum)(value)) \
    M(BindTexGenParameterEXT,                                Uint,          (Enum)(unit)(Enum)(coord)(Enum)(value)) \
    M(BindTextureUnitParameterEXT,                           Uint,          (Enum)(unit)(Enum)(value)) \
    M(BindVertexShaderEXT,                                   void,          (Uint)(id)) \
    M(DeleteVertexShaderEXT,                                 void,          (Uint)(id)) \
    M(DisableVariantClientStateEXT,                          void,          (Uint)(id)) \
    M(EnableVariantClientStateEXT,                           void,          (Uint)(id)) \
    M(EndVertexShaderEXT,                                    void,          ) \
    M(ExtractComponentEXT,                                   void,          (Uint)(res)(Uint)(src)(Uint)(num)) \
    M(GenSymbolsEXT,                                         Uint,          (Enum)(dataType)(Enum)(storageType)(Enum)(range)(Uint)(components)) \
    M(GenVertexShadersEXT,                                   Uint,          (Uint)(range)) \
    M(GetInvariantBooleanvEXT,                               void,          (Uint)(id)(Enum)(value)(Bool*)(data)) \
    M(GetInvariantFloatvEXT,                                 void,          (Uint)(id)(Enum)(value)(Float*)(data)) \
    M(GetInvariantIntegervEXT,                               void,          (Uint)(id)(Enum)(value)(Int*)(data)) \
    M(GetLocalConstantBooleanvEXT,                           void,          (Uint)(id)(Enum)(value)(Bool*)(data)) \
    M(GetLocalConstantFloatvEXT,                             void,          (Uint)(id)(Enum)(value)(Float*)(data)) \
    M(GetLocalConstantIntegervEXT,                           void,          (Uint)(id)(Enum)(value)(Int*)(data)) \
    M(GetVariantBooleanvEXT,                                 void,          (Uint)(id)(Enum)(value)(Bool*)(data)) \
    M(GetVariantFloatvEXT,                                   void,          (Uint)(id)(Enum)(value)(Float*)(data)) \
    M(GetVariantIntegervEXT,                                 void,          (Uint)(id)(Enum)(value)(Int*)(data)) \
    M(GetVariantPointervEXT,                                 void,          (Uint)(id)(Enum)(value)(void**)(data)) \
    M(InsertComponentEXT,                                    void,          (Uint)(res)(Uint)(src)(Uint)(num)) \
    M(IsVariantEnabledEXT,                                   Bool,          (Uint)(id)(Enum)(cap)) \
    M(SetInvariantEXT,                                       void,          (Uint)(id)(Enum)(type)(void*)(addr)) \
    M(SetLocalConstantEXT,                                   void,          (Uint)(id)(Enum)(type)(void*)(addr)) \
    M(ShaderOp1EXT,                                          void,          (Enum)(op)(Uint)(res)(Uint)(arg1)) \
    M(ShaderOp2EXT,                                          void,          (Enum)(op)(Uint)(res)(Uint)(arg1)(Uint)(arg2)) \
    M(ShaderOp3EXT,                                          void,          (Enum)(op)(Uint)(res)(Uint)(arg1)(Uint)(arg2)(Uint)(arg3)) \
    M(SwizzleEXT,                                            void,          (Uint)(res)(Uint)(in)(Enum)(outX)(Enum)(outY)(Enum)(outZ)(Enum)(outW)) \
    M(VariantPointerEXT,                                     void,          (Uint)(id)(Enum)(type)(Uint)(stride)(void*)(addr)) \
    M(VariantbvEXT,                                          void,          (Uint)(id)(Byte*)(addr)) \
    M(VariantdvEXT,                                          void,          (Uint)(id)(Double*)(addr)) \
    M(VariantfvEXT,                                          void,          (Uint)(id)(Float*)(addr)) \
    M(VariantivEXT,                                          void,          (Uint)(id)(Int*)(addr)) \
    M(VariantsvEXT,                                          void,          (Uint)(id)(Short*)(addr)) \
    M(VariantubvEXT,                                         void,          (Uint)(id)(Ubyte*)(addr)) \
    M(VariantuivEXT,                                         void,          (Uint)(id)(Uint*)(addr)) \
    M(VariantusvEXT,                                         void,          (Uint)(id)(Ushort*)(addr)) \
    M(WriteMaskEXT,                                          void,          (Uint)(res)(Uint)(in)(Enum)(outX)(Enum)(outY)(Enum)(outZ)(Enum)(outW)) \
    M(VertexWeightPointerEXT,                                void,          (Int)(size)(Enum)(type)(Isize)(stride)(void*)(pointer)) \
    M(VertexWeightfEXT,                                      void,          (Float)(weight)) \
    M(VertexWeightfvEXT,                                     void,          (Float*)(weight)) \
    M(AcquireKeyedMutexWin32EXT,                             Bool,          (Uint)(memory)(Uint64)(key)(Uint)(timeout)) \
    M(ReleaseKeyedMutexWin32EXT,                             Bool,          (Uint)(memory)(Uint64)(key)) \
    M(WindowRectanglesEXT,                                   void,          (Enum)(mode)(Isize)(count)(const Int*)(box)) \
    M(ImportSyncEXT,                                         Sync,          (Enum)(external_sync_type)(IntPtr)(external_sync)(Bitfield)(flags)) \
    M(FrameTerminatorGREMEDY,                                void,          ) \
    M(StringMarkerGREMEDY,                                   void,          (Isize)(len)(const void*)(string)) \
    M(GetImageTransformParameterfvHP,                        void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(GetImageTransformParameterivHP,                        void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(ImageTransformParameterfHP,                            void,          (Enum)(target)(Enum)(pname)(const Float)(param)) \
    M(ImageTransformParameterfvHP,                           void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(ImageTransformParameteriHP,                            void,          (Enum)(target)(Enum)(pname)(const Int)(param)) \
    M(ImageTransformParameterivHP,                           void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(MultiModeDrawArraysIBM,                                void,          (const Enum*)(mode)(const Int*)(first)(const Isize*)(count)(Isize)(primcount)(Int)(modestride)) \
    M(MultiModeDrawElementsIBM,                              void,          (const Enum*)(mode)(const Isize*)(count)(Enum)(type)(const void *const*)(indices)(Isize)(primcount)(Int)(modestride)) \
    M(ColorPointerListIBM,                                   void,          (Int)(size)(Enum)(type)(Int)(stride)(const void**)(pointer)(Int)(ptrstride)) \
    M(EdgeFlagPointerListIBM,                                void,          (Int)(stride)(const Bool **)(pointer)(Int)(ptrstride)) \
    M(FogCoordPointerListIBM,                                void,          (Enum)(type)(Int)(stride)(const void**)(pointer)(Int)(ptrstride)) \
    M(IndexPointerListIBM,                                   void,          (Enum)(type)(Int)(stride)(const void**)(pointer)(Int)(ptrstride)) \
    M(NormalPointerListIBM,                                  void,          (Enum)(type)(Int)(stride)(const void**)(pointer)(Int)(ptrstride)) \
    M(SecondaryColorPointerListIBM,                          void,          (Int)(size)(Enum)(type)(Int)(stride)(const void**)(pointer)(Int)(ptrstride)) \
    M(TexCoordPointerListIBM,                                void,          (Int)(size)(Enum)(type)(Int)(stride)(const void**)(pointer)(Int)(ptrstride)) \
    M(VertexPointerListIBM,                                  void,          (Int)(size)(Enum)(type)(Int)(stride)(const void**)(pointer)(Int)(ptrstride)) \
    M(MapTexture2DINTEL,                                     void *,        (Uint)(texture)(Int)(level)(Bitfield)(access)(Int*)(stride)(Enum*)(layout)) \
    M(SyncTextureINTEL,                                      void,          (Uint)(texture)) \
    M(UnmapTexture2DINTEL,                                   void,          (Uint)(texture)(Int)(level)) \
    M(ColorPointervINTEL,                                    void,          (Int)(size)(Enum)(type)(const void**)(pointer)) \
    M(NormalPointervINTEL,                                   void,          (Enum)(type)(const void**)(pointer)) \
    M(TexCoordPointervINTEL,                                 void,          (Int)(size)(Enum)(type)(const void**)(pointer)) \
    M(VertexPointervINTEL,                                   void,          (Int)(size)(Enum)(type)(const void**)(pointer)) \
    M(BeginPerfQueryINTEL,                                   void,          (Uint)(queryHandle)) \
    M(CreatePerfQueryINTEL,                                  void,          (Uint)(queryId)(Uint*)(queryHandle)) \
    M(DeletePerfQueryINTEL,                                  void,          (Uint)(queryHandle)) \
    M(EndPerfQueryINTEL,                                     void,          (Uint)(queryHandle)) \
    M(GetFirstPerfQueryIdINTEL,                              void,          (Uint*)(queryId)) \
    M(GetNextPerfQueryIdINTEL,                               void,          (Uint)(queryId)(Uint*)(nextQueryId)) \
    M(GetPerfCounterInfoINTEL,                               void,          (Uint)(queryId)(Uint)(counterId)(Uint)(counterNameLength)(char*)(counterName)(Uint)(counterDescLength)(char*)(counterDesc)(Uint*)(counterOffset)(Uint*)(counterDataSize)(Uint*)(counterTypeEnum)(Uint*)(counterDataTypeEnum)(Uint64*)(rawCounterMaxValue)) \
    M(GetPerfQueryDataINTEL,                                 void,          (Uint)(queryHandle)(Uint)(flags)(Isize)(dataSize)(void*)(data)(Uint*)(bytesWritten)) \
    M(GetPerfQueryIdByNameINTEL,                             void,          (char*)(queryName)(Uint*)(queryId)) \
    M(GetPerfQueryInfoINTEL,                                 void,          (Uint)(queryId)(Uint)(queryNameLength)(char*)(queryName)(Uint*)(dataSize)(Uint*)(noCounters)(Uint*)(noInstances)(Uint*)(capsMask)) \
    M(TexScissorFuncINTEL,                                   void,          (Enum)(target)(Enum)(lfunc)(Enum)(hfunc)) \
    M(TexScissorINTEL,                                       void,          (Enum)(target)(FClamp)(tlow)(FClamp)(thigh)) \
    M(BlendBarrierKHR,                                       void,          ) \
    M(DebugMessageCallback,                                  void,          (LogFunc)(callback)(const void*)(userParam)) \
    M(DebugMessageControl,                                   void,          (Enum)(source)(Enum)(type)(Enum)(severity)(Isize)(count)(const Uint*)(ids)(Bool)(enabled)) \
    M(DebugMessageInsert,                                    void,          (Enum)(source)(Enum)(type)(Uint)(id)(Enum)(severity)(Isize)(length)(const char*)(buf)) \
    M(GetDebugMessageLog,                                    Uint,          (Uint)(count)(Isize)(bufSize)(Enum*)(sources)(Enum*)(types)(Uint*)(ids)(Enum*)(severities)(Isize*)(lengths)(char*)(messageLog)) \
    M(GetObjectLabel,                                        void,          (Enum)(identifier)(Uint)(name)(Isize)(bufSize)(Isize*)(length)(char*)(label)) \
    M(GetObjectPtrLabel,                                     void,          (void*)(ptr)(Isize)(bufSize)(Isize*)(length)(char*)(label)) \
    M(ObjectLabel,                                           void,          (Enum)(identifier)(Uint)(name)(Isize)(length)(const char*)(label)) \
    M(ObjectPtrLabel,                                        void,          (void*)(ptr)(Isize)(length)(const char*)(label)) \
    M(PopDebugGroup,                                         void,          ) \
    M(PushDebugGroup,                                        void,          (Enum)(source)(Uint)(id)(Isize)(length)(const char *)(message)) \
    M(MaxShaderCompilerThreadsKHR,                           void,          (Uint)(count)) \
    M(GetnUniformfv,                                         void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Float*)(params)) \
    M(GetnUniformiv,                                         void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Int*)(params)) \
    M(GetnUniformuiv,                                        void,          (Uint)(program)(Int)(location)(Isize)(bufSize)(Uint*)(params)) \
    M(ReadnPixels,                                           void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(Isize)(bufSize)(void*)(data)) \
    M(BufferRegionEnabled,                                   Uint,          ) \
    M(DeleteBufferRegion,                                    void,          (Enum)(region)) \
    M(DrawBufferRegion,                                      void,          (Uint)(region)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Int)(xDest)(Int)(yDest)) \
    M(NewBufferRegion,                                       Uint,          (Enum)(region)) \
    M(ReadBufferRegion,                                      void,          (Uint)(region)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(ResizeBuffersMESA,                                     void,          ) \
    M(WindowPos2dMESA,                                       void,          (Double)(x)(Double)(y)) \
    M(WindowPos2dvMESA,                                      void,          (const Double*)(p)) \
    M(WindowPos2fMESA,                                       void,          (Float)(x)(Float)(y)) \
    M(WindowPos2fvMESA,                                      void,          (const Float*)(p)) \
    M(WindowPos2iMESA,                                       void,          (Int)(x)(Int)(y)) \
    M(WindowPos2ivMESA,                                      void,          (const Int*)(p)) \
    M(WindowPos2sMESA,                                       void,          (Short)(x)(Short)(y)) \
    M(WindowPos2svMESA,                                      void,          (const Short*)(p)) \
    M(WindowPos3dMESA,                                       void,          (Double)(x)(Double)(y)(Double)(z)) \
    M(WindowPos3dvMESA,                                      void,          (const Double*)(p)) \
    M(WindowPos3fMESA,                                       void,          (Float)(x)(Float)(y)(Float)(z)) \
    M(WindowPos3fvMESA,                                      void,          (const Float*)(p)) \
    M(WindowPos3iMESA,                                       void,          (Int)(x)(Int)(y)(Int)(z)) \
    M(WindowPos3ivMESA,                                      void,          (const Int*)(p)) \
    M(WindowPos3sMESA,                                       void,          (Short)(x)(Short)(y)(Short)(z)) \
    M(WindowPos3svMESA,                                      void,          (const Short*)(p)) \
    M(WindowPos4dMESA,                                       void,          (Double)(x)(Double)(y)(Double)(z)(Double)(_)) \
    M(WindowPos4dvMESA,                                      void,          (const Double*)(p)) \
    M(WindowPos4fMESA,                                       void,          (Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(WindowPos4fvMESA,                                      void,          (const Float*)(p)) \
    M(WindowPos4iMESA,                                       void,          (Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(WindowPos4ivMESA,                                      void,          (const Int*)(p)) \
    M(WindowPos4sMESA,                                       void,          (Short)(x)(Short)(y)(Short)(z)(Short)(w)) \
    M(WindowPos4svMESA,                                      void,          (const Short*)(p)) \
    M(BeginConditionalRenderNVX,                             void,          (Uint)(id)) \
    M(EndConditionalRenderNVX,                               void,          ) \
    M(LGPUCopyImageSubDataNVX,                               void,          (Uint)(sourceGpu)(Bitfield)(destinationGpuMask)(Uint)(srcName)(Enum)(srcTarget)(Int)(srcLevel)(Int)(srcX)(Int)(srxY)(Int)(srcZ)(Uint)(dstName)(Enum)(dstTarget)(Int)(dstLevel)(Int)(dstX)(Int)(dstY)(Int)(dstZ)(Isize)(width)(Isize)(height)(Isize)(depth)) \
    M(LGPUInterlockNVX,                                      void,          ) \
    M(LGPUNamedBufferSubDataNVX,                             void,          (Bitfield)(gpuMask)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)(const void*)(data)) \
    M(StereoParameterfNV,                                    void,          (Enum)(pname)(Float)(param)) \
    M(StereoParameteriNV,                                    void,          (Enum)(pname)(Int)(param)) \
    M(MultiDrawArraysIndirectBindlessNV,                     void,          (Enum)(mode)(const void*)(indirect)(Isize)(drawCount)(Isize)(stride)(Int)(vertexBufferCount)) \
    M(MultiDrawElementsIndirectBindlessNV,                   void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)(Isize)(drawCount)(Isize)(stride)(Int)(vertexBufferCount)) \
    M(MultiDrawArraysIndirectBindlessCountNV,                void,          (Enum)(mode)(const void*)(indirect)(IntPtr)(drawCount)(Isize)(maxDrawCount)(Isize)(stride)(Int)(vertexBufferCount)) \
    M(MultiDrawElementsIndirectBindlessCountNV,              void,          (Enum)(mode)(Enum)(type)(const void*)(indirect)(IntPtr)(drawCount)(Isize)(maxDrawCount)(Isize)(stride)(Int)(vertexBufferCount)) \
    M(GetImageHandleNV,                                      Uint64,        (Uint)(texture)(Int)(level)(Bool)(layered)(Int)(layer)(Enum)(format)) \
    M(GetTextureHandleNV,                                    Uint64,        (Uint)(texture)) \
    M(GetTextureSamplerHandleNV,                             Uint64,        (Uint)(texture)(Uint)(sampler)) \
    M(IsImageHandleResidentNV,                               Bool,          (Uint64)(handle)) \
    M(IsTextureHandleResidentNV,                             Bool,          (Uint64)(handle)) \
    M(MakeImageHandleNonResidentNV,                          void,          (Uint64)(handle)) \
    M(MakeImageHandleResidentNV,                             void,          (Uint64)(handle)(Enum)(access)) \
    M(MakeTextureHandleNonResidentNV,                        void,          (Uint64)(handle)) \
    M(MakeTextureHandleResidentNV,                           void,          (Uint64)(handle)) \
    M(ProgramUniformHandleui64NV,                            void,          (Uint)(program)(Int)(location)(Uint64)(value)) \
    M(ProgramUniformHandleui64vNV,                           void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(values)) \
    M(UniformHandleui64NV,                                   void,          (Int)(location)(Uint64)(value)) \
    M(UniformHandleui64vNV,                                  void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(BlendBarrierNV,                                        void,          ) \
    M(BlendParameteriNV,                                     void,          (Enum)(pname)(Int)(value)) \
    M(ViewportPositionWScaleNV,                              void,          (Uint)(index)(Float)(xcoeff)(Float)(ycoeff)) \
    M(CallCommandListNV,                                     void,          (Uint)(list)) \
    M(CommandListSegmentsNV,                                 void,          (Uint)(list)(Uint)(segments)) \
    M(CompileCommandListNV,                                  void,          (Uint)(list)) \
    M(CreateCommandListsNV,                                  void,          (Isize)(n)(Uint*)(lists)) \
    M(CreateStatesNV,                                        void,          (Isize)(n)(Uint*)(states)) \
    M(DeleteCommandListsNV,                                  void,          (Isize)(n)(const Uint*)(lists)) \
    M(DeleteStatesNV,                                        void,          (Isize)(n)(const Uint*)(states)) \
    M(DrawCommandsAddressNV,                                 void,          (Enum)(primitiveMode)(const Uint64*)(indirects)(const Isize*)(sizes)(Uint)(count)) \
    M(DrawCommandsNV,                                        void,          (Enum)(primitiveMode)(Uint)(buffer)(const IntPtr*)(indirects)(const Isize*)(sizes)(Uint)(count)) \
    M(DrawCommandsStatesAddressNV,                           void,          (const Uint64*)(indirects)(const Isize*)(sizes)(const Uint*)(states)(const Uint*)(fbos)(Uint)(count)) \
    M(DrawCommandsStatesNV,                                  void,          (Uint)(buffer)(const IntPtr*)(indirects)(const Isize*)(sizes)(const Uint*)(states)(const Uint*)(fbos)(Uint)(count)) \
    M(GetCommandHeaderNV,                                    Uint,          (Enum)(tokenID)(Uint)(size)) \
    M(GetStageIndexNV,                                       Ushort,        (Enum)(shadertype)) \
    M(IsCommandListNV,                                       Bool,          (Uint)(list)) \
    M(IsStateNV,                                             Bool,          (Uint)(state)) \
    M(ListDrawCommandsStatesClientNV,                        void,          (Uint)(list)(Uint)(segment)(const void**)(indirects)(const Isize*)(sizes)(const Uint*)(states)(const Uint*)(fbos)(Uint)(count)) \
    M(StateCaptureNV,                                        void,          (Uint)(state)(Enum)(mode)) \
    M(BeginConditionalRenderNV,                              void,          (Uint)(id)(Enum)(mode)) \
    M(EndConditionalRenderNV,                                void,          ) \
    M(SubpixelPrecisionBiasNV,                               void,          (Uint)(xbits)(Uint)(ybits)) \
    M(ConservativeRasterParameterfNV,                        void,          (Enum)(pname)(Float)(value)) \
    M(ConservativeRasterParameteriNV,                        void,          (Enum)(pname)(Int)(param)) \
    M(CopyBufferSubDataNV,                                   void,          (Enum)(readtarget)(Enum)(writetarget)(IntPtr)(readoffset)(IntPtr)(writeoffset)(IsizePtr)(size)) \
    M(CopyImageSubDataNV,                                    void,          (Uint)(srcName)(Enum)(srcTarget)(Int)(srcLevel)(Int)(srcX)(Int)(srcY)(Int)(srcZ)(Uint)(dstName)(Enum)(dstTarget)(Int)(dstLevel)(Int)(dstX)(Int)(dstY)(Int)(dstZ)(Isize)(width)(Isize)(height)(Isize)(depth)) \
    M(ClearDepthdNV,                                         void,          (Double)(depth)) \
    M(DepthBoundsdNV,                                        void,          (Double)(zmin)(Double)(zmax)) \
    M(DepthRangedNV,                                         void,          (Double)(zNear)(Double)(zFar)) \
    M(DrawBuffersNV,                                         void,          (Isize)(n)(const Enum*)(bufs)) \
    M(DrawArraysInstancedNV,                                 void,          (Enum)(mode)(Int)(first)(Isize)(count)(Isize)(primcount)) \
    M(DrawElementsInstancedNV,                               void,          (Enum)(mode)(Isize)(count)(Enum)(type)(const void*)(indices)(Isize)(primcount)) \
    M(DrawTextureNV,                                         void,          (Uint)(texture)(Uint)(sampler)(Float)(x0)(Float)(y0)(Float)(x1)(Float)(y1)(Float)(z)(Float)(s0)(Float)(t0)(Float)(s1)(Float)(t1)) \
    M(DrawVkImageNV,                                         void,          (Uint64)(vkImage)(Uint)(sampler)(Float)(x0)(Float)(y0)(Float)(x1)(Float)(y1)(Float)(z)(Float)(s0)(Float)(t0)(Float)(s1)(Float)(t1)) \
    M(GetVkProcAddrNV,                                       VulkanProc,    (const char*)(name)) \
    M(SignalVkFenceNV,                                       void,          (Uint64)(vkFence)) \
    M(SignalVkSemaphoreNV,                                   void,          (Uint64)(vkSemaphore)) \
    M(WaitVkSemaphoreNV,                                     void,          (Uint64)(vkSemaphore)) \
    M(EvalMapsNV,                                            void,          (Enum)(target)(Enum)(mode)) \
    M(GetMapAttribParameterfvNV,                             void,          (Enum)(target)(Uint)(index)(Enum)(pname)(Float*)(params)) \
    M(GetMapAttribParameterivNV,                             void,          (Enum)(target)(Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(GetMapControlPointsNV,                                 void,          (Enum)(target)(Uint)(index)(Enum)(type)(Isize)(ustride)(Isize)(vstride)(Bool)(packed)(void*)(points)) \
    M(GetMapParameterfvNV,                                   void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetMapParameterivNV,                                   void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(MapControlPointsNV,                                    void,          (Enum)(target)(Uint)(index)(Enum)(type)(Isize)(ustride)(Isize)(vstride)(Int)(uorder)(Int)(vorder)(Bool)(packed)(const void*)(points)) \
    M(MapParameterfvNV,                                      void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(MapParameterivNV,                                      void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(GetMultisamplefvNV,                                    void,          (Enum)(pname)(Uint)(index)(Float*)(val)) \
    M(SampleMaskIndexedNV,                                   void,          (Uint)(index)(Bitfield)(mask)) \
    M(TexRenderbufferNV,                                     void,          (Enum)(target)(Uint)(renderbuffer)) \
    M(DeleteFencesNV,                                        void,          (Isize)(n)(const Uint*)(fences)) \
    M(FinishFenceNV,                                         void,          (Uint)(fence)) \
    M(GenFencesNV,                                           void,          (Isize)(n)(Uint*)(fences)) \
    M(GetFenceivNV,                                          void,          (Uint)(fence)(Enum)(pname)(Int*)(params)) \
    M(IsFenceNV,                                             Bool,          (Uint)(fence)) \
    M(SetFenceNV,                                            void,          (Uint)(fence)(Enum)(condition)) \
    M(TestFenceNV,                                           Bool,          (Uint)(fence)) \
    M(FragmentCoverageColorNV,                               void,          (Uint)(color)) \
    M(GetProgramNamedParameterdvNV,                          void,          (Uint)(id)(Isize)(len)(const Ubyte*)(name)(Double*)(params)) \
    M(GetProgramNamedParameterfvNV,                          void,          (Uint)(id)(Isize)(len)(const Ubyte*)(name)(Float*)(params)) \
    M(ProgramNamedParameter4dNV,                             void,          (Uint)(id)(Isize)(len)(const Ubyte*)(name)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(ProgramNamedParameter4dvNV,                            void,          (Uint)(id)(Isize)(len)(const Ubyte*)(name)(const Double*)(v)) \
    M(ProgramNamedParameter4fNV,                             void,          (Uint)(id)(Isize)(len)(const Ubyte*)(name)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(ProgramNamedParameter4fvNV,                            void,          (Uint)(id)(Isize)(len)(const Ubyte*)(name)(const Float*)(v)) \
    M(BlitFramebufferNV,                                     void,          (Int)(srcX0)(Int)(srcY0)(Int)(srcX1)(Int)(srcY1)(Int)(dstX0)(Int)(dstY0)(Int)(dstX1)(Int)(dstY1)(Bitfield)(mask)(Enum)(filter)) \
    M(RenderbufferStorageMultisampleNV,                      void,          (Enum)(target)(Isize)(samples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(RenderbufferStorageMultisampleCoverageNV,              void,          (Enum)(target)(Isize)(coverageSamples)(Isize)(colorSamples)(Enum)(internalformat)(Isize)(width)(Isize)(height)) \
    M(ProgramVertexLimitNV,                                  void,          (Enum)(target)(Int)(limit)) \
    M(MulticastBarrierNV,                                    void,          ) \
    M(MulticastBlitFramebufferNV,                            void,          (Uint)(srcGpu)(Uint)(dstGpu)(Int)(srcX0)(Int)(srcY0)(Int)(srcX1)(Int)(srcY1)(Int)(dstX0)(Int)(dstY0)(Int)(dstX1)(Int)(dstY1)(Bitfield)(mask)(Enum)(filter)) \
    M(MulticastBufferSubDataNV,                              void,          (Bitfield)(gpuMask)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)(const void*)(data)) \
    M(MulticastCopyBufferSubDataNV,                          void,          (Uint)(readGpu)(Bitfield)(writeGpuMask)(Uint)(readBuffer)(Uint)(writeBuffer)(IntPtr)(readOffset)(IntPtr)(writeOffset)(IsizePtr)(size)) \
    M(MulticastCopyImageSubDataNV,                           void,          (Uint)(srcGpu)(Bitfield)(dstGpuMask)(Uint)(srcName)(Enum)(srcTarget)(Int)(srcLevel)(Int)(srcX)(Int)(srcY)(Int)(srcZ)(Uint)(dstName)(Enum)(dstTarget)(Int)(dstLevel)(Int)(dstX)(Int)(dstY)(Int)(dstZ)(Isize)(srcWidth)(Isize)(srcHeight)(Isize)(srcDepth)) \
    M(MulticastFramebufferSampleLocationsfvNV,               void,          (Uint)(gpu)(Uint)(framebuffer)(Uint)(start)(Isize)(count)(const Float*)(v)) \
    M(MulticastGetQueryObjecti64vNV,                         void,          (Uint)(gpu)(Uint)(id)(Enum)(pname)(Int64*)(params)) \
    M(MulticastGetQueryObjectivNV,                           void,          (Uint)(gpu)(Uint)(id)(Enum)(pname)(Int*)(params)) \
    M(MulticastGetQueryObjectui64vNV,                        void,          (Uint)(gpu)(Uint)(id)(Enum)(pname)(Uint64*)(params)) \
    M(MulticastGetQueryObjectuivNV,                          void,          (Uint)(gpu)(Uint)(id)(Enum)(pname)(Uint*)(params)) \
    M(MulticastWaitSyncNV,                                   void,          (Uint)(signalGpu)(Bitfield)(waitGpuMask)) \
    M(RenderGpuMaskNV,                                       void,          (Bitfield)(mask)) \
    M(ProgramEnvParameterI4iNV,                              void,          (Enum)(target)(Uint)(index)(Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(ProgramEnvParameterI4ivNV,                             void,          (Enum)(target)(Uint)(index)(const Int*)(params)) \
    M(ProgramEnvParameterI4uiNV,                             void,          (Enum)(target)(Uint)(index)(Uint)(x)(Uint)(y)(Uint)(z)(Uint)(w)) \
    M(ProgramEnvParameterI4uivNV,                            void,          (Enum)(target)(Uint)(index)(const Uint*)(params)) \
    M(ProgramEnvParametersI4ivNV,                            void,          (Enum)(target)(Uint)(index)(Isize)(count)(const Int*)(params)) \
    M(ProgramEnvParametersI4uivNV,                           void,          (Enum)(target)(Uint)(index)(Isize)(count)(const Uint*)(params)) \
    M(ProgramLocalParameterI4iNV,                            void,          (Enum)(target)(Uint)(index)(Int)(x)(Int)(y)(Int)(z)(Int)(w)) \
    M(ProgramLocalParameterI4ivNV,                           void,          (Enum)(target)(Uint)(index)(const Int*)(params)) \
    M(ProgramLocalParameterI4uiNV,                           void,          (Enum)(target)(Uint)(index)(Uint)(x)(Uint)(y)(Uint)(z)(Uint)(w)) \
    M(ProgramLocalParameterI4uivNV,                          void,          (Enum)(target)(Uint)(index)(const Uint*)(params)) \
    M(ProgramLocalParametersI4ivNV,                          void,          (Enum)(target)(Uint)(index)(Isize)(count)(const Int*)(params)) \
    M(ProgramLocalParametersI4uivNV,                         void,          (Enum)(target)(Uint)(index)(Isize)(count)(const Uint*)(params)) \
    M(GetUniformi64vNV,                                      void,          (Uint)(program)(Int)(location)(Int64*)(params)) \
    M(GetUniformui64vNV,                                     void,          (Uint)(program)(Int)(location)(Uint64*)(params)) \
    M(ProgramUniform1i64NV,                                  void,          (Uint)(program)(Int)(location)(Int64)(x)) \
    M(ProgramUniform1i64vNV,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform1ui64NV,                                 void,          (Uint)(program)(Int)(location)(Uint64)(x)) \
    M(ProgramUniform1ui64vNV,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(ProgramUniform2i64NV,                                  void,          (Uint)(program)(Int)(location)(Int64)(x)(Int64)(y)) \
    M(ProgramUniform2i64vNV,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform2ui64NV,                                 void,          (Uint)(program)(Int)(location)(Uint64)(x)(Uint64)(y)) \
    M(ProgramUniform2ui64vNV,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(ProgramUniform3i64NV,                                  void,          (Uint)(program)(Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)) \
    M(ProgramUniform3i64vNV,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform3ui64NV,                                 void,          (Uint)(program)(Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)) \
    M(ProgramUniform3ui64vNV,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(ProgramUniform4i64NV,                                  void,          (Uint)(program)(Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)(Int64)(w)) \
    M(ProgramUniform4i64vNV,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(ProgramUniform4ui64NV,                                 void,          (Uint)(program)(Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)(Uint64)(w)) \
    M(ProgramUniform4ui64vNV,                                void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform1i64NV,                                         void,          (Int)(location)(Int64)(x)) \
    M(Uniform1i64vNV,                                        void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform1ui64NV,                                        void,          (Int)(location)(Uint64)(x)) \
    M(Uniform1ui64vNV,                                       void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform2i64NV,                                         void,          (Int)(location)(Int64)(x)(Int64)(y)) \
    M(Uniform2i64vNV,                                        void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform2ui64NV,                                        void,          (Int)(location)(Uint64)(x)(Uint64)(y)) \
    M(Uniform2ui64vNV,                                       void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform3i64NV,                                         void,          (Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)) \
    M(Uniform3i64vNV,                                        void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform3ui64NV,                                        void,          (Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)) \
    M(Uniform3ui64vNV,                                       void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniform4i64NV,                                         void,          (Int)(location)(Int64)(x)(Int64)(y)(Int64)(z)(Int64)(w)) \
    M(Uniform4i64vNV,                                        void,          (Int)(location)(Isize)(count)(const Int64*)(value)) \
    M(Uniform4ui64NV,                                        void,          (Int)(location)(Uint64)(x)(Uint64)(y)(Uint64)(z)(Uint64)(w)) \
    M(Uniform4ui64vNV,                                       void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Color3hNV,                                             void,          (Ushort)(red)(Ushort)(green)(Ushort)(blue)) \
    M(Color3hvNV,                                            void,          (const Ushort*)(v)) \
    M(Color4hNV,                                             void,          (Ushort)(red)(Ushort)(green)(Ushort)(blue)(Ushort)(alpha)) \
    M(Color4hvNV,                                            void,          (const Ushort*)(v)) \
    M(FogCoordhNV,                                           void,          (Ushort)(fog)) \
    M(FogCoordhvNV,                                          void,          (const Ushort*)(fog)) \
    M(MultiTexCoord1hNV,                                     void,          (Enum)(target)(Ushort)(s)) \
    M(MultiTexCoord1hvNV,                                    void,          (Enum)(target)(const Ushort*)(v)) \
    M(MultiTexCoord2hNV,                                     void,          (Enum)(target)(Ushort)(s)(Ushort)(t)) \
    M(MultiTexCoord2hvNV,                                    void,          (Enum)(target)(const Ushort*)(v)) \
    M(MultiTexCoord3hNV,                                     void,          (Enum)(target)(Ushort)(s)(Ushort)(t)(Ushort)(r)) \
    M(MultiTexCoord3hvNV,                                    void,          (Enum)(target)(const Ushort*)(v)) \
    M(MultiTexCoord4hNV,                                     void,          (Enum)(target)(Ushort)(s)(Ushort)(t)(Ushort)(r)(Ushort)(q)) \
    M(MultiTexCoord4hvNV,                                    void,          (Enum)(target)(const Ushort*)(v)) \
    M(Normal3hNV,                                            void,          (Ushort)(nx)(Ushort)(ny)(Ushort)(nz)) \
    M(Normal3hvNV,                                           void,          (const Ushort*)(v)) \
    M(SecondaryColor3hNV,                                    void,          (Ushort)(red)(Ushort)(green)(Ushort)(blue)) \
    M(SecondaryColor3hvNV,                                   void,          (const Ushort*)(v)) \
    M(TexCoord1hNV,                                          void,          (Ushort)(s)) \
    M(TexCoord1hvNV,                                         void,          (const Ushort*)(v)) \
    M(TexCoord2hNV,                                          void,          (Ushort)(s)(Ushort)(t)) \
    M(TexCoord2hvNV,                                         void,          (const Ushort*)(v)) \
    M(TexCoord3hNV,                                          void,          (Ushort)(s)(Ushort)(t)(Ushort)(r)) \
    M(TexCoord3hvNV,                                         void,          (const Ushort*)(v)) \
    M(TexCoord4hNV,                                          void,          (Ushort)(s)(Ushort)(t)(Ushort)(r)(Ushort)(q)) \
    M(TexCoord4hvNV,                                         void,          (const Ushort*)(v)) \
    M(Vertex2hNV,                                            void,          (Ushort)(x)(Ushort)(y)) \
    M(Vertex2hvNV,                                           void,          (const Ushort*)(v)) \
    M(Vertex3hNV,                                            void,          (Ushort)(x)(Ushort)(y)(Ushort)(z)) \
    M(Vertex3hvNV,                                           void,          (const Ushort*)(v)) \
    M(Vertex4hNV,                                            void,          (Ushort)(x)(Ushort)(y)(Ushort)(z)(Ushort)(w)) \
    M(Vertex4hvNV,                                           void,          (const Ushort*)(v)) \
    M(VertexAttrib1hNV,                                      void,          (Uint)(index)(Ushort)(x)) \
    M(VertexAttrib1hvNV,                                     void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttrib2hNV,                                      void,          (Uint)(index)(Ushort)(x)(Ushort)(y)) \
    M(VertexAttrib2hvNV,                                     void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttrib3hNV,                                      void,          (Uint)(index)(Ushort)(x)(Ushort)(y)(Ushort)(z)) \
    M(VertexAttrib3hvNV,                                     void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttrib4hNV,                                      void,          (Uint)(index)(Ushort)(x)(Ushort)(y)(Ushort)(z)(Ushort)(w)) \
    M(VertexAttrib4hvNV,                                     void,          (Uint)(index)(const Ushort*)(v)) \
    M(VertexAttribs1hvNV,                                    void,          (Uint)(index)(Isize)(n)(const Ushort*)(v)) \
    M(VertexAttribs2hvNV,                                    void,          (Uint)(index)(Isize)(n)(const Ushort*)(v)) \
    M(VertexAttribs3hvNV,                                    void,          (Uint)(index)(Isize)(n)(const Ushort*)(v)) \
    M(VertexAttribs4hvNV,                                    void,          (Uint)(index)(Isize)(n)(const Ushort*)(v)) \
    M(VertexWeighthNV,                                       void,          (Ushort)(weight)) \
    M(VertexWeighthvNV,                                      void,          (const Ushort*)(weight)) \
    M(VertexAttribDivisorNV,                                 void,          (Uint)(index)(Uint)(divisor)) \
    M(GetInternalformatSampleivNV,                           void,          (Enum)(target)(Enum)(internalformat)(Isize)(samples)(Enum)(pname)(Isize)(bufSize)(Int*)(params)) \
    M(UniformMatrix2x3fvNV,                                  void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix2x4fvNV,                                  void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix3x2fvNV,                                  void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix3x4fvNV,                                  void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix4x2fvNV,                                  void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(UniformMatrix4x3fvNV,                                  void,          (Int)(location)(Isize)(count)(Bool)(transpose)(const Float*)(value)) \
    M(BeginOcclusionQueryNV,                                 void,          (Uint)(id)) \
    M(DeleteOcclusionQueriesNV,                              void,          (Isize)(n)(const Uint*)(ids)) \
    M(EndOcclusionQueryNV,                                   void,          ) \
    M(GenOcclusionQueriesNV,                                 void,          (Isize)(n)(Uint*)(ids)) \
    M(GetOcclusionQueryivNV,                                 void,          (Uint)(id)(Enum)(pname)(Int*)(params)) \
    M(GetOcclusionQueryuivNV,                                void,          (Uint)(id)(Enum)(pname)(Uint*)(params)) \
    M(IsOcclusionQueryNV,                                    Bool,          (Uint)(id)) \
    M(ProgramBufferParametersIivNV,                          void,          (Enum)(target)(Uint)(buffer)(Uint)(index)(Isize)(count)(const Int*)(params)) \
    M(ProgramBufferParametersIuivNV,                         void,          (Enum)(target)(Uint)(buffer)(Uint)(index)(Isize)(count)(const Uint*)(params)) \
    M(ProgramBufferParametersfvNV,                           void,          (Enum)(target)(Uint)(buffer)(Uint)(index)(Isize)(count)(const Float*)(params)) \
    M(CopyPathNV,                                            void,          (Uint)(resultPath)(Uint)(srcPath)) \
    M(CoverFillPathInstancedNV,                              void,          (Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Enum)(coverMode)(Enum)(transformType)(const Float*)(transformValues)) \
    M(CoverFillPathNV,                                       void,          (Uint)(path)(Enum)(coverMode)) \
    M(CoverStrokePathInstancedNV,                            void,          (Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Enum)(coverMode)(Enum)(transformType)(const Float*)(transformValues)) \
    M(CoverStrokePathNV,                                     void,          (Uint)(path)(Enum)(coverMode)) \
    M(DeletePathsNV,                                         void,          (Uint)(path)(Isize)(range)) \
    M(GenPathsNV,                                            Uint,          (Isize)(range)) \
    M(GetPathColorGenfvNV,                                   void,          (Enum)(color)(Enum)(pname)(Float*)(value)) \
    M(GetPathColorGenivNV,                                   void,          (Enum)(color)(Enum)(pname)(Int*)(value)) \
    M(GetPathCommandsNV,                                     void,          (Uint)(path)(Ubyte*)(commands)) \
    M(GetPathCoordsNV,                                       void,          (Uint)(path)(Float*)(coords)) \
    M(GetPathDashArrayNV,                                    void,          (Uint)(path)(Float*)(dashArray)) \
    M(GetPathLengthNV,                                       Float,         (Uint)(path)(Isize)(startSegment)(Isize)(numSegments)) \
    M(GetPathMetricRangeNV,                                  void,          (Bitfield)(metricQueryMask)(Uint)(firstPathName)(Isize)(numPaths)(Isize)(stride)(Float*)(metrics)) \
    M(GetPathMetricsNV,                                      void,          (Bitfield)(metricQueryMask)(Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Isize)(stride)(Float*)(metrics)) \
    M(GetPathParameterfvNV,                                  void,          (Uint)(path)(Enum)(pname)(Float*)(value)) \
    M(GetPathParameterivNV,                                  void,          (Uint)(path)(Enum)(pname)(Int*)(value)) \
    M(GetPathSpacingNV,                                      void,          (Enum)(pathListMode)(Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Float)(advanceScale)(Float)(kerningScale)(Enum)(transformType)(Float*)(returnedSpacing)) \
    M(GetPathTexGenfvNV,                                     void,          (Enum)(texCoordSet)(Enum)(pname)(Float*)(value)) \
    M(GetPathTexGenivNV,                                     void,          (Enum)(texCoordSet)(Enum)(pname)(Int*)(value)) \
    M(GetProgramResourcefvNV,                                void,          (Uint)(program)(Enum)(programInterface)(Uint)(index)(Isize)(propCount)(const Enum*)(props)(Isize)(bufSize)(Isize*)(length)(Float*)(params)) \
    M(InterpolatePathsNV,                                    void,          (Uint)(resultPath)(Uint)(pathA)(Uint)(pathB)(Float)(weight)) \
    M(IsPathNV,                                              Bool,          (Uint)(path)) \
    M(IsPointInFillPathNV,                                   Bool,          (Uint)(path)(Uint)(mask)(Float)(x)(Float)(y)) \
    M(IsPointInStrokePathNV,                                 Bool,          (Uint)(path)(Float)(x)(Float)(y)) \
    M(MatrixLoad3x2fNV,                                      void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixLoad3x3fNV,                                      void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixLoadTranspose3x3fNV,                             void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixMult3x2fNV,                                      void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixMult3x3fNV,                                      void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(MatrixMultTranspose3x3fNV,                             void,          (Enum)(matrixMode)(const Float*)(m)) \
    M(PathColorGenNV,                                        void,          (Enum)(color)(Enum)(genMode)(Enum)(colorFormat)(const Float*)(coeffs)) \
    M(PathCommandsNV,                                        void,          (Uint)(path)(Isize)(numCommands)(const Ubyte*)(commands)(Isize)(numCoords)(Enum)(coordType)(const void*)(coords)) \
    M(PathCoordsNV,                                          void,          (Uint)(path)(Isize)(numCoords)(Enum)(coordType)(const void*)(coords)) \
    M(PathCoverDepthFuncNV,                                  void,          (Enum)(zfunc)) \
    M(PathDashArrayNV,                                       void,          (Uint)(path)(Isize)(dashCount)(const Float*)(dashArray)) \
    M(PathFogGenNV,                                          void,          (Enum)(genMode)) \
    M(PathGlyphIndexArrayNV,                                 Enum,          (Uint)(firstPathName)(Enum)(fontTarget)(const void*)(fontName)(Bitfield)(fontStyle)(Uint)(firstGlyphIndex)(Isize)(numGlyphs)(Uint)(pathParameterTemplate)(Float)(emScale)) \
    M(PathGlyphIndexRangeNV,                                 Enum,          (Enum)(fontTarget)(const void*)(fontName)(Bitfield)(fontStyle)(Uint)(pathParameterTemplate)(Float)(emScale)(Uint*)(baseAndCount)) \
    M(PathGlyphRangeNV,                                      void,          (Uint)(firstPathName)(Enum)(fontTarget)(const void*)(fontName)(Bitfield)(fontStyle)(Uint)(firstGlyph)(Isize)(numGlyphs)(Enum)(handleMissingGlyphs)(Uint)(pathParameterTemplate)(Float)(emScale)) \
    M(PathGlyphsNV,                                          void,          (Uint)(firstPathName)(Enum)(fontTarget)(const void*)(fontName)(Bitfield)(fontStyle)(Isize)(numGlyphs)(Enum)(type)(const void*)(charcodes)(Enum)(handleMissingGlyphs)(Uint)(pathParameterTemplate)(Float)(emScale)) \
    M(PathMemoryGlyphIndexArrayNV,                           Enum,          (Uint)(firstPathName)(Enum)(fontTarget)(IsizePtr)(fontSize)(const void*)(fontData)(Isize)(faceIndex)(Uint)(firstGlyphIndex)(Isize)(numGlyphs)(Uint)(pathParameterTemplate)(Float)(emScale)) \
    M(PathParameterfNV,                                      void,          (Uint)(path)(Enum)(pname)(Float)(value)) \
    M(PathParameterfvNV,                                     void,          (Uint)(path)(Enum)(pname)(const Float*)(value)) \
    M(PathParameteriNV,                                      void,          (Uint)(path)(Enum)(pname)(Int)(value)) \
    M(PathParameterivNV,                                     void,          (Uint)(path)(Enum)(pname)(const Int*)(value)) \
    M(PathStencilDepthOffsetNV,                              void,          (Float)(factor)(Float)(units)) \
    M(PathStencilFuncNV,                                     void,          (Enum)(func)(Int)(ref)(Uint)(mask)) \
    M(PathStringNV,                                          void,          (Uint)(path)(Enum)(format)(Isize)(length)(const void*)(pathString)) \
    M(PathSubCommandsNV,                                     void,          (Uint)(path)(Isize)(commandStart)(Isize)(commandsToDelete)(Isize)(numCommands)(const Ubyte*)(commands)(Isize)(numCoords)(Enum)(coordType)(const void*)(coords)) \
    M(PathSubCoordsNV,                                       void,          (Uint)(path)(Isize)(coordStart)(Isize)(numCoords)(Enum)(coordType)(const void*)(coords)) \
    M(PathTexGenNV,                                          void,          (Enum)(texCoordSet)(Enum)(genMode)(Int)(components)(const Float*)(coeffs)) \
    M(PointAlongPathNV,                                      Bool,          (Uint)(path)(Isize)(startSegment)(Isize)(numSegments)(Float)(distance)(Float*)(x)(Float*)(y)(Float*)(tangentX)(Float*)(tangentY)) \
    M(ProgramPathFragmentInputGenNV,                         void,          (Uint)(program)(Int)(location)(Enum)(genMode)(Int)(components)(const Float*)(coeffs)) \
    M(StencilFillPathInstancedNV,                            void,          (Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Enum)(fillMode)(Uint)(mask)(Enum)(transformType)(const Float*)(transformValues)) \
    M(StencilFillPathNV,                                     void,          (Uint)(path)(Enum)(fillMode)(Uint)(mask)) \
    M(StencilStrokePathInstancedNV,                          void,          (Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Int)(reference)(Uint)(mask)(Enum)(transformType)(const Float*)(transformValues)) \
    M(StencilStrokePathNV,                                   void,          (Uint)(path)(Int)(reference)(Uint)(mask)) \
    M(StencilThenCoverFillPathInstancedNV,                   void,          (Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Enum)(fillMode)(Uint)(mask)(Enum)(coverMode)(Enum)(transformType)(const Float*)(transformValues)) \
    M(StencilThenCoverFillPathNV,                            void,          (Uint)(path)(Enum)(fillMode)(Uint)(mask)(Enum)(coverMode)) \
    M(StencilThenCoverStrokePathInstancedNV,                 void,          (Isize)(numPaths)(Enum)(pathNameType)(const void*)(paths)(Uint)(pathBase)(Int)(reference)(Uint)(mask)(Enum)(coverMode)(Enum)(transformType)(const Float*)(transformValues)) \
    M(StencilThenCoverStrokePathNV,                          void,          (Uint)(path)(Int)(reference)(Uint)(mask)(Enum)(coverMode)) \
    M(TransformPathNV,                                       void,          (Uint)(resultPath)(Uint)(srcPath)(Enum)(transformType)(const Float*)(transformValues)) \
    M(WeightPathsNV,                                         void,          (Uint)(resultPath)(Isize)(numPaths)(const Uint*)(paths)(const Float*)(weights)) \
    M(FlushPixelDataRangeNV,                                 void,          (Enum)(target)) \
    M(PixelDataRangeNV,                                      void,          (Enum)(target)(Isize)(length)(void*)(pointer)) \
    M(PointParameteriNV,                                     void,          (Enum)(pname)(Int)(param)) \
    M(PointParameterivNV,                                    void,          (Enum)(pname)(const Int*)(params)) \
    M(PolygonModeNV,                                         void,          (Enum)(face)(Enum)(mode)) \
    M(GetVideoi64vNV,                                        void,          (Uint)(video_slot)(Enum)(pname)(Int64*)(params)) \
    M(GetVideoivNV,                                          void,          (Uint)(video_slot)(Enum)(pname)(Int*)(params)) \
    M(GetVideoui64vNV,                                       void,          (Uint)(video_slot)(Enum)(pname)(Uint64*)(params)) \
    M(GetVideouivNV,                                         void,          (Uint)(video_slot)(Enum)(pname)(Uint*)(params)) \
    M(PresentFrameDualFillNV,                                void,          (Uint)(video_slot)(Uint64)(minPresentTime)(Uint)(beginPresentTimeId)(Uint)(presentDurationId)(Enum)(type)(Enum)(target0)(Uint)(fill0)(Enum)(target1)(Uint)(fill1)(Enum)(target2)(Uint)(fill2)(Enum)(target3)(Uint)(fill3)) \
    M(PresentFrameKeyedNV,                                   void,          (Uint)(video_slot)(Uint64)(minPresentTime)(Uint)(beginPresentTimeId)(Uint)(presentDurationId)(Enum)(type)(Enum)(target0)(Uint)(fill0)(Uint)(key0)(Enum)(target1)(Uint)(fill1)(Uint)(key1)) \
    M(PrimitiveRestartIndexNV,                               void,          (Uint)(index)) \
    M(PrimitiveRestartNV,                                    void,          ) \
    M(CombinerInputNV,                                       void,          (Enum)(stage)(Enum)(portion)(Enum)(variable)(Enum)(input)(Enum)(mapping)(Enum)(componentUsage)) \
    M(CombinerOutputNV,                                      void,          (Enum)(stage)(Enum)(portion)(Enum)(abOutput)(Enum)(cdOutput)(Enum)(sumOutput)(Enum)(scale)(Enum)(bias)(Bool)(abDotProduct)(Bool)(cdDotProduct)(Bool)(muxSum)) \
    M(CombinerParameterfNV,                                  void,          (Enum)(pname)(Float)(param)) \
    M(CombinerParameterfvNV,                                 void,          (Enum)(pname)(const Float*)(params)) \
    M(CombinerParameteriNV,                                  void,          (Enum)(pname)(Int)(param)) \
    M(CombinerParameterivNV,                                 void,          (Enum)(pname)(const Int*)(params)) \
    M(FinalCombinerInputNV,                                  void,          (Enum)(variable)(Enum)(input)(Enum)(mapping)(Enum)(componentUsage)) \
    M(GetCombinerInputParameterfvNV,                         void,          (Enum)(stage)(Enum)(portion)(Enum)(variable)(Enum)(pname)(Float*)(params)) \
    M(GetCombinerInputParameterivNV,                         void,          (Enum)(stage)(Enum)(portion)(Enum)(variable)(Enum)(pname)(Int*)(params)) \
    M(GetCombinerOutputParameterfvNV,                        void,          (Enum)(stage)(Enum)(portion)(Enum)(pname)(Float*)(params)) \
    M(GetCombinerOutputParameterivNV,                        void,          (Enum)(stage)(Enum)(portion)(Enum)(pname)(Int*)(params)) \
    M(GetFinalCombinerInputParameterfvNV,                    void,          (Enum)(variable)(Enum)(pname)(Float*)(params)) \
    M(GetFinalCombinerInputParameterivNV,                    void,          (Enum)(variable)(Enum)(pname)(Int*)(params)) \
    M(CombinerStageParameterfvNV,                            void,          (Enum)(stage)(Enum)(pname)(const Float*)(params)) \
    M(GetCombinerStageParameterfvNV,                         void,          (Enum)(stage)(Enum)(pname)(Float*)(params)) \
    M(FramebufferSampleLocationsfvNV,                        void,          (Enum)(target)(Uint)(start)(Isize)(count)(const Float*)(v)) \
    M(NamedFramebufferSampleLocationsfvNV,                   void,          (Uint)(framebuffer)(Uint)(start)(Isize)(count)(const Float*)(v)) \
    M(GetBufferParameterui64vNV,                             void,          (Enum)(target)(Enum)(pname)(Uint64*)(params)) \
    M(GetIntegerui64vNV,                                     void,          (Enum)(value)(Uint64*)(result)) \
    M(GetNamedBufferParameterui64vNV,                        void,          (Uint)(buffer)(Enum)(pname)(Uint64*)(params)) \
    M(IsBufferResidentNV,                                    Bool,          (Enum)(target)) \
    M(IsNamedBufferResidentNV,                               Bool,          (Uint)(buffer)) \
    M(MakeBufferNonResidentNV,                               void,          (Enum)(target)) \
    M(MakeBufferResidentNV,                                  void,          (Enum)(target)(Enum)(access)) \
    M(MakeNamedBufferNonResidentNV,                          void,          (Uint)(buffer)) \
    M(MakeNamedBufferResidentNV,                             void,          (Uint)(buffer)(Enum)(access)) \
    M(ProgramUniformui64NV,                                  void,          (Uint)(program)(Int)(location)(Uint64)(value)) \
    M(ProgramUniformui64vNV,                                 void,          (Uint)(program)(Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(Uniformui64NV,                                         void,          (Int)(location)(Uint64)(value)) \
    M(Uniformui64vNV,                                        void,          (Int)(location)(Isize)(count)(const Uint64*)(value)) \
    M(CompressedTexImage3DNV,                                void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Isize)(imageSize)(const void*)(data)) \
    M(CompressedTexSubImage3DNV,                             void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Isize)(imageSize)(const void*)(data)) \
    M(CopyTexSubImage3DNV,                                   void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \
    M(FramebufferTextureLayerNV,                             void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Int)(layer)) \
    M(TexImage3DNV,                                          void,          (Enum)(target)(Int)(level)(Enum)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexSubImage3DNV,                                       void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TextureBarrierNV,                                      void,          ) \
    M(TexImage2DMultisampleCoverageNV,                       void,          (Enum)(target)(Isize)(coverageSamples)(Isize)(colorSamples)(Int)(internalFormat)(Isize)(width)(Isize)(height)(Bool)(fixedSampleLocations)) \
    M(TexImage3DMultisampleCoverageNV,                       void,          (Enum)(target)(Isize)(coverageSamples)(Isize)(colorSamples)(Int)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedSampleLocations)) \
    M(TextureImage2DMultisampleCoverageNV,                   void,          (Uint)(texture)(Enum)(target)(Isize)(coverageSamples)(Isize)(colorSamples)(Int)(internalFormat)(Isize)(width)(Isize)(height)(Bool)(fixedSampleLocations)) \
    M(TextureImage2DMultisampleNV,                           void,          (Uint)(texture)(Enum)(target)(Isize)(samples)(Int)(internalFormat)(Isize)(width)(Isize)(height)(Bool)(fixedSampleLocations)) \
    M(TextureImage3DMultisampleCoverageNV,                   void,          (Uint)(texture)(Enum)(target)(Isize)(coverageSamples)(Isize)(colorSamples)(Int)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedSampleLocations)) \
    M(TextureImage3DMultisampleNV,                           void,          (Uint)(texture)(Enum)(target)(Isize)(samples)(Int)(internalFormat)(Isize)(width)(Isize)(height)(Isize)(depth)(Bool)(fixedSampleLocations)) \
    M(ActiveVaryingNV,                                       void,          (Uint)(program)(const char*)(name)) \
    M(BeginTransformFeedbackNV,                              void,          (Enum)(primitiveMode)) \
    M(BindBufferBaseNV,                                      void,          (Enum)(target)(Uint)(index)(Uint)(buffer)) \
    M(BindBufferOffsetNV,                                    void,          (Enum)(target)(Uint)(index)(Uint)(buffer)(IntPtr)(offset)) \
    M(BindBufferRangeNV,                                     void,          (Enum)(target)(Uint)(index)(Uint)(buffer)(IntPtr)(offset)(IsizePtr)(size)) \
    M(EndTransformFeedbackNV,                                void,          ) \
    M(GetActiveVaryingNV,                                    void,          (Uint)(program)(Uint)(index)(Isize)(bufSize)(Isize*)(length)(Isize*)(size)(Enum*)(type)(char*)(name)) \
    M(GetTransformFeedbackVaryingNV,                         void,          (Uint)(program)(Uint)(index)(Int*)(location)) \
    M(GetVaryingLocationNV,                                  Int,           (Uint)(program)(const char*)(name)) \
    M(TransformFeedbackAttribsNV,                            void,          (Uint)(count)(const Int*)(attribs)(Enum)(bufferMode)) \
    M(TransformFeedbackVaryingsNV,                           void,          (Uint)(program)(Isize)(count)(const Int*)(locations)(Enum)(bufferMode)) \
    M(BindTransformFeedbackNV,                               void,          (Enum)(target)(Uint)(id)) \
    M(DeleteTransformFeedbacksNV,                            void,          (Isize)(n)(const Uint*)(ids)) \
    M(DrawTransformFeedbackNV,                               void,          (Enum)(mode)(Uint)(id)) \
    M(GenTransformFeedbacksNV,                               void,          (Isize)(n)(Uint*)(ids)) \
    M(IsTransformFeedbackNV,                                 Bool,          (Uint)(id)) \
    M(PauseTransformFeedbackNV,                              void,          ) \
    M(ResumeTransformFeedbackNV,                             void,          ) \
    M(VDPAUFiniNV,                                           void,          ) \
    M(VDPAUGetSurfaceivNV,                                   void,          (IntPtr)(surface)(Enum)(pname)(Isize)(bufSize)(Isize*)(length)(Int*)(values)) \
    M(VDPAUInitNV,                                           void,          (const void*)(vdpDevice)(const void*)(getProcAddress)) \
    M(VDPAUIsSurfaceNV,                                      void,          (IntPtr)(surface)) \
    M(VDPAUMapSurfacesNV,                                    void,          (Isize)(numSurfaces)(const IntPtr*)(surfaces)) \
    M(VDPAURegisterOutputSurfaceNV,                          IntPtr,        (const void*)(vdpSurface)(Enum)(target)(Isize)(numTextureNames)(const Uint*)(textureNames)) \
    M(VDPAURegisterVideoSurfaceNV,                           IntPtr,        (const void*)(vdpSurface)(Enum)(target)(Isize)(numTextureNames)(const Uint*)(textureNames)) \
    M(VDPAUSurfaceAccessNV,                                  void,          (IntPtr)(surface)(Enum)(access)) \
    M(VDPAUUnmapSurfacesNV,                                  void,          (Isize)(numSurface)(const IntPtr*)(surfaces)) \
    M(VDPAUUnregisterSurfaceNV,                              void,          (IntPtr)(surface)) \
    M(FlushVertexArrayRangeNV,                               void,          ) \
    M(VertexArrayRangeNV,                                    void,          (Isize)(length)(void*)(pointer)) \
    M(GetVertexAttribLi64vNV,                                void,          (Uint)(index)(Enum)(pname)(Int64*)(params)) \
    M(GetVertexAttribLui64vNV,                               void,          (Uint)(index)(Enum)(pname)(Uint64*)(params)) \
    M(VertexAttribL1i64NV,                                   void,          (Uint)(index)(Int64)(x)) \
    M(VertexAttribL1i64vNV,                                  void,          (Uint)(index)(const Int64*)(v)) \
    M(VertexAttribL1ui64NV,                                  void,          (Uint)(index)(Uint64)(x)) \
    M(VertexAttribL1ui64vNV,                                 void,          (Uint)(index)(const Uint64*)(v)) \
    M(VertexAttribL2i64NV,                                   void,          (Uint)(index)(Int64)(x)(Int64)(y)) \
    M(VertexAttribL2i64vNV,                                  void,          (Uint)(index)(const Int64*)(v)) \
    M(VertexAttribL2ui64NV,                                  void,          (Uint)(index)(Uint64)(x)(Uint64)(y)) \
    M(VertexAttribL2ui64vNV,                                 void,          (Uint)(index)(const Uint64*)(v)) \
    M(VertexAttribL3i64NV,                                   void,          (Uint)(index)(Int64)(x)(Int64)(y)(Int64)(z)) \
    M(VertexAttribL3i64vNV,                                  void,          (Uint)(index)(const Int64*)(v)) \
    M(VertexAttribL3ui64NV,                                  void,          (Uint)(index)(Uint64)(x)(Uint64)(y)(Uint64)(z)) \
    M(VertexAttribL3ui64vNV,                                 void,          (Uint)(index)(const Uint64*)(v)) \
    M(VertexAttribL4i64NV,                                   void,          (Uint)(index)(Int64)(x)(Int64)(y)(Int64)(z)(Int64)(w)) \
    M(VertexAttribL4i64vNV,                                  void,          (Uint)(index)(const Int64*)(v)) \
    M(VertexAttribL4ui64NV,                                  void,          (Uint)(index)(Uint64)(x)(Uint64)(y)(Uint64)(z)(Uint64)(w)) \
    M(VertexAttribL4ui64vNV,                                 void,          (Uint)(index)(const Uint64*)(v)) \
    M(VertexAttribLFormatNV,                                 void,          (Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)) \
    M(BufferAddressRangeNV,                                  void,          (Enum)(pname)(Uint)(index)(Uint64)(address)(IsizePtr)(length)) \
    M(ColorFormatNV,                                         void,          (Int)(size)(Enum)(type)(Isize)(stride)) \
    M(EdgeFlagFormatNV,                                      void,          (Isize)(stride)) \
    M(FogCoordFormatNV,                                      void,          (Enum)(type)(Isize)(stride)) \
    M(GetIntegerui64i_vNV,                                   void,          (Enum)(value)(Uint)(index)(Uint64*)(result)) \
    M(IndexFormatNV,                                         void,          (Enum)(type)(Isize)(stride)) \
    M(NormalFormatNV,                                        void,          (Enum)(type)(Isize)(stride)) \
    M(SecondaryColorFormatNV,                                void,          (Int)(size)(Enum)(type)(Isize)(stride)) \
    M(TexCoordFormatNV,                                      void,          (Int)(size)(Enum)(type)(Isize)(stride)) \
    M(VertexAttribFormatNV,                                  void,          (Uint)(index)(Int)(size)(Enum)(type)(Bool)(normalized)(Isize)(stride)) \
    M(VertexAttribIFormatNV,                                 void,          (Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)) \
    M(VertexFormatNV,                                        void,          (Int)(size)(Enum)(type)(Isize)(stride)) \
    M(AreProgramsResidentNV,                                 Bool,          (Isize)(n)(const Uint*)(ids)(Bool*)(residences)) \
    M(BindProgramNV,                                         void,          (Enum)(target)(Uint)(id)) \
    M(DeleteProgramsNV,                                      void,          (Isize)(n)(const Uint*)(ids)) \
    M(ExecuteProgramNV,                                      void,          (Enum)(target)(Uint)(id)(const Float*)(params)) \
    M(GenProgramsNV,                                         void,          (Isize)(n)(Uint*)(ids)) \
    M(GetProgramParameterdvNV,                               void,          (Enum)(target)(Uint)(index)(Enum)(pname)(Double*)(params)) \
    M(GetProgramParameterfvNV,                               void,          (Enum)(target)(Uint)(index)(Enum)(pname)(Float*)(params)) \
    M(GetProgramStringNV,                                    void,          (Uint)(id)(Enum)(pname)(Ubyte*)(program)) \
    M(GetProgramivNV,                                        void,          (Uint)(id)(Enum)(pname)(Int*)(params)) \
    M(GetTrackMatrixivNV,                                    void,          (Enum)(target)(Uint)(address)(Enum)(pname)(Int*)(params)) \
    M(GetVertexAttribPointervNV,                             void,          (Uint)(index)(Enum)(pname)(void**)(pointer)) \
    M(GetVertexAttribdvNV,                                   void,          (Uint)(index)(Enum)(pname)(Double*)(params)) \
    M(GetVertexAttribfvNV,                                   void,          (Uint)(index)(Enum)(pname)(Float*)(params)) \
    M(GetVertexAttribivNV,                                   void,          (Uint)(index)(Enum)(pname)(Int*)(params)) \
    M(IsProgramNV,                                           Bool,          (Uint)(id)) \
    M(LoadProgramNV,                                         void,          (Enum)(target)(Uint)(id)(Isize)(len)(const Ubyte*)(program)) \
    M(ProgramParameter4dNV,                                  void,          (Enum)(target)(Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(ProgramParameter4dvNV,                                 void,          (Enum)(target)(Uint)(index)(const Double*)(params)) \
    M(ProgramParameter4fNV,                                  void,          (Enum)(target)(Uint)(index)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(ProgramParameter4fvNV,                                 void,          (Enum)(target)(Uint)(index)(const Float*)(params)) \
    M(ProgramParameters4dvNV,                                void,          (Enum)(target)(Uint)(index)(Isize)(num)(const Double*)(params)) \
    M(ProgramParameters4fvNV,                                void,          (Enum)(target)(Uint)(index)(Isize)(num)(const Float*)(params)) \
    M(RequestResidentProgramsNV,                             void,          (Isize)(n)(Uint*)(ids)) \
    M(TrackMatrixNV,                                         void,          (Enum)(target)(Uint)(address)(Enum)(matrix)(Enum)(transform)) \
    M(VertexAttrib1dNV,                                      void,          (Uint)(index)(Double)(x)) \
    M(VertexAttrib1dvNV,                                     void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib1fNV,                                      void,          (Uint)(index)(Float)(x)) \
    M(VertexAttrib1fvNV,                                     void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib1sNV,                                      void,          (Uint)(index)(Short)(x)) \
    M(VertexAttrib1svNV,                                     void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib2dNV,                                      void,          (Uint)(index)(Double)(x)(Double)(y)) \
    M(VertexAttrib2dvNV,                                     void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib2fNV,                                      void,          (Uint)(index)(Float)(x)(Float)(y)) \
    M(VertexAttrib2fvNV,                                     void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib2sNV,                                      void,          (Uint)(index)(Short)(x)(Short)(y)) \
    M(VertexAttrib2svNV,                                     void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib3dNV,                                      void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)) \
    M(VertexAttrib3dvNV,                                     void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib3fNV,                                      void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(z)) \
    M(VertexAttrib3fvNV,                                     void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib3sNV,                                      void,          (Uint)(index)(Short)(x)(Short)(y)(Short)(z)) \
    M(VertexAttrib3svNV,                                     void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4dNV,                                      void,          (Uint)(index)(Double)(x)(Double)(y)(Double)(z)(Double)(w)) \
    M(VertexAttrib4dvNV,                                     void,          (Uint)(index)(const Double*)(v)) \
    M(VertexAttrib4fNV,                                      void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(VertexAttrib4fvNV,                                     void,          (Uint)(index)(const Float*)(v)) \
    M(VertexAttrib4sNV,                                      void,          (Uint)(index)(Short)(x)(Short)(y)(Short)(z)(Short)(w)) \
    M(VertexAttrib4svNV,                                     void,          (Uint)(index)(const Short*)(v)) \
    M(VertexAttrib4ubNV,                                     void,          (Uint)(index)(Ubyte)(x)(Ubyte)(y)(Ubyte)(z)(Ubyte)(w)) \
    M(VertexAttrib4ubvNV,                                    void,          (Uint)(index)(const Ubyte*)(v)) \
    M(VertexAttribPointerNV,                                 void,          (Uint)(index)(Int)(size)(Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(VertexAttribs1dvNV,                                    void,          (Uint)(index)(Isize)(n)(const Double*)(v)) \
    M(VertexAttribs1fvNV,                                    void,          (Uint)(index)(Isize)(n)(const Float*)(v)) \
    M(VertexAttribs1svNV,                                    void,          (Uint)(index)(Isize)(n)(const Short*)(v)) \
    M(VertexAttribs2dvNV,                                    void,          (Uint)(index)(Isize)(n)(const Double*)(v)) \
    M(VertexAttribs2fvNV,                                    void,          (Uint)(index)(Isize)(n)(const Float*)(v)) \
    M(VertexAttribs2svNV,                                    void,          (Uint)(index)(Isize)(n)(const Short*)(v)) \
    M(VertexAttribs3dvNV,                                    void,          (Uint)(index)(Isize)(n)(const Double*)(v)) \
    M(VertexAttribs3fvNV,                                    void,          (Uint)(index)(Isize)(n)(const Float*)(v)) \
    M(VertexAttribs3svNV,                                    void,          (Uint)(index)(Isize)(n)(const Short*)(v)) \
    M(VertexAttribs4dvNV,                                    void,          (Uint)(index)(Isize)(n)(const Double*)(v)) \
    M(VertexAttribs4fvNV,                                    void,          (Uint)(index)(Isize)(n)(const Float*)(v)) \
    M(VertexAttribs4svNV,                                    void,          (Uint)(index)(Isize)(n)(const Short*)(v)) \
    M(VertexAttribs4ubvNV,                                   void,          (Uint)(index)(Isize)(n)(const Ubyte*)(v)) \
    M(BeginVideoCaptureNV,                                   void,          (Uint)(video_capture_slot)) \
    M(BindVideoCaptureStreamBufferNV,                        void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(frame_region)(IntPtr)(offset)) \
    M(BindVideoCaptureStreamTextureNV,                       void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(frame_region)(Enum)(target)(Uint)(texture)) \
    M(EndVideoCaptureNV,                                     void,          (Uint)(video_capture_slot)) \
    M(GetVideoCaptureStreamdvNV,                             void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(pname)(Double*)(params)) \
    M(GetVideoCaptureStreamfvNV,                             void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(pname)(Float*)(params)) \
    M(GetVideoCaptureStreamivNV,                             void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(pname)(Int*)(params)) \
    M(GetVideoCaptureivNV,                                   void,          (Uint)(video_capture_slot)(Enum)(pname)(Int*)(params)) \
    M(VideoCaptureNV,                                        Enum,          (Uint)(video_capture_slot)(Uint*)(sequence_num)(Uint64*)(capture_time)) \
    M(VideoCaptureStreamParameterdvNV,                       void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(pname)(const Double*)(params)) \
    M(VideoCaptureStreamParameterfvNV,                       void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(pname)(const Float*)(params)) \
    M(VideoCaptureStreamParameterivNV,                       void,          (Uint)(video_capture_slot)(Uint)(stream)(Enum)(pname)(const Int*)(params)) \
    M(DepthRangeArrayfvNV,                                   void,          (Uint)(first)(Isize)(count)(const Float *)(v)) \
    M(DepthRangeIndexedfNV,                                  void,          (Uint)(index)(Float)(n)(Float)(f)) \
    M(DisableiNV,                                            void,          (Enum)(target)(Uint)(index)) \
    M(EnableiNV,                                             void,          (Enum)(target)(Uint)(index)) \
    M(GetFloati_vNV,                                         void,          (Enum)(target)(Uint)(index)(Float*)(data)) \
    M(IsEnablediNV,                                          Bool,          (Enum)(target)(Uint)(index)) \
    M(ScissorArrayvNV,                                       void,          (Uint)(first)(Isize)(count)(const Int *)(v)) \
    M(ScissorIndexedNV,                                      void,          (Uint)(index)(Int)(left)(Int)(bottom)(Isize)(width)(Isize)(height)) \
    M(ScissorIndexedvNV,                                     void,          (Uint)(index)(const Int *)(v)) \
    M(ViewportArrayvNV,                                      void,          (Uint)(first)(Isize)(count)(const Float *)(v)) \
    M(ViewportIndexedfNV,                                    void,          (Uint)(index)(Float)(x)(Float)(y)(Float)(w)(Float)(h)) \
    M(ViewportIndexedfvNV,                                   void,          (Uint)(index)(const Float *)(v)) \
    M(ViewportSwizzleNV,                                     void,          (Uint)(index)(Enum)(swizzlex)(Enum)(swizzley)(Enum)(swizzlez)(Enum)(swizzlew)) \
    M(FramebufferTextureMultiviewOVR,                        void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Int)(baseViewIndex)(Isize)(numViews)) \
    M(FramebufferTextureMultisampleMultiviewOVR,             void,          (Enum)(target)(Enum)(attachment)(Uint)(texture)(Int)(level)(Isize)(samples)(Int)(baseViewIndex)(Isize)(numViews)) \
    M(AlphaFuncQCOM,                                         void,          (Enum)(func)(FClamp)(ref)) \
    M(DisableDriverControlQCOM,                              void,          (Uint)(driverControl)) \
    M(EnableDriverControlQCOM,                               void,          (Uint)(driverControl)) \
    M(GetDriverControlStringQCOM,                            void,          (Uint)(driverControl)(Isize)(bufSize)(Isize*)(length)(char*)(driverControlString)) \
    M(GetDriverControlsQCOM,                                 void,          (Int*)(num)(Isize)(size)(Uint*)(driverControls)) \
    M(ExtGetBufferPointervQCOM,                              void,          (Enum)(target)(void**)(params)) \
    M(ExtGetBuffersQCOM,                                     void,          (Uint*)(buffers)(Int)(maxBuffers)(Int*)(numBuffers)) \
    M(ExtGetFramebuffersQCOM,                                void,          (Uint*)(framebuffers)(Int)(maxFramebuffers)(Int*)(numFramebuffers)) \
    M(ExtGetRenderbuffersQCOM,                               void,          (Uint*)(renderbuffers)(Int)(maxRenderbuffers)(Int*)(numRenderbuffers)) \
    M(ExtGetTexLevelParameterivQCOM,                         void,          (Uint)(texture)(Enum)(face)(Int)(level)(Enum)(pname)(Int*)(params)) \
    M(ExtGetTexSubImageQCOM,                                 void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Enum)(format)(Enum)(type)(void*)(texels)) \
    M(ExtGetTexturesQCOM,                                    void,          (Uint*)(textures)(Int)(maxTextures)(Int*)(numTextures)) \
    M(ExtTexObjectStateOverrideiQCOM,                        void,          (Enum)(target)(Enum)(pname)(Int)(param)) \
    M(ExtGetProgramBinarySourceQCOM,                         void,          (Uint)(program)(Enum)(shadertype)(char*)(source)(Int*)(length)) \
    M(ExtGetProgramsQCOM,                                    void,          (Uint*)(programs)(Int)(maxPrograms)(Int*)(numPrograms)) \
    M(ExtGetShadersQCOM,                                     void,          (Uint*)(shaders)(Int)(maxShaders)(Int*)(numShaders)) \
    M(ExtIsProgramBinaryQCOM,                                Bool,          (Uint)(program)) \
    M(FramebufferFoveationConfigQCOM,                        void,          (Uint)(fbo)(Uint)(numLayers)(Uint)(focalPointsPerLayer)(Uint)(requestedFeatures)(Uint*)(providedFeatures)) \
    M(FramebufferFoveationParametersQCOM,                    void,          (Uint)(fbo)(Uint)(layer)(Uint)(focalPoint)(Float)(focalX)(Float)(focalY)(Float)(gainX)(Float)(gainY)(Float)(foveaArea)) \
    M(FramebufferFetchBarrierQCOM,                           void,          ) \
    M(EndTilingQCOM,                                         void,          (Bitfield)(preserveMask)) \
    M(StartTilingQCOM,                                       void,          (Uint)(x)(Uint)(y)(Uint)(width)(Uint)(height)(Bitfield)(preserveMask)) \
    M(AlphaFuncx,                                            void,          (Enum)(func)(IClamp)(ref)) \
    M(ClearColorx,                                           void,          (IClamp)(red)(IClamp)(green)(IClamp)(blue)(IClamp)(alpha)) \
    M(ClearDepthx,                                           void,          (IClamp)(depth)) \
    M(Color4x,                                               void,          (Fixed)(red)(Fixed)(green)(Fixed)(blue)(Fixed)(alpha)) \
    M(DepthRangex,                                           void,          (IClamp)(zNear)(IClamp)(zFar)) \
    M(Fogx,                                                  void,          (Enum)(pname)(Fixed)(param)) \
    M(Fogxv,                                                 void,          (Enum)(pname)(const Fixed*)(params)) \
    M(Frustumf,                                              void,          (Float)(left)(Float)(right)(Float)(bottom)(Float)(top)(Float)(zNear)(Float)(zFar)) \
    M(Frustumx,                                              void,          (Fixed)(left)(Fixed)(right)(Fixed)(bottom)(Fixed)(top)(Fixed)(zNear)(Fixed)(zFar)) \
    M(LightModelx,                                           void,          (Enum)(pname)(Fixed)(param)) \
    M(LightModelxv,                                          void,          (Enum)(pname)(const Fixed*)(params)) \
    M(Lightx,                                                void,          (Enum)(light)(Enum)(pname)(Fixed)(param)) \
    M(Lightxv,                                               void,          (Enum)(light)(Enum)(pname)(const Fixed*)(params)) \
    M(LineWidthx,                                            void,          (Fixed)(width)) \
    M(LoadMatrixx,                                           void,          (const Fixed*)(m)) \
    M(Materialx,                                             void,          (Enum)(face)(Enum)(pname)(Fixed)(param)) \
    M(Materialxv,                                            void,          (Enum)(face)(Enum)(pname)(const Fixed*)(params)) \
    M(MultMatrixx,                                           void,          (const Fixed*)(m)) \
    M(MultiTexCoord4x,                                       void,          (Enum)(target)(Fixed)(s)(Fixed)(t)(Fixed)(r)(Fixed)(q)) \
    M(Normal3x,                                              void,          (Fixed)(nx)(Fixed)(ny)(Fixed)(nz)) \
    M(Orthof,                                                void,          (Float)(left)(Float)(right)(Float)(bottom)(Float)(top)(Float)(zNear)(Float)(zFar)) \
    M(Orthox,                                                void,          (Fixed)(left)(Fixed)(right)(Fixed)(bottom)(Fixed)(top)(Fixed)(zNear)(Fixed)(zFar)) \
    M(PointSizex,                                            void,          (Fixed)(size)) \
    M(PolygonOffsetx,                                        void,          (Fixed)(factor)(Fixed)(units)) \
    M(Rotatex,                                               void,          (Fixed)(angle)(Fixed)(x)(Fixed)(y)(Fixed)(z)) \
    M(SampleCoveragex,                                       void,          (IClamp)(value)(Bool)(invert)) \
    M(Scalex,                                                void,          (Fixed)(x)(Fixed)(y)(Fixed)(z)) \
    M(TexEnvx,                                               void,          (Enum)(target)(Enum)(pname)(Fixed)(param)) \
    M(TexEnvxv,                                              void,          (Enum)(target)(Enum)(pname)(const Fixed*)(params)) \
    M(TexParameterx,                                         void,          (Enum)(target)(Enum)(pname)(Fixed)(param)) \
    M(Translatex,                                            void,          (Fixed)(x)(Fixed)(y)(Fixed)(z)) \
    M(ClipPlanef,                                            void,          (Enum)(plane)(const Float*)(equation)) \
    M(ClipPlanex,                                            void,          (Enum)(plane)(const Fixed*)(equation)) \
    M(GetClipPlanef,                                         void,          (Enum)(pname)(Float*)(eqn)) \
    M(GetClipPlanex,                                         void,          (Enum)(pname)(Fixed*)(eqn)) \
    M(GetFixedv,                                             void,          (Enum)(pname)(Fixed*)(params)) \
    M(GetLightxv,                                            void,          (Enum)(light)(Enum)(pname)(Fixed*)(params)) \
    M(GetMaterialxv,                                         void,          (Enum)(face)(Enum)(pname)(Fixed*)(params)) \
    M(GetTexEnvxv,                                           void,          (Enum)(env)(Enum)(pname)(Fixed*)(params)) \
    M(GetTexParameterxv,                                     void,          (Enum)(target)(Enum)(pname)(Fixed*)(params)) \
    M(PointParameterx,                                       void,          (Enum)(pname)(Fixed)(param)) \
    M(PointParameterxv,                                      void,          (Enum)(pname)(const Fixed*)(params)) \
    M(PointSizePointerOES,                                   void,          (Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(TexParameterxv,                                        void,          (Enum)(target)(Enum)(pname)(const Fixed*)(params)) \
    M(ErrorStringREGAL,                                      const char*,   (Enum)(error)) \
    M(GetExtensionREGAL,                                     Bool,          (const char*)(ext)) \
    M(IsSupportedREGAL,                                      Bool,          (const char*)(ext)) \
    M(LogMessageCallbackREGAL,                               void,          (LogFuncREGAL)(callback)) \
    M(GetProcAddressREGAL,                                   void *,        (const char*)(name)) \
    M(DetailTexFuncSGIS,                                     void,          (Enum)(target)(Isize)(n)(const Float*)(points)) \
    M(GetDetailTexFuncSGIS,                                  void,          (Enum)(target)(Float*)(points)) \
    M(FogFuncSGIS,                                           void,          (Isize)(n)(const Float*)(points)) \
    M(GetFogFuncSGIS,                                        void,          (Float*)(points)) \
    M(SampleMaskSGIS,                                        void,          (FClamp)(value)(Bool)(invert)) \
    M(SamplePatternSGIS,                                     void,          (Enum)(pattern)) \
    M(InterleavedTextureCoordSetsSGIS,                       void,          (Int)(factor)) \
    M(SelectTextureCoordSetSGIS,                             void,          (Enum)(target)) \
    M(SelectTextureSGIS,                                     void,          (Enum)(target)) \
    M(SelectTextureTransformSGIS,                            void,          (Enum)(target)) \
    M(MultisampleSubRectPosSGIS,                             void,          (Int)(x)(Int)(y)) \
    M(GetSharpenTexFuncSGIS,                                 void,          (Enum)(target)(Float*)(points)) \
    M(SharpenTexFuncSGIS,                                    void,          (Enum)(target)(Isize)(n)(const Float*)(points)) \
    M(TexImage4DSGIS,                                        void,          (Enum)(target)(Int)(level)(Enum)(internalformat)(Isize)(width)(Isize)(height)(Isize)(depth)(Isize)(extent)(Int)(border)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(TexSubImage4DSGIS,                                     void,          (Enum)(target)(Int)(level)(Int)(xoffset)(Int)(yoffset)(Int)(zoffset)(Int)(woffset)(Isize)(width)(Isize)(height)(Isize)(depth)(Isize)(extent)(Enum)(format)(Enum)(type)(const void*)(pixels)) \
    M(GetTexFilterFuncSGIS,                                  void,          (Enum)(target)(Enum)(filter)(Float*)(weights)) \
    M(TexFilterFuncSGIS,                                     void,          (Enum)(target)(Enum)(filter)(Isize)(n)(const Float*)(weights)) \
    M(AsyncMarkerSGIX,                                       void,          (Uint)(marker)) \
    M(DeleteAsyncMarkersSGIX,                                void,          (Uint)(marker)(Isize)(range)) \
    M(FinishAsyncSGIX,                                       Int,           (Uint*)(markerp)) \
    M(GenAsyncMarkersSGIX,                                   Uint,          (Isize)(range)) \
    M(IsAsyncMarkerSGIX,                                     Bool,          (Uint)(marker)) \
    M(PollAsyncSGIX,                                         Int,           (Uint*)(markerp)) \
    M(AddressSpace,                                          void,          (Enum)(space)(Bitfield)(mask)) \
    M(DataPipe,                                              Int,           (Enum)(space)) \
    M(FlushRasterSGIX,                                       void,          ) \
    M(FogLayersSGIX,                                         void,          (Isize)(n)(const Float*)(points)) \
    M(GetFogLayersSGIX,                                      void,          (Float*)(points)) \
    M(TextureFogSGIX,                                        void,          (Enum)(pname)) \
    M(FragmentColorMaterialSGIX,                             void,          (Enum)(face)(Enum)(mode)) \
    M(FragmentLightModelfSGIX,                               void,          (Enum)(pname)(Float)(param)) \
    M(FragmentLightModelfvSGIX,                              void,          (Enum)(pname)(Float*)(params)) \
    M(FragmentLightModeliSGIX,                               void,          (Enum)(pname)(Int)(param)) \
    M(FragmentLightModelivSGIX,                              void,          (Enum)(pname)(Int*)(params)) \
    M(FragmentLightfSGIX,                                    void,          (Enum)(light)(Enum)(pname)(Float)(param)) \
    M(FragmentLightfvSGIX,                                   void,          (Enum)(light)(Enum)(pname)(Float*)(params)) \
    M(FragmentLightiSGIX,                                    void,          (Enum)(light)(Enum)(pname)(Int)(param)) \
    M(FragmentLightivSGIX,                                   void,          (Enum)(light)(Enum)(pname)(Int*)(params)) \
    M(FragmentMaterialfSGIX,                                 void,          (Enum)(face)(Enum)(pname)(const Float)(param)) \
    M(FragmentMaterialfvSGIX,                                void,          (Enum)(face)(Enum)(pname)(const Float*)(params)) \
    M(FragmentMaterialiSGIX,                                 void,          (Enum)(face)(Enum)(pname)(const Int)(param)) \
    M(FragmentMaterialivSGIX,                                void,          (Enum)(face)(Enum)(pname)(const Int*)(params)) \
    M(GetFragmentLightfvSGIX,                                void,          (Enum)(light)(Enum)(value)(Float*)(data)) \
    M(GetFragmentLightivSGIX,                                void,          (Enum)(light)(Enum)(value)(Int*)(data)) \
    M(GetFragmentMaterialfvSGIX,                             void,          (Enum)(face)(Enum)(pname)(const Float*)(data)) \
    M(GetFragmentMaterialivSGIX,                             void,          (Enum)(face)(Enum)(pname)(const Int*)(data)) \
    M(FrameZoomSGIX,                                         void,          (Int)(factor)) \
    M(IglooInterfaceSGIX,                                    void,          (Enum)(pname)(void*)(param)) \
    M(AllocMPEGPredictorsSGIX,                               void,          (Isize)(width)(Isize)(height)(Isize)(n)(Uint*)(predictors)) \
    M(DeleteMPEGPredictorsSGIX,                              void,          (Isize)(n)(Uint*)(predictors)) \
    M(GenMPEGPredictorsSGIX,                                 void,          (Isize)(n)(Uint*)(predictors)) \
    M(GetMPEGParameterfvSGIX,                                void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetMPEGParameterivSGIX,                                void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetMPEGPredictorSGIX,                                  void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(pixels)) \
    M(GetMPEGQuantTableubv,                                  void,          (Enum)(target)(Ubyte*)(values)) \
    M(IsMPEGPredictorSGIX,                                   Bool,          (Uint)(predictor)) \
    M(MPEGPredictorSGIX,                                     void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(pixels)) \
    M(MPEGQuantTableubv,                                     void,          (Enum)(target)(Ubyte*)(values)) \
    M(SwapMPEGPredictorsSGIX,                                void,          (Enum)(target0)(Enum)(target1)) \
    M(GetNonlinLightfvSGIX,                                  void,          (Enum)(light)(Enum)(pname)(Int*)(terms)(Float*)(data)) \
    M(GetNonlinMaterialfvSGIX,                               void,          (Enum)(face)(Enum)(pname)(Int*)(terms)(const Float*)(data)) \
    M(NonlinLightfvSGIX,                                     void,          (Enum)(light)(Enum)(pname)(Int)(terms)(Float*)(params)) \
    M(NonlinMaterialfvSGIX,                                  void,          (Enum)(face)(Enum)(pname)(Int)(terms)(const Float*)(params)) \
    M(PixelTexGenSGIX,                                       void,          (Enum)(mode)) \
    M(DeformSGIX,                                            void,          (Bitfield)(mask)) \
    M(LoadIdentityDeformationMapSGIX,                        void,          (Bitfield)(mask)) \
    M(MeshBreadthSGIX,                                       void,          (Int)(breadth)) \
    M(MeshStrideSGIX,                                        void,          (Int)(stride)) \
    M(ReferencePlaneSGIX,                                    void,          (const Double*)(equation)) \
    M(SpriteParameterfSGIX,                                  void,          (Enum)(pname)(Float)(param)) \
    M(SpriteParameterfvSGIX,                                 void,          (Enum)(pname)(Float*)(params)) \
    M(SpriteParameteriSGIX,                                  void,          (Enum)(pname)(Int)(param)) \
    M(SpriteParameterivSGIX,                                 void,          (Enum)(pname)(Int*)(params)) \
    M(TagSampleBufferSGIX,                                   void,          ) \
    M(GetVectorOperationSGIX,                                void,          (Enum)(operation)) \
    M(VectorOperationSGIX,                                   void,          (Enum)(operation)) \
    M(AreVertexArraysResidentSGIX,                           Bool,          (Isize)(n)(const Uint*)(arrays)(Bool*)(residences)) \
    M(BindVertexArraySGIX,                                   void,          (Uint)(array)) \
    M(DeleteVertexArraysSGIX,                                void,          (Isize)(n)(const Uint*)(arrays)) \
    M(GenVertexArraysSGIX,                                   void,          (Isize)(n)(Uint*)(arrays)) \
    M(IsVertexArraySGIX,                                     Bool,          (Uint)(array)) \
    M(PrioritizeVertexArraysSGIX,                            void,          (Isize)(n)(const Uint*)(arrays)(const FClamp*)(priorities)) \
    M(ColorTableParameterfvSGI,                              void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(ColorTableParameterivSGI,                              void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(ColorTableSGI,                                         void,          (Enum)(target)(Enum)(internalformat)(Isize)(width)(Enum)(format)(Enum)(type)(const void*)(table)) \
    M(CopyColorTableSGI,                                     void,          (Enum)(target)(Enum)(internalformat)(Int)(x)(Int)(y)(Isize)(width)) \
    M(GetColorTableParameterfvSGI,                           void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetColorTableParameterivSGI,                           void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(GetColorTableSGI,                                      void,          (Enum)(target)(Enum)(format)(Enum)(type)(void*)(table)) \
    M(GetPixelTransformParameterfvSGI,                       void,          (Enum)(target)(Enum)(pname)(Float*)(params)) \
    M(GetPixelTransformParameterivSGI,                       void,          (Enum)(target)(Enum)(pname)(Int*)(params)) \
    M(PixelTransformParameterfSGI,                           void,          (Enum)(target)(Enum)(pname)(Float)(param)) \
    M(PixelTransformParameterfvSGI,                          void,          (Enum)(target)(Enum)(pname)(const Float*)(params)) \
    M(PixelTransformParameteriSGI,                           void,          (Enum)(target)(Enum)(pname)(Int)(param)) \
    M(PixelTransformParameterivSGI,                          void,          (Enum)(target)(Enum)(pname)(const Int*)(params)) \
    M(PixelTransformSGI,                                     void,          (Enum)(target)) \
    M(FinishTextureSUNX,                                     void,          ) \
    M(GlobalAlphaFactorbSUN,                                 void,          (Byte)(factor)) \
    M(GlobalAlphaFactordSUN,                                 void,          (Double)(factor)) \
    M(GlobalAlphaFactorfSUN,                                 void,          (Float)(factor)) \
    M(GlobalAlphaFactoriSUN,                                 void,          (Int)(factor)) \
    M(GlobalAlphaFactorsSUN,                                 void,          (Short)(factor)) \
    M(GlobalAlphaFactorubSUN,                                void,          (Ubyte)(factor)) \
    M(GlobalAlphaFactoruiSUN,                                void,          (Uint)(factor)) \
    M(GlobalAlphaFactorusSUN,                                void,          (Ushort)(factor)) \
    M(ReadVideoPixelsSUN,                                    void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)(Enum)(format)(Enum)(type)(void*)(pixels)) \
    M(ReplacementCodePointerSUN,                             void,          (Enum)(type)(Isize)(stride)(const void*)(pointer)) \
    M(ReplacementCodeubSUN,                                  void,          (Ubyte)(code)) \
    M(ReplacementCodeubvSUN,                                 void,          (const Ubyte*)(code)) \
    M(ReplacementCodeuiSUN,                                  void,          (Uint)(code)) \
    M(ReplacementCodeuivSUN,                                 void,          (const Uint*)(code)) \
    M(ReplacementCodeusSUN,                                  void,          (Ushort)(code)) \
    M(ReplacementCodeusvSUN,                                 void,          (const Ushort*)(code)) \
    M(Color3fVertex3fSUN,                                    void,          (Float)(r)(Float)(g)(Float)(b)(Float)(x)(Float)(y)(Float)(z)) \
    M(Color3fVertex3fvSUN,                                   void,          (const Float*)(c)(const Float*)(v)) \
    M(Color4fNormal3fVertex3fSUN,                            void,          (Float)(r)(Float)(g)(Float)(b)(Float)(a)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(Color4fNormal3fVertex3fvSUN,                           void,          (const Float*)(c)(const Float*)(n)(const Float*)(v)) \
    M(Color4ubVertex2fSUN,                                   void,          (Ubyte)(r)(Ubyte)(g)(Ubyte)(b)(Ubyte)(a)(Float)(x)(Float)(y)) \
    M(Color4ubVertex2fvSUN,                                  void,          (const Ubyte*)(c)(const Float*)(v)) \
    M(Color4ubVertex3fSUN,                                   void,          (Ubyte)(r)(Ubyte)(g)(Ubyte)(b)(Ubyte)(a)(Float)(x)(Float)(y)(Float)(z)) \
    M(Color4ubVertex3fvSUN,                                  void,          (const Ubyte*)(c)(const Float*)(v)) \
    M(Normal3fVertex3fSUN,                                   void,          (Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(Normal3fVertex3fvSUN,                                  void,          (const Float*)(n)(const Float*)(v)) \
    M(ReplacementCodeuiColor3fVertex3fSUN,                   void,          (Uint)(rc)(Float)(r)(Float)(g)(Float)(b)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiColor3fVertex3fvSUN,                  void,          (const Uint*)(rc)(const Float*)(c)(const Float*)(v)) \
    M(ReplacementCodeuiColor4fNormal3fVertex3fSUN,           void,          (Uint)(rc)(Float)(r)(Float)(g)(Float)(b)(Float)(a)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiColor4fNormal3fVertex3fvSUN,          void,          (const Uint*)(rc)(const Float*)(c)(const Float*)(n)(const Float*)(v)) \
    M(ReplacementCodeuiColor4ubVertex3fSUN,                  void,          (Uint)(rc)(Ubyte)(r)(Ubyte)(g)(Ubyte)(b)(Ubyte)(a)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiColor4ubVertex3fvSUN,                 void,          (const Uint*)(rc)(const Ubyte*)(c)(const Float*)(v)) \
    M(ReplacementCodeuiNormal3fVertex3fSUN,                  void,          (Uint)(rc)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiNormal3fVertex3fvSUN,                 void,          (const Uint*)(rc)(const Float*)(n)(const Float*)(v)) \
    M(ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN, void,          (Uint)(rc)(Float)(s)(Float)(t)(Float)(r)(Float)(g)(Float)(b)(Float)(a)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN,void,          (const Uint*)(rc)(const Float*)(tc)(const Float*)(c)(const Float*)(n)(const Float*)(v)) \
    M(ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN,        void,          (Uint)(rc)(Float)(s)(Float)(t)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN,       void,          (const Uint*)(rc)(const Float*)(tc)(const Float*)(n)(const Float*)(v)) \
    M(ReplacementCodeuiTexCoord2fVertex3fSUN,                void,          (Uint)(rc)(Float)(s)(Float)(t)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiTexCoord2fVertex3fvSUN,               void,          (const Uint*)(rc)(const Float*)(tc)(const Float*)(v)) \
    M(ReplacementCodeuiVertex3fSUN,                          void,          (Uint)(rc)(Float)(x)(Float)(y)(Float)(z)) \
    M(ReplacementCodeuiVertex3fvSUN,                         void,          (const Uint*)(rc)(const Float*)(v)) \
    M(TexCoord2fColor3fVertex3fSUN,                          void,          (Float)(s)(Float)(t)(Float)(r)(Float)(g)(Float)(b)(Float)(x)(Float)(y)(Float)(z)) \
    M(TexCoord2fColor3fVertex3fvSUN,                         void,          (const Float*)(tc)(const Float*)(c)(const Float*)(v)) \
    M(TexCoord2fColor4fNormal3fVertex3fSUN,                  void,          (Float)(s)(Float)(t)(Float)(r)(Float)(g)(Float)(b)(Float)(a)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(TexCoord2fColor4fNormal3fVertex3fvSUN,                 void,          (const Float*)(tc)(const Float*)(c)(const Float*)(n)(const Float*)(v)) \
    M(TexCoord2fColor4ubVertex3fSUN,                         void,          (Float)(s)(Float)(t)(Ubyte)(r)(Ubyte)(g)(Ubyte)(b)(Ubyte)(a)(Float)(x)(Float)(y)(Float)(z)) \
    M(TexCoord2fColor4ubVertex3fvSUN,                        void,          (const Float*)(tc)(const Ubyte*)(c)(const Float*)(v)) \
    M(TexCoord2fNormal3fVertex3fSUN,                         void,          (Float)(s)(Float)(t)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)) \
    M(TexCoord2fNormal3fVertex3fvSUN,                        void,          (const Float*)(tc)(const Float*)(n)(const Float*)(v)) \
    M(TexCoord2fVertex3fSUN,                                 void,          (Float)(s)(Float)(t)(Float)(x)(Float)(y)(Float)(z)) \
    M(TexCoord2fVertex3fvSUN,                                void,          (const Float*)(tc)(const Float*)(v)) \
    M(TexCoord4fColor4fNormal3fVertex4fSUN,                  void,          (Float)(s)(Float)(t)(Float)(p)(Float)(q)(Float)(r)(Float)(g)(Float)(b)(Float)(a)(Float)(nx)(Float)(ny)(Float)(nz)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(TexCoord4fColor4fNormal3fVertex4fvSUN,                 void,          (const Float*)(tc)(const Float*)(c)(const Float*)(n)(const Float*)(v)) \
    M(TexCoord4fVertex4fSUN,                                 void,          (Float)(s)(Float)(t)(Float)(p)(Float)(q)(Float)(x)(Float)(y)(Float)(z)(Float)(w)) \
    M(TexCoord4fVertex4fvSUN,                                void,          (const Float*)(tc)(const Float*)(v)) \
    M(AddSwapHintRectWIN,                                    void,          (Int)(x)(Int)(y)(Isize)(width)(Isize)(height)) \

#pragma endregion

    bool Supports(const char* name);
    Enum InitGLEW();

#define COMMA() ,
#define EMPTY()
#define WAIT(X) X EMPTY() ()
#define RUN(X) X
#define CAT(A, B) A##B
#define CAT2(A, B) CAT(A, B)
#define DEL_FIRST(X, ...) __VA_ARGS__
#define DEF_FN(NAME, RET, ARGS) RET NAME(RUN(DEL_FIRST EMPTY() (CAT2(ARGS_1 ARGS, END))));
#define ARGS_1(T) WAIT(COMMA) T ARGS_2
#define ARGS_2(V) V ARGS_1
#define ARGS_1END
#define ARGS_2END

    GLPORT_ON_FUNCTIONS(DEF_FN)

#undef COMMA
#undef EMPTY
#undef WAIT
#undef RUN
#undef CAT
#undef CAT2
#undef DEL_FIRST
#undef DEF_FN
#undef ARGS_1
#undef ARGS_2
#undef ARGS_1END
#undef ARGS_2END
}