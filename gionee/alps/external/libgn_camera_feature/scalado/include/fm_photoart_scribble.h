/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    © 2000-2010 Scalado AB. All rights reserved.                             .
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

#ifndef FM_PHOTOART_SCRIBBLE_H
#define FM_PHOTOART_SCRIBBLE_H
 
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/** 
    @ingroup fm_photoart
    @file fm_photoart_scribble.h
    @brief Defines the available API's for the scribble effect 
    in Caps Feature Module: @a PhotoArt
*/
//=============================================================================
/**
    @addtogroup fm_photoart
    @{
*/

/**
 @defgroup fxgroup_scribble Scribble 
 @{
 */

/**
 The handle type used for scribble insertion sessions.
 */
typedef struct caps_scribble* CAPS_SCRIBBLE;
//.............................................................................
/**
     Defines the brush shape to use with caps_setDotInScribble(),
     caps_setLineInScribble() and caps_removeDotInScribble().
 */
typedef enum 
{
    SHAPE_CIRCLE = 1,  ///< Circular Shape
    SHAPE_SQUARE       ///< Squared Shape
} CAPS_SCRIBBLE_SHAPE;
//.............................................................................
/**
     @brief
     Begins the task of creating a scribble image on the current session.
     
     @param pScreen A valid @c CTScreen.
     
     @param pImage 
     Optional argument. Pointer to a valid @c CTImage with the same size
     as the (above) provided @c pScreen. Supported image color modes are
     ::CM_COLOR_1_ALFA and ::CM_RGB565_G0.
     \n
     <b>Note</b>: Ownership of the image remains with the caller but must not be
     destroyed until the associated session is destroyed.
     If this argument is set to NULL an image will be allocated internally 
     for the scribble using the color mode provided in @c pImageColorMode. If an
     image is provided @c pImageColorMode must be set to NULL.
     
     @param pImageColorMode
     A pointer to a @c CTColormode containing the desired image color mode
     for the internally allocated scribble image. Valid color modes are 
     ::CM_COLOR_1_ALFA and ::CM_RGB565_G0.
     \n
     <b>Note</b>: If this argument is set to NULL a valid image must be provided in
     @c pImage. If a color mode is provided @c pImage must be set to NULL.
     
     @param color Specifies the color to use for drawing primitives.
     
     @param[out] out_scribble
     Pointer to a scribble handle.
     
     The task of inserting a scribble is carried out in three stages:
     -# Begin scribble insertion.
     -# Insert geometrical figures, dots or any data into the image.
     Change color and adjust orientation. (This step is optional).
     -# End scribble insertion.
     .
     
     Between step 1 and 3, no other effects or operations may be carried out;
     i.e the scribble insertion task have to be concluded/ended before 
     proceeding with other effects. Note that this includes Zoom and Pan
     operations. A scribble cannot be modified once the insertion process
     has been ended, the scribble handle is turned invalid after
     calling caps_endScribble().
     
     @return 
     @c CERR_OK if successful or a specific error code upon failure.
     
     @since 3.6
 */
SCBIMPORT CRESULT caps_beginScribble( CTScreen* pScreen,
                                     CTImage* pImage,
                                     CTColormode* pImageColorMode,
                                     CTColor color,
                                     CAPS_SCRIBBLE* out_scribble );

//.............................................................................
/**
    @brief
    Concludes the task of inserting a scribble image.
     
    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().
     
    @remarks
    The scribble handle will be invalid after calling this function.
     
    @return 
    @c CERR_OK if successful or a specific error code upon failure.
     
    @since 3.6
 */
SCBIMPORT CRESULT caps_endScribble( CAPS_SCRIBBLE scribble );
//.............................................................................
/**
    @brief
    Retrieves the current orientation setting for a scribble.

    All coordinates retrieved should be regarded within the current 
    coordinate system.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param[out] position
    Pointer to a @c CTPoint which will receive the current scribble
    position. Position refers to the center of the scribble.

    @param[out] scale
    Pointer to a @c CTfloat  which will receive the current scribble 
    scaling factor.

    @param[out] angle
    Pointer to a @c CTfloat which will receive the current scribble 
    rotation angle in degrees, [0.0 360.0].

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
 */
SCBIMPORT CRESULT caps_getScribbleOrientation( CAPS_SCRIBBLE scribble, CTPoint* position, 
                                              CTfloat* scale, CTfloat* angle);

//.............................................................................
/**
    @brief
    Adjusts the orientation of a scribble.

    The coordinates given to this function is current coordinate system.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param position
    A @c CTPoint specifying the vertical and horizontal position of 
    the scribble in current coordinates. Position refers to the center of 
    the scribble.

    @param scale    
    Scribble scaling factor. Range [0.001, 64.0].

    @param angle
    Rotation of the scribble in degrees, [0.0 360.0].

    @remarks
    After calling this function, no additional data can be inserted to
    the buffer with the functions: caps_setDotInScribble(), 
    caps_setLineInScribble(), caps_setRectangleInScribble(), 
    caps_setEllipseInScribble() and caps_removeDotInScribble().

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
 */
SCBIMPORT CRESULT caps_setScribbleOrientation( CAPS_SCRIBBLE scribble, CTPoint position, 
                                              CTfloat scale, CTfloat angle);

//.............................................................................
/**
    @brief
    Retrieves the current size of a scribble.

    The retrieved size should be regarded within the current coordinate 
    system.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param[out] size
    Pointer to a @c CTSize struct to which the width and height will be written.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
 */
SCBIMPORT CRESULT caps_getScribbleSize( CAPS_SCRIBBLE scribble, CTSize* size );

//.............................................................................
/**
    @brief
    Retrieves the current color of a scribble.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param[out] pColor
    A pointer to a @c CTColor which will receive the current scribble 
    color.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
 */
SCBIMPORT CRESULT caps_getScribbleColor( CAPS_SCRIBBLE scribble, CTColor* pColor );

//.............................................................................
/**
    @brief
    Adjusts the color of a scribble.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param color Specifies the color to use for drawing.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
 */
SCBIMPORT CRESULT caps_setScribbleColor( CAPS_SCRIBBLE scribble, CTColor color );

//.............................................................................
/**
    @brief
    Places a dot into the scribble.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param position
    A @c CTPoint specifying the position of the dot in @em screen
    @em coordinates. The coordinates are not allowed to be negative
    and must be smaller than the associated @c CTScreen object.

    @param dotRadius
    Specifies the radius of the squared dot. For example, a dot with
    radius 1 will be 3x3 pixels wide.

    @param shape
    Specifies the brush shape. Can be one of the values from the 
    @c CAPS_SCRIBBLE_SHAPE enumeration.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setScribbleOrientation()\n

    @since 3.6
 */
SCBIMPORT CRESULT caps_setDotInScribble( CAPS_SCRIBBLE scribble, 
                                        CTPoint position,
                                        CTuint32 dotRadius,
                                        CAPS_SCRIBBLE_SHAPE shape );

//.............................................................................
/**
    @brief
    Places a line ínto the scribble.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param srcCoords
    A @c CTPoint specifying the starting point of the line.
    The coordinates are not allowed to be negative and must be smaller
    than the associated @c CTScreen object.

    @param dstCoords
    A @c CTPoint specifying the end point of the line. The
    coordinates are not allowed to be negative and must be smaller than
    the associated @c CTScreen object.

    @param brushRadius
    Variable specifying the radius of the borders. The width of the border
    will be ( 2*brushRadius +1 ) pixels wide.

    @param shape
    Variable specifying the brush shape. Use one of the values from the 
    @c ::CAPS_SCRIBBLE_SHAPE enumeration.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setScribbleOrientation()\n

    @since 3.6
 */
SCBIMPORT CRESULT caps_setLineInScribble( CAPS_SCRIBBLE scribble, 
                                         CTPoint srcCoords, 
                                         CTPoint dstCoords, 
                                         CTuint32 brushRadius,
                                         CAPS_SCRIBBLE_SHAPE shape );

//.............................................................................
/**
    @brief
    Places a retangle into the scribble.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param upperLeft
    The coordinates of the upper-left corner of the rectangle. The
    coordinates are not allowed to be negative and must be smaller
    than the associated @c CTScreen object.

    @param rectangleSize
    Specifies the width and height of the rectangle.

    @param brushRadius
    The radius of the brush. The width of the border
    will be ( 2*brushRadius + 1 ) pixels wide.

    @param filled
    Determines whether the rectangle should be filled or not.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setScribbleOrientation()\n

    @since 3.6
 */
SCBIMPORT CRESULT caps_setRectangleInScribble( CAPS_SCRIBBLE scribble, 
                                              CTPoint upperLeft, 
                                              CTSize rectangleSize, 
                                              CTuint32 brushRadius,
                                              CTbool filled );

//.............................................................................
/**
    @brief
    Places a ellipse into the scribble.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param upperLeft
    Specifies the upper-left corner of the bounding-box for the ellipse.
    The coordinates are not allowed to be negative and must be smaller
    than the associated @c CTScreen object.

    @param ellipseSize
    Specifies the widht and height of the ellipse.

    @param brushRadius
    The radius of the brush. The width of the border
    will be ( 2*brushRadius + 1 ) pixels wide.

    @param filled
    Specifies whether the ellipse should be filled or not.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setScribbleOrientation()\n

    @since 3.6
 */
SCBIMPORT CRESULT caps_setEllipseInScribble( CAPS_SCRIBBLE scribble, CTPoint upperLeft, 
                                            CTSize ellipseSize, CTuint32 brushRadius,
                                            CTbool filled );

//.............................................................................
/**
    @brief
    Removes a dot into the scribble. This is an "Eraser"-function.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param coords
    Specifies the @em screen @em coordinates of the dot to remove.
    The coordinates are not allowed to be negative and must be smaller than
    the screen.

    @param dotRadius
    Radius of the dot. For example, a dot with
    radius 1 will be 3x3 pixels wide.

    @param shape
    The shape of the brush. Can be one of the values from the 
    @c ::CAPS_SCRIBBLE_SHAPE enumeration.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setScribbleOrientation()\n

    @since 3.6
 */
SCBIMPORT CRESULT caps_removeDotInScribble( CAPS_SCRIBBLE scribble, 
                                           CTPoint coords, 
                                           CTuint32 dotRadius,
                                           CAPS_SCRIBBLE_SHAPE shape );

//.............................................................................
/**
    @brief
    Erases all data in the image currently used by the scribble.
    All data in this buffer will be set to 0.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
 */
SCBIMPORT CRESULT caps_eraseScribbleBuffer( CAPS_SCRIBBLE scribble );

//.............................................................................
/**
    @brief
    Returns the image currently used by the scribble.

    @param scribble
    A valid scribble handle which has been created in a previous call to 
    caps_beginScribble().

    @param[out] scribbleBuffer
    Pointer address of a @c CTImage which, after the call, will point to the
    scribble image.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
 */
SCBIMPORT CRESULT caps_getCurrentScribbleBuffer( CAPS_SCRIBBLE scribble, 
                                                CTImage** scribbleBuffer );

/** @} */
// end 'Scribble'

/**
    @}
*/
// end 'fm_photoart_scribble'
//=============================================================================


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_PHOTOART_SCRIBBLE_H )
