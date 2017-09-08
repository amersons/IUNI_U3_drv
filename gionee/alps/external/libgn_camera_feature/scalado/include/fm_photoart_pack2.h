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

#ifndef FM_PHOTOART_PACK2_H
#define FM_PHOTOART_PACK2_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/**
    @ingroup fm_photoart
    @file fm_photoart_pack2.h
    @brief Defines the available API's for filters included in filter pack 2
    for the Caps Feature Module: @a PhotoArt
*/
//=============================================================================
/**
    @addtogroup fm_photoart
    @{
*/

//-----------------------------------------------------------------------------


/** @defgroup fx_chromakey ChromaKey */
/**
    @ingroup fx_chromakey

    @brief
    Adds alfa channel data to the current session image.

    @param session
    A valid session handle.

    @param key
    The color to make transparent. R, G and B are used to define the key.
    A is used to determine the amount of transparency for a non-key color
    pixel. A value of 0 gives full transparency and a value of 255 gives
    no transparency.

    @param invertAlfa
    If false, full transparency in the alfa channel is the value 0.
    If true, full transparency in the alfa channel is the value 255.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

*/
SCBIMPORT CRESULT caps_applyChromaKey( CTSession session,
                             CTColor key,
                             CTbool invertAlfa );

//-----------------------------------------------------------------------------

/** @defgroup fx_antique Antique */
/**
    @ingroup fx_antique

    @brief
    Produces a look of an old color photo.

    @param session
    A valid session handle.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_applyAntique( CTSession session );

//-----------------------------------------------------------------------------

/**
    @ingroup fx_oily

    @brief
    Makes the session image look like an oil painting.

    @param session
    A valid session handle.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyOily( CTSession session );

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_color_adjustment Color Adjustment
    @{
        @copydoc begin_end_effects
*/

/**
    @brief
    Begins the task of adjusting the RGB color values.

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginRGBColorAdjust( CTSession session );
//.............................................................................
/**
    @brief
    Adjusts the RGB color composition of the current session image.

    @param session
    Handle to a valid session.

    @param r
    Red channel adjustment. Range (-1.0) - (1.0).

    @param g
    Green channel adjustment. Range (-1.0) - (1.0).

    @param b
    Blue channel adjustment. Range (-1.0) - (1.0).

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setRGBColorAdjust( CTSession session, CTfloat r, CTfloat g,
                                CTfloat b );
//.............................................................................
/**
    @brief
    Applies the color adjustments made to the current session.

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endRGBColorAdjust( CTSession session );
/** @} */
// end 'Color Adjustment'

//-----------------------------------------------------------------------------

/** @defgroup fx_oily Oily
    @{
        @copydoc begin_end_effects
*/

/**
    @brief Defines the intensity of the effect applied by caps_setOily()
*/
typedef enum
{
    OILY_LOW = 4,          ///< Low
    OILY_MEDIUM = 8,       ///< Medium
    OILY_HIGH = 12         ///< High

} CAPS_OILY_LEVEL;
//.............................................................................

/**
    @brief
	Begins the task of applying an oily effect to the current session image.

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8.2
*/
SCBIMPORT CRESULT caps_beginOily( CTSession session );

//.............................................................................
/**
    @brief
    Applies oily effect to the current session image.

    @param session
    Handle to a valid session.

    @param oily_level
    The level of the oily effect. Can be one of the values from the
    @c ::CAPS_OILY_LEVEL enumeration.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8.2
*/
SCBIMPORT CRESULT caps_setOily( CTSession session, CAPS_OILY_LEVEL oily_level);

//.............................................................................
/**
    @brief
    Ends the task of applying an oily effect to the current session image.

    @param session
    Handle to a valid session.

    @since 3.8.2
*/
SCBIMPORT void caps_endOily( CTSession session );

/** @} */
// end defgroup 'fx_oily'

//-----------------------------------------------------------------------------

/** @defgroup fx_milky Milky */
/**
    @ingroup fx_milky

    @brief
    Applies a "milky" surface effect to the current session image.

    @param session
    A valid session handle.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0

*/
SCBIMPORT CRESULT caps_applyMilky( CTSession session );

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_emboss Emboss
    @{
        @copydoc begin_end_effects
*/
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginEmboss( CTSession session );
//.............................................................................
/**
    @brief
    Applies an emboss effect in grayscale.

    @param session
    Handle to a valid session.

    @param emboss_level
    The level of the emboss effect.
    Range: 0.0 - 1.0

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setEmboss( CTSession session, CTfloat emboss_level );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endEmboss( CTSession session );
/** @} */
// end 'Emboss'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_solarize Solarize
    @{
        @copydoc begin_end_effects
*/
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginSolarize( CTSession session );
//.............................................................................
/**
    @brief
    Applies a solarize effect.

    @param session
    Handle to a valid session.

    @param threshold
    The threshold level of the solarize effect.
    Range: 0.0 - 1.0

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setSolarize( CTSession session, CTfloat threshold );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endSolarize( CTSession session );
/** @} */
// end 'Solarize'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_posterize Posterize
    @{
        @copydoc begin_end_effects
*/
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginPosterize( CTSession session );
//.............................................................................
/**
    @brief
    Applies a posterize effect. Reduces the number of colors.

    @param session
    Handle to a valid session.

    @param levels
    The number of allowed values for each color component.
    Range: 2 - 16

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setPosterize( CTSession session, CTuint16 levels );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endPosterize( CTSession session );
/** @} */
// Posterize'

//-----------------------------------------------------------------------------

/** @defgroup fx_fog Fog */
/**
    @ingroup fx_fog

    @brief
    Applies a fog effect.

    @param session
    A valid session handle.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_applyFog( CTSession session);

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_stamp Stamp
    @{
        @copydoc begin_end_effects
*/
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginStamp( CTSession session );
//.............................................................................
/**
    @brief
    Applies a stamp effect. Result is a b/w image.

    @param session
    Handle to a valid session.

    @param smoothness
    Range: 0-6

    @param threshold
    Range: 0-255

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setStamp( CTSession session, CTuint8 smoothness, CTuint8 threshold );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endStamp( CTSession session );
/** @} */
// end 'Stamp'

//-----------------------------------------------------------------------------

/**
    @defgroup fx_sketch Sketch
    @{
*/

/**
    @brief Defines the sketch modes to use with caps_applySketch().
*/
typedef enum
{
    SKETCH_GRAY = 0,    ///< Sketch the image in gray.
    SKETCH_COLOR = 1    ///< Sketch the image in color.
} CAPS_SKETCH_MODE;
//.............................................................................
/**
    @brief

    @param session
    A valid session handle.

    @param mode
    How to sketch the image.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_applySketch( CTSession session, CAPS_SKETCH_MODE mode );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.x
*/
SCBIMPORT CRESULT caps_beginSketch( CTSession session );
//.............................................................................
/**
    @brief

    @param session
    A valid session handle.

    @param mode
    How to sketch the image.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.x
*/
SCBIMPORT CRESULT caps_setSketch( CTSession session, CAPS_SKETCH_MODE mode );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.x
*/
SCBIMPORT void caps_endSketch( CTSession session );
/** @} */
// Sketch

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_noise Noise
    @{
        @copydoc begin_end_effects
*/

/**
    @brief Possible 'Noise' settings.
*/
typedef enum
{
    NOISE_MIN = 1,
    NOISE_MEDIUM,
    NOISE_MAX

} CAPS_NOISE_LEVEL;
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginNoise( CTSession session );
//.............................................................................
/**
    @brief
    Applies noise to the current session image.

    @param session
    Handle to a valid session.

    @param noise
    The amount of noise. Can be any of the values from the @c ::CAPS_NOISE_LEVEL
    enumeration.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setNoise( CTSession session, CAPS_NOISE_LEVEL noise );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endNoise( CTSession session );
/** @} */
// Noise

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_spotlight Spotlight
    @{
*/

/**
    @brief The handle type used for spotlight insertion sessions.
*/
//.............................................................................
typedef struct caps_spotlight* CAPS_SPOTLIGHT;
//.............................................................................
/**
    @brief
    Begins the task of inserting a spotlight effect on the current session
    image.

    The coordinates given to this function is interpreted as being
    within the "current" coordinate system. See section 'Coordinate conversions'
    in @ref caps_baseapi_screen

    @param session
    A valid session handle.

    @param position
    A @c CTPoint value specifying the center of the spotlight circle.

    @param radius
    The radius of the spotlight circle in pixels. Current coordinates.
    Range: [ 0 , 65535 - 1024 ]

    @param transition_size
    The size of the transition region given in fraction of the radius.
    See the Developers Guide for more information.
    Range: [ 0.0 , 1.0 ]

    @param spotlight
    Pointer to a @c CAPS_SPOTLIGHT value which will receive the spotlight
    handle for subsequent adjustments and conclusion of the spotlight
    insertion. See remarks section for details.

    @remarks
    The task of inserting a spotlight is carried out in three stages:
    @n
    -# Begin spotlight insertion.
    -# Adjust spotlight orientation (optional)
    -# End spotlight insertion.
    .
    @n
    Between step 1 and 3, no other effects or operations may be carried out.
    I.e. the spotlight insertion task have to be concluded/ended before
    proceeding with other effects. A spotlight cannot be modified once the
    insertion process has been ended, the spotlight handle is effectively
    turned invalid after calling caps_endSpotlight().

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_setSpotlightOrientation()
    - caps_getSpotlightOrientation()
    - caps_endSpotlight()
    .

    @since 3.0
*/
SCBIMPORT CRESULT caps_beginSpotlight( CTSession session, CTPoint position, CTuint32 radius,
                             CTfloat transition_size, CAPS_SPOTLIGHT* spotlight);
//.............................................................................
/**
    @brief
    Adjusts the orientation of a spotlight effect.

    The coordinates given to this function is interpreted as being within the
    "current" coordinate system. See section 'Coordinate conversions'
    in @ref caps_baseapi_screen

    @param spotlight
    A valid @c CAPS_SPOTLIGHT handle which has been created in a previous call to
    caps_beginSpotlight().

    @param position
    A @c CTPoint value specifying the position of the spotlight circle.

    @param radius
    The radius of the spotlight circle in pixels.
    Range: (0 <= radius <= 65535 - 1024)

    @param transition_size
    The size of the transition region given in fraction of the radius.
    See the Developers Guide for more information.
    Range: (0.0 < transition_size <= 1.0)

    @remarks

    Note that a spotlight handle is invalid after calling caps_endSpotlight()
    with it. The behaviour when calling this function with an invalid spotlight
    handle is undefined.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_beginSpotlight()
    - caps_getSpotlightOrientation()
    - caps_endSpotlight()
    .

    @since 3.0
*/
SCBIMPORT CRESULT caps_setSpotlightOrientation( CAPS_SPOTLIGHT spotlight, CTPoint position,
                                      CTuint32 radius, CTfloat transition_size );
//.............................................................................
/**
    @brief
    Retrieves the current orientation setting for a spotlight effect.

    All coordinates retrieved should be regarded within the "current"
    coordinate system.

    @param spotlight
    A valid @c CAPS_SPOTLIGHT handle which has been created in a previous call to
    caps_beginSpotlight().

    @param position
    Pointer to a @c CTPoint object which will receive the current spotlight
    position.

    @param radius
    Pointer to a @c CTuint32 value which will receive the radius of the spotlight
    circle in pixels. Range: (0 <= radius <= 65535 - 1024)

    @param transition_size
    Pointer to a @c CTfloat value which will receive the size of the transition
    region in fractions of the radius, See the Develops Guide for more information.
    Range: (0.0 < transition_size <= 1.0)

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_beginSpotlight()
    - caps_setSpotlightOrientation()
    - caps_endSpotlight()
    .

    @since 3.0

*/
SCBIMPORT CRESULT caps_getSpotlightOrientation( CAPS_SPOTLIGHT spotlight,
                                      CTPoint* position, CTuint32* radius,
                                      CTfloat* transition_size);
//.............................................................................
/**
    @brief
    Concludes the task of inserting a spotlight effect.

    @param spotlight
    A valid @c CAPS_SPOTLIGHT handle which has been created in a previous call to
    caps_beginSpotlight().

    @remarks

    The spotlight handle is invalid after calling this function and should
    preferably be reset to null directly upon calling it.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_beginSpotlight()
    - caps_setSpotlightOrientation()
    - caps_getSpotlightOrientation()
    .

    @since 3.0
*/
SCBIMPORT CRESULT caps_endSpotlight( CAPS_SPOTLIGHT spotlight );
/** @} */
// end 'Spotlight'

//-----------------------------------------------------------------------------

/** @defgroup fx_moonlight Moonlight */
/**
    @ingroup fx_moonlight

    @brief
    Applies a Moonlight effect on the current session image.

    @param session
    A valid session handle.

	@param clock
	Time of night in clock (1~24) affect only at night time (17~7).


	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_applyMoonlight( CTSession session, CTint16  clock);

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_frosted_glass Frosted Glass
    @{
        @copydoc begin_end_effects
*/

/**
    @brief Defines the "frosted glass" impact levels to use
    with caps_applyFrostedGlass().
*/
typedef enum
{
    FROSTED_MINIMUM = 1,  ///< Minimum
    FROSTED_LOW,          ///< Low
    FROSTED_MEDIUM,       ///< Medium
    FROSTED_HIGH,         ///< High
    FROSTED_MAX,          ///< Max
	FROSTED_5,
	FROSTED_6,
	FROSTED_7,
	FROSTED_8

} CAPS_FROSTED_LEVEL;
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginFrostedGlass( CTSession session );
//.............................................................................
/**
    @brief
    Applies a "frosted glass" surface effect on the current session image.

    @param session
    Handle to a valid session.

    @param level
    The effect level. Can be any of the values from the @c ::CAPS_FROSTED_LEVEL
    enumeration.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setFrostedGlass( CTSession session, CAPS_FROSTED_LEVEL level );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endFrostedGlass( CTSession session );
/** @} */
// end 'Frosted Glass'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_mosaic Mosaic
    @{
        @copydoc begin_end_effects
*/

/**
    @brief Defines the mosaic impact levels to use with caps_setMosaic().
*/
typedef enum
{
	MOSAIC_SIZE_8 = 1,	///< 8x8 square
	MOSAIC_SIZE_16,		///< 16x16 square
	MOSAIC_SIZE_32,		///< 32x32 square
	MOSAIC_SIZE_64,		///< 64x64 square
	MOSAIC_SIZE_128		///< 128x128 square
} CAPS_MOSAIC_SIZE;
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7
*/
SCBIMPORT CRESULT caps_beginMosaic( CTSession session );
//.............................................................................
/**
    @brief
    Mosaic effect to the current session image.

    @param session
    Handle to a valid session.

    @param size
    The Mosaic square size. Can be any of the values from the @c ::CAPS_MOSAIC_SIZE
    enumeration.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7
*/
SCBIMPORT CRESULT caps_setMosaic( CTSession session, CAPS_MOSAIC_SIZE size );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.7
*/
SCBIMPORT void caps_endMosaic( CTSession session );
/** @} */
// end 'Mosaic'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_despeckle Despeckle
    @{
        @copydoc begin_end_effects
*/

/**
    @brief Defines the despeckle impact levels to use with caps_applyDespeckle().
*/
typedef enum
{
    DESPECKLE_MINIMUM = 1,  ///< Minimum
    DESPECKLE_LOW,          ///< Low
    DESPECKLE_HIGH,         ///< High
	DESPECKLE_MAX,			///< Max
    DESPECKLE_5,
	DESPECKLE_6,
	DESPECKLE_7,
	DESPECKLE_8

} CAPS_DESPECKLE_LEVEL;
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginDespeckle( CTSession session );
//.............................................................................
/**
    @brief
    Applies a "despeckle" surface effect to the current session image.

    @param session
    Handle to a valid session.

    @param level
    The effect level. Can be any of the values from the @c ::CAPS_DESPECKLE_LEVEL
    enumeration.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setDespeckle( CTSession session, CAPS_DESPECKLE_LEVEL level );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endDespeckle( CTSession session );
/** @} */
// end 'Despeckle'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_blur Blur
    @{
        @copydoc begin_end_effects
*/

/**
    @brief Defines the blur impact levels to use with caps_applyBlur().
*/
typedef enum
{
    BLUR_MINIMUM = 1,  ///< Minimum
    BLUR_LOW,          ///< Low
    BLUR_HIGH,         ///< High
    BLUR_MAX,          ///< Max
	BLUR_5,
	BLUR_6,
	BLUR_7,
	BLUR_8

} CAPS_BLUR_LEVEL;
//.............................................................................
/**
    @brief Defines the way the blur region is interpreted.
*/
typedef enum
{
    BLUR_REGION_RECTANGULAR, ///< The region is a rectangle
    BLUR_REGION_CIRCULAR     ///< The region is an ellipse fitted into a rectangle
} CAPS_BLUR_REGION_MODE;
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginBlur( CTSession session );
//.............................................................................
/**
    @brief
    Blurs the current session image.

    @param session
    Handle to a valid session.

    @param level
    The blur effect level. Can be any of the values from the @c ::CAPS_BLUR_LEVEL
    enumeration.

    @param region
    (OPTIONAL) Pointer to a @c CTRect object specifying the effective region to
    blur within the image, given in current coordinates. Set this
    argument to @c NULL if the effect should be applied to the entire image.
    The blur is applied to the entire image if the width and/or height value is zero
    (independent of the position).
    The coordinates given will correspond to the upper-left corner of the blur region.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setBlur( CTSession session, CAPS_BLUR_LEVEL level, CTRect* region );
//.............................................................................
/**
    @brief
    Set the region mode of the blur effect

    @param session
    Handle to a valid session.

    @param mode
    The blur region mode. Can be any of the values from
    the @c ::CAPS_BLUR_REGION_MODE
    enumeration.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7
*/
SCBIMPORT CRESULT caps_setBlurRegionMode( CTSession session, CAPS_BLUR_REGION_MODE mode);
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endBlur( CTSession session );
/** @} */
// end 'Blur'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_colorize Colorize
    @{
        @copydoc begin_end_effects
*/

/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginColorization( CTSession session );
//.............................................................................
/**
    @brief
    Adjusts color tone and luminance/chrominance levels.
    Adds a single color to an image.

    @param session
    Handle to a valid session.

    @param r
    Red component of reference color.
    Range: 0-255

    @param g
    Green component of reference color.
    Range: 0-255

    @param b
    Blue component of reference color.
    Range: 0-255

    @param luminance_strength
    Strength of luminance.
    Range: (-100)-(200)

    @param chrominance_strength
    Strength of chrominance.
    Range: (-100)-(200)

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setColorization( CTSession session, CTuint8 r, CTuint8 g,
                              CTuint8 b, CTint16 luminance_strength,
                              CTint16 chrominance_strength );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endColorization( CTSession session );
/** @} */
// end 'Colorize'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_monocolor Mono Color
    @{
        @copydoc begin_end_effects
*/

/**
    @brief
    Preserves one color-tone and will convert other colors to grayscale.

    @param session
    Handle to a valid session.

    @param preserveColor
	Parameter that specifies which color that should be preserved.

    @param colorDistance
	Specifies the tolerance level of the effect. If the colorDistance is
	small, only a small variation around the color defined with preserveColor
	will be preserved. Must be in the range 0 < colorDistance <=255.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7
*/
SCBIMPORT CRESULT caps_beginMonoColor( CTSession session, CTColor preserveColor,
							 CTuint32 colorDistance );
//.............................................................................
/**
    @brief
    Adjusts the parameters of the Mono-color filter.

    @param session
    Handle to a valid session.

    @param preserveColor
	Parameter that specifies which color that should be preserved.

    @param colorDistance
	Specifies the tolerance level of the effect. If the colorDistance is
	small, only a small variation around the color defined with preserveColor
	will be preserved. Must be in the range 0 < colorDistance <=255.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7
*/
SCBIMPORT CRESULT caps_setMonoColor( CTSession session, CTColor preserveColor,
						   CTuint32 colorDistance );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.7
*/
SCBIMPORT void caps_endMonoColor( CTSession session );
/** @} */
// end 'MonoColor'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_colorswap Color Swap
    @{
        @copydoc begin_end_effects
*/

/**
    @brief
    Adjusts the parameters of the Color-swap filter.

    @param session
    Handle to a valid session.

    @param srcColor
	Parameter that specifies which color that should be converted.

    @param swapColor
	Parameter that specifies which color srcColor should be converted to.

    @param colorDistance
	Specifies the tolerance level of the effect. If the colorDistance is
	small, only a small variation around the color defined with srcColor
	will be converted to swapColor. Must be in the range 0 < colorDistance
    <=255.

	@param doMonoColor
	Specifies if the other colors should be converted to grayscale or be
	preserved.

    @param swapLuminance
    Parameter to control if the luminance should be included in the color swap.
    If swapLuminance is set to false only the color components will be swapped,
    not the luminance.
    If swapLuminance is set to true the source color and the range specified
    with colorDistance will be transformed exact the color specified with
    swapColor. Recommended value for best photorealistic results is to set
    swapLuminance to false.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7 (Backported to 3.6.1)
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT caps_beginColorSwap( CTSession session, CTColor srcColor,
                                       CTColor swapColor, CTuint32 colorDistance,
                                       CTbool doMonoColor, CTbool swapLuminance );

//-----------------------------------------------------------------------------
/**
    @brief
    Adjusts the parameters of the Color-swap filter.

    @param session
    Handle to a valid session.

    @param srcColor
	Parameter that specifies which color that should be converted.

    @param swapColor
	Parameter that specifies which color srcColor should be converted to.

    @param colorDistance
	Specifies the tolerance level of the effect. If the colorDistance is
	small, only a small variation around the color defined with srcColor
	will be converted to swapColor. Must be in the range 0 < colorDistance
    <=255.

    @param doMonoColor
    Specifies if the other colors should be converted to grayscale or be
    preserved.

    @param swapLuminance
    Parameter to control if the luminance should be included in the color swap.
    If swapLuminance is set to false only the color components will be swapped,
    not the luminance.
    If swapLuminance is set to true the source color and the range specified
    with colorDistance will be transformed exact the color specified with
    swapColor. Recommended value for best photorealistic results is to set
    swapLuminance to false.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @remarks

    @copydoc begin_end_effects

    @since 3.7
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT caps_setColorSwap( CTSession session, CTColor srcColor,
                                     CTColor swapColor, CTuint32 colorDistance,
                                     CTbool doMonoColor, CTbool swapLuminance );

//-----------------------------------------------------------------------------
/**
    @brief

    @param session
    Handle to a valid session.

    @remarks

    @copydoc begin_end_effects

    @since 3.7
*/
//-----------------------------------------------------------------------------
SCBIMPORT void caps_endColorSwap( CTSession session );
/** @} */
// end 'ColorSwap'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_cartoon Cartoon
    @{
        @copydoc begin_end_effects
*/

/**
    @brief

    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginCartoon( CTSession session );
//.............................................................................
/**
    @brief
    Transforms the current session image to typical cartoon graphics style.

    @param session
    Handle to a valid session.

    @param distinct_edges
    If set to @a true all detected edges in the image are rendered
    distinctively, if @c false edges are ignored.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setCartoon( CTSession session, CTbool distinct_edges );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endCartoon( CTSession session );
/** @} */
// end 'Cartoon'

//-----------------------------------------------------------------------------

/** @defgroup fx_magicpen Magic Pen */
/**
    @ingroup fx_magicpen

    @brief
    Applies a mix of edge distinction and color manipulation of the image.

    @param session
    A valid session handle.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyMagicPen( CTSession session  );

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_warp Warp
    @{
*/

/**
    The handle type used for warp effect sessions.
*/
typedef struct caps_warparea* CAPS_WARPAREA;

/**
    Warp effects
*/
enum CAPS_WARP_EFFECT
{
    CAPS_WARP_UPNOSE      =  0,  ///< Upnose       
    CAPS_WARP_TWISTER     =  1,  ///< Twister      
    CAPS_WARP_SMALLNOSE   =  2,  ///< Small Nose   
    CAPS_WARP_WIDESMILE   =  3,  ///< Wide Smile   
    CAPS_WARP_GRIT        =  4,  ///< Grit         
    CAPS_WARP_BIGFACE     =  5,  ///< Big Face     
    CAPS_WARP_PROFESSOR   =  6,  ///< Professor    
    CAPS_WARP_ALIEN       =  7,  ///< Alien        
    CAPS_WARP_BIGNOSE     =  8,  ///< Big Nose     
    CAPS_WARP_ALIENHYBRID =  9,  ///< Alien Hybrid 
    CAPS_WARP_GOBBLER     = 10,  ///< Gobbler      
    CAPS_WARP_SQUARE      = 11,  ///< Square       
    CAPS_WARP_SHARPCHIN   = 12,  ///< Sharpchin    
    CAPS_WARP_LONGFACED   = 13,  ///< Long-faced   
    CAPS_WARP_HAPPYFOOL   = 14,  ///< Happy fool   
    CAPS_WARP_INSECT      = 15   ///< Insect       
};

//-----------------------------------------------------------------------------
/**
    @brief
    Warp effect on selected areas in a session.

    After this function, the default warp effect, of index 0, is applied.

    @param session 
    A valid session handle.

    @param pRects Array of rectangles where warp is applied. 
    The array is copied, so this object does not need to be kept alive during
    the out_warp session. Rectangles that are outside of the session's
    current image size will be cropped to the valid area.
    There must be at least one rectangle in the array.

    @param numRects Number of rectangles in array, minimum 1.

    @param out_warp A handle for the warp session

    @copydoc begin_end_effects

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.2
*/
SCBIMPORT CRESULT caps_beginWarpArea(CTSession session,
                                     const CTRect *pRects,
                                     CTuint32 numRects,
                                     CAPS_WARPAREA* out_warp);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets the warp effect to apply

    @param warp
    [IN]A valid warp handle which has been created in a previous call to 
    caps_beginWarpArea().

    @param index
    [IN] A number between 0 and 15 which defines which warp to
    use on the rectangles. The available index values are defined in
    #CAPS_WARP_EFFECT

    @param strength Amount of effect applied. 0.0f means no effect. 1.0f means
    full effect.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.2
*/
SCBIMPORT CRESULT caps_setWarpAreaIndex(CAPS_WARPAREA warp,
                                        CTint32 index,
                                        CTfloat strength);

//-----------------------------------------------------------------------------
/**
    @brief

    @param session
    Handle to a valid session.

    @remarks
    This function has the same effect as caps_endWarpAreaEx()

    @copydoc begin_end_effects

    @since 5.2
*/
SCBIMPORT void caps_endWarpArea( CTSession session );

//-----------------------------------------------------------------------------
/**
    @brief

    @param warp
    Handle to a valid warp area.

    @remarks
    This function has the same effect as caps_endWarpArea()

    @copydoc begin_end_effects

    @since 5.2
*/
SCBIMPORT void caps_endWarpAreaEx( CAPS_WARPAREA warp );

//----------------------------------------------------------------------------
/**
    @brief
    Applies a warp effect to the current session image.

    @param session
    A valid session handle.

    @param filename
    Filename specifying the warp table file to use when applying the warp
    effect.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyWarpFromFile( CTSession session, const DCHAR* filename  );

//.............................................................................
/**
    @brief
    Applies a warp effect to the current session image.

    @param session
    A valid session handle.

    @param wrptable
    Buffer containing the warptable to apply.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_applyWarpFromBuffer( CTSession session, const CTBuffer* wrptable );
/** @} */
// end 'Warp'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_lomo Lomo
    @{
        @copydoc begin_end_effects
*/

/**
    @brief Defines the vignetting impact levels to use with caps_setLomo()
*/
typedef enum
{
    LOMO_VIGNETTING_LOW,     ///< The vignetting is low
    LOMO_VIGNETTING_MEDIUM,  ///< The vignetting is medium
    LOMO_VIGNETTING_HIGH     ///< The vignetting is high
} CAPS_LOMO_VIGNETTING;
//.............................................................................
/**
    @brief Defines the color styles to use with caps_setLomo()
*/
typedef enum
{
    LOMO_STYLE_NEUTRAL,     ///< The image is neutral
    LOMO_STYLE_RED,         ///< The image gets a red tone
    LOMO_STYLE_GREEN,       ///< The image gets a green tone
    LOMO_STYLE_BLUE,        ///< The image gets a blue tone
    LOMO_STYLE_YELLOW       ///< The image gets a yellow tone
} CAPS_LOMO_STYLE;
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
SCBIMPORT CRESULT caps_beginLomo( CTSession session );
//.............................................................................
/**
    @brief
    Applies lomo effect on the current session image.

    @param session
    Handle to a valid session.

    @param brightness
    Adjust the brightness of the image. Range (0.0) - (1.0),
    where 0.0 gives a bright image and 1.0 a dark image.

    @param saturation
    Adjust the color saturation of the image. Range (0.0) - (1.0),
    where 0.0 implies no saturation.

    @param vignetting
    Adjust the vignetting level. Can be one of the values from the
    @c ::CAPS_LOMO_VIGNETTING enumeration.

    @param style
    Change color style. Can be one of the values from the
    @c ::CAPS_LOMO_STYLE enumeration.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
SCBIMPORT CRESULT caps_setLomo( CTSession session,
                                CTfloat brightness,
                                CTfloat saturation,
                                CAPS_LOMO_VIGNETTING vignetting,
                                CAPS_LOMO_STYLE style );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.8
*/
SCBIMPORT void caps_endLomo( CTSession session );
/** @} */
// 'Lomo'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_vignetting Vignetting
    @{
        @copydoc begin_end_effects
*/

//.............................................................................
/**
    @brief
    Begins the task of applying vignetting effect to the current session image.

    @param session
    Handle to a valid session.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9 R01
*/
SCBIMPORT CRESULT caps_beginVignetting( CTSession session );
//.............................................................................
/**
    @brief
    Sets working parameters for the vignetting effect being applied.

    @param session
    Handle to a valid session.

    @param region
    A CTRect defining where the vignetting should be applied. The transition area
    will start outside the ellipse that can be inscribed inside this region.
    The CTRect::x and CTRect::y members specifies the offset in pixels of
    the region's top left corner, seen from the top left corner of the image.
    The CTRect::w and CTRect::h members specifies the size of the region in
    pixels. Coordinates should be given using current coordinates.
    The region has the following restrictions:
    - region.x and region.y must be located inside the image
    - region.h >= 10% of the image height
    - region.h < 131070/(transitionSize + 1)
    - region.w >= 10% of image width
    - region.w <= 20 * region.h
    - region.w < 131070/(transitionSize + 1)
    .

    @param transitionSize
    The size of the transition region given in fraction of the radius.
    Range: [0.0, 15.0]

    @param color
    The color to use for the vignetting effect.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9 R01
*/
SCBIMPORT CRESULT caps_setVignetting( CTSession session,
                                      CTRect region,
                                      CTfloat transitionSize,
                                      CTColor color );
//.............................................................................
/**
    @brief
    Ends the task of applying vignetting effect to the current session image.

    @param session
    Handle to a valid session.

    @since 3.9 R01
*/
SCBIMPORT void caps_endVignetting( CTSession session );
/** @} */
// 'Vignetting'

//-----------------------------------------------------------------------------


/**
    @defgroup fxgroup_watercolor Watercolor
    @{
        @copydoc begin_end_effects
*/
//-----------------------------------------------------------------------------
/**
    @param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/
SCBIMPORT CRESULT caps_beginWatercolor( CTSession session );
//.............................................................................
/**
    @brief
    Adjusts the light and color intensity of the watercolor effect.

    @param session
    Handle to a valid session.

    @param light
    A @c CTfloat specifying the light intensity.
    Range (0.0) - (1.0).

    @param color
    A @c CTfloat specifying the color intenisy.
    Range (0.0) - (1.0).

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/
SCBIMPORT CRESULT caps_setWatercolor( CTSession session,
                                      CTfloat light,
                                      CTfloat color );
//.............................................................................
/**
    @param session
    Handle to a valid session.

    @since 3.9
*/
//.............................................................................
SCBIMPORT void caps_endWatercolor( CTSession session );
/** @} */
// end 'Watercolor'
//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_splittoning SplitToning
    @{
        @copydoc begin_end_effects
*/
//-----------------------------------------------------------------------------
/**
    @brief Defines a split toning luminance interval, and a color value (RGB)
    to be applied.

    Used with caps_setSplitToning().
*/
typedef struct CTSplitToneRange
{
    /**
        @brief Defines the lower luminance value.
        Allowed range is [ 0, 255 ]. Must be lower than @c luminanceHighValue.
    */
 	CTuint32 luminanceLowValue;

    /**
        @brief Defines the higher luminance value.
        Allowed range is [ 0, 255 ]. Must be higher than @c luminanceLowValue.
    */
	CTuint32 luminanceHighValue;

    /**
        @brief Defines the R value of the RGB color to be set for the luminance
        range: [ @c luminanceLowValue, @c luminanceHighValue ].
        Allowed @c rValue range: [ 0, 255 ]. */
	CTuint32 rValue;

    /**
        @brief Defines the G value of the RGB color to be set for the luminance range:
        [ @c luminanceLowValue, @c luminanceHighValue ].
        Allowed @c gValue range: [ 0, 255 ]. */
	CTuint32 gValue;

    /**
        @brief Defines the B value of the RGB color to be set for the luminance range:
        [ @c luminanceLowValue, @c luminanceHighValue ].
        Allowed @c bValue range: [ 0, 255 ]. */
    CTuint32 bValue;

}CTSplitToneRange;

//-----------------------------------------------------------------------------
/**
    @brief
	This function connects a SplitToning effect to the current session.

	@param session
    Handle to a valid session.

	@return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/

SCBIMPORT CRESULT caps_beginSplitToning( CTSession session );

//.............................................................................
/**
    @brief
    Sets one, or more, luminance ranges with specific colors for the SplitToning filter.

	The SplitToning effect applies a given color to pixels with luminance values within an
    interval specified by a @c CTSplitToneRange struct. Several different intervals may be
    specified, each with a different color associated to it.

    Typical usage is to define a @em shadow luminance range, and a @em highlight luminance
    range, with different colors applied to each range.

	@param session
    Handle to a valid session.

    @param pSplitRange
    Array of @c CTSplitToneRange settings.

    @param splitRangeSize
    Number of elements in the @c pSplitRange array.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/
SCBIMPORT CRESULT caps_setSplitToning( CTSession session, CTSplitToneRange *pSplitRange, CTuint32 splitRangeSize );

//.............................................................................
/**
    @brief
	Disconnects the SplitToning filter from current session and frees memory from SplitToning parameters.

	@param session
    Handle to a valid session.

    @since 3.9
*/
SCBIMPORT void caps_endSplitToning( CTSession session );

/** @} */
// end 'SplitToning'
//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_brightness_n_contrast Brightness and Contrast 
    @{
        @copydoc begin_end_effects
*/

/**
    @brief
    Begins the task of applying Brightness and Contrast effect to the current 
    session image.

    @param session
    Handle to a valid session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT caps_beginBrightnessNContrast(CTSession session);

//.............................................................................

/**
    @brief
    Adjusts the brightness level of the current session image.

    @param session
    Handle to a valid session.

    @param brightness
    A @c CTfloat specifying the brightness modification level. 
    Range (-1.0) - (1.0), where 0.0 implies no adjustment.   

    @param contrast
    The contrast adjustment level. Range (-1.0) - (1.0), where values below
    zero decreases contrast and above zero increases it.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT caps_setBrightnessNContrast(CTSession session,
                                              CTfloat brightness,
                                              CTfloat contrast);

//.............................................................................

/**
    @brief
    Ends the task of applying Brightness and Contrast effect to the current 
    session image.

    @param session
    Handle to a valid session.

    @since 5.3
*/

SCBIMPORT void caps_endBrightnessNContrast(CTSession session);
/** @} */
// end 'Brightness and Contrast'
//-----------------------------------------------------------------------------


/**
    @}
*/
// end 'fm_photoart'
//=============================================================================


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_PHOTOART_PACK2_H )
