/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2009 Scalado AB. All rights reserved.                           .
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

#ifndef CTSTREAM_H
#define CTSTREAM_H

#include "scbdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @ingroup scb_ctstream
    @file ctstream.h
    @brief Public interface for the stream subsystem.
*/
//=============================================================================
/**
    @addtogroup scb_ctstream
    @brief Stream handling.

    CTStream provides a generic interface for stream operations. The interface
    can be implemented in different ways, and operate on different underlying
    media (e.g. memory, file, network stream).

    @par Note about usage
    Most functions that take a CTStream object as an input parameter and
    (temporarily) take ownership of a stream, will modify the stream state
    during their execution (e.g. reading from, and writing to, the stream).
    This means that streams can't normally be reused between calls, or objects.
    For instance, when a CAPS session is finished with a stream, that stream
    will not be automatically reset to the beginning.  A reason for this is that
    the streams may not represent a data source where it's possible to do a seek
    operation, such as a network connection. Also, there may be interesting data
    at the end of a stream. Thus resetting the stream would lead to inconsistent
    behavior, and complicate application development.

    @par
    The recommended way to get the same data again, is to recreate the stream
    from the same source. For some applications, where a stream is known to be a
    file, buffer, or some other medium where seek is supported, the stream can,
    alternatively, be reset to the beginnning by calling ctstream_seek() with 
    @c offset=0.

    @par Customizing CTStream
    For implementation of support for other stream types, see: @ref scb_ctstream_interface

    @{
        @defgroup scb_ctstream_buffer Buffer streams
        @defgroup scb_ctstream_file   File streams
*/
//--------------------------------------------------------------------------

/**
    @ingroup types_n_defs
    @brief
    Public object to represent generic streams.

    @sa CIStream.

    @since 3.8
*/
typedef struct CTStream CTStream;
//--------------------------------------------------------------------------
/**
    @brief
    Destroys a stream.

    @param pStream a valid pointer to a stream object, or NULL.

    @since 3.8
*/
SCBIMPORT void 
ctstream_destroy ( CTStream *pStream );
//--------------------------------------------------------------------------
/**
    @brief
    Returns the user data from the underlying stream.

    @param pStream a valid pointer to a stream object.

    @return pointer to the underlying stream user data.

    @since 3.8
*/
SCBIMPORT const void* 
ctstream_getContext ( CTStream *pStream );
//--------------------------------------------------------------------------
/**
    @brief
    Request a read data buffer.

    Requests a buffer with given amount of bytes from the stream,
    without blocking the caller.

    The requested buffer can be received in the readLock function
    at a later time.

    @param pStream A valid instance of a stream object.
    @param numBytes Amount of requested bytes.

    @since 3.8
*/

SCBIMPORT void 
ctstream_readRequest ( CTStream *pStream, CTuint32 numBytes );
//--------------------------------------------------------------------------
/**
    @brief
    Locks an internal stream buffer, that holds the requested data ( if available )
    or an error code.

    This function can block if the requested data has not yet been received
    by the underlaying stream.

    @param pStream A valid instance of a stream object.
    @param[out] ppData A buffer with the data requested. This buffer can 
    only be freed using ctstream_readRelase.
    @param[out] pReadBytes Number of bytes returned in the locked buffer.

    @return  @c CRESULT
    
    @li @c CRES_STREAM_DELAYED if there is no data available right now,
    but it will be available in a later moment. readLock should be called again
    until the requested data is available. In this case, pReadBytes will be 
    equal to 0.

    @li @c CERR_STREAM_END_OF_DATA if there is not enough data in the stream
    to fulfill the request ( typical case when the stream maps to a file, and
    there is no more data left to read from the file ). pReadBytes will 
    return the amount of data read.

    @li @c CERR_OK if the whole request could be fulfilled. pReadBytes will be
    equal to the amount of bytes requested in the request function.

    Other proper error codes that depends on the underlying stream or
    memory subsystem.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_readLock ( CTStream *pStream, 
                            CTuint8 **ppData, 
                            CTuint32 *pReadBytes );
//--------------------------------------------------------------------------
/**
    @brief
    Releases latest locked block of data.

    All locked blocks must be released with this function in order to 
    avoid resource leaks.

    For optimal performance, the user of this API should not keep 
    locked buffers for future use. If it is required to store the locked data
    for future use, it is recommended to copy this buffer to a 
    local buffer.

    @param pStream A valid instance of a stream object.
    @param usedBytes Amount of bytes read from the locked buffer.

    @since 3.8
*/
SCBIMPORT void 
ctstream_readRelease ( CTStream *pStream, CTuint32 usedBytes );
//-----------------------------------------------------------------------------
/**
    @brief
    Returns a locked buffer for writing of numBytes in size. 

    @param pStream A valid instance of a stream object.
    @param numBytes Number of bytes to lock.
    @param[out] ppBuffer Pointer to locked buffer.
    @param[out] pLockedBytes Number of bytes actually locked. With some streams 
    with constrained capacity, this value may be less than the actually requested. 

    @return @c CRESULT with proper error code. This function does not block 
    and does not delay. But it can return CERR_STREAM_END_OF_DATA, and in that
    case, pLockedBytes will be less than the required amount.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_writeLock( CTStream *pStream,
                    CTuint32 numBytes,
                    CTuint8 **ppBuffer,
                    CTuint32 *pLockedBytes );
//-----------------------------------------------------------------------------
/**
    @brief
    Tells the underlying stream, how many bytes are actually written to
    the locked buffer, and can start an synchronous operation if the
    underlying stream supports it.

    @param[in] pStream 
    A valid instance of a stream object.

    @param[in] writtenBytes 
    Amount of bytes written to the locked buffer. This value must be lower than
    or equal to the number of bytes previously locked.

    @since 3.8
*/
SCBIMPORT void 
ctstream_writeRespond ( CTStream *pStream, CTuint32 writtenBytes );
//--------------------------------------------------------------------------
/**
    @brief
    Release previous locked buffer. This function can delay.

    @param pStream A valid instance of a stream object.

    @return @c CRESULT
    
    @li @c CRES_STREAM_DELAYED 
    If it is not possible to write the data now, but it will be possible in
    a later moment. This function should be called successively until another
    result code is returned.

    Other proper error codes that depends on the underlying stream or
    memory subsystem.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_writeRelease ( CTStream *pStream );
//--------------------------------------------------------------------------
/**
    @brief
    Flush all internal buffers to the underlying stream.
    This function shall be used to guarantee that the data is 
    actually written.

    This function can delay.

    @param pStream A valid instance of a stream object.

    @return @c CRESULT
    
    @li @c CRES_STREAM_DELAYED 
    If it is not possible to write the data now, but it will be possible in
    a later moment. This function should be called successively until another
    result code is returned.

    Other proper error codes that depends on the underlying stream or
    memory subsystem.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_writeFlush ( CTStream *pStream );
//--------------------------------------------------------------------------
/**
    @brief
    Skips @c numBytes from the stream.

    @param pStream A valid instance of a stream object.
    @param numBytes Amount of bytes to skip.

    @since 3.8
*/
SCBIMPORT void 
ctstream_skip ( CTStream *pStream, CTuint32 numBytes );
//--------------------------------------------------------------------------
/**
    @brief
    This function returns true if the underlaying stream supports
    seeking to absolute positions.
    
    If this function returns true,
    it also means that the stream can return the current position
    with the tell function.

    @param pStream A valid instance of a stream object.
    @return @c true if the stream can seek, @c false otherwise.

    @since 3.8
*/
SCBIMPORT CTbool 
ctstream_canSeek ( CTStream *pStream );
//--------------------------------------------------------------------------
/**
    @brief
    Seeks into the stream to offset position.
    
    The seek is absolute, but it should not be assumed that
    a just created stream is positioned at offset 0. 
    The tell function should be used to determine the initial 
    stream position.

    @param pStream A valid instance of a stream object.
    @param offset Absolute offset where to seek.

    @since 3.8
*/
SCBIMPORT void 
ctstream_seek ( CTStream *pStream, CTuint32 offset );
//--------------------------------------------------------------------------
/**
    @brief
    returns the current stream position ( if available ).

    canSeek must be used to determine if the function can return 
    the current position.

    @param pStream A valid instance of a stream object.
    @param[out] pOffset current global offset position.

    @return @c CRESULT with proper error code.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_tell ( CTStream *pStream, CTuint32 *pOffset );
//--------------------------------------------------------------------------
/**
    @brief
    Aborts the current stream operation.

    This function shall be used if all ongoing operations are going to 
    be aborted. An example of use is in the case a reading stream has started
    a request, but a subsequent lock is not necessary. 
    
    It will also clear possible old error states.

    Calling abort will let the stream in a usable state.

    @param pStream A valid instance of a stream object.

    @since 3.8
*/
SCBIMPORT void 
ctstream_abort ( CTStream *pStream );
//--------------------------------------------------------------------------
/**
    @brief
    Copy data from a read enabled source stream to a write enabled destination
    stream.

    @param pSrcStream read enabled stream where the data is going to be copied from.
    @param pDstStream write enabled stream where the data is going to be copied to.

    @param numBytes Number of bytes to copy. Special value 0, can be used
    for copying all of the data in pSrcStream from the current position
    to the end of the stream.

    @param copyChunkSize A performance parameter. This will specify the
    size in bytes of the chunks used to make the copy operation. A large value
    can increase performance but also increase the memory consumption, while a 
    small value can decrease performance.
    
    If this parameter is set to zero, the function will estimate chunk size 
    based on the internal characteristics of the stream, which will give a good
    trade-off between performance and memory consumption.

    @return @c CRESULT
    
    @li @c CRES_STREAM_DELAYED 
    If it is not possible to write the data now, but it will be possible in
    a later moment. This function should be called successively until another
    result code is returned.

    Other proper error codes that depends on the underlying stream or
    memory subsystem.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_copy ( CTStream *pSrcStream, 
                CTStream *pDstStream, 
                CTuint32 numBytes,
                CTuint32 copyChunkSize );

//-----------------------------------------------------------------------------
/**
    @brief
    This function returns an estimation of the remaining size of the 
    internal chunk (data cache) for a stream. 
    The size can be used too minimize overhead in the stream when requesting 
    data and is then used as number of bytes to request.

    @param pStream A valid instance of a stream object.
    @param[out] pChunkSize Address of @c CTuint32 variable which will 
    receive the chunk size.

    @remark
    The size can change between consecutive read or write calls.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8.2 R01
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT
ctstream_getRemainingChunkSize( CTStream *pStream, CTuint32 *pChunkSize );

//-----------------------------------------------------------------------------
/**
    @brief
    Set current position in the stream to origin.
    
    @param[in] pStream
    A valid instance of a stream object.

    @remark
    Origin only affect ctstream_seek() and ctstream_tell(), it will not 
    change the absolute stream position.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    ctstream_popOrigin()

    @since 3.8
*/
//--------------------------------------------------------------------------
SCBIMPORT CRESULT 
ctstream_pushOrigin( CTStream *pStream );

//--------------------------------------------------------------------------
/**
    @brief
    Restore previous origin point.

    @param[in] pStream
    A valid instance of a stream object.

    @remark
    Origin only affect ctstream_seek() and ctstream_tell(), it will not 
    change the absolute stream position.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
//--------------------------------------------------------------------------
SCBIMPORT CRESULT 
ctstream_popOrigin( CTStream *pStream );

//--------------------------------------------------------------------------
/**
    @brief
    Retrieves the auxiliary data associated with this stream

    @param[in] pStream
    Stream pointer to retrieve aux data from.

    @param[out] ppAuxData
    Data to retrieve.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
//--------------------------------------------------------------------------
SCBIMPORT CRESULT 
ctstream_auxData ( CTStream *pStream, void** ppAuxData );


//--------------------------------------------------------------------------
/**
    @brief
    Sets the aux data associated with this stream.

    @param[in] pStream
    Stream pointer to retrieve aux data from.

    @param[out] pAuxData
    Pointer to data to set as aux data.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
//--------------------------------------------------------------------------
SCBIMPORT CRESULT 
ctstream_setAuxData ( CTStream *pStream, void* pAuxData );

/**
    @}
*/ // end of addtogroup 'scb_ctstream'
//--------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif


#endif 
