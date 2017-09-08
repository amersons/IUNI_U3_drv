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

#ifndef OSLDIR_H
#define OSLDIR_H

#include "scbdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/** 
    @file osldir.h
    Declares the virtual interface (used internally in CAPS), providing
    support for directory  management.
    @ingroup os_dir
*/
//=============================================================================
/** 
    @addtogroup os_dir
    @brief Mapping of basic operating system directory functionality.

    These function declarations are found in the header file: osldir.h
    
    @{
*/
//-----------------------------------------------------------------------------


/**
    @brief Maximum path length in characters for a file or a directory entry.
*/
#define OSLDIR_MAX_PATH_LENGTH (260)

/*
    If compile errors appear here, the default Scalado file path length 
    changed. Resolve the mismatch by altering the OSLDIR_MAX_PATH_LENGTH to 
    the same value as that used by Scalado.
*/
SCB_STATIC_ASSERT( OSLDIR_MAX_PATH_LENGTH == SCB_MAXPATH );


/** 
    @brief 
    Provides access to the items contained in a directory
	(i.e. files and subfolders).

	@see
	- ctdirlist_create()
	- ctdirlist_next()
	.

*/
typedef struct CTDirList CTDirList;
//-----------------------------------------------------------------------------

/**
    @brief Content specifiers for ::CTDirEntry.
*/
typedef enum
{
    OSLDIR_TYPE_UNKNOWN, ///< The type of the entry is unknown.

    OSLDIR_TYPE_FILE,    ///< The type of the entry is a file.

    OSLDIR_TYPE_DIR      ///< The type of the entry is a dir.
} CTDirEntryType;
//-----------------------------------------------------------------------------

/**
    @brief Flags for specifying which fields have been filled for a ::CTDirEntry.
*/
typedef enum
{
    /**
        @brief  The @c size field of @c CTDirEntry has been filled.
    */
    OSLDIR_FIELD_SIZE = 0x01,

    /**
        @brief The @c timeWrite field of @c CTDirEntry has been filled.
    */
    OSLDIR_FIELD_TIMEWRITE = 0x02
} CTDirListFields;
//-----------------------------------------------------------------------------

/**
    @brief Structure holding information about a directory entry returned from
    ::ctdirlist_next()
*/
typedef struct CTDirEntry
{
    /** 
        @brief
		The entry name without the path (i.e not a fully qualified file name).

		In case of a directory the entry name is the difference compared
		to the parent directory.

        @since 1.0
    */
    DCHAR name[OSLDIR_MAX_PATH_LENGTH];

    /** 
        @brief The entry type.

        @since 1.0
    */
    CTDirEntryType type;

    /** 
        @brief  The entry size in bytes.

        @since 1.0
    */
    CTuint32 size;      

    /** 
        @brief  The last write time in seconds of the entry.

        @since 1.0
    */
    CTuint32 timeWrite;

    /**
        @brief Creation time of the entry.

        @since 3.10
    */
    CTuint32 timeCreate;

	/**
		@brief
		Extension of the name if applicable.

        This is, on most operating systems, the part of the filename after the
		last '.'. Eg: jpg, txt, ext etc. The '.' must not be included in the
        extension. If the file does not have an extension, then this member 
        points to an empty string, so that *(pDirEntry->pExtension) == 0.

		@since 3.10
	*/
	const DCHAR *pExtension;

} CTDirEntry;
//-----------------------------------------------------------------------------

/**
    @brief
    Creates and initializes a @c CTDirList for iterating all the entries
    (files and directories) in a directory.

    Operating system-specific additions such as "." or ".." are filtered
    out before the results are returned.
    
    @param pDirectory
    Pointer to the directory path to iterate on. The string must not contain
    a trailing separator character. May not be 0.

    @param[out] ppDirList
    Directory iterator returned by the function.

    @return
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    - ::CTDirEntry
	- ctdirlist_next();
	- ctdirlist_destroy();
	.

    @since 3.10
*/
CRESULT ctdirlist_create( const DCHAR *pDirectory,
						  CTDirList **ppDirList );

//-----------------------------------------------------------------------------
/**
    @brief
    This method retrieves the next valid @c CTDirEntry in the current listing.
    
    @param pDirList
    Pointer to an initialized @c CTDirList instance.

    @param pEntry
    Pointer to an existing @c CTDirEntry instance to be filled with info
    for the next entry in the iteration.

    @return
    - CERR_OK if info for another @c CTDirEntry was successfully retrieved.
    - CERR_TASK_COMPLETE if there are no more items to retrieve.
    - Otherwise an error code.
    .

    @since 3.10
*/
CRESULT ctdirlist_next( CTDirList *pDirList,
					    CTDirEntry *pEntry );
//-----------------------------------------------------------------------------

/**
    @brief
    This method destroys the @c CTDirList instance.
    
    @param pDirList
    A pointer to a @c CTDirList instance or 0.

    @since 3.10
*/
void ctdirlist_destroy( CTDirList *pDirList );
//-----------------------------------------------------------------------------

/**
    @brief Creates a directory with the given path name.

    @param pDirectory
	The path name of the directory to create.

    @return
    CERR_OK if the leaf directory was created successfully or the leaf directory
    already existed, otherwise an error code.

    @remarks
    If the path name consists of a directory hierarchy, all needed parent 
    directories are also created as part of this call.

	@since 3.10
*/
CRESULT osldir_makeDir( const DCHAR *pDirectory );
//-----------------------------------------------------------------------------

/**
    @brief Removes directories recursively.

    The function removes the given directory by removing all files/directories
    inside it and finally the directory itself.

    @param pDirectory 
    String pointer to the directory to destroy.

    @return
    CERR_OK if the leaf directory was removed successfully, otherwise an error code.

	@since 3.10
*/
CRESULT osldir_removeDir( const DCHAR *pDirectory );
//-----------------------------------------------------------------------------

/**
    @brief This function creates a new fully qualified path name by joining the 
    directory with the file name.

    @param pDirectory
    Directory name. If this is an empty string, pFilename will be returned in 
    pFullPath. This directory may optionally end with a separator character, 
    but if not, one is appended automatically unless the string is a zero 
    length string.

    @param pFilename
    File name. If the file name contains a directory separator, the portion of 
    the file to the left of the separator is considered part of pDirectory for 
    the purpose of joining.

    @param pFullPath
    Pointer to a string where the full path name is stored.

    @param fullPathMaxLength
    Maximum length of the pFullPath string variable (typically set to the
    allocated length).

    @return
    A const pointer to the separator string.

	@since 3.10
*/
CRESULT osldir_join( const DCHAR *pDirectory, 
                     const DCHAR *pFilename, 
                     DCHAR *pFullPath, 
                     CTuint32 fullPathMaxLength );
//-----------------------------------------------------------------------------

/**
    @brief This function splits a path into a directory and filename component.

    @param pFullPath
    Fully qualified path name to split.

    @param pDirectory
    Pointer where the directory string is stored. At least maxOutputLength
    characters (DCHAR) must be allocated for the directory name. The output
    directory will always end with a separator unless a relative path name
    is specified where the directory portion is empty. This is the case only 
    when pFullPath is exactly a file name.

    @param pFilename
    Pointer where the file name will be stored. At least maxOutputLength
    characters (DCHAR) must be allocated for the file name. pFilename must
    never contain any directory separators.

    @param maxOutputLength
    Maximum length of the allocated strings pDirectory and pFilename. Note 
    that a single value is used for both strings.

    @return
    A CRESULT error code to indicate if the call was successful or failed.

	@since 3.10
*/
CRESULT osldir_split( const DCHAR *pFullPath, 
                      DCHAR *pDirectory, 
                      DCHAR *pFilename, 
                      CTuint32 maxOutputLength );

/**
    @}
*/ // end addtogroup 'os_dir'
//=============================================================================

#ifdef __cplusplus
} // extern "C"
#endif
#endif // !defined( OSLDIR_H )
