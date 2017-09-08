/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    Copyright (c) 2000-2011 Scalado AB. All rights reserved.                 .
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

#ifndef CTSTEREOSESSION_H
#define CTSTEREOSESSION_H

#include "scbdefs.h"
#include "caps_types.h"
#include "ctstream.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================

/**
    @file ctstereosession.h
    @brief Defines the interface for stereoscopic image management in CAPS.
    @ingroup ctstereosession
*/
//=============================================================================

/**
    @addtogroup ctstereosession
    @brief Write stereoscopic images.

    CTStereoSession is a general interface for writing stereoscopic images as
    JPS files. In the future other methods may be added to support additional
    file formats and use cases.

    When rendering the images to a JPS, they're arranged in a side by side
    cross eyed configuration.

    <h3>Usage</h3>
    In the basic use case you call the functions in the following order:
    -# ctstereosession_create()
    -# ctstereosession_setLeftEyeSession()
    -# ctstereosession_setRightEyeSession()
    -# ctstereosession_finalizeJps()
    -# ctstereosession_destroy()
    .

    @{
*/

/**
    @brief
    Object representing a stereoscopic image session.

    @since 5.0.1
*/
typedef struct CTStereoSession CTStereoSession;
//--------------------------------------------------------------------------

/**
    @brief
    Creates a CTStereoSession object.

    @param[out] ppStereoSession A pointer to a variable of the type (CTStereoSession *).
    On a successful call, the object will be created.

    @return CERR_OK on success.

    @since 5.0.1
*/
SCBIMPORT CRESULT ctstereosession_create(CTStereoSession **ppStereoSession);
//--------------------------------------------------------------------------

/**
    @brief
    Sets the image corresponding to the left eye's view.

    The image in the provided session will be rendered to the JPS file as
    the image representing the left eye vision when
    ctstereosession_finalizeJps() is called.

    The ownership of the session will not be passed to the CTStereoSession
    object, so the session will have to be destroyed independently after the
    destruction of the CTStereoSession object.

    @param pStereoSession A valid pointer to a CTStereoSession object.

    @param leftSession a session that will be added to the
    CTStereoSession object.

    @return CERR_OK on success.

    @since 5.0.1
*/
SCBIMPORT CRESULT ctstereosession_setLeftEyeSession(CTStereoSession *pStereoSession, CTSession leftSession);
//--------------------------------------------------------------------------

/**
    @brief
    Sets the image corresponding to the right eye's view.

    The image in the provided session will be rendered to the JPS file as
    the image representing the right eye vision when
    ctstereosession_finalizeJps() is called.

    The ownership of the session will not be passed to the CTStereoSession
    object, so the session will have to be destroyed independently after the
    destruction of the CTStereoSession object.

    @param pStereoSession A valid pointer to a CTStereoSession object.

    @param rightSession a session that will be added to the
    CTStereoSession object.

    @return CERR_OK on success.

    @since 5.0.1
*/
SCBIMPORT CRESULT ctstereosession_setRightEyeSession(CTStereoSession *pStereoSession, CTSession rightSession);
//--------------------------------------------------------------------------

/**
    @brief
    Render a CTStereoSession to an output stream.

    All images added to the CTStereoSession will be written, via the
    provided stream, to a newly created JPS file.

    @param pStereoSession A valid pointer to a CTStereoSession object.

    @param pOut A pointer to a stream, which the CTStereoSession object
    will be rendered/written to.

    @param[in,out] ppIterator If a valid pointer, to a variable of the type:  (CTIterator *),
    is provided, an iterator object will be created (see: @ref caps_iterators).
    @n
    If @c NULL is passed, the operation will be completed before this function returns.

    @return CERR_OK on success.

    @since 5.0.1
*/
SCBIMPORT CRESULT ctstereosession_finalizeJps(CTStereoSession *pStereoSession, CTStream *pOut, CTIterator **ppIterator);
//--------------------------------------------------------------------------

/**
    @brief
    Destroys a CTStereoSession object.

    @param pStereoSession Pointer to a valid CTStereoSession object, or NULL.

    @since 5.0.1
*/
SCBIMPORT void ctstereosession_destroy(CTStereoSession *pStereoSession);
//--------------------------------------------------------------------------

/** @} */
#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( CTSTEREOSESSION_H )
