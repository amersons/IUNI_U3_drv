/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    � 2000-2009 Scalado AB. All rights reserved.                             .
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

#ifndef FM_SPEEDVIEW_SESSION_H
#define FM_SPEEDVIEW_SESSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fm_speedview_defs.h"
#include "caps_base.h"

//=============================================================================
/**
    @ingroup fm_speedview_api
    @file fm_speedview_session.h
    @brief Defines the spmo usage for CTSession acceleration
    Caps Feature Module: @a SpeedView
*/
//=============================================================================
/**
    @addtogroup fm_speedview_api
    @{
*/
//-----------------------------------------------------------------------------

/**
    @brief 
    Start new session with speedview.

    @param[in] pStream 
    A stream pointer specifying a stream containing image data. The stream
    is not copied, and must stay alive while using it as source.

    @param[in] format 
    The format of the image data contained in the file. Only IMAGE_FORMAT_JPEG
    is supported in the current version.

    @param[in] pSpmo 
    Pointer to an Spmo object.
    NOTE: The Spmo must not be destroyed while outSession is active.

    @param[in] verificationMode 
    States which mode to use in the verification process to verify that the 
    SPMO is coherent with the image data.

    @param[out] pSession 
    Pointer to a handle which will receive the constructed session. 
    If construction fails this argument is NULL. 

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8 

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_createSessionWithSpmo( CTStream* pStream,
                                    IMAGE_FORMAT_SPEC format, 
                                    const CTSpmo* pSpmo,
                                    SPMO_VERIFICATION_MODE verificationMode,
                                    CTSession* pSession );
//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source image of the given session to the specified image
    stream with speedview.

    @param[in] session
    Handle to a session.

    @param[in] pStream 
    A stream pointer specifying a stream containing image data. The stream
    is not copied, and must stay alive while using it as source.

    @param[in] format 
    The format of the image data contained in the file. Only IMAGE_FORMAT_JPEG
    is supported in the current version.

    @param[in] pSpmo 
    Pointer to an Spmo object.
    NOTE: The Spmo must not be destroyed while outSession is active or source 
    image is changed.

    @param[in] verificationMode 
    States which mode to use in the verification process to verify that the 
    Spmo is coherent with the image data. Note that the Spmo must have a 
    checksum inserted if the verification is enabled, otherwise, 
    CERR_DATA_CORRUPT will be returned.

    In CAPS 3.7 the checksum is calculated when the SPMO is created.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setSourceImage()\n
    caps_setSourceImageFile()\n
    caps_setSourceImageBuffer()\n

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_setSourceImageWithSpmo( CTSession session, 
                                     CTStream* pStream, 
                                     IMAGE_FORMAT_SPEC format, 
                                     CTSpmo* pSpmo, 
                                     SPMO_VERIFICATION_MODE verificationMode );

//-----------------------------------------------------------------------------
/**
    @brief 
    Start new session with speedview.

    @param filename 
    The file system path to the file.

    @param format 
    The format of the image data contained in the file. Only IMAGE_FORMAT_JPEG
    is supported in the current version.

    @param spmo 
    Pointer to Spmo.
    NOTE: The Spmo must not be destroyed while outSession is active.

    @param verificationMode 
    States which mode to use in the verification process to verify that the 
    Spmo is coherent with the image data. Note that the Spmo must have a 
    checksum inserted if the verification is enabled, otherwise, 
    CERR_DATA_CORRUPT will be returned.

    In CAPS 3.7 the checksum is calculated when the SPMO is created.

    @param outSession 
    Pointer to a handle which will receive the constructed session. 
    If construction fails this argument is NULL. 

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_spmoNewSessionWithFileHandle();\n
    caps_spmoNewSessionWithBuffer()\n

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoNewSessionWithFile( const DCHAR* filename, 
    IMAGE_FORMAT_SPEC format, 
    const CTSpmo* spmo,
    SPMO_VERIFICATION_MODE verificationMode,
    CTSession* outSession );

//-----------------------------------------------------------------------------

/**
    @brief 
    Start new session with speedview.

    @param handle 
    Address of an open CTFile object with read access. This file handle must
    stay open during the entire lifetime of the session. Closing the file
    handle before caps_destroySession() will likely result in access violation
    errors.

    @param format 
    The format of the image data contained in the file. Only IMAGE_FORMAT_JPEG
    is supported in the current version.

    @param spmo 
    Pointer to Spmo.
    NOTE: The Spmo must not be destroyed while outSession is active.

    @param verificationMode 
    States which mode to use in the verification process to verify that the 
    Spmo is coherent with the image data. Note that the Spmo must have a 
    checksum inserted if the verification is enabled, otherwise, 
    CERR_DATA_CORRUPT will be returned.

    In CAPS 3.7 the checksum is calculated when the SPMO is created.

    @param outSession 
    Pointer to a handle which will receive the constructed session. 
    If construction fails this argument is NULL. 

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_spmoNewSessionWithFile()\n
    caps_spmoNewSessionWithBuffer()\n

    @since 3.7 

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoNewSessionWithFileHandle( const CTFile* handle, 
    IMAGE_FORMAT_SPEC format, 
    const CTSpmo* spmo,
    SPMO_VERIFICATION_MODE verificationMode,
    CTSession* outSession );

//-----------------------------------------------------------------------------

/**
    @brief 
    Start new session with speedview. Note: as the entire jpeg image is read 
    into memory, caps_spmoNewSessionWithFile() should be used if possible for 
    optimal performance.

    @param buffer
    A @c CTBuffer pointer specifying a buffer containing image data. The buffer
    is not copied, and must stay alive while using it as source.

    @param format 
    The format of the image data contained in the file. Only IMAGE_FORMAT_JPEG
    is supported in the current version.
    @param spmo 
    Pointer to Spmo.
    NOTE: The Spmo must not be destroyed while outSession is active.

    @param verificationMode 
    States which mode to use in the verification process to verify that the 
    Spmo is coherent with the image data. Note that the Spmo must have a 
    checksum inserted if the verification is enabled, otherwise, 
    CERR_DATA_CORRUPT will be returned.

    In CAPS 3.7 the checksum is calculated when the SPMO is created.

    @param outSession 
    Pointer to a handle which will receive the constructed session. 
    If construction fails this argument is NULL. 

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_spmoNewSessionWithFile();\n
    caps_spmoNewSessionWithFileHandle();\n

    @since 3.6

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoNewSessionWithBuffer( const CTBuffer* buffer, 
    IMAGE_FORMAT_SPEC format, 
    const CTSpmo* spmo,
    SPMO_VERIFICATION_MODE verificationMode,
    CTSession* outSession );

//-----------------------------------------------------------------------------
/** @} */
// 'fm_speedview_session'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_SPEEDVIEW_SESSION_H )
