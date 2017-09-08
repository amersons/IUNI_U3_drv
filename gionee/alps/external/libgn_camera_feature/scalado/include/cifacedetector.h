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

#ifndef CIFACEDETECTOR_H
#define CIFACEDETECTOR_H

#include "scbdefs.h"
#include "ctfacedetector_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CIFaceDetector CIFaceDetector;

//=============================================================================
/**
    @file cifacedetector.h
    @brief Defines the face detector interface.
    @ingroup cifacedetector

*/
//=============================================================================
/**
    @addtogroup cifacedetector
    @brief Feature detector interface

    @{
*/
//-----------------------------------------------------------------------------

/**
    @brief Creates a @c CTFaceDetector object using the provided interface.

    @param pInterface Pointer to a face detector interface.
           @sa CIFaceDetector.
    @param pContext Pointer to user data related to
           one specific face detector.
    @param[out] ppFaceDetector Pointer to a newly created face detector.

    When the face detector object (returned by this function) is no longer
    needed, it should be destroyed using: ctfacedetector_destroy()

    @return A @c CRESULT result code.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctfacedetector_create ( const CIFaceDetector *pInterface,
                        void *pContext,
                        CTFaceDetector **ppFaceDetector );

//-----------------------------------------------------------------------------
/**
    @interface CIFaceDetector
    @brief face detector interface.
*/
struct CIFaceDetector
{
    /**
        @brief Destroys the underlying face detector.
        Must be possible to call at any time, also while iterating.

        @param pContext Pointer to user specific data for this face detector.
    */
    void (*destroy) ( void *pContext );

    /** 
        @brief Get which types of features this face detector can detect

        @param pContext Pointer to user specific data for this face detector

        @return Sum of all supported feature types in CTFeatureType.
    */
    CTuint32 (*getDetectableFeatures) ( void *pContext );

	/** 
        @brief Set the types of features this face detector will detect

        @param pContext Pointer to user specific data for this face detector

		@param featureSet A sum of the feature types from CTFeatureType
        defining which features should be detected.

        @return @c CERR_OK if successful or a specific error code upon failure.
    */
	CRESULT (*setFeaturesToDetect) ( void *pContext, CTuint32 featureSet );

    /** 
        @brief Get supported color mode

        @param pContext Pointer to user specific data for this face detector

        @return The colormode that must be used by the image input in
        detectBegin()

        Will be one of
        @li CM_GRAY8
        @li CM_ARGB8888
        @li CM_AYUV4444
        @li CM_RGB565
        @li CM_YUV422_Y1UY2V

        @remarks
        CM_RGB565 is a endian-dependent 16 bit color format where each pixel is a
        CTuint16 with upper 5 bits R, middle 6 bits G, lower 5 bits B.
    */
    CTColormode (*getColormode) ( void *pContext );

    /**
        @brief Detect features in a CTImage

        @param pContext Pointer to user specific data for this face detector

        @param pImage Input image. The colormode of this image must be the
        one given from getColormode().
        Any dimensions are allowed, however the face detector is assumed to be
        optimized for images of roughly VGA size.

        @return @c CERR_OK if successful or a specific error code upon failure.

        @remarks
        Results of the face detection is given by getFaces().
        The previous iterative detection must be completed before starting a new
        one.
    */
    CRESULT (*detectBegin)( void *pContext,
                            CTImage *pImage );

    /**
        @brief Perform one iteration of a face detection

        @param pContext Pointer to user specific data for this face detector

        @param pPercentDone[OUT] Percent done for this detector. [0,100]. Must
        not decrease compared to the latest iteration. The precision of the
        output is not strictly defined but should be as detailed as feasible
        for the specific interface implementation.

        @return @c CERR_OK if successful or a specific error code upon failure.
        The last iteration returns @c CRES_TASK_COMPLETE upon success.
    */
    CRESULT (*detectIterate) ( void *pContext,
                               CTuint32 *pPercentDone );

    /**
        @brief Called after detectIterate has returned CRES_TASK_COMPLETE

        This function is not allowed to be called when an error has occurred.

        @param pContext Pointer to user specific data for this face detector

        @param pNumberOfFaces[OUT] The number of faces found

        @return @c CERR_OK if successful or a specific error code upon failure.
    */
    CRESULT (*detectEnd) ( void *pContext, CTuint32 *pNumberOfFaces );

    /** 
        @brief Returns a face collection containing the result of the previous face detection. 

        @param pContext Pointer to user specific data for this face detector
        @param[out] ppFaceCollection The collection containing all detected faces.
                    The collection is always owned by the CTFaceDetector and should NOT be freed by the caller.

        @return @c CERR_OK if successful or a specific error code upon failure.

        @remarks
        @li The number of faces in the collection is guaranteed to be
        equal to the number of faces given by detectEnd.
        @li This function may only support being called once for each
        feature detection operation.
        @li The returned CTFaceCollection is only valid until next call to detectBegin().
        @li The returned CTFaceCollection is owned by the CTFaceDetector and should NOT be freed by the caller.
    */
    CRESULT (*getFaces) ( void *pContext,
                             CTFaceCollection **ppFaceCollection );
};
// end of 'struct CIFaceDetector'
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'cifacedetector'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif //CIFACEDETECTOR_H

