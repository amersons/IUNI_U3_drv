/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    � 2000-2009 Scalado AB. All rights reserved.                             .
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

#ifndef FM_JPEGTOOLS_H
#define FM_JPEGTOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctstream.h"
#include "caps_iterator.h"


#ifndef OSLFILE_CTFILE
#define OSLFILE_CTFILE
typedef struct CTFile CTFile;
#endif

//=============================================================================
/**
    @ingroup fm_jpegtools
    @file fm_jpegtools.h
    @brief Defines the interface of the Caps Feature Module: @a JPEGTools
*/
//=============================================================================
/**
    @addtogroup fm_jpegtools
    @brief Jpeg functions operating in the compressed domain.
    @{
*/

//-----------------------------------------------------------------------------
/**
    @page rotate_flip_limitations Limitation for lossless rotate and flip functions

    The lossless rotate and flip functions have limitations depending on image
    dimensions and MCU (Minimum Coded Unit) size. The code below describes the
    constraints for the different directions. If the constraints isn't fullfilled,
    CERR_UNSUPPORTED_IMAGE will be returned. To rotate such images please use the
    (lossy) rotate function found in the Base API.

    @code
        case CAPS_90_DEGREE_WITH_FLIP:
            if ( ( width % mcuWidth ) || ( height % mcuHeight ) )
            {
                return CERR_UNSUPPORTED_IMAGE;
            }
            break;
        case CAPS_90_DEGREE_WITHOUT_FLIP:
            if ( height % mcuHeight )
            {
                return CERR_UNSUPPORTED_IMAGE;
            }
            break;
        case CAPS_180_DEGREE_WITH_FLIP:
            if ( height % mcuHeight )
            {
                return CERR_UNSUPPORTED_IMAGE;
            }
            break;
        case CAPS_180_DEGREE_WITHOUT_FLIP:
            if ( ( width % mcuWidth ) || ( height % mcuHeight ) )
            {
                return CERR_UNSUPPORTED_IMAGE;
            }
            break;
        case CAPS_270_DEGREE_WITH_FLIP:
            return CERR_OK;
        case CAPS_270_DEGREE_WITHOUT_FLIP:
            if ( width % mcuWidth )
            {
                return CERR_UNSUPPORTED_IMAGE;
            }
            break;
        case CAPS_0_DEGREE_WITH_FLIP:
            if ( width % mcuWidth )
            {
                return CERR_UNSUPPORTED_IMAGE;
            }
            break;
    @endcode
*/
//=============================================================================
//---------------- Lossless Rotate -------------------------------------------


/** 
    @defgroup fxgroup_rotate Lossless Rotate
    @{
*/

/** @brief Possible orientation settings */
typedef enum
{
    CAPS_90_DEGREE_WITHOUT_FLIP = 6,    ///< Rotate  90 (CCW), no flip
    CAPS_180_DEGREE_WITHOUT_FLIP = 3,   ///< Rotate 180, no flip
    CAPS_270_DEGREE_WITHOUT_FLIP = 8,   ///< Rotate -90 (CW), no flip
    
    CAPS_0_DEGREE_WITH_FLIP = 2,        ///< Flip horizontally
    CAPS_90_DEGREE_WITH_FLIP = 5,       ///< Flip horizontally, and rotate  90 (CCW)
    CAPS_180_DEGREE_WITH_FLIP = 4,      ///< Flip horizontally, and rotate 180
    CAPS_270_DEGREE_WITH_FLIP = 7       ///< Flip horizontally, and rotate -90 (CW)

} CAPS_ORIENTATION_MODE;

//-----------------------------------------------------------------------------
/**
    @brief Lossless rotate, rotates a jpeg into a new jpeg.

    @param[in] pSrcStream stream containing the input image.
    @param[in] pDstStream stream containing the output image.
    @param[in] mode Orientation mode. Can be any of the values 
               from the ::CAPS_ORIENTATION_MODE enumeration,
               or the result from calling caps_getFlipRotationMode.
    @param[out] ppIterator A pointer to an iterator object. If set to NULL,
                the operation will be performed directly.

    @remarks
    @copydoc rotate_flip_limitations
    \n
    @copydoc iterative_operations

    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.

    @since 3.8
*/
SCBIMPORT CRESULT caps_rotateJpeg ( CTStream *pSrcStream,
                                    CTStream *pDstStream,
                                    CAPS_ORIENTATION_MODE mode,
                                    CTIterator **ppIterator );

//-----------------------------------------------------------------------------
/**
    Lossless rotate, rotates a jpeg file into a new jpeg file.

    @param[in] pSrcJpegFilename Filename of the input image.
    @param[in] pDstJpegFilename Filename of the output image.
    @param[in] orientation Orientation mode. Can be any of the values 
                           from the @c ::CAPS_ORIENTATION_MODE enumeration..    

    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.

    @copydoc rotate_flip_limitations

    @since 3.1
*/
SCBIMPORT CRESULT caps_rotateJpegFileToFile ( const DCHAR* pSrcJpegFilename, 
                                    const DCHAR* pDstJpegFilename,
                                    CTuint8 orientation);

//-----------------------------------------------------------------------------
/**
    Lossless rotate, rotates a jpeg file into a new jpeg file.

    @param[in] pSrcJpegBuffer Pointer to the input image.
    @param[in] pDstJpegBuffer Pointer to the output image.
    @param[out] pActualDstSize Pointer to the actual size of the resulting jpeg.
    @param[in] orientation Orientation mode. Can be any of the values 
                           from the @c ::CAPS_ORIENTATION_MODE enumeration..    

    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.

    @copydoc rotate_flip_limitations

    @since 3.1
*/
SCBIMPORT CRESULT caps_rotateJpegMemToMem ( const CTBuffer* pSrcJpegBuffer, 
                                  CTBuffer* pDstJpegBuffer,
                                  CTuint32* pActualDstSize,
                                  CTuint8 orientation);

/**
    @}
*/ // end 'Lossless Rotate'
//=============================================================================

/**
    Lossless flip, flips a jpeg file into a new jpeg file.

    @param[in] pSrcJpegFilename Filename of the input image.
    @param[in] pDstJpegFilename Filename of the output image.
    @param[in] flipHorizontal Flips the image horizontally.    
    @param[in] flipVertical Flips the image vertically.    

    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.

    @copydoc rotate_flip_limitations

    @since 3.1
*/
SCBIMPORT CRESULT caps_flipJpegFileToFile ( const DCHAR* pSrcJpegFilename, 
                                  const DCHAR* pDstJpegFilename,
                                  CTbool flipHorizontal,
                                  CTbool flipVertical);

//-----------------------------------------------------------------------------
/**
    Lossless flip, flips a jpeg file into a new jpeg file.

    @param[in] pSrcJpegBuffer Pointer to the input image.
    @param[in] pDstJpegBuffer Pointer to the output image.
    @param[out] pActualDstSize Pointer to the actual size of the resulting jpeg.
    @param[in] flipHorizontal Flips the image horizontally.    
    @param[in] flipVertical Flips the image vertically.    

    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.

    @copydoc rotate_flip_limitations

    @since 3.1
*/
SCBIMPORT CRESULT caps_flipJpegMemToMem ( const CTBuffer* pSrcJpegBuffer, 
                                CTBuffer* pDstJpegBuffer,
                                CTuint32* pActualDstSize,
                                CTbool flipHorizontal,
                                CTbool flipVertical);

//=============================================================================
//-------------- Jpeg Blend ---------------------------------------------------
/**
    @defgroup fxgroup_blend Blend
    @{
*/

/**
    Jpeg Blend, blends a jpeg image with an other image into a new jpeg file.
	The source image dimensions cannot be smaller than 
	the dimensions of the image to blend. 

    @param[in] pSrcStream Stream of the input image.
    @param[in] pDstStream Stream of the output image.
    @param[in] pExifDataBuffer Pointer to Exif meta data.
    @param[in] pImage       Pointer to image to blend in. The image must be 
                            in either ARGB8888 or AYUV4444 format.
    @param[in] pImagePosition Pointer to the position where to 
                              blend in the image (upper left corner). 
    @param[out] ppIterator A pointer to an iterator object. If set to NULL,
                the operation will be performed directly. 

    @remarks
    @copydoc iterative_operations
    
    @return
    @c CERR_OK if no errors or an appropriate error code otherwise.
    @c CERR_UNSUPPORTED_COLOR_MODE if the color mode is unsupported.

    @since 3.8
*/
SCBIMPORT CRESULT caps_blendJpeg ( CTStream *pSrcStream, 
                         CTStream *pDstStream,
                         const CTBuffer *pExifDataBuffer,
                         const CTImage  *pImage,
                         const CTPoint  *pImagePosition,
                         CTIterator **ppIterator );

/**
    @}
*/ // end 'fxgroup_blend'
//-----------------------------------------------------------------------------
/**
    @}
*/ // end addtogroup 'fm_jpegtools'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_JPEGTOOLS_H )
