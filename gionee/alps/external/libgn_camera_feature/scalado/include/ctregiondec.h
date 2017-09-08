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

#ifndef CTREGIONDEC_H
#define CTREGIONDEC_H

#include "scbdefs.h"
#include "caps_iterator.h"
#include "ctimagechannels.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
/**
    @file ctregiondec.h
    @brief This file defines the interface to a CTRegionDec.
    @ingroup ctregiondecoder
*/
//==============================================================================

/**
    @addtogroup ctregiondecoder
    @brief A region decoder object, CTRegionDec, is responsible for decoding
    pixel data from a generic pixel source.

    This pixel data can be any rectangular subset of the original image, so a
    decoder supporting this interface can be used to "random access" pixels of
    the image.
    
    Normally this pixel source comes from a decoder (and the CTRegionDec is 
    created by using the CTDecoder function for that purpose) but this is not 
    necessarily the case.

    @{
*/
//------------------------------------------------------------------------------

/**
    @brief The region decoder object.
*/
typedef struct CTRegionDec CTRegionDec;

//------------------------------------------------------------------------------
/**
    @brief
    Prepares the region decoder to decode pixel data.

    @param pRegionDec
    Decoder to prepare for decoding.

    @param[out] ppIterator
    Iterator to use for preparing the decoder. If left as null, the operation 
    will complete instantly.

    @return
    @c CERR_OK if successful or an appropriate error code on failures.

    @remarks
    Even if the image is corrupt, this function should return CERR_OK, as long as
    the image can be decoded using ctregiondec_decodeRegion(). If the image is corrupt
    but can be decoded, an appropriate error specification should be given in
    ctregiondec_getDecodeResult().

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT ctregiondec_prepare( CTRegionDec *pRegionDec, 
                                       CTIterator **ppIterator );

//------------------------------------------------------------------------------
/**
    @brief
    Decodes a region of the image.

    @param pRegionDec A pointer to a valid CTRegionDec instance.
    @param pRect A pointer to a valid rectangle object.
    @param downScale A downscaling factor less or equal to 128. 
                     It must be a power.
    @param pImageChs A pointer to a valid image object.

    @remarks
    Only AYUV4444 and ARGB8888 supported.

    @return
    @c CERR_OK if successful or an appropriate error code on failures.

    @since 3.8.2 R01
 */
SCBIMPORT CRESULT ctregiondec_decodeRegion( CTRegionDec *pRegionDec, 
                                            CTRect *pRect, 
                                            CTuint32 downScale, 
                                            CTImageChannels *pImageChs );

//------------------------------------------------------------------------------
/**
    @brief
    Destroys the region decoder.

    @param pRegionDec A pointer to a valid CTRegionDec instance, or NULL.

    @since 3.8.2 R01
*/
SCBIMPORT void ctregiondec_destroy ( CTRegionDec *pRegionDec );

//------------------------------------------------------------------------------
/**
    @brief
    Retrieves the result of decoding the image.

    Typically, this call indicates whether the image was correctly decoded or 
    if the image could only be partially decoded.

    @param pRegionDec Region decoder to query.
    @param pDecodeResult Result of the decoding process

    @return CRESULT indicating whether the decoder could be queried for
    decoding state.

    @remarks
    This function is normally called after prepare has completed successfully.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT ctregiondec_getDecodeResult( CTRegionDec *pRegionDec, 
                                               CRESULT *pDecodeResult );

//------------------------------------------------------------------------------
/**
    @brief
    Retrieves the image size of the underlying image.

    @param pRegionDec Region decoder
    @param[out] pSize Pointer to a CTSize where the result is stored.

    @return 
    @c CERR_OK if successful, or an error code on failure.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT ctregiondec_getImageSize( CTRegionDec *pRegionDec, 
                                            CTSize *pSize );

//==============================================================================
/** @} */
// end addtogroup ctregiondecoder

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif // CTREGIONDEC_H
