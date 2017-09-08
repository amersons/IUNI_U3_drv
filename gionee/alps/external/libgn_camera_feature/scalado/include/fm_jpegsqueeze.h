/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    © 2000-2009 Scalado AB. All rights reserved.                             .
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

#ifndef FM_JPEGSQUEEZE_H
#define FM_JPEGSQUEEZE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctstream.h"
#include "caps_iterator.h"

//=============================================================================
/**
    @ingroup fm_jpegsqueeze
    @file fm_jpegsqueeze.h
    @brief Defines the interface of the Caps Feature Module: @a JPEGSqueeze
*/
//=============================================================================
/**
    @addtogroup fm_jpegsqueeze
    @brief Fast compression of jpeg to specified size.
    @{
*/

//-----------------------------------------------------------------------------
/**
    @defgroup fm_jpegsqueeze_api JpegSqueeze API
    @{
*/

/**
    @brief
    Jpeg squeeze, squeezes a jpeg image into a new smaller jpeg  
    with a desired maximum size.

    @param[in] pSrcStream Stream containing the input image.
    @param[in] pDstStream Stream where the output image will be outputted.
    @param[in] proposedSize Desired maximum size of the new jpeg image in bytes.
               Must be greater than 0.
    @param[out] ppIterator A pointer to an iterator object. If set to NULL,
                the operation will be performed directly.

    @remarks
    @copydoc iterative_operations

    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.
       CERR_OPERATION_FAILED is returned if the function failed to
       create a small enough jpeg.

    @since 3.8
*/
SCBIMPORT CRESULT caps_squeezeJpeg ( CTStream *pSrcStream, 
                                     CTStream *pDstStream,
                                     CTuint32 proposedSize,
                                     CTIterator **ppIterator );

//-----------------------------------------------------------------------------
/**
    @brief
    Jpeg squeeze, squeezes a jpeg file into a new smaller jpeg file 
    with a desired maximum size.

    @param[in] pSrcJpegFilename Filename of the input image.
    @param[in] pDstJpegFilename Filename of the output image.
    @param[in] proposedSize Desired maximum size of the new jpeg file.
               Must be greater than 0.
    
    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.
       CERR_OPERATION_FAILED is returned if the function failed to
       create a small enough jpeg file. If this happens, the created
       file will not be deleted by this function.

    @since 3.1
*/
SCBIMPORT CRESULT caps_squeezeJpegFileToFile ( const DCHAR* pSrcJpegFilename, 
                                     const DCHAR* pDstJpegFilename,
                                     CTuint32 proposedSize);

//-----------------------------------------------------------------------------
/**
    Jpeg squeeze, squeezes a jpeg file into a new smaller jpeg file 
    with a desired maximum size.

    @param[in] pSrcJpegFilename Filename of the input image.
    @param[in] pDstJpegBuffer Pointer to the output image.
    @param[in] proposedSize Desired maximum size of the new jpeg file.    
               Must be greater than 0.
    @param[out] pActualDstSize Pointer to the actual size of the resulting jpeg.
    
    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.
       CERR_OPERATION_FAILED is returned if the function failed to
       create a small enough jpeg file.

    @since 3.1
*/
SCBIMPORT CRESULT caps_squeezeJpegFileToMem ( const DCHAR* pSrcJpegFilename, 
                                    CTBuffer* pDstJpegBuffer,
                                    CTuint32 proposedSize,
                                    CTuint32* pActualDstSize);

//-----------------------------------------------------------------------------
/**
    Jpeg squeeze, squeezes a jpeg file into a new smaller jpeg file 
    with a desired maximum size.

    @param[in] pSrcJpegBuffer Pointer to the input image.
    @param[in] pDstJpegBuffer Pointer to the output image.
    @param[in] proposedSize Desired maximum size of the new jpeg file.    
               Must be greater than 0.
    @param[out] pActualDstSize Pointer to the actual size of the resulting jpeg.
    
    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.
       CERR_OPERATION_FAILED is returned if the function failed to
       create a small enough jpeg file.

    @since 3.1
*/
SCBIMPORT CRESULT caps_squeezeJpegMemToMem ( const CTBuffer* pSrcJpegBuffer, 
                                   CTBuffer* pDstJpegBuffer,
                                   CTuint32 proposedSize,
                                   CTuint32* pActualDstSize);

//-----------------------------------------------------------------------------
/**
    Jpeg squeeze, squeezes a jpeg file into a new smaller jpeg file 
    with a desired maximum size.

    @param[in] pSrcJpegBuffer Pointer to the input image.
    @param[in] pDstJpegFilename Filename of the output image.
    @param[in] proposedSize Desired maximum size of the new jpeg file.    
               Must be greater than 0.
    
    @return 
    @c CERR_OK if no errors or an appropriate error code otherwise.
       CERR_OPERATION_FAILED is returned if the function failed to
       create a small enough jpeg file. If this happens, the created
       file will not be deleted by this function.

    @since 3.1
*/
SCBIMPORT CRESULT caps_squeezeJpegMemToFile ( const CTBuffer* pSrcJpegBuffer, 
                                    const DCHAR* pDstJpegFilename,
                                    CTuint32 proposedSize);

//-----------------------------------------------------------------------------

/**
    @brief The different behaviours of auto resize.
*/
typedef enum {

    /**
        Auto resize will try to preserve the source encoding quality while
        shrinking the width and height of the image.
    */
    AUTO_RESIZE_PRESERVE_SOURCE_ENCODING_QUALITY,
    
    /**
        Auto resize will try to preserve the maxImageSize while lowering
        the encoding quality.
    */
    AUTO_RESIZE_PRIORITIZE_LARGE_IMAGE_SIZE,
    
    /**
        Auto resize will try to preserve the highest possible encoding quality
        while shrinking the width and height of the image. This might be
        useful if you substantially reduce the size of the image.
    */
    AUTO_RESIZE_PRIORITIZE_HIGH_ENCODING_QUALITY,

    /**
        Auto resize will simultaneously lower the encoding quality and shrink
        the width and height of the image.
    */
    AUTO_RESIZE_MIDDLE_COURSE

} AUTO_RESIZE_ACTION;

//-----------------------------------------------------------------------------

/** 
    @brief A structure containing information specifying the behaviour
    of auto resize.
*/
typedef struct {

    /** The requested new file size. */
    CTuint32 maxFileSize;

    /**
        The rendered image will fit within this outer bounding box when
        allowing for rotation.
        
        The size must be larger than @c autoResizeInfo::minImageSize.

        A maxImageSize of {640, 480} will, for the following different source
        image sizes, give this maximum size:
        @n@n
        {1024, 1024} will be at most {480, 480}
        @n@n
        {1280, 640}  will be at most {640, 320}
        @n@n
        {640, 1280}  will be at most {320, 640}
    */
    CTSize maxImageSize;

    /**
        The rendered image will be at least as large as this box in at least
        one dimension when allowing for rotation. This means that minImageSize
        defines a box that after being rotated and cropped to the same aspect
        ratio as the image will be an inner bounding box for the rendered image.
        
        The size must be smaller than @c autoResizeInfo::maxImageSize.

        A minImageSize of {160, 120} will, for the following different source
        image sizes, give this minimum size:
        @n@n
        {1024, 1024} will be at least {120, 120}
        @n@n
        {1280, 640}  will be at least {160, 80}
        @n@n
        {640, 1280}  will be at least {80, 160}
    */
    CTSize minImageSize;

    /** The desired behaviour of auto resize. */
    AUTO_RESIZE_ACTION action;

    /** The lowest desired encoding quality.
        Must be in the range (0.0) - (1.0).
    */
    CTfloat minEncodingQuality;

    /** The color spacing of the new image. */
    CTColorspacing colorSpacing;

    /** Currently unused. */
    void* data;

} autoResizeInfo;

//-----------------------------------------------------------------------------
/**
    Auto resize, changes the image size and encoding quality to make
    the new image fit into the desired file size. Auto resize will
    maintain the aspect ratio of the image.

    If the achieved file size returned by this function is larger than
    the requested file size the user can use one of the squeeze functions
    in this feature module to further reduce the file size.

    @param[in]  pSrcJpegFilename Filename of the input image.
    @param[in]  pDstJpegFilename Filename of the output image.
    @param[in]  pInfo Information specifying the auto resize behaviour.    
    @param[out] achievedFileSize The size of the resized file.
    
    @return
    @c CERR_OK if no errors, or an appropriate error code otherwise.
    @c CERR_OPERATION_FAILED is returned if the function is sure it will
    fail in creating a small enough file given the information in pInfo.
    This will happen, for instance, when the minimum encoding quality
    is larger than the quality required to produce an image with
    the specified minimum image size and maximum file size.

    @remarks
    maxImageSize must be larger than minImageSize.

    @since 3.4
*/
SCBIMPORT CRESULT caps_autoResizeImageFileToFile ( const DCHAR* pSrcJpegFilename,
                                         const DCHAR* pDstJpegFilename,
                                         const autoResizeInfo* pInfo,
                                         CTuint32* achievedFileSize);


//-----------------------------------------------------------------------------
/**
    Auto resize, changes the image size and encoding quality to make
    the new image fit into the desired file size. Auto resize will
    maintain the aspect ratio of the image.

    If the achieved file size returned by this function is larger than
    the requested file size the user can use one of the squeeze functions
    in this feature module to further reduce the file size.

    @param[in]  pSrcJpeg Buffer containing the input jpeg image.
    @param[in]  pDstJpeg Buffer containing the output resized jpeg image.     
    @param[in]  pInfo Information specifying the auto resize behaviour.    
    @param[out] achievedFileSize The size of the resized file.
    
    @return
    @c CERR_OK if no errors, or an appropriate error code otherwise.
    @c CERR_OPERATION_FAILED is returned if the function is sure it will
    fail in creating a small enough file given the information in pInfo.
    This will happen, for instance, when the minimum encoding quality
    is larger than the quality required to produce an image with
    the specified minimum image size and maximum file size.

    @remarks
    maxImageSize must be larger than minImageSize.
    
    See caps_renderToBuffer() for information about how the 
    destination @c CTBuffer is treated.

    @since 3.7
*/
SCBIMPORT CRESULT caps_autoResizeImageMemToMem ( const CTBuffer* pSrcJpeg,
                                       CTBuffer* pDstJpeg,
                                       const autoResizeInfo* pInfo,
                                       CTuint32* achievedFileSize);

/**
    @}
*/// end 'fm_jpegsqueeze_api'
//-----------------------------------------------------------------------------
/**
    @}
*/// end addtogroup 'fm_jpegsqueeze'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_JPEGSQUEEZE_H )
