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

#ifndef CISTREAM_H
#define CISTREAM_H

#include "scbdefs.h"
#include "ctstream.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CIStream CIStream;


//=============================================================================
/**
    @ingroup scb_ctstream_interface
    @file cistream.h
    @brief Header for the stream interface.
*/
//=============================================================================
/**
    @addtogroup scb_ctstream_interface
    @brief Low level stream interface
    
    The CIStream interface is the virtual low-level stream interface. If
    support is needed for other stream types than file/buffer
    (see  @ref scb_ctstream_file/@ref scb_ctstream_buffer), an
    implementation of this interface must be provided.

    For creation of file- and buffer-based streams, see:
    - @ref ctstream_createBufferStream()
    - @ref ctstream_createFileStream()
    - @ref ctstream_createFileStreamEx()
    .

    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief
    Creates a @c CTStream object.

    Creates a @c CTStream object using the provided interface.

    @param pInterface Pointer to an stream interface. @sa CIStream.
    @param pContext Pointer to user data related to one specific stream.
    @param[out] ppStream Pointer to a newly created stream.

    When the stream object (returned by this function) is no longer needed, it
    should be destroyed using: ctstream_destroy()

    @return A @c CRESULT result code.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_create ( const CIStream *pInterface,
                  void *pContext,
                  CTStream **ppStream );
//-----------------------------------------------------------------------------
/**
    @interface CIStream
    @brief Low level stream interface.

    This interface provides a mean to extend stream handling to generic types.

    The CIStream interface is the virtual low-level stream interface. To add
    support for a new stream type, an implementation of this interface must be
    provided. It is the responsibility of the provider of this implementation
    to assure that each function executes the @em proper operation on the
    underlying data (stream); i.e. @em proper meaning that it exactly match
    the description/behavior specified below.

    @since 3.8
*/
struct CIStream
{
    /**
        @brief Requests a block of data from the stream.

        This function tells the underlying stream that a chunk of
        data is required, and it will be expected in a subsequent call 
        to @c readLock. 

        In an asynchronous operation, this function could start the
        fetching of data for better performance.

        Note that it is not possible to perform a request more than one at a
        time, until a lock has been performed.

        @param pContext Pointer to user specific data for this stream.
        @param numBytes Number of bytes to request.

        @return @c CRESULT
    */
    CRESULT (*readRequest) ( void *pContext, CTuint32 numBytes );
    //.........................................................................
    /**
        @brief Locks a buffer of a previously requested size.

        This function will provide a buffer of the requested size
        or it will delay if the data is not available at the moment
        of the call.
        
        The amount of bytes received can less than the requested amount
        if the stream has reached the end of data.

        Note that it is not possible to lock more than one buffer at
        a time.

        @param pContext Pointer to user specific data for this stream.
        @param[out] ppData A pointer to the buffer containing the data.
        @param[out] pReadBytes Amount of bytes actually delivered.

        @return A @c CRESULT result code, where these are specific for this 
        interface:

        @li @c CRES_STREAM_DELAYED - If data will be available in a later time. 
        @li @c CERR_STREAM_END_OF_DATA - If the stream has reached the end of data.
        @li @c CERR_ALREADY_LOCKED - If the stream is already in lock state.

        Note: While the stream is delayed, it cannot be used until this function
        return CERR_OK or other status code.
    */
    CRESULT (*readLock)    ( void *pContext, 
                             CTuint8 **ppData, 
                             CTuint32 *pReadBytes );
    //.........................................................................
    /**
        @brief Release a last locked buffer.

        This function tells the underlying stream that the previously
        locked buffer is no longer required. The integration may reuse
        this buffer for future locks.

        @param pContext Pointer to user specific data for this stream.
        @param usedBytes Amount of bytes actually read from the locked
        buffer.
    */
    void (*readRelease) ( void *pContext, CTuint32 usedBytes );
    //.........................................................................
    /**
        @brief Skips data from the stream.

        @param pContext Pointer to user specific data for this stream.
        @param numbytes Number of bytes to skip.

        @return A @c CRESULT result code.
    */
    CRESULT (*skip) ( void *pContext, CTuint32 numBytes );
    //.........................................................................
    /**
       @brief Seeks to a determined offset in the stream.

       This function is optional ( but highly recommended ). 
       The upper layers may skip some functionality if this 
       function is omitted, or will lead to less optimal algorithms.

       @param pContext Pointer to user specific data for this stream.
       @param offset Global offset where to move the stream pointer.
       
       @return A @c CRESULT result code.
    */
    CRESULT (*seek) ( void *pContext, CTuint32 offset );
    //.........................................................................
    /**
        @brief Tells the current global offset pointer.
        
        Note that this function is mandatory: it has to be
        implemented even if seek is not present.

        @param pContext Pointer to user specific data for this stream.
        @param[out] pOffset offset Global offset where to move the stream pointer.
       
        @return A @c CRESULT result code.
    */
    CRESULT (*tell) ( void *pContext, CTuint32 *pOffset );
    //.........................................................................
    /**
        @brief Locks a write buffer. 
        
        This function should return a pointer to a buffer of @c numBytes in size
        or smaller. In this buffer data will be written to, and later translated
        to the underlying stream ( after @c writeRespond ).

        This function should not delay.

        @param pContext Pointer to user specific data for this stream.
        @param numBytes Amount of bytes requested to be locked.
        @param[out] ppData Pointer to the locked buffer.
        @param[out] pLockedBytes Amount of bytes actually locked.

        @return A @c CRESULT result code.
    */
    CRESULT (*writeLock) ( void *pContext, 
                           CTuint32 numBytes,
                           CTuint8 **ppData,
                           CTuint32 *pLockedBytes );
    //.........................................................................
    /**
        Tells the underlying stream that the locked buffer for writing
        is not needed anymore and that it can be translated to the 
        underlying stream.
    
        @param pContext Pointer to user specific data for this stream.
        @param usedBytes Amount of bytes actually written to the buffer.
    */
    void (*writeRespond) ( void *pContext, CTuint32 usedBytes );
    //.........................................................................
    /**
        @brief Releases a write locked buffer.
        
        @param pContext Pointer to user specific data for this stream.

        @return A @c CRESULT result code, where these are specific for this 
        interface:

        @li @c CRES_STREAM_DELAYED - If data will be written in a later time.
        Note: the stream cannot be used until this function returns @c CERR_OK.
    */
    CRESULT (*writeRelease) ( void *pContext );
    //.........................................................................
    /**
        @brief Flushes all data to the underlying stream.

        This function must be used to guarantee that all data has been written
        to the underlying stream. 

        @param pContext Pointer to user specific data for this stream.

        @return A @c CRESULT result code, where these are specific for this 
        interface:

        @li @c CRES_STREAM_DELAYED - If data will be written in a later time.
        Note: the stream cannot be used until this function returns @c CERR_OK.
    */
    CRESULT (*writeFlush) ( void *pContext );
    //.........................................................................
    /**
        @brief Destroys the underlying stream.

        @param pContext Pointer to user specific data for this stream.
    */
    void (*destroy) ( void *pContext );
    //.........................................................................
    /**
        @brief Returns the internal working chunk size ( where it applies ).

        The size returned should be the amount of bytes left in the 
        internal chunk ( data cache ), if the stream actually have such
        a chunk.

        @param pContext Pointer to user specific data for this stream.
        @param[out] pChunkSize Returned amount of bytes left in the current chunk.
    */
    void (*chunkSize) ( void *pContext, CTuint32 *pChunkSize );
    //.........................................................................
};
// end of 'struct CIStream'
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'scb_ctstream_interface'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif
