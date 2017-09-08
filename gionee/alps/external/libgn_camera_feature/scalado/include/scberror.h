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

#ifndef SCBERROR_H
#define SCBERROR_H

#include "scbdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @ingroup return_codes
    @file scberror.h
    @brief
    Defines macros usefull for implementing the error mechanism
    and exports some global error codes.
*/
//=============================================================================
/**
    @addtogroup return_codes
    @brief Global error and status codes.
    @{
*/
//-----------------------------------------------------------------------------

/** 
    @brief Determines whether or not a value equals a failure code.
*/
#define CFAILED( result ) ( ( result ) >= 0 )

/** 
    @brief Determines whether or not a value equals a failure code.
*/
#define CSUCCEED( result ) ( ( result ) < 0 )

//-----------------------------------------------------------------------------

#define SCB_BEGIN_RANGE( module ) module##_BASE = (module << 8)
#define SCB_GET_RANGE( result ) ( ( result >> 8 ) & 0xff )
#define SCB_GET_VALUE( result ) ( result & 0xff )


// Error generating modules and subsets of error codes.
typedef enum
{
    SCB_STATUS_CODES = -1,
    SCB_MODULE_GENERAL = 0,
    SCB_MODULE_IPL = 1,
    SCB_MODULE_CTDECODER = 2,
    SCB_MODULE_RAJPEG = 3,
    SCB_MODULE_EXIF = 4, 
    SCB_MODULE_CTCACHE = 5,
    SCB_MODULE_CTSTREAM = 6, 
    SCB_MODULE_PANORAMA = 7, 
    SCB_MODULE_JPEGTOOLS = 8, 
    SCB_MODULE_OSLFILE = 9,
    SCB_MODULE_OSLJPEG = 10,
    SCB_MODULE_SPMO = 11,
    SCB_MODULE_STORAGE = 12

} SCB_MODULE_ID;

//-----------------------------------------------------------------------------
/**
    @brief
    Error and status codes.
*/
typedef enum
{
    /** @brief  <b>General status codes:</b> */
    SCB_BEGIN_RANGE( SCB_STATUS_CODES ),
        CERR_OK, ///< Ok
        CRES_TASK_COMPLETE, ///< Render operation complete.

    /** @brief  <b>General error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_GENERAL ),
        CERR_RENDER_INCOMPLETE, ///< Render operation terminated early.
        CERR_MEMORY_OUT_OF_BOUNDS, ///< A buffer was too small for the source data.
        CERR_INVALID_PARAMETER, ///< A parameter passed to the function is invalid.
        CERR_NOT_IMPLEMENTED, ///< The called function is not implemented.
        CERR_INTERNAL_ERROR, ///< An internal error has occurred.

        CERR_MEMALLOC_FAILED, ///< Memory allocation failed.

        CERR_ITEM_NOT_FOUND, ///< Requested item could not be found.
        CERR_ILLEGAL_CALL, ///< The function call is illegal at this time or in this context.
        CERR_DATA_CORRUPT, ///< Corrupt data was encountered.

        CERR_INCOMPATIBLE_VERSION, ///< The version of the operation/item is not supported.
        CERR_DIVISION_BY_ZERO, ///< A division by zero occurred.
        CERR_OPERATION_FAILED, ///< Operation failed.

        CERR_CONSTRUCTION_FAILED, ///< Object construction failed.

        CERR_INCOMPATIBLE_IMAGE, ///< The image is of correct type but contains unsupported subsets specific to its format.
        CERR_UNSUPPORTED_IMAGE, ///< The image data is of an unsupported/unknown format.
        CERR_IMAGE_CORRUPT, ///< The image data is of an unsupported/unknown format.
        CERR_INVALID_COLORMODE, ///< Invalid color mode.
        CERR_INCOMPLETE_IMAGE, ///< Image file is incomplete.

        CERR_INVALID_INTERFACE, ///< The interface definition was invalid for this class.
        CERR_ILLEGAL_ENVIRONMENT, ///< The environment has not been setup correctly.

    /** @brief  <b>Internal error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_IPL ),
        CERR_FILTER_CONNECTION_FAILED, ///< Internal error
        CERR_ILLEGAL_FILTER, ///< Internal error
        CERR_INVALID_FILTER_GRAPH, ///< Internal error
        CERR_FILTER_INCOMPATIBLE_COLOR_FORMAT, ///< Internal error

    SCB_BEGIN_RANGE( SCB_MODULE_CTDECODER ),
        CERR_DECODER_NOT_PREPARED, ///< Internal error
        CERR_DECODER_NOT_PARSED, ///< Internal error

    SCB_BEGIN_RANGE( SCB_MODULE_RAJPEG ),
        CERR_RAJPEG_NO_SOI_MARKER, ///< Internal error
        CERR_RAJPEG_NUM_COMPONENTS, ///< Internal error
        CERR_RAJPEG_TOO_MANY_COEFFS, ///< Internal error
        CERR_RAJPEG_MISSING_RESTART, ///< Internal error
        CERR_RAJPEG_NO_EOI_MARKER, ///< Internal error
        CERR_RAJPEG_NOT_ENOUGH_DATA, ///< Internal error
        CERR_RAJPEG_JFIF_LENGTH, ///< Internal error
        CERR_RAJPEG_JFIF_SOS, ///< Internal error
        CERR_RAJPEG_42, ///< Internal error
        CERR_RAJPEG_43, ///< Internal error
        CERR_RAJPEG_JFIF_42, ///< Internal error

    /** @brief  <b>Exif related error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_EXIF ),
        CERR_EXIF_IDENTIFIER_NOT_FOUND, ///< No exif block found
        CERR_EXIF_ENDIAN_FORMAT_CORRUPT, ///< Mismatched endian format
        CERR_EXIF_THUMBNAIL_FORMAT_NOT_SUPPORTED, ///< Thumbnail format was unsupported.
        CERR_EXIF_TAG_NOT_FOUND, ///< The requested tag was not found.
        CERR_EXIF_INSANE_POINTER, ///< Corrupt exif data.
        CERR_EXIF_NO_THUMBNAIL, ///< No thumbnail found in exif.
        CERR_EXIF_CORRUPT_DATABASE, ///< Database was corrupted.
        CERR_EXIF_WRONG_THUMBNAIL_DATATYPE, ///< Thumbnail data type mismatch.
        CERR_EXIF_COULD_NOT_DELETE_TAG, ///< Failed to delete exif tag.
        CERR_EXIF_TIFF_NOT_MATCHING_LENGTHS, ///< Internal exif error.
        CERR_EXIF_THUMBNAIL_COMPRESSION_SCHEME_ERROR, ///< Exif thumbnail error.
        CERR_EXIF_INSANE_NR_OF_DIR, ///< Exif directory count too large.
        CERR_EXIF_INVALID_TAG, ///< Exif tag was invalid.
        CERR_EXIF_CORRUPT, ///< Exif block is corrupt
        CERR_JFIF_NO_SOI_MARKER, ///< Missing SOI (start of image) marker.

    /** @brief  <b>Cache related error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_CTCACHE ),
        CERR_CACHE_FULL, ///< The cache is filled with data and can accept no more.

    /** @brief  <b>I/O Stream related error codes module:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_CTSTREAM ),
        /**
            @brief
            This result code tells that the underlying stream has been delayed.
            
            Either than there is no data available currently, or it is not possible
            to write to the stream right now ). When a stream delays, it is assumed
            that it will be possible to read or write to the stream in a later moment,
            this depends on the particular implementation or resource associated to
            the stream.
        */
        CERR_STREAM_DELAYED, 
        /**
            @brief
            This error is returned when some operation needs to seek into the
            stream, but the seek function is not available (for example if the stream
            is mapped to a network device, it is not always possible to perform seek ).
        */
        CERR_STREAM_OP_REQUIRE_SEEK, 
        CERR_STREAM_END_OF_DATA, ///< There is no more data available in the stream.
        CERR_STREAM_ALREADY_LOCKED, ///< This error is returned when the user tries to lock a stream that has already been locked.
        /**
            @brief
            An operation such as readLock or readRelease has been performed
            without making a readRequest.
        */
        CERR_STREAM_MISSING_REQUEST, 
        /**
            @brief
            This error code is returned when a stream is full and it is not
            possible to write more data to it.
        */
        CERR_STREAM_FULL, 
        /**
            @brief
            This error code is returned when readRequest already have been 
            called with a different amount of requested bytes.
        */
        CERR_STREAM_REQUEST_MISMATCH, 

    /** @brief  <b>Autorama related error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_PANORAMA ),
        CERR_PANORAMA_LENS, ///< Error in lens parameters.
        CERR_PANORAMA_TRANSFORM, ///< Transform not valid.
        CERR_PANORAMA_GEOMETRY, ///< Could not match images to form a valid geometry for the panorama.

    /** @brief  <b>JpegTools related error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_JPEGTOOLS ),
        CERR_UNSUPPORTED_COLOR_MODE, ///< Color mode was unsupported.

    /** @brief  <b>OS file system related error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_OSLFILE ),
        CERR_FILE_NOT_FOUND, ///< File not found.
        CERR_FILE_ACCESS_DENIED, ///< Access denied.
        CERR_FILE_READ_FAILED, ///< Read operation failed.
        CERR_FILE_WRITE_FAILED, ///< Write operation failed.
        CERR_FILE_REMOVE_FAILED, ///< File remove operation failed.
        CERR_FILE_SEEK_FAILED, ///< File seek operation failed.
        CERR_FILE_POS_FAILED, ///< File move position failed.
        CERR_FILE_FLUSH_FAILED, ///< File could not be flushed.

    /** @brief  <b>Hardware related error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_OSLJPEG ),
        /**
            @brief
            Error code when hardware is busy or for some reason not available on the 
            current platform. This may be a permanent or temporary condition depending
            on the capabilities of the running environment.
        */
        CERR_HARDWARE_NOT_AVAILABLE, 

    /** @brief  <b>Speedview related error codes:</b> */
    SCB_BEGIN_RANGE( SCB_MODULE_SPMO ),
        CERR_SPMO_APP4_CORRUPT, ///< Data in SPMO object is corrupt.

    /** 
        @brief <b>Error codes related to CTStorage</b> 
    */
    SCB_BEGIN_RANGE( SCB_MODULE_STORAGE ),
        CERR_CTSTORAGE_NEXT,                ///< Internal error.
        CERR_CTSTORAGE_UNDEF_DATATYPE,      ///< Internal error.
        CERR_CTSTORAGE_NO_DATA,             ///< Internal error.
        CERR_CTSTORAGE_NO_SPACE,            ///< Internal error.
        CERR_CTSTORAGE_TOO_MANY_DATATYPE,   ///< Internal error.
        CERR_CTSTORAGE_MULT_INDEX_FILE      ///< Internal error.

} CRESULT;

//-----------------------------------------------------------------------------

/**
    @brief Returns the string representation of an error code.

    @param result Code to convert to a string
    
    @return A pointer to constant memory indicating the desired string
    representation.

    @remarks If the error code is not defined, or internal to Scalado,
    a "CERR_UNKNOWN_ERROR" is returned.
*/
const DCHAR *scberror_cresultToString( CRESULT result );

//-----------------------------------------------------------------------------
/** @} */
// doxygen defgroup end.
//=============================================================================


// Basic, random sanity tests
SCB_STATIC_ASSERT( CSUCCEED( CERR_OK ) );
SCB_STATIC_ASSERT( CSUCCEED( CRES_TASK_COMPLETE ) );
SCB_STATIC_ASSERT( CFAILED( CERR_INVALID_PARAMETER ) );

SCB_STATIC_ASSERT( CSUCCEED( -1 ) != CFAILED( -1 ) );
SCB_STATIC_ASSERT( CSUCCEED( 0 ) != CFAILED( 0 ) );
SCB_STATIC_ASSERT( CSUCCEED( 1 ) != CFAILED( 1 ) );

SCB_STATIC_ASSERT( SCB_GET_RANGE( CERR_FILE_NOT_FOUND ) == SCB_MODULE_OSLFILE );
SCB_STATIC_ASSERT( SCB_GET_VALUE( CERR_OK ) == 1 );
SCB_STATIC_ASSERT( SCB_GET_RANGE( SCB_MODULE_OSLJPEG_BASE ) == SCB_MODULE_OSLJPEG );


#ifdef __cplusplus
} // extern "C"
#endif

#endif // !defined( SCBERROR_H )
