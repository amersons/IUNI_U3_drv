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

#ifndef CTFACECOLLECTION_ADD_H
#define CTFACECOLLECTION_ADD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctfacedetector_types.h"

//=============================================================================
/**
    @file ctfacecollection_add.h
    @ingroup ctfacecollection_add
*/
//=============================================================================
/**
    @addtogroup ctfacecollection_add
    @brief Provides methods for adding data to a ::CTFaceCollection object,
    which is the (output) data type from a @ref ctfacedetector

    @{
*/
//-----------------------------------------------------------------------------
// CTFeatureFace
/** 
    @brief Add face to feature collection

    @param pCollection  A pointer to a data structure to fill-in.
    @param pRect The face rectangle should cover the outer contours of the head.
    @param[out] ppFace  Handle to a face in pCollection (optional). This object
    is at all times owned by pCollection.

    @return @c CERR_OK if successful or a specific error code upon failure.      

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctfacecollection_addFace( CTFaceCollection *pCollection, CTRect *pRect, CTFeatureFace **ppFace );

//-----------------------------------------------------------------------------

/** 
@brief Scale rectangles in a face and in all its subfeatures

@param pFace A face
@param scale Scale, must be >= 0.0f

@since 3.9
*/
SCBIMPORT void
ctfeatureface_scale( CTFeatureFace *pFace, CTfloat scale );

//-----------------------------------------------------------------------------

/** 
    @brief Set left eye of face

    @param pFace A face
    @param pEyeRect The rect of an eye

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfeatureface_setLeftEye( CTFeatureFace *pFace, CTRect *pEyeRect );

//-----------------------------------------------------------------------------

/** 
    @brief Set the centerpoint of the left eye of face

    @param pFace A face
    @param pEyePoint The point of an eye

    @since 5.1
*/
SCBIMPORT void 
ctfeatureface_setLeftEyePoint( CTFeatureFace *pFace, CTPoint *pEyePoint );

//-----------------------------------------------------------------------------

/** 
    @brief Set right eye of face

    @param pFace A face
    @param pEyeRect The rect of an eye

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfeatureface_setRightEye( CTFeatureFace *pFace, CTRect *pEyeRect );

//-----------------------------------------------------------------------------

/** 
    @brief Set the centerpoint of the right eye of face

    @param pFace A face
    @param pEyePoint The point of an eye

    @since 5.1
*/
SCBIMPORT void 
ctfeatureface_setRightEyePoint( CTFeatureFace *pFace, CTPoint *pEyePoint );

//-----------------------------------------------------------------------------

/** 
    @brief Set face's mouth

    @param pFace  A face
    @param pCentralEyePoint The point right between the eyes

    @since 5.1
*/
SCBIMPORT void 
ctfeatureface_setCentralEyePoint( CTFeatureFace *pFace, CTPoint *pCentralEyePoint );

//-----------------------------------------------------------------------------

/** 
    @brief Set face's mouth

    @param pFace  A face
    @param pMouthRect The rect of a mouth

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfeatureface_setMouth( CTFeatureFace *pFace, CTRect *pMouthRect );

//-----------------------------------------------------------------------------

/** 
    @brief Set face's nose

    @param pFace A face
    @param pNoseRect The rect of a nose

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfeatureface_setNose( CTFeatureFace *pFace, CTRect *pNoseRect );

//-----------------------------------------------------------------------------

/** 
    @brief Set face's smile percent

    @param pFace  A face
    @param smilePercent The face's smile percent in the range [0, 100]

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfeatureface_setSmile( CTFeatureFace *pFace, CTuint32 smilePercent );

/** 
    @brief Set whether the face is tracked or not.

    @param pFace  A face
    @param isTracked Indicates whether the face is tracked or not.

    @since 5.3
*/
SCBIMPORT void ctfeatureface_setIsTracked( CTFeatureFace *pFace, CTbool isTracked );

/** 
    @brief Set a face's Angle.

    @param pFace  A face
    @param angle The face's Angle.

    @since 5.3
*/
SCBIMPORT void ctfeatureface_setAngle( CTFeatureFace *pFace, CTint32 angle );

//-----------------------------------------------------------------------------

/** 
    @brief Set a face's blink percent

    @param pFace  A face
    @param blinkPercent The face's blink percent in the range [0, 100]

    @since 3.9
*/
SCBIMPORT void 
ctfeatureface_setBlink( CTFeatureFace *pFace, CTuint32 blinkPercent );

//-----------------------------------------------------------------------------

/** 
    @brief Set a face's ID.

    @param pFace  A face
    @param id The face's ID.

    @remark Used by CTFaceDetector when tracking is enabled.

    @since 3.9
*/
SCBIMPORT void ctfeatureface_setID( CTFeatureFace *pFace, CTuint32 id );




/** @} */
// end addtogroup 'ctfacecollection_add'
//=============================================================================

#ifdef __cplusplus
} // extern "C"
#endif

#endif //CTFACECOLLECTION_ADD_H
