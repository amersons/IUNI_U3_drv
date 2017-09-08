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

#ifndef CTMPOSESSION_H
#define CTMPOSESSION_H

#include "scbdefs.h"
#include "ctencoder.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================

/**
    @file ctmposession.h
    @brief Defines the interface for MPO management in CAPS.
    @ingroup ctmposession
*/
//=============================================================================

/**
    @addtogroup ctmposession
    @brief Read, write and create MPO (Multi Picture Object) files.

    CTMpoSession is a general interface for reading and creating MPO files.
    The format of MPO files is described by the standard document
    "CIPA DC-007-2009". The user of this interface is advised to study
    this document before using the interface.

    <h3>Usage</h3>
    All functions (except the constructors) takes a pointer to a
    ::CTMpoSession object as an argument. As a second argument, most functions
    also take an index that specifies which source/destination image within the
    MPO file that the call should affect.

    Functions that set, get, or remove tag specific attributes have names that are
    derived from the tag name as follows: @c ctmposession_ + @em \<op\> + @em \<tag-name\>,
    where @em \<op\> is either @c set, @c get, or @c remove, and @em \<tag-name\> the
    name (as defined in the standard) of the MPO tag/attribute to read/modify.
    For example, to set, get, or remove the attribute associated with the
    @c PanOrientation tag, the following functions are used:
    - ctmposession_setPanOrientation()
    - ctmposession_getPanOrientation()
    - ctmposession_removePanOrientation()
    .
    For an explanation of the purpose and usage of each tag/attribute the reader
    is referred to read the MPO standard.

    There are two basic use cases for this interface:

    <h3>Render images from an existing MPO file</h3>
    - Calling ctmposession_createFromMpoStream() will create a ::CTMpoSession from
    a stream containing an existing MPO file.
    - Given the MPO session, an image can then be retrieved, via a stream object, by
    calling ctmposession_getStream().
    - From the provided stream, in turn, a regular ::CTSession can be created from
      which the contained image can be rendered to, for example, the screen.
    - Finally, ctmposession_destroy() will destroy the CTMpoSession, including
    any streams and encoders owned by the MPO session.
    .

    <h3>Create a new MPO file given a set of images</h3>
    - Calling ctmposession_create() creates a new MPO session, with default
      tags/values set.
    - To add one or more images to the session, call
      ctmposession_addSourceStream()
    - Set specific tag/attribute values, or modify the default values. (Note,
      regarding the set default values, a disparity use case as described in
      the standard is assumed).
    - When done adding images and modifying tag values, the resulting MPO file
      can be written to a stream by calling ctmposession_finalize().
    - Finally, ctmposession_destroy() will destroy the CTMpoSession, including
      any associated streams and encoders owned by the MPO session. Remember to
      clean up any pending @em input streams, as ctmposession_addSourceStream()
      does not take ownership of these.

    @{
*/
//--------------------------------------------------------------------------

/**
    @brief
    Object representing an MPO session.

    @since 5.0
*/
typedef struct CTMpoSession CTMpoSession;

//--------------------------------------------------------------------------
/**
    @brief
    Creates a CTMpoSession object.

    @param[out] ppMpoSession A pointer to a variable of the type (CTMpoSession *).
    On a successful call, the object will be created.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_create( CTMpoSession **ppMpoSession );

//--------------------------------------------------------------------------
/**
    @brief
    Creates a CTMpoSession object based on a MPO file in a provided stream.

    @param[out] ppMpoSession A pointer to a variable of the type (CTMpoSession *).
    On a successful call, the object will be created.

    @param pStream A stream containing a MPO file that the CTMpoSession object
    will be based on.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_createFromMpoStream( CTMpoSession **ppMpoSession, CTStream *pStream );

//--------------------------------------------------------------------------
/**
    @brief
    Destroys a CTMpoSession object.

    @param pMpoSession Pointer to a valid CTMpoSession object, or NULL.

    @since 5.0
*/
SCBIMPORT void ctmposession_destroy( CTMpoSession *pMpoSession );

//--------------------------------------------------------------------------
/**
    @brief
    Adds a stream (containing a Jpeg image) to a CTMpoSession.

    The image in the provided stream will be added to the MPO file when
    ctmposession_finalize() is called. If several different streams are added to a
    CTMpoSession, the images will be written in the order that their corresponding
    streams were added.

    The ownership of an added stream will not be passed to the CTMpoSession
    object, so the stream will have to be freed independently after the
    destruction of the CTMpoSession object. The stream should not be 
    destroyed before the destruction of the CTMpoSession object.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param pStream a pointer to a stream that will be added to the
    CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_addSourceStream( CTMpoSession *pMpoSession, CTStream *pStream );

//--------------------------------------------------------------------------
/**
    @brief
    Creates an encoder that can be used to add an individual (Jpeg) image to
    a CTMpoSession/MPO file.

    This function provides an alternative way to add an image to a
    CTMpoSession/MPO file. Given the created encoder, an image is added
    to the MPO file by calling caps_renderToEncoder().

    The rendered images will be arranged in the same order that the encoders
    are created.

    An encoder created with this function should not be manually destroyed, but is owned by the
    CTMpoSession, and will be freed when the session is destroyed.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param[out] ppEncoder A pointer to a variable of the type: (CTEncoder *)
    On a successful call, the object will be created.

    @see caps_renderToEncoder()

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_createJpegEncoder( CTMpoSession *pMpoSession, CTEncoder **ppEncoder );

//--------------------------------------------------------------------------
/**
    @brief
    Gets an individual image from a CTMpoSession object, via a stream.

    The ownership of the stream will remain with the CTMpoSession object.
    Streams that are created with this method, will be cleaned up when the
    CTMpoSession is destroyed.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param ppStream A pointer to a variable of the type: (CTStream *).
    On a successful call, the object will be created.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getStream( CTMpoSession *pMpoSession, CTuint32 index, CTStream **ppStream );

//--------------------------------------------------------------------------
/**
    @brief
    Render a CTMpoSession to an output stream.

    All settings (i.e. tags and attribute values) and images added to the
    CTMpoSession will be written, via the provided stream, to a newly
    created MPO file.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param pOutStream A pointer to a stream, which the CTMpoSession object
    will be rendered/written to.

    @param[in,out] ppIterator If a valid pointer, to a variable of the type:  (CTIterator *),
    is provided, an iterator object will be created (see: @ref caps_iterators).
    @n
    If @c NULL is passed, the operation will be completed before this function returns.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_finalize( CTMpoSession *pMpoSession, CTStream *pOutStream, CTIterator **ppIterator );

//--------------------------------------------------------------------------
/**
    @brief
    Tests if a tag exists or not.

    For an explanation of the purpose and use of a tag, the user is
    advised to read the standard document.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param tag The value of the tag that should be tested.

    @return True if the tag exists.

    @since 5.0
*/
CTbool ctmposession_tagExists( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 tag );

//--------------------------------------------------------------------------
/**
    @brief
    Gets the @c NumberOfImages value.

    This value is typically only present in the first stream. It's
    not possible to set or remove this value directly through the API.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pNumImages A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getNumberOfImages( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 *pNumImages );

//--------------------------------------------------------------------------
/**
    @brief
    Sets the @c TotalFrames value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param totalFrames The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setTotalFrames( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 totalFrames );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c TotalFrames value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pTotalFrames A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getTotalFrames( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 *pTotalFrames );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c TotalFrames value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeTotalFrames( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c MPIndividualNum value.

    This value is set automatically when creating a new MPO file.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pIndNum A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getMPIndividualNum( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 *pIndNum );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c PanOrientation value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param panOrient The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setPanOrientation( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 panOrient );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c PanOrientation value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pPanOrient A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getPanOrientation( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 *pPanOrient );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c PanOrientation value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removePanOrientation( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c PanOverlap_H value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param panOverlap_H The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setPanOverlap_H( CTMpoSession *pMpoSession, CTuint32 index, CTRational panOverlap_H );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c PanOverlap_H value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pPanOverlap_H A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getPanOverlap_H( CTMpoSession *pMpoSession, CTuint32 index, CTRational *pPanOverlap_H );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c PanOverlap_H value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removePanOverlap_H( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c PanOverlap_V value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param panOverlap_V The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setPanOverlap_V( CTMpoSession *pMpoSession, CTuint32 index, CTRational panOverlap_V );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c PanOverlap_V value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pPanOverlap_V A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getPanOverlap_V( CTMpoSession *pMpoSession, CTuint32 index, CTRational *pPanOverlap_V );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c PanOverlap_V value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removePanOverlap_V( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c BaseViewpointNum value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param baseViewpoint The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setBaseViewpointNum( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 baseViewpoint );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c BaseViewpointNum value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pBaseViewpoint A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getBaseViewpointNum( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 *pBaseViewpoint );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c BaseViewpointNum value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeBaseViewpointNum( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c ConvergenceAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param convAngle The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setConvergenceAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational convAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c ConvergenceAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pConvAngle A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getConvergenceAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pConvAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c ConvergenceAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeConvergenceAngle( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c BaselineLength value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param baseLen The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setBaselineLength( CTMpoSession *pMpoSession, CTuint32 index, CTRational baseLen );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c BaselineLength value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pBaseLen A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getBaselineLength( CTMpoSession *pMpoSession, CTuint32 index, CTRational *pBaseLen );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c BaselineLength value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeBaselineLength( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c VerticalDivergence value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param vertDiv The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setVerticalDivergence( CTMpoSession *pMpoSession, CTuint32 index, CTSRational vertDiv );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c VerticalDivergence value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pVertDiv A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getVerticalDivergence( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pVertDiv );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c VerticalDivergence value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeVerticalDivergence( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c AxisDistance_X value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param axDist_X The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setAxisDistance_X( CTMpoSession *pMpoSession, CTuint32 index, CTSRational axDist_X );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c AxisDistance_X value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pAxDist_X A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getAxisDistance_X( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pAxDist_X );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c AxisDistance_X value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeAxisDistance_X( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c AxisDistance_Y value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param axDist_Y The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setAxisDistance_Y( CTMpoSession *pMpoSession, CTuint32 index, CTSRational axDist_Y );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c AxisDistance_Y value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pAxDist_Y A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getAxisDistance_Y( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pAxDist_Y );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c AxisDistance_Y value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeAxisDistance_Y( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c AxisDistance_Z value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param axDist_Z The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setAxisDistance_Z( CTMpoSession *pMpoSession, CTuint32 index, CTSRational axDist_Z );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c AxisDistance_Z value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pAxDist_Z A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getAxisDistance_Z( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pAxDist_Z );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c AxisDistance_Z value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeAxisDistance_Z( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c YawAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param yawAngle The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setYawAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational yawAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c YawAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pYawAngle A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getYawAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pYawAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c YawAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeYawAngle( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c PitchAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pitchAngle The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setPitchAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational pitchAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c PitchAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pPitchAngle A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getPitchAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pPitchAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c PitchAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removePitchAngle( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c RollAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param rollAngle The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setRollAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational rollAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c RollAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pRollAngle A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getRollAngle( CTMpoSession *pMpoSession, CTuint32 index, CTSRational *pRollAngle );
//--------------------------------------------------------------------------

/**
    @brief
    Removes the @c RollAngle value.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_removeRollAngle( CTMpoSession *pMpoSession, CTuint32 index );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c "Individual Image Attribute" value in the @c MPEntry tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param attribute The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setIndividualImageAttribute( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 attribute );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c "Individual Image Attribute" value in the @c MPEntry tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pAttribute A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getIndividualImageAttribute( CTMpoSession *pMpoSession, CTuint32 index, CTuint32 *pAttribute );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c "Dependent Image 1 Entry Number" value in the @c MPEntry tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param depImage1 The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setDependentImage1EntryNumber( CTMpoSession *pMpoSession, CTuint32 index, CTuint16 depImage1 );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c "Dependent Image 1 Entry Number" value in the @c MPEntry tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pDepImage1 A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getDependentImage1EntryNumber( CTMpoSession *pMpoSession, CTuint32 index, CTuint16 *pDepImage1 );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c "Dependent Image 2 Entry Number" value in the @c MPEntry tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param depImage2 The value it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setDependentImage2EntryNumber( CTMpoSession *pMpoSession, CTuint32 index, CTuint16 depImage2 );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c "Dependent Image 2 Entry Number" value in the @c MPEntry tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pDepImage2 A valid pointer which content will be set to the
    requested value.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getDependentImage2EntryNumber( CTMpoSession *pMpoSession, CTuint32 index, CTuint16 *pDepImage2 );
//--------------------------------------------------------------------------

/**
    @brief
    Sets the @c "Individual Image Unique ID" value in the @c ImageUIDList tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param pUID A pointer to the null terminated string it should be set to.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_setIndividualImageUniqueID( CTMpoSession *pMpoSession, CTuint32 index, CTuint8 *pUID );
//--------------------------------------------------------------------------

/**
    @brief
    Gets the @c "Individual Image Unique ID" value in the @c ImageUIDList tag.

    @param pMpoSession A valid pointer to a CTMpoSession object.

    @param index An individual image within the CTMpoSession object.

    @param ppUID A valid pointer which content will be set to the
    address of the null terminated string representing the UID.

    @return CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT ctmposession_getIndividualImageUniqueID( CTMpoSession *pMpoSession, CTuint32 index, CTuint8 **ppUID );
//--------------------------------------------------------------------------

/** @} */

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( CTMPOSESSION_H )
