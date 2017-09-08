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

//-----------------------------------------------------------------------------
//    Example of implementation of read functions for file.
//-----------------------------------------------------------------------------

#ifndef CTSTREAM_FILE_H
#define CTSTREAM_FILE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "ctstream.h"
#include "oslfile.h"

//=============================================================================
/**
    @file ctstream_file.h
    @brief File based stream creation.
    @ingroup scb_ctstream_file
*/
//=============================================================================
/**
    @addtogroup scb_ctstream_file
    @brief Creation of file streams
    @{
*/

/**
    @brief
    Recommended default chunk size that gives a good trade-off between 
    performance and memory consumption.

    @sa ctstream_createFileStream
    @sa ctstream_createFileStreamEx
*/
#define CTSTREAM_FILE_CHUNK_SIZE 32768

//-----------------------------------------------------------------------------
/**
    @brief
    Creates a stream from a file handle.

    @param pFile A file handle created with @c oslfile_open

    @param chunkSize desired chunk reading size in bytes. The file will be 
    accessed in chunks of the size given in this parameter. This parameter should be 
    fine tuned to some optimal chunk size for the platform file system. 
    As recommended default size that gives a good trade-off between performance 
    and memory consumption use @c CTSTREAM_FILE_CHUNK_SIZE.

    @param[out] ppStream The created file stream.

    When the stream object (returned by this function) is no longer needed, it
    should be destroyed using: ctstream_destroy()

    @return
    @li @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8    
*/
SCBIMPORT CRESULT 
ctstream_createFileStream ( CTFile *pFile, 
                                    CTuint32 chunkSize, 
                                    CTStream **ppStream );
//-----------------------------------------------------------------------------
/**
    @brief
    Creates a stream from a file name.

    @param pFilename A file name for the file to use as the underlying 
    stream resource.
    @param flags Flag set to be used when opening the file. 
    See @c OSLFILE_OPEN_FLAGS.
    
    @param chunkSize This parameter should be 
    fine tuned to some optimal chunk size for the platform file system. 
    As recommended default size that gives a good trade-off between performance 
    and memory consumption use @c CTSTREAM_FILE_CHUNK_SIZE.

    @param[out] ppStream Pointer to an stream object.

    When the stream object (returned by this function) is no longer needed, it
    should be destroyed using: ctstream_destroy()

    @return
    @li @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_createFileStreamEx ( const DCHAR *pFilename, 
                                      OSLFILE_OPEN_FLAGS flags,
                                      CTuint32 chunkSize, 
                                      CTStream **ppStream );
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'scb_ctstream'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // CTSTREAM_FILE_H
