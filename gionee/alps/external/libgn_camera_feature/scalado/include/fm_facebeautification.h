/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
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

#ifndef FM_FACEBEAUTIFICATION_H
#define FM_FACEBEAUTIFICATION_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/**
    @ingroup fm_facebeautification
    @file fm_facebeautification.h
    @brief Defines interfaces for the Caps Feature Module: @a FaceBeautification
*/
//=============================================================================
/**
    @addtogroup fm_facebeautification
    @brief Face beautification

    @{
*/

typedef struct CTFaceBeautification CTFaceBeautification;

/**
    @brief
    Rectangles specifying face features
*/
typedef struct CTFaceFeaturesRect
{
    CTRect faceRect;
    CTRect rightEye;
    CTRect leftEye;
}CTFaceFeaturesRect;


/**
    @brief
    Available face beautification types.

*/
typedef enum
{
    FB_SKIN_SMOOTHING = 1,
    FB_EYES_ENHANCEMENT = 2,
    FB_TEETH_WHITENING = 4,
    FB_SKIN_TONING  = 8,
    FB_EYES_ENLARGEMENT = 16

}FACEBEAUTIFICATION_CORRECTION_EFFECT_TYPE;

/**
    @brief
    Available skin smoothing effect types.

*/
typedef enum
{
    FB_SUBTLE = 1,       ///< Subtle correction removes the wrinkles and spots alone 
                         ///< while it keeps the texture of the face unchanged.
    FB_SKINSOFTENING     ///< Default level of correction. In this case the appearance of the entire skin 
                         ///< including wrinkles, spots and hot spots is changed (softened).           
    
} FACEBEAUTIFICATION_SKIN_SMOOTHING_TYPE;

/**
    @brief
    Available skin toning effect types.

*/
typedef enum
{
   FB_WHITE,  ///< Whitens (bleaches) face. Recommended mainly for darker skin.
   FB_PALE,   ///< Makes skin look lighter and more pale. 
   FB_WARM,   ///< Warms skin tone. 
   FB_TAN     ///< Darkens skin, makes it look naturally tanned.
    
} FACEBEAUTIFICATION_SKIN_TONING_TYPE;

/**
    @brief
    Available face beautification effect levels.

*/
typedef enum
{
    FB_LEVEL_SUBTLE = 1, ///< Subtle level.
    FB_LEVEL_STD,        ///< Standard level.
    FB_LEVEL_HIGH        ///< High intensity level.

} FACEBEAUTIFICATION_CORRECTION_LEVEL;


/**
    @brief
    Creates beautifier object with default configuration. Configuration can be changed thereafter.
    Following configuration is default one:
    
    Default applied correction effects: 
    FB_SKIN_SMOOTHING
    FB_EYES_ENHANCEMENT
    FB_TEETH_WHITENING
    FB_EYES_ENLARGEMENT

    Skin smoothing default configuration:
    Type = FB_SKINSOFTENING
    Level = FB_LEVEL_STD

    Skin toning default configuration (observe that effect is by default disabled):
    Type = FB_WARM
    Level = FB_LEVEL_SUBTLE

    Teeth whitening default configuration:
    Level = FB_LEVEL_HIGH

    Eyes enhancement default configuration:
    Level = FB_LEVEL_STD

    Eyes enlargement default configuration:
    Level = FB_LEVEL_SUBTLE


    @param[out] ppFaceBeautifier
    Created beautifier object.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_create(CTFaceBeautification **ppFaceBeautifier);


/**
    @brief
    Applies a beautifying effect on the current session image and renders it to
    output image. Provided beautifier object contains configurations that will be applied.
    Faces are automatically detected and selected configuration will be applied on all detected faces.
    Beautification is applied as best effort which means that some corrections might not be
    possible to apply due to different technical reasons or missing face features.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[in] session
    Handle to a valid session.

    @param[in] pImage
    Output image. For best memory and performance the image should have the
    same dimensions as the input session and color format CM_YUV422_Y1UY2V.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_renderToImage(CTFaceBeautification *pFaceBeautifier, CTSession session, CTImage* pImage);

/**
    @brief
    Applies a beautifying effect on the current session image and renders it to
    a jpeg stream. Provided beautifier object contains configurations that will be applied. 
    Faces are automatically detected and selected configuration will be applied on all detected faces.
    Beautification is applied as best effort which means that some corrections might not be
    possible to apply due to different technical reasons or missing face features.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[in] session
    Handle to a valid session.
    
    @param[in] pStream
    A stream where to write the image with the beautification effects added to it.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_renderToStream(CTFaceBeautification *pFaceBeautifier, CTSession session, CTStream* pStream);


/**
    @brief
    Applies a beautifying effect on the current session image within provided input face rectangles. Renders result to
    output image. Provided beautifier object contains configurations that will be applied.
    Beautification is applied as best effort which means that some corrections might not be
    possible to apply due to different technical reasons or missing face features. 
    Provided face features rectangles must be in session image current resolution format.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[in] session
    Handle to a valid session.

    @param[in] pFaceRectList
    Valid list of faces.

    @param[in] numberOfFaces
    Number of faces in face list.
    
    @param[in] pImage
    Output image. For best memory and performance the image should have the
    same dimensions as the input session and color format CM_YUV422_Y1UY2V.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_doBeautification(CTFaceBeautification *pFaceBeautifier, 
                                                        CTSession session, 
                                                        CTFaceFeaturesRect *pFaceRectList, 
                                                        CTuint32 numberOfFaces, 
                                                        CTImage* pImage);

/**
    @brief
    Inactivates one or several effects at the same time without changing effect configurations.
    If several effects are to be inactivated use | between effect type names. 
    See FACEBEAUTIFICATION_CORRECTION_EFFECT_TYPE enum for available effects.

    @param[in] pFaceBeautifier
    Valid beautifier object.
    
    @param[in] type
    Type of the effect(s) that are to be inactivated.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_inactivateCorrectionEffect(CTFaceBeautification *pFaceBeautifier,
                                                                  FACEBEAUTIFICATION_CORRECTION_EFFECT_TYPE type);

/**
    @brief
    Activates one or several effects at the same time without changing effect configurations. Effect configurations
    will be those last edited or if nothing was re-configured then default ones.
    To change effect configurations use "set" functions to do so. Set functions will also automatically enable desired effect.
    If several effects are to be activated use | between effect type names.
    See FACEBEAUTIFICATION_CORRECTION_EFFECT_TYPE enum for available effects.

    @param[in] pFaceBeautifier
    Valid beautifier object.
    
    @param[in] type
    Type of the effect(s) that are to be activated.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_activateCorrectionEffect(CTFaceBeautification *pFaceBeautifier,
                                                                FACEBEAUTIFICATION_CORRECTION_EFFECT_TYPE type);


/**
    @brief
    Destroys beautifier object.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @since 5.3
*/
SCBIMPORT void ctfacebeautification_destroy(CTFaceBeautification *pFaceBeautifier);


/**
    @brief
    Sets skin smoothing effect as active with provided configurations.

    @param[in] pFaceBeautifier
    Valid beautifier object.
    
    @param[in] type
    Skin smoothing type. See FACEBEAUTIFICATION_SKIN_SMOOTHING_TYPE for available types.

    @param[in] level
    Level of applied skin smoothing effect. See FACEBEAUTIFICATION_CORRECTION_LEVEL for available levels.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_setSkinSmoothing(CTFaceBeautification *pFaceBeautifier,
                                                        FACEBEAUTIFICATION_SKIN_SMOOTHING_TYPE type, 
                                                        FACEBEAUTIFICATION_CORRECTION_LEVEL level);



/**
    @brief
    Returns current skin smoothing effect configurations.

    @param[in] pFaceBeautifier
    Valid beautifier object.
    
    @param[out] pType
    Currently configured skin smoothing type.

    @param[out] pLevel
    Currently configured level of applied skin smoothing effect.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_getSkinSmoothingParameters(CTFaceBeautification *pFaceBeautifier,
                                                                  FACEBEAUTIFICATION_SKIN_SMOOTHING_TYPE *pType, 
                                                                  FACEBEAUTIFICATION_CORRECTION_LEVEL *pLevel);

/**
    @brief
    Sets skin toning effect as active with provided configurations.

    @param[in] pFaceBeautifier
    Valid beautifier object.
   
    @param[in] type
    Skin toning type. See FACEBEAUTIFICATION_SKIN_TONING_TYPE for available types.

    @param[in] level
    Level of applied skin toning effect. See FACEBEAUTIFICATION_CORRECTION_LEVEL for available levels.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_setSkinToning(CTFaceBeautification *pFaceBeautifier,
                                                     FACEBEAUTIFICATION_SKIN_TONING_TYPE type, 
                                                     FACEBEAUTIFICATION_CORRECTION_LEVEL level);

/**
    @brief
    Returns current skin toning effect configurations.

    @param[in] pFaceBeautifier
    Valid beautifier object.
    
    @param[out] pType
    Currently configured skin toning type.

    @param[out] pLevel
    Currently configured level of applied skin toning effect.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_getSkinToningParameters(CTFaceBeautification *pFaceBeautifier,
                                                               FACEBEAUTIFICATION_SKIN_TONING_TYPE *pType, 
                                                               FACEBEAUTIFICATION_CORRECTION_LEVEL *pLevel);

/**
    @brief
    Sets teeth whitening effect as active with whitening level.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[in] level
    Level of applied teeth whitening effect. See FACEBEAUTIFICATION_CORRECTION_LEVEL for available levels.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_setTeethWhitening(CTFaceBeautification *pFaceBeautifier,
                                                         FACEBEAUTIFICATION_CORRECTION_LEVEL level);

/**
    @brief
    Returns current teeth whitening level.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[out] pLevel
    Currently configured level of applied teeth whitening effect. 

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_getTeethWhiteningLevel(CTFaceBeautification *pFaceBeautifier,
                                                              FACEBEAUTIFICATION_CORRECTION_LEVEL *pLevel);

/**
    @brief
    Sets eyes enlargement effect as active with enlargement level.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[in] level
    Level of applied eyes enlargement effect. See FACEBEAUTIFICATION_CORRECTION_LEVEL for available levels.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_setEyesEnlargement(CTFaceBeautification *pFaceBeautifier,
                                                          FACEBEAUTIFICATION_CORRECTION_LEVEL level);

/**
    @brief
    Returns current eyes enlargement level.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[out] pLevel
    Currently configured level of applied eyes enlargement effect.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_getEyesEnlargementLevel(CTFaceBeautification *pFaceBeautifier,
                                                               FACEBEAUTIFICATION_CORRECTION_LEVEL *pLevel);

/**
    @brief
    Sets eyes enhancement effect as active with enhancement level.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[in] level
    Level of applied eyes enhancement effect. See FACEBEAUTIFICATION_CORRECTION_LEVEL for available levels.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_setEyesEnhancement(CTFaceBeautification *pFaceBeautifier,
                                                         FACEBEAUTIFICATION_CORRECTION_LEVEL level);

/**
    @brief
    Returns current eyes enhancement level.

    @param[in] pFaceBeautifier
    Valid beautifier object.

    @param[out] pLevel
    Currently configured level of applied eyes enhancement effect.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.3
*/
SCBIMPORT CRESULT ctfacebeautification_getEyesEnhancementLevel(CTFaceBeautification *pFaceBeautifier,
                                                              FACEBEAUTIFICATION_CORRECTION_LEVEL *pLevel);

/**
@}
*/
// end addtogroup 'fm_facebeautification'

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // !defined(FM_FACEBEAUTIFICATION_H)

