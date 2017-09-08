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

#ifndef CTFACEDETECTOR_H
#define CTFACEDETECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctfacedetector_types.h"
#include "caps_iterator.h"

//=============================================================================
/**
    @file ctfacedetector.h
    @brief Public interface of CTFaceDetector
    @ingroup ctfacedetector
*/
//=============================================================================

/**
    @addtogroup ctfacedetector
    @brief Face detection functionality.

    This interface contains functions for using a face detector.
    The normal scenario for detecting faces in an image is:

    - Create a face detector. Call ctfacedetector_createStandard()
    (in file ctfacedetector_standard.h)
    - Create the CTImage that should contain the image for detection.
        The image must have the colorformat returned by ctfacedetector_getColormode();
    - Set what features should be detected with ctfacedetector_setFeaturesToDetect().
        To set all features possible, use ctfacedetector_getDetectableFeatures.
    - Detect faces and features with ctfacedetector_detect().
    - Get all detected faces with ctfacedetector_getFaces().
    .

    For optimal performance and accuracy of the face detection it is recommended to use
    input images in VGA resolution (640x480).

    @{
*/
//-----------------------------------------------------------------------------

/** 
    @brief Destroy a CTFaceDetector

    @param pFaceDetector A feature detector

    @remarks
    This function must handle NULL as input.

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctfacedetector_destroy( CTFaceDetector *pFaceDetector );


/** 
    @brief Get which types of features a feature detector can detect

    @param pFaceDetector A face detector

    @return An OR:ed combination of supported CTFeatureType:s.

    @since 3.8.2 R01
*/
SCBIMPORT CTuint32 
ctfacedetector_getDetectableFeatures( CTFaceDetector *pFaceDetector );

/** 
    @brief Set which features a face detector should detect

    @param pFaceDetector A face detector

	@param featureSet An OR:ed combination of CTFeatureType values
    describing which features should be detected.

    @return @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctfacedetector_setFeaturesToDetect( CTFaceDetector *pFaceDetector, CTuint32 featureSet );

/** 
    @brief Get supported color mode

    @param pFaceDetector A face detector

    @return The colormode that must be used by the image input in
    ctfacedetector_detect()

    Will be one of
    @li CM_GRAY8
    @li CM_ARGB8888
    @li CM_RGB565
    @li CM_AYUV4444
    @li CM_YUV422_Y1UY2V

    @remarks
    CM_RGB565 is a endian-dependent 16 bit color format where each pixel is a
    CTuint16 with upper 5 bits R, middle 6 bits G, lower 5 bits B.

    @since 3.8.2 R01
*/
SCBIMPORT CTColormode 
ctfacedetector_getColormode( CTFaceDetector *pFaceDetector);

/**
    @brief Detect features in a CTImage

    @param pFaceDetector A face detector

    @param pImage Input image. The colorformat must be the
    one given from ctfacedetector_getColormode().
    Any dimensions are allowed, however the face detector is assumed to be
    optimized for images of roughly VGA size.

    @param ppIterator If != NULL, an iterator is created, otherwise
    the detection should be finished with this call.

    @return @c CERR_OK if successful or a specific error code upon failure.

    @remarks
    Results of the faces with features are given by ctfacedetector_getFaces().
    The previous iterative detection must be completed before starting a new one.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT
ctfacedetector_detect( CTFaceDetector *pFaceDetector,
                          CTImage *pImage,
                          CTIterator **ppIterator );

/** 
    @brief Get the number of faces found by the latest
    ctfacedetector_detect().

    @param pFaceDetector A face detector

    @return The number of faces found in the latest ctfacedetector_detect()

    @remarks
    @li This operation is not valid before the detection is complete.

    @since 3.8.2 R01
*/
SCBIMPORT CTuint32 
ctfacedetector_getNumberOfFaces( CTFaceDetector *pFaceDetector );

/** 
    @brief Return the faces, with features, found during detection.

    @param pFaceDetector A face detector
    @param[out] ppFaceCollection A collection containing all detected faces. If no faces are found null is returned.
                 The collection is always owned by the CTFaceDetector and should NOT be freed on its own.

    @return @c CERR_OK if successful or a specific error code upon failure.

    @remarks
    @li The number of faces in the collection is guaranteed to be
    equal to the result from ctfacedetector_getNumberOfFaces().
    @li The returned collection is only valid until the next call to ctfacedetector_detect().
    @li The detection operation must finish before calling this function
    @li The CTFaceCollection is owned by the CTFaceDetector and should NOT be freed by the caller.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctfacedetector_getFaces( CTFaceDetector *pFaceDetector,
                         CTFaceCollection **ppFaceCollection );

/** @} */
// end addtogroup 'ctfacedetector'
//=============================================================================

#ifdef __cplusplus
} // extern "C"
#endif



#endif //CTFACEDETECTOR_H

