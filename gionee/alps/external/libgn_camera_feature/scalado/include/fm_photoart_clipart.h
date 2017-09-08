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

#ifndef FM_PHOTOART_CLIPART_H
#define FM_PHOTOART_CLIPART_H
 
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/** 
    @ingroup fm_photoart
    @file fm_photoart_clipart.h
    @brief Defines the available API's clipart and frame effect 
    in Caps Feature Module: @a PhotoArt
*/
//=============================================================================
/**
    @addtogroup fm_photoart
    @{
*/

/**
    @defgroup fxgroup_frame Frame
    @{
*/
//.............................................................................
/**
    @brief
    Inserts a frame on the current session image.

    @param session
    Handle to a valid session.

    @param pStream
    A pointer to a stream containing the frame image. The ownership of the stream
    stays with the caller and must stay alive until the session is destroyed.

    @param format
    The image format of the stream.

    @param streamOwnership
    An option from the ::OWNERSHIP_POLICY enumeration which specifies what
    ownership policy to use with the @a pStream argument. If CAPS is given
    ownership responsibility over @a pStream, it will be destroyed using
    caps_destroyStream() when no longer needed. 
    The ownership is only transferred to CAPS if the function succeeds.

    @remarks

    A frame is an overlay image stretched or contracted to fit the size of the
    session image.

    The following image types are supported:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertFrameFromFile()\n
    caps_insertFrameFromBuffer()\n
    caps_insertFrameFromRaw()

    @since 3.8

*/
SCBIMPORT CRESULT caps_insertFrame( CTSession session, 
                          CTStream* pStream,
                          IMAGE_FORMAT_SPEC format,
                          OWNERSHIP_POLICY streamOwnership );

//.............................................................................
/**
    @brief
    Inserts a frame on the current session image.
   
    @param session
    Handle to a valid session.
    
    @param filename
    String specifying the filesystem path of the image.
    
    @remarks

    A frame is an overlay image stretched or contracted to fit the size of the
    session image.

    The following image types are supported:

    @li PNG
    @li GIF
    @li JPEG 
    @li BMP
    @li WBMP
    @li TIFF

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertFrameFrom()\n
    caps_insertFrameFromBuffer()\n
    caps_insertFrameFromRaw()

    @since 3.0 (support for more image types in 3.8)
*/
SCBIMPORT CRESULT caps_insertFrameFromFile( CTSession session, const DCHAR* filename );

//.............................................................................
/**
    @brief
    Inserts a frame on the current session image.
   
    @param session
    Handle to a valid session.
    
    @param buffer
    A memory buffer containing the frame image. The ownership of the buffer
    stays with the caller and must stay alive until the session is destroyed.
    
	@param bufferOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a buffer argument. If CAPS is given
	ownership responsibility over @a buffer, it will be destroyed using
	caps_destroyBuffer() when no longer needed. Available since 3.2.
    The ownership is only transfered to CAPS if the function succedes.

    @remarks

    A frame is an overlay image stretched or contracted to fit the size of the
    session image.

    The following image types are supported:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_insertFrameFrom()\n
    caps_insertFrameFromFile()\n
    caps_insertFrameFromRaw()

    @since 3.1 (parameters modified in 3.2, support for more image types in 3.8)
*/
SCBIMPORT CRESULT caps_insertFrameFromBuffer( CTSession session, 
                                    CTBuffer* buffer,
									OWNERSHIP_POLICY bufferOwnership );

//.............................................................................
/**
    @brief
    Inserts a frame on the current session image.
   
    @param session
    Handle to a valid session.
    
    @param image
    An @c CTImage containing raw data. The ownership of the raw data buffer
    stays with the caller but must stay alive until the session is destroyed.
    
	@param imageOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a image argument. If CAPS is given
	ownership responsibility over @a image, it will be destroyed using
	caps_destroyImage() when no longer needed. Available since 3.2.
    The ownership is only transfered to CAPS if the function succedes.

    @remarks
    A frame is an overlay image stretched or contracted to fit the size of the
    session image.\n\n

    IMPORTANT:\n
    The raw image data must be in one of the following color formats:
    - @c CM_AYUV4444
    - @c CM_ARGB8888
    - @c CM_BGRA8888
    - @c CM_RGBA8888
    - @c CM_ABGR8888
	- @c CM_ARGB6666
	- @c CM_GBRGAR264462
    - @c CM_BGRA6666
    - @c CM_A8R8G8B8
    - @c CM_RGB565_G0
    - @c CM_BGR565_G0
    .

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    casp_insertFrame()\n
    caps_insertFrameFromBuffer()\n
    caps_insertFrameFromFile()

    @since 3.1 (parameters modified in 3.2)

*/

SCBIMPORT CRESULT caps_insertFrameFromRaw( CTSession session, 
                                 CTImage* image, 
								 OWNERSHIP_POLICY imageOwnership );
/** @} */
// 'Frame'



/**
    @defgroup fxgroup_clipart Clipart 
    @{
*/
//.............................................................................
/**
    @brief The handle type used for clipart insertion sessions.
*/
typedef struct caps_clipart* CAPS_CLIPART;
//.............................................................................
/**
    @brief
    Begins the task of inserting a clipart image on the current session image.

    @param session 
    A valid session handle.

    @param pStream 
    A pointer to a stream containing a image.

    @param streamOwnership
    An option from the ::OWNERSHIP_POLICY enumeration which specifies what
    ownership policy to use with the @a pStream argument. If CAPS is given
    ownership responsibility over @a pStream, it will be destroyed using
    caps_destroyStream() when no longer needed. 
    The ownership is only transfered to CAPS if the function succeeds.

    @param format
    The image format of the stream.

    @param position
    A @c CTPoint object specifying the vertical and horizontal position of the 
    clipart in current coordinates. Position refers to the center of the clipart.

    @param scale
    Clipart scaling factor. Range [0.1, 64.0].

    @param angle
    Rotation of the clipart in degrees, [0.0 360.0].

    @param out_clipart
    Pointer to a clipart handle which will receive the handle to the clipart
    for subsequent adjustments and conclusion of the clipart insertion. See
    remarks section for details.

    @remarks

    The task of inserting a clipart is carried out in three stages:

    @li 1.) Begin clipart insertion.
    @li 2.) Adjust clipart orientation (optional)
    @li 3.) End clipart insertion.

    Between step 1 and 3, no other effects or operations may be carried out.
    I.e the clipart insertion task have to be concluded/ended before proceeding
    with other effects. A clipart cannot be modified once the insertion
    process has been ended, the clipart handle is effectively turned invalid
    after calling caps_endClipart().

    The following image formats are supported for the input image stream:

    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setClipartOrientation()\n
    caps_getClipartOrientation()\n
    caps_getClipartSize()\n
    caps_endClipart()\n
    caps_beginClipartFromFile()\n
    caps_beginClipartFromRaw()\n
    caps_beginClipartFromBuffer()

    @since 3.8
*/
SCBIMPORT CRESULT caps_beginClipart( CTSession session, 
                           CTStream* pStream,
                           OWNERSHIP_POLICY streamOwnership,
                           IMAGE_FORMAT_SPEC format,
                           CTPoint position, 
                           CTfloat scale, 
                           CTfloat angle, 
                           CAPS_CLIPART* out_clipart );


//.............................................................................
/**
    @brief
    Begins the task of inserting a clipart image on the current session image.

    @param session 
    A valid session handle.

    @param filename 
    String specifying the filesystem path of the image.

    @param format
    The image format of the file.

    @param position
    A @c CTPoint object specifying the vertical and horizontal position of the 
    clipart in current coordinates. Position refers to the center of the clipart.

    @param scale    
    Clipart scaling factor. Range [0.1, 64.0].

    @param angle
    Rotation of the clipart in degrees, [0.0 360.0].

    @param out_clipart
    Pointer to a clipart handle which will receive the handle to the clipart
    for subsequent adjustments and conclusion of the clipart insertion. See
    remarks section for details.

    @remarks

    The task of inserting a clipart is carried out in three stages:
    @li 1.) Begin clipart insertion.
    @li 2.) Adjust clipart orientation (optional)
    @li 3.) End clipart insertion.

    Between step 1 and 3, no other effects or operations may be carried out.
    I.e the clipart insertion task have to be concluded/ended before proceeding
    with other effects. A clipart cannot be modified once the insertion
    process has been ended, the clipart handle is effectively turned invalid
    after calling caps_endClipart().

    The following image formats are supported for the input image file:
    @li JPEG 
    @li PNG
    @li GIF
    @li BMP
    @li WBMP
    @li TIFF

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setClipartOrientation()\n
    caps_getClipartOrientation()\n
    caps_getClipartSize()\n
    caps_endClipart()\n
    caps_beginClipartFromRaw()\n
    caps_beginClipartFromBuffer()

    @since 3.0 (parameters modified in 3.2, support for more formats in 3.8)
*/
SCBIMPORT CRESULT caps_beginClipartFromFile( CTSession session, const DCHAR* filename,
                                   IMAGE_FORMAT_SPEC format,
                                   CTPoint position, CTfloat scale, 
                                   CTfloat angle, CAPS_CLIPART* out_clipart );


//.............................................................................
/**
    @brief
    Begins the task of inserting a buffered clipart image on the current 
    session image.

    @param session 
    A valid session handle.

    @param buffer 
    A @c CTBuffer pointer to the buffer data. The format of the data within this
    buffer must be specified through the @c format argument. Ownership of the
    buffer remains with the caller but must stay alive until the associated
    session is destroyed.

	@param bufferOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a buffer argument. If CAPS is given
	ownership responsibility over @a buffer, it will be destroyed using
	caps_destroyBuffer() when no longer needed. Available since 3.2.
    The ownership is only transfered to CAPS if the function succedes.

    @param format 
    The format of the image data contained in @c buffer. Can be any of the
    formats specified in the @c ::IMAGE_FORMAT_SPEC enumeration.

    @param position
    A @c CTPoint object specifying the vertical and horizontal position of the 
    clipart in current coordinates. Position refers to the center of the 
    clipart.

    @param scale    
    Clipart scaling factor. Range [0.1, 64.0].

    @param angle
    Rotation of the clipart in degrees, [0.0 360.0].

    @param out_clipart
    Pointer to a clipart handle which will receive the handle to the clipart
    for subsequent adjustments and conclusion of the clipart insertion. See
    remarks section for details.

    @remarks

    The task of inserting a clipart is carried out in three stages:

    @li 1.) Begin clipart insertion.
    @li 2.) Adjust clipart orientation (optional)
    @li 3.) End clipart insertion.

    Between step 1 and 3, no other effects or operations may be carried out.
    I.e. the clipart insertion task have to be concluded/ended before proceeding
    with other effects. A clipart cannot be modified once the insertion
    process has been ended, the clipart handle is effectively turned invalid
    after calling caps_endClipart().
    
    @return 
    @c CERR_OK if successful or a specific error code upon failure.
    
    @sa
    caps_setClipartOrientation()\n
    caps_getClipartOrientation()\n
    caps_getClipartSize()\n
    caps_endClipart()\n
    caps_beginClipartFromRaw()\n
    caps_beginClipartFromFile()

    @since 3.1 (parameters modified in 3.2)
*/
SCBIMPORT CRESULT caps_beginClipartFromBuffer( CTSession session, CTBuffer* buffer, 
									 OWNERSHIP_POLICY bufferOwnership,
                                     IMAGE_FORMAT_SPEC format, CTPoint position, 
                                     CTfloat scale, CTfloat angle, 
                                     CAPS_CLIPART* out_clipart );


//.............................................................................
/**
    @brief
    Begins the task of inserting a clipart image on the current session image.

    @param session 
    A valid session handle.

    @param image 
    Pointer to a @c CTImage object containing the clipart image. Ownership of
    the raw data buffer remains with the caller but it must stay alive until
    the associated session is destroyed.

	@param imageOwnership
	An option from the ::OWNERSHIP_POLICY enumeration which specifies what
	ownership policy to use with the @a image argument. If CAPS is given
	ownership responsibility over @a image, it will be destroyed using
	caps_destroyImage() when no longer needed. Available since 3.2.
    The ownership is only transfered to CAPS if the function succedes.

    @param position
    A @c CTPoint object specifying the vertical and horizontal position of the 
    clipart in current coordinates. Position refers to the center of the clipart.

    @param scale    
    Clipart scaling factor. Range [0.1, 64.0].

    @param angle
    Rotation of the clipart in degrees, [0.0 360.0].

    @param out_clipart
    Pointer to a clipart handle which will receive the handle to the clipart
    for subsequent adjustments and conclusion of the clipart insertion. See
    remarks section for details.

    @remarks

    The task of inserting a clipart is carried out in three stages:

    @li 1.) Begin clipart insertion.
    @li 2.) Adjust clipart orientation (optional)
    @li 3.) End clipart insertion.

    Between step 1 and 3, no other effects or operations may be carried out.
    I.e. the clipart insertion task have to be concluded/ended before proceeding
    with other effects. A clipart cannot be modified once the insertion
    process has been ended, the clipart handle is effectively turned invalid
    after calling caps_endClipart().\n\n

	IMPORTANT:

    The raw image data must be in one of the valid (input) color formats,
    specified in: @ref supported_colorformats

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

    @sa
    caps_setClipartOrientation()\n
    caps_getClipartOrientation()\n
    caps_getClipartSize()\n
    caps_endClipart()\n
    caps_beginClipartFromBuffer()\n
    caps_beginClipartFromFile()

    @since 3.0 (parameters modified in 3.2)
*/
SCBIMPORT CRESULT caps_beginClipartFromRaw( CTSession session, CTImage* image,
								  OWNERSHIP_POLICY imageOwnership,
                                  CTPoint position, CTfloat scale, 
                                  CTfloat angle, CAPS_CLIPART* out_clipart );


//.............................................................................
/**
    @brief
    Adjusts the orientation of a clipart previthe most recently inserted clipart.

    The coordinates given to this function is interpreted as being within the
    current coordinate system. See section 'Coordinate conversions'
    in @ref caps_baseapi_screen
    
    @param clipart
    A valid clipart handle which has been created in a previous call to one of
    the "begin clipart" functions.

    @param position
    A @c CTPoint object specifying the vertical and horizontal position of the 
    clipart in current coordinates. Position refers to the center of the clipart.

    @param scale    
    Clipart scaling factor. Range [0.1, 64.0].

    @param angle
    Rotation of the clipart in degrees, [0.0 360.0].

    @remarks

    Note that a clipart handle is invalid after calling caps_endClipart() with
    it. The behaviour when calling this function with an invalid clipart handle
    is undefined.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa    
    caps_getClipartOrientation()\n
    caps_getClipartSize()\n
    caps_endClipart()\n
    caps_beginClipartFromBuffer()\n
    caps_beginClipartFromFile()\n
    caps_beginClipartFromRaw()

    @since 3.0
*/
SCBIMPORT CRESULT caps_setClipartOrientation( CAPS_CLIPART clipart, CTPoint position, 
                                    CTfloat scale, CTfloat angle);


//.............................................................................
/**
    @brief
    Retrieves the current orientation setting for a clipart.

    All coordinates retrieved should be regarded within the current 
    coordinate system.

    @param clipart
    A valid clipart handle which has been created in a previous call to one of
    the "begin clipart" functions.

    @param position
    Pointer to a @c CTPoint object which will receive the current clipart 
    position. Position refers to the center of the clipart.

    @param scale    
    Pointer to a @c CTfloat value which will receive the current clipart scaling 
    factor.

    @param angle
    Pointer to a @c CTfloat value which will receive the current clipart rotation
    angle in degrees, [0.0 360.0].

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setClipartOrientation()\n    
    caps_getClipartSize()\n
    caps_endClipart()\n
    caps_beginClipartFromBuffer()\n
    caps_beginClipartFromFile()\n
    caps_beginClipartFromRaw()

    @since 3.0
*/
SCBIMPORT CRESULT caps_getClipartOrientation( CAPS_CLIPART clipart, CTPoint* position, 
                                    CTfloat* scale, CTfloat* angle);


//.............................................................................
/**
    @brief
    Retrieves the current size of a clipart.

    The retrieved size should be regarded within the current coordinate 
    system.

    @param clipart
    A valid clipart handle which has been created in a previous call to one of
    the "begin clipart" functions.

    @param size
    Pointer to a @c CTSize object which will receive the current clipart size.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setClipartOrientation()\n    
    caps_getClipartOrientation()\n
    caps_endClipart()\n
    caps_beginClipartFromBuffer()\n
    caps_beginClipartFromFile()\n
    caps_beginClipartFromRaw()

    @since 3.0
*/
SCBIMPORT CRESULT caps_getClipartSize( CAPS_CLIPART clipart, CTSize* size );


//.............................................................................
/**
    @brief
    Retrieves the current bounding box of a clipart.

    The retrieved rectangle should be regarded within the current coordinate 
    system.

    @param clipart
    A valid clipart handle which has been created in a previous call to one of
    the "begin clipart" functions.

    @param rect
    Pointer to a @c CTRect object which will receive the current clipart
    bounding box.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setClipartOrientation()\n    
    caps_getClipartOrientation()\n
    caps_endClipart()\n
    caps_beginClipartFromBuffer()\n
    caps_beginClipartFromFile()\n
    caps_beginClipartFromRaw()

    @since 3.6
*/
SCBIMPORT CRESULT caps_getClipartRect( CAPS_CLIPART clipart, CTRect* rect );


//.............................................................................
/**
    @brief
    Concludes the task of inserting a clipart image.

    @param clipart
    A valid handle to a clipart which has been created in a previous call to
    one of the "begin clipart" functions.

    @remarks

    The clipart handle is invalid after calling this function and should
    preferably be set to NULL directly upon calling it.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa
    caps_setClipartOrientation()\n    
    caps_getClipartOrientation()\n   
    caps_getClipartSize()\n
    caps_beginClipartFromBuffer()\n
    caps_beginClipartFromFile()\n
    caps_beginClipartFromRaw()

    @since 3.0
*/
SCBIMPORT CRESULT caps_endClipart( CAPS_CLIPART clipart );


/** @} */
// end 'Clipart'

/**
    @}
*/
// end 'fm_photoart'
//=============================================================================
#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_PHOTOART_CLIPART_H )
