/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
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

#ifndef CAPS_BASE_H
#define CAPS_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "caps_types.h"
#include "caps_iterator.h"
#include "ctstream.h"
#include "ctencoder.h"
#include "ctdecoder.h"
#include "ctbitmap.h"


//=============================================================================
/**
    @file caps_base.h
    @brief This header defines the public interface of the CAPS Base API.
    @ingroup caps_baseapi_basicops
*/
//=============================================================================
/**
    @addtogroup caps_baseapi
    @par Notable conventions
    All functions of the CAPS API return errorcodes, except for
    destruction interfaces which by design cannot fail.\n\n

    @par
    Due to the above convention, if a construction interface fails, it always
    uses the return value to propagate the error back to the caller and the
    constructed object is always passed back to the caller through an output
    argument.

    @par Design By Contract
    CAPS is implemented by the so called "Design by contract" principle.
    All API functions handle invalid user input by returning the error code
    @c CERR_INVALID_PARAMETER. This error is returned as an alternative to
    triggering an assert/breakpoint and should not be treated as "normal"
    errors which can be reported and recovered from. Since no implicit
    execution break is performed by CAPS in unrecoverable error cases it
    is essential that all error codes returned from the API are handled
    properly.
*/
//-----------------------------------------------------------------------------
/**
    @addtogroup caps_baseapi_basicops
    @brief Basic operations provided by the CAPS Imaging Engine module.
    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the release version of the API.

    @return
    The version as a static constant null-terminated string.

    @since 3.0
*/
SCBIMPORT const DCHAR* caps_getVersion(void);
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the image type from the file extension.

    @param pFilename
    The filesystem path to the file.

    @param[out] pFormat
    Contains the detected image type if the function returns CERR_OK.

    @return
    - @c CERR_OK if function succeds and format is identified.
    - @c CERR_UNSUPPORTED_IMAGE if function succeds and format isn't recognized.
    - An error code, if the function fails (i.e @c CERR_MEMALLOC_FAILED).
    .

    @sa
    caps_getImageType()\n

    @since 3.2
*/
SCBIMPORT CRESULT caps_getImageTypeFromExt( const DCHAR *pFilename,
                                            CTImageFormat *pFormat );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the image type from the file header.

    @param pStream
    A pointer to a stream comtaining an image.

    @param[out] pFormat
    Contains the detected image type if the function returns CERR_OK.

    @note This function will restores the stream position to where it started reading,
    so the stream may safely be used in subsequent calls.

    @return
    - @c CERR_OK if function succeds and format is identified
    - @c CERR_UNSUPPORTED_IMAGE if function succeds and format isn't recognized.\n
    - An error code, if the function fails (i.e @c CERR_MEMALLOC_FAILED).
    .

    @sa
    caps_getImageTypeFromExt()\n

    @since 3.8
*/
SCBIMPORT CRESULT caps_getImageType( CTStream *pStream, CTImageFormat *pFormat );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the image type from the file header.

    @param pFilename
    The filesystem path to the file.

    @param[out] pFormat
    Contains the detected image type if the function returns CERR_OK.

    @return
    - @c CERR_OK if function succeds and format is identified
    - @c CERR_UNSUPPORTED_IMAGE if function succeds and format isn't recognized.\n
    - An error code, if the function fails (i.e @c CERR_MEMALLOC_FAILED).
    .

    @sa
    caps_getImageTypeFromExt()\n
    caps_getImageType()\n
    caps_getImageTypeFromHdrMem()\n
    caps_getImageTypeFromHdrFileHandle()\n

    @since 3.4
*/
SCBIMPORT CRESULT caps_getImageTypeFromHdrFile( const DCHAR *pFilename,
                                                CTImageFormat *pFormat );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the image type from the file header.

    @param pHandle
    A handle to a file with read permissions.

    @param[out] pFormat
    Contains the detected image type if the function returns CERR_OK.
    NOTE: Currently only SRCIMG_FORMAT_UNDEFINED or SRCIMG_FORMAT_JPEG_BASELINE
    are returned.

    @return
    - @c CERR_OK if function succeds and format is identified
    - @c CERR_UNSUPPORTED_IMAGE if function succeds and format isn't recognized.\n
    - An error code, if the function fails (i.e @c CERR_MEMALLOC_FAILED).
    .

    @sa
    caps_getImageTypeFromExt()\n
    caps_getImageType() \n
    caps_getImageTypeFromHdrMem()\n
    caps_getImageTypeFromHdrFile()\n

    @since 3.4
*/
SCBIMPORT CRESULT caps_getImageTypeFromHdrFileHandle( CTFile *pHandle,
                                                      CTImageFormat *pFormat);
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the image type from the file header.

    @param pBuffer
    A pointer to a buffer containing the file.

    @param[out] pFormat
    Contains the detected image type if the function returns CERR_OK.

    @return
    - @c CERR_OK if function succeds and format is identified
    - @c CERR_UNSUPPORTED_IMAGE if function succeds and format isn't recognized.\n
    - An error code, if the function fails (i.e @c CERR_MEMALLOC_FAILED).
    .

    @sa
    caps_getImageTypeFromExt()\n
    caps_getImageType()\n
    caps_getImageTypeFromHdrFile()\n
    caps_getImageTypeFromHdrFileHandle()\n

    @since 3.4
*/
SCBIMPORT CRESULT caps_getImageTypeFromHdrMem( const CTBuffer *pBuffer,
                                               CTImageFormat *pFormat);

//-----------------------------------------------------------------------------
/**
    @brief
    Create a CTDecoder from a given image format

    @param pStream 
    A pointer to a CTStream object containing an image, opened with read access.
    If this function is successful, the stream must be alive, and must not be
    manipulated with, during the lifetime of the CTDecoder.

    @param format
    The image format of the stream.
    The following formats are supported:
    @b JPEG, @b PNG, @b GIF, @b BMP, @b WBMP, @b TIFF

    @param[out] ppDecoder The created decoder.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_getImageType()
    .

    @since 3.8.2 R01

*/
SCBIMPORT CRESULT caps_createDecoderFromFormat( CTStream *pStream,
                                                CTImageFormat format,
                                                CTDecoder** ppDecoder );

//-----------------------------------------------------------------------------
/**
    @brief
    Create a CTEncoder from a given CTImageFormat

    @param pStream 
    A pointer to a stream opened with write access.
    If this function is successful, the stream must be alive, and must not be
    manipulated with, during the lifetime of the CTEncoder.

    @param format
    The desired image format that the encoder should output to.
    The following formats are supported:
    @b JPEG

    @param[out] ppEncoder The created encoder.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8.2 R01

*/
SCBIMPORT CRESULT caps_createEncoderFromFormat( CTStream *pStream,
                                                CTImageFormat format,
                                                CTEncoder** ppEncoder );

//-----------------------------------------------------------------------------
/**
    @brief
    Initiates a new session using an image from the stream as input.

    @param pStream
    A pointer to a CTStream object containing an image. This stream object
    cannot be used, or freed, by the caller until the session has been
    destroyed, or until the source used by the session has been changed
    using: caps_setSourceImage().

    @param format
    The image format of the stream.

    @param[out] session
    Pointer to a handle which will receive the constructed session. If
    construction fails this argument is NULL.

    The following image formats are supported:
    @b JPEG, @b PNG, @b GIF, @b BMP, @b WBMP, @b TIFF

    @note
    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    If an unknown image format is encountered the task is passed over to the
    an external decoder function. See caps_extDecode() for more
    information.
    
    For creation of streams see:
    - @ref scb_ctstream_buffer
    - @ref scb_ctstream_file
    - @ref scb_ctstream_interface
    .

    @remark
    By default, when @c caps_newSession is called, the entire Jpeg image is
    read into memory. This is usually desired since it provides best (speed)
    performance, but is not always neccessary. In particular, if
    a @c CTSession is created from a buffer stream, this would duplicate the
    memory buffer. To disable the caching in this case, the function:
    caps_uthSetPrefetchFlag() should be called with the @c enablePrefetch
    parameter set to @c false.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_uthSetPrefetchFlag()
    - caps_createSessionFromDecoder()
    - caps_newSessionWithRaw()
    - caps_newSessionWithColor()
    - caps_getImageType()

    @since 3.8
*/
SCBIMPORT CRESULT caps_createSession( CTStream *pStream,
                                      IMAGE_FORMAT_SPEC format,
                                      CTSession *session );

//-----------------------------------------------------------------------------
/**
    @brief
    Initiates a new session using a CTDecoder as input.

    @param pDecoder
    A pointer to a CTDecoder object containing an image. This decoder object
    cannot be used, or freed, by the caller until the session has been
    destroyed, or until the source used by the session has been changed.

    @param[out] session
    Pointer to a handle which will receive the constructed session. If
    construction fails this argument is NULL.

    @note
    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_createDecoderFromFormat()
    - caps_getImageType()
    - caps_newSessionWithRaw()
    - caps_newSessionWithColor()
    .

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT caps_createSessionFromDecoder( CTDecoder *pDecoder,
                                                CTSession *session );

//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source image of the given session to the specified decoder.

    @param session
    Handle to a session.

    @param pDecoder
    A pointer to a CTDecoder object containing an image. This decoder object
    cannot be used, or freed, by the caller until the session has been
    destroyed, or until the source used by the session has been changed.

    @attention
    This function is not intended to be used iteratively in performance
    critical realtime scenarios. It is intended to make the task of changing
    source easier, while preserving current settings and effects.

    @note
    Calling this function will reset the @c enablePrefetch flag to
    @c true (default); see: caps_uthSetPrefetchFlag()
    If this is not desired, @c caps_uthSetPrefetchFlag must be called
    with the appropriate parameters after each call
    to @c caps_setSourceImage.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_createSessionFromDecoder()
    - caps_setSourceImage()
    .

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT caps_setSourceDecoder( CTSession session,
                                         CTDecoder *pDecoder );


//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source image of the given session to the specified image
    stream.

    @param session
    Handle to a session.

    @param pStream
    A pointer to a stream containing an image. This stream object cannot be
    used or freed by anyone until the session has been destroyed, or
    until the source used by the session has been changed
    ( using caps_setSourceImage ).

    @param format
    The image format of the stream.

    The following image formats are supported:
    @b JPEG, @b PNG, @b GIF, @b BMP, @b WBMP, @b TIFF

    @attention
    This function is not intended to be used iteratively in performance
    critical realtime scenarios. It is intended to make the task of changing
    source easier, while preserving current settings and effects.

    @note
    Calling this function will reset the @c enablePrefetch flag to
    @c true (default); see: caps_uthSetPrefetchFlag()
    If this is not desired, @c caps_uthSetPrefetchFlag must be called
    with the appropriate parameters after each call
    to @c caps_setSourceImage.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - caps_createSession()
    - caps_uthSetPrefetchFlag()
    - caps_getImageTypeFromExt()
    - caps_getImageType()
    - caps_setSourceImage()
    .

    @since 3.8
*/
SCBIMPORT CRESULT caps_setSourceImage( CTSession session,
                             CTStream *pStream,
                             IMAGE_FORMAT_SPEC format );

//-----------------------------------------------------------------------------
/** 
    @brief 
    Speed up the first time a CTSession is rendered, using speedtags index.

    @param session
    Handle to a session.

    @param pIndexStream
    A pointer to a stream containing a speedtags image index.
    This stream object cannot be used or freed by anyone until the session has
    been destroyed, or until the source used by the session has been changed 
    ( using caps_setSourceImage ).

    @remarks
    The currently supported image formats are:
    @li JPEG 

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 5.2
*/
SCBIMPORT CRESULT caps_setSourceImageIndex( CTSession session,
                                            CTStream* pIndexStream );

//-----------------------------------------------------------------------------

/**
    @brief
    Initiates a new session using an image from the filesystem as input.


    @param filename
    The filesystem path to the file.

    @param format
    The image format of the file.

    @param[out] session
    Pointer to a handle which will receive the constructed session. If
    construction fails this argument is NULL.

    @remarks

    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    The currently supported image formats are:

    @li JPEG
    @li PNG
    @li GIF
    @li BMP
    @li WBMP

    If an unknown image format is encountered the task is passed over to the
    an external decoder function. See caps_extDecode() for more
    information.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    CRESULT res;
    CTSession session;
    //Start a session from a PNG image from file
    res = caps_newSessionWithFile(_D("png1.png"), IMAGE_FORMAT_PNG, &session);
    //..
    //Add effects and/or do other operations
    //..
    caps_destroySession(session);

    @endcode

    @sa
    caps_createSession()\n
    caps_newSessionWithFileHandle()\n
    caps_newSessionWithBuffer()\n
    caps_newSessionWithRaw()\n
    caps_newSessionWithColor()\n
    caps_getImageTypeFromHdrFile()


    @since 3.0 (parameters modified in 3.2)
*/
SCBIMPORT CRESULT caps_newSessionWithFile( const DCHAR* filename,
                                           IMAGE_FORMAT_SPEC format,
                                           CTSession* session );
//-----------------------------------------------------------------------------
/**
    @brief
    Initiates a new session using an image from an open file handle.


    @param handle
    Address of an open CTFile object with read access. This file handle must
    stay open during the entire lifetime of the session. Closing the file
    handle before caps_destroySession() will likely result in access violation
    errors.

    @param format
    The image format of the file.

    @param[out] session
    Pointer to a handle which will receive the constructed session. If
    construction fails this argument is NULL.

    @remarks

    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    The currently supported image formats are:

    @li JPEG
    @li PNG
    @li GIF
    @li BMP
    @li WBMP


    If an unknown image format is encountered the task is passed over to the
    an external decoder function. See caps_extDecode() for more
    information.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    CTFile* file1 = 0;
    CTFile* file2 = 0;
    CTSession session;
    CTSize dims = {0};
    //Open source file, get a file handle
    res = oslfile_open(_D("jpeg.jpg"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    res = caps_newSessionWithFileHandle(file, IMAGE_FORMAT_JPEG, &session);
    //Example: Flip image
    res = caps_beginFlip(session);
    res = caps_setFlip(session, CAPS_FLIP_VERTICAL);
    caps_endFlip (CTSession session)
    res = caps_getSourceImageSize(session, &dims);
    //Open destination file, get a file handle
    res = oslfile_open(_D("outJpeg.jpg"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file2);
    res = caps_renderToFileHandle(session, file2,
        dims, CAPS_OUTPUT_STRETCH, IMAGE_FORMAT_JPEG, 0);
    caps_destroySession(session);

    @endcode

    @sa
    caps_createSession()\n
    caps_newSessionWithFile()\n
    caps_newSessionWithBuffer()\n
    caps_newSessionWithRaw()\n
    caps_newSessionWithColor()\n
    caps_getImageTypeFromExt()\n
    caps_getImageTypeFromHdrFileHandle()

    @since 3.4 (Support more image types in 3.8)
*/
SCBIMPORT CRESULT caps_newSessionWithFileHandle( const CTFile* handle,
                                                 IMAGE_FORMAT_SPEC format,
                                                 CTSession* session );
//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source image of the given session to the specified image
    file.

    @param session
    Handle to a session.

    @param filename
    The filesystem path to the file.

    @param format
    The image format of the file.

    @remarks

    IMPORTANT: This function is not intended to be used iteratively in
    performance critical realtime scenarios. It is intended to make the task
    of changing source while preserving current settings and effects easier.
    \n\n

    The currently supported image formats are:

    @li JPEG
    @li PNG
    @li GIF
    @li BMP
    @li WBMP

    See documentation of caps_newSessionWithFile() for more information.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    CRESULT res;
    CTSession session;
    CTSize size = {1024, 768};
    //Start a session from a JPEG image from file
    res = caps_newSessionWithFile(_D("jpeg1.jpg"), IMAGE_FORMAT_JPEG, &session);

    //Example: Add antique
    res = caps_applyAntique(session);
    //Render session image to file with Antique applied
    res = caps_renderToFile(session, _D("jpeg1_antique.jpg"), size,
        CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);
    //Change session image
    res = caps_setSourceImageFile(session,
        _D("jpeg2.jpg"), IMAGE_FORMAT_JPEG);
    //Render jpeg2.jpg to file with antique applied
    res = caps_renderToFile(session, _D("jpeg2_antique.jpg"), size,
        CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);

    caps_destroySession(session);

    @endcode

    @sa
    caps_getImageTypeFromExt()\n
    caps_getImageTypeFromHdrFile()\n
    caps_setSourceImage()\n
    caps_setSourceImageBuffer()\n

    @since 3.1 (parameters modified in 3.2)
*/
SCBIMPORT CRESULT caps_setSourceImageFile( CTSession session, 
                                           const DCHAR* filename,
                                           IMAGE_FORMAT_SPEC format );
//-----------------------------------------------------------------------------
/**
    @brief
    Initiates a new session using a buffer with image data.

    @param buffer
    A @c CTBuffer pointer specifying a buffer containing image data. The buffer
    is not copied, and must stay alive while using it as source.

    @param format
    The format of the image data contained in @c buffer. This value can be one
    of the @c ::CTImageFormat values supported by CAPS internally, or it can
    specify a value not known to CAPS and thereby invoking the external decoder
    interface. In such case the value is passed on to the external decoder. See
    caps_extDecode() for more information.

    @param[out] session
    Pointer to a handle which will receive the constructed session. If
    construction fails this argument is NULL.

    @remarks

    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    The internally supported image formats are described in the enumeration
    type @c ::CTImageFormat. External image format values must be located
    outside the range @c IMAGE_FORMAT_RANGE_MIN to @c IMAGE_FORMAT_RANGE_MAX to avoid
    conflicts with the internal image format ranges.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    CTBuffer* buffer;
    CRESULT res;
    CTFile* file;
    CTuint32 fileSize;
    CTSession session;

    res = oslfile_open(_D("jpeg.jpg"), FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    fileSize = oslfile_size(file);
    caps_createBuffer(fileSize, &buffer);
    res = oslfile_read(file, buffer->data, buffer->size);
    oslfile_close(file);
    res = caps_newSessionWithBuffer(buffer, IMAGE_FORMAT_JPEG, &session);
    //...
    //...
    caps_destroySession(session);
    caps_destroyBuffer(buffer);

    @endcode

    @sa
    caps_createSession()\n
    caps_newSessionWithFile()\n
    caps_newSessionWithFileHandle()\n
    caps_newSessionWithRaw()\n
    caps_newSessionWithColor()
    caps_getImageTypeFromHdrMem()\n

    @since 3.0
*/
SCBIMPORT CRESULT caps_newSessionWithBuffer( const CTBuffer* buffer,
                                             IMAGE_FORMAT_SPEC format,
                                             CTSession* session );
//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source image of the given session to the specified image
    buffer.

    @param session
    Handle to a session.

    @param buffer
    A @c CTBuffer pointer specifying a buffer containing image data. The buffer
    is not copied, and must stay alive while using it as source.

    @param format
    The format of the image data contained in @c buffer. This value can be one
    of the @c ::CTImageFormat values supported by CAPS internally, or it can
    specify a value not known to CAPS and thereby invoking the external decoder
    interface. In such case the value is passed on to the external decoder. See
    caps_extDecode() for more information.

    @remarks

    IMPORTANT: This function is not intended to be used iteratively in
    performance critical realtime scenarios. It is intended to make the task
    of changing source while preserving current settings and effects easier.
    \n\n

    caps_signalSessionEvent() with CTSessionEvent = EVENT_SOURCEDATA_CHANGE
    should be called after this function to notify that the source data have changed.

    See documentation of caps_newSessionWithBuffer() for more information.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_newSessionWithBuffer()\n
    caps_signalSessionEvent()

    @since 3.1
*/
SCBIMPORT CRESULT caps_setSourceImageBuffer( CTSession session, 
                                             const CTBuffer* buffer,
                                             IMAGE_FORMAT_SPEC format );
//-----------------------------------------------------------------------------
/**
    @brief
    Initiates a new session using raw image data.

    @param image
    A pointer to a @c CTImage object containing the raw image data with
    associated information. The raw image data is not copied by the
    session and must stay alive while using it as source.

    @param[out] session
    Pointer to a @c CTSession handle wich will receive the constructed
    session. If construction fails this argument is NULL.

    @attention
    The raw image data must be in one of the valid (input) color formats,
    specified in: @ref supported_colorformats

    @remarks
    The color format is specified by the @c CTImage::format member.

    \n\n
    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    @return
    @c CERR_OK if successful or a specific error code upon failure, in which
    case both the @c session and @c image arguments are left unmodified.

    @sa
    caps_newSessionWithFile()\n
    caps_newSessionWithFileHandle()\n
    caps_newSessionWithBuffer()\n
    caps_newSessionWithColor()

    @code

    //Example: Convert from raw YUV file to raw RGB888 file
    CTSession sess;
    CRESULT res = CERR_OK;
    CTuint32 fileSize = 0;
    CTuint32 bitSize = 0;
    CTSize dims = {320, 240};
    CTImage* image = 0;
    CTImage* outImage = 0;
    CTFile* file = 0;

    res = oslfile_open(_D("yuv422_Y1UY2V_320x240.raw"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    fileSize = oslfile_size(file);
    caps_createBuffer(fileSize, &buffer);
    oslfile_read(file, buffer->data, buffer->size);
    oslfile_close(file);

    bitSize = caps_pixelBitSize(CM_YUV422_Y1UY2V);
    res = caps_createImage(buffer, dims, dims.w * (bitSize / 8),
        CM_YUV422_Y1UY2V, &image);

    res = caps_newSessionWithRaw(image, &sess);

    bitSize = caps_pixelBitSize(CM_RGB888);
    res = caps_createImage(0, dims, dims.w * (bitSize / 8),
        CM_RGB888, &outImage);
    res = caps_renderAsRawToBuffer(sess, outImage, CAPS_OUTPUT_STRETCH, 0);

    res = oslfile_open(_D("rgb888_320x240.raw"),
        FOF_ACCESS_WRITE | FOF_MODE_BINARY, &file);
    oslfile_write(file, outImage->pixels->data, outImage->pixels->size);
    oslfile_close(file);

    caps_destroyImage(image);
    caps_destroyImage(outImage);
    caps_destroySession(sess);

    @endcode

    @since 3.0
*/
SCBIMPORT CRESULT caps_newSessionWithRaw( const CTImage* image, 
                                          CTSession* session );

//-----------------------------------------------------------------------------
/**
    @brief
    Initiates a new session using raw image data.

    @param pBitmap
    A pointer to a @c CTBitmap object containing the raw image data with
    associated information. The raw image data is not copied by the
    session and must stay alive while using it as source.

    @param[out] session
    Pointer to a @c CTSession handle wich will receive the constructed
    session. If construction fails this argument is NULL.

    @attention
    The raw image data must be in one of the valid (input) color formats,
    specified in: @ref supported_colorformats

    @remarks
    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    @return
    @c CERR_OK if successful or a specific error code upon failure, in which
    case both the @c session and @c pBitmap arguments are left unmodified.

    @sa
    caps_newSessionWithFile()\n
    caps_newSessionWithFileHandle()\n
    caps_newSessionWithBuffer()\n
    caps_newSessionWithColor()

    @since 5.3
*/
SCBIMPORT CRESULT caps_newSessionWithBitmap( CTBitmap *pBitmap,
                                             CTSession *session );

//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source image of the given session to the specified raw image
    buffer.

    @param session
    Handle to a session.

    @param image
    A pointer to a @c CTImage object containing the raw image data with
    associated information. The raw image data is not copied by the
    session and must stay alive while using it as source.

    @remarks

    IMPORTANT: This function is not intended to be used iteratively in
    performance critical realtime scenarios. It is intended to make the task
    of changing source while preserving current settings and effects easier.
    \n\n

    caps_signalSessionEvent() with CTSessionEvent = EVENT_SOURCEDATA_CHANGE
    should be called after this function to notify that the source data have changed.

    See documentation of caps_newSessionWithRaw() for more information.

    @return
    @c CERR_OK if successful or a specific error code upon failure, in which
    case the @c image argument is left unmodified.

    @sa
    caps_signalSessionEvent()

    @since 3.1
*/
SCBIMPORT CRESULT caps_setSourceImageRaw( CTSession session, 
                                          const CTImage* image );

//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source image of the given session to the specified raw image
    buffer.

    @param session
    Handle to a session.

    @param pBitmap
    A pointer to a @c CTBitmap object containing the raw image data with
    associated information. The raw image data is not copied by the
    session and must stay alive while using it as source.

    caps_signalSessionEvent() with CTSessionEvent = EVENT_SOURCEDATA_CHANGE
    should be called after this function to notify that the source data have changed.

    See documentation of caps_newSessionWithRaw() for more information.

    @return
    @c CERR_OK if successful or a specific error code upon failure

    @sa
    caps_signalSessionEvent()

    @since 5.3
*/
SCBIMPORT CRESULT caps_setSourceImageBitmap( CTSession session, CTBitmap *pBitmap);

//-----------------------------------------------------------------------------
/**
    @brief
    Initiates a new session using a plain color surface as source image.

    @param color
    A @c CTColor object specifying the the surface color. The alpha channel of
    the specified color is ignored.

    @param size
    The requested size in pixels of the color surface.

    @param[out] session
    Address of a @c CTSession handle wich will receive the constructed
    session. If construction fails this argument is NULL.

    @remarks

    When the session is no longer needed it should be destroyed using
    caps_destroySession().

    @return
    @c CERR_OK if successful or a specific error code upon failure, in which
    case the @c session argument is left unmodified.

    @code

    CTColor color = {255, 0, 255, 0};
    CTSize size = {640, 480};
    CTSession session;
    //Starts a session with an green VGA sized rectangle
    res = caps_newSessionWithColor(color, size, &session);
    //...
    caps_destroySession(session);

    @endcode

    @sa
    caps_newSessionWithFile()\n
    caps_newSessionWithFileHandle()\n
    caps_newSessionWithBuffer()\n
    caps_newSessionWithRaw()

    @since 3.0
*/
SCBIMPORT CRESULT caps_newSessionWithColor( CTColor color, 
                                            CTSize size,
                                            CTSession* session );
//-----------------------------------------------------------------------------
/**
    @brief
    Changes the source of the session to a color surface of the specified size.

    @param session
    Handle to a session.

    @param color
    A @c CTColor object specifying the the surface color. The alpha channel of
    the specified color is ignored.

    @param size
    The requested size in pixels of the color surface.

    @attention
    This function is not intended to be used iteratively in
    performance critical realtime scenarios. It is intended to make the task
    of changing source while preserving current settings and effects easier.

    See documentation of caps_newSessionWithColor() for more information.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_setSourceColor( CTSession session, 
                                       CTColor color, 
                                       CTSize size );
//-----------------------------------------------------------------------------
/**
    @brief
    Destroys a previously constructed session object.

    @param session
    Handle to a session.

    @remarks

    The session handle along with all its associated data is invalid after
    calling this function. I.e all CTImage(s) and CTBuffer(s) added to the
    session with OWNERSHIP_POLICY = OWNERSHIP_CAPS.

    @since 3.0
*/
SCBIMPORT void caps_destroySession( CTSession session );
//-----------------------------------------------------------------------------
/**
    @brief
    Signals the given session about certain events.

    @param session
    Handle to a session.

    @param event
    The event signal. Can be any of the @c ::CTSessionEvent values. Refer to
    documentation of this enumeration for details.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setSourceImageRaw()

    @since 3.1
*/
SCBIMPORT CRESULT caps_signalSessionEvent( CTSession session, 
                                           CTSessionEvent event );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the source image dimensions.

    @param session
    A valid session handle.

    @param[out] size
    Pointer to a @c CTSize object which will receive the size.

    @remarks

    The source image dimensions are available directly after constructing the
    session.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_getCurrentImageSize()

    @since 3.0
*/
SCBIMPORT CRESULT caps_getSourceImageSize( CTSession session, CTSize* size );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the dimensions of the current session image.

    @param session
    A valid session handle.

    @param[out] size
    Pointer to a @c CTSize object which will receive the size.

    @remarks

    The "current" image is the result of the source image with all currently
    added effects applied to it. For example if a source image is 640x480
    in size and a cropping effect is applied which crops a rectangle of 100x100
    pixels, the current session image size will equal 100x100 pixels.

    Note that the output image size may differ from the current image size.
    It is not allowed to call this function during a rendering process.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_getSourceImageSize()

    @since 3.0
*/
SCBIMPORT CRESULT caps_getCurrentImageSize( CTSession session, CTSize* size );
//-----------------------------------------------------------------------------
/**
    @brief
    Sets the background color to use for empty blocks, or transparent portions,
    of the input image.

    @param session
    A valid session handle.

    @param color
    A @c CTColor structure defining the new background color.

    @remarks
    Background color will show through at the edges of a rendered image, when
    rendered, unless the image is stretched during rendering or perfectly 
    matches the output dimensions.

    Background color will also show through transparent (or semi-transparent)
    portions of the source image.

    The alpha information of the background color is ignored, and the color
    is considered completely opaque.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    //...
    CTSize currSize = {0};
    CTSize outSize = {0};
    CTColor color = {255, 255, 0, 0};

    res = caps_getCurrentImageSize(session, &currSize);
    //Change aspect ratio
    outSize.w = currSize.w + currSize.w / 2;
    outSize.h = currSize.h;
    res = caps_setBackgroundColor(session, color);

    //Render session to file. Resulting image will have red borders
    //to the left and to the right
    res = caps_renderToFile(session, _D("jpeg_red_borders.jpg"), outSize,
        CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);

    @endcode

    @since 3.0
*/
SCBIMPORT CRESULT caps_setBackgroundColor( CTSession session, CTColor color );
//-----------------------------------------------------------------------------
/**
    @brief
    Tell CAPS whether to blend in the background color when rendering
    from a png or gif source containing alfa data. The default setting for
    this in CAPS is TRUE, i.e. CAPS will blend in the background color.

    @param session
    A valid session handle.

    @param blendInBackground
    A @c if true, use source alpha channel to blend in background color to
    the source color channels. If false, the color channels remains untouched.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4
*/
SCBIMPORT CRESULT caps_blendBackgroundColor( CTSession session, 
                                             CTbool blendInBackground);
//-----------------------------------------------------------------------------
/**
    @brief
    Reverts the most recent undoable operation.

    @param session
    A valid session handle.

    @remarks

    Undoable operations includes all the imaging effects.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code
    //...
    CTSize screenSize = {320, 240};
    CTScreen* screen;
    CTSession sess;
    res = caps_newSessionWithFile(_D("jpeg.jpg"), IMAGE_FORMAT_JPEG, &sess);
    res = caps_createScreen(sess, screenSize, CM_RGB565, 0, &screen);
    res = caps_applyPaint(sess);
    //Render screen with Paint applied
    res = caps_renderScreen(screen, 0);
    res = caps_beginSharpness(sess);
    res = caps_setSharpness(sess, SHARP_LOW);
    //Render screen with Paint and Sharpness = SHARP_LOW applied
    res = caps_renderScreen(screen, 0);
    //Increase the strength of sharpness
    res = caps_setSharpness(sess, SHARP_HIGH);
    //Render screen with Paint and Sharpness = SHARP_HIGH applied
    res = caps_renderScreen(screen, 0);
    res = caps_endSharpness(sess);
    res = caps_beginSharpness(sess);
    res = caps_setSharpness(sess, SHARP_MAX);
    res = caps_endSharpness(sess);
    //Render screen with Paint, Sharpness = SHARP_HIGH
    //and Sharpness = SHARP_MAX applied. Note that the second
    //sharpness filter works relative to the first sharpen effect.
    res = caps_renderScreen(screen, 0);
    res = caps_applyWhiteBalance(sess, WB_CLUSTER_MODE, 0, 0, 0);
    //Render screen with Paint, Sharpness = SHARP_LOW
    //,Sharpness = SHARP_MAX and White balance applied
    res = caps_renderScreen(screen, 0);
    res = caps_undo(sess);
    //Render screen with Paint, Sharpness = SHARP_HIGH
    //and Sharpness = SHARP_MAX applied.
    res = caps_renderScreen(screen, 0);
    res = caps_undo(sess);
    //Render screen with Paint and Sharpness = SHARP_HIGH applied
    res = caps_renderScreen(screen, 0);
    res = caps_undo(sess);
    //Render screen with Paint applied
    res = caps_renderScreen(screen, 0);
    res = caps_undo(sess);
    //Render screen with no effect applied
    res = caps_renderScreen(screen, 0);
    //...
    caps_destroyScreen(screen);
    caps_destroySession(sess);
    @endcode

    @since 3.0
*/
SCBIMPORT CRESULT caps_undo( CTSession session );
//-----------------------------------------------------------------------------
/**
    @brief
    Determines if there are available operations on the undo stack.

    @param session
    A valid session handle.

    @param[out] canUndo
    Pointer to a @c CTbool value which is set to @a false if no operations
    are available for undo, otherwise it is set to @a true.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code
    CTbool canUndo;
    //...
    (void)caps_canUndo(session, &canUndo);
    if (canUndo)
    {
        res = caps_undo(session);
    }
    //...
    @endcode

    @since 3.0
*/
SCBIMPORT CRESULT caps_canUndo( CTSession session, CTbool* canUndo );
//-----------------------------------------------------------------------------
/**
    @brief
    Reverts all undoable operations performed on the session.

    @param session
    A valid session handle.

    @remarks

    This function basically invokes caps_undo() until caps_canUndo() returns
    false.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4
*/
SCBIMPORT CRESULT caps_undoAll( CTSession session );

//-----------------------------------------------------------------------------
/**
    @brief
    Renders the output to a buffer in RAW format.

    @param session
    A valid session handle.

    @param outputImage
    A @c CTImage pointer which should be pre-initialized for the render operation.
    See remarks section for details.
    Range: [0 < width, height < 16384]

    @param outputOption
    Specifies how the API should behave when resizing the image to the requested
    output size. See @c ::CAPS_OUTPUT_OPTION enumeration for details.

    @param it
    Pointer to a @c CTIterator object if the render operation should be performed
    as an iterative sequence, otherwise @c NULL. See remarks section for more
    information.

    @remarks
    The @c outputImage argument should be pre-initialized with dimensions and
    colormode (@c CTImage::dims and @c CTImage::format respectively) before passing
    it to this function. The session will regard this information as a request
    from the caller and will render the output image accordingly.

    @attention
    The @c CTImage::format member must be set to one of the valid (output) formats
    specified in: @ref supported_colorformats

    @remarks
    The @c CTImage::pixels member of @c outputImage can be treated in two ways;
    - If set to zero, the session will allocate the buffer to manage the
    output pixels. In this case the ownership of the buffer is passed over to
    the caller and should be freed when no longer needed.
    - If the buffer is previously allocated (i.e non-zero), the session uses
    the buffer as it is for the output, updating only scanline information.
    .

    @remarks
    See also caps_calculateRawSize(), calculating buffer size for specific
    dimensions and colormode.
    \n\n
    @copydoc iterative_operations

    @return
    @c CERR_OK if successful or a specific error code upon failure, in which case
    the @c outputImage argument is left unmodified. If an iterative render
    operation is currently active when calling this function, @c CERR_ILLEGAL_CALL
    is returned.

    @code
    CTSize size = {0};
    CRESULT res = CERR_OK;
    CTuint32 scanline = 0;
    CTImage* image = 0;
    CTFile* file = 0;
    CTColormode colormode = CM_RGB888;

    res = caps_getCurrentImageSize(session, &size);

    scanline = caps_pixelByteSize(colormode) * size.w;
    res = caps_createImage(0, size, scanline, colormode, &image);

    res = caps_renderAsRawToBuffer(session, image, CAPS_OUTPUT_PRESERVE_AR, 0);

    res = oslfile_open(dstFilename, FOF_ACCESS_WRITE | FOF_MODE_BINARY, &file);
    oslfile_write(file, image->pixels->data, image->pixels->size);
    oslfile_close(file);

    caps_destroyImage(image);
    @endcode

    @sa
    caps_render()\n

    @since 3.0
*/
SCBIMPORT CRESULT caps_renderAsRawToBuffer( CTSession session, 
                                            CTImage* outputImage,
                                            CAPS_OUTPUT_OPTION outputOption,
                                            CTIterator** it );

/**
    @brief
    Renders the output to a buffer in RAW format.

    @param session
    A valid session handle.

    @param pBitmap
    A @c valid CTBitmap object.
    Range: [0 < width, height < 16384]

    @param flags
    Specifies how the API should behave when rendering the image.

    @attention
    The @c Bitmap color format must be set to one of the valid (output) formats
    specified in: @ref supported_colorformats

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_render()\n

    @since 5.3
*/
SCBIMPORT CRESULT caps_renderToBitmap( CTSession session,
                                       CTBitmap *pBitmap,
                                       SCB_RENDER_OPT flags );

//-----------------------------------------------------------------------------
/**
    Renders the current session image to an encoder

    @param session
    A valid session handle.

    @param pEncoder
    A pointer to a valid encoder instance.

    @param outputDims
    Output dimensions of the image. This size specification is handled
    differently depending on the @a outputOption argument.
    Range: [0 < width, height < 16384]

    @param outputOption
    Specifies how the API should behave when sizing the image to the requested
    output size. See @c ::CAPS_OUTPUT_OPTION enumeration for details.

    @param ppIterator
    Pointer to a @c CTIterator object if the render operation should be performed
    as an iterative sequence, otherwise @c NULL. See remarks section for more
    information.

    @copydoc iterative_operations

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ILLEGAL_CALL If an iterative render operation is currently
    active when calling this function.
    .

    @sa
    - caps_createEncoderFromFormat()
    - caps_renderAsRawToBuffer()
    - caps_render()
    .

    @since 3.8.2 R01

*/
SCBIMPORT CRESULT caps_renderToEncoder( CTSession session, 
                                        CTEncoder *pEncoder, 
                                        CTSize outputDims, 
                                        CAPS_OUTPUT_OPTION outputOption,
                                        CTIterator **ppIterator );
//-----------------------------------------------------------------------------
/**
    @brief
    Renders the current session image to a stream

    @param session
    A valid session handle.

    @param pStream
    A pointer to the destination stream.

    @param outputDims
    Output dimensions of the image. This size specification is handled
    differently depending on the @a outputOption argument.
    Range: [0 < width, height < 16384]

    @param outputOption
    Specifies how the API should behave when sizing the image to the requested
    output size. See @c ::CAPS_OUTPUT_OPTION enumeration for details.

    @param outputFormat
    The format in which to encode the output image. This argument can specify
    any format of choice, but for formats not included in the
    ::CTImageFormat enumeration, a registered external encoder must exist
    which can handle it.
    Among the formats specified within the ::CTImageFormat enumeration,
    currently the only format supported for file encoding
    is @c IMAGE_FORMAT_JPEG.

    @param ppIterator
    Pointer to a @c CTIterator object if the render operation should be performed
    as an iterative sequence, otherwise @c NULL. See remarks section for more
    information.

    @copydoc iterative_operations

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ILLEGAL_CALL If an iterative render operation is currently
    active when calling this function.
    .

    @sa
    caps_renderAsRawToBuffer()\n

    @since 3.8
*/
SCBIMPORT CRESULT caps_render( CTSession session, 
                               CTStream* pStream, 
                               CTSize outputDims, 
                               CAPS_OUTPUT_OPTION outputOption,
                               IMAGE_FORMAT_SPEC outputFormat, 
                               CTIterator **ppIterator );
//-----------------------------------------------------------------------------
/**
    @brief
    Renders the current session image to file.

    @param session
    A valid session handle.

    @param filename
    Filename specifying where to store the output file.

    @param outputDims
    Output dimensions of the image. This size specification is handled
    differently depending on the @a outputOption argument.
    Range: [0 < width, height < 16384]

    @param outputOption
    Specifies how the API should behave when sizing the image to the requested
    output size. See @c ::CAPS_OUTPUT_OPTION enumeration for details.

    @param outputFormat
    The format in which to encode the output image. This argument can specify
    any format of choice, but for formats not included in the
    ::CTImageFormat enumeration, a registered external encoder must exist
    which can handle it.
    Among the formats specified within the ::CTImageFormat enumeration,
    currently the only format supported for file encoding
    is @c IMAGE_FORMAT_JPEG.

    @param it
    Pointer to a @c CTIterator object if the render operation should be performed
    as an iterative sequence, otherwise @c NULL. See remarks section for more
    information.

    @remarks
    The limit of the downscale factor varies with the aspect ratio of the 
    source image. It is also dependent on the decode quality and choice of 
    render mode. We guarantee that downscaling with factor lower or equal 
    to 256 always is possible. In most of the cases will be possible to 
    downscale even more.
    \n\n
    @copydoc iterative_operations

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ILLEGAL_CALL If an iterative render operation is currently
    active when calling this function.
    .

    @sa
    caps_render()\n
    caps_renderToFileHandle()\n
    caps_renderToBuffer()\n
    caps_renderAsRawToBuffer()\n

    @since 3.0
*/
SCBIMPORT CRESULT caps_renderToFile( CTSession session, 
                                     const DCHAR *filename,
                                     CTSize outputDims, 
                                     CAPS_OUTPUT_OPTION outputOption,
                                     IMAGE_FORMAT_SPEC outputFormat, 
                                     CTIterator** it );
//-----------------------------------------------------------------------------
/**
    @brief
    Renders the current session image to an open file handle.

    @param session
    A valid session handle.

    @param handle
    Address of an open CTFile object with write access. This file handle must
    stay open until the entire render operation has concluded.
    In particular this has to be regarded when using
    @ref iterative_operations

    @param outputDims
    Output dimensions of the image. This size specification is handled
    differently depending on the @a outputOption argument.
    Range: [0 < width, height < 16384]

    @param outputOption
    Specifies how the API should behave when sizing the image to the requested
    output size. See @c ::CAPS_OUTPUT_OPTION enumeration for details.

    @param outputFormat
    The format in which to encode the output image. This argument can specify
    any format of choice, but for formats not included in the
    ::CTImageFormat enumeration, a registered external encoder must exist
    which can handle it.
    Among the formats specified within the ::CTImageFormat enumeration,
    currently the only format supported for encoding to file handle
    is @c IMAGE_FORMAT_JPEG.

    @param it
    Pointer to a @c CTIterator object if the render operation should be performed
    as an iterative sequence, otherwise @c NULL. See remarks section for more
    information.

    @copydoc iterative_operations

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ILLEGAL_CALL If an iterative render operation is currently
    active when calling this function.
    .

    @code
    CTFile* file1 = 0;
    CTFile* file2 = 0;
    CTSession session;
    CTSize dims = {0};
    //Open source file, get a file handle
    res = oslfile_open(_D("jpeg.jpg"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    res = caps_newSessionWithFileHandle(file, IMAGE_FORMAT_JPEG, &session);
    //Example: Flip image
    res = caps_beginFlip(session);
    res = caps_setFlip(session, CAPS_FLIP_VERTICAL);
    caps_endFlip (CTSession session)
    res = caps_getSourceImageSize(session, &dims);
    //Open destination file, get a file handle
    res = oslfile_open(_D("outJpeg.jpg"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file2);
    res = caps_renderToFileHandle(session, file2,
        dims, CAPS_OUTPUT_STRETCH, IMAGE_FORMAT_JPEG, 0);
    caps_destroySession(session);
    @endcode

    @sa
    caps_render()\n
    caps_renderToFile()\n
    caps_renderToBuffer()\n
    caps_renderAsRawToBuffer()\n

    @since 3.4
*/
SCBIMPORT CRESULT caps_renderToFileHandle( CTSession session, 
                                           CTFile* handle,
                                           CTSize outputDims,
                                           CAPS_OUTPUT_OPTION outputOption,
                                           IMAGE_FORMAT_SPEC outputFormat,
                                           CTIterator** it );
//-----------------------------------------------------------------------------
/**
    @brief
    Renders the current session image encoded to a buffer.

    @param session
    A valid session handle.

    @param buffer
    Pointer to a @c CTBuffer object which will receive the encoded image data.
    This buffer must be previously created using caps_createBuffer, but if not
    large enough for the image, it will be resized internally. Note however
    that ownership of the buffer remains with the caller, i.e the buffer must
    be destroyed using caps_destroyBuffer() when no longer needed. See remarks
    section for detailed information. The @c size member of the buffer will
    specify the exact size of the jpeg data when the render operation is
    completed.

    @param maxBuffer
    The maximum size of the buffer in bytes. Set to zero if no limitation is
    required. If this argument is less than the present size of the buffer
    (without equaling zero) the function will return @c CERR_INVALID_PARAMETER.\n\n

    @param outputDims
    Output dimensions of the image. This size specification is handled
    differently depending on the @a outputOption argument.
    Range: [0 < width, height < 16384]

    @param outputOption
    Specifies how the API should behave when sizing the image to the requested
    output size. See @c ::CAPS_OUTPUT_OPTION enumeration for details.

    @param outputFormat
    The format in which to encode the output image. This argument can specify
    any format of choice, but for formats not included in the
    ::CTImageFormat enumeration, a registered external encoder must exist
    which can handle it.
    Among the formats specified within the ::CTImageFormat enumeration,
    currently the only format supported for buffer encoding
    is @c IMAGE_FORMAT_JPEG.

    @param it
    Pointer to a @c CTIterator object if the render operation should be performed
    as an iterative sequence, otherwise @c NULL. When rendering to JPEG format,
    the number of bytes written during each iteration can be retrieved by
    calling caps_getIterationData(). See remarks section for more information.

    @remarks When using maxBuffer (non-zero) and rendering to a JPEG buffer, the 
    maxBuffer must be at least 16kB greater that the actual output buffer 
    size. This means that if the produced output file is 512kB, the maxBuffer
    value must be at least 528kB in order for the rendering to succeed.\n\n

    The limit of the downscale factor varies with the aspect ratio of the 
    source image. It is also dependent on the decode quality and choice of 
    render mode. We guarantee that downscaling with factor lower or equal 
    to 256 always is possible. In most of the cases will be possible to 
    downscale even more.\n\n

    <b>For internal encoders</b>\n
    Since the final size of the encoded output in most cases is unknown (for
    instance because of the impossibility to determine JPEG size in advance),
    the render process will incrementally encode and append data to the given
    output buffer. If the output buffer is too small to receive a chunk of
    data during this process, the buffer is incremented by reallocating and
    copying data. In order to preserve optimal performance during the render
    operation the number of buffer incrementations is minimized by allocating
    memory in largest possible blocks, which might produce memory allocation
    failure.\n
    The @a maxBuffer argument can be used to specify the limit of how large the
    resulting buffer is allowed to be. If it proves to be to small to fit the
    encoded data the @c CERR_MEMORY_OUT_OF_BOUNDS code will be returned from
    this function in a none-iterative render operation, or from
    caps_doNextIteration() in case an iterator is used to complete the render
    operation.

    CAUTION: Since the provided buffer may be reallocated internally by the
    API, any pointers to the data in the @c CTBuffer previously stored should
    be regarded as invalid after a call to this function.\n\n

    <b>For external encoders</b>\n
    The external encoder is responsible of allocating the encoding ::CTBuffer
    in the ::CTEncodingJob when using external encoders.
    \n\n
    If no internal or external configuration is found to handle the specified
    format, error code @c CERR_UNSUPPORTED_IMAGE is returned.
    \n\n
    If the output format is set to @c IMAGE_FORMAT_JPEG and the operation is
    performed iteratively, the number of bytes written in each subsequent call
    to caps_doNextIteration() can be retrieved by calling
    caps_getIterationData().
    \n\n
    @copydoc iterative_operations

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ILLEGAL_CALL If an iterative render operation is currently
    active when calling this function.
    .

    @code
    CTSession sess;
    CRESULT res = CERR_OK;
    CTBuffer* outBuffer = 0;
    CTSize dims = {640, 480};
    CTFile* file = 0;

    //Example1: Render a session to buffer and write it to disk.
    //The memory usage is limited to 200kB
    CTuint32 maxBuffer = 200000;

    res = caps_newSessionWithFile(srcFilename, IMAGE_FORMAT_JPEG, &sess);

    res = caps_createBuffer(maxBuffer, &outBuffer);

    res = caps_renderToBuffer(sess, outBuffer, maxBuffer,
        dims, CAPS_OUTPUT_STRETCH, IMAGE_FORMAT_JPEG, 0);

    //Note: The resulting size of the jpeg image is given in outBuffer->size.
    //The actual size of buffer is still maxBuffer.
    res = oslfile_open(dstFilename, FOF_ACCESS_WRITE | FOF_MODE_BINARY, &file);
    oslfile_write(file, outBuffer->data, outBuffer->size);
    oslfile_close(file);

    caps_destroyBuffer(outBuffer);
    caps_destroySession(sess);


    //Example2: Render a session to memory and write it to disk.
    //There is no limitation on the memory usage.
    maxBuffer = 0;

    res = caps_newSessionWithFile(srcFilename, IMAGE_FORMAT_JPEG, &sess);

    //Specify the size to 0.
    res = caps_createBuffer(maxBuffer, &outBuffer);

    //outBuffer will be inflated to fit the output image
    res = caps_renderToBuffer(sess, outBuffer, maxBuffer,
        dims, CAPS_OUTPUT_STRETCH, IMAGE_FORMAT_JPEG, 0);

    //Note: The resulting size of the jpeg image is given in outBuffer->size.
    //The actual size of outBuffer is outBuffer->size.
    res = oslfile_open(dstFilename, FOF_ACCESS_WRITE | FOF_MODE_BINARY, &file);
    oslfile_write(file, outBuffer->data, outBuffer->size);
    oslfile_close(file);

    caps_destroyBuffer(outBuffer);
    caps_destroySession(sess);
    @endcode

    @sa
    caps_render()\n
    caps_renderAsRawToBuffer()\n
    caps_renderToFile()

    @since 3.0
*/
SCBIMPORT CRESULT caps_renderToBuffer( CTSession session, 
                                       CTBuffer* buffer,
                                       CTuint32 maxBuffer, 
                                       CTSize outputDims,
                                       CAPS_OUTPUT_OPTION outputOption,
                                       IMAGE_FORMAT_SPEC outputFormat, 
                                       CTIterator** it );
//-----------------------------------------------------------------------------
/**
    @brief
    Returns the result from the decoding process of the source image.
    process.

    @param session
    A valid session handle.

    @remarks
    A session will always try to complete a rendering process even if the
    source image is incomplete. If the rendering process is successful,
    CAPS will return @c CERR_OK. If however the source image is incomplete,
    caps_getSourceRenderResult() will return @c CERR_INCOMPLETE_IMAGE.

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ILLEGAL_CALL If an iterative render operation is currently
    active when calling this function.
    .

    @code
    CTFile* file1 = 0;
    CTFile* file2 = 0;
    CTSession session;
    CTSize dims = {0};
    //Open source file, get a file handle
    res = oslfile_open(_D("jpeg.jpg"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    res = caps_newSessionWithFileHandle(file, IMAGE_FORMAT_JPEG, &session);
    //Example: Decode and encode
    res = caps_getSourceImageSize(session, &dims);
    //Open destination file, get a file handle
    res = oslfile_open(_D("outJpeg.jpg"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file2);
    res = caps_renderToFileHandle(session, file2,
        dims, CAPS_OUTPUT_STRETCH, IMAGE_FORMAT_JPEG, 0);
    res = caps_getSourceRenderResult( session );
    caps_destroySession(session);
    @endcode

    @since 3.7
*/
SCBIMPORT CRESULT caps_getSourceRenderResult( CTSession session );
//-----------------------------------------------------------------------------
/**
    @}
*/
// end of section 'group_baseapi_basicops'

//=============================================================================

/**
    @addtogroup types_n_defs
    @{
*/

/**
    @brief
    Image information object type used when acquiring information about images.

    For information on how to retrieve image information using the @c CTImageInfo object,
    study the documentation for the following functions, and enum:

    - enum @ref IIF
    - caps_getSourceImageInfo()
    - caps_getImageInfoField()
    - caps_imageInfoHasField()

    @since 3.4
*/
typedef struct CTImageInfo CTImageInfo;

//-----------------------------------------------------------------------------

/**
    @brief
    This enumeration type includes all available information fields of a
    CTImageInfo object. Please refer to documentation of individual field values
    for specific information.

    @note Regarding GIF images (IMAGE_FORMAT_GIF), all information retrieved
    when IIF_FORMAT specifies IMAGE_FORMAT_GIF applies to the image at index 0.
    This fact concerns the following fields:

    - IIF_WIDTH
    - IIF_HEIGHT
    - IIF_COLORMODE
    - IIF_HASALPHA
    - IIF_PALETTE
    .

    @since 3.4
*/
typedef enum
{
    /**
        @brief The format of the image.

        @par Field data type:
        ::IMAGE_FORMAT_SPEC

        @par Availability
        Always available.

        @par Example
        @code
        IMAGE_FORMAT_SPEC format = 0;
        res = caps_getImageInfoField( info, IIF_FORMAT, (CTint32*)&format );
        if( format == IMAGE_FORMAT_JPEG )
        {
            //...
        }
        @endcode
    */
    IIF_FORMAT = 1,
    //-----------------------------------------------------------------------------

    /**
        @brief The pixel width of the image.

        @par Field data type:
        CTuint32

        @par Availability
        Available for all formats.

        @par Example
        @code
        CTSize imageDims = {0,0};
        res = caps_getImageInfoField( info, IIF_WIDTH, (CTint32*)&imageDims.w );
        @endcode
    */
    IIF_WIDTH,
    //-----------------------------------------------------------------------------

    /**
        @brief The pixel height of the image.

        @par Field data type:
        CTuint32

        @par Availability
        Available for all formats.

        @par Example
        @code
        CTSize imageDims = {0,0};
        res = caps_getImageInfoField( info, IIF_HEIGHT, (CTint32*)&imageDims.h );
        @endcode
    */
    IIF_HEIGHT,
    //-----------------------------------------------------------------------------

    /**
        @brief The pixel colormode of the image.

        @par Field data type:
        ::CTColormode

        @par  Availability
        Available for all formats except for ::IMAGE_FORMAT_VIRTUAL

        @remarks
        For @ref IMAGE_FORMAT_GIF the colormode applies to the image at index 0.

        @par Example
        @code
        CTColormode cm = 0;
        res = caps_getImageInfoField( info, IIF_COLORMODE, (CTint32*)&cm );
        @endcode
    */
    IIF_COLORMODE,
    //-----------------------------------------------------------------------------

    /**
        @brief The colorspacing of the image.

        @par Field data type:
        ::CTColorspacing

        @par  Availability
        Available when IIF_FORMAT equals ::IMAGE_FORMAT_JPEG

        @par Example
        @code
        CTColorspacing cs = CS_UNDEFINED;
        res = caps_getImageInfoField( info, IIF_COLORSPACING, (CTint32*)&cs );
        @endcode
    */
    IIF_COLORSPACING,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicator if the image have an alpha channel.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_FORMAT equals any of the following values:

        - ::IMAGE_FORMAT_RAW
        - ::IMAGE_FORMAT_PNG
        - ::IMAGE_FORMAT_GIF
        - ::IMAGE_FORMAT_TIFF
        .

        Only the above formats will be accepted, all other will return CERR_ITEM_NOT_FOUND

        @par Example
        @code
        CTint32 hasAlpha = 0; // 0 = false
        res = caps_getImageInfoField( info, IIF_HASALPHA, &hasAlpha );
        @endcode
    */
    IIF_HASALPHA,
    //-----------------------------------------------------------------------------

    /**
        @brief The bit resolution if the image.

        @par Field data type:
        CTuint32

        @par  Availability
        Available for all format except ::IMAGE_FORMAT_VIRTUAL

        @par Example
        @code
        CTuint32 bpp = 0;
        res = caps_getImageInfoField( info, IIF_BPP, (CTint32*)&bpp );
        @endcode
    */
    IIF_BPP,
    //-----------------------------------------------------------------------------

    /**
        @brief The color palette used by the image.

        @par Field data type:
        ::CTBuffer *

        @par  Availability
        Available when IIF_FORMAT equals any of the following values:

        - IMAGE_FORMAT_GIF
        - IMAGE_FORMAT_PNG
        - IMAGE_FORMAT_BMP
        - IMAGE_FORMAT_TIFF
        .

        @note
        For @ref IMAGE_FORMAT_GIF the palette applies to the image at index 0.

        @par Example
        @code
        CTBuffer* palette = 0;
        res = caps_getImageInfoField( info, IIF_PALETTE, (CTint32*)&palette );
        @endcode
    */
    IIF_PALETTE,
    //-----------------------------------------------------------------------------

    /**
        @brief The huffman tables of the image.

        @par Field data type:
        ::CTBuffer **

        @par  Availability
        Available when IIF_FORMAT equals ::IMAGE_FORMAT_JPEG

        @remarks
        The retrieved array of CTBuffer pointers will always be at least
        @a (sizeof(CTBuffer*)*6) long. The three leading tables are the DC huffman
        tables of the image and the last three are the AC tables.

        Please note that the occurance of empty tables is normal. In such case
        both CTBuffer::size and CTBuffer::data will be zero.

        @par Example
        @code
        CTBuffer** huffTbls = 0;
        int huffCount = 6;
        res = caps_getImageInfoField( info, IIF_HUFFMANTBLS, (CTint32*)&huffTbls );
        if( res == CERR_OK )
        {
            for( int n = 0 ; n < huffCount ; n++ )
            {
                CTBuffer* pHuffTable = huffTbls[n];
                CTuint8*  huffmanTableData = pHuffTable->data;
                CTuint32  huffmanTableSize = pHuffTable->size;

                if( huffmanTableSize != 0 )
                {
                    // Safe to access 'huffmanTableData'.
                }
            }
        }
        @endcode
    */
    IIF_HUFFMANTBLS,
    //-----------------------------------------------------------------------------

    /**
        @brief The quantization tables of the image.

        @par Field data type:
        ::CTBuffer **

        @par  Availability
        Available for the following formats:

        - IMAGE_FORMAT_JPEG
        .

        @remarks
        The retrieved array of CTBuffer pointers will always be at least
        @a (sizeof(CTBuffer*)*3) long.

        Please note that the occurance of empty tables is normal. In such case
        both CTBuffer::size and CTBuffer::data will be zero.

        @par Example
        @code
        CTBuffer** quantTbls = 0;
        int quantCount = 3;
        res = caps_getImageInfoField( info, IIF_QUANTTBLS, (CTint32*)&quantTbls );
        if( res == CERR_OK )
        {
            for( int n = 0 ; n < quantCount ; n++ )
            {
                CTBuffer* pTable = quantTbls[n];
                CTuint8*  quantizationTableData = pTable->data;
                CTuint32  quantizationTableSize = pTable->size;

                if( quantizationTableSize != 0 )
                {
                    // Safe to access 'quantizationTableData'.
                }
            }
        }
        @endcode
    */
    IIF_QUANTTBLS,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the image allows progressive decoding.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_FORMAT equals any of the following values:

        - ::IMAGE_FORMAT_JPEG
        .

        Only the above format will be accepted, all other will return CERR_ITEM_NOT_FOUND

        @par Example
        @code
        CTbool isProgressive = false;
        res = caps_getImageInfoField( info, IIF_ISPROGRESSIVE, (CTint32*)&isProgressive );
        @endcode
    */
    IIF_ISPROGRESSIVE,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the image is interlaced.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_FORMAT equals any of the following values:

        - IMAGE_FORMAT_PNG
        .

        Only the above format will be accepted, all other will return CERR_ITEM_NOT_FOUND

        @par Example
        @code
        CTbool isInterlaced = false;
        res = caps_getImageInfoField( info, IIF_ISINTERLACED, (CTint32*)&isInterlaced );
        @endcode
    */
    IIF_ISINTERLACED,
    //-----------------------------------------------------------------------------

    /**
        @brief The number of frames contained in a gif image.

        @par Field data type:
        CTuint32

        @par Availability
        If IIF_FORMAT equals ::IMAGE_FORMAT_GIF

        Only the above format will be accepted, all other will return CERR_ITEM_NOT_FOUND

        @par Example
        @code
        CTuint32 noOfGifFrames = 0;
        res = caps_getImageInfoField( info, IIF_GIFNOOFFRAMES,
            (CTint32*)&noOfGifFrames );
        @endcode
    */
    IIF_GIFNOOFFRAMES,
    //-----------------------------------------------------------------------------

    /**
        @brief get the total delay time in 1/100 sek for all frames contained in a gif image

        @par Field data type:
        CTuint32

        @par  Availability
        Available when IIF_FORMAT equals the following value:

        - IMAGE_FORMAT_GIF
        .

        Only the above format will be accepted, all other will return CERR_ITEM_NOT_FOUND

        @par Example
        @code
        CTuint32 totalGifDelayTime = 0;
        res = caps_getImageInfoField( info, IIF_GIFTOTALDELAYTIME,
            (CTint32*)&totalGifDelayTime );
        @endcode
*/
    IIF_GIFTOTALDELAYTIME,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the image is a JPS image.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_FORMAT equals any of the following values:

        - IMAGE_FORMAT_JPEG
        - IMAGE_FORMAT_JPS
        .

        Only the above format will be accepted, all other will return CERR_ITEM_NOT_FOUND

        @par Example
        @code
        CTbool isJps = false;
        res = caps_getImageInfoField( info, IIF_ISJPS, (CTint32*)&isJps );
        @endcode
    */
    IIF_ISJPS,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the image is stereoscopic.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTbool isStereo = false;
        res = caps_getImageInfoField( info, IIF_ISJPS, (CTint32*)&isStereo );
        @endcode
    */
    IIF_JPS_ISSTEREO,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the image is anaglyphic.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTbool isAnaglyphic = false;
        res = caps_getImageInfoField( info, IIF_JPS_ANAGLYPHIC, (CTint32*)&isAnaglyphic );
        @endcode
    */
    IIF_JPS_ANAGLYPHIC,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if left is red in an anaglyphic image.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTbool leftIsRed = false;
        res = caps_getImageInfoField( info, IIF_JPS_ANAG_LEFT_RED, (CTint32*)&leftIsRed );
        @endcode
    */
    IIF_JPS_ANAG_LEFT_RED,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the left and right regions are interleaved.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTbool isInterleaved = false;
        res = caps_getImageInfoField( info, IIF_JPS_INTERLEAVED, (CTint32*)&isInterleaved );
        @endcode
    */
    IIF_JPS_INTERLEAVED,
    //-----------------------------------------------------------------------------

    /**
        @brief The X coordinate of the right image region in a stereoscopic image.
        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_RIGHT_X, &(right.x) );
        @endcode
    */
    IIF_JPS_RIGHT_X,
    //-----------------------------------------------------------------------------

    /**
        @brief The Y coordinate of the right image region in a stereoscopic image.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_RIGHT_Y, &(right.y) );
        @endcode
    */
    IIF_JPS_RIGHT_Y,
    //-----------------------------------------------------------------------------

    /**
        @brief The height of the right image region in a stereoscopic image.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_RIGHT_H, &(right.h) );
        @endcode
    */
    IIF_JPS_RIGHT_H,
    //-----------------------------------------------------------------------------

    /**
        @brief The width of the right image region in a stereoscopic image.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_RIGHT_W, &(right.w) );
        @endcode
    */
    IIF_JPS_RIGHT_W,
    //-----------------------------------------------------------------------------

    /**
        @brief The X coordinate of the left image region in a stereoscopic image.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_LEFT_X, &(left.x) );
        @endcode
    */
    IIF_JPS_LEFT_X,
    //-----------------------------------------------------------------------------

    /**
        @brief The Y coordinate of the left image region in a stereoscopic image.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_LEFT_Y, &(left.y) );
        @endcode
    */
    IIF_JPS_LEFT_Y,
    //-----------------------------------------------------------------------------

    /**
        @brief The height of the left image region in a stereoscopic image.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_LEFT_H, &(left.h) );
        @endcode
    */
    IIF_JPS_LEFT_H,
    //-----------------------------------------------------------------------------

    /**
        @brief The width of the left image region in a stereoscopic image.

        @par Field data type:
        CTint32

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTRect left, right;
        res = caps_getImageInfoField( info, IIF_JPS_LEFT_W, &(left.w) );
        @endcode
    */
    IIF_JPS_LEFT_W,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the image is half height.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTbool isHalfHeight = false;
        res = caps_getImageInfoField( info, IIF_JPS_HALF_HEIGHT, (CTint32*)&isHalfHeight );
        @endcode
    */
    IIF_JPS_HALF_HEIGHT,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the image is half width.

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_ISJPS is true.

        @par Example
        @code
        CTbool isHalfWidth = false;
        res = caps_getImageInfoField( info, IIF_JPS_HALF_WIDTH, (CTint32*)&isHalfWidth );
        @endcode
    */
    IIF_JPS_HALF_WIDTH,
    //-----------------------------------------------------------------------------

    /**
        @brief Indicates if the file is an MPO file

        @par Field data type:
        CTbool

        @par  Availability
        Available when IIF_FORMAT equals any of the following values:

        - IMAGE_FORMAT_JPEG
        - IMAGE_FORMAT_JPS
        .

        Only the above format will be accepted, all other will return CERR_ITEM_NOT_FOUND

        @par Example
        @code
        CTbool isMpo = false;
        res = caps_getImageInfoField( info, IIF_ISMPO, (CTint32*)&isMpo );
        @endcode
    */
    IIF_ISMPO
    //-----------------------------------------------------------------------------
} IIF;
/**
    @}
*/ // end of addtogroup 'types_n_defs'

//=============================================================================

/**
    @addtogroup caps_baseapi_basicops
    @{
*/

/** @name Image querying */
// @{

/**
    @brief
    Retrieves information about the current source image.

    @param session
    A valid session handle.

    @param imageInfo
    Address of CTImageInfo pointer which will receive an allocated object
    filled with all available information about the current source image.
    The object can subsequently be queried for specific information by calling
    caps_getImageInfoField(). Ownership of the allocated object is transferred
    to the caller and must be destroyed using caps_destroyImageInfo().

    @remarks
    The allocated object is valid even after the queried session is destroyed.

    @par Example:
    @code
    CRESULT res = CERR_OK;
    CTImageInfo* info = 0;
    IMAGE_FORMAT_SPEC format;

    res = caps_getSourceImageInfo( session, &info );
    HANDLE_ERROR( res );

    caps_destroySession( session );

    res = caps_getImageInfoField( info, IIF_FORMAT, (CTuint32*)&format );
    HANDLE_ERROR( res );

    switch( format )
    {
        ...
    }

    caps_destroyImageInfo( info );
    @endcode

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_getImageInfoField()

    @since 3.4
*/
SCBIMPORT CRESULT caps_getSourceImageInfo( CTSession session, CTImageInfo** imageInfo );
//-----------------------------------------------------------------------------
/**
    @brief
    Destroys a CTImageInfo object.

    @param imageInfo
    Pointer to a previously created CTImageInfo object.

    @sa
    caps_getSourceImageInfo()\n

    @since 3.4
*/
SCBIMPORT void caps_destroyImageInfo( CTImageInfo* imageInfo );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves a field of information from a CTImageInfo object.

    @param pInfo
    Pointer to a CTImageInfo object which has been previously retrieved from
    a session.

    @param field
    ID of the field to retrieve data from. Can be one of the values from the
    ::IIF enumeration. If the given field is unavailable the function returns
    CERR_ITEM_NOT_FOUND.

    @param pData
    Pointer to a CTint32 variable which will receive the field data. The
    returned contents of the field is different depending on which field is
    being requested. Please refer to the documentation of each member of the
    ::IIF enumeration for information on how to handle the @a data argument
    for each field ID.

    @remarks
    caps_imageInfoHasField() can be used to determin in advance if a certain
    information field exists in the given info object.

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ITEM_NOT_FOUND is returned if the field is unavailable.
    .

    @sa
    caps_getSourceImageInfo()\n
    caps_imageInfoHasField()\n

    @since 3.4
*/
SCBIMPORT CRESULT caps_getImageInfoField( CTImageInfo *pInfo, 
                                          IIF field, 
                                          CTint32 *pData );
//-----------------------------------------------------------------------------
/**
    @brief
    Determines whether a field within the given image information object is 
    available or not.

    @param pInfo
    Pointer to a CTImageInfo object which has been previously retrieved from
    a session.

    @param field
    The field ID to query.

    @param pHasField
    Pointer to a CTbool variable which will receive @c true if the given field
    exists or 2c false otherwise.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_getSourceImageInfo()\n
    caps_imageInfoHasField()\n

    @since 3.4
*/
SCBIMPORT CRESULT caps_imageInfoHasField( CTImageInfo *pInfo, 
                                          IIF field, 
                                          CTbool *pHasField );
// @}
// end 'Image querying' section.

//=============================================================================

/** @name Jpeg quality */
//   @{

/**
    @brief
    Sets the JPEG compression quality to use in subsequent render operations.

    @param session
    A valid session handle.

    @param quality
    The JPEG quality factor, range (0.0 < quality <= 1.0).

    @remarks
    The JPEG quality factor is only used when rendering the output to
    JPEG format.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_setJpegQuality( CTSession session, CTfloat quality );
//  @}
// end 'Jpeg quality' section.

//=============================================================================

/** @name Jpeg header (Application segment) management */
//   @{

/**
    @brief
    Adds XMP meta data to a session.

    The added data will written to the header when the session is
    rendered to a Jpeg-file.

    @note Only valid when rendering to Jpeg-files.

    @param session
    A valid CAPS CTSession.

    @param xmpData
    A buffer containing the XMP meta data.
    If @c NULL is passed, any previously set data will be deleted from the session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.
    
    @since 3.11
*/
SCBIMPORT CRESULT caps_addXmpDataFromBuffer( CTSession session, const CTBuffer* xmpData );

//-------------------------------------------------------------------------

/**
    @brief
    Adds one, or more, Jpeg APPn segment(s) to a session.

    The added data will written to the header when the session is
    rendered to a Jpeg-file.

    @note Only valid when rendering to Jpeg-files.

    @param session
    A valid CAPS CTSession.

    @param auxData
    A buffer containing the APP block data. The buffer may hold several APP blocks.
    If @c NULL is passed, any previously set data will be deleted from the session.
	Note that no sanity check is made on this buffer. The caller must make sure
	that the APP block identifier(s) and associated size(s) are correct. Incorrect identifiers
	and sizes may result in failure to decode the jpeg image.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.
    
    @since 3.11
*/
SCBIMPORT CRESULT caps_addAppBlocksToJpegHeaderFromBuffer( CTSession session, const CTBuffer* auxData );

//  @}
// end 'Jpeg header meta data section'.
//=============================================================================


/** @name Gif selection */
//  @{

/**
    @brief
    This function shall be used to select which gif image contained in a gif
    file to be displayed.

    @param session
    A valid session handle.

    @param index
    Index of the gif sub-image to be displayed.
    The numbering starts with index = 0.
    The number of gif images in a gif file can be obtained with
    caps_getSourceImageInfo(). See CTImageInfo.

    @param pDisplayTime
    The display time in resolution of 1/100 seconds for the image according to
    the information embedded in the gif file. Note that the display time is
    is coded individually for all sub-images. Infinite display time
    is indicated with zero.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7
*/
SCBIMPORT CRESULT caps_setGifFrame( CTSession session,
                                    CTuint32 index,
                                    CTuint32* pDisplayTime);

//  @}
// end 'Gif section'.
//=============================================================================
/**
    @}
*/
// end addtogroup 'caps_baseapi_basicops'.
//=============================================================================

/**
    @addtogroup caps_baseapi_extdecod
    @brief  The extension interface functions can be implemented externally
    in order to extend the capabilities of the framework.

    @{
*/

/**
    @brief
    Interface for external decoder definitions.

    @param pStream
    A pointer to a stream containing an image. Cannot be NULL.

    @param format
    The format specification of the @c buffer content. This should be an
    externally defined value which is interpreted by the external decoder. It
    must not be located within the range for the internally supported image
    formats, i.e. from @c IMAGE_FORMAT_RANGE_MIN to @c IMAGE_FORMAT_RANGE_MAX.

    @param[out] ppImage
    Address of a @a CTImage pointer which will receive the decoded
    image. Cannot be @c NULL.

    @remarks
    When the framework is confronted with an image of an unsupported/unknown
    image format it attempts to pass the job over to a potential external
    decoder by calling this interface.\n\n

    The @c ppImage argument should be allocated internally by the implementation
    if the image was decoded successfully, otherwise it must be ignored.
    Its ownership should be transferred to the caller (i.e. the framework).
    See caps_createImage() for details.

    The interface is by default implemented as a stub function returning
    @c CERR_UNSUPPORTED_IMAGE. See the accompaning user guide for detailed
    information on how to provide an external implementation.

    @return
    @c The function should return @c CERR_OK if the image was successfully
    decoded, otherwise a specific error code which describes the error. In case
    of an error the @c image argument should be ignored and left unmodified.
    In most cases the error code returned from the implementation is propagated
    back to	the user. This behavior might however change in future versions
    and should not be relied upon. See the accompanying user guide for detailed
    information on the error codes to use for given error scenarios.

    @since 3.8

    @deprecated This function is deprecated. It will be removed in 5.4.
*/
SCBIMPORT CRESULT caps_extDecode( CTStream *pStream,
                                  IMAGE_FORMAT_SPEC format,
                                  CTImage **ppImage );
//-----------------------------------------------------------------------------
/**
    @}
*/
// end of group 'caps_baseapi_extdecod'

//=============================================================================

/**
    @addtogroup buffer_utility
    @brief Helper functions for CTBuffer handling.
    @{
*/

/**
    @brief
    Creates a new buffer.

    @param size
    The requested size of the new buffer in bytes.

    @param[out] buffer
    Address to a @c CTBuffer pointer which will receive the created buffer.

    @remarks
    When the buffer is no longer needed it should be destroyed using
    caps_destroyBuffer().

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_createBuffer( CTuint32 size, CTBuffer** buffer );
//-----------------------------------------------------------------------------
/**
    @brief
    Destroys a previously created buffer.

    @param buffer
    Pointer to a @c CTBuffer to destroy. This pointer is invalid after the call.

    @sa
    caps_createBuffer()\n
    caps_createBufferCopy()

    @since 3.0
*/
SCBIMPORT void caps_destroyBuffer( CTBuffer* buffer );
//-----------------------------------------------------------------------------
/**
    @brief
    Creates an exact copy of the provided buffer.

    @param original
    The @c CTBuffer object to copy.

    @param[out] copy
    Address to a @c CTBuffer pointer which will receive the copy.

    @remarks
    When no longer needed the buffer should be destroyed using
    caps_destroyBuffer().

    @sa
    caps_createBuffer()

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_createBufferCopy( const CTBuffer* original, CTBuffer** copy );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the address to the data in a @c CTBuffer.

    @param buffer
    The @c CTBuffer object from which to retrieve the data pointer.

    @param[out] data
    Address of a pointer which will receive the buffer data address.
    Ownership of the pointer is NOT transferred to the caller and should not be
    regarded as permanent. When the @c CTBuffer object is destroyed the pointer
    will be invalid.

    @sa
    caps_getBufferSize()

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code
    CTBuffer* buffer = 0;
    CTBuffer buffer2 = {0};
    CTuint32 bufferSize = 0;
    CTuint8* data = 0;

    //Create a buffer of BUFFER_SIZE bytes
    caps_createBuffer(BUFFER_SIZE, &buffer);

    //Retrieve the size and a pointer to the data
    caps_getBufferSize(buffer, &bufferSize);
    caps_getBufferData(buffer, &data);

    //Manually create a a new buffer
    buffer2.size = bufferSize;
    buffer2.data = (CTuint8*)oslmem_alloc(buffer2.size);
    
    //Copy data to buffer2.data. 
    //Note: The standard (ANSI) C function: memcpy() should be replaced with
    // the corresponding function on the target platform.
    memcpy (buffer2.data, data, bufferSize);

    //Destroy original buffer
    caps_destroyBuffer(buffer);
    @endcode

    @since 3.0
*/
SCBIMPORT CRESULT caps_getBufferData( const CTBuffer* buffer, CTuint8** data );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the size of a buffer.

    @param buffer
    The @c CTBuffer object from which to retrieve the size.

    @param[out] size
    Pointer to a @c CTuint32 variable which will receive the size in bytes
    of the buffer data.

    @sa
    caps_getBufferData()

    @return
    @c CERR_OK if succesful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getBufferSize( const CTBuffer* buffer, CTuint32* size );
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'buffer_utility'

//=============================================================================

/**
    @addtogroup image_utility
    @brief Helper functions for CTImage handling.
    @{
*/

/**
    @brief
    Creates a @c CTImage object.

    @param pPixels
    Optional argument, a @c CTBuffer pointer which will be set as the pixel buffer
    of the image. On success, the ownership of the buffer will be taken over by
    the CTImage object and will be deallocated when the CTImage is destroyed.
    On failure, the ownership of the buffer remains with the caller.
    If the provided argument (@em pixels) is @c NULL, a buffer will be allocated
    internally for the image.

    @param dims
    The dimensions in pixels of the image.

    @param scanline
    The width in bytes of one scanline within the image. If set to zero, a 
    suitable scanline is assigned to the image.

    @param format
    The color mode format of the image. See @c CTColormode enumeration.

    @param[out] ppImage
    The created @c CTImage object returned as an output argument. If the
    function fails this argument is NULL.

    @remarks
    The arguments passed to this function are precisely corresponding with
    the members of @c CTImage. See documentation of this type for more info.

    @sa
    caps_getImagePixels()\n
    caps_setImagePixels()

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @par Example: Convert from raw YUV file to raw RGB888 file.
    @code
    CTSession sess;
    CRESULT res = CERR_OK;
    CTuint32 fileSize = 0;
    CTuint32 bitSize = 0;
    CTSize dims = {320, 240};
    CTImage* image = 0;
    CTImage* outImage = 0;
    CTFile* file = 0;

    res = oslfile_open(_D("yuv422_Y1UY2V_320x240.raw"),
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    fileSize = oslfile_size(file);
    caps_createBuffer(fileSize, &buffer);
    oslfile_read(file, buffer->data, buffer->size);
    oslfile_close(file);

    bitSize = caps_pixelBitSize(CM_YUV422_Y1UY2V);
    res = caps_createImage(buffer, dims, (dims.w * bitSize + 7) / 8,
        CM_YUV422_Y1UY2V, &image);

    res = caps_newSessionWithRaw(image, &sess);

    bitSize = caps_pixelBitSize(CM_RGB888);
    res = caps_createImage(0, dims, (dims.w * bitSize + 7) / 8,
        CM_RGB888, &outImage);
    res = caps_renderAsRawToBuffer(sess, outImage, CAPS_OUTPUT_STRETCH, 0);

    res = oslfile_open(_D("rgb888_320x240.raw"),
        FOF_ACCESS_WRITE | FOF_MODE_BINARY, &file);
    oslfile_write(file, outImage->pixels->data, outImage->pixels->size);
    oslfile_close(file);

    caps_destroyImage(image);
    caps_destroyImage(outImage);
    caps_destroySession(sess);
    @endcode

    @since 3.0
*/
SCBIMPORT CRESULT caps_createImage(CTBuffer *pPixels, 
                                   CTSize dims, 
                                   CTuint32 scanline,
                                   CTColormode format, 
                                   CTImage **ppImage );
//-----------------------------------------------------------------------------
/**
    @brief
    Calculates the required buffer byte size for corresponding dimensions and
    colormode.

    @param dims
    The dimensions of the raw image to calculate buffer size for.

    @param scanline
    Number of bytes per image row.

    @param format
    The color format of the raw image to calculate buffer size for. See remarks
    section for details.

    @param[out] pByteSize
    Pointer to an @c CTuint32 which will receive the calculated buffer size.

    @remarks
    The @c format argument must be one of the valid color formats specified in:
    @ref supported_colorformats

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @note
    Image size calculations are potentially complex so it is normally easiest
    to leave the scanline parameter at zero. When the scanline is not specified,
    the system may assume a scanline that is not optimally small, but instead
    (for instance) word aligned.

    @note
    This function will not necessarily return the smallest allowed size for an
    image of the specified format.
 
    @since 3.1
*/
SCBIMPORT CRESULT caps_calculateRawSize(CTSize dims, 
                                        CTuint32 scanline,
                                        CTColormode format,
                                        CTuint32 *pByteSize);
//-----------------------------------------------------------------------------
/**
    @brief
    Returns the number of bytes needed for storing a pixel of the given
    format.

    @param format
    The colormode format to calculate pixel size for.

    @remarks
    Only color formats with a pixel bit size of a multiple of 8 bits
    are supported by this function.
    \n

    @return
    The required size in bytes of one pixel or 0 if an unsupported color mode
    is provided.

    @code
    CTuint32 byteSize = 0;
    CTuint32 bitSize = 0;
    CTColormode colormode;

    colormode = CM_RGB888;
    byteSize = caps_pixelByteSize(colormode);
    //Returns byteSize = 3
    bitSize = caps_pixelBitSize(colormode);
    //Returns bitSize = 24

    colormode = CM_YUV422SP;
    byteSize = caps_pixelByteSize(colormode);
    //Returns byteSize = 2
    bitSize = caps_pixelBitSize(colormode);
    //Returns byteSize = 16
    @endcode

    @since 3.2
*/
SCBIMPORT CTuint32 caps_pixelByteSize( CTColormode format );
//-----------------------------------------------------------------------------
/**
    @brief
    Returns the number of bits needed for storing a pixel of the given format.

    @param format
    The colormode format to calculate pixel size for.

    @return
    The required size in bits of one pixel or 0 if an unsupported color mode
    is provided.

    @code
    CTuint32 byteSize = 0;
    CTuint32 bitSize = 0;
    CTColormode colormode;

    colormode = CM_RGB888;
    byteSize = caps_pixelByteSize(colormode);
    //Returns byteSize = 3
    bitSize = caps_pixelBitSize(colormode);
    //Returns bitSize = 24

    colormode = CM_YUV422SP;
    byteSize = caps_pixelByteSize(colormode);
    //Returns byteSize = 2
    bitSize = caps_pixelBitSize(colormode);
    //Returns byteSize = 16
    @endcode

    @since 3.5
*/
SCBIMPORT CTuint32 caps_pixelBitSize( CTColormode format );
//-----------------------------------------------------------------------------
/**
    @brief
    Destroys a previously created @c CTImage object.

    @param image
    The @c CTImage object to destroy. This pointer is invalid when the function
    returns.

    @since 3.0
*/
SCBIMPORT void caps_destroyImage( CTImage* image );

/**
    @}
*/ // end of addtogroup 'image_utility'

//=============================================================================

/**
    @addtogroup caps_baseapi_screen
    @{
*/

/**
    @name Coordinate conversions
    The coordinate conversion functions are useful in particular when using API
    functions that require coordinate information, since all such functions
    in CAPS interpret coordinates within the @a current coordinate system.
*/
// @{

/**
    @brief
    Converts a coordinate from @a current to @a screen coordinate system.

    @param screen
    A CTScreen pointer specifying the screen to which to convert the
    coordinate.

    @param coord
    Pointer to a CTPoint object with the coordinate to convert. The converted
    coordinate is stored back into the object.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
*/
SCBIMPORT CRESULT caps_coordCurrentToScreen( CTScreen* screen, CTPoint* coord );
//-----------------------------------------------------------------------------
/**
    @brief
    Converts a coordinate from @a screen to @a current coordinate system.

    @param screen
    A @c CTScreen pointer specifying the screen from which to convert the
    coordinate.

    @param coord
    Pointer to a @c CTPoint object with the coordinate to convert. The converted
    coordinate is stored back into the object.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_coordScreenToCurrent( CTScreen* screen, CTPoint* coord );
//-----------------------------------------------------------------------------
/**
    @brief
    Converts a coordinate from @a canvas to @a current coordinate system.

    @param screen
    A @c CTScreen pointer specifying a screen in which the canvas from which to
    convert the coordinate is located.

    @param coord
    Pointer to a @c CTPoint object with the coordinate to convert. The converted
    coordinate is stored back into the object.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_coordCanvasToCurrent( CTScreen* screen, CTPoint* coord );
//-----------------------------------------------------------------------------
//@}
// end of section: 'Coordinate conversions'
//=============================================================================
/**
    @}
*/
// end of addtogroup 'caps_baseapi_screen'
//=============================================================================

/**
    @addtogroup fxgroup_crop
    @{
*/

/**
    @brief
    Crops an area of the current session image.

    @param session
    A valid session handle.

    @param crop_region
    A @c CTRect object specifying the crop region.
    Range: [8= < width, height < 16384]

    @remarks

    The cropped area will after this operation become the new "current" session
    image for subsequent modifications.
    \n\n
    The crop area coordinates are treated as "current" coordinates. Note that
    the 8x8 crop area constraint applies to the size after a potential
    coordinate conversion. For instance, a GUI may allow a user to define a
    crop area when cropped on the screen, even if this area is larger than
    8x8 pixels, it may in reality be smaller than 8x8 when converted to
    the "current" coordinate system before passed to this function.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code
    //Example: Crop to what you see in the screen.
    CRESULT cropToCurrent(CTScreen* screen)
    {
        CRESULT res;
        CTSession session;
        CTPoint upperLeft = {0};
        CTPoint lowerRight = {0};
        CTRect canvasRect = {0};
        CTRect cropArea = {0};

        res = caps_getScreenCanvasArea(screen, &canvasRect);
        if (res != CERR_OK)
        {
            return res;
        }

        lowerRight.x = canvasRect.w;
        lowerRight.y = canvasRect.h;

        res = caps_coordCanvasToCurrent(screen, &upperLeft);
        if (res != CERR_OK)
        {
            return res;
        }

        res = caps_coordCanvasToCurrent(screen, &lowerRight);
        if (res != CERR_OK)
        {
            return res;
        }

        cropArea.x = upperLeft.x;
        cropArea.y = upperLeft.y;
        cropArea.w = lowerRight.x - upperLeft.x;
        cropArea.h = lowerRight.y - upperLeft.y;

        res = caps_getScreenSession(screen, &session);
        if (res != CERR_OK)
        {
            return res;
        }

        res = caps_doCrop(session, cropArea);
        if (res != CERR_OK)
        {
            return res;
        }

        //Reset zoom and pan
        (void)caps_setZoom(screen, 1.0f);
        (void)caps_setPan(screen, 0.f, 0.f);

        return CERR_OK;
    }
    @endcode

    @since 3.0

*/
SCBIMPORT CRESULT caps_doCrop( CTSession session, CTRect crop_region );
//-----------------------------------------------------------------------------
/**
    @brief
    Crops an elliptic area of the current session image. Alpha
    values of the pixels within the rectangular bounding box which is not
    part of ellipsis values are set to fully transparent.

    The elliptic area is the largest ellipse that fills the rectangle specified
    by crop_region.

    @param session
    A valid session handle.

    @param crop_region
    A @c CTRect object specifying the crop region.
    Range: [10 = < width, height < 16384]

    @remarks
    The cropped area will after this operation become the new "current" session
    image for subsequent modifications.
    \n\n
    The crop area coordinates are treated as "current" coordinates. Note that
    the 10x10 crop area constraint applies to the size after a potential
    coordinate conversion. For instance, a GUI may allow a user to define a
    crop area when cropped on the screen, even if this area is larger than
    10x10 pixels, it may in reality be smaller than 10x10 when converted to
    the "current" coordinate system before passed to this function.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code
    //Example: Use elliptic crop together with cliparts.
    CRESULT res = CERR_OK;
    CTRect cropRegion = {0};
    CTSession sess;
    CTSize dims = {0};
    CTuint32 scanline = 0;
    CTPoint pos = {0};
    CAPS_CLIPART clipart;
    CTImage* image = 0;

    res = caps_newSessionWithFile(_D("jpeg2.jpg"), IMAGE_FORMAT_JPEG, &sess);
    res = caps_getCurrentImageSize(sess, &dims);
    //Crop a circle with a radius = 75 with center in the middle of the image.
    cropRegion.h = 2 * 75;
    cropRegion.w = 2 * 75;
    cropRegion.x = dims.w / 2 - 75;
    cropRegion.y = dims.h / 2 - 75;
    res = caps_doEllipticCrop(sess, cropRegion);

    res = caps_getCurrentImageSize(sess, &dims);
    scanline = dims.w * caps_pixelByteSize(CM_ARGB8888);
    res = caps_createImage(0, dims, scanline, CM_ARGB8888, &image);

    res = caps_renderAsRawToBuffer(sess, image, CAPS_OUTPUT_PRESERVE_AR, 0);
    caps_destroySession(sess);

    res = caps_newSessionWithFile(_D("jpeg2.jpg"), IMAGE_FORMAT_JPEG, &sess);
    res = caps_getCurrentImageSize(sess, &dims);

    //Past the cropped circular area in th middle
    pos.x = dims.w / 2;
    pos.y = dims.h / 2;
    res = caps_beginClipartFromRaw(sess, image, OWNERSHIP_CAPS, pos,
        3.0f, 0.0f, &clipart);
    res = caps_endClipart(clipart);

    res = caps_renderToFile(sess, _D("jpeg_with_clipart.jpg"), dims,
        CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);

    caps_destroySession(sess);
    @endcode

    @since 3.5

*/
SCBIMPORT CRESULT caps_doEllipticCrop( CTSession session, CTRect crop_region );
/**
    @}
*/ // end of group 'fxgroup_crop'
//=============================================================================
/**
    @addtogroup fxgroup_flip
    @{
*/
//.............................................................................
// NOTE! - This documentation block is referenced from all begin-end style
// functions, in order to prevent duplication.
/**
    @page begin_end_effects Begin/End Effects
    This function family follows the "begin-end" framework. These operations need
    to be applied in the following order:
    -# @c caps_begin@em \<FUNC\>()
    -# @c caps_set@em \<FUNC\>()
    -# @c caps_end@em \<FUNC\>()
    .

    where @em \<FUNC\> is the function (family) name; e.g. Flip, Blur, Noise.
    Multiple calls to @c caps_set@em \<FUNC\>() are possible before the call
    to @c caps_end@em \<FUNC\>()

    @attention
    Calling any of these functions out of context (e.g. order) will cause it to
    return CERR_ILLEGAL_CALL.
*/
//.............................................................................
/**
    @ingroup types_n_defs
    @brief Defines the flip modes to use with caps_doFlip().
*/
typedef enum
{
    FLIP_NONE       = 0,
    FLIP_VERTICAL   = 1,    ///< Flips the image horizontally
    FLIP_HORIZONTAL = 2,    ///< Flips the image vertically
    FLIP_BOTH       = (FLIP_VERTICAL | FLIP_HORIZONTAL)
} CAPS_FLIP_MODE;
//-----------------------------------------------------------------------------
/**
    @brief

    @param session
    Handle to a valid session.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginFlip( CTSession session );
//-----------------------------------------------------------------------------
/**
    @brief
    Flips the current session image horizontally or vertically.

    @param session
    Handle to a valid session.

    @param flip_mode
    The direction to flip the image.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setFlip( CTSession session, CAPS_FLIP_MODE flip_mode );
//-----------------------------------------------------------------------------
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endFlip( CTSession session );
/**
    @}
*/ // 'Flip'
//=============================================================================

/**
    @addtogroup fxgroup_rotate_90
    @{

    @copydoc begin_end_effects
*/

/**
    @ingroup types_n_defs
    @brief Defines the rotation directions to use use with caps_doRotate().
*/
typedef enum
{
    ROTATE_TO_0     = 3, ///< Rotates the image to zero degrees clockwise.
    ROTATE_TO_90    = 1, ///< Rotates the image to 90 degrees clockwise.
    ROTATE_TO_180   = 2, ///< Rotates the image to 180 degrees clockwise.
    ROTATE_TO_270   = 0  ///< Rotates the image to 270 degrees clockwise.

} CAPS_ROTATION;
//-----------------------------------------------------------------------------
/**
    @brief

    @param session
    Handle to a valid session.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_beginRotate( CTSession session );
//-----------------------------------------------------------------------------
/**
    @brief
    Rotates the current session image in 90 degrees steps.

    @param session
    Handle to a valid session.

    @param direction
    The angle into which the image should be roated. Can be any of the values
    from the @c ::CAPS_ROTATION enumeration.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setRotate( CTSession session, CAPS_ROTATION direction );
//-----------------------------------------------------------------------------
/**
    @brief

    @param session
    Handle to a valid session.

    @since 3.2
*/
SCBIMPORT void caps_endRotate( CTSession session );
/**
    @}
*/ // 'Rotate 90'
//=============================================================================

/**
    @addtogroup caps_baseapi_screen
    @{
*/

/**
    @brief
    Creates a new screen for displaying the session output.

    @param session
    A valid session handle.

    @param size
    A @c CTSize object specifying the size in pixels of the new screen.
    Range: [0 < width, height < 16384]


    @param colormode
    A @c CTColormode object specifying the pixel format of the screen buffer.

    @param screenBuffer
    Optional pointer to a @c CTBuffer which specifies an external screen buffer
    into which all rendering will be performed. Ownership of the buffer will
    remain with the caller. See remarks section for more information.

    @param[out] screen
    Pointer to a @c CTScreen object which will receive the created
    screen. This argument is NULL if the function
    fails. The screen must be destroyed before its associated session is destroyed.

    @remarks
    If the @c screenBuffer argument is set to @c NULL, an internal screen buffer
    will be allocated. The screen pixels can be retrieved by calling
    caps_getScreenImage(). Note that caps_getScreenImage may be used also when
    using external screen buffers, in which case the @c pixels member of the retrieved
    @c CTImage will equal the screen buffer passed to this function.

    @remarks
    The @c colormode argument must be set to one of the valid (output) formats
    specified in: @ref supported_colorformats

    @remarks
    Not all screen related functions support all of these color modes.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code
    CRESULT res = CERR_OK;
    CTSize screenSize = {320, 240};
    CTScreen* screen = 0;
    CTBuffer screenBuffer;
    CTSession sess;

    extern CTuint8* scrBuffer;

    res = caps_newSessionWithFile(_D("c:/testim.jpg"),
        IMAGE_FORMAT_JPEG, &sess);

    //Case 1: External screen buffer
    screenBuffer.data = scrBufferp;
    screenBuffer.size = 320 * 240 * 2;
    res = caps_createScreen(sess, screenSize, CM_RGB565,
        &screenBuffer, &screen);
    //..
    //Add effects, render screen..
    //
    //Screen will be destroyed, screen buffer will not be destroyed
    caps_destroyScreen(screen);

    //Case 2: Internal screen buffer
    res = caps_createScreen(sess, screenSize, CM_RGB565,
        0, &screen);
    //..
    //Add effects, render screen..
    //
    //Screen and internal screen buffer will be destroyed
    caps_destroyScreen(screen);

    caps_destroySession(sess);
    @endcode

    @sa
    caps_setScreenBuffer()\n

    @since 3.0
*/
SCBIMPORT CRESULT caps_createScreen( CTSession session, CTSize size,
                           CTColormode colormode, CTBuffer* screenBuffer,
                           CTScreen** screen );
//-----------------------------------------------------------------------------
/**
    @brief
    Creates a new screen for displaying the session output.

    @param session
    A valid session handle.

    @param size
    A @c CTSize object specifying the size in pixels of the new screen.
    Range: [0 < width, height < 16384]

    @param colormode
    A @c CTColormode object specifying the pixel format of the screen buffer.
    NOTE: Only CM_RGB888, CM_BGR888, CM_ARGB8888,
    CM_BGRA8888, CM_RGBA8888, CM_RGB565 and CM_BGR565 are valid color modes.

    @param scanline
    The scanline of the screen image.
    NOTE: It is possible to specify a scanline >= (width * bytes per pixel).

    @param screenBuffer
    Optional pointer to a @c CTBuffer which specifies an external screen buffer
    into which all rendering will be performed. Ownership of the buffer will
    remain with the caller. See remarks section for more information.

    @param[out] screen
    Pointer to a @c CTScreen object which will receive the created
    screen. This argument is NULL if the function
    fails. The screen must be destroyed before its associated session is destroyed.

    @remarks
    If the @c screenBuffer argument is set to @c NULL, an internal screen buffer
    will be allocated. The screen pixels can be retrieved by calling
    caps_getScreenImage(). Note that caps_getScreenImage may be used also when
    using external screen buffers, in which case the @c pixels member of the retrieved
    @c CTImage will equal the screen buffer passed to this function.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @code
    CRESULT res = CERR_OK;
    CTSize screenSize = {230, 230};
    CTScreen* screen = 0;
    CTBuffer screenBuffer;
    CTSession sess;
    CTuint32 scanline;

    extern CTuint8* scrBuffer;

    res = caps_newSessionWithFile(_D("c:/testim.jpg"),
        IMAGE_FORMAT_JPEG, &sess);

    //Case 1: External screen buffer
    screenBuffer.data = scrBufferp;
    scanline = 232 * 3; //4 byte boundary
    screenBuffer.size = scanline * 230;
    res = caps_createScreenEx(sess, screenSize, CM_BGR888, scanline,
        &screenBuffer, &screen);
    //..
    //Add effects, render screen..
    //
    //Screen will be destroyed, screen buffer will not be destroyed
    caps_destroyScreen(screen);

    //Case 2: Internal screen buffer
    res = caps_createScreenEx(sess, screenSize, CM_BGR888, scanline,
        0, &screen);
    //..
    //Add effects, render screen..
    //
    //Screen and internal screen buffer will be destroyed
    caps_destroyScreen(screen);

    caps_destroySession(sess);
    @endcode

    @sa
    caps_setScreenBuffer()\n

    @since 3.7
*/
SCBIMPORT CRESULT caps_createScreenEx( CTSession session, CTSize size, CTuint32 scanline,
                           CTColormode colormode, CTBuffer* screenBuffer,
                           CTScreen** screen );
//-----------------------------------------------------------------------------
/**
    @brief
    Destroys a previously created screen. This function must be called before
    caps_destroySession().

    @param screen
    Pointer to the @c CTScreen object to destroy.

    @since 3.0
*/
SCBIMPORT void caps_destroyScreen( CTScreen* screen );
//-----------------------------------------------------------------------------
/**
    @brief
    Adds additional sharpness for the screen.

    @param screen
    A pointer to a screen object for which to set the sharpness factor.

    @param sharpness_level
    A CTint32 sharpness factor in the range 0 - 4, where 0 means off
    and 4 is the highest amount of sharpness.

    @note
    The effect will only be active on the screen image.
    If sharpness is desired to be applied when rendering to file or memory,
    caps_beginSharpness(), caps_setSharpness() and caps_endSharpness()
    must be used.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.5
*/
SCBIMPORT CRESULT caps_setScreenSharpness( CTScreen* screen, CTint32 sharpness_level );


//-----------------------------------------------------------------------------
/**
    @brief
    Adjust the RGB color appearance of the screen.

    @param screen
    A pointer to a screen object on which to adjust colors.

    @param r
    Red channel adjustment. Range (-1.0) - (1.0).
    
    @param g
    Green channel adjustment. Range (-1.0) - (1.0).
    
    @param b
    Blue channel adjustment. Range (-1.0) - (1.0).

    @note
    The effect will only affect the screen image. If RGB color adjustment is
    desired to be applied when rendering to file or memory, then
    caps_beginRGBColorAdjust(), caps_setRGBColorAdjust() and 
    caps_endRGBColorAdjust() must be used.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8 R4
*/
SCBIMPORT CRESULT caps_setScreenRgbAdjust( CTScreen* screen,
                                           CTfloat r,
                                           CTfloat g,
                                           CTfloat b );
//-----------------------------------------------------------------------------
/**
    @brief
    Dithering filter to prevent gradient errors.

    @param screen
    Handle to a valid @c CTScreen.

    @param status
    A @c CTbool. Set status to true if dithering should be enabled. If set to
    false it is disabled.

    @note
    Currently only screens with colormode CM_RGB565 and CM_BGR565 are
    supported by this function. There will not be any effect with any other
    colormode.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
*/
SCBIMPORT CRESULT caps_applyScreenDithering( CTScreen* screen, CTbool status );
//-----------------------------------------------------------------------------
/**
    @brief
    Rotates the current screen in 90 degrees steps.

    @param screen
    Handle to a valid @c CTScreen.

    @param rotation
    The angle into which the screen should be rotated. Can be any of the values
    from the @c ::CAPS_ROTATION enumeration.

    @note
    The effect will only be active on the screen image.
    If rotation is desired to be applied when rendering to file or memory,
    caps_beginRotate(), caps_setRotate() and caps_endRotate()
    must be used.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
*/
SCBIMPORT CRESULT caps_setScreenRotation( CTScreen* screen, CAPS_ROTATION rotation );
//-----------------------------------------------------------------------------
/**
    @brief
    Get the current screen rotation in 90 degrees steps.

    @param screen
    Handle to a valid @c CTScreen.

    @return
    @c ::CAPS_ROTATION enumeration. The angle into which the screen is
    rotated.

    @since 3.6
*/
SCBIMPORT CAPS_ROTATION caps_getScreenRotation( CTScreen* screen );
//-----------------------------------------------------------------------------
/**
    @brief
    Changes the screen buffer address of the given screen.

    @param screen
    Pointer to a @c CTScreen object previously created with
    caps_createScreen().

    @param screenBuffer
    Pointer to a @c CTBuffer object which specifies the new external screen
    buffer into which all rendering will be performed. Ownership of the buffer
    will remain with the caller.

    @remarks
    If an external screen buffer was passed to caps_createScreen() for this
    screen object, the old screen buffer can be deallocated safely after a
    successful call to this function.

    If the provided screen buffer is smaller in size from the previous one, the
    function returns CERR_INVALID_PARAMETER.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT caps_setScreenBuffer( CTScreen* screen, CTBuffer* screenBuffer );
//-----------------------------------------------------------------------------
/**
    @brief
    Renders the given screen.

    @param screen
    Pointer to the @c CTScreen object to render.

    @param it
    Optional pointer to a @c CTIterator object if the render operation should be performed
    as an iterative sequence, otherwise it should be set to @c NULL.
    @ref caps_iterators "Iterative operations"

    @attention
    The selected color mode in the format member in @c CTScreen::image must be one of
    the valid (output) formats specified in: @ref supported_colorformats

    @return
    - @c CERR_OK if successful or a specific error code upon failure.
    - @c CERR_ILLEGAL_CALL  If an iterative render operation is currently
    active when calling this function.
    .

    @since 3.0
*/
SCBIMPORT CRESULT caps_renderScreen( CTScreen* screen, CTIterator** it );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the image data of the given screen.

    @param screen
    Pointer to a @c CTScreen.

    @param[out] image
    Pointer to a @c CTImage object which will receive a pointer
    to the screen image data.
    The contents of the object is invalid after the screen object
    has been destroyed.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getScreenImage( CTScreen* screen, CTImage* image );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the size of the given screen.

    @param screen
    Pointer to the @c CTScreen object from which to retrieve size.

    @param[out] size
    Pointer to a @c CTSize object which will be initialized with the size
    of the given screen in pixels.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getScreenSize( CTScreen* screen, CTSize* size );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the top left corner and size of the canvas in the
    given screen.

    @param screen
    Pointer to the @c CTScreen object from which to retrieve the canvas area.

    @param[out] canvas_area
    Pointer to a CTRect object which will be initialized with the area
    information. The CTRect::x and CTRect::y members of the object will
    specify the offset in pixels of the canvas' top left corner, seen from the
    top left corner of the screen. The CTRect::w and CTRect::h members will
    specify the size of the canvas area in pixels.

    @remarks
    The screen canvas is the portion of the screen containing actual image
    data, excluding any borders created when fitting an image with preserved
    aspect ratio.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getScreenCanvasArea( CTScreen* screen, CTRect* canvas_area );
//-----------------------------------------------------------------------------
/**
    @brief
    Sets the zoom factor for the screen.

    @param screen
    A pointer to a screen object for which to set the zoom factor.

    @param zoom
    A floating point zoom factor in the range 1.0 - [inf].

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_setZoom( CTScreen* screen, CTfloat zoom );
//-----------------------------------------------------------------------------
/**
    @brief
    Sets zoom and pan for the screen, defined by middle point and zoom factor.

    @param screen
    A pointer to a screen object for which to set the zoom factor.

    @param zoom
    A floating point zoom factor in the range 1.0 - [inf].

    @param pMidpoint
    (IN/OUT) Input and output parameter. Sets the middle point of what should be
    shown in the screen in the @a current coordinate system. Internally this
    function uses the caps_setZoom and the caps_setPan functions. If the computed
    panning parameters would go outside of the [-1, 1] range, the values are clamped
    and the values of @c pMidpoint->x and @c pMidpoint->y are updated to match the
    clamped values.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa caps_setZoom
    @sa caps_setPan
    @sa caps_setZoomRect
    @sa caps_coordScreenToCurrent

    @since 3.5
*/
SCBIMPORT CRESULT caps_setZoomPoint( CTScreen* screen,
                          CTfloat    zoom,
                          CTPoint*   pMidpoint);
//-----------------------------------------------------------------------------
/**
    @brief
    Gets zoom and pan for the screen, defined by middle point and zoom factor.

    @param[in] screen
    A pointer to a screen object from which to get the zoom level and mid point.

    @param[out] pZoom
    Pointer to a floating point where the zoom factor is stored. May be NULL.

    @param[out] pMidpoint
    Gets the middle point of what should be shown in the screen in the
    @a current coordinate system.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa caps_getZoom
    @sa caps_getPan
    @sa caps_coordScreenToCurrent

    @since 3.8
*/
SCBIMPORT CRESULT caps_getZoomPoint( CTScreen* screen,
                           CTfloat*   pZoom,
                           CTPoint*   pMidpoint);
//-----------------------------------------------------------------------------
/**
    @brief
    Sets zoom and pan for the screen, defined by rectangle in
    current image coordinates. This function can be utilized for viewing an
    image in 1:1 scale, which can be used for avoiding problems with non-WYSIWYG effects.

    @param screen
    A pointer to a screen object for which to set the zoom factor.

    @param pZoomRect
    (IN/OUT) Input and output parameter. Sets the region
    shown in the screen in the @a current coordinate system. Internally this
    function uses the caps_setZoom and the caps_setPan functions.

    If the aspect ratio of the pZoomRect does not match the screen aspect ratio,
    the aspect ratio of the pZoomRect is changed to match the screen aspect ratio.

    If the zoom rectangle is outside of the current image area, it is moved inside
    the current image area.

    The maximum size of the zoom rectangle is the size of the current image area
    that is shown in scale 1. If the zoom rectangle size is larger than this,
    it is changed to this.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa caps_setZoom()
    @sa caps_setPan()
    @sa caps_setZoomPoint()
    @sa caps_coordScreenToCurrent()

    @code
    @par Example: Viewing an image in 1:1 scale

    //Start a session, create a screen...
    //...
    //...

    //Apply effect
    res = caps_beginEmboss(session);
    res = caps_setEmboss(session, 0.5f);
    caps_endEmboss(session);
    res = caps_getScreenSize(screen, &screenSize);

    rect.h = screenSize.h;
    rect.w = screenSize.w;
    rect.x = 0; //panning coordinate
    rect.y = 0; //panning coordinate

    res = caps_setZoomRect(screen, &rect);
    res = caps_renderScreen(screen, 0);
    //...
    //...
    @endcode

    @since 3.5
*/
SCBIMPORT CRESULT caps_setZoomRect( CTScreen* screen,
                                    CTRect* pZoomRect);
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the current zoom setting.

    @param screen
    Pointer to a screen object for which to retrieve the zoom factor.

    @param[out] zoom
    Pointer to a @c CTfloat which will receive the zoom factor.
    Range (1.0) - [inf].

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getZoom( CTScreen* screen, CTfloat* zoom );
//-----------------------------------------------------------------------------
/**
    @brief
    Sets the pan for the screen.

    @param screen
    Pointer to a screen object for which to set the pan.

    @param panX
    Horizontal pan setting. Range (-1.0) - (1.0).

    @param panY
    Vertical pan setting. Range (-1.0) - (1.0).

    @remarks
    The pan setting only affects the output image when rendering to raw memory
    buffer, since this is seen as the case where output is commonly used for
    screen.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @par Example:
    Move the center point in a zoomed image @c deltaX screen pixels horizontally and\n
    @c deltaY screen pixels vertically.

    @code
    CRESULT panDelta(CTScreen* screen, CTint32 deltaX, CTint32 deltaY, CTfloat* new_panX, CTfloat* new_panY)
    {
        CRESULT res = CERR_OK;
        CTSize  im = {0};
        CTSize  sc = {0};
        CTfloat zoom = 0.f, pan_dX = 0.f, pan_dY = 0.f;
        CTfloat panX = 0.f, panY = 0.f, ratio = 0.f;
        CTfloat panWidth = 0.f, panHeight = 0.f;
        CTPoint zero = {0}, movement = {0};
        CTSession session;
        CAPS_ROTATION rotation = ROTATE_TO_0;

        res = caps_getScreenSize(screen, &sc);
        rotation = caps_getScreenRotation(screen);
        res = caps_getScreenSession(screen, &session);
        res = caps_getCurrentImageSize(session, &im);
        res = caps_getZoom(screen, &zoom);

        ratio = (CTfloat) sc.h / (CTfloat) sc.w;

        if ((im.w / sc.w) > (im.h / sc.h))
        {
            panWidth  = (CTfloat) (im.w * (zoom - 1)) / zoom;
            panHeight = (CTfloat) im.h - (( (CTfloat) im.w / zoom) * ratio);
        }
        else
        {
            panHeight  = (CTfloat) im.h * ((zoom - 1) / zoom);
            panWidth = (CTfloat) im.w - (( (CTfloat) im.h / zoom) / ratio);
        }

        zero.x = 0;
        zero.y = 0;

        movement.x = ABS(deltaX);
        movement.y = ABS(deltaY);

        res = caps_coordCanvasToCurrent(screen, &zero);
        res = caps_coordCanvasToCurrent(screen, &movement);

        M_ROTATE(deltaX,deltaY,rotation,SWAPI);

        if (deltaX > 0)
        {
            deltaX = movement.x - zero.x;
        }
        else
        {
            deltaX = -(movement.x - zero.x);
        }

        if (deltaY > 0)
        {
            deltaY = movement.y - zero.y;
        }
        else
        {
            deltaY = -(movement.y - zero.y);
        }

            switch(rotation)
            {
                  case ROTATE_TO_0:
                        break;
                  case ROTATE_TO_90:
                        deltaY = -deltaY;
                        break;
                  case ROTATE_TO_180:
                        deltaX = -deltaX;
                        deltaY = -deltaY;
                        break;
                  case ROTATE_TO_270:
                        deltaX = -deltaX;
                        break;
                  default:
                        break;
            }

        if (panWidth > 0)
        {
            pan_dX = (CTfloat)(2 * deltaX) / panWidth;
        }

        if (panHeight > 0)
        {
            pan_dY = (CTfloat)(2 * deltaY) / panHeight;
        }

        res = caps_getPan(screen, &panX, &panY);

       *new_panX = panX + pan_dX;
       *new_panY = panY + pan_dY;

       *new_panX  = CLAMP2(*new_panX,-1.f,1.f);
       *new_panY  = CLAMP2(*new_panY,-1.f,1.f);

        //(void)caps_setPan(me->screen, new_panX, new_panY);

        return res;

    }

    #define SWAPI(a , b )\
    {\
        CTint32 tmp = a;\
        a = b;\
        b = tmp;\
    }

    #define M_ROTATE(X, Y, rot, swapfunc)\
    switch(rot)\
    {\
        case ROTATE_TO_0:\
            break;\
        case ROTATE_TO_90:\
            swapfunc(X, Y);\
            Y = -Y;\
            break;\
        case ROTATE_TO_180:\
            X = -X;\
            Y = -Y;\
            break;\
        case ROTATE_TO_270:\
            swapfunc(Y, X);\
            X = -X;\
            break;\
        default: \
            break;\
    }
    @endcode

    @since 3.0
*/
SCBIMPORT CRESULT caps_setPan( CTScreen* screen, CTfloat panX, CTfloat panY );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the current pan setting.

    @param screen
    Pointer to a screen object from which to get the pan.

    @param[out] panX
    Pointer to a @c CTfloat which will receive the current horizontal pan
    setting. Range (-1.0) - (1.0).

    @param[out] panY
    Pointer to a @c CTfloat which will receive the current vertical pan
    setting. Range (-1.0) - (1.0).

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getPan( CTScreen* screen, CTfloat* panX, CTfloat* panY );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the session within which a screen has been created.

    @param screen
    Pointer to a @c CTScreen object from which to retrieve the session.

    @param[out] session
    Pointer to a @c CTSession handle which will receive the session
    associated with the given screen.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getScreenSession( CTScreen* screen, CTSession* session );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the screen which was rendered to most recently.

    @param session
    A valid session handle.

    @param[out] screen
    Address of a @c CTScreen pointer which will receive the current
    screen.

    @remarks
    A screen object is "current" in a session after a call to
    caps_renderScreen(). If no such call has been made, or if other render
    operations has been performed since then, no screen will be current and
    this function will return @c NULL in the output argument.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
*/
SCBIMPORT CRESULT caps_getCurrentScreen( CTSession session, CTScreen** screen );
/**
    @}
*/ // end of group 'caps_baseapi_screen'
//=============================================================================


/**
    @addtogroup supported_colorformats
    @{
*/
/**
    @page supported_input_output_colormodes Supported colorformats

    The required byte size and the bit/byte packing order of each color format
    is described in ::CTColormode

    - @ref CM_AYUV4444
    - @ref CM_YUV422_UY1VY2
    - @ref CM_YUV422_Y1UY2V
    - @ref CM_YUV422P
    - @ref CM_YUV422SP
    - @ref CM_YVU422SP
    - @ref CM_YUV420P
    - @ref CM_YUV420SP
    - @ref CM_YVU420SP
    - @ref CM_ARGB8888
    - @ref CM_BGRA8888
    - @ref CM_RGBA8888
    - @ref CM_RGB888
    - @ref CM_BGR888
    - @ref CM_RGB444
    - @ref CM_BGR444
    - @ref CM_RGB565
	- @ref CM_RGB565D
	- @ref CM_RGB565FD
    - @ref CM_BGR565
    - @ref CM_RGB3553
    - @ref CM_ARGB6666
    - @ref CM_GBRGAR264462
    - @ref CM_BGRA6666
    - @ref CM_GBRG3553
    - @ref CM_GRBG3553
    - @ref CM_GRAY1
    - @ref CM_GRAY2
    - @ref CM_GRAY4
    - @ref CM_GRAY8
    - @ref CM_RGB565_G0
    - @ref CM_BGR565_G0
    .

    @note
    CM_YUV422 has been deprecated and is replaced by @ref CM_YUV422_UY1VY2.

    @note
    CM_YUV422_UY1VY2, CM_YUV422_Y1UY2V and CM_YUV420P
    requires the corresponding image width to be a multiple of two.

    <hr>
*/
//-----------------------------------------------------------------------------
/**
    @page supported_input_colormodes Additional input (only) colormodes
    - @ref CM_YUV422_VY2UY1
    - @ref CM_YUV420SP32
    .

    @note
    CM_YUV422R has been deprecated and is replaced by @ref CM_YUV422_VY2UY1.

    @note CM_YUV420SP32 requires the corresponding image width and height to
    be a multiple of two.

    <hr>
*/
//-----------------------------------------------------------------------------
/**
    @page supported_output_colormodes Additional output (only) colormodes
    - @ref CM_RGB565D (With dithering to minimize gradient errors)
    - @ref CM_RGB565FD (With dithering to minimize gradient errors. Faster but 
           less visual appealing than CM_RGB565D.)
    - @ref CM_BGR565D (With dithering to minimize gradient errors)
    - @ref CM_ARGB8565
	- @ref CM_RGBA5658
    - @ref CM_RGB666
    .
*/
/**
    @}
*/ // end of addtogroup supported_colorformats
//=============================================================================


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // !defined( CAPS_BASE_H )
