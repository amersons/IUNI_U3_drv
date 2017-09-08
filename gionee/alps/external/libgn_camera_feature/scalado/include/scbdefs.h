/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2011 Scalado AB. All rights reserved.                           .
.                                                                             .
.    Technologies used in this source code are patented or patent pending     .
.    by Scalado AB Swedish Org. Number, 556594-6885.                          .
.                                                                             .
.    All Intellectual Property Rights related to this source code,            .
.    belongs to Scalado AB.                                                   .
.                                                                             .
.    This source code is furnished under license agreement and may be used    .
.    or copied only in accordance with terms of such license agreement.       .
.                                                                             .
.    Except as permitted by such license agreement, no part of this source    .
.    code may be reproduced, stored in a retrieval system, or transmitted,    .
.    in any form or by any means, electronic, mechanical, recording, or       .
.    otherwise, without the prior written permission of Scalado.              .
.                                                                             .
.    Scalado assumes no responsibility or liability for any errors or         .
.    inaccuracies in this source code or any consequential, incidental or     .
.    indirect damage arising out of the use of this source code.              .
.                                                                             .
.    Scalado and the Scalado logo are either registered trademarks or         .
.    trademarks of Scalado AB in Sweden and/or other countries.               .
.                                                                             .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/

#ifndef SCBDEFS_H
#define SCBDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#define IS_ALIGNED(p, a) ((((CTuint32) p) & ((a) - 1)) == 0)

#if defined(_MSC_VER) && defined(SCB_DBGMODE_MEMORY)
// put all const data into .rdata$<x> so that
// we can find the segment for debugging purposes.
#pragma const_seg(".rdata$dbgmda_consts")
#define SCB_DBGMDA_CONSTS_SEGMENT_IS_ON
#endif

/* A compile-time static assert */
#define SCB_STATIC_ASSERT(expression) \
    extern char _static_assert[(expression)?1:-1]


#define SCB_REVISION_STR _SD("$Rev$")
#ifndef WIN32 
#if (__STDC_VERSION__ >= 199901L)
#define SCB_C99
#endif
#endif


//=============================================================================
/**
    @ingroup types_n_defs
    @file scbdefs.h
    @brief Defines public symbols, macros and types.
*/
//=============================================================================
/**
    @addtogroup types_n_defs
    @brief Defines public symbols, macros and types.

    @par Naming conventions
    Type names are always prefixed with @c CT. Following the @c CT prefix is
    always the specifier of the type. If the first letter of the type
    specifier is lower case it signifies that it's primitive (e.g @c CTint) and
    upper case that it's complex (e.g @c CTRect).

    @par Visibility
    Complex types are always public within this header as it by definition
    doesn't require linkage.

    @{
*/
//-----------------------------------------------------------------------------

/**
    @name Primitive data types
*/
// @{
typedef signed char         CTint8;         ///< 8 bit signed integer
typedef unsigned char       CTuint8;        ///< 8 bit unsigned integer

typedef short               CTint16;        ///< 16 bit signed integer
typedef unsigned short      CTuint16;       ///< 16 bit unsigned integer

#ifdef __LP64__
    /* Support for GCC 64 bit targets where long int and pointer 
       both use 64-bits and int uses 32-bit. */
    typedef int             CTint32;        ///< 32 bit signed integer
    typedef unsigned int    CTuint32;       ///< 32 bit unsigned integer

#else
    typedef long            CTint32;        ///< 32 bit signed integer
    typedef unsigned long   CTuint32;       ///< 32 bit unsigned integer

#endif


typedef float               CTfloat;        ///< Float
typedef double              CTdouble;       ///< Double
typedef unsigned char       CTbyte;         ///< Unsigned char
typedef char                CTchar;         ///< Char
// @}
//-----------------------------------------------------------------------------

/**
    @brief 64 bit unsigned integer representation.
*/
typedef struct CTuint64
{
    CTuint32    low;    ///< Least significant bits.
    CTuint32    high;   ///< Most significant bits.
}CTuint64;

/**
    @brief 128 bit unsigned integer representation.
*/
typedef CTuint8 CTuint128[16];

/**
    @brief Unsigned rational representation.
*/
typedef struct CTRational
{
    CTuint32 numerator;     ///< Numerator.
    CTuint32 denominator;   ///< Denominator.
} CTRational;

/**
    @brief Signed rational representation.
*/
typedef struct CTSRational
{
    CTint32 numerator;      ///< Numerator.
    CTint32 denominator;    ///< Denominator.
} CTSRational;

#if !defined( __MARM__ )
    typedef unsigned short  CTwchar;
#else
    typedef unsigned short  CTwchar;
#endif


#define SCB_MAXPATH         260


// Make sure primitive types have valid sizes.

SCB_STATIC_ASSERT( sizeof( CTchar ) == 1 );
SCB_STATIC_ASSERT( sizeof( CTbyte ) == 1 );
SCB_STATIC_ASSERT( sizeof( CTint8 ) == 1 );
SCB_STATIC_ASSERT( sizeof( CTint16 ) == 2 );
SCB_STATIC_ASSERT( sizeof( CTint32 ) == 4 );
SCB_STATIC_ASSERT( sizeof( CTuint8 ) == 1 );
SCB_STATIC_ASSERT( sizeof( CTuint16 ) == 2 );
SCB_STATIC_ASSERT( sizeof( CTuint32 ) == 4 );

typedef CTuint32 CTbool;    ///< Boolean (true/false).

#ifndef __cplusplus
    #define true  1
    #define false 0
#endif


//  -  Byte order (endian) configuration.
#define SCB_LITTLE_ENDIAN   1
#define SCB_BIG_ENDIAN      2

#if defined( BYTE_ORDER_LITTLE_ENDIAN )
    #define SCB_BYTE_ORDER SCB_LITTLE_ENDIAN
#elif defined( BYTE_ORDER_BIG_ENDIAN )
    #define SCB_BYTE_ORDER SCB_BIG_ENDIAN
#elif defined( __BIG_ENDIAN )
    #define SCB_BYTE_ORDER SCB_BIG_ENDIAN
#else // None specified, default to little endian.
#if defined(_MSC_VER)
    #pragma message("**WARNING, no byte order specified on build commandline, defaulting to SCB_LITTLE_ENDIAN.")
#endif
    #define SCB_BYTE_ORDER SCB_LITTLE_ENDIAN
#endif

// Just to make sure..
#ifndef SCB_BYTE_ORDER
    #error No byte order configured!
#endif

//-----------------------------------------------------------------------------
/**
    @name Object framework core definitions
    @brief
    Macros and types needed to declare classes.

    The following macros and definitions are part of the object framework, and
    are needed (at compile time) by other header files that define classes,
    which are based on the Scalado object framework; i.e. classes that are
    derived from @ref ctobject "CTObject".
*/
//@{

/**
    @brief
    Defines an interface Id used when querying classes or interface for their
    type.

    There is only one such construct, because it serves a similar role
    in the case of both interfaces and classes, so there's no real point to
    provide two distinct implementations.

*/
typedef struct
{
    const char *pName;///< The name of the interface.
} CTInterfaceId;


//    It is necessary to check this condition, because class definition uses this
//    size during interface table definitions.
SCB_STATIC_ASSERT(sizeof(CTInterfaceId) > sizeof(CTuint8));

/**
    @brief
    Returns the class's Id, given its name.

    eg: SCC_CLASS_ID(CTObject) would be replaced by CTObjectId
*/
#define SCC_CLASS_ID(className) className##Id

/**
    @brief
    Returns the interface's Id, given its name.

    eg: SCC_INTERFACE_ID(CTSerializable) would be replaced by CTSerializableId
*/
#define SCC_INTERFACE_ID(interfaceName) interfaceName##Id

/**
    @brief
    Returns the variable name of the class, given its name.

    eg: SCC_CLASS_NAME(CTObject) would be replaced by CTObjectClass

*/
#define SCC_CLASS_NAME(className) className##Class

/**
    @brief
    This macro declares the necessary parts of a class in order to use it in
    code.

    Currently that is an external declaration of the class id, and a
    typedef for the class structure (which is private in this context).

*/
#define SCC_CLASS_DECLARE(className) \
    extern const CTInterfaceId SCC_CLASS_ID(className); \
    extern const CTClass SCC_CLASS_NAME(className); \
    typedef struct className className

/**
    @brief
    Declares an interface for public use.

    This is necessary to invoke in the public header file, as it declares the
    interface id and interface structure.

*/
#define SCC_INTERFACE_DECLARE(interfaceName) \
    extern const CTInterfaceId SCC_INTERFACE_ID(interfaceName); \
    typedef struct interfaceName interfaceName

/**
    @brief
    Holds information about the class Id, parent/super
    class, and virtual function table etc.

    Although, the function table may not always be complete, and it does not
    represent the function table of a live object of that class (necessarily).

    The members of this struct are not intended to be accessed directly.

*/
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4510 )
#pragma warning( disable : 4512 )
#pragma warning( disable : 4610 )
#endif

typedef struct CTClass CTClass;
struct CTClass
{
    const CTInterfaceId classId;// Identifier of the class
    const CTClass *const pSuperClass;// Pointer to the super class
    void *const pVtable;// Virtual function table for this class
    CTuint32 vtableSize;// Size of the virtual function table
    CTbool *const pInitialized;// Tell if the class has been initialized or not
    void (*initFunction)(void);// Pointer to function used to initialize this class
    CTuint32 numInterfaces;// Number of interfaces implemented by this class
    const void *pInterfaces;// Interface table
};

#ifdef WIN32
#pragma warning( pop )
#endif
//@}
// end named section: "Object framework core definitions" ----------------------

/**
    @brief
    Defines a color mode/format by specifying the depth and alignment of the
    channels comprising the color.
*/
typedef enum 
{
    CM_UNDEFINED     = 0x0000,

    CM_YUV420        = 0x0001,          ///< Standard interleaved YUV420
    //CM_YUV422      = 0x0002,          // AYUV422
    //CM_AYUV4444    = 0x0004,          // AYUV4444
    CM_AYUV4444      = 0x0040,          ///< Standard interleaved AYUV, 4 byte per pixels.
    CM_RGB888        = 0x0008,          ///< 3 byte per pixels, interleaved.
    CM_RGB161616     = 0x0009,          ///< 8 byte per pixel, interleaved.
    CM_RGB444        = 0x0010,          ///< 12 bits per pixel, interleaved.
    CM_RGB555        = 0x0011,          ///< 15 bits per pixel, interleaved.
    CM_RGB565        = 0x0020,          ///< 5 bits red, 6 bits green, 5 bits blue, interleaved.
    CM_RGB565D       = 0x0021,          ///< 5 bits red, 6 bits green, 5 bits blue, interleaved with dithering to minimize gradient errors.
    CM_RGB565FD      = 0x0023,          ///< 5 bits red, 6 bits green, 5 bits blue, interleaved with dithering to minimize gradient errors. Faster but less visual appealing than CM_RGB565D.
    CM_ARGB8565      = 0x0022,          ///< 24 bits per pixel, 8 bits for alpha, followed by 5 bits red, 6 bits green, 5 bits blue, interleaved.
	CM_RGBA5658      = 0x0024,          ///< 24 bits per pixel, 5 bits red, followed by 6 bits green, 5 bits blue, 8 bits for alpha, interleaved.
    //CM_ARGB8888    = 0x0040,          // ARGB8888
    CM_ARGB8888      = 0x0004,          ///< 4 bytes per pixel, interleaved.
    CM_BGR888        = 0x0080,          ///< 3 bytes per pixel, interleaved.
    CM_BGRA8888      = 0x0100,          ///< 4 bytes per pixel, interleaved.

    CM_GRAY1         = 0x0200,          ///< 1 bit grayscale, 1 bit per pixel.
    CM_GRAY2         = 0x0400,          ///< 2 bit grayscale, 2 bit per pixel.
    CM_GRAY4         = 0x0800,          ///< 4 bit grayscale, 4 bit per pixel.
    CM_GRAY8         = 0x1000,          ///< 8 bit grayscale, 8 bit per pixel.
    CM_GRAY16        = 0x1003,          ///< 16 bit grayscale, 16 bit per pixel.
    CM_COLOR_1_ALFA  = 0x1007,          ///< 1 bit colormode with transparency.
    CM_COLOR_2       = 0x2000,          ///< 1 bit colormode.
    CM_COLOR_4       = 0x4000,          ///< 2 bit colormode.
    CM_COLOR_16      = 0x8000,          ///< 4 bit colormode.
    CM_COLOR_256     = 0x1001,          ///< 8 bit colormode.
    CM_GRAYALPHA88   = 0x1002,          ///< 2 byte per pixel. 1 byte grayscale, 1 byte alpha interleaved.
    CM_GRAYALPHA1616 = 0x1005,          ///< 4 byte per pixel. 2 byte grayscale, 2 byte alpha interleaved.
    CM_RGBA8888      = 0x1004,          ///< 4 byte per pixel, interleaved.
    CM_RGBA16161616  = 0x1006,          ///< 8 byte per pixl, interleaved.

    CM_BGR444        = 0x1100,          ///< 12 bits per pixel, interleaved.
    CM_BGR555        = 0x1101,          ///< 15 bits per pixel, interleaved.
    CM_BGR565        = 0x1400,          ///< 5 bits blue 6 bits green, 5 bits red, interleaved.
    CM_BGR565D       = 0x1401,          ///< 5 bits blue, 6 bits green, 5 bits red, interleaved with dithering to minimize gradient errors.
    CM_RGB565_G0     = 0x1800,          ///< 5 bits red, 5 bits green, 1 bit alpha, 5 bits blue, interleaved.
    CM_BGR565_G0     = 0x1110,          ///< 5 bits blue, 5 bits green, 1 bit alpha, 5 bits red, interleaved.
    CM_ABGR8888      = 0x1120,          ///< 4 bytes per pixel, interleaved.
    CM_YUV422_UY1VY2 = 0x1180,          ///< 2 byte per pixel. U, Y, V, Y, interleaved.
    CM_YUV422        = CM_YUV422_UY1VY2,// Deprecated. Replaced by CM_YUV422_UY1VY2.
    CM_RGB666        = 0x1111,          ///< 18 bitar per pixel, interleaved.
    CM_RGB3553       = 0x1112,          ///< RGB3553 (Big Endian RGB565).
    CM_A8R8G8B8      = 0x1114,          ///< Planar ARGB8888, 4 bytes per pixel. AAA..., RRR..., GGG..., BBB...

    CM_YUV422P       = 0x1118,          ///< Planar YUV422, 2 bytes per pixel. YYY..., UUU..., VVV...
    CM_YUV422_VY2UY1 = 0x1119,          ///< 2 byte per pixel. V, Y, U, Y, interleaved.
    CM_YUV422R       = CM_YUV422_VY2UY1,// Deprecated. Replaced by CM_YUV422_VY2UY1.
    CM_YUV420SP      = 0x111a,          ///< Semi-planar YUV422, 2 bytes per pixel. YYY..., UVUVUV...
    CM_YUV420SP32    = 0x111b,          ///< Semi-planar YUV422, 2 bytes per pixel. YYY..., UVUV... Padded to even 32-bit words for each row.
    CM_YVU420SP      = 0x111c,          ///< Semi-planar YVU420, 2 bytes per pixel. YYY..., VUVUVU...
    CM_YUV422SP      = 0x111d,          ///< Semi-planar YUV422, 2 bytes per pixel. YYY..., UVUVUV...
    CM_YVU422SP      = 0x111e,          ///< Semi-planar YVU422, 2 bytes per pixel. YYY..., VUVUVU...
    CM_YUV420P       = 0x111f,          ///< Planar YUV420, 2 bytes per pixel. YYY..., UUU..., VVV...
    CM_YUV444P       = 0x1121,          ///< Planar YUV444, 3 bytes per pixel. YYY..., UUU..., VVV...
    CM_YUV422RP      = 0x1122,          ///< Planar YUV422-Rotated, 2 bytes per pixel. YYY..., UUU..., VVV...
    CM_YUV888        = 0x2001,          
    CM_RGB666_G4B4R6G2Z6B2Z8 = 0x2002,
    CM_BGRX8888      = 0x2004,          ///< 32 bit pixels, last byte unused.
    CM_ARGB6666      = 0x2008,          ///< 24 bit, interleaved.
    CM_GBRGAR264462  = 0x2009,          ///< 24 bit, Big Endian CM_ARGB6666, interleaved.
    CM_BGRA6666      = 0x2010,          ///< 24 bit, interleaved.
    CM_GRBG3553      = 0x2020,          ///< (Big Endian RGB565) Same as RGB565.
    CM_GBRG3553      = 0x2040,          ///< (Big Endian BGR565) Same as BGR565.
    CM_RGB565Q       = CM_RGB565,       // Deprecated. Replaced by CM_RGB565. CM_RGB565 has improved quality.
    CM_YUV422_Y1UY2V = 0x2060,          ///< 2 byte per pixel. Y, U, Y, V, interleaved.
    CM_YUV422_Y1Y2UV = 0x2080,          ///< 2 byte per pixel. Y, Y, U, V, interleaved.
    CM_YUVP          = 0x2100,          ///< Unsupported
    CM_Y,                               ///< Represent a single Y channel
    CM_U,                               ///< Represent a single U channel
    CM_V,                               ///< Represent a single V channel
    CM_UV,                              ///< Represent a single UV channel, UVUVUV...
    CM_VU,                              ///< Represent a single VU channel, VUVUVU...

    CM_ALL           = 0xFFFF,

    CM_RANGE_MIN = CM_UNDEFINED - 1,
    CM_RANGE_MAX = CM_ALL + 1

} CTColormode;
//-----------------------------------------------------------------------------
/**
    @brief Defines colorspacing modes for YUV component data.
*/
typedef enum
{
    CS_UNDEFINED = 0x000000, ///< Unknown or undefined colorspacing.
    CS_YUV420    = 0x221111, ///< YUV420
    CS_YUV422    = 0x211111, ///< YUV422
    CS_YUV422ROT = 0x121111, ///< YUV422 Rotated
    CS_YUV444    = 0x111111, ///< YUV444
    CS_YUV400    = 0x110000  ///< YUV400 (Grayscale)
    
} CTColorspacing;
//-----------------------------------------------------------------------------
/**
    @cond scb_internal_doc
    @brief Cache modes.
*/
typedef enum
{
    SCB_CACHE_MODE_NONE         = 0, ///< No caching
    SCB_CACHE_MODE_SCREEN       = 1, ///< Optimized for low screen resolution output.
    SCB_CACHE_MODE_FULL_SIZE    = 2, ///< Optimized for high screen resolution output.
    SCB_CACHE_MODE_CACHE_ROW    = 3  ///< Optimized for almost sequential accessing. Avaiable during HW decoding
} CTCacheMode;
/** @endcond */
//-----------------------------------------------------------------------------
/**
    @brief Sampling mode options.
*/
typedef enum
{
    SCB_SAMPLING_POINT      = 0x1,   ///< Point sampling.
    SCB_SAMPLING_BOX,                ///< Box sampling.
    SCB_SAMPLING_BILINEAR           ///< Bi-linear sampling.
} SCB_SAMPLING_MODE;
//-----------------------------------------------------------------------------
/**
    @brief Render blocksize values.
*/
typedef enum
{
    OPT_RENDER_BLOCKSIZE_8          = 0x0003, ///<    8 pixels.
    OPT_RENDER_BLOCKSIZE_16         = 0x0004, ///<   16 pixels.
    OPT_RENDER_BLOCKSIZE_32         = 0x0005, ///<   32 pixels.
    OPT_RENDER_BLOCKSIZE_64         = 0x0006, ///<   64 pixels.
    OPT_RENDER_BLOCKSIZE_128        = 0x0007, ///<  128 pixels.
    OPT_RENDER_BLOCKSIZE_256        = 0x0008, ///<  256 pixels.
    OPT_RENDER_BLOCKSIZE_512        = 0x0009, ///<  512 pixels.
    OPT_RENDER_BLOCKSIZE_1024       = 0x000A, ///< 1024 pixels.
    OPT_RENDER_JPEG_TILES           = 0x007F 

} CTRenderBlocksize;
//-----------------------------------------------------------------------------
/**
    @brief
    This enumeration specifies the subIFD when editing Exif tags.

    @since 3.2
*/
typedef enum
{
    IFD_ROOT = 0,               ///<  IFD Root
    IFD_EXIF = 1,               ///<  Exif IFD
    IFD_GPS = 3,                ///<  GPS IFD
    IFD_INTEROPERABILITY = 2    ///<  Interoperability IFD

} EXIF_SUB_IFD;
//-----------------------------------------------------------------------------
/**
    @brief Defines a rectangle.
*/
typedef struct CTRect
{
    CTint32     x;  ///< Horizontal offset.
    CTint32     y;  ///< Vertical offset.
    CTint32     w;  ///< Rectangle width.
    CTint32     h;  ///< Rectangle height.

} CTRect;
//-----------------------------------------------------------------------------
/**
    @brief Defines a rectangle with floating point precision.

*/
typedef struct 
{
    CTfloat x;
    CTfloat y;
    CTfloat w;
    CTfloat h;

} CTRectf;
//-----------------------------------------------------------------------------
/**
    @brief Defines a point/coordinate.
*/
typedef struct CTPoint
{
    CTint32         x;  ///< Horizontal position.
    CTint32         y;  ///< Vertical position.

} CTPoint;
//-----------------------------------------------------------------------------
/**
    @cond scb_internal_doc
*/
typedef struct CTVector
{
    CTint32         x;
    CTint32         y;

} CTVector;
/** @endcond */
//-----------------------------------------------------------------------------
/**
    @brief Defines a two-dimensional size.
*/
typedef struct CTSize
{
    CTint32     w; ///< Width
    CTint32     h; ///< Height

} CTSize;
//-----------------------------------------------------------------------------
/**
    @brief
    Defines the color of a single pixel by the channels @a alpha, @a red, @a green
    and @a blue. Each channel is in the range 0-255.
*/
typedef struct CTColor
{
    CTuint8         a;  ///< Alpha channel
    CTuint8         r;  ///< Red channel
    CTuint8         g;  ///< Green channel
    CTuint8         b;  ///< Blue channel

} CTColor;
//-----------------------------------------------------------------------------
/**
    @brief Defines a buffer with accompaning size.
*/
typedef struct CTBuffer
{
    CTuint32        size; ///< The size in bytes of the buffer.
    CTuint8*        data; ///< Address of the buffer data.

} CTBuffer;
//-----------------------------------------------------------------------------
/**
    @cond scb_internal_doc
*/
typedef struct CTBuffer32
{
    CTuint32        size;
    CTint32*        data;

} CTBuffer32;
/** @endcond */
//-----------------------------------------------------------------------------
/**
    @cond scb_internal_doc
*/
typedef struct CTBufferFloat
{
    CTuint32        size;
    CTfloat*        data;

} CTBufferFloat;
/** @endcond */
//-----------------------------------------------------------------------------
/** 
    @brief 
    Defines an uncompressed raw image through a pixel buffer and associated 
    information.

*/
typedef struct CTImage
{
    CTBuffer*   pixels;     ///< A buffer representing the pixel data of the image.
    CTSize      dims;       ///< The dimensions (width and height) in pixels of the image.
    
    /**
        The width in bytes of one scanline within the image. Cannot be zero.
     
        For a planar pixel format, the scanline specifies the number of bytes needed
        for the pixel buffer for a single row of pixels. That is, the total needed
        size for the image is scanline * height bytes.
     
        For an interleaved image the above holds true, but in this special case, the
        scanline also means the number of bytes for each row of pixels.
    */
    CTuint32    scanline;
    CTColormode format;     ///< The color format of the image's pixel data.
    
    CTuint32*   pARGBTable; ///< Look-up table for table based color modes.
    CTuint32*   pAYUVTable; ///< Look-up table for table based color modes.
} CTImage;

/** 
@brief 
Image format
*/
typedef enum CTImageFormat
{
    IMAGE_FORMAT_RANGE_MIN = 0, ///< Lower range limit for internal formats

    IMAGE_FORMAT_JPEG,          ///< JPEG image format
    IMAGE_FORMAT_JPS,           ///< JPS image format
    IMAGE_FORMAT_PNG,           ///< PNG image format
    IMAGE_FORMAT_GIF,           ///< GIF image format
    IMAGE_FORMAT_BMP,           ///< BMP image format
    IMAGE_FORMAT_WBMP,          ///< WBMP image format
    IMAGE_FORMAT_TIFF,          ///< TIFF image format
    IMAGE_FORMAT_RAW,           ///< RAW image format, used internally
    IMAGE_FORMAT_VIRTUAL,       ///< VIRTUAL image format, used internally
    IMAGE_FORMAT_CTDECODER,     ///< session created from a CTDecoder, used internally
    IMAGE_FORMAT_UNDEFINED,     ///< undefined image format, used internally
    IMAGE_FORMAT_RANGE_MAX      ///< Upper range limit for internal formats
} CTImageFormat;

/**
@brief
Directions on how to render an image
*/
typedef CTuint32 SCB_RENDER_OPT;
#define SCB_RENDER_OPT_STRETCH               (1 << 0) ///< Stretch the output. (Default is to keep aspect ratio)
#define SCB_RENDER_OPT_DITHER                (1 << 1) ///< If available, use a dithering algorithm for color conversion
#define SCB_RENDER_OPT_FAST_DITHER           (1 << 2) ///< If available, use a fast dithering algorithm for color conversion. If SCB_RENDER_OPT_DITHER is also requested, fast dithering will be applied if it available.

/**
    @brief Defines a point/coordinate using CTfloat.
*/
typedef struct
{
    CTfloat x;  ///< Horizontal position.
    CTfloat y;  ///< Vertical position.
} CTPointf;

//-----------------------------------------------------------------------------
/**
    @cond scb_internal_doc
*/
/**
    @brief
    Vertex point to use with OpenGL
*/
typedef struct
{
	CTint16 x;
	CTint16 y;
} Vertex;
/** @endcond */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
    @ingroup types_n_defs
    @brief Defines an iterator type.

    Defines an iterator object which is used to handle operations distributed
    as a sequence of iterations rather than a complete, blocking process.

    @since 3.0

    @deprecated The use of iterators is deprecated since 5.3.
*/
typedef struct CTIterator CTIterator;

//-----------------------------------------------------------------------------

// --- Unicode configuration. -----
#if defined(UNICODE) || defined(_UNICODE) || defined(SCB_UNICODE)

    typedef CTwchar DCHAR;

    #define _D(x) (const DCHAR*) L ## x 
    #define _SD(x) L ## x

    #define WIDEN2(x) _D(x)
    #define WIDEN(x) WIDEN2(x)
    #define __SCB_THISFILE__ WIDEN(__FILE__)

#else // non unicode

    typedef char DCHAR;
    #define _D(x) x
    #define _SD(x) x

    #define __SCB_THISFILE__ __FILE__

#endif

// --- Compilation helpers -----
#if defined(_MSC_VER)
    #define SCB_UNUSED(arg) ((void)(arg))
#elif defined (__MWERKS__)
    #pragma warn_unusedarg off
    #define SCB_UNUSED(arg)
#else
    #define SCB_UNUSED(arg) if( ((void*)&arg) > (void*)&arg ){   }
#endif

#if defined WIN_DLL 
    #define SCBIMPORT _declspec(dllexport)
    #define SCBEXPORT _declspec(dllexport)
#elif defined SYMB_DLL 
    #include <e32def.h> 
    #define SCBIMPORT IMPORT_C 
    #define SCBEXPORT EXPORT_C
#elif defined LINUX_DLL
    #if __GNUC__ >= 4 //Don't forget to pass -fvisibility=hidden to GCC
        #define SCBIMPORT __attribute__ ((visibility("default"))) 
        #define SCBEXPORT __attribute__ ((visibility("default")))
    #else
        #error "Not supported"
    #endif
#else 
    #define SCBIMPORT 
    #define SCBEXPORT 
#endif


//-----------------------------------------------------------------------------

/** @cond scb_internal_doc */

/**
    @if scb_internal_doc
    @page failsec_usage Fail-section macros

    Fail-section macros are provided to aid in writing code which may fail
    in several locations and which requires a cleanup step upon failure.

    The failsection macros work only with CRESULT values!

    Failsection macros usage:

    @code
        //Example, three allocations, one point of return.
        CRESULT result = CERR_OK;
        CTuint32* my_first_buffer  = 0;
        CTuint32* my_second_buffer = 0;
        CTuint32* my_third_buffer  = 0;

        SCB_TRY
        {
            my_first_buffer  = (CTuint32*)oslmem_alloc( sizeof(CTuint32) * 1024 );
            SCB_THROW_IF( my_first_buffer == 0, CERR_MEMALLOC_FAILED );

            my_second_buffer = (CTuint32*)oslmem_alloc( sizeof(CTuint32) * 2048 );
            SCB_THROW_IF( my_second_buffer == 0, CERR_MEMALLOC_FAILED );

            my_third_buffer  = (CTuint32*)oslmem_alloc( sizeof(CTuint32) * 3072 );
            SCB_THROW_IF( my_third_buffer == 0, CERR_MEMALLOC_FAILED );
        }
        SCB_CATCH( result )
        {
            // one of the allocations failed, free all buffers
            oslmem_free( my_first_buffer );
            oslmem_free( my_second_buffer );
            oslmem_free( my_third_buffer );
        }
        SCB_ENDTRY;
    @endcode

    @endif
*/
//-----------------------------------------------------------------------------

/** @brief Starts a fail section main block. */
#define SCB_TRY {CRESULT __res__=CERR_OK;

/** @brief Marks the end of the fail section main block and starts the exit block. */
#define SCB_CATCH( res ) \
    goto __scb_end_try_label_;\
    __scb_try_label_: res = __res__; if ( CFAILED( __res__ ) ) {

/** @brief Ends a fail section block. */
#define SCB_ENDTRY }}__scb_end_try_label_:

/** @brief Exits a fail section block with the given result. */
#define SCB_THROW( res ) __res__ = res; goto __scb_try_label_

/** @brief Exits a fail section block with the given result if the given condition is met. */
#define SCB_THROW_IF( cond, res ) if ( cond ) { SCB_THROW ( res ); }

/** @brief Exits a fail section block with the given result if the given result is an error code. */
#define SCB_THROW_IF_ERR( res ) \
{ \
    CRESULT _tempRes = (res); \
    SCB_THROW_IF( CFAILED( _tempRes ), _tempRes ); \
}

/** 
    @brief Skips out of the fail section with no further actions. 
    
    @remarks Note that this macro skips past the error handler as well. Use with care!
*/
#define SCB_LEAVE() goto __scb_end_try_label_
/** 
    @brief Skips out of the fail section with no further actions if the given condition is met.

    @remarks Note that this macro skips past the error handler as well. Use with care!
*/
#define SCB_LEAVE_IF( cond ) if ( cond ) SCB_LEAVE();

/** @endcond */


//-----------------------------------------------------------------------------
/** @cond scb_internal_doc */

#define SCB_BREAK_IF( cond ) { if( cond ) break; }
#define SCB_RETURN_IF( cond, value ) { if( ( cond ) ) return ( value ); }
#define SCB_BREAK_IF_ERR( cres ) { if ( CFAILED(cres) ) break; }
#define SCB_RETURN_IF_ERR( cres ) { CRESULT __tempRes = (cres); if ( CFAILED(__tempRes) ) return (__tempRes); }

/** @endcond */
    
//-----------------------------------------------------------------------------
/** @cond scb_internal_doc */

/** 
    @brief Starts a fail section main block. 
    @deprecated This macro is now deprecated in favor of SCB_TRY.
*/
#define SCB_BEGIN_FAILSECTION \
{ \
    int exit_request = 0; \
    CRESULT __res__ = CERR_OK; \
    while(__res__ == CERR_OK) \
{

/** 
    @brief Marks the end of the fail section main block and starts the exit block. 
    @deprecated This macro is now deprecated in favor of SCB_CATCH
*/
#define SCB_FAILSECTION_EXIT(errCode) break;}fail_section_end_label_0x1f321c31 : if(exit_request){CRESULT errCode = __res__;

/** 
    @brief Ends a fail section block. 
    @deprecated This macro is deprecated in favor of SCB_ENDTRY
*/
#define SCB_END_FAILSECTION \
    } \
    }

/** 
    @brief Exits a fail section block with the given result. 
    @deprecated This macro is deprecated in favor of SCB_THROW
*/
#define DO_EXIT_FAILSECTION( result ) \
    __res__ = result; \
    exit_request=1; \
    goto fail_section_end_label_0x1f321c31;

/** 
    @brief Exits a fail section block with the given result if the given condition is met. 
    @deprecated This macro is deprecated in favor of SCB_THROW_IF and SCB_THROW_IF_ERR
*/
#define DO_EXIT_FAILSECTION_IF( condition, result ) if(condition){DO_EXIT_FAILSECTION(result);}


/** @endcond */

//-----------------------------------------------------------------------------
/**
    @cond scb_internal_doc
*/
typedef enum
{
    SCB_STATUS_OK,
    SCB_STATUS_ERROR,
    SCB_STATUS_FINISHED,
    SCB_STATUS_CONTINUE,
    SCB_STATUS_NOT_ENOUGH_DATA
} CTStatus;
/** @endcond */
//-----------------------------------------------------------------------------
/**
    @}
*/
// end of defgroup 'types_n_defs'.
//=============================================================================


//-----------------------------------------------------------------------------
/**
    Include the list of error codes.

*/
#include "scberror.h"



#ifdef __ARMCC_VERSION
    #if (__ARMCC_VERSION > 300000)
        #define SCB_RESTRICT __restrict
    #else
        #define SCB_RESTRICT 
    #endif
#else
    #define SCB_RESTRICT 
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // !defined( SCBDEFS_H )
