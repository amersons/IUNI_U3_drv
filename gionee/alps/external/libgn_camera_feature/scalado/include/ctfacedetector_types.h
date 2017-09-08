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

#ifndef SCBFEATUREDETECTION_TYPES_H
#define SCBFEATUREDETECTION_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"

//=============================================================================
/**
    @file ctfacedetector_types.h
    @brief Defines the public types used with CTFaceDetector.
    @ingroup ctfacedetector_types
*/
//=============================================================================

/**
    @addtogroup ctfacedetector_types
    @brief Types and definitions used with CAPS Feature Module @ref fm_face

    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief
    Face detector object
*/
typedef struct CTFaceDetector CTFaceDetector;

//-----------------------------------------------------------------------------
/**
    @brief
    Collection of face related features
*/
typedef struct CTFaceCollection CTFaceCollection;

//-----------------------------------------------------------------------------
/**
    @brief
    Type of a feature
*/

typedef enum CTFeatureType
{
    CTFEATURETYPE_FACE  = (1 << 0),   ///< Type associated with CTFeatureFace
    CTFEATURETYPE_EYE   = (1 << 1),   ///< Type associated with CTFeatureEye
    CTFEATURETYPE_MOUTH = (1 << 2),   ///< Type associated with CTFeatureMouth
    CTFEATURETYPE_NOSE  = (1 << 3),   ///< Type associated with CTFeatureNose
    CTFEATURETYPE_SMILE = (1 << 4),   ///< Type associated with CTFeatureSmile
    CTFEATURETYPE_BLINK = (1 << 5)    ///< Type associated with CTFeatureBlink
} CTFeatureType;

//-----------------------------------------------------------------------------
/**
    @brief
    Face
*/
typedef struct CTFeatureFace CTFeatureFace;

//-----------------------------------------------------------------------------
/**
    @brief
    Mouth
*/
typedef struct CTFeatureMouth CTFeatureMouth;

//-----------------------------------------------------------------------------
/**
    @brief
    Eye
*/
typedef struct CTFeatureEye CTFeatureEye;

//-----------------------------------------------------------------------------
/**
    @brief
    Nose
*/
typedef struct CTFeatureNose CTFeatureNose;

//-----------------------------------------------------------------------------
/**
    @brief
    Smile
*/
typedef struct CTFeatureSmile CTFeatureSmile;

//-----------------------------------------------------------------------------
/**
    @brief
    Blink
*/
typedef struct CTFeatureBlink CTFeatureBlink;

/** @} */
// end addtogroup 'ctfacedetector_types'
//=============================================================================

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SCBFEATUREDETECTION_TYPES_H
