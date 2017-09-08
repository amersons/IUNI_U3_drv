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

#ifndef CISEQDEC_H
#define CISEQDEC_H

#include "scbdefs.h"
#include "caps_iterator.h"
#include "ctseqdec.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
/**
    @file ciseqdec.h
    @brief This file contains the interface for a sequential decoder.
    @ingroup ciseqdecoder
*/
//==============================================================================

/**
    @addtogroup ciseqdecoder
    @brief
    The CISeqDec defines the interface to be used when decoding pixel 
    data from some pixel source in a sequential manner (normally top to bottom,
    left to right).

    @{
*/
//------------------------------------------------------------------------------

/**
    @interface CISeqDec
    @brief
    Sequential Decoder.

    This object provides the interface to sequential decoding of images.

    The images will be decoded in a scanline per scanline basis, and the
    result of the decoding will be sent to a scanline processor, that will
    perform some operation with the pixel data ( such as render it to screen ).
*/
typedef struct
{

    /**
        @brief
        Deinitialize  the sequential decoder context.

        @param pDecoder A pointer to a valid sequential decoder.

    */
    void (*deinit)( CTSeqDec *pDecoder );

    /**
        @brief
        Starts the decoding process, and returns an iterator that can
        be used to perform the decoding.

        @param pDecoder A pointer to a valid sequential decoder.
        @param pScanProc A pointer to a valid scanline processor instance.
        @param ppIterator[out] A pointer to an iterator to be used for performing the decoding.

        @return CERR_OK or a proper error code.

    */
    CRESULT (*decode)( CTSeqDec *pDecoder,
                       CTScanProc *pScanProc,
                       CTIterator **ppIterator );

} CISeqDec;

//------------------------------------------------------------------------------

/**
    @brief
    Creates a sequential decoder.

    This function is normally used in the specific constructor of the
    decoder implementing the interface.

    @param pInterface    A pointer to a valid sequential decoder interface.
    @param sizeOfContext Size of the context to be created.
    @param pScanProc     Scan processor to use for this sequential decoder.
    @param[out] ppSeqDec A pointer to the created sequential decoder.

    @return CERR_OK or a proper error code.

    @remarks
    The context has to be initialized by the caller and can be 
    retrieved by ctseqdec_context(). 
    The context must be compatible with this sequential decoder. Some 
    implementations choose to use the main decoder context for the
    sequential decoding context as well. In that case, destroy must
    not dispose of the memory passed in pContext.

    @since 3.8.2 R02
*/
CRESULT ctseqdec_create( const CISeqDec *pInterface,
                         CTuint32 sizeOfContext,
                         CTScanProc *pScanProc,
                         CTSeqDec **ppSeqDec );

/**
    @brief
    Retrieves the sequential decoder context allocated in ctseqdec_create().
    
    @param pDecoder A pointer to a valid reference of an sequential decoder.
    
    @return The interface context for the sequential decoder object, or NULL if the
    decoder is invalid.

    @since 3.8.2 R02
*/
void* ctseqdec_context( CTSeqDec *pDecoder );

//==============================================================================
/** @} */
// end addtogroup ciseqdecoder


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif // CISEQDEC_H
