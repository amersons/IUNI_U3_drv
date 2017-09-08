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

#ifndef CTSPMODECODER_H
#define CTSPMODECODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ctdecoderfactory.h"
#include "fm_speedview.h"

/**
    @brief
    Creates a factory capable of producing spmo decoders.

    @param[out] ppFactory
    Pointer to a reference to the factory.

    @return
    @c CERR_OK or a specific error code on failure.

    @since 3.9
*/
CRESULT ctspmodecoder_createDecoderFactory( CTDecoderFactory **ppFactory );

/**
    @brief
    Creates a CTDecoder from a CTSpmo

    @param[out] ppDecoder
    Pointer to a reference to the decoder.

    @param pSpmo Spmo object. Must be alive during the lifetime of the decoder.

    @return
    @c CERR_OK or a specific error code on failure.

    @since 3.9
*/
CRESULT ctspmodecoder_create( CTSpmo *pSpmo, CTDecoder **ppDecoder );


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // CTSPMODECODER_H
