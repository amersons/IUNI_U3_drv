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

#ifndef FM_EXIF_H
#define FM_EXIF_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/**
    @file fm_exif.h
    @brief Defines the interface of the Caps Feature Module: @a Exif
    @ingroup fm_exif
*/
//=============================================================================
/**
    @addtogroup fm_exif
    @brief Utility functions for setting/getting Exif tags/content
    @{
        @defgroup fm_exif_general General functions
        @defgroup fm_exif_thumbnail Thumbnail functions
        @defgroup fm_exif_gettag getTag functions
        @defgroup fm_exif_settag setTag functions
        @defgroup fm_exif_gpstags GPSTags functions
        @defgroup fm_exif_examples Examples
        @brief Example code for some typical use cases.
*/
// end of (sub)group definitions in 'fm_exif'.

/**
    @brief
    The session used to store the exif information.

    This is necessary for all editing of exif data, such as tags and 
    thumbnails.

    @since 3.2
*/
typedef struct ctExifSession* CTExifSession;

/** @} */
// end addtogroup 'fm_exif'.

//-----------------------------------------------------------------------------

/**
    @addtogroup fm_exif_general
    @{
*/

/**
    @brief
    This structure holds the information for the exif tags.

    Note that this structure may be used as both input and output argument.
    For more information about exif tags, see the specification:
    "Digital Still Camera Image File Format Standard" v2.1, JEIDA.

    @since 3.2
*/
struct CTTagInfo
{        
    CTuint8  IFD;           ///< The IFD identifier, 0 - Main image, 1 - Thumbnail
    EXIF_SUB_IFD subIFD;    ///< The sub IFD identifier
    CTuint16 tagId;         ///< The tag identifier
    CTuint16 nofRecords;    ///< The number of records of type 'tagType'    
    CTuint8  tagType;       ///< The type of record
    CTuint8* tagData;       ///< The data value of the tag
};
typedef struct CTTagInfo CTTagInfo;

//-----------------------------------------------------------------------------
/**
    @brief
    Checks if an image contains exif data.

    @param pBuffer
    Buffer containing the data.

    @param isExif
    True, if exif data exists, False otherwise.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_isExifFile()\n  
	exif_isExifFileHandle()\n

    @since 3.2
*/
SCBIMPORT CRESULT exif_isExifBuffer(const CTBuffer* pBuffer, CTbool* isExif);

//-----------------------------------------------------------------------------
/**
    @brief
    Checks if an image contains exif data.

    @param filename
    Filename of the image.

    @param isExif
    True, if exif data exists, False otherwise.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_isExifBuffer()\n 
	exif_isExifFileHandle()\n

    @since 3.2
*/
SCBIMPORT CRESULT exif_isExifFile(const DCHAR* filename, CTbool* isExif);

//-----------------------------------------------------------------------------
/**
    @brief
    Checks if an image contains exif data.

    @param handle
    Filehandle to the image.

    @param isExif
    True, if exif data exists, False otherwise.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_isExifBuffer()\n 
	exif_isExifFile()\n

    @since 3.4
*/
SCBIMPORT CRESULT exif_isExifFileHandle(const CTFile* handle, CTbool* isExif);

//-----------------------------------------------------------------------------
/**
    @brief
    Starts a new exif editing session from buffer.
    Endian format is set to the same as the existing data.

    @param pBuffer
    Buffer containing the exif header.

    @param exifSession
    The session to hold the exif data.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @copydoc exif_newsessionwithbuffer_example

    @sa
    exif_newSessionWithFile()\n
	exif_newSessionWithFileHandle()\n
    exif_newSessionWithBlank()\n

    @since 3.2
*/
SCBIMPORT CRESULT exif_newSessionWithBuffer(const CTBuffer* pBuffer, 
								  CTExifSession* exifSession);

//-----------------------------------------------------------------------------
/**
    @brief
    Starts a new exif editing session from file.
    Endian format is set to the same as the existing data.

    @param filename
    Filename of jpeg image

    @param exifSession
    The session to hold the exif data. This argument is set to NULL
	if the function fails.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @code
	//Example: Read existing exif header from file,
	//Modify, delete or add tags or thumbnails,
	//add the exif header to an existing CAPS CTSession
	CRESULT res = CERR_OK;	
	CTExifSession exifSession;	
	
	res = exif_newSessionWithFile(_D("exif.jpg"), &exifSession); 	
	//...
	//Modify, delete or add tags or thumbnails
	//		
	res = exif_addExifHeaderFromSession(session, exifSession);
	exif_destroySession(exifSession);
	//...
    @endcode

    @sa
    exif_newSessionWithBuffer()\n
	exif_newSessionWithFileHandle()\n
    exif_newSessionWithBlank()\n

    @since 3.2
*/
SCBIMPORT CRESULT exif_newSessionWithFile( const DCHAR* filename, 
                                 CTExifSession* exifSession );

//-----------------------------------------------------------------------------
/**
    @brief
    Starts a new exif editing session from a file handle.
    Endian format is set to the same as the existing data.

    @param srcHandle
    File handle to a jpeg image

    @param exifSession
    The session to hold the exif data. This argument is set to NULL
	if the function fails.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_newSessionWithFile()\n
	exif_newSessionWithBuffer()\n
    exif_newSessionWithBlank()\n

    @since 3.4
*/
SCBIMPORT CRESULT exif_newSessionWithFileHandle( const CTFile* srcHandle, 
									   CTExifSession* exifSession );

//-----------------------------------------------------------------------------
/**
    @brief
    Starts a new empty exif session    
    Default endian is SCB_LITTLE_ENDIAN.

    @param exifSession
    The session to hold the exif data. This argument is set to NULL
	if the function fails.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @copydoc exif_newemptysession_example

    @sa
    exif_newSessionWithBuffer()\n
    exif_newSessionWithFile()\n
	exif_newSessionWithFileHandle()\n

    @since 3.2
*/
SCBIMPORT CRESULT exif_newSessionWithBlank( CTExifSession* exifSession );

//-----------------------------------------------------------------------------
/**
    @brief
    Adds an exif header to be rendered in a CAPS session.    

    @param session
    A valid CAPS CTSession

    @param exifSession
    The session that holds the exif data.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_addExifHeaderFromBuffer()

    @since 3.2
*/
SCBIMPORT CRESULT exif_addExifHeaderFromSession( CTSession session, 
                                       CTExifSession exifSession );

//-----------------------------------------------------------------------------
/**
    @brief
    Adds an exif header to be rendered in a CAPS session.    

    @param session
    A valid CAPS CTSession

    @param exifData
    A buffer containing the exif header. Pass this
    argument as NULL in order to remove current exif data from the session

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_addExifHeaderFromSession()

    @since 3.2
*/
SCBIMPORT CRESULT exif_addExifHeaderFromBuffer( CTSession session, 
                                      const CTBuffer* exifData );

//-----------------------------------------------------------------------------
/**
    @brief
    Destroys an exif session    

    @param exifSession
    The session that holds the exif data

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_destroySession(CTExifSession exifSession);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets the size in bytes of the exif block    

    @param exifSession
    The session to hold the exif data

    @param size
    The current size of the exif block.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getExifBlockSize(CTExifSession exifSession, CTuint32* size);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets the endian to use when rendering the session.

    @param exifSession
    The session to hold the exif data

    @param endian
    SCB_LITTLE_ENDIAN or SCB_BIG_ENDIAN

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_renderSession()

    @since 3.2
*/
SCBIMPORT CRESULT exif_setEndian(CTExifSession exifSession, CTuint32 endian);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets the endian to use when rendering the session   

    @param exifSession
    The session to hold the exif data

    @param endian
    SCB_LITTLE_ENDIAN or SCB_BIG_ENDIAN

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_renderSession()

    @since 3.2
*/
SCBIMPORT CRESULT exif_getEndian(CTExifSession exifSession, CTuint32* endian);

//-----------------------------------------------------------------------------
/**
    @brief
    Renders the exif data in the session to a buffer.

    The exif header will be written in the endian format specified by
    exif_setEndian(). Default for all sessions are little endian.

    @param exifSession
    The session to hold the exif data

    @param pBuffer
    The buffer to write the exif data to. This buffer must be provided by the
    caller. The struct member CTBuffer::size of the provided buffer will be
    updated to reflect the actual number of bytes written to the buffer.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa exif_getExifBlockSize() for querying the required buffer size.
    
    @since 3.2
*/
SCBIMPORT CRESULT exif_renderSession( CTExifSession exifSession, 
                            CTBuffer* pBuffer );

//-----------------------------------------------------------------------------
/**
    @brief
    Copies all the data associated with an exif session.    

    @param copiedSession
    The new session to be created.

    @param exifSession
    The session that holds the exif data to be copied.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_copySession( CTExifSession* copiedSession, 
                          CTExifSession exifSession );

/**
    @}
*/ // 'fm_exif_general' - NOTE! Continued below.

//-----------------------------------------------------------------------------

/** @addtogroup fm_exif_thumbnail
    @{
*/

/**
    @brief
    This structure holds the information for raw rgb thumbnails.
    Note that this structure may be used as both input and output argument.

    @since 3.2
*/
struct CTRawThumbnailInfo
{        
    CTSize size;                        ///< width and height in pixels
    CTuint32 bitsPerSample;             ///< Currently only 24 bits is supported
    CTuint32 photometricInterpretation; ///< Can be 2 (RGB) or 6 (YCbCr)
    CTuint32 samplesPerPixel;           ///< Currently only 3 is supported
};
typedef struct CTRawThumbnailInfo CTRawThumbnailInfo;

/**
    @brief
    This structure holds the information for jpeg thumbnails.

    @since 3.8.2 R02
*/
typedef struct CTJpegThumbnailInfo
{
    /**
        @brief
        Size of jpeg thumbnail in bytes. 0 if no thumbnail is found.
    */
    CTuint32 size;

    /**
        @brief
        Offset to jpeg data from the FF in the FF E1 marker.
    */
    CTuint32 offset;

    /**
        @brief
        The orientation tag of the thumbnail. 0 if no orientation flag is found.

        @note 0 is not a valid exif orientation. For valid orientation values,
        see, for example: exif_getThumbnailFromBuffer()
    */
    CTuint32 IFD1Orientation;
} CTJpegThumbnailInfo;

//-----------------------------------------------------------------------------

/**
    @brief
    Gets a copy of the thumbnail from the Exif block if present.

    @remarks
    If the user only wants a read-only reference to the thumbnail, then it is
    more memory efficient to use exif_getExifData() to extract the information
    needed, such as:

    Offsets and length of thumbnail,

    and if RAW:

    Width and height in pixels,
    Bits per sample,
    Photometric interpretation and
    Samples per pixel.

    @param exifSession
    The session that holds the exif data.

    @param buffer
    A buffer that will recieve a copy of the thumbnail. The user must 
    de-allocate this buffer, I.e call caps_destroyBuffer().

    @param rawInfo
    [optional] A structure describing the thumbnail if it is of raw rgb format.
    The member of this structure will be 0 if the thumbnail is jpeg.

	@return 
    @c CERR_OK if successful, CERR_ITEM_NOT_FOUND if no thumbnail was found
    or a specific error code upon failure.

    @sa
    exif_getThumbnailFromBuffer()\n
    exif_getThumbnailFromFile()\n
    exif_addThumbnailToSession()

    @since 3.2
*/
SCBIMPORT CRESULT exif_getThumbnailFromSession( CTExifSession exifSession, 
                                      CTBuffer** buffer, 
                                      CTRawThumbnailInfo* rawInfo );

//-----------------------------------------------------------------------------
/**
    @brief
    Adds a thumbnail to the Exif session        

    @param exifSession
    The session that holds the exif data.

    @param buffer
    A CTBuffer that contains the thumbnail image data.

    @param rawInfo
    [optional] A structure describing the thumbnail if it is of raw rgb format.
    Must be NULL if the thumbnail is jpeg format

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_getThumbnailFromBuffer()\n
    exif_getThumbnailFromSession()\n
    exif_getThumbnailFromSession()

    @since 3.2
*/
SCBIMPORT CRESULT exif_addThumbnailToSession( CTExifSession exifSession, 
                                    const CTBuffer* buffer, 
                                    CTRawThumbnailInfo* rawInfo );

//----------------------------------------------------------------------------
/**
    @brief Parse out thumbnail and its orientation from an exif APP1 block

    @param pBuffer Buffer pointing to an FF E1 marker
    @param[out] pThumbnail Jpeg thumbnail information,
    i.e. if there is a jpeg thumbnail, its offset and orientation.

    @return CERR_OK or an error code on invalid parameters or corrupt exif data.

    @sa exif_getThumbnailFromBuffer()

    @since 3.8.2 R02
*/
SCBIMPORT CRESULT exif_getJpegThumbnailInfo( const CTBuffer *pBuffer,
                                             CTJpegThumbnailInfo *pThumbnail );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets the exif thumbnail from an image. Note that this function only
    supports jpeg format thumbnails. This is a faster way than getting the 
    thumbnail from the CTExifSession.

    @param imageBuffer
    A buffer containing the image. The image must have exif data.

    @param thumbBuffer
    A buffer that will recieve the thumbnail. The user must de-allocate this 
    buffer.

    @param orientation
    The orientation of the thumbnail.

    1 - 0th row at visual top of image. 0th column at visual left-hand side\n
    2 - 0th row at visual top of image. 0th column at visual right-hand side\n
    3 - 0th row at visual bottom of image. 0th column at visual right-hand side\n
    4 - 0th row at visual bottom of image. 0th column at visual left-hand side\n
    5 - 0th row at visual left-hand side of image. 0th column at visual top\n
    6 - 0th row at visual right-hand side of image. 0th column at visual top\n
	(Camera is rotated 90 degrees clockwise)\n
    7 - 0th row at visual right-hand side of image. 0th column at visual bottom\n
    8 - 0th row at visual left-hand side of image. 0th column at visual bottom\n
	(Camera is rotated 90 degrees counter-clockwise)\n
    
	@return 
    @c CERR_OK if successful, CERR_ITEM_NOT_FOUND if no thumbnail was found
        or a specific error code upon failure.
    
    @sa
    exif_getThumbnailFromFile()\n
    exif_getThumbnailFromSession()\n
    exif_addThumbnailToSession()

    @since 3.2
*/
SCBIMPORT CRESULT exif_getThumbnailFromBuffer( const CTBuffer* imageBuffer, 
                                     CTBuffer** thumbBuffer, 
                                     CTuint16* orientation );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets the exif thumbnail from an image from file. Note that this function 
    only supports jpeg format thumbnails. This is a faster way than getting the
    thumbnail from the CTExifSession.

    @param filename
    Filename of the imagee. The image must have exif data.

    @param thumbBuffer
    A buffer that will recieve the thumbnail. The user must de-allocate this 
    buffer. i.e. call caps_desrtoyBuffer().

    @param orientation
    The orientation of the thumbnail.

	1 - 0th row at visual top of image. 0th column at visual left-hand side\n
    2 - 0th row at visual top of image. 0th column at visual right-hand side\n
    3 - 0th row at visual bottom of image. 0th column at visual right-hand side\n
    4 - 0th row at visual bottom of image. 0th column at visual left-hand side\n
    5 - 0th row at visual left-hand side of image. 0th column at visual top\n
    6 - 0th row at visual right-hand side of image. 0th column at visual top\n
	(Camera is rotated 90 degrees clockwise)\n
    7 - 0th row at visual right-hand side of image. 0th column at visual bottom\n
    8 - 0th row at visual left-hand side of image. 0th column at visual bottom\n
	(Camera is rotated 90 degrees counter-clockwise)\n
    
	@return 
    @c CERR_OK if successful, CERR_ITEM_NOT_FOUND if no thumbnail was found
        or a specific error code upon failure.

    @sa
    exif_getThumbnailFromBuffer()\n
    exif_getThumbnailFromSession()\n
    exif_addThumbnailToSession()

    @since 3.2
*/
SCBIMPORT CRESULT exif_getThumbnailFromFile( const DCHAR* filename, 
                                   CTBuffer** thumbBuffer, 
                                   CTuint16* orientation );
/** @} */
// end 'fm_exif_thumbnail'

 //-----------------------------------------------------------------------------

/**
    @addtogroup fm_exif_general
    @{
*/

/**
    @brief Check if the stream contains a jpeg image with an exif (APP1) block.
    Get offset and size of that block.

    @note This function will restores the stream position to where it started reading,
    so the stream may safely be used in subsequent calls.

    @param pStream Stream that must have seek feature (canSeek). Stream must point to
    the start of a jpeg image.
    @param pHasExif will be set to false upon error or if no exif block was found,
    true if a block has been found.
    @param pOffset (Optional) Stream offset of the FF in the FF E1 marker (Only valid if *pHasExif is set to true)
    @param pLength (Optional) Length of app1 including FF E1 marker. (Only valid if *pHasExif is set to true)

    @return CERR_OK or an error code only if the stream reports an error.

    @remarks
    @li If CERR_OK is returned from this function, the stream offset has not
    been changed.
    @li If end of data is found, CERR_OK will be returned.

    @since 3.8.2 R02
*/
SCBIMPORT CRESULT exif_streamHasExif( CTStream *pStream,
                     CTbool *pHasExif,
                     CTuint32 *pOffset,
                     CTuint32 *pLength );

/**
    @brief Get the size of a flashpix (jpeg) screennail from a jpeg image.

    @note This function will restores the stream position to where it started reading,
    so the stream may safely be used in subsequent calls.

    @param pStream Stream that must have seek feature (canSeek). Stream must point
    to the start of a jpeg image.
    @param[out] pSize Size of the flashpix screennail jpeg data in bytes. If the stream contains
    no flashpix screennail, it is set to 0.
    @return @c CERR_OK or an error code.
    @c CERR_OK is returned also if the stream does not contain a flashpix screennail or if the
    stream is of unknown format.

    @remarks
    @li If CERR_OK is returned from this function, the stream offset has not
    been changed.

    @since 3.8.2 R03
*/
SCBIMPORT CRESULT exif_streamGetScreenNailSize( CTStream *pStream,
                                                CTuint32 *pSize );

/**
    @brief Get a flashpix (jpeg) screennail from a jpeg image.

    @note This function will restores the stream position to where it started reading,
    so the stream may safely be used in subsequent calls.

    @param pStream Stream that must have seek feature (canSeek). Stream must point
    to the start of a jpeg image.
    @param[out] pBuffer Buffer where the screen nail is copied to.
    The buffer must be allocated with the size of the screennail, as given from
    exif_streamGetScreenNailSize().

    @return CERR_OK or an error code.

    @remarks
    @li If CERR_OK is returned from this function, the stream offset has not
    been changed.
    @li This function does not guarantee that the jpeg data written to
    pBuffer is complete and correct.

    @since 3.8.2 R03
*/
SCBIMPORT CRESULT exif_streamGetScreenNail( CTStream *pStream,
                                            CTBuffer *pBuffer );

/**
    @brief
    Gets the orientation of an image 

    @param pBuffer
    A buffer containing the image. The image must have exif data. 

    @param orientation
    The orientation of the image.

    1 - 0th row at visual top of image. 0th column at visual left-hand side\n
    2 - 0th row at visual top of image. 0th column at visual right-hand side\n
    3 - 0th row at visual bottom of image. 0th column at visual right-hand side\n
    4 - 0th row at visual bottom of image. 0th column at visual left-hand side\n
    5 - 0th row at visual left-hand side of image. 0th column at visual top\n
    6 - 0th row at visual right-hand side of image. 0th column at visual top\n
	(Camera is rotated 90 degrees clockwise)\n
    7 - 0th row at visual right-hand side of image. 0th column at visual bottom\n
    8 - 0th row at visual left-hand side of image. 0th column at visual bottom\n
	(Camera is rotated 90 degrees counter-clockwise)\n
    
	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    exif_getTagOrientation()\n

    @since 3.2
*/
SCBIMPORT CRESULT exif_getImageOrientation( const CTBuffer* pBuffer, 
                                  CTuint16* orientation );

//-----------------------------------------------------------------------------
/**
    @brief
    Replaces the jfif header in a jpeg file with an exif header.
    Note that the exif header is independant of the image i.e
    tags like image dimensions will not be modified in this function.        

    @param jpegFile
    Buffer containg the jfif jpeg file.
	If not JFIF compliant, CERR_UNSUPPORTED_IMAGE will be returned.

    @param exifData
    Buffer containing the exif data to add.

    @param exifFile 
    Buffer with the resulting exif jpeg file. The buffer must be large enough
	to accomodate both the original image and the exif header.
	
	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @copydoc exif_newemptysession_example

    @since 3.2
*/
SCBIMPORT CRESULT exif_addExifToJfifFile( const CTBuffer* jpegFile, 
                                const CTBuffer* exifData, CTBuffer* exifFile);

//-----------------------------------------------------------------------------
/**
    @brief
    Replaces the jfif header in a jpeg file with an exif header and writes
	it to file. Note that the exif header is independant of the image i.e
    tags like image dimensions will not be modified in this function.        

    @param jpegFile
    Buffer containg the jfif jpeg file.
	If not JFIF compliant, CERR_UNSUPPORTED_IMAGE will be returned.

    @param exifData
    Buffer containing the exif data to add.

    @param filename 
    Filename of the resulting exif jpeg file.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6

*/
SCBIMPORT CRESULT exif_writeExifAndJfifToFile( const CTBuffer* jpegFile, 
									 const CTBuffer* exifData, const DCHAR* filename);

//-----------------------------------------------------------------------------
/**
    @brief
    Replaces the jfif header in a jpeg file with an exif header.
    Note that the exif header is independant of the image i.e
    tags like image dimensions will not be modified in this function.
    Also, the buffer containing the JFIF file must be large enough to 
    accommodate both the original jpeg file plus the exif data.

    @param jpegFile
    Buffer containg the jfif jpeg file.
	If not JFIF compliant, CERR_UNSUPPORTED_IMAGE will be returned.

    @param exifData
    Buffer containing the exif data to add.

    @param srcJpegSize 
    Size of original JFIF file if known, otherwise
    set to zero.
    
    @param newJpegSize 
    The resulting size of the jpeg after insertion of the
    exif data.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_insertExifIntoJfifFile(const CTBuffer* jpegFile, 
                                    const CTBuffer* exifData, 
                                    CTuint32  srcJpegSize,
                                    CTuint32* newJpegSize);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets the information assosiated with a specified tag        

    @param exifSession
    The session that holds the exif data.

    @param tagInfo
    A CTTaginfo structure that contains tag information.
    The user must allocate and deallocate this structure.
    Struct members, IFD, subIFD and tagId must be specified when calling.
    Members nofRecords, tagType and tagData will be set by the function.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @copydoc exif_getexifdata_example

    @since 3.2
*/
SCBIMPORT CRESULT exif_getExifData(CTExifSession exifSession, CTTagInfo* tagInfo);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets information assosiated with a specified tag        

    @param exifSession
    The session that holds the exif data.

    @param tagInfo
    A CTTaginfo structure that contains tag information.    
    The user must allocate and deallocate this structure.
    All members of this struct must be set by the caller.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @copydoc exif_setexifdata_example

    @since 3.2
*/
SCBIMPORT CRESULT exif_setExifData(CTExifSession exifSession, CTTagInfo* tagInfo);

//-----------------------------------------------------------------------------
/**
    @brief
    Deletes a specified tag        

    @param exifSession
    The session that holds the exif data.

    @param tagInfo
    A CTTaginfo structure that contains tag information. 
    The user must allocate and deallocate this structure.
    The struct members IFD and tagId must be set by the caller, 
    other members are ignored.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_deleteExifData(CTExifSession exifSession, CTTagInfo* tagInfo);

//-----------------------------------------------------------------------------
/**
    @brief
    Deletes all data within a specific IFD tag

    @param exifSession
    The session that holds the exif data.

    @param IFD
    The id of the IFD tag that should be deleted from the exif session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7 R7
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT exif_deleteExifIFD(CTExifSession exifSession, CTuint32 IFD);

//-----------------------------------------------------------------------------
/**
    @brief
    Deletes all data within a specific IFD tag

    @param exifSession
    The session that holds the exif data.

    @param IFD
    The id of the IFD tag that should be deleted from the exif session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7 R7
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT exif_deleteExifIFD(CTExifSession exifSession, CTuint32 IFD);

//-----------------------------------------------------------------------------
/**
    @brief
    Deletes all data within a specific sub-IFD tag.

    @param exifSession
    The session that holds the exif data.

    @param IFD
    The id of the IFD tag that holds the sub-IFD that should be deleted.

    @param subIFD
    The sub-IFD tag that should be deleted from the exif session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.7 R7
*/
//-----------------------------------------------------------------------------
SCBIMPORT CRESULT exif_deleteExifsubIFD( CTExifSession exifSession, CTuint32 IFD, 
                               EXIF_SUB_IFD subIFD );

//-----------------------------------------------------------------------------
/**
    @brief
    Checks if a specified tag exists and get information associated with the 
    tag.

    @param exifSession
    The session that holds the exif data.

    @param tagInfo
    A CTTaginfo structure that contains tag information. 
    The user must allocate and deallocate this structure.

	@return 
    @c CERR_OK if successful or CERR_EXIF_TAG_NOT_FOUND if the tag don't exists.

    @since 3.2
*/
SCBIMPORT CRESULT exif_checkExifData(CTExifSession exifSession, CTTagInfo* tagInfo);

/** @} */
// end 'fm_exif_general'

//-----------------------------------------------------------------------------

/**
    @addtogroup fm_exif_gettag
    @{
*/

/**
    @brief
    Gets tag 0x10f.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagMake(CTExifSession exifSession, CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x110.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagModel(CTExifSession exifSession, CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x132.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagDateTime(CTExifSession exifSession, CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9003.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagDateTimeOriginal( CTExifSession exifSession, 
                                     CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9004.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagDateTimeDigitized( CTExifSession exifSession, 
                                      CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x1.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagInteroperabilityIndex( CTExifSession exifSession, 
                                          CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x2.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagInteroperabilityVersion( CTExifSession exifSession, 
                                            CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9000.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagExifVersion( CTExifSession exifSession, 
                                CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa000.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagFlashPixVersion( CTExifSession exifSession, 
                                    CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9101.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagComponentsConfiguration( CTExifSession exifSession, 
                                            CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x128.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagResolutionUnit( CTExifSession exifSession, 
                                   CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x213.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagYCbCrPositioning( CTExifSession exifSession, 
                                     CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x8769.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagExifIdPointer( CTExifSession exifSession, 
                                  CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x112.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagOrientation( CTExifSession exifSession, 
                                CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa001.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagColorSpace(CTExifSession exifSession, CTint32* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa002.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagPixelXDimension( CTExifSession exifSession, 
                                    CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa003.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagPixelYDimension( CTExifSession exifSession, 
                                    CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x201.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagJpegInterchangeFormat( CTExifSession exifSession, 
                                          CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x103.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagThumbCompression( CTExifSession exifSession, 
                                     CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x128.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagThumbResolutionUnit( CTExifSession exifSession, 
                                        CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x202.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagJpegInterchangeFormatLength( CTExifSession exifSession, 
                                                CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x112.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagThumbOrientation( CTExifSession exifSession, 
                                     CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa401.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagCustomRendered( CTExifSession exifSession, 
                                   CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa402.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagExposureMode( CTExifSession exifSession, 
                                 CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa403.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagWhiteBalance( CTExifSession exifSession, 
                                 CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa406.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagSceneCaptureType( CTExifSession exifSession, 
                                     CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x8827.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagISOSpeedRatings( CTExifSession exifSession, 
                                    CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9208.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagLightSource( CTExifSession exifSession, 
                                CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9209.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagFlash( CTExifSession exifSession, 
                          CTint32* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x11a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagXResolution( CTExifSession exifSession, 
                                CTint32* numerator, CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x11b.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagYResolution(CTExifSession exifSession, 
                               CTint32* numerator, CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x11a. (IFD 1)

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagThumbXResolution( CTExifSession exifSession, 
                                     CTint32* numerator, 
                                     CTint32* denominator );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x11b. (IFD 1)

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagThumbYResolution( CTExifSession exifSession, 
                                     CTint32* numerator, 
                                     CTint32* denominator );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa404.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagDigitalZoomRatio( CTExifSession exifSession, 
                                     CTint32* numerator, 
                                     CTint32* denominator );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa407.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGainControl( CTExifSession exifSession, 
                                CTint32* numerator, CTint32* denominator );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9201.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagShutterSpeedValue( CTExifSession exifSession, 
                                      CTint32* numerator, 
                                      CTint32* denominator );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x829a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagExposureTime(CTExifSession exifSession, 
                               CTint32* numerator, CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9202.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagApertureValue( CTExifSession exifSession, 
                                  CTint32* numerator, CTint32* denominator );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x829d.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagFNumber( CTExifSession exifSession, 
                            CTint32* numerator, CTint32* denominator );

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x920a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagFocalLength( CTExifSession exifSession, 
                                CTint32* numerator, CTint32* denominator );
/** @} */
// end 'fm_exif_gettag'

//-----------------------------------------------------------------------------

/**
    @addtogroup fm_exif_settag
    @{
*/

/**
    @brief
    sets tag 0x10f.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. This ascii string must be NULL terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagMake(CTExifSession exifSession, CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x110.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. This ascii string must be NULL terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagModel(CTExifSession exifSession, CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x132.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. This ascii string must be NULL terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagDateTime(CTExifSession exifSession, CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9003.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. This ascii string must be NULL terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagDateTimeOriginal( CTExifSession exifSession, 
                                     CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9004.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. This ascii string must be NULL terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagDateTimeDigitized( CTExifSession exifSession, 
                                      CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x1.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. This ascii string must be NULL terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagInteroperabilityIndex( CTExifSession exifSession, 
                                          CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x2.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagInteroperabilityVersion( CTExifSession exifSession, 
                                            CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9000.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagExifVersion( CTExifSession exifSession, 
                                CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa000.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagFlashPixVersion( CTExifSession exifSession, 
                                    CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9101.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagComponentsConfiguration( CTExifSession exifSession, 
                                            CTuint8* parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x128.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagResolutionUnit( CTExifSession exifSession, 
                                   CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x213.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagYCbCrPositioning( CTExifSession exifSession, 
                                     CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x8769.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagExifIdPointer( CTExifSession exifSession, 
                                  CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x112.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagOrientation( CTExifSession exifSession, CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa001.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagColorSpace( CTExifSession exifSession, CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa002.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagPixelXDimension( CTExifSession exifSession, 
                                    CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa003.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagPixelYDimension( CTExifSession exifSession, 
                                    CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x201.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagJpegInterchangeFormat( CTExifSession exifSession, 
                                          CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x103.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagThumbCompression( CTExifSession exifSession, 
                                     CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x128.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagThumbResolutionUnit( CTExifSession exifSession, 
                                        CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x202.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagJpegInterchangeFormatLength( CTExifSession exifSession, 
                                                CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x112.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagThumbOrientation( CTExifSession exifSession, 
                                     CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa401.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagCustomRendered( CTExifSession exifSession, 
                                   CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa402.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagExposureMode( CTExifSession exifSession, 
                                 CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa403.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagWhiteBalance(CTExifSession exifSession, CTint32 parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa406.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagSceneCaptureType( CTExifSession exifSession, 
                                     CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x8827.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagISOSpeedRatings( CTExifSession exifSession, 
                                    CTint32 parameter );

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9208.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagLightSource(CTExifSession exifSession, CTint32 parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9209.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagFlash(CTExifSession exifSession, CTint32 parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x11a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagXResolution(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x11b.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagYResolution(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x11a. (IFD 1)

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagThumbXResolution(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x11b. (IFD 1)

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagThumbYResolution(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa404.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagDigitalZoomRatio(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa407.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGainControl(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9201.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagShutterSpeedValue(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x829a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagExposureTime(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9202.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagApertureValue(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x829d.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagFNumber(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x920a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagFocalLength(CTExifSession exifSession, 
                               CTint32 numerator, CTint32 denominator);
/** @} */
// end 'fm_exif_settag'

//-----------------------------------------------------------------------------

/**
    @addtogroup fm_exif_gpstags
    @{
*/

/**
    @brief
    Sets tag 0x0.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSVersion(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x0.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

    @param paramSize
    The size of the data to get.
    If parameter is NULL, the function sets paramSize 
    to the amount of bytes needed for parameter.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSVersion(CTExifSession exifSession, 
                              CTuint8* parameter,
                              CTuint32* paramSize);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x5.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSAltitudeReference(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa5.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSAltitudeReference(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x1.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSLatitudeReference(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x1.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSLatitudeReference(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x3.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSLongitudeReference(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa3.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSLongitudeReference(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x9.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSStatus(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x9.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSStatus(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xa.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSMeasureMode(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xa.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSMeasureMode(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xc.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSSpeedRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xc.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSSpeedRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xe.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSTrackRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xe.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSTrackRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x10.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSImgDirectionRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x10.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSImgDirectionRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x13.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestLatitudeRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x13.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestLatitudeRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x15.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestLongitudeRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x15.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestLongitudeRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x17.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestBearingRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x17.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestBearingRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x19.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestDistanceRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x19.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestDistanceRef(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x8.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. Must be null terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSSatellites(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x8.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSSatellites(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x12.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to set. Must be null terminated.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSMapDatum(CTExifSession exifSession, 
                              CTuint8* parameter);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x12.

    @param exifSession
    The session that holds the exif data.

    @param parameter
    The data to get.

    @param paramSize
    The size of the data to get.
    If parameter is NULL, the function sets paramSize 
    to the amount of bytes needed for parameter.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSMapDatum(CTExifSession exifSession, 
                              CTuint8* parameter, 
                              CTuint32* paramSize);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x6.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSAltitude(CTExifSession exifSession, 
                              CTint32 numerator,
                              CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x6.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSAltitude(CTExifSession exifSession, 
                              CTint32* numerator,
                              CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xb.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDOP(CTExifSession exifSession, 
                              CTint32 numerator,
                              CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xb.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDOP(CTExifSession exifSession, 
                              CTint32* numerator,
                              CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xd.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSSpeed(CTExifSession exifSession, 
                              CTint32 numerator,
                              CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xd.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSSpeed(CTExifSession exifSession, 
                              CTint32* numerator,
                              CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0xf.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSTrack(CTExifSession exifSession, 
                              CTint32 numerator,
                              CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0xf.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSTrack(CTExifSession exifSession, 
                              CTint32* numerator,
                              CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x11.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSImgDirection(CTExifSession exifSession, 
                              CTint32 numerator,
                              CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x11.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSImgDirection(CTExifSession exifSession, 
                              CTint32* numerator,
                              CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x18.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestBearing(CTExifSession exifSession, 
                              CTint32 numerator,
                              CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x18.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestBearing(CTExifSession exifSession, 
                              CTint32* numerator,
                              CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x1a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to set.

    @param denominator
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestDistance(CTExifSession exifSession, 
                              CTint32 numerator,
                              CTint32 denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x1a.

    @param exifSession
    The session that holds the exif data.

    @param numerator
    The numerator of the data value to get.

    @param denominator
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestDistance(CTExifSession exifSession, 
                              CTint32* numerator,
                              CTint32* denominator);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x2.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to set.

    @param denominator1
    The denominator of the data value to set

    @param numerator2
    The numerator of the data value to set.

    @param denominator2
    The denominator of the data value to set

    @param numerator3
    The numerator of the data value to set.

    @param denominator3
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSLatitude(CTExifSession exifSession, 
                               CTint32 numerator1, CTint32 denominator1,
                               CTint32 numerator2, CTint32 denominator2,
                               CTint32 numerator3, CTint32 denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x2.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to get.

    @param denominator1
    The denominator of the data value to get

    @param numerator2
    The numerator of the data value to get.

    @param denominator2
    The denominator of the data value to get

    @param numerator3
    The numerator of the data value to get.

    @param denominator3
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSLatitude(CTExifSession exifSession, 
                               CTint32* numerator1, CTint32* denominator1,
                               CTint32* numerator2, CTint32* denominator2,
                               CTint32* numerator3, CTint32* denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x4.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to set.

    @param denominator1
    The denominator of the data value to set

    @param numerator2
    The numerator of the data value to set.

    @param denominator2
    The denominator of the data value to set

    @param numerator3
    The numerator of the data value to set.

    @param denominator3
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSLongitude(CTExifSession exifSession, 
                               CTint32 numerator1, CTint32 denominator1,
                               CTint32 numerator2, CTint32 denominator2,
                               CTint32 numerator3, CTint32 denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x4.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to get.

    @param denominator1
    The denominator of the data value to get

    @param numerator2
    The numerator of the data value to get.

    @param denominator2
    The denominator of the data value to get

    @param numerator3
    The numerator of the data value to get.

    @param denominator3
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSLongitude(CTExifSession exifSession, 
                               CTint32* numerator1, CTint32* denominator1,
                               CTint32* numerator2, CTint32* denominator2,
                               CTint32* numerator3, CTint32* denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x7.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to set.

    @param denominator1
    The denominator of the data value to set

    @param numerator2
    The numerator of the data value to set.

    @param denominator2
    The denominator of the data value to set

    @param numerator3
    The numerator of the data value to set.

    @param denominator3
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSTimeStamp(CTExifSession exifSession, 
                               CTint32 numerator1, CTint32 denominator1,
                               CTint32 numerator2, CTint32 denominator2,
                               CTint32 numerator3, CTint32 denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x7.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to get.

    @param denominator1
    The denominator of the data value to get

    @param numerator2
    The numerator of the data value to get.

    @param denominator2
    The denominator of the data value to get

    @param numerator3
    The numerator of the data value to get.

    @param denominator3
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSTimeStamp(CTExifSession exifSession, 
                               CTint32* numerator1, CTint32* denominator1,
                               CTint32* numerator2, CTint32* denominator2,
                               CTint32* numerator3, CTint32* denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x14.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to set.

    @param denominator1
    The denominator of the data value to set

    @param numerator2
    The numerator of the data value to set.

    @param denominator2
    The denominator of the data value to set

    @param numerator3
    The numerator of the data value to set.

    @param denominator3
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestLatitude(CTExifSession exifSession, 
                               CTint32 numerator1, CTint32 denominator1,
                               CTint32 numerator2, CTint32 denominator2,
                               CTint32 numerator3, CTint32 denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x14.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to get.

    @param denominator1
    The denominator of the data value to get

    @param numerator2
    The numerator of the data value to get.

    @param denominator2
    The denominator of the data value to get

    @param numerator3
    The numerator of the data value to get.

    @param denominator3
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestLatitude(CTExifSession exifSession, 
                               CTint32* numerator1, CTint32* denominator1,
                               CTint32* numerator2, CTint32* denominator2,
                               CTint32* numerator3, CTint32* denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Sets tag 0x16.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to set.

    @param denominator1
    The denominator of the data value to set

    @param numerator2
    The numerator of the data value to set.

    @param denominator2
    The denominator of the data value to set

    @param numerator3
    The numerator of the data value to set.

    @param denominator3
    The denominator of the data value to set

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_setTagGPSDestLongitude(CTExifSession exifSession, 
                               CTint32 numerator1, CTint32 denominator1,
                               CTint32 numerator2, CTint32 denominator2,
                               CTint32 numerator3, CTint32 denominator3);

//-----------------------------------------------------------------------------
/**
    @brief
    Gets tag 0x16.

    @param exifSession
    The session that holds the exif data.

    @param numerator1
    The numerator of the data value to get.

    @param denominator1
    The denominator of the data value to get

    @param numerator2
    The numerator of the data value to get.

    @param denominator2
    The denominator of the data value to get

    @param numerator3
    The numerator of the data value to get.

    @param denominator3
    The denominator of the data value to get

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.2
*/
SCBIMPORT CRESULT exif_getTagGPSDestLongitude(CTExifSession exifSession, 
                               CTint32* numerator1, CTint32* denominator1,
                               CTint32* numerator2, CTint32* denominator2,
                               CTint32* numerator3, CTint32* denominator3);

/** @} */
// end 'fm_exif_gpstags'

//-----------------------------------------------------------------------------

/**
    @addtogroup fm_exif_examples
    @{
*/

/**
    @page exif_newsessionwithbuffer_example Read existing Exif header

    @par Example use case:
    Read existing exif header from buffer, modify, delete or add tags or thumbnails,
    output the resulting exif header to buffer.

    @code
    //Example: Read existing exif header from buffer,
    //Modify, delete or add tags or thumbnails,
    //output the resulting exif header to buffer
    CRESULT res = CERR_OK;
    CTBuffer* inputBuffer = 0;
    CTBuffer* exifBuffer = 0;
    CTExifSession exifSession = 0;
    CTuint32 exifSize;
    CTFile* file;
    CTuint32 fileSize;

    res = oslfile_open(_D("exif.jpg"), FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
    fileSize = oslfile_size(file);
    caps_createBuffer(fileSize, &inputBuffer);
    oslfile_read(file, inputBuffer->data, inputBuffer->size);
    oslfile_close(file);

    res = exif_newSessionWithBuffer(inputBuffer, &exifSession); 
    caps_destroyBuffer(inputBuffer);
    //...
    //Modify, delete or add tags or thumbnails
    //
    res = exif_getExifBlockSize(exifSession, &exifSize);

    res = caps_createBuffer(exifSize, &exifBuffer);
    res = exif_renderSession(exifSession, exifBuffer);
    res = exif_destroySession(exifSession);
    //...
    @endcode
*/
//.............................................................................
/**
    @page exif_newemptysession_example Start an empty exif session

    @par Example use case:
    Start an empty exif session, add some tags, add thumbnail from an
    existing CTSession, output the resulting exif header to an existing
    JFIF file, and save to file as a new exif file.

	@code
	//Example: Start an empty exif session,
	//add some tags, add thumbnail from an existing CTSession,
	//output the resulting exif header to an existing JFIF file,
	//and save to file as a new exif file
	CRESULT res = CERR_OK;
	CTBuffer* buffer = 0;
	CTBuffer* jfifBuffer = 0;
	CTBuffer* outBuffer = 0;
	CTExifSession exifSession = 0;
	CTSize thumbSize = {320, 240};
	CTuint32 exifSize = 0;
	CTuint32 newJpegSize = 0;
	CTuint32 fileSize = 0;
	CTFile* file;
	CTuint32 nofBytes = 0;
	
	res = exif_newSessionWithBlank(&exifSession); 
	res = exif_setTagMake(exifSession, (CTuint8*)"COMPANY ABC");
	res = exif_setTagThumbCompression(exifSession, 6); //6 means jpeg compression

	//Use YUV422 for DCT compliance
	res = caps_uthSetJpegColorspacing(sess, CS_YUV422); 
	caps_createBuffer(0, &buffer);
	res = caps_renderToBuffer(sess, buffer, 0, thumbSize, 
		CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);	

	res = exif_addThumbnailToSession(exifSession, buffer, 0);
	caps_destroyBuffer(buffer);

	res = exif_getExifBlockSize(exifSession, &exifSize);
	caps_createBuffer(exifSize, &buffer);
	res = exif_renderSession(exifSession, buffer); 
	exif_destroySession(exifSession);

	res = oslfile_open(_D("jfif.jpg"), FOF_ACCESS_READ | FOF_MODE_BINARY, &file);
	fileSize = oslfile_size(file);
	caps_createBuffer(fileSize, &jfifBuffer);
	nofBytes = oslfile_read(file, jfifBuffer->data, jfifBuffer->size);
	oslfile_close(file);

	caps_createBuffer(fileSize + exifSize, &outBuffer);
	res = exif_addExifToJfifFile(jfifBuffer, buffer, outBuffer); 

	res = oslfile_open(_D("exif.jpg"), FOF_ACCESS_WRITE | FOF_MODE_BINARY, &file);
	nofBytes = oslfile_write(file, outBuffer->data, outBuffer->size);
	oslfile_close(file);
	
	//destroy
	caps_destroyBuffer(buffer);
	caps_destroyBuffer(jfifBuffer);
	caps_destroyBuffer(outBuffer);
	//...
	@endcode
*/
//.............................................................................
/**
    @page exif_getexifdata_example Get Exif data.
	@code
	CTExifSession exifSession;
	CRESULT res = CERR_OK;
	CTTagInfo tagInfo = {0};
	char myMakeString[256] = {0};

	res = exif_newSessionWithFile(_D("exif.jpg"), &exifSession);

	//Get tag 0x10f, "Make"
	tagInfo.IFD = 0;
	tagInfo.subIFD = IFD_ROOT;
	tagInfo.tagId = 0x10f;
	
	res = exif_getExifData(exifSession, &tagInfo);
	
	//Copy to myMakeString
	memcpy(myMakeString, tagInfo.tagData, tagInfo.nofRecords * sizeof(char));
	
	exif_destroySession(exifSession);
	@endcode
*/
//.............................................................................
/**
    @page exif_setexifdata_example Set Exif data.
	@code
	CTExifSession exifSession;
	CRESULT res = CERR_OK;
	CTTagInfo tagInfo = {0};
	CTuint8 data[2] = {0};

	res = exif_newSessionWithFile(_D("exif.jpg"), &exifSession);

	//Set tag 0x103, "Compression" in IFD1 (thumbnail)
	tagInfo.IFD = 1;//thumbnail
	tagInfo.subIFD = IFD_ROOT;
	tagInfo.tagId = 0x103;
	tagInfo.nofRecords = 1;
	tagInfo.tagType = 3; //Short
	data[0] = 0;
	data[1] = 6;
	tagInfo.tagData = (CTuint8*)data;	
	res = exif_setExifData(exifSession, &tagInfo);

	//Set tag 0x110, "Model" in main image
	tagInfo.IFD = 0;//main image
	tagInfo.subIFD = IFD_ROOT;
	tagInfo.tagId = 0x110;
	tagInfo.nofRecords = 8;//including NULL at end
	tagInfo.tagType = 2; //ascii
	tagInfo.tagData = (CTuint8*)"SCALADO";
	res = exif_setExifData(exifSession, &tagInfo);
	
	exif_destroySession(exifSession);
	@endcode
*/

/**
    @}
*/ // end 'fm_exif_examples'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_EXIF_H )
