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

#ifndef CTDECODER_H
#define CTDECODER_H

#include "scbdefs.h"
#include "ctregiondec.h"
#include "ctseqdec.h"
#include "ctinterfaceid.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
/**
    @file ctdecoder.h
    @brief This file defines the public interface of CTDecoder class.

    @ingroup ctdecoder
*/
//==============================================================================

/**
    @addtogroup ctdecoder
    @brief CTDecoder provides an abstraction of decoding image data and
    properties.

    The CTDecoder class itself is responsible only for decoding image metadata,
    such as the header, and creating a CTRegionDec or CTSeqDec which can decode
    pixel data from the image.

    @{
*/
//------------------------------------------------------------------------------

/**
    @brief
    CTDecoder provides a generic image decoding interface. 
*/
typedef struct CTDecoder CTDecoder;


/**
    @brief
    Destroys an instance of a CTDecoder.

    @param pDecoder A pointer to a valid decoder instance or NULL.

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctdecoder_destroy(CTDecoder *pDecoder);

/**
    @brief
    Parses the header. 
    
    The iterator returned by this function must be iterated until a 
    CRES_TASK_COMPLETE is returned before most other operations on the decoder
    object can be called.

    @param pDecoder
    A pointer to a valid decoder instance.

    @param[out] ppIterator
    Iterator created by the call to this function. If left as null, the 
    call will complete instantly.

    @return @c CERR_OK if successful or a specific error code upon failure.

    @remarks The iterator must be destroyed by the caller.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctdecoder_parseHeader(CTDecoder *pDecoder, 
                      CTIterator **ppIterator);

/**
    @brief
    Returns a sequential decoder.

    This functions creates an instance of a sequential decoder and returns
    it to the caller. The caller will be responsible for destroying this object.
    Before calling this function, the decoder must be parsed.

    @param pDecoder A pointer to a valid decoder instance.
    @param pImage An image on which the image will be decoded.
    @param[out] ppSeqDec A pointer to a valid sequential decoder instance.

    @return 
    @c CERR_OK if successful, or an error code on failure.
    @c CERR_NOT_IMPLEMENTED if this operation is not supported.
    @c CERR_DECODER_NOT_PARSED if the decoder has not yet been parsed.
    @c CERR_UNSUPPORTED_COLOR_MODE if the image has an unsupported color mode.

    @sa ctseqdec.h

    @since 5.2
*/
SCBIMPORT CRESULT 
ctdecoder_getSeqDec(CTDecoder *pDecoder, 
                    CTImage *pImage,
                    CTSeqDec **ppSeqDec);
    
/**
    @brief
    Returns a sequential decoder.
     
    This functions creates an instance of a sequential decoder and returns
    it to the caller. The caller will be responsible for destroying this object.
    Before calling this function, the decoder must be parsed.
     
    @param pDecoder A pointer to a valid decoder instance.
    @param pScanProc The scanline processor to be used with this decoder.
    @param[out] ppSeqDec A pointer to a valid sequential decoder instance.
     
    @return 
    @c CERR_OK if successful, or an error code on failure.
    @c CERR_NOT_IMPLEMENTED if this operation is not supported.
    @c CERR_DECODER_NOT_PARSED if the decoder has not yet been parsed.

    @sa ctseqdec.h

    @since 3.8.2
*/
SCBIMPORT CRESULT 
ctdecoder_getSeqDecWithScanProc(CTDecoder *pDecoder, 
                                CTScanProc *pScanProc,
                                CTSeqDec **ppSeqDec);
    

/**
    @brief
    Returns a region decoder.

    This functions creates an instance of a region decoder and returns it to 
    the caller. The caller will be responsible of destroying this object.
    Before calling this function, the decoder must be parsed.
 
    @param pDecoder A pointer to a valid decoder instance.
    @param[out] ppRegionDec The created region decoder.

    @return 
    @c CERR_OK if successful, or an error code on failure.
    @c CERR_NOT_IMPLEMENTED if this operation is not supported.
    @c CERR_DECODER_NOT_PARSED if the decoder has not yet been parsed.

    @sa ctregiondec.h

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctdecoder_getRegionDec(CTDecoder *pDecoder,
                       CTRegionDec **ppRegionDec);

/**
    @brief
    Returns the interface context related to the interface id.

    The caller is responsible for knowing the exact type returned
    by a call to this function.

    @param pDecoder Decoder to use for this call.
    @param interfaceId Interface id to query for a context.
    @param[out] ppInterfaceContext Pointer to the returned context. The 
    caller does not own the reference, and so must not attempt to free
    it.

    @return 
    @c CERR_OK if successful, or an error code on failure.
    @c CERR_NOT_IMPLEMENTED if this operation is not implemented by the
    decoder implementation.
    @c CERR_INVALID_PARAMETER if the particular requested interface is not
    available.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctdecoder_interfaceContext(CTDecoder *pDecoder, 
                           CTInterfaceID interfaceId, 
                           void **ppInterfaceContext);

/**
    @brief
    Retrieves the image size of the underlying image.

    @param pDecoder Decoder to use for this call.
    @param[out] pSize Pointer to a CTSize where the result is stored.

    @return 
    @c CERR_OK if successful, or an error code on failure.
    @c CERR_DECODER_NOT_PARSED if the decoder has not yet been parsed.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctdecoder_getImageSize(CTDecoder *pDecoder, CTSize *pSize);

//==============================================================================
/** @} */
// end addtogroup ctdecoder


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // CTDECODER_H
