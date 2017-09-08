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

#ifndef CTBITMAP_H
#define CTBITMAP_H

#include "scbdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @ingroup ctbitmap
    @file ctbitmap.h
    @brief Defines a raw bitmap buffer CTBitmap
*/
//=============================================================================
/**
    @addtogroup ctbitmap
    @brief Raw bitmap buffer

    @{
*/


/**
    @brief
    Type representing a raw bitmap buffer

    @since 5.3
*/
typedef struct CTBitmap CTBitmap;

/**
    Structure defining a bitmap plane. Note that measurements are in the 
    plane context. 
 
    This means that if the plane has a pixel format of CM_U, the dims property 
    means the number of U pixels inside the plane. In a similar way, if the 
    plane has color mode CM_UV, each pixel is a U _and_ V component wide 
    (16 bytes), and the dims property specify how many of these UV pixels
    are present in the plane.
 
    This is very relevant for sub sampled planar color formats, where plane
    dimensions, scanlines and bpp will be different than the same measurements
    on the bitmap.
*/
typedef struct
{
    CTuint8 *pData;         ///< Pointer to the first pixel in the pixel plane
    CTSize dims;            ///< Dimensions of this pixel plane
    CTuint32 scanline;      ///< Scanline in bytes
    CTColormode colorMode;  ///< Pixel format for each pixel in the plane

} CTPlane;

/**
    @brief Creates a new ctbitmap with the given dimensions and format.
 
    @param dims Desired dimensions of the bitmap
    @param format Desired color mode of the bitmap
    @param[out] ppBitmap Variable where the bitmap is stored
 
    @return CRESULT indicating result of the operation.

    @since 5.3
*/
SCBIMPORT CRESULT ctbitmap_create(CTSize dims, CTColormode format, CTBitmap **ppBitmap);

/**
    Destroy a ctbitmap
    @param pBitmap A bitmap

    @since 5.3
 */
SCBIMPORT void ctbitmap_destroy(CTBitmap *pBitmap);

/**
    Creates a ctbitmap from an existing ctimage. Memory is shared between the
    two structures.
    
    @param pImage       Existing image. This image must be kept alive at least as long
                        as the created bitmap.
    @param[out] ppBitmap    Output from the function
 
    @return CRESULT indicating success. Only when CERR_OK is true will ppBitmap be
    written to.

    @deprecated This functionality is deprecated. Use ctbitmap_createFromData()
    or ctbitmap_createFromDataPlanar() instead.

    @since 5.3
*/
SCBIMPORT CRESULT ctbitmap_createFromImage(CTImage *pImage, CTBitmap **ppBitmap);

/**
    Creates an image from the pointer given by pData.
    For planar color formats ctbitmap_createFromDataPlanar() should be used 
    instead.
 
    @param pData        Pointer to a byte buffer of pixel data.
    @param dims         Dimensions of the bitmap representation
    @param scanline Scanline of the bitmap representation. If set to zero, a
    suitable scanline will be assigned.    
    @param format       Color mode of the pixels described by pData
    @param[out] ppBitmap    Output bitmap from the function.

    @return CRESULT indicating result of the operation.

    @since 5.3
*/
SCBIMPORT CRESULT ctbitmap_createFromData(CTuint8 *pData,
                                CTSize dims, 
                                CTuint32 scanline, 
                                CTColormode format, 
                                CTBitmap **ppBitmap);

/**
    Creates a CTBitmap from the pointers given by ppData.

    @param ppData
    Pointer to an array of data pointers. ppData[n] points to the nth plane's pixel data.
    @param pScanline Pointer to an array of scanlines.
    @param dims         Dimensions of the bitmap representation
    @param format       Color mode of the pixels described by pData
    @param[out] ppBitmap    Output bitmap from the function.

    @return CRESULT indicating result of the operation.

    @since 5.3
 */
SCBIMPORT CRESULT ctbitmap_createFromDataPlanar(CTuint8 **ppData,
                                      const CTuint32 *pScanline,
                                      CTSize dims,
                                      CTColormode format,
                                      CTBitmap **ppBitmap);

/**
    @brief Returns the width and height of a bitmap.
 
    @param pBitmap Pointer to a valid bitmap object.
 
    @return Dimensions of the bitmap or (0,0) if an error occured (typically bad
    input parameter, such as a null pointer).

    @since 5.3
*/
SCBIMPORT CTSize ctbitmap_getDims(CTBitmap *pBitmap);

/**
    Retrieves the ctbitmap color format.
    
    @param pBitmap Pointer to a valid bitmap object.
 
    @return CM_UNDEFINED if pBitmap is invalid.

    @since 5.3
*/
SCBIMPORT CTColormode ctbitmap_getColorMode(CTBitmap *pBitmap);

/**
    Returns the number of planes for the specified image.
    
    @param pBitmap Pointer to a valid bitmap object.
 
    @return 0 if pBitmap is invalid, or if the call fails.

    @since 5.3
*/
SCBIMPORT CTuint32 ctbitmap_getPlaneCount(CTBitmap *pBitmap);

/**
    Retrieves an image plane from the ctbitmap.

    @param pBitmap Pointer to a valid bitmap object.
    @param bitmapPlane Index of the bitmap plane to retrieve.
 
    @return zero in all fields if the call fails. Typically, because pBitmap is invalid or
    because imagePlane is larger than the number of available planes.

    @since 5.3
*/
SCBIMPORT CTPlane ctbitmap_getPlane(CTBitmap *pBitmap, CTuint32 bitmapPlane);

/**
    @brief Returns a pointer to the plane pixel data
 
    @param pBitmap      Pointer to a valid bitmap
    @param imagePlane Index of a valid image plane
 
    @return Pointer to the beginning of the bitmap byte buffer for the specified
    plane.

    @since 5.3
*/
SCBIMPORT CTuint8 *ctbitmap_getPlaneOffset(CTBitmap *pBitmap, CTuint32 imagePlane);

/**
@}
*/
// end addtogroup ctbitmap


#ifdef __cplusplus
}      // extern "C"
#endif // __cplusplus
#endif // CTBITMAP_H

