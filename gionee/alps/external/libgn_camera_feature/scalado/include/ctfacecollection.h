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

#ifndef CTFACECOLLECTION_H
#define CTFACECOLLECTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctfacedetector_types.h"
#include "ctfacecollection_add.h"

//=============================================================================
/**
    @file ctfacecollection.h
    @ingroup ctfacecollection
*/
//=============================================================================

/**
    @addtogroup ctfacecollection
    @brief Functions for querying result of face detection.

    A collection contains a number of faces. The faces can have different
    features, e.g. eyes and smile amount. A typical parsing of a collection:

    @li Get number of faces in a collection, ctfacecollection_getNumberOfFaces()
    @li For each face:
    @li Get face, ctfacecollection_getFace()
    @li Get location and size of face, ctfeatureface_getRect()
    @li Get feature of interest, for example ctfeatureface_getLeftEye()
    @li Get location and size of feature, ctfeatureeye_getRect()

    @{
*/
//-----------------------------------------------------------------------------

/** 
    @brief Create a CTFaceCollection. 

    @param maxNumberOfFaces Maximum number of faces in collection
    @param[out] ppCollection Created object

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctfacecollection_create( CTuint32 maxNumberOfFaces,
                         CTFaceCollection **ppCollection );

//-----------------------------------------------------------------------------

/** 
    @brief Destroy a CTFaceCollection

    @param pCollection Collection to destroy. Function accepts NULL.

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfacecollection_destroy( CTFaceCollection *pCollection );

//-----------------------------------------------------------------------------

/** 
    @brief Clone a CTFaceCollection

    Create a new CTFaceCollection that is a copy of an existing one.

    @param pSrc Existing collection
    @param[out] ppDst Created object

    @since 3.10.1.0
*/
SCBIMPORT CRESULT ctfacecollection_clone( CTFaceCollection *pSrc, CTFaceCollection **ppDst );

//-----------------------------------------------------------------------------

/** 
    @brief Reset a CTFaceCollection and clear all faces from it

    @param pCollection Collection to reset.

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfacecollection_reset( CTFaceCollection *pCollection );

//-----------------------------------------------------------------------------

/** 
    @brief Get number of faces

    @param pCollection CTFaceCollection object

    @return Number of faces that are currently in this object.

    @since 3.8.2 R01
*/
SCBIMPORT CTuint32 
ctfacecollection_getNumberOfFaces( CTFaceCollection *pCollection );

//-----------------------------------------------------------------------------

/** 
    @brief Get maximum number of faces this collection can hold

    @param pCollection CTFaceCollection object

    @return Maximum number of faces that this object han hold.

    @since 3.8.2 R01
*/
SCBIMPORT CTuint32 
ctfacecollection_getMaxNumberOfFaces( CTFaceCollection *pCollection );

//-----------------------------------------------------------------------------

/** 
    @brief Get a CTFeatureFace at a given index in a CTFaceCollection

    @param pCollection CTFaceCollection object
    @param index Index of face, [ 0 , ctfacecollection_getNumberOfFaces() - 1 ]
    @param[out] ppFace Pointer to face within collection.

    @return @c CERR_OK if successful or a specific error code upon failure.

    @remark The face is at all time owned by the collection.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctfacecollection_getFace( CTFaceCollection *pCollection,
                          CTuint32 index,
                          CTFeatureFace **ppFace );

//=============================================================================
// CTFeatureSmile

/** 
    @brief Get the percentSmile property of a CTFeatureSmile

    @param pSmile a CTFeatureSmile

    @return @c Percent smile, in the range [0,100]

    @since 3.8.2 R01
*/
SCBIMPORT CTuint32 
ctfeaturesmile_getPercentSmile( CTFeatureSmile *pSmile );

//=============================================================================
// CTFeatureBlink

/** 
    @brief Get the percentBlink property of a CTFeatureBlink

    @param pBlink a CTFeatureBlink

    @return Percent blink, in the range [0,100]

    @since 3.9
*/
SCBIMPORT CTuint32 
ctfeatureblink_getPercentBlink( CTFeatureBlink *pBlink );

//=============================================================================
// CTFeatureNose

/**
    @brief Get the rect of a CTFeatureNose

    @param pNose a CTFeatureNose
    @param[out] pRect the rect of the feature

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/
SCBIMPORT CRESULT ctfeaturenose_getRect( CTFeatureNose *pNose, CTRect *pRect );

//=============================================================================
// CTFeatureMouth

/**
    @brief Get the rect of a CTFeatureMouth

    @param pMouth a CTFeatureMouth
    @param[out] pRect the rect of the feature

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/
SCBIMPORT CRESULT ctfeaturemouth_getRect( CTFeatureMouth *pMouth, CTRect *pRect );

//=============================================================================
// CTFeatureEye

/**
    @brief Get the rect of a CTFeatureEye

    @param pEye a CTFeatureEye
    @param[out] pRect the rect of the feature

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/
SCBIMPORT CRESULT ctfeatureeye_getRect( CTFeatureEye *pEye, CTRect *pRect );

//-----------------------------------------------------------------------------

/**
    @brief Get the point of a CTFeatureEye

    @param pEye a CTFeatureEye
    @param[out] pPoint the point of the feature

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 5.1
*/
SCBIMPORT CRESULT ctfeatureeye_getPoint( CTFeatureEye *pEye, CTPoint *pPoint );

//=============================================================================
// CTFeatureFace

/**
    @brief Get the rect of a CTFeatureFace

    @param pFace a CTFeatureFace
    @param[out] pRect the rect of the feature

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 3.9
*/
SCBIMPORT CRESULT ctfeatureface_getRect( CTFeatureFace *pFace, CTRect *pRect );

//-----------------------------------------------------------------------------

/** 
    @brief Get left eye of face

    @param pFace a face

    @return left eye of face or null if face has no left eye

    @since 3.8.2 R01
*/
SCBIMPORT CTFeatureEye *ctfeatureface_getLeftEye( CTFeatureFace *pFace );

//-----------------------------------------------------------------------------

/** 
    @brief Get right eye of face

    @param pFace a face

    @return right eye of face or null if face has no right eye

    @since 3.8.2 R01
*/
SCBIMPORT CTFeatureEye *ctfeatureface_getRightEye( CTFeatureFace *pFace );

//-----------------------------------------------------------------------------

/** 
    @brief Get the centerpoint of the eyes

    @param pFace a face
    
    @param pPoint the point right between the eyes

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 5.1
*/
SCBIMPORT CRESULT ctfeatureface_getCentralEyePoint( CTFeatureFace *pFace, CTPoint *pPoint );

//-----------------------------------------------------------------------------

/** 
    @brief Get face's mouth

    @param pFace a face

    @return face's mouth or null if face has no mouth

    @since 3.8.2 R01
*/
SCBIMPORT CTFeatureMouth *ctfeatureface_getMouth( CTFeatureFace *pFace );

//-----------------------------------------------------------------------------

/** 
    @brief Get face's nose

    @param pFace a face

    @return face's nose or null if face has no nose

    @since 3.8.2 R01
*/
SCBIMPORT CTFeatureNose *ctfeatureface_getNose( CTFeatureFace *pFace );

//-----------------------------------------------------------------------------

/** 
    @brief Get face's smile

    @param pFace a face

    @return face's smile or null if face has no smile

    @since 3.8.2 R01
*/
SCBIMPORT CTFeatureSmile *ctfeatureface_getSmile( CTFeatureFace *pFace );

//-----------------------------------------------------------------------------

/** 
    @brief Get face's blink

    @param pFace a face

    @return face's blink or null if face has no blink

    @since 3.9
*/
SCBIMPORT CTFeatureBlink *ctfeatureface_getBlink( CTFeatureFace *pFace );

//-----------------------------------------------------------------------------

/** 
    @brief Get face's ID when tracking is used.

    @param pFace a face

    @return face's id.

    @remark The ID of a face is only valid when using a tracking enabled CTFaceDetector.

    @since 3.9
*/
SCBIMPORT CTuint32 ctfeatureface_getID( CTFeatureFace *pFace );

/** @} */
// end addtogroup 'ctfacecollection'
//=============================================================================

#ifdef __cplusplus
} // extern "C"
#endif

#endif //CTFACECOLLECTION_H

