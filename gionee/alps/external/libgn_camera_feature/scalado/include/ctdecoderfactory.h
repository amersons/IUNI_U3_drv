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

#ifndef CTDECODERFACTORY_H
#define CTDECODERFACTORY_H

#include "scbdefs.h"
#include "ctstream.h"
#include "ctdecoder.h"
#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
/**
    @file ctdecoderfactory.h
    @brief This header file defines the public interface of the CTDecoderFactory
    class.
    @ingroup ctdecoderfactory
*/
//==============================================================================

/**
    @addtogroup ctdecoderfactory
    @brief The CTDecoderFactory defines a common interface for detecting the image
    type and for creating an appropriate decoder for the detected image type.
    
    A typical implementation of a CTDecoderFactory can, for instance, determine
    whether a stream is suitable for a jpeg decoder and to create that decoder
    once a stream is determined to be suitable.

    Using this interface makes it possible to use a single interface for 
    creating decoders with different constructor signatures.

    @{
*/
//------------------------------------------------------------------------------

/**
    CTDecoderFactory provides an interface to creating decoders.

*/
typedef struct CTDecoderFactory CTDecoderFactory;

/**
    Tries to check whether the decoder factory can create a suitable
    decoder for the provided stream.

    @param pFactory
    Factory instance to query.

    @param pStream
    Input stream to check.

    @param[out] pCanParse
    Pointer to the response of the query.

    @returns
    @c CERR_OK if successful, or an error code on failure.
    @c CERR_NOT_IMPLEMENTED if the operation is not implemented.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctdecoderfactory_canParse( CTDecoderFactory *pFactory, 
                           CTStream *pStream, 
                           CTbool *pCanParse );

/**
    @brief
    Creates a decoder attached to the provided stream.

    After a call to this function, the decoder is considered to be owning 
    the stream until the decoder is destroyed. Decoder destruction will 
    not automatically release resources associated with the stream, and 
    this will remain the callers responsibility.

    @param pFactory
    Factory instance to use for the decoder creation.

    @param pStream 
    Input stream to connect to the decoder.

    @param[out] ppDecoder
    The created decoder object.

    @returns
    @c CERR_OK if successful or a suitable error code if an error occurred.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT
ctdecoderfactory_createDecoder( CTDecoderFactory *pFactory, 
                                CTStream *pStream, 
                                CTDecoder **ppDecoder );

/**
    Destroys an instance of a decoder factory.

    @param pFactory Decoder factory to destroy.

    @since 3.8.2 R01
*/
SCBIMPORT void 
ctdecoderfactory_destroy( CTDecoderFactory *pFactory );

//==============================================================================
/** @} */
// end addtogroup ctdecoderfactory

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // CTDECODERFACTORY_H
