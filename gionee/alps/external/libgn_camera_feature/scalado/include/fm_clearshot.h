/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    � 2000-2010 Scalado AB. All rights reserved.                             .
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

#ifndef FM_CLEARSHOT_H
#define FM_CLEARSHOT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/**
    @ingroup fm_clearshot
    @file fm_clearshot.h
    @brief Defines the interface of the Caps Feature Module: @a ClearShot
*/
//=============================================================================
/**
    @addtogroup fm_clearshot
    @brief Image enhancing effects
    @{
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
    @defgroup fxgroup_local_boost Local Boost
    @copydoc begin_end_effects
    @{
*/

/**
    @brief
    Automatically boost and enhance images with unequal illumination.
    
    The image is analyzed and segmented into a dark part and a light part.
    The two parts are processed separatly with the parameters given in
    caps_setLocalBoost() and are finally blended together to produce a
    modified image.

    @param session
    A valid session handle.   

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @remarks
    This function should not be used together with the deprecated caps_applyLocalBoost().

    @sa 
    caps_setLocalBoost()\n
    caps_endLocalBoost()\n

    @since 3.6
*/
SCBIMPORT CRESULT caps_beginLocalBoost(CTSession session);

//.........................................................

/**
    @brief
    Automatically boost and enhance images with unequal illumination.
    
    This function can operate in two modes; manual or automatic. In manual mode,
    the user specifies and adjusts the values of gamma, darkContrast,
    lightContrast and sensitivityLevel to reach a satisfactory result. In
    automatic mode, the autoLevel parameter maps the manual parameters in
    a range [0-14]. NOTE: The behavior and range of the automatic mode may
    change in later versions.

    @param session
    A valid session handle.

    @param gamma [In/Optional]
    Gamma correction for the dark part of the image.\n
    Must be NULL if automatic mode is used.\n
    Range: [0.1 <= gamma < 5.0]\n
    Recommended default value: 1.9\n

    @param darkContrast [In/Optional]
    Contrast amplification of the dark part.\n
    Must be NULL if automatic mode is used.\n
    Range: [0.5 <= darkContrast < 1.0]\n
    Recommended default value: 0.625\n
    
    @param lightContrast [In/Optional]
    Contrast amplification of the light part.\n
    Must be NULL if automatic mode is used.\n
    Range: [0.5 <= lightContrast < 1.0]\n
    Recommended default value: 0.5\n

    @param sensitivityLevel [In/Optional]
    Specifies how much of the processed image that will be blended in the original image.\n 
    If sensitivityLevel equals 0, the result will be 100% of the orignal 
    image and 0% of the processed image.\n
    If sensitivityLevel equals 256, the result will be 0% of the original 
    image and 100% of the processed image.\n
    Must be NULL if automatic mode is used.\n
    Range: [0.0 <= sensitivityLevel <= 256.0]\n
    Recommended default value: 256.0\n

    @param autoLevel [In/Optional]
    Must be NULL if manual mode is used.\n
    Range: [0 <= autoLevel <= 14]\n
    Recommended default value: 8\n

    @return 
    @c CERR_OK if successful or a specific error code upon failure.
    
    @sa 
    caps_beginLocalBoost()\n
    caps_endLocalBoost()\n

    @since 3.6
*/
SCBIMPORT CRESULT caps_setLocalBoost( CTSession session, CTfloat* gamma,
                                               CTfloat* darkContrast,
                                               CTfloat* lightContrast,
                                               CTfloat* sensitivityLevel,
                                               CTint32* autoLevel);

//.........................................................

/**
    @brief
    Ends the LocalBoost effect.

    @param session 
    A valid session handle.   

    @return 
    None

    @sa 
    caps_beginLocalBoost()\n
    caps_setLocalBoost()\n

    @since 3.6
*/
SCBIMPORT void caps_endLocalBoost( CTSession session );
/** @} */
// end 'Local Boost'
//cxm_node_end

//-----------------------------------------------------------------------------

//cxm_node[Color Boost]
/**
    @defgroup fxgroup_color_boost Color Boost 
    @copydoc begin_end_effects
    @{
*/
//.........................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginColorBoost( CTSession session );

//.........................................................

/**
    @brief
    Amplifies the colors of the current session image.

    @param session
    Handle to a valid session.

    @param gain
    The color boost gain level. Range [-1.0, 20.0]. Negative values reduce the 
    colors. Recommended values are in the range [-1.0, 1.0].

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setColorBoost( CTSession session, CTfloat gain );

//.........................................................

/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endColorBoost( CTSession session );
/** @} */
// end 'Color Boost'
//cxm_node_end

//-----------------------------------------------------------------------------

//cxm_node[WhiteBalance]
/**
    @defgroup fxgroup_white_balance White Balance 
    @{
*/
//.........................................................

/** @brief Defines the white balance modes to use with caps_applyWhiteBalance(). */
typedef enum 
{
    /** Uses the estimated mean gray for the color correction.*/
    WB_MEAN_MODE = 1,
    /** Uses the estimated maximum intensity color.*/
    WB_MAX_MODE,
    /** Uses a white reference color.*/
    WB_MANUAL_MODE,
    /** Calulates the reference from the mean value of the 256-bin distribution.*/
    WB_CLUSTER_MODE

} CAPS_WB_MODE;

//.........................................................

/**
    @brief
    Performs white balance adjustment on an image.

    @param session 
    A valid session handle.   

    @param mode
    The white balance mode, can be any of the values from the @c ::CAPS_WB_MODE
    enumeration. WB_CLUSTER_MODE is prefered as default.

    @param r
    Red component of the white color used for reference 
    This requires that @c mode is set to @c WB_MANUAL_MODE, neglected otherwise.

    @param g
    Green component of the white color used for reference
    This requires that @c mode is set to @c WB_MANUAL_MODE, neglected otherwise.

    @param b
    Blue component of the white color used for reference
    This requires that @c mode is set to @c WB_MANUAL_MODE, neglected otherwise.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.


    @since 3.1
*/
SCBIMPORT CRESULT caps_applyWhiteBalance( CTSession session, 
                                CAPS_WB_MODE mode, 
                                CTuint8 r, 
                                CTuint8 g, 
                                CTuint8 b );

/** @} */
// end 'White Balance'
//cxm_node_end

//-----------------------------------------------------------------------------

//cxm_node[Levels]
/**
    @defgroup fxgroup_levels Levels 
    @copydoc begin_end_effects
    @{
*/
//.........................................................
/**
    @brief

    @param session
    Handle to a valid session.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4
*/
SCBIMPORT CRESULT caps_beginLevels( CTSession session );

//.........................................................

/**
    @brief
    Applies level adjustment to the current session image.

    @param session
    Handle to a valid session.

    @param white
    The position of the bright saturating point. Range (0.0) - (1.0).

    @param gray
    The relative position of the middle gray point. Range (0.0) - (1.0),
    where 0.0 is at the bright saturating point and 1.0 is at
    the dark saturating point.

    @param black
    The position of the dark saturating point. Range (0.0) - (1.0).

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @remarks
    The value of 'black' should be smaller than, or equal to
    the value of 'white'.

    @since 3.4
*/
SCBIMPORT CRESULT caps_setLevels( CTSession session, CTfloat white,
                        CTfloat gray, CTfloat black );

//.........................................................

/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.4
*/
SCBIMPORT void caps_endLevels( CTSession session );

//.........................................................

/**
    @brief
    Applies auto level adjustment to the current session image.
    
    @param session 
    A valid session handle.

    @remarks
    Auto level adjustment balances the intensity level of the image, for
    example making dark images lighter and vice versa.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_applyAutoLevels( CTSession session );
/** @} */
// end 'Levels'
//cxm_node_end

//-----------------------------------------------------------------------------

//cxm_node[Exposure]
/**
	@defgroup fxgroup_exposure Exposure 
    @copydoc begin_end_effects
	@{
*/
//.........................................................

/** @brief Defines the exposure modes to use with caps_setExposureMode(). */
typedef enum 
{
    /** @brief
        Adjust the brightness of an image using a gamma correction curve. */
    EXPOSURE_GAMMA_MODE = 1,
    
    /** @brief
        Adjust the brightness of an image using a "natural" curve inspired
        by a @em film @em characteristic @em curve. This mode preserves
        the blacks in an image much better than the gamma mode. */
    EXPOSURE_NATURAL_MODE
    
} CAPS_EXPOSURE_MODE;

//.........................................................
/**
    @brief
    Adjust the brightness of an image using one of the modes in
    @c ::CAPS_EXPOSURE_MODE. The default mode is EXPOSURE_GAMMA_MODE.

    @param session
    Handle to a valid session.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4
*/
SCBIMPORT CRESULT caps_beginExposure( CTSession session );

//.........................................................

/**
    @brief
    Set the desired exposure level. Positive values will make the image
    brighter, negative values will make it darker.

    @param session
    Handle to a valid session.

    @param gain
    The exposure level. Range is [ -1.0, 1.5 ], but for gamma mode the 
    effect saturates at 1.0, which means that everything between ]1.0, 1.5]
    will be intrepreted as 1.0. 
    0.0 equals no change of exposure. Recommended range for both gamma and 
    natural mode for normal usage is [ -1.0, 1.0 ].

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4
*/
SCBIMPORT CRESULT caps_setExposure( CTSession session, CTfloat gain );

//.........................................................

/**
    @brief
    Select which exposure mode to be used, @c ::CAPS_EXPOSURE_MODE.
    Default mode is EXPOSURE_GAMMA_MODE.
 
    @param session
    Handle to a valid session.
 
    @param mode
    The exposure mode.
 
    @return 
    @c CERR_OK if successful or a specific error code upon failure.
 
    @since 3.9 R01
 */
SCBIMPORT CRESULT caps_setExposureMode( CTSession session,
                                        CAPS_EXPOSURE_MODE mode );

//.........................................................
    
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.4
*/
SCBIMPORT void caps_endExposure( CTSession session );
/** @} */
// end 'Exposure'
//cxm_node_end

//-----------------------------------------------------------------------------

//cxm_node[AutoEnhance]
/**
    @defgroup fxgroup_autoenhance AutoEnhance

    AutoEnhance can be used to correct images that have been taken in poor
    lighting conditions. One or more of the following adjustements can be made
    simultaneously:
    - White balance
    - Contrast
    - Local boost
    .

    Suitable parameters for each effect can be set manually, or estimated and
    set automatically (see ::AutoEnhanceParameters). When used in automatic
    mode, parameter estimation will be performed (and applied) in the next
    render operation.

    @copydoc begin_end_effects
    @{
*/
//.........................................................
/**
    @brief Parameters defining the behaviour of the auto enhance effect.

    Note that when an @em auto<EffectName> flag is set to @c true,
    values that are associated the given effect will be estimated
    automatically. In this case, any manually set values, associated with the given
    effect, will be ignored.
*/
typedef struct
{
    /** @name White balance: */
    //@{
    /** @brief If true, white balance is applied. */
    CTbool  applyWhiteBalance;

    /** @brief If true, white balance will try to find the white point in the source.
        If false, the provided white point (@c sourceWhite) will be used. */
    CTbool  autoSourceWhite;

    /** @brief The source white point. Used when autoSourceWhite is false.
        The luminance of the provided color is ignored, only the chrominance
        information is used.
    */
    CTColor sourceWhite;

    /** @brief The desired target white point. The luminance of the provided color
        is ignored, only the chrominance information is used. Must be specified when
        white balance is applied.*/
    CTColor targetWhite;
    //@}


    /** @name Contrast: */
    //@{
    /** @brief If true, contrast is applied. */
    CTbool  applyContrast;

    /** @brief If true, an automatic contrast enhancement is performed.
        If false, the @c contrast and @c brightness parameters are used. */
    CTbool  autoContrast;

    /** @brief Values greater then 0 will increase the contrast.
        Values less than 0 will decrease the contrast.
        contrast should be in the range [-1.0 1.0]. */
    CTfloat contrast;
    
    /** @brief Values greater then 0 will make the image brighter.
        Values less than 0 will make the image darker.
        brightness should be in the range [-1.0 1.0]. */
    CTfloat brightness;
    //@}


    /** @name Local boost: */
    //@{
    /** @brief If true, local boost is applied. */
    CTbool  applyLocalBoost;

    /** @brief If true, local boost will try to estimate the needed amount of boost
        and automatically set @c gamma, @c darkContrast, @c lightContrast and
        @c sensitivityLevel. */
    CTbool  autoLocalBoost;

    /** @brief The gamma correction applied to the dark areas in the image.
        Values greater than 1.0 gives a logarithmic response and will make
        these parts brighter. Values less than 1.0 gives an exponential
        response and will make these parts darker.
        gamma should be in the range [0.01 10.0]. */
    CTfloat gamma;

    /** @brief Contrast applied to the dark areas in the image.
        Values greater than 0.5 will increase the contrast. Values less
        than 0.5 will decrease the contrast. @c darkContrast should be
        in the range [0.0 0.99]. */
    CTfloat darkContrast;

    /** @brief Contrast applied to the bright areas in the image. Values greater
        than 0.5 will increase the contrast. Values less than 0.5 will
        decrease the contrast.
        lightContrast should be in the range [0.0 0.99]. */
    CTfloat lightContrast;

    /** @brief The amount of boost to apply. sensitivityLevel should be in
        the range [0.0 1.0] where 0.0 is no effect and 1.0 is
        full local boost. */
    CTfloat sensitivityLevel;
    //@}

    /* 
       Saturation enhancement, not yet implemented and thus invisible
       to doxygen.
    */
    CTbool  applySaturation;        // not yet implemented
    CTbool  autoSaturation;         // not yet implemented
    CTfloat gain;                   // not yet implemented

} AutoEnhanceParameters;

//.........................................................

/**
    @brief
    Starts an enhancement block on the current session image.

    @param session
    Handle to a valid session.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
*/
SCBIMPORT CRESULT caps_beginAutoEnhance( CTSession session );

//.........................................................

/**
    @brief
    Specifies the desired behaviour of the image enhancement.
    
    The following effects can be applied:
    - White balance
    - Contrast
    - Local boost
    .

    If more than one effect is set, they will be applied in the given order.

    The behaviour can be fully automatic, semi automatic or manual. It is
    possible to start with full automatic and switch over to semi automatic
    or manual. For a small example of this see caps_getAutoEnhance(). It is
    of course possible to switch back to fully automatic again if desired.

    @note In order to take effect, a render operation must be completed;
    see for example caps_render().

    @param session
    Handle to a valid session.

    @param parameters
    A pointer to a structure defining the desired behaviour.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
*/
SCBIMPORT CRESULT caps_setAutoEnhance( CTSession session,
                             const AutoEnhanceParameters* parameters );

//.........................................................

/**
    @brief
    Retrieves the auto enhance parameters used in the last rendering
    (only valid within the current @em begin - @em end block).
    
    Using this function an application can let the user start with a fully
    automatic enhancement and later switch over to manually adjust
    the enhancement parameters. E.g. after an automatic contrast adjustment
    a call to caps_getAutoEnhance() will retrieve the values of @c contrast
    and @c brightness found by the automatic contrast. Then set @c autoContrast
    to false, adjust @c contrast and @c brightness, call caps_setAutoEnhance()
    and render again.

    If an effect is set to be auto but not active, the effect will not try to
    estimate the parameters. E.g. if @c autoContrast = @c true and
    @c applyContrast=false then @c contrast and @c brightness will be left
    untouched.

    @param session
    Handle to a valid session.

    @param parameters
    A pointer to a structure retrieving the current behaviour.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    AutoEnhanceParameters auto_enhance;

    // Automatic white balance.
    auto_enhance.applyWhiteBalance = true;
    auto_enhance.autoSourceWhite = true;
    auto_enhance.targetWhite.r = 255;
    auto_enhance.targetWhite.g = 255;
    auto_enhance.targetWhite.b = 255;

    // Automatic contrast.
    auto_enhance.applyContrast = true;
    auto_enhance.autoContrast = true;

    // Manual local boost. Start with 0 boost.
    auto_enhance.applyLocalBoost = true;
    auto_enhance.autoLocalBoost = false;
    auto_enhance.gamma = 1.9f;
    auto_enhance.darkContrast = 0.625f;
    auto_enhance.lightContrast = 0.5f;
    auto_enhance.sensitivityLevel = 0.0f;

    // Start enhance block and set parameters.
    (void)caps_beginAutoEnhance(session);
    (void)caps_setAutoEnhance(session, &auto_enhance);

    //
    // Render...
    //

    // Get the updated parameters.
    (void)caps_getAutoEnhance(session, &auto_enhance);

    // Decrease the amount of contrast and switch to manual.
    auto_enhance.autoContrast = false;
    auto_enhance.contrast -= 0.1f;

    // Increase lokal boost.
    auto_enhance.sensitivityLevel += 0.3f;

    // Update the parameters.
    (void)caps_setAutoEnhance(session, &auto_enhance);

    //
    // Render ...
    //

    // End enhance block.
    caps_endAutoEnhance(session);

    //
    // Render ...
    //

    @endcode 

    @since 3.6
*/
SCBIMPORT CRESULT caps_getAutoEnhance( CTSession session,
                             AutoEnhanceParameters* parameters );

//.........................................................

/**
    @brief
    Ends an enhancement block on the current session image.

    @param session
    Handle to a valid session.

    @since 3.6
*/
SCBIMPORT void caps_endAutoEnhance( CTSession session );
/** @} */
// end 'AutoEnhance'
//cxm_node_end
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//cxm_node[TemperatureAndTint]
/**
    @defgroup fxgroup_temperatre_and_tint Temperature And Tint 
    @{
*/

//.........................................................

/**
    @brief Begin the Temperature and Tint effect.

    @param session
    Handle to a valid session.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9.2
*/
SCBIMPORT CRESULT caps_beginTemperatureAndTint( CTSession session );


/**
    @brief
    Set function to modify the color temperature and tint.

	@param session Handle to a valid session.

	@param temperatureIndex Color temperature index.
		Range [-100, 100], where 0 is default, unmodified color temperature.

	@param tintIndex Color tint index.
		Range [-100, 100], where 0 is the default, unmodified color tint. 

	@return 
    @c CERR_OK if successful or a specific error code upon failure.


    @since 3.9.2
*/
SCBIMPORT CRESULT 
caps_setTemperatureAndTint( CTSession session, 
                         CTint32 temperatureIndex, 
                         CTint32 tintIndex );

/**
    @brief
    End temperature and tint effect.

	@param session  Handle to a valid session.

    @since 3.9.2
*/
SCBIMPORT void caps_endTemperatureAndTint( CTSession session );

/** @} */
// end 'fxgroup_temperatre_and_tint'

/**
    @}
*/
// end 'fm_clearshot'
//=============================================================================


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_CLEARSHOT_H )
