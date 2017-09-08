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

#ifndef FM_FACE_H
#define FM_FACE_H

#ifdef __cplusplus
extern "C" {
#endif


#include "ctfacedetector_types.h"
#include "caps_base.h"
#include "scbdefs.h"

//=============================================================================
/** 
    @file fm_face.h
    @brief Defines the interface of the Caps Feature Module: @ref fm_face
    @ingroup fm_face
*/
//=============================================================================
/** 
    @addtogroup fm_face
    @brief Face and facial features detection

    The normal scenario for detecting faces in a ::CTSession :

    - Create a face detector with ctfacedetector_createStandard()
    - Call caps_findFaceFeatures()
    - Get the detected features using a @ref ctfacecollection
    .

    See also @ref fm_face_example for usage details.

    To detect faces in a single image, use a detector with tracking disabled
    for higher accuracy. To detect faces in a sequence of images, use a tracking
    enabled detector for speedup. In the latter case, the faces
    are labeled with ID:s, see ctfeatureface_getID().

    To detect faces in raw images, or to get more detailed control of
    the detection, use the functions in @ref ctfacedetector.

    For optimal performance and accuracy of the face detection it is recommended to use
    input images in VGA resolution (640x480).

    @{
        @defgroup ctfacedetector_types          Types and definitions
        @defgroup ctfacedetector                CTFaceDetector API
        @defgroup ctfacecollection              CTFaceCollection API
        @defgroup scb_facedetector_interface    Face Detector Extension Interface
        @brief Face detector extension interface, and auxiliary functions.
        @{
            @defgroup cifacedetector          CIFaceDetector
            @defgroup ctfacecollection_add    Face detection output construction
*/
/**     @} */
/**
        @defgroup fm_face_example Face detection code sample
        @brief Example of how to use the face detector api.
        @{
            @include fm_face_example.c
*/
/**     @} */

//-----------------------------------------------------------------------------

/**
    @brief Analyze the current session for faces and face features

    @param session
    A valid caps session. The state of the session will be modified during the
    iterative execution of this function. Therefore, the session must not be
    occupied in another iterative task, and must be kept untouched until the
    iterations are done and the iterator is destroyed.

    @param pFaceDetector
    A CTFaceDetector created externally. This feature detector will be
    used for feature detection on the session. The state of the feature detector
    will be modified during the iterative execution of this function. Therefore,
    the internal state of the feature detector must not be modified from the
    outside, until the iterator is destroyed.

    @param featureSet
    An OR:ed combination of ::CTFeatureType values
    describing which features should be detected. If the detector lacks
    capability of detecting any of these feature types, an error will be
    returned, @c CERR_INVALID_PARAMETER, and no feature detection will occur.

    @param maxAnalyzeDimension
    Internally, a raw buffer is generated, which is given to the
    detection algorithm. The buffer has the largest dimension set to
    maxAnalyzeDimension, while keeping the aspect ratio of the session current 
    image size. The raw buffer uses between one and four bytes per pixel and
    is allocated and freed internally in this function.
    \n\n
    The larger the buffer, the more memory is used by this function and the
    longer time it takes to find faces. However the larger the buffer, the more
    faces are found. An appropriate default value of this parameter is 400.
    \n\n
    <b>For example:</b> \n
    if the maxAnalyzeDimension is 320 and the current image size is 640x480,
    the internal analyze buffer is 320x240. If the current image size is 480x640, 
    the internal analyze buffer would be 240x320.
    \n\n
    The parameter must be in the range [32, 4096].

    @param ppFeatures
    Result of a feature detection. This object is owned by the detector.
    This object is valid until the detector is used again.
    If no features are found, the *ppFeatures is set to NULL.
    If an iterator is used, the variable/address pointed to by ppFeatures
    must be valid when the iterations are performed. The collection is
    not accessible until the iterations are complete.

    @param ppIterator
    (Optional) Iterator object.
    Perform caps_doNextIteration on this object until
    @c CRES_TASK_COMPLETE or an error is returned.
    If @c CRES_TASK_COMPLETE was returned.
    Destroy the iterator with caps_destroyIterator().
    \n\n
    Only the following functions are valid for the iterator object:

    @li caps_doNextIteration()
    @li caps_destroyIterator()

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT caps_findFaceFeatures( CTSession session,
                                     CTFaceDetector *pFaceDetector,
                                     CTuint32 featureSet,
                                     CTuint32 maxAnalyzeDimension,
                                     CTFaceCollection **ppFeatures,
                                     CTIterator **ppIterator );

//-----------------------------------------------------------------------------
/** @} */
// end addtogroup 'fm_face'
//=============================================================================

#ifdef __cplusplus
}
#endif

#endif // FM_FACE_H
