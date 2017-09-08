/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2010 Scalado AB. All rights reserved.                           .
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

#ifndef FM_SPEEDVIEW_ANIMATION_H
#define FM_SPEEDVIEW_ANIMATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "caps_base.h"

//=============================================================================
/**
    @ingroup fm_speedview_animation
    @file fm_speedview_animation.h
    @brief The animation part of the Caps Feature Module: @a SpeedView
*/
//=============================================================================
/**
    @addtogroup fm_speedview_animation
    @brief Creating zoom, and pan, animations/transitions.
    @{
*/

typedef struct CTAnimation CTAnimation;

/**
    @brief
    This function creates the animation instance used for both zoom and pan.

    @param pScreen
    Handle to the screen.
 
    @param[out] ppAnimation
    Pointer to the animation instance pointer to be created.

    @return 
    CERR_OK if successful or a specific error code upon failure.
    CERR_INVALID_COLORMODE if the screen specifies an invalid color mode.

    @note
    Valid color modes are 
    @n (32 bit) CM_ARGB8888, CM_BGRA8888, CM_AYUV4444, CM_RGBA8888.
    @n (24 bit) CM_RGB888, CM_BGR888.
    @n (16 bit) CM_RGB565, CM_RGB565D, CM_RGB565FD.

    An animation object can only be used for one animation sequence. This means that  
    only one pair of caps_animationBegin and caps_animationEnd may exists between 
    caps_animationCreate() and caps_animationDestroy().

    @deprecated This function has been deprecated since 3.10.2 Use instead
    @c caps_animationCreateEx()

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationCreate( CTScreen* pScreen,
                                        CTAnimation** ppAnimation );


//-----------------------------------------------------------------------------
/**
    @brief
    This function creates the animation instance used for both zoom and pan, 
    with a specified quality setting.

    This function allows user to balance between memory consumption and 
    animation visual quality.

    @param  pScreen
    Handle to the screen.
 
    @param quality
    Quality setting 100 equals highest quality and memory consumption.
    Quality parameter range is between 1-100.
    
    @param[out] ppAnimation
    Pointer to the animation instance pointer to be created.

    @return 
    CERR_OK if successful or a specific error code upon failure.
    CERR_INVALID_COLORMODE if the screen specifies an invalid color mode.

    @note
    Valid color modes are 
    @n (32 bit) CM_ARGB8888, CM_BGRA8888, CM_AYUV4444, CM_RGBA8888.
    @n (24 bit) CM_RGB888, CM_BGR888.
    @n (16 bit) CM_RGB565, CM_RGB565D, CM_RGB565FD.

    An animation object can only be used for one animation sequence. This means that  
    only one pair of caps_animationBegin and caps_animationEnd may exists between 
    caps_animationCreate() and caps_animationDestroy().

    @since 3.10.2

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationCreateEx( CTScreen* pScreen, 
                                          CTuint32 quality, 
                                          CTAnimation** ppAnimation );


//-----------------------------------------------------------------------------
/**
    @brief
    This function makes all preparation required for a pan animation.

    @param pAnimation 
    Pointer to the animation instance.

    @param pStopPoint
    The desired destination midpoint coordinate.

    @return 
    @c CERR_OK If successful or a specific error code upon failure.
    @c CERR_ILLEGAL_CALL if an animation has already been started on this object.

    @note
    The animation API may modify the destination point due to screen size 
    constraints at the current zoom level. Use caps_animationGetEndPoint to 
    retrieve the actual animation stop point.

    Current zoom and mid point is fetched from the screen object provided 
    to the animation object during construction.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationBeginPan(CTAnimation* pAnimation, CTPoint* pStopPoint);
//-----------------------------------------------------------------------------
/**
    @brief
    This function makes all preparation required for a zoom animation.

    @param  pAnimation
    Animation instance to modify.

    @param  zoomStop
    The desired zoom factor of the last frame in the animation.

    @param pTargetPoint
    Target midpoint of the end image. May be NULL, which means that the
    target point will be as unmodified as possible (due to screen constraints
    it may still be moved).

    @param[out] ppIt
    Use an iterator to distribute the begin animate calculations. If ppIt 
    is NULL, then all calculations needed for begin animation will be done 
    in one step. For more information on how to use caps iterator, see 
    @c CTIterator.

    @return
    @c CERR_OK if successful or a specific error code upon failure.
    @c CERR_ILLEGAL_CALL if an animation has already been started on this object.
    @c CERR_INVALID_PARAMETER if the target point and zoom factor combines to 
    produce a view rectangle which ends up outside the current screen.

    @note
    The animation API may fail due to screen constraints. A target zoom 
    rectangle which is not a subset of the current screen view rectangle will 
    return CERR_INVALID_PARAMETER.

    The destination point may also be clamped to the image. In this case
    the view rectangle will be moved to contain as much image data as possible.
    Use caps_animationGetEndPoint to retrieve the actual stop point.

    Current zoom and mid point is fetched from the screen object provided to 
    the animation object during construction.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationBeginZoom(CTAnimation* pAnimation,
                                          CTfloat zoomStop,
                                          CTPoint* pTargetPoint,
                                          CTIterator** ppIt);
//-----------------------------------------------------------------------------
/**
    @brief
    Function to render an animated zoom frame and do animation calculations.

    @param  pAnimation
    Pointer to the animation object

    @param  frameIndex
    The requested frame index, specified in the range [0, 1], where zero is 
    the first frame of the animation and 1 is the last. Specifying a value 
    less than zero returns a CERR_INVALID_PARAMETER. See notes for how values
    greater than 1 are handled. 
    
    Use caps_animationGetFrameIndex to retrieve a suitable frame index if 
    only the desired zoom factor is available.

    @param  renderIndex
    renderIndex, 0.0 to 1.0, specifies how much background processing the 
    application expects  that the animation module has done so far. If 
    outside the allowed range, it is clamped to the allowed values.

    @return 
    @c CERR_OK if successful, or a specific error code on failure.

    @note
    If frameIndex is set to less than zero, a CERR_INVALID_PARAMETER is 
    returned.

    If frameIndex is greater than 1.0 and the animation has been extended
    the call will trigger the extension, and frameIndex (0.0 to 1.0) will be assumed
    to represent the new (extended) range in the next call to this function.

    @sa
    caps_animationGetFrameIndex(); \n
    caps_animationExtendZoom(); \n

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationUpdateScreen(CTAnimation* pAnimation, 
                                             CTfloat frameIndex,
                                             CTfloat renderIndex );

//-----------------------------------------------------------------------------
/**
    @brief
    Ends the zoom animation by finishing all remaining jobs and updates the 
    screen with the specified end frame. This function may require heavy 
    calculations, depending on how much background processing that have 
    been performed before this function is called. Therefore, this function 
    offers the possibility to use an iterator to distribute the calculations.
    The the animation object can not be reused afterwards.

    @param   pAnimation
    Pointer to the animation object

    @param[out] ppIt
    Use an iterator to distribute the calculations. If ppIt is NULL, then all 
    calculations will be done in one step. For more information on how to use 
    caps iterator, see @c CTIterator. 

    @return 
    @c CERR_OK If successful or a specific error code upon failure.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationEnd(CTAnimation* pAnimation,
                                    CTIterator** ppIt);
//-----------------------------------------------------------------------------
/**
    @brief
    This function destroys the animation object.

    @param   pAnimation
    Pointer to the animation object

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT void caps_animationDestroy(CTAnimation* pAnimation);
//-----------------------------------------------------------------------------
/**
    @brief
    This function extends the zoom animation, to allow an easy implementation 
    of for example continuous zooming. 

    @param pAnimation
    Pointer to the animation object

    @param newZoomStop
    Desired new end zoom factor.

    @return 
    @c CERR_OK If successful or a specific error code upon failure.

    @note
    There is no performance cost associated with calling 
    caps_animationExtendZoom, but the animation module may start to do 
    internal calculations in order to provide a smooth zoom. It is therefore 
    beneficial to extend the zoom as early as possible to smooth out these 
    calculations over several iterations of caps_animationUpdateScreen.

    caps_animationExtendZoom must be called before the function 
    caps_animationUpdateScreen returns CRES_TASK_COMPLETE. 
    If caps_animationExtendZoom is called after CRES_TASK_COMPLETE is returned 
    from caps_animationUpdateScreen, the extended zoom will be ignored. 

    Successive calls to caps_animationExtendZoom will overwrite each other 
    and dispose of any previous calculations made.

    Zooming is not extended until the previous zoomStop (specified in 
    caps_animationBeginZoom) has been passed.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationExtendZoom(CTAnimation* pAnimation, CTfloat newZoomStop);
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the zoom/pan setting for a certain animation frame.

    @param pAnimation
    Pointer to the animation object to query.

    @param frameIndex
    Frame index of the animation frame to query for zoom/pan coordinates. Frame
    index must be between [0, 1] or a @c CERR_INVALID_PARAMETER is returned.

    @param[out] pMidPoint
    Midpoint of the requested frame in image coordinates.

    @param[out] pZoom
    Zoom level of the requested frame.

    @return
    @c CERR_OK If successful or a specific error code upon failure.
    @c CERR_ILLEGAL_CALL if an animation is not running.
    @c CERR_INVALID_PARAMETER if frameIndex is out of bounds, or a NULL
    animation object is passed.

    @note
    pMidPoint or pZoom may be NULL. In that case, no information is returned
    for that parameter.

    An animation must be started for this call to be valid.

    @c ::caps_animationGetEndPoint is a special case of this function, with
    frameIndex set to 1.0.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT caps_animationGetZoomPoint(CTAnimation* pAnimation, 
                                             CTfloat frameIndex, 
                                             CTPoint* pMidPoint, 
                                             CTfloat* pZoom);

//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the current end point, ie. the zoom level and position at which
    the final frame will be rendered when calling caps_animationEnd.

    @param  pAnimation
    Pointer to the animation object

    @param[out]  pMidPoint
    Midpoint of the final frame in image coordinates.

    @param[out]  pZoom
    Zoom level of the final frame.

    @return
    @c CERR_OK If successful or a specific error code upon failure.
    @c CERR_ILLEGAL_CALL if an animation is not running.

    @note
    pMidPoint or pZoom may be NULL. In that case, no information is returned
    for that parameter.

    An animation must be started for this call to be valid.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_animationGetEndPoint(CTAnimation* pAnimation, 
                                            CTPoint* pMidPoint, 
                                            CTfloat* pZoom);
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the frameIndex for a certain zoom level when using zoom 
    animations.

    @param pAnimation
    Pointer to the animation object

    @param zoom
    Zoom level to query for frameIndex.

    @param[out]  pFrameIndex
    Frame index to set to caps_animationRenderFrame. The frame index is
    returned according to the zoom provided so it may be out of bounds
    compared to what caps_animationUpdateScreen expects. Please see 
    @c caps_animationUpdateScreen for a discussion on how that function
    handles out of bounds parameters.

    @return
    @c CERR_OK if successful.
    @c CERR_ILLEGAL_CALL if the animation object is not a zoom animation.
    or a specific error code upon failure.

    @note
    A zoom animation must be started for this call to be valid.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT caps_animationGetFrameIndex(CTAnimation* pAnimation, 
                                              CTfloat zoom, 
                                              CTfloat* pFrameIndex);
//-----------------------------------------------------------------------------
/**
    @}
*/ //'fm_speedview_animation'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif // FM_SPEEDVIEW_ANIMATION_H

