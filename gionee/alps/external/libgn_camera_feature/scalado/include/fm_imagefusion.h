/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2009 Scalado AB. All rights reserved.                           .
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

#ifndef FM_IMAGEFUSION_H
#define FM_IMAGEFUSION_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/**
    @ingroup fm_imagefusion
    @file fm_imagefusion.h
    @brief Defines the interface of the Caps Feature Module: @a ImageFusion
*/
//=============================================================================
/**
    @addtogroup fm_imagefusion
    @brief Blending image pairs using defined masks.

    @{
*/

//-----------------------------------------------------------------------------
/**
    @defgroup fm_imagefusion_api ImageFusion API
    @{
*/

/**
    @brief
    Inserts a frame on the current session with a separately defined alpha
    mask.

    @param session
    Handle to a valid session.

    @param pImageStream
    A pointer to a stream containing an image.

    @param imageFormat
    The image format of the image.

    @param imageOwnership
    An option from the ::OWNERSHIP_POLICY enumeration which specifies what
    ownership policy to use with the @a pImageStream argument. If CAPS is given
    ownership responsibility over @a pImageStream, it will be destroyed using
    ctstream_destroy() when no longer needed.

    @param pMaskStream
    A pointer to a stream containing a mask.

    @param maskFormat
    The image format of the mask.

    @param maskOwnership
    An option from the ::OWNERSHIP_POLICY enumeration which specifies what
    ownership policy to use with the @a pMaskStream argument. If CAPS is given
    ownership responsibility over @a pMaskStream, it will be destroyed using
    ctstream_destroy() when no longer needed.

    @param invertAlpha
    If this is false, 0 - 255 is fading from session to frame
    If this is true,  0 - 255 is fading from frame to session

    @remarks

    A frame is an overlay image stretched or contracted to fit the size of the
    session image. The blending of the frame and the session image is
    defined by an alpha mask. The image and the alpha mask are stretched
    separately, and may have different dimensions.

    The following image types are supported for the image:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

    \n
    The following image types are supported for the mask:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

    \n
    The mask is typically a gray scale image.


    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertFrameFromBufferMask()\n
    caps_insertFrameFromFileMask()\n

    @since 3.8

    @deprecated This function is deprecated since 5.3.
    Use caps_insertImageFromRawMask() instead.
*/
SCBIMPORT CRESULT caps_insertFrameMask( CTSession session,
                              CTStream* pImageStream,
                              IMAGE_FORMAT_SPEC imageFormat,
                              OWNERSHIP_POLICY imageOwnership, 
                              CTStream* pMaskStream,
                              IMAGE_FORMAT_SPEC maskFormat,
                              OWNERSHIP_POLICY maskOwnership,
                              CTbool invertAlpha );

//-----------------------------------------------------------------------------
/**
    @brief
    Inserts a frame on the current session with a separately defined alpha
    mask.

    @param session
    Handle to a valid session.

    @param imagename
    String specifying the file system path of the image.

    @param maskname
    String specifying the file system path of the alpha mask. The luminance
    channel of the mask image is used as the frame's alpha channel.

    @param invertAlpha
    If this is false, 0 - 255 is fading from session to frame
    If this is true,  0 - 255 is fading from frame to session

    @remarks

    A frame is an overlay image stretched or contracted to fit the size of the
    session image. The blending of the frame and the session image is
    defined by an alpha mask. The image and the alpha mask are stretched
    separately, and may have different dimensions.

    The following image types are supported for the image:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

    \n
    The following image types are supported for the mask:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

    \n
    The mask is typically a gray scale image.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertFrameMask()\n
    caps_insertFrameFromBufferMask()\n
    caps_insertFrameFromFile()\n

    @since 3.6 (support for more image types in 3.8)

    @deprecated This function is deprecated since 5.3.
    Use caps_insertImageFromRawMask() instead.
*/
SCBIMPORT CRESULT caps_insertFrameFromFileMask( CTSession session, const DCHAR* imagename,
                                     const DCHAR* maskname, CTbool invertAlpha);

//-----------------------------------------------------------------------------
/**
    @brief
	Inserts a frame on the current session with a separately defined alpha
	mask.

	@param session
	Handle to a valid session.

	@param pImage
	Buffer containing the image.

	@param imageOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a pImage argument. If CAPS is given
	ownership responsibility over @a pImage, it will be destroyed using
	caps_destroyBuffer() when no longer needed.

	@param pMask
	Buffer containing the alpha mask. The luminance
	channel of the mask image is used as the frame's alpha channel.

	@param maskOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a pMask argument. If CAPS is given
	ownership responsibility over @a pMask, it will be destroyed using
	caps_destroyBuffer() when no longer needed.

    @param invertAlpha
    If this is false, 0 - 255 is fading from session to frame
    If this is true,  0 - 255 is fading from frame to session

	@remarks

	A frame is an overlay image stretched or contracted to fit the size of the
	session image. The blending of the frame and the session image is
	defined by an alpha mask. The image and the alpha mask are stretched
	separately, and may have different dimensions.

	The following image types are supported for the image:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

	\n
	The following image types are supported for the mask:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

	\n
	The mask is typically a gray scale image.

	@return 
	@c CERR_OK if successful or a specific error code upon failure.

	@sa
	caps_insertFrameFileMask()\n
	caps_insertFrameFromBuffer()\n

	@since 3.6 (support for more image types in 3.8)

    @deprecated This function is deprecated since 5.3.
    Use caps_insertImageFromRawMask() instead.
*/
SCBIMPORT CRESULT caps_insertFrameFromBufferMask( CTSession session,
                                        CTBuffer* pImage,
                                        OWNERSHIP_POLICY imageOwnership, 
                                        CTBuffer* pMask,
                                        OWNERSHIP_POLICY maskOwnership,
                                        CTbool invertAlpha );

//-----------------------------------------------------------------------------
/**
	@brief
	Inserts a raw image on the current session with a separately defined alpha
	mask.

	@param session
	Handle to a valid session.

	@param pImage
	A raw image

	@param imageOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a pImage argument. If CAPS is given
	ownership responsibility over @a pImage, it will be destroyed using
	caps_destroyImage() when no longer needed.

	@param pMask
	A raw image containing the alpha mask.

	@param maskOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a pMask argument. If CAPS is given
	ownership responsibility over @a pMask, it will be destroyed using
	caps_destroyImage() when no longer needed.

    @param invertAlpha
    If this is false, 0 - 255 is fading from session to frame
    If this is true,  0 - 255 is fading from frame to session

	@remarks

	@note
	The supported color modes are different from caps_insertFrameFromRaw.

	The following color modes are supported for the image:

	@li @c  CM_ARGB8888
	@li @c  CM_BGRA8888
	@li @c  CM_RGBA8888
	@li @c  CM_RGB888
	@li @c  CM_BGR888
	@li @c  CM_RGB444
	@li @c  CM_RGB565
	@li @c  CM_BGR565
	@li @c  CM_ARGB6666
    @li @c  CM_GBRGAR264462
	@li @c  CM_BGRA6666
	@li @c  CM_AYUV4444

	The following color modes are supported for the mask:

	@li @c  CM_GRAY8
	@li @c  CM_GRAY4
	@li @c  CM_GRAY2
	@li @c  CM_GRAY1

	@return 
	@c CERR_OK if successful or a specific error code upon failure.

	@sa
	caps_insertFrameFromRaw()\n

	@since 3.6 (support for different sizes in 3.8)
*/
SCBIMPORT CRESULT caps_insertImageFromRawMask( CTSession session,
                                     CTImage* pImage,
                                     OWNERSHIP_POLICY imageOwnership,
                                     CTImage* pMask,
                                     OWNERSHIP_POLICY maskOwnership,
                                     CTbool invertAlpha );

/**
    @}
*/
// end 'fm_imagefusion_api'
//-----------------------------------------------------------------------------
/**
    @}
*/
// end 'fm_imagefusion'
//-----------------------------------------------------------------------------


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_IMAGEFUSION_H )
