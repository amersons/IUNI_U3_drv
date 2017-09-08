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

#ifndef FM_PHOTOART_PACK1_H
#define FM_PHOTOART_PACK1_H
 
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/** 
    @ingroup fm_photoart
    @file fm_photoart_pack1.h
    @brief Defines the available API's for filters included in filter pack 1 
    for the Caps Feature Module: @a PhotoArt
*/
//=============================================================================
/**
    @addtogroup fm_photoart
    @{
*/

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_brightness Brightness 
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
SCBIMPORT CRESULT caps_beginBrightness( CTSession session );

//.............................................................................
/**
    @brief
    Adjusts the brightness level of the current session image.

    @param session
    Handle to a valid session.

    @param brightness
    A @c CTfloat specifying the brightness modification level. 
    Range (-1.0) - (1.0), where 0.0 implies no adjustment.   

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setBrightness( CTSession session, CTfloat brightness );

//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endBrightness( CTSession session );
/** @} */
// 'Brightness'

/**
    @defgroup fxgroup_huesaturation HueSaturation 
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

    @since 3.8
*/
SCBIMPORT CRESULT caps_beginHueSaturation( CTSession session );

//.............................................................................
/**
    @brief
    Adjusts the Hue and Saturation level of the current session image.

    @param session
    Handle to a valid session.

    @param hue
    A @c CTuint32 specifying the Hue modification level. 
    Range 0 - 255, where 128 implies no adjustment.   

    @param saturation
    A @c CTuint32 specifying the Saturation modification level. 
    Range 0 - 255, where 128 implies no adjustment.   

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
SCBIMPORT CRESULT caps_setHueSaturation( CTSession session, 
                                         CTuint32 hue, 
                                         CTuint32 saturation );

//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.8
*/
SCBIMPORT void caps_endHueSaturation( CTSession session );
/** @} */
// 'HueSaturation'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_sharpen Sharpen 
    @{
        @copydoc begin_end_effects
*/

/** 
    Defines the sharpness impact levels to use with caps_setSharpness().
*/
typedef enum 
{
    SHARPNESS_LEVEL_NONE = 0, ///< Sharpness disabled
    SHARPNESS_LEVEL_1,        ///< Level 1 sharpness
    SHARPNESS_LEVEL_2,        ///< Level 2 sharpness
    SHARPNESS_LEVEL_3,        ///< Level 3 sharpness
    SHARPNESS_LEVEL_4,        ///< Level 4 sharpness
    SHARPNESS_LEVEL_5,        ///< Level 5 sharpness  
    SHARPNESS_LEVEL_6,        ///< Level 6 sharpness 
    SHARPNESS_LEVEL_7         ///< Level 7 sharpness
} CAPS_SHARPNESS_LEVEL;

//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginSharpness( CTSession session );

//.............................................................................
/**
    @brief
    Applies sharpness to the current session image.

    @param session
    Handle to a valid session.

    @param sharp_level
    The sharpness impact level. Can be one of the values from the 
    @c ::CAPS_SHARPNESS_LEVEL enumeration.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setSharpness( CTSession session, CAPS_SHARPNESS_LEVEL sharp_level);

//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endSharpness( CTSession session );
/** @} */
// 'Sharpen'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_rotation Rotation
    @{
        @copydoc begin_end_effects
*/
/** @brief Scaling behavior */
typedef enum 
{
    SCALE_IGNORE = 0,
    SCALE_FIT_INSIDE,
    SCALE_FIT_OUTSIDE

} CAPS_ROTATION_SCALE_MODE;
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginRotation( CTSession session );

//.............................................................................
/**
    @brief
    Arbitrary rotation on the current session image.

    @param session
    Handle to a valid session.

    @param angle
    Range: [0.0 360.0]

    @param scale_mode 
	Can be any of the values 
    from the @c ::CAPS_ROTATION_SCALE_MODE enumeration.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setRotation( CTSession session, CTfloat angle,
                          CAPS_ROTATION_SCALE_MODE scale_mode );

//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endRotation( CTSession session );
/** @} */
// end 'Rotation'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_contrast Contrast
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
SCBIMPORT CRESULT caps_beginContrast( CTSession session );
//.............................................................................
/**
    @brief
    Applies contrast adjustment to the current session image.

    @param session
    Handle to a valid session.

    @param contrast
    The contrast adjustment level. Range (-1.0) - (1.0), where values below
    zero decreases contrast and above zero increases it.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setContrast( CTSession session, CTfloat contrast );
//.............................................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endContrast( CTSession session );
/** @} */
// end 'Contrast'

//-----------------------------------------------------------------------------

/**
    @defgroup fxgroup_sepia Sepia
    @{
        @copydoc begin_end_effects
*/

/** @brief Defines the sepia levels to use with caps_applySepia().*/
typedef enum
{
    SEPIA_MINIMUM = 1,  ///< Minimum
    SEPIA_LOW,          ///< Low
    SEPIA_MEDIUM,       ///< Medium
    SEPIA_HIGH,         ///< High
    SEPIA_MAX           ///< Max

} CAPS_SEPIA_LEVEL;
//.............................................................................
/**
    @brief
	Applies a sepia effect to the current session image.

    @param session
    Handle to a valid session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.5
*/
SCBIMPORT CRESULT caps_beginSepia( CTSession session );

//.............................................................................
/**
    @brief	

    @param session
    Handle to a valid session.

    @param sepia_level
    The level of sepia. Can be one of the values from the 
    @c ::CAPS_SEPIA_LEVEL enumeration.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.5
*/
SCBIMPORT CRESULT caps_setSepia( CTSession session, CAPS_SEPIA_LEVEL sepia_level);

//.............................................................................
/**
    @brief	

    @param session
    Handle to a valid session.

    @since 3.5
*/
SCBIMPORT void caps_endSepia( CTSession session );
/** @} */
// end 'Sepia'.

//-----------------------------------------------------------------------------

/**
    @brief
    Applies a sepia effect to the current session image.

    @param session 
    A valid session handle.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applySepia( CTSession session );

//-----------------------------------------------------------------------------

/** @defgroup fx_grayscale Grayscale */
/**
    @ingroup fx_grayscale

    @brief
    Converts the current session image to grayscale.

    @param session 
    A valid session handle.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyGrayscale( CTSession session );

//-----------------------------------------------------------------------------

/** @defgroup fx_negative Negative */
/**
    @ingroup fx_negative

    @brief
    Converts the current session image to negative.
    
    @param session 
    A valid session handle.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyNegative( CTSession session );

//-----------------------------------------------------------------------------

/** @defgroup fx_grayscale_negative Grayscale Negative */
/**
    @ingroup fx_grayscale_negative

    @brief
    Converts the current session image to combined grayscale and negative.
    
    @param session 
    A valid session handle.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyGrayscaleNegative( CTSession session );

//-----------------------------------------------------------------------------

/** @defgroup fx_paint Paint 
    @{
        @copydoc begin_end_effects
*/

/**
    @brief
	Begins the task of applying the Paint effect to the current session image.

    @param session
    Handle to a valid session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.10
*/
SCBIMPORT CRESULT caps_beginPaint( CTSession session );

//.............................................................................
/**
    @brief
    Applies Paint effect to the current session image.

    @param session
    Handle to a valid session.

    @param paintLevel
    The level of the paint effect. Range [1, 4]

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.10
*/
SCBIMPORT CRESULT caps_setPaint( CTSession session, CTuint32 paintLevel);

//.............................................................................
/**
    @brief	
    Ends the task of applying the Paint effect to the current session image.

    @param session
    Handle to a valid session.

    @since 3.10
*/
SCBIMPORT void caps_endPaint( CTSession session );

/**
    @brief
    Applies a painted effect on the current session image.

    @param session 
    A valid session handle.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyPaint( CTSession session );

/** @} */
// end defgroup 'fx_paint'

//-----------------------------------------------------------------------------

/** @defgroup fx_mirror Mirror */
/**
    @ingroup fx_mirror

    @brief
    Applies a mirror effect on the current session image.

    @param session 
    A valid session handle.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyMirror( CTSession session );

//-----------------------------------------------------------------------------

/**
    @}
*/
// end 'fm_photoart'
//=============================================================================


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_PHOTOART_PACK1_H )
