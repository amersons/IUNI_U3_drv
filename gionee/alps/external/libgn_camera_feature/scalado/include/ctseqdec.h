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

#ifndef CTSEQDEC_H
#define CTSEQDEC_H

#include "scbdefs.h"
#include "caps_iterator.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
/**
    @file ctseqdec.h
    @brief This header file defines the interface needed to access a CTSeqDec
    object.
    @ingroup ctseqdecoder
*/
//==============================================================================

/**
    @addtogroup ctseqdecoder
    @brief The CTSeqDec class defines an interface to access sequantial decoding
    of pixel data.

    While this is normally aquired from a CTDecoder source using the specific
    interface for requesting pixel decoders, this is not necessarily the case.

    @{
*/
//------------------------------------------------------------------------------

typedef struct CTSeqDec CTSeqDec;
typedef struct CTScanProc CTScanProc;

/**
    @brief
    Destroys a sequential decoder instance.

    @param pDecoder A pointer to the decoder to be destroyed.

    @since 3.8.2 R01
*/
void ctseqdec_destroy( CTSeqDec *pDecoder );

//------------------------------------------------------------------------------

/**
    @brief
    Starts the decoding process, and returns an iterator that can
    be used to perform the decoding.

    @param pDecoder A decoder instance to decode from.
    @param[out] ppIterator A pointer to an iterator to be used for performing
    the decoding.

    @return CERR_OK or a proper error code.

    @since 3.8.2 R01
*/
CRESULT ctseqdec_decode( CTSeqDec *pDecoder,
                         CTIterator **ppIterator );

//==============================================================================
/** @} */
// end addtogroup ctseqdecoder


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // CTSEQDEC_H
