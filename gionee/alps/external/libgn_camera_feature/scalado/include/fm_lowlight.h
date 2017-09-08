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

#ifndef FM_LOWLIGHT_H
#define FM_LOWLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "caps_base.h"
#include "caps_types.h"

//=============================================================================
/**
    @file fm_lowlight.h
    @brief Defines the interface of the Caps Feature Module: @a LowLight
    @ingroup fm_lowlight
*/
//=============================================================================
/**
    @addtogroup fm_lowlight
    @brief Creation of Low Light images.
    
    The CTLowLight API provides functionality for creating Low Light images,
    given four images.

    <h3>Usage</h3>
    -# Create a new LowLight object with ctlowlight_create()
    -# Add four images to the LowLight object using ctlowlight_addSourceSession() or 
       @n
       ctlowlight_addSourceDecoder()
    -# Render a preview to display on screen using ctlowlight_generatePreview(),
       @n
       render the result to a stream with ctlowlight_renderToStream()
       @n
       or render the result to an Image using ctlowlight_renderToImage()
    -# Destroy the LowLight object, ctlowlight_destroy()
    .
    
    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief Type representing a low light object.
*/
typedef struct CTLowLight CTLowLight;

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a CTLowLight object.

    @param[out] ppLowLight
    Pointer to the created CTLowLight object if the function returns CERR_OK.

    @return CERR_OK on success.

    @see
    ctlowlight_destroy()

    @since 5.2
*/
SCBIMPORT CRESULT ctlowlight_create(CTLowLight **ppLowLight);

//-----------------------------------------------------------------------------

/**
    @brief
    Adds an image, provided via a CTSession, to the CTLowLight object.

    The images that the created LowLight image will be based on must be added before calling
    ctlowlight_renderToStream(), ctlowlight_renderToImage() or ctlowlight_generatePreview().

    @param pLowLight
    A valid CTLowLight object.

    @param sourceSession
    A session providing the image to add.

    @return CERR_OK on success.

    @see
    - ctlowlight_generatePreview()
    - ctlowlight_render()
    .

    @since 5.2
*/
SCBIMPORT CRESULT ctlowlight_addSourceSession(CTLowLight *pLowLight, CTSession sourceSession);
/**
    @brief
    Adds an image, provided via a CTDecoder, to the CTLowLight object.

    The images that the created LowLight image will be based on must be added before calling
    ctlowlight_renderToStream(), ctlowlight_renderToImage() or ctlowlight_generatePreview().


    @param pLowLight
    A valid CTLowLight object.

    @param pDecoder
    A decoder providing the image to add.

    @return CERR_OK on success.

    @see
    - ctlowlight_generatePreview()
    - ctlowlight_render()
    .

    @since 5.2
*/
SCBIMPORT CRESULT ctlowlight_addSourceDecoder(CTLowLight *pLowLight, CTDecoder *pDecoder);

//-----------------------------------------------------------------------------
/**
     @brief
     Returns the dimensions of the output of the next call to ctlowlight_renderToStream() or ctlowlight_renderToImage().

     The images that the created low light image should be based on must be added before calling ctlowlight_getRenderSize().

     @param pLowLight
     A valid CTLowLight object.

     @param[out] pSize
     A valid CTSize object. The dimensions of the next rendered image will be inserted in the provided CTSize object.

     @since 5.2
 */
SCBIMPORT CRESULT ctlowlight_getRenderSize(CTLowLight *pLowLight, CTSize *pSize);

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a low light image from source images, and renders it to the provided image.

    Exact four source images must have been added with
    ctlowlight_addSourceSession() before a low light image can be created.

    The size of the generated low light image will correspond to the size of the intersection
    of all the added images after registration. This size can be fetched with ctlowlight_getRenderSize().

    @param pLowLight
    A valid CTLowLight object.

    @param[in,out] pOutputImage
    An output image to which the low light image will be rendered.
    The output image must have the color format CM_YUV420P and the size returned 
    by ctlowlight_getRenderSize(). If not CERR_INVALID_PARAMETER will be returned.

    @return CERR_OK on success 

    @see
    - ctlowlight_addSourceSession()
    - ctlowlight_getRenderSize()
    - ctlowlight_generatePreview()
    .

    @since 5.2
*/
SCBIMPORT CRESULT ctlowlight_renderToImage(CTLowLight *pLowLight, CTImage *pOutputImage);

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a low light image from four images, and renders it to a provided stream.

    Exact four source images must have been added with
    ctlowlight_addSourceSession() before a low light image can be created.

    The size of the generated low light image will correspond to the size of the intersection
    of all the added images after registration. This size can be fetched with ctlowlight_getRenderSize().

    @param pLowLight
    A valid CTLowLight object.

    @param[in,out] pOutputStream
    An output stream to which the low light image will be written.
    The rendered image will be encoded as a Jpeg.

    @return CERR_OK on success.

    @see
    - ctlowlight_addSourceSession()
    - ctlowlight_getRenderSize()
    - ctlowlight_generatePreview()
    .

    @since 5.2
*/
SCBIMPORT CRESULT ctlowlight_renderToStream(CTLowLight *pLowLight, CTStream *pOutputStream);

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a low light image from four images, and renders it to a provided
    @c CTImage buffer.

    Exact four source images must have been added with
    ctlowlight_addSourceSession() before a low light image can be created.

    The low light image will be scaled to fit the dimensions specified in the provided
    CTImage buffer; i.e. the resolution given by CTImage::dims.

    The output color format is determined by that specified in CTImage::format.
    
    @param pLowLight
    A valid CTLowLight object.

    @param[in,out] pPreviewImage
    An image buffer that the low light image will be written to.

    @return CERR_OK on success.
    
    @see
    - ctlowlight_addSourceSession()
    - ctlowlight_renderToStream()
    .

    @since 5.2
*/
SCBIMPORT CRESULT ctlowlight_generatePreview(CTLowLight *pLowLight, CTImage *pPreviewImage);

//-----------------------------------------------------------------------------
/**
    @brief
    Destroys a CTLowLight object.

    @param pLowLight
    The CTLowLight object to destroy.

    @since 5.2
*/
SCBIMPORT void ctlowlight_destroy(CTLowLight *pLowLight);

//-----------------------------------------------------------------------------
/** @} */
// end 'fm_lowlight'
//==============================================================================


#ifdef __cplusplus
}//extern "C" {
#endif

#endif // FM_LOWLIGHT_H

