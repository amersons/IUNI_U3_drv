/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2010 Scalado AB. All rights reserved.                           .
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

#ifndef OSLFILE_H
#define OSLFILE_H

#include "scbdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/** 
    @file oslfile.h
    @brief Declares the virtual interface (used internally in CAPS), providing
    support for file management.

    It is strongly recommended that an underlying implementation of this
    virtual file interface is based on a buffered file API in order to get the
    best performance from CAPS and other software based on CAPS.
*/
//=============================================================================
/** 
    @addtogroup os_file
    @brief Mapping of basic OS file functionality.

    These function declarations are found in the header file: oslfile.h
    
    @{
*/
//-----------------------------------------------------------------------------

#ifndef OSLFILE_CTFILE
#define OSLFILE_CTFILE
//-----------------------------------------------------------------------------
/**
    @brief The generic file handle type.
*/
typedef struct CTFile CTFile;
//-----------------------------------------------------------------------------
#endif

/** See: oslfile_seek().*/
#define OSLFILE_SEEK_CUR   1
/** See: oslfile_seek().*/
#define OSLFILE_SEEK_SET   2
#define OSLFILE_SEEK_END   3 

//-----------------------------------------------------------------------------
/**
    @brief
    Flags for specifying access rights, mode and share policy when opening
    a file with oslfile_open().

    The following behavior is expected in oslfile_open():
    <table width="80%" border="1">
        <tr>
            <th align="left">Flag</td>
            <th align="left">If file exist</td>
            <th align="left">If file does not exist</td>
        </tr>
        <tr>
            <td>FOF_ACCESS_READ</td>
            <td>CERR_OK</td>
            <td>CERR_FILE_NOT_FOUND</td>
        </tr>
        <tr>
            <td>FOF_ACCESS_WRITE</td>
            <td><i>create empty file</i></td>
            <td><i>create empty file</i></td>
        </tr>
    </table>
*/
typedef enum
{
    /** @brief The file is opened with read-only access (default). */
    FOF_ACCESS_READ         = 0x00000001,
    
    /** @brief The file is opened with write access. */
    FOF_ACCESS_WRITE        = 0x00000002,
    
    /** @brief The file is opened with read and write access. */
    FOF_ACCESS_READWRITE    = 0x00000003,
    
    /**
        @deprecated

        This behaviour is default. The file is opened in binary
        mode (default). This is the only behavior guaranteed to work
    */
    FOF_MODE_BINARY         = 0x00000010,
    
    /**
        @brief Optional support. If the file system does not support this,
        open as binary.
    */
    FOF_MODE_TEXT           = 0x00000020,

    /**
        @deprecated

        Optional support. If the file system does not support this,
        ignore. The file may not be opened by other processes.
    */
    FOF_SHARE_EXCLUSIVE     = 0x00000100,

	/**
        @deprecated

        Optional support. If the file system does not support this,
        ignore. The file may only be opened by other processes for reading.
    */
    FOF_SHARE_READONLY      = 0x00000200,
    
    /**
        @deprecated

        Optional support. If the file system does not support this,
        ignore. The file may be shared by other processes for both reading and
        writing (default).
    */
    FOF_SHARE_FULL          = 0x00000400,

    /**
        @brief
        File system implementation may ignore this.
        This flag can only be used together with read and write access. When 
        this flag is enabled, files will not be truncated when opened with write
        access.
    */
    FOF_BEHAVE_NO_REPLACE   = 0x00001000,

    FOF_DUMMY_MIN = -1,
    FOF_DUMMY_MAX = 0x7fffffff

} FOF_DUMMY;
//-----------------------------------------------------------------------------

typedef CTint32 OSLFILE_OPEN_FLAGS;

//-----------------------------------------------------------------------------
/**
    @brief
    Opens a file from the local file system.

    @param pFilename    File system path to the requested file.

    @param flags        The access rights, mode and share policy to use when
                        opening the file. See FILE_OPEN_FLAGS for details.

    @param ppOutFile    Address of a CTFile pointer which will receive the 
                        opened file.

    @remarks
    The file handle returned in pOutFile should be closed with oslfile_close()
    when no longer needed. This file will not create subdirectories when opening
    a file for writing. CERR_FILE_NOT_FOUND is returned if a file can not be
    created because sub directories are missing.
    @n@n
    The file pointer is always positioned at the beginning of the file, even
    when FOF_ACCESS_READWRITE is used.

    @return CERR_OK if successful or a specific error code upon failure.
*/
CRESULT oslfile_open( const DCHAR* pFilename, 
                      OSLFILE_OPEN_FLAGS flags, 
                      CTFile **ppOutFile );
//-----------------------------------------------------------------------------
/** 
    @brief
    Closes a file previously opened with oslfile_open().

    @param pFile        A CTFile pointer specifying an open file.
*/
void oslfile_close( CTFile *pFile );
//-----------------------------------------------------------------------------
/**
    @brief
    Reads the specified number of bytes from a file.

    @param pFile        A CTFile pointer specifying an open file.

    @param pBuffer      Buffer to which data will be read. Cannot be zero and
                        must be of at least \p count size in bytes.
    @param count        Number of bytes to read from the file.

    @return Number of bytes actually read from the file. Zero is returned if 
    no data can be read or if an error occurred.
 */
CTuint32 oslfile_read( CTFile *pFile, void *pBuffer, CTuint32 count );
//-----------------------------------------------------------------------------
/**
    @brief
    Writes a specified amount of data to a file.

    @param pFile        CTFile pointer specifying an open file.

    @param pBuffer      Buffer with data to be written. Cannot be zero and must
                        be of at least \p count size in bytes.
    @param count        Number of bytes to be written.

    @return Number of bytes actually written to the file. Zero is returned if 
    no data can be read or if an error occurred.
*/
CTuint32 oslfile_write( CTFile *pFile, const void *pBuffer, CTuint32 count );
//-----------------------------------------------------------------------------
/**
    @brief
    Forces any pending buffered output to be written to a file.

    @param pFile        CTFile pointer specifying an open file.

    @return @c CERR_OK if successful, otherwise an error code.
*/
CRESULT oslfile_flush( CTFile *pFile );
//-----------------------------------------------------------------------------
/**
    @brief
    Checks whether an end-of-file indicator has been set for a file.

    @param pFile        CTFile pointer specifying an open file.

    @return
    - @c true, if end-of-file indicator is set.
    - @c false, otherwise.
    .
 */
CTbool oslfile_eof( const CTFile *pFile );
//-----------------------------------------------------------------------------
/**
    @brief
    Changes the current read/write position.

    @param pFile        CTFile pointer specifying an open file.

    @param offset       Offset to seek from the position specified by \em mode.

    @param mode         The seek mode, see remarks section for details.

    @remarks
    The @c mode argument can be one of the following values:
    - OSLFILE_SEEK_CUR - The @c offset is from the current position.
    - OSLFILE_SEEK_SET - The @c offset is from the beginning of the file.
    .

    @return CERR_OK if successful, otherwise an error code.
 */
CRESULT oslfile_seek( CTFile *pFile, CTint32 offset, CTint32 mode );
//-----------------------------------------------------------------------------
/**
    @brief
    Retrieves the current read/write file position.

    @param pFile        CTFile pointer specifying an open file.

    @param pOutPos      CTuint32 pointer which will receive the position.
        
    @return CERR_OK if successful, otherwise a specific error code.
 */
CRESULT oslfile_pos( CTFile *pFile, CTuint32 *pOutPos );

//-----------------------------------------------------------------------------
/**
    @brief
    Determines the size of a file.

    @param pFile        CTFile pointer specifying an open file.

    @return The size of the file in bytes. 
 */
CTuint32 oslfile_size( CTFile *pFile );
//-----------------------------------------------------------------------------
/**
    @brief
    Removes a file from the file system.

    @param pFilename    Name of the file to be removed.

    @return CERR_OK if successful, otherwise an error code.
 */
CRESULT oslfile_remove( const DCHAR *pFilename );
//-----------------------------------------------------------------------------
/**
    @}
*/ // end addtogroup 'os_file'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef SCB_DBGMODE_FILE
#include "scbdbg_file.h"
#endif

#endif // !defined( OSLFILE_H )
