/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    Copyright (c) 2000-2011 Scalado AB. All rights reserved.                 .
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

#ifndef CTVIEWPORT_H
#define CTVIEWPORT_H


#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @file ctviewport.h
    @brief This header defines the public interface of the CTViewport object.
    @ingroup ctviewport
*/
//=============================================================================
/**
    @addtogroup ctviewport
    @brief CTViewport is a helper object, to CTScreen2, for zooming, panning and
    rotating images.

    CTViewport is used by @ref ctscreen2 to perform zooming, panning and rotation.
    The CTViewport object can be used to get the viewport, and the modelview 
    matrix for an image after performing zooming, panning and rotation.

    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief Type representing CTViewport objects.
*/
typedef struct CTViewport CTViewport;

//-----------------------------------------------------------------------------
/**
    @brief Creates a @c CTViewport object.

    Both the width and height of the target and image dimensions must be larger 
    than 0.

    @param targetDims The dimensions of the target where the image should be 
                      presented. This could be the dimensions of a screen where 
                      the image is rendered.

    @param imageDims The dimensions of the source image to zoom and pan in.

    @param[out] ppViewport Pointer to the newly created object.

    @return @c CERR_OK on success.
*/
CRESULT ctviewport_create(CTSize targetDims, 
                          CTSize imageDims, 
                          CTViewport **ppViewport);

//-----------------------------------------------------------------------------
/**
    @brief Destroys a CTViewport object

    @param pViewport Pointer to the CTViewport object to destroy.
*/
void ctviewport_destroy(CTViewport *pViewport);

//-----------------------------------------------------------------------------
/**
    @brief Sets a specific zoom level.

    Level 0 equals the zoom level where the entire image is visible.
    Positive values equals zooming in, and negative values equals zooming out.
    Increasing the zoom factor by one doubles the zoom effect.
    
    If a pivot point has been set, this function will keep that point fixed
    in the viewport during the zooming motion, that is, that pivot point will 
    not appear to move regardless of zoom level. If a pivot point has not been 
    set, the current centre of the viewport is used as pivot point.

    @param pViewport A pointer to a CTViewport object.

    @param zoomLevel The new zoom level. Range [-16.0, 16.0]

    @return @c CERR_OK on success.
*/
CRESULT ctviewport_setZoom(CTViewport *pViewport, 
                           CTfloat zoomLevel);

//-----------------------------------------------------------------------------
/**
    @brief Gets the current zoom level.

    @param pViewport A pointer to a CTViewport object.

    @return The current zoom level.
*/
CTfloat ctviewport_getZoom(CTViewport *pViewport);

//-----------------------------------------------------------------------------
/**
    @brief Sets the zoom level with a specified midpoint.

    Sets the specified zoom @em level (range: [-16, 16]).
    After the zoom, the given midpoint (in source coordinates) will be centered
    on the target.

    @param pViewport A pointer to a CTViewport object.

    @param zoomLevel The new zoom level. Range [-16, 16]

    @param midPoint A point in source image coordinates on which the viewport
                    will be centered.

    @return @c CERR_OK on success.
*/
CRESULT ctviewport_setZoomPoint(CTViewport *pViewport,
                                CTfloat zoomLevel,
                                CTPointf midPoint);

//-----------------------------------------------------------------------------
/**
    @brief Gets the zoom level and midpoint.

    Gets the current zoom level, and the source image coordinates of the 
    current midpoint.

    @param pViewport A pointer to a CTViewport object.

    @param[out] pZoomLevel The zoom level. Range [-16, 16].

    @param[out] pMidPoint The source image coordinates of the center point of 
                          the target.

    @return @c CERR_OK on success.
*/
CRESULT ctviewport_getZoomPoint(CTViewport *pViewport,
                                CTfloat *pZoomLevel,
                                CTPointf *pMidPoint);

//-----------------------------------------------------------------------------
/**
    @brief Pan the image.

    Moves the visible part of the viewport object.

    @param pViewport A pointer to a CTViewport object.

    @param delta Point specifying the pan delta for x and y in source image
                 coordinates.

    @return @c CERR_OK on success.
*/
CRESULT ctviewport_pan(CTViewport *pViewport, CTPointf delta);

//-----------------------------------------------------------------------------
/**
    @brief Sets the rotation angle of the viewport.

    Sets the rotation angle of the image. If a pivot point has been set the
    image is rotated around the specified point, otherwise the centre of the
    viewport.

    @param pViewport A pointer to a CTViewport object.

    @param angle The angle, in degrees. Range [-360.0, 360.0]

    @return @c CERR_OK on success or an error code on failure.
*/
CRESULT ctviewport_setRotation(CTViewport *pViewport, 
                               CTfloat angle);

//-----------------------------------------------------------------------------
/**
    @brief Sets the pivot point.

    @param pViewport A pointer to a CTViewport object.
    
    @param pivotPoint Pivot point to set.
    
    @return CRESULT indicating status of the operation.
*/
CRESULT ctviewport_setPivotPoint(CTViewport *pViewport, CTPointf pivotPoint);

//-----------------------------------------------------------------------------
/**
    @brief Retrieves the pivot point
    
    If a pivot point has been set, this function will retrieve it. If no pivot
    point has been set, CERR_ILLEGAL_CALL is returned.

    @param pViewport A pointer to a CTViewport object.
    
    @param pPivotPoint Pivot point to retrieve.

    @return 
    @c CERR_OK if the pivot point was fetched.
    @c CERR_INVALID_PARAMETER if either of the two parameters were NULL.
    @c CERR_ILLEGAL_CALL if a pivot point has not been set.
*/
CRESULT ctviewport_getPivotPoint(CTViewport *pViewport, CTPointf *pPivotPoint);

//-----------------------------------------------------------------------------
/**
    @brief Clears the pivot point and moves the pivot back to the centre of the
    viewport.
    
    Calling this function will release the pivot point and further viewport 
    operations that utilize the pivot (setZoom, setRotation) will work on the 
    centre of the viewport instead.

    @param pViewport A pointer to a CTViewport object.

    @return 
    @c CERR_OK if the pivot point was fetched.
    @c CERR_INVALID_PARAMETER if either of the two parameters were NULL.
*/
CRESULT ctviewport_clearPivotPoint(CTViewport *pViewport);

//-----------------------------------------------------------------------------
/**
    @brief Convert from target coordinates to image coordinates.

    Converts a point in target coordinates to the corresponding point in source
    image coordinates.
    
    Note that not all points in the target coordinate system are part of the 
    source image, for example if the viewport is positioned so that it is 
    partially or fully outside of the source image.

    @param pViewport A pointer to a CTViewport object.

    @param targetPoint Point in the viewport coordinate system to convert.

    @param[out] pImagePoint Converted point in source the image coordinate system.

    @return @c CERR_OK on success or an error code on failure.
*/
CRESULT ctviewport_targetToImage(CTViewport *pViewport, 
                                 CTPointf targetPoint,
                                 CTPointf *pImagePoint);

//-----------------------------------------------------------------------------
/**
    @brief Convert from source image coordinates to viewport coordinates.

    Converts a point in source the source image to the viewport coordinate 
    system. Note that not every point in the source image is visible in
    the viewport, so the return value may not correspond to a valid viewport
    point (within the viewport constraints established during creation).
    
    @param pViewport A pointer to a CTViewport object.

    @param sourcePoint Point in the source image coordinate system
    
    @param[out] pTargetPoint Converted point in the target coordinate system.

    @return @c CERR_OK on success or an error code on failure.
*/
CRESULT ctviewport_imageToTarget(CTViewport *pViewport, 
                                 CTPointf sourcePoint,
                                 CTPointf *pTargetPoint);

//-----------------------------------------------------------------------------
/**
    @brief Gets the current viewport.

    @param pViewport A pointer to a CTViewport object.

    @return A rectangle specifying the current viewport, in source image
            coordinates, of the viewport object.
*/
CTRectf ctviewport_getViewport(CTViewport *pViewport);

//-----------------------------------------------------------------------------
/**
    @brief Get the one-to-one zoom level.

    Gets the zoom level required for viewing the source image full in resolution,
    i.e where one source point/pixel corresponds to one target image point/pixel.

    @param pViewport A pointer to a CTViewport object.

    @return The zoom level.
*/
CTfloat ctviewport_getOneToOneZoom(CTViewport *pViewport);

//-----------------------------------------------------------------------------
/**
    @brief Applies all settings from another viewport object.  

    This can be useful when you want to apply best fit factors, or some other
    precalculated state to a CTViewport object.

    @param pViewport Pointer to a destination viewport object.

    @param pViewportSource Pointer to a source viewport object.

    @return @c CERR_OK on success.
*/
CRESULT ctviewport_setFrom(CTViewport *pViewport, CTViewport *pViewportSource);

//-----------------------------------------------------------------------------
/**
    @brief Gets a viewport object with zoom and pan set to best fit.

    Returns a viewport object with zoom and pan set for best fit.
    The image is scaled so that the whole image is shown. The aspect ratio of
    the image is maintained. If the image does not fully fill the target area
    the image is centered on the target.

    @param pViewport A pointer to a CTViewport object.

    @param[out] ppBestFit Pointer to a viewport object.

    @return @c CERR_OK on success.
*/
CRESULT ctviewport_getBestFitFactors(CTViewport *pViewport, 
                                     CTViewport **ppBestFit);

//-----------------------------------------------------------------------------
/**
    @brief Gets the model view matrix.

    Gets the model view matrix describing the rotation, zoom and pan operations
    performed on the viewport object. The intended user of this function is 
    @c CTScreen2, it is probably of no use for other users of CTViewport.

    @param pViewport A pointer to a CTViewport object.

    @return Pointer to 16 consecutive values that are used as the elements of a		    
			4x4 column-major matrix.
*/
CTfloat *ctviewport_modelMatrix(CTViewport *pViewport);
//-----------------------------------------------------------------------------
/** @} */
// end of addtogroup 'ctviewport'

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CTVIEWPORT_H