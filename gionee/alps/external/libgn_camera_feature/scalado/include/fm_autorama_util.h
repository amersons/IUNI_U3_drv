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

#ifndef FM_AUTORAMA_UTIL_H
#define FM_AUTORAMA_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fm_autorama.h"

//=============================================================================
/**
    @ingroup fm_autorama_util
    @file fm_autorama_util.h
    @brief Utility functions for the AutoRama feature module.
*/
//=============================================================================
/**
    @addtogroup fm_autorama_util
    @brief Utility functions for the feature module AutoRama

    @{
*/
//-----------------------------------------------------------------------------
/**
    @defgroup example_create_viewfinder_warp Example - warp table creation.
    @brief Sample code illustrating usage of caps_panoramaUtilCreateViewfinderWarp()
    @{
        @include create_viewfinder_warp.c
    */  // see: .../modules/fm_autorama_util/doc/
/** @} */
//-----------------------------------------------------------------------------
/**
    @brief Creates a warp table to be used when overlaying a part of the previous
    capture in the live viewfinder.

    A panoramic image is created from several images, captured by the camera device
    user in a controlled manner. In order to guide the user to aim the camera
    device optimally, a part of the latest captured image can be shown overlaid
    on the live viewfinder image. Due to camera geometry, the latest
    captured image must be transformed - warped - prior to overlaying it on the
    viewfinder. This function, caps_panoramaUtilCreateViewfinderWarp(), creates this
    transform, as a warp buffer that can be passed to caps_applyWarp().

    @image html CropRectangles.png

    The left image shows the latest captured image (dashed line),
    with the desired overlap (grey).
    The right image shows the warped latest captured image (dashed line), the
    current viewfinder image (solid line) and the warped overlap (grey).

    Setup:
    -# Capture dimensions are @c im_w, @c im_h
    -# Viewfinder dimensions are @c vf_w , @c vf_h
    -# The desired overlap is @c overlap . For example 0.30f if the overlap is 30%
    -# Lens parameters are in @c pLens
    .

    Constraints:
    -# The panorama direction is left to right. ->
    -# The aspect ratio of the captured image, the viewfinder image and the lens
        must be the same.
        - @code im_w / im_h == vf_w / vf_h @endcode
        - @code im_w / im_h == pLens->iWidth / pLens->iHeight @endcode
        .
    .

    Usage overview:
    -# Initialize warp. Calculate the viewfinder warp with
    caps_panoramaUtilCreateViewfinderWarp().
    -# @c n @c = @c 0
    -# Capture image n, @c im_n
    -# For each new capture:
        -# Create a viewfinder sized image from the capture, @c vf_n
        -# Crop the overlapping part of @c vf_n, call this @c vf_crop_n
        -# Apply the calculated warp to @c vf_crop_n.
        -# Crop the warped image with pOutputCrop, resulting in @c overlay_n
        -# For each frame
            -# Display the @c overlay_n on top of the
               live viewfinder until a new capture is triggered.
            .
        -# @c n++
        .
    .

    @image html algosteps.png

    For implementation details, see example:
    @a create_viewfinder_warp.c (below)

    @param[out] pIxOutputCrop The overlap parameter defines a crop rectangle of the
    latest capture. The pIxOutputCrop coordinates are defined as relative
    coordinates in this rectangle. each coordinate is in the range [0 , 65536]
    @param[out] ppWarpBuffer Warp buffer compatible with caps_applyWarpFromBuffer().
    The ownership of the result belongs to the caller. Thus the buffer must be
    destroyed with caps_destroyBuffer().
    @param pLens A lens description
    @param overlap Desired overlap between two successive image captures. Range
    [0.1f, 1.0f].

    @return CERR_OK or a specific error code.

    @since 3.3
*/
SCBIMPORT CRESULT caps_panoramaUtilCreateViewfinderWarp( CTRect* pIxOutputCrop,
                                         CTBuffer** ppWarpBuffer,
                                         const PanoramaLens* pLens,
                                         CTfloat overlap );

//-----------------------------------------------------------------------------
/**
    @}
*/ // end 'fm_autorama_util'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // FM_AUTORAMA_UTIL_H
