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

#ifndef CTIMAGECHANNELS_H
#define CTIMAGECHANNELS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctimage.h"

//=============================================================================
/**
    @file ctimagechannels.h
    @brief Defines the public interface of CTImageChannels
    @ingroup imagechannels_utility
*/
//=============================================================================

/**
    @addtogroup imagechannels_utility
    @brief
    Utility functions for creating and managing image buffers, with the image
    data arranged in separate color buffers/channels.

    @{
*/

//-----------------------------------------------------------------------------

/**
    @brief
    The image channels type supports images with several channels. 
    
    For example CM_YUV422P is a planar format which consist of three channels;
    one for Y, one for U and one for V. However CM_ARGB8888 and CM_AYUV4444 
    are not planar formats and they consist of one channel which holds the 
    entire image.
*/
typedef struct CTImageChannels CTImageChannels;

//-----------------------------------------------------------------------------

/**
    @brief
    Create an image channels object.
    
    @param dims A CTSize which describes the image dimensions.
    @param colorMode The image color mode.
    @param[out] ppImageChs The created image channels object.
 
    @remarks
    Only AYUV4444, ARGB8888 and YUV422P is supported.

    @return
    @c CERR_OK if successful or an appropriate error code on failures.

    @since 3.8.2 R01
 */
SCBIMPORT CRESULT ctimagechannels_create( CTSize dims, 
                                          CTColormode colorMode, 
                                          CTImageChannels **ppImageChs );

//-----------------------------------------------------------------------------

/**
    @brief
    Create an image channels object from images.
    
    @param dims A CTSize which describes the image dimensions
    @param colorMode The image color mode.
    @param pImages An array of CTImageBase types which the image channels will be 
                   created from. Each CTImageBase represent a channel and 
                   the scanline has to be 32-bit aligned. The routine will only 
                   use as many CTImageBase as the color mode implies and 
                   @c CERR_INVALID_PARAMETER will be returned if there is too 
                   few CTImageBase.
    @param[out] ppImageChs The created image channels object.
 
    @remarks
    Only AYUV4444, ARGB8888 and YUV422P is supported.
    The ownership of the pixel data will remain with the caller.

    @return
    @c CERR_OK if successful or an appropriate error code on failures.

    @since 3.8.2 R01
 */
SCBIMPORT CRESULT ctimagechannels_createFromImages( CTSize dims,
                                                    CTColormode colorMode,
                                                    CTImageBase *pImages,
                                                    CTImageChannels **ppImageChs );

//-----------------------------------------------------------------------------

/**
    @brief
    Destroys an image channels object.
    
    @param pImageChs Valid pointer to a CTImageChannels.

    @remarks
    If the CTImageChannels where created with ctimagechannels_createFromImages() 
    the pixel data is not destroyed, the ownership remains with the caller.

    @since 3.8.2 R01
 */
SCBIMPORT void ctimagechannels_destroy( CTImageChannels *pImageChs );

//-----------------------------------------------------------------------------

/**
    @brief
    Get the color mode of the CTImageChannels.
    
    @param pImageChs A valid pointer to a CTImageChannels.
    @param[out] pColorMode A pointer where the color mode will be stored.

    @return
    @c CERR_OK if successful or an appropriate error code on failures.

    @since 3.8.2 R01
 */
SCBIMPORT CRESULT ctimagechannels_getColorMode( CTImageChannels *pImageChs, 
                                                CTColormode *pColorMode );

//-----------------------------------------------------------------------------

/**
    @brief
    Get the image dimension of the CTImageChannels.
    
    @param pImageChs A valid pointer to a CTImageChannels.
    @param[out] pDims A pointer where the dimension will be stored.

    @return
    @c CERR_OK if successful or an appropriate error code on failures.

    @since 3.8.2 R01
 */
SCBIMPORT CRESULT ctimagechannels_getDims( CTImageChannels *pImageChs, CTSize *pDims );

//-----------------------------------------------------------------------------

/**
    @brief
    Get number of channels the CTImageChannels consists of.
    
    @param pImageChs A valid pointer to a CTImageChannels.

    @return The number of channels.

    @since 3.8.2 R01
 */
SCBIMPORT CTuint32 ctimagechannels_getNumChannels( CTImageChannels *pImageChs );

//-----------------------------------------------------------------------------

/**
    @brief
    Get a channel from the CTImageChannels.
    
    @param pImageChs A valid pointer to a CTImageChannels.
    @param channelIndex The index of the channel to return. The index start at 0.
    @param[out] pImage A pointer to CTImageBase which will contain the channel 
                       image information.

    @return
    @c CERR_OK if successful or an appropriate error code on failures.

    @since 3.8.2 R01
 */
SCBIMPORT CRESULT ctimagechannels_getChannel( CTImageChannels *pImageChs, 
                                              CTuint32 channelIndex, 
                                              CTImageBase *pImage );

/** @} */
// end addtogroup 'imagechannels_utility'
//=============================================================================

#ifdef __cplusplus
}      // extern "C"
#endif // __cplusplus
#endif // CTIMAGECHANNELS_H
