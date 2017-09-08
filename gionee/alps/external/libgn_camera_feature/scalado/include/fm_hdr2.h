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
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */

#ifndef FM_HDR2_H
#define FM_HDR2_H

#ifdef __GNUC__
#   pragma GCC diagnostic ignored "-Wunused-function" // This disables warning for unused declarations
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "caps_base.h"
#include "caps_types.h"

//=============================================================================
/**
    @file fm_hdr2.h
    @brief Defines the interface of the Caps Feature Module: @a HDR2
    @ingroup fm_hdr2
*/
//=============================================================================
/**
    @addtogroup fm_hdr2
    @brief Creation of High Dynamic Range images.
    
    The CTHDR2 API provides functionality for creating HDR (High Dynamic Range)
    images, given two images taken with different exposure settings, but
    depicting the same scene.

    For optimal result the images should be taken in such a way that
    all areas of the scene look good in at least one of the images.
    E.g. when taking a picture that has both indoors and outdoors areas (windows or
    similar) take one shot where the indoors look good and one where the outdoors
    looks good.

    If exposure intelligence is unavailable it is recommended to use frame average
    exposure and use a slightly overexposed and a slightly underexposed image.
    A simple rule of thumb is that increased exposure step between input images
    gives a more apparent HDR effect.


    <h3>Usage</h3>
    -# Create a new HDR2 object with cthdr2_create()
    -# Add two images to the HDR2 object using cthdr2_addLDRSession()
    -# Render a preview to display on screen using cthdr2_generatePreview(),
       @n
       render the result to a stream with cthdr2_renderToStream()
       @n
       or render the result to an Image using cthdr2_renderToImage()
    -# Destroy the HDR2 object, cthdr2_destroy()
    .
    
    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief Type representing a HDR2 object.
*/
typedef struct CTHDR2 CTHDR2;

//----------------------------------------------------------------------------

#define CTHDR2OPTIONS_BLENDMODE_STANDARD 0
#define CTHDR2OPTIONS_BLENDMODE_NORMALDARK 1
#define CTHDR2OPTIONS_BLENDMODE_NORMALDARK_FAST 2
#define CTHDR2OPTIONS_ANTIGHOSTMODE_OFF 0
#define CTHDR2OPTIONS_ANTIGHOSTMODE_ON 1


typedef struct CTHDR2Options
{
    CTuint32 blendMode; ///< 0 standard mode, 1 normal+dark mode, 2 normal+dark simple mode
    CTuint32 antiGhostMode; ///< 0 no anti ghost, 1 anti ghost mode working for blend modes 1 and 2
    CTuint32 maximumBlend; ///< The amount of blend. Range [0 100], 0 keep normal image only, 100 blend fully. Valid for blend mode 1 and 2.
    CTuint32 blurSize; ///< Size of smoothness kernel side in pixels. 0 no smoothness applied. Must be a power of two. [0, 128]
    CTuint32 overexposureLimit; ///< [0,255]. Pixels over this value are considered overexposed.
} CTHDR2Options;

static CTHDR2Options CTMakeHDR2Options(CTuint32 blendMode,
                                       CTuint32 antiGhostMode,
                                       CTuint32 maximumBlend,
                                       CTuint32 blurSize,
                                       CTuint32 overexposureLimit)
{
    CTHDR2Options opt;

    opt.blendMode = blendMode;
    opt.antiGhostMode = antiGhostMode;
    opt.maximumBlend = maximumBlend;
    opt.blurSize = blurSize;
    opt.overexposureLimit = overexposureLimit;

    return opt;
}

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a CTHDR2 object.

    @param[out] ppHDR
    Pointer to the created CTHDR2 object if the function returns CERR_OK.

    @return CERR_OK on success.

    @see
    cthdr2_destroy()

    @since 5.1.1
*/
SCBIMPORT CRESULT cthdr2_create(CTHDR2 **ppHDR);

//----------------------------------------------------------------------------
/**
    @brief
    Sets options of a CTHDR2 object.

    @param pHDR
    A valid CTHDR2 object.

    @param options
    Options.

    @return CERR_OK on success.

    @since 5.3
*/
SCBIMPORT CRESULT cthdr2_setOptions(CTHDR2 *pHDR, CTHDR2Options options);

//-----------------------------------------------------------------------------

/**
    @brief
    Adds an image, provided via a CTSession, to the CTHDR2 object.

    Two images that the created HDR image will be based on must be added before calling
    cthdr2_renderToStream(), cthdr2_renderToImage() or cthdr2_generatePreview().

    Any added session must not be modified until after the CTHDR2 object
    has been destroyed.

    Note that if more than two images are added only the first two will be used.

    @param pHDR
    A valid CTHDR2 object.

    @param ldrSession
    A session providing the image to add.

    @return CERR_OK on success.

    @see
    - cthdr2_generatePreview()
    - cthdr2_renderToStream()
    - cthdr2_renderToImage()
    .

    @since 5.1.1
*/
SCBIMPORT CRESULT cthdr2_addLDRSession(CTHDR2 *pHDR, CTSession ldrSession);

//-----------------------------------------------------------------------------

/**
    @brief
    Adds an image, provided via a CTImage, to the CTHDR2 object. This is a less general way of adding images and only
    very few color formats are supported (CM_YUV420P, CM_YUV420SP, CM_YVU420SP). If other formats are used please refer
    to the more general cthdr2_addLDRSession().

    Two images that the created HDR image will be based on must be added before calling
    cthdr2_renderToStream(), cthdr2_renderToImage() or cthdr2_generatePreview().

    Any added images must not be modified or destroyed until after the CTHDR2 object
    has been destroyed.

    Note that if more than two images are added only the first two will be used.

    @param pHDR
    A valid CTHDR2 object.

    @param pLDRImage
    An image to add.

    @return CERR_OK on success.

    @see
    - cthdr2_generatePreview()

    - cthdr2_renderToStream()
    - cthdr2_renderToImage()
    .

    @since 5.2
*/
SCBIMPORT CRESULT cthdr2_addLDRImage(CTHDR2 *pHDR, CTImage *pLDRImage);

//-----------------------------------------------------------------------------
/**
     @brief
     Returns the dimensions of the output of the next call to cthdr2_renderToStream() or cthdr2_renderToImage().

     The two images that the created HDR image should be based on must be added before calling cthdr2_getRenderSize().

     @param pHDR
     A valid CTHDR2 object.

     @param[out] pSize
     A valid CTSize object. The dimensions of the next rendered image will be inserted in the provided CTSize object.

     @return CERR_OK on success.

     @since 5.1.1
 */
SCBIMPORT CRESULT cthdr2_getRenderSize(CTHDR2 *pHDR, CTSize *pSize);

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a HDR image from two images, and renders it to the provided image.

    Two LDR (Low Dynamic Range) images must have been added with
    cthdr2_addLDRSession() before a HDR image can be created.

    The size of the generated HDR image will correspond to the size of the intersection
    of all the added LDR images after registration. This size must be fetched with cthdr2_getRenderSize().

    The image will be rendered to the color format described by the CTImage. For highest performance YUV420P, YUV420SP
    or YVU420SP must be used.

    @param pHDR
    A valid CTHDR2 object.

    @param[in,out] pOutputImage
    An output image to which the HDR image will be rendered.

    @return CERR_OK on success.

    @see
    - cthdr2_addLDRSession()
    - cthdr2_getRenderSize()
    - cthdr2_generatePreview()
    .

    @since 5.1.1
*/
SCBIMPORT CRESULT cthdr2_renderToImage(CTHDR2 *pHDR, CTImage *pOutputImage);

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a HDR image from two images, and renders it to a provided stream.

    Two LDR (Low Dynamic Range) images must have been added with
    cthdr2_addLDRSession() before a HDR image can be created.

    The size of the generated HDR image will correspond to the size of the intersection
    of all the added LDR images after registration.

    @param pHDR
    A valid CTHDR2 object.

    @param[in,out] pOutputStream
    An output stream to which the HDR image will be written.
    The rendered image will be encoded as a Jpeg.

    @return CERR_OK on success.

    @see
    - cthdr2_addLDRSession()
    - cthdr2_generatePreview()
    .

    @since 5.1.1
*/
SCBIMPORT CRESULT cthdr2_renderToStream(CTHDR2 *pHDR, CTStream *pOutputStream);

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a HDR image from two images, and renders it to a provided
    @c CTImage buffer.

    Two LDR (Low Dynamic Range) images must have been added with
    cthdr2_addLDRSession() before a HDR image can be created.

    The HDR image will be scaled to fit the dimensions specified in the provided
    CTImage buffer; i.e. the resolution given by CTImage::dims.

    The output color format is determined by that specified in CTImage::format. For highest performance YUV420P,
    YUV420SP or YVU420SP must be used.
    
    @param pHDR
    A valid CTHDR2 object.

    @param[in,out] pPreviewImage
    An image buffer that the HDR image will be written to.

    @return CERR_OK on success.
    
    @see
    - cthdr2_addLDRSession()
    - cthdr2_renderToStream()
    .

    @since 5.1.1
*/
SCBIMPORT CRESULT cthdr2_generatePreview(CTHDR2 *pHDR, CTImage *pPreviewImage);

//-----------------------------------------------------------------------------
/**
    @brief
    Destroys a CTHDR2 object.

    @param pHDR
    The CTHDR2 object to destroy.

    @since 5.1.1
*/
SCBIMPORT void cthdr2_destroy(CTHDR2 *pHDR);

//-----------------------------------------------------------------------------
/** @} */
// end 'fm_hdr2'
//==============================================================================


#ifdef __cplusplus
}//extern "C" {
#endif

#endif // FM_HDR2_H

