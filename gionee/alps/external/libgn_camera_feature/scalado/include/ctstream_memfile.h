/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2011 Scalado AB. All rights reserved.                             .
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


#ifndef CTSTREAM_MEMFILE_H
#define CTSTREAM_MEMFILE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "ctstream.h"
#include "oslfile.h"


//=============================================================================
/**
    @file ctstream_memfile.h
    @brief Memory mapped file based stream creation.
    @ingroup scb_ctstream_memfile
*/
//=============================================================================
/**
    @addtogroup scb_ctstream_memfile
    @brief Creation of memory mapped file streams
    @{
*/

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a memory mapped stream from a file name.
    The memory mapped file stream only supports reading, but is considerably 
    faster than ctstream_file on some platforms.    

    @param pFilename A file name for the file to use as the underlying 
    stream resource.

    @param[out] ppStream The created file stream.

    When the stream object (returned by this function) is no longer needed, it
    should be destroyed using: ctstream_destroy()

    @return
    @li @c CERR_OK if successful or a specific error code upon failure. Returns
    CERR_NOT_IMPLEMENTED on platforms where it isn't supported.

    @note
    This stream type is not available on all platforms.

    @since 5.3
*/
SCBIMPORT CRESULT 
ctstream_createMemFileStream(const DCHAR *pFilename,
                             CTStream **ppStream);

//-----------------------------------------------------------------------------
/**
    @brief
    If memory mapped streams are supported on the platform a memory mapped 
    stream is created, otherwise a normal file stream is created.

    @param pFilename A file name for the file to use as the underlying 
    stream resource.

    @param chunkSize This parameter should be 
    fine tuned to some optimal chunk size for the platform file system. 
    As recommended default size that gives a good trade-off between performance 
    and memory consumption use @c CTSTREAM_FILE_CHUNK_SIZE.
    If a memory mapped file stream is created, this parameter is ignored.

    @param[out] ppStream The created file stream.

    When the stream object (returned by this function) is no longer needed, it
    should be destroyed using: ctstream_destroy()

    @return
    @li @c CERR_OK if successful or a specific error code upon failure. 

    @since 5.3
*/
SCBIMPORT CRESULT 
ctstream_createMemFileOrFileStream(const DCHAR *pFilename,
                                   CTuint32 chunkSize,
                                   CTStream **ppStream);

//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'scb_ctstream_memfile'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // CTSTREAM_MEMFILE_H
