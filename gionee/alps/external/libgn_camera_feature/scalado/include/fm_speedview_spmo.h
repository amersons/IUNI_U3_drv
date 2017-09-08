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

#ifndef FM_SPEEDVIEW_SPMO_H
#define FM_SPEEDVIEW_SPMO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "caps_types.h" // IMAGE_FORMAT_SPEC
#include "caps_iterator.h" // CTIterator
#include "fm_speedview_defs.h"
#include "ctstream.h"

//=============================================================================
/**
    @ingroup fm_speedview_api
    @file fm_speedview_spmo.h
    @brief Defines the spmo creation interface of the Caps Feature
    Module: @a SpeedView
*/
//=============================================================================
/**
    @addtogroup fm_speedview_api
    @brief
    For information regarding utility functions, for external storage of SPMO
    (i.e. storage outside of the jpeg header), see: @em Cache @em API

    @{
*/
//-----------------------------------------------------------------------------

/** 
    @brief 
    Initiates creation of Spmo using an image from an input stream.

    @param pStream
    An input stream where to load the original image.

    @param format
    The image format.

    @param optimalSize 
    Desired display size that the Spmo will be optimized for.
    Normally equal to the size of the screen.
    
    @param pOptions
    Options to control the spmo creation process. 
    Set to 0 to use default options. 

    @param[out] ppDstSpmo 
    Destination of created Spmo. If creation fails this argument is NULL.

    @param[out] ppIt
    Pointer to a @c CTIterator object if the render operation should be 
    performed as an iterative sequence, otherwise @c NULL. See remarks section 
    for more information.

    @remarks

    The currently supported image formats are:
    
    @li JPEG 
    Note: Adobe RGB format is currently not supported.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @par Example: Create Spmo with non-edited image
    @code

    CRESULT res;
    CTSpmo* spmo = 0;	
    //Spmo optimized for landscape QVGA
    CTSize optimalSize = {320, 240};	
    //Creates spmo from a JPEG image from file
    res = caps_createSpmo( pSrcStream, 
                           IMAGE_FORMAT_JPEG,
                           optimalSize,
                           0,
                           &spmo,
                           0 );
    
    
    @endcode

    @par Example: Create Spmo with edited image
    @code

    CRESULT res;
    CTSession session;
    CTStream* pFileStream;
    CTBuffer* pBuffer;
    CTStream* pBufferStream;
    CTSize srcDims;
    //Spmo optimized for landscape QVGA
    CTSize optimalSize = {320, 240};
    CTSpmo* pSpmo;

    //Create a stream from a jpeg file
    res = ctstream_createFileStreamEx( filename, 
                                       FOF_ACCESS_READ|FOF_MODE_BINARY, 
                                       32768, 
                                       &pFileStream );

    //Create a session
    res = caps_createSession( pFileStream, IMAGE_FORMAT_JPEG, &session );
    res = caps_getSourceImageSize( session, &srcDims );

    //Example: Convert image to grayscale
    res = caps_applyGrayscale( session );

    //Create buffer stream which we render the edited image to.
    res = caps_createBuffer( 0, &pBuffer );
    res = ctstream_createBufferStream( pBuffer, 0, &pBufferStream );
    res = caps_render( session, 
                       pBufferStream, 
                       srcDims, 
                       CAPS_OUTPUT_PRESERVE_AR, 
                       IMAGE_FORMAT_JPEG, 
                       0 );

    caps_destroySession( session );
    ctstream_destroy( pFileStream );
    ctstream_destroy( pBufferStream );

    //Create Spmo from the buffer stream.
    res = ctstream_createBufferStream( pBuffer, 0, &pBufferStream );
    res = caps_createSpmo( pBufferStream, 
                           IMAGE_FORMAT_JPEG, 
                           optimalSize, 
                           0, 
                           &pSpmo, 
                           0 );
    ctstream_seek(pBufferStream, 0);

    //Create a stream from filename which we add the Spmo to.
    res = ctstream_createFileStreamEx( filename, 
                                       FOF_ACCESS_WRITE|FOF_MODE_BINARY, 
                                       32768, 
                                       &pFileStream );
    res = caps_addSpmo( pSpmo, pBufferStream, pFileStream );

    caps_destroySpmo(pSpmo);
    ctstream_destroy(pFileStream);
    ctstream_destroy(pBufferStream);
    caps_destroyBuffer(pBuffer);

    @endcode

    @sa caps_spmoCreateOptions()

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_createSpmo( CTStream *pStream, 
                         IMAGE_FORMAT_SPEC format,
                         CTSize optimalSize,
                         CTSpmoOptions* pOptions,
                         CTSpmo** ppDstSpmo,
                         CTIterator** ppIt );
//-----------------------------------------------------------------------------
/**
    @brief 
    Initiates creation of Spmo using an image from the filesystem as input.

    @param filename
    The filesystem path to the file.

    @param format
    The image format of the file.

    @param optimalSize 
    Desired display size that the Spmo will be optimized for.
    Normally equal to the size of the screen.
    
    @param options
    Options to control the spmo creation process. 
    Set to 0 to use default options. 

    @param[out] dstSpmo 
    Destination of created Spmo. If creation fails this argument is NULL.

    @param[out] it
    Pointer to a @c CTIterator object if the render operation should be 
    performed as an iterative sequence, otherwise @c NULL. See remarks section 
    for more information.

    @remarks
    The currently supported image formats are:
    
    @li JPEG 
    Note: Adobe RGB format is currently not supported.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    CRESULT res;
    CTSpmo* spmo = 0;	
    //Spmo optimized for landscape QVGA
    CTSize optimalSize = {320, 240};	
    //Creates spmo from a JPEG image from file
    res = caps_createSpmoFromFile( _D("image.jpg"), 
                                   IMAGE_FORMAT_JPEG,
                                   optimalSize,
                                   0,
                                   &spmo,
                                   0 );
    
    
    @endcode 

    @sa
    caps_createSpmoFromFileHandle()\n
    caps_createSpmoFromBuffer()

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_createSpmoFromFile( const DCHAR* filename, 
                                 IMAGE_FORMAT_SPEC format,
                                 CTSize optimalSize,
                                 CTSpmoOptions* options, 
                                 CTSpmo** dstSpmo,
                                 CTIterator** it );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Initiates creation of Spmo using an image from an open file handle.


    @param handle
    An open CTFile object with read access.

    @param format
    The image format of the file.

    @param optimalSize 
    Desired display size that the Spmo will be optimized for. 
    Normally equal to the size of the screen. The size is "bounded box"-style.
    This will guarantee preservation of aspect ratio.

    @param options
    Options to control the spmo creation process. 
    Set to 0 to use default options. 

    @param[out] dstSpmo 
    sDestination of created Spmo. If creation fails this argument is NULL.

    @param[out] it
    Pointer to a @c CTIterator object if the render operation should be 
    performed as an iterative sequence, otherwise @c NULL. See remarks section 
    for more information.

    @remarks

    The currently supported image formats are:
    
    @li JPEG 
    Note: Adobe RGB format is currently not supported.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @code

    CTFile* file = 0;
    CTSpmo* spmo = 0;	
    //Spmo optimized for landscape QVGA
    CTSize optimalSize = {320, 240};

    //Open source file, get a file handle
    res = oslfile_open(_D("jpeg.jpg"), 
        FOF_ACCESS_READ | FOF_MODE_BINARY, &file);

    res = caps_createSpmoFromFile( file, 
                                   IMAGE_FORMAT_JPEG,
                                   optimalSize,
                                   0,
                                   &spmo,
                                   0 );

    @endcode

    @sa
    caps_createSpmoFromFile()\n
    caps_createSpmoFromBuffer()

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_createSpmoFromFileHandle( const CTFile* handle, 
                                       IMAGE_FORMAT_SPEC format,
                                       CTSize optimalSize,
                                       CTSpmoOptions* options, 
                                       CTSpmo** dstSpmo,
                                       CTIterator** it );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Initiates creation of Spmo using a buffer with image data.

    @param buffer
    A @c CTBuffer pointer specifying a buffer containing image data.

    @param format
    The image format of the file.

    @param optimalSize 
    Desired display size that the Spmo will be optimized for. 
    Normally equal to the size of the screen. The size is "bounded box"-style.
    This will guarantee preservation of aspect ratio.

    @param options
    Options to control the spmo creation process. 
    Set to 0 to use default options. 

    @param[out] dstSpmo 
    Destination of created Spmo. If creation fails this argument is NULL.

    @param[out] it
    Pointer to a @c CTIterator object if the render operation should be 
    performed as an iterative sequence, otherwise @c NULL. See remarks section 
    for more information.

    @remarks

    The currently supported image formats are:
    
    @li JPEG 
    Note: Adobe RGB format is currently not supported.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.
    @code

    CTBuffer* buffer;
    CRESULT res;
    CTFile* file;
    CTuint32 fileSize;
    CTSpmo* spmo = 0;	
    //Spmo optimized for landscape QVGA
    CTSize optimalSize = {320, 240};
    
    res = oslfile_open(_D("jpeg.jpg"), 
                        FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    fileSize = oslfile_size(file);
    caps_createBuffer(fileSize, &buffer);
    res = oslfile_read(file, buffer->data, buffer->size);
    oslfile_close(file);
    res = caps_createSpmoFromBuffer( buffer, 
                                     IMAGE_FORMAT_JPEG,
                                     optimalSize,
                                     0,
                                     &spmo,
                                     0 );
    //...
    //...
    caps_destroyBuffer(buffer);

    @endcode

    @sa
    caps_createSpmoFromFile()\n
    caps_createSpmoFromFileHandle()

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_createSpmoFromBuffer( const CTBuffer* buffer, 
                                   IMAGE_FORMAT_SPEC format,
                                   CTSize optimalSize,
                                   CTSpmoOptions* options, 
                                   CTSpmo** dstSpmo,
                                   CTIterator** it );
//-----------------------------------------------------------------------------


// STORE API
//-----------------------------------------------------------------------------
/**
    @brief
    Adds a Spmo to a jpeg stream.

    @param spmo 
    Spmo to add to stream.
    Original jpeg image, will remain unchanged.

    @param srcStream 
    A pointer to a stream containing the original jpeg image, 
    will remain unchanged.

    @param dstStream 
    A pointer to destination stream which the Spmo will be added to
    ( it will include the jpeg image in the source stream plus the spmo object ).

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertSpmoIntoJpegFile()\n
    caps_insertSpmoIntoJpegBuffer()\n
    caps_addSpmoToJpegFile()\n
    caps_addSpmoToJpegBuffer()\n
    caps_addSpmoToJpegBufferToFileHandle()\n
    caps_removeSpmo()\n

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_addSpmo( CTSpmo* spmo, 
                                CTStream* srcStream, 
                                CTStream* dstStream );
//-----------------------------------------------------------------------------
/**
    @brief
    Adds a Spmo to a jpeg file.

    @param srcJpegFilename 
    Original jpeg file, will remain unchanged.

    @param dstJpegFilename 
    Destination jpeg file, to which the Spmo will be added.
    Will be created by the function. 
    If a file with the same name already exists, it will be overwritten.

    @param spmo 
    Spmo to add to file.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertSpmoIntoJpegFile()\n
    caps_insertSpmoIntoJpegBuffer()\n
    caps_addSpmoToJpegBuffer()\n
    caps_addSpmoToJpegBufferToFileHandle\n

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_addSpmoToJpegFile(
                            const DCHAR* srcJpegFilename, 
                            const DCHAR* dstJpegFilename,
                            const CTSpmo* spmo
                            );
//-----------------------------------------------------------------------------
/**
    @brief
    Adds a Spmo to a jpeg in a memory buffer.

    @param srcJpegBuffer 
    Original jpeg buffer, will remain unchanged.

    @param dstJpegBuffer 
    Destination jpeg buffer, to which the Spmo will be added.

    @param spmo 
    Spmo to add to file

    @param numBytesWritten 
    Size in bytes of new jpeg

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertSpmoIntoJpegFile()\n
    caps_insertSpmoIntoJpegBuffer()\n
    caps_addSpmoToJpegFile()\n
    caps_addSpmoToJpegBufferToFileHandle\n

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_addSpmoToJpegBuffer(
                            const CTBuffer* srcJpegBuffer, 
                            CTBuffer* dstJpegBuffer,
                            const CTSpmo* spmo,
                            CTuint32* numBytesWritten
                            );
//-----------------------------------------------------------------------------
/**
    @brief
    Adds a Spmo to a jpeg in a memory buffer. The result will be written 
    to a file handle.

    @param srcJpegBuffer 
    Original jpeg buffer, will remain unchanged.    

    @param spmo 
    Spmo to add to file

    @param dstFileHandle 
    File handle to write the resulting jpeg (including Spmo) to.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertSpmoIntoJpegFile()\n
    caps_insertSpmoIntoJpegBuffer()\n
    caps_addSpmoToJpegFile()\n
    caps_addSpmoToJpegBuffer()\n

    @since 3.6

    @deprecated This function is deprecated since 5.3.
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT caps_addSpmoToJpegBufferToFileHandle(
                            const CTBuffer* srcJpegBuffer,                             
                            const CTSpmo* spmo,
                            CTFile* dstFileHandle);
//-----------------------------------------------------------------------------
/**
    @brief
    Inserts a Spmo into a jpeg file. Any previous stored spmo's in the file 
    will be overwritten.

    @param jpegFilename 
    Source and destination jpeg file. The Spmo will be inserted into the 
    original jpeg file. 
    
    @param spmo 
    Spmo to insert into file

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertSpmoIntoJpegBuffer()\n
    caps_addSpmoToJpegFile()\n
    caps_addSpmoToJpegBuffer()\n
    caps_addSpmoToJpegBufferToFileHandle\n

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT 
caps_insertSpmoIntoJpegFile( const DCHAR* jpegFilename,
                             const CTSpmo* spmo );

//-----------------------------------------------------------------------------
/**
    @brief
    Inserts a Spmo into a jpeg memory buffer. Any previous stored spmo's in the 
    file will be overwritten.

    @param jpegBuffer 
    Source and destination jpeg buffer. The Spmo will be inserted into the 
    original jpeg buffer. The buffer must be large enough to accommodate both 
    the original jpeg plus the Spmo.
    
    @param spmo 
    Spmo to insert into buffer

    @param srcJpegSize 
    Original size of jpeg. Set to 0 (zero) if unknown.

    @param numBytesWritten 
    Size in bytes of new jpeg

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertSpmoIntoJpegFile()\n
    caps_addSpmoToJpegFile()\n
    caps_addSpmoToJpegBuffer()\n
    caps_addSpmoToJpegBufferToFileHandle\n

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_insertSpmoIntoJpegBuffer(
                            CTBuffer* jpegBuffer,
                            const CTSpmo* spmo,
                            CTuint32 srcJpegSize,
                            CTuint32* numBytesWritten
                            );

// REMOVE API
//-----------------------------------------------------------------------------
/**
    @brief
    Remove a Spmo from a jpeg stream.

    @param srcStream 
    A pointer to a stream containing a jpeg image with Spmo, 
    will remain unchanged.

    @param dstStream 
    A pointer to destination stream which will contain the 
    jpeg image without the Spmo.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertSpmoIntoJpegFile()\n
    caps_insertSpmoIntoJpegBuffer()\n
    caps_addSpmoToJpegFile()\n
    caps_addSpmoToJpegBuffer()\n
    caps_addSpmoToJpegBufferToFileHandle\n

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_removeSpmo(CTStream* srcStream, CTStream* dstStream);

// GET API
//-----------------------------------------------------------------------------
/**
    @brief
    Function for retrieving a Spmo from a stream. The stream could either 
    contain a jpeg stream where the Spmo resides inside the jpeg or a data 
    stream where only the Spmo is stored.

    @param[in] pSrcStream 
    A pointer to a stream where the Spmo is stored.

    @param[out] ppSpmo 
    Pointer to an address where the retrieved Spmo will be copied to.

    @remarks
    The data stream can only contain one Spmo.

    @return 
    @li @c CERR_OK if successful or a specific error code upon failure.
    @li @c CERR_SPMO_APP4_CORRUPT if the APP4 block containing the Spmo is 
    corrupt, however the jpeg image can still be used. The corrupt block can 
    be removed with caps_removeSpmo().

    @sa
    caps_destroySpmo();

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_getSpmo( CTStream* pSrcStream, 
                      CTSpmo** ppSpmo );
//-----------------------------------------------------------------------------
/**
    @brief
    Function for retrieving a Spmo from a memory buffer. The memory buffer 
    could either be jpeg buffer where the Spmo resides inside the jpeg or
    a data buffer where only the Spmo is stored.
    
    @param buffer 
    Pointer to a buffer where the Spmo is stored.

    @param spmo 
    Pointer to an address where the retrieved Spmo will be copied to.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_destroySpmo();

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_getSpmoFromMem(
                            const CTBuffer* buffer, 
                            CTSpmo** spmo
                            );
//-----------------------------------------------------------------------------
/**
    @brief
    Function for retrieving a Spmo from file. The file could either be jpeg
    file where the Spmo resides inside the jpeg or a file where only the Spmo 
    is stored.

    @param filename 
    Path to the file where the Spmo is stored.

    @param spmo 
    Pointer to an address where the retrieved Spmo will be copied to.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_destroySpmo();

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_getSpmoFromFile(
                            const DCHAR* filename,  
                            CTSpmo** spmo
                            );
//-----------------------------------------------------------------------------
/**
    @brief
    Function for retrieving a Spmo from file handle. The file could either be jpeg
    file handle where the Spmo resides inside the jpeg or a file handle where only the Spmo 
    is stored.

    @param handle 
    Address of an open CTFile object with read access.

    @param spmo 
    Pointer to an address where the retrieved Spmo will be copied to.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_destroySpmo();

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_getSpmoFromFileHandle(
                                  const CTFile* handle,
                                  CTSpmo** spmo
                                  );
//-----------------------------------------------------------------------------
/**
    @brief
    Returns the version of the Spmo.

    @param[in] pSpmo 
    Pointer to Spmo.

    @param[out] pVersion 
    Pointer to the version of the Spmo.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7 R7

    @deprecated This function is deprecated since 5.3.
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT caps_spmoGetVersion( CTSpmo* pSpmo, CTuint32* pVersion );

//-----------------------------------------------------------------------------
/**
    @brief
    Returns the storage size in bytes of the Spmo.

    @param spmo 
    Pointer to Spmo.

    @param size 
    Pointer to the storage size of the Spmo.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoGetStorageSize( const CTSpmo* spmo, CTuint32* size );
//-----------------------------------------------------------------------------
/**
    @brief
    Returns the storage size in bytes of the Spmo if the Spmo is going to be 
    stored in a jpeg file.

    @param spmo 
    Pointer to Spmo.

    @param size 
    Pointer to the storage size of the Spmo.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoGetStorageSizeForJpeg( const CTSpmo* spmo, CTuint32* size );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Retrieves the address to the Spmo data. Use this function if the Spmo is
    going to be stored in a separate file/buffer instead of inside a jpeg.

    @param spmo
    The Spmo from which to retrieve the data pointer.

    @param[out] dataBuffer
    Address of a pointer which will receive the data buffer address. 
    Ownership of the pointer is NOT transferred to the caller and should not be 
    regarded as permanent. When the Spmo is destroyed the pointer 
    will be invalid.
        
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoGetDataBuffer( CTSpmo* spmo, CTBuffer** dataBuffer );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Creates (a) valid App block(s) that encapsulates the Spmo data when storing
    the Spmo in a jpeg file.

    @param spmo
    The Spmo that will be encapsulated in (a) App block(s).

    @param[out] dataBuffer
    Address of a pointer which will receive the data buffer address. 
    Ownership of the pointer is transferred to the caller and should be 
    freed by caller.

    @param targetSize
    If set, this will be the exact size of the dataBuffer. Set to zero to 
    keep the dataBuffer as small as possible. If set to non zero, the value must
    be larger than 44 that is the minimum size of the app block.
        
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoCreateAppBlockForJpeg( CTSpmo* spmo, 
                                        CTBuffer** dataBuffer,
                                        CTuint32 targetSize);
//-----------------------------------------------------------------------------

//=============================================================================
/**
    @name Functions supporting delayed insertion of SPMO
    
    These functions provide support for reserving space, in a Jpeg file
    (-header), and for insertion of a SPMO into this "pre-allocated" space
    at a later point in time.
 */
// @{

/**
    @brief 
    Creates (a) valid App block(s) to encapsulates the Spmo data when storing
    the Spmo in a jpeg file. Use this function to create an app-block with 
    pre-allocated space for spmo.

    @param dataBuffer
    Pointer to the user allocated data buffer to be filled by the function. 
    Ownership of the pointer remains with the caller.

    @param targetSize
    This will be the exact size of the the application block(s) including 
    marker(s). The value must be larger than 44 that is the minimum size of the app block.
      
        
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoCreateEmptyAppBlockForJpeg( CTBuffer* dataBuffer,
                                             CTuint32 targetSize);
//-----------------------------------------------------------------------------
/**
    @brief
    Checks if the file contains any pre allocated space for spmo.    

    @param filename A Jpeg file.
    
    @param pPosition Position where the pre-allocated area starts, will be 0 
                     if no pre-allocated area is found..

    @param pSize Size of the pre-allocated area, will be 0 if no pre-allocated 
                 area is found.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoHasAllocedAppBlockInFile( const DCHAR* filename, 
                                           CTuint32* pPosition,
                                           CTuint32* pSize);
//-----------------------------------------------------------------------------
/**
    @brief
    Checks if the buffer contains any pre allocated space for spmo.

    @param buffer A Jpeg file.
    
    @param pPosition Position where the pre-allocated area starts, will be 0 
                     if no pre-allocated area is found..

    @param pSize Size of the pre-allocated area, will be 0 if no pre-allocated 
                 area is found.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoHasAllocedAppBlockInBuffer( const CTBuffer* buffer, 
                                               CTuint32* pPosition,
                                               CTuint32* pSize);
//-----------------------------------------------------------------------------
/**
    @brief
    Inserts, if the available space is enough, the speedview object into a
    pre-allocated area in the file.

    @param filename Jpeg file with pre-allocated space for spmo

    @param pSpmo The speedview object to be inserted in the jpeg file.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_insertSpmoIntoAppBlockInJpegFile( const DCHAR* filename, 
                                               CTSpmo* pSpmo );
//-----------------------------------------------------------------------------
/**
    @brief
    Inserts, if the available space is enough, the speedview object into a
    pre-allocated area in the file

    @param pJpegBuffer Jpeg file with pre-allocated space for spmo

    @param pSpmo The speedview object to be inserted in the jpeg file.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_insertSpmoIntoAppBlockInJpegBuffer( CTBuffer* pJpegBuffer, 
                                                 CTSpmo* pSpmo );
//-----------------------------------------------------------------------------
// @}
// end section: 'spmo delayed insertion'
//=============================================================================
/**
    @brief
    Destroys a Speedview object.    

    @param spmo 
    Pointer to Speedview object.   

    NOTE: If the Spmo is active in a session i.e, caps_spmoNewSessionWithFile,
    make sure to destroy the session before calling this function.

    @since 3.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT void caps_destroySpmo( CTSpmo* spmo );
//-----------------------------------------------------------------------------
/**
    @brief
    Estimates the size (in bytes) of the Spmo using default options.    

    @param pOriginalSize 
    
    @param pOptimalSize 

    @sa
    caps_estimateSpmoSizeWithOptions()\n

    @since 3.4

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CTuint32 caps_estimateSpmoSize(CTSize* pOriginalSize, CTSize* pOptimalSize);
//-----------------------------------------------------------------------------
/**
    @brief
    Estimates the size (in bytes) of the Spmo using the supplied options.    

    @param pOriginalSize 
    
    @param pOptimalSize

    @param pOptions 

    @sa
    caps_estimateSpmoSize()\n

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CTuint32 caps_estimateSpmoSizeWithOptions( CTSize* pOriginalSize, 
                                           CTSize* pOptimalSize,
                                           CTSpmoOptions* pOptions );
//-----------------------------------------------------------------------------
/**
    @brief
    Checks if the stream contains a spmo.

    @note This function will restores the stream position to where it started reading,
    so the stream may safely be used in subsequent calls.

    @param stream 
    A pointer to a stream containing a jpeg image.

    @param pHasSpmo True if the stream contains spmo, otherwise false.
    Note that the function just identify the Spmo tag. Therefore, if the
    Spmo is errouneous, pHasSpmo may be true.	

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_hasSpmo( CTStream* stream, CTbool* pHasSpmo);
//-----------------------------------------------------------------------------
/**
    @brief
    Checks if the file contains any spmo.    

    @param filename 
    
    @param pHasSpmo True if the file contains spmo, otherwise false.
    Note that the function just identify the Spmo tag. Therefore, if the
    Spmo is errouneous, pHasSpmo may be true.	

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.5

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_hasSpmoFromFile( const DCHAR* filename, CTbool* pHasSpmo );
//-----------------------------------------------------------------------------
/**
    @brief
    Checks if the buffer contains any spmo.    

    @param buffer 
    
    @param pHasSpmo True if the buffer contains spmo, otherwise false.
    Note that the function just identify the Spmo tag. Therefore, if the
    Spmo is errouneous, pHasSpmo may be true.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.5

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_hasSpmoFromBuffer( const CTBuffer* buffer, CTbool* pHasSpmo );
//-----------------------------------------------------------------------------

//=============================================================================
/**
    @name Functions for setting SPMO-options
    @brief The options set using these functions determine the content
    of the SPMO when created.
*/
// @{

/**
    @brief
    Creates a spmo option with default values set. Spmo option is used to 
    control the creation process of the spmo. 

    @param ppOptions Pointer to the handle of the created options.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_spmoDestroyOptions()\n

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoCreateOptions( CTSpmoOptions** ppOptions );
//-----------------------------------------------------------------------------
/**
    @brief
    Destroys spmo option

    @param pOptions Handle to spmo options.
    
    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT void caps_spmoDestroyOptions( CTSpmoOptions* pOptions );
//-----------------------------------------------------------------------------
/**
    @brief
    Sets the quality option.    

    @param pOptions Handle to spmo options.
    
    @param quality A value between 0-10, there 0 represents lower quality, and
                   10 is the maximum quality (default= 5).
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoOptionsSetQuality( CTSpmoOptions* pOptions, CTuint32 quality );
//-----------------------------------------------------------------------------
/**
    @brief
    Sets the SPMO mode options.

    @param pOptions Handle to spmo options.

    @param mode An enum with the possible values ::SPMO_NO_INDEX (0) and 
    ::SPMO_INDEXED (10), where @c SPMO_NO_INDEX represents a pure viewing case,
    and SPMO_INDEXED gives the maximum performance boost for zoom/pan and
    editing use cases.

    Setting @c mode to @c SPMO_INDEXED will result in a larger SPMO.
    @n
    @c SPMO_INDEXED is recommended for use cases that needs to maximize
    performance of zoom/pan and editing.
    @n
    @c SPMO_NO_INDEX is the recommended mode to use for viewing (only).

    @note For JPEG images with optimized huffman tables, @c mode will be 
    defaulting to @c SPMO_NO_INDEX, regardless of the input to this function.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoOptionsSetMode( CTSpmoOptions* pOptions, CTSpmoMode mode );
//-----------------------------------------------------------------------------
/**
    @brief
    Gets the quality option.

    @param pOptions Handle to spmo options.
    
    @param pQuality Pointer to the value that will receive the current quality
                    setting used.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoOptionsGetQuality( CTSpmoOptions* pOptions, CTuint32* pQuality );
//-----------------------------------------------------------------------------
/**
    @brief
    Gets the mode option.

    @param pOptions Handle to spmo options.
    
    @param pMode Pointer to the value that will receive the current mode
                 of spmo options.
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_spmoOptionsGetMode( CTSpmoOptions* pOptions, CTuint32* pMode );

// @}
// end section 'SPMO create options'
//=============================================================================
/**
    @}
*/ // 'fm_speedview_api'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_SPEEDVIEW_SPMO_H )
