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

#ifndef CIDECODER_H
#define CIDECODER_H

#include "scbdefs.h"
#include "ctdecoder.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
/**
    @file cidecoder.h
    @brief This files describes the public interface of a generic decoder.
    @ingroup cidecoder
*/
//==============================================================================

/**
    @addtogroup cidecoder
    @brief The CIDecoder interface enables construction of CTDecoder objects
    to decode the image header of some format, and to create a decoder for
    decoding pixel data.

    @{
*/
//------------------------------------------------------------------------------

/**
    @interface CIDecoder
    @brief
    Decoder Interface.
 
    Defines the internal interface of the CTDecoder. A customized decoder 
    (derived from CTDecoder) must provide an implementation of this interface.
 
    The interface supports both sequential and region decoding,
    whereas they are both optional.

    The interface is fully copied on object construction, and decoders 
    may thus be created dynamically to suit a particular factory need.
 */
typedef struct
{
    /**
        @brief
        Releases internal allocations in the context, but not the memory 
        allocated for the context itself.

        @param pDecoder A pointer to a valid decoder.

        @remarks
        If the context is null, no action must be taken.

    */
    void (*deinit)( CTDecoder *pDecoder );

    /**
        @brief
        Parses the stream to read header information.

        @param pDecoder A pointer to a valid reference of an decoder to parse.
        @param[out] ppIterator Reference to an iterator pointer to return
        to the caller.

        @return
        @c CERR_OK if successful, or an appropriate error code if not.

        @remarks
        Unlike most iterators, the ppIterator argument to this function is not
        optional.

    */
    CRESULT (*parse)( CTDecoder *pDecoder, CTIterator **ppIterator );

    /**
        @brief
        A sequential decoder factory interface.

        This interface is used to create sequential decoders. A decoder can only
        be created after the decoder has been parsed.

        @param pDecoder A pointer to a valid reference of an decoder.
        @param pScanProc Scan processor to connect to the sequential decoder.
        @param[out] ppSeqDec Pointer to a pointer to hold the sequential decoder.

        @return
        @c CERR_OK if successful, or an appropriate error code if not.
        @c CERR_DECODER_NOT_PARSED if the decoder has not yet been parsed.

        @remarks
        This interface is optional and may be left as null.

    */
    CRESULT (*createSeqDec)( CTDecoder *pDecoder, 
                             CTScanProc *pScanProc, 
                             CTSeqDec **ppSeqDec );

    /**
        @brief
        A region decoder factory function.

        This method is used to create a region decoder for pixel data from this
        ctdecoder. The decoder must be parsed before a pixel decoder can be created.

        @param pDecoder A pointer to a valid reference of an decoder.
        @param[out] ppDecoder The created region pixel decoder.

        @return 
        @c CERR_OK if successful or an error code if the call failed.
        @c CERR_DECODER_NOT_PARSED if the decoder has not yet been parsed.

    */
    CRESULT (*createRegionDec)( CTDecoder *pDecoder, CTRegionDec **ppDecoder );

    /**
        @brief
        Returns the interface context related to the interface id.

        This interface is implementation specific and the caller is responsible 
        for casting the returned pointer to the correct type.

        This operation may be thought of as upcasting an interface.

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

        @remarks This method is optional to implement. If not implemented, it 
        will return an appropriate error code.

    */
    CRESULT (*interfaceContext)( CTDecoder *pDecoder, 
                                 CTInterfaceID interfaceId, 
                                 void **ppInterfaceContext);

    /**
        @brief
        Retrieves the image size of the underlying image.

        @param pDecoder A pointer to a valid reference of an decoder.
        @param[out] pSize Pointer to a CTSize where the result is stored.

        @return 
        @c CERR_OK if successful, or an error code on failure.
        @c CERR_DECODER_NOT_PARSED if the decoder has not yet been parsed.

    */
    CRESULT (*getImageSize)( CTDecoder *pDecoder, CTSize *pSize );

} CIDecoder;

//------------------------------------------------------------------------------

/**
    @brief Creates a decoder and user context for a given interface.

    @param pInterface A valid implementation of the CIDecoder interface.
    @param sizeOfContext Size of the context to be created.
    @param[out] ppDecoder Pointer to the decoder reference to be created.

    @remarks The context has to be initialized by the caller and can be 
    retrieved by ctdecoder_context().

    @return
    @c CERR_OK if successful or an error code on failure.

    @since 3.8.2 R02
*/
SCBIMPORT CRESULT ctdecoder_create( const CIDecoder *pInterface,
                                    CTuint32 sizeOfContext, 
                                    CTDecoder **ppDecoder );

/**
    @brief
    Retrieves the decoder context allocated in ctdecoder_create().
    
    @param pDecoder A pointer to a valid reference of an decoder.
    
    @return The interface context for the decoder object, or NULL if the
    decoder is invalid.

    @since 3.8.2 R02
*/
SCBIMPORT void *ctdecoder_context( CTDecoder *pDecoder );

//==============================================================================
/** @} */
// end addtogroup cidecoder


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif // CIDECODER_H
