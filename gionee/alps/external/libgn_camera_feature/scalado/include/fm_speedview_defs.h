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

#ifndef FM_SPEEDVIEW_DEFS_H
#define FM_SPEEDVIEW_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"

//=============================================================================
/**
    @ingroup fm_speedview_api
    @file fm_speedview_defs.h
    @brief Speedview defines and typedefs: @a SpeedView
*/
//=============================================================================
/**
    @addtogroup fm_speedview_api
    @{
*/
//-----------------------------------------------------------------------------

/**
    @brief Handle to Speedview object
*/
typedef struct CTSpmo CTSpmo;
//-----------------------------------------------------------------------------
/**
    @brief Handle to Speedview options object
*/
typedef struct CTSpmoOptions CTSpmoOptions;
//-----------------------------------------------------------------------------
typedef struct CTCreateSpmoSession CTCreateSpmoSession;
//-----------------------------------------------------------------------------
/**
    @brief Available VERIFICATION modes for SPMO objects.
*/
typedef enum 
{
    /**
        @brief No verification will be used to ensure coherent data.

        This option could be used if the user is absolutely sure that the image
        haven't been altered since the Spmo was created.
    */
    SPMO_VERIFICATION_MODE_DISABLED     = 0x00,
    
    /**
        @brief A fast verification mode, which will be sufficient for most cases.
    */
    SPMO_VERIFICATION_MODE_ENABLED  = 0x01

} SPMO_VERIFICATION_MODE;

/**
    @brief Spmo index mode.
*/
typedef enum
{
    SPMO_NO_INDEX = 0,  ///< No index.
    SPMO_INDEXED  = 10  ///< Full index.
} CTSpmoMode;

/** @} */
// 'fm_speedview_defs'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_SPEEDVIEW_DEFS_H )
