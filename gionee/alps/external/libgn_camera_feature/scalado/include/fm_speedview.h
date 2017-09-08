/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    � 2000-2009 Scalado AB. All rights reserved.                             .
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

#ifndef FM_SPEEDVIEW_H
#define FM_SPEEDVIEW_H

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @ingroup fm_speedview_api
    @file fm_speedview.h
    @brief Defines the interface of the Caps Feature Module: @a SpeedView
*/
//=============================================================================
/**
    @addtogroup fm_speedview
    @deprecated This interface is deprecated since 5.3.
    @brief SPMO handling
    @{
        @defgroup fm_speedview_api Speedview API
        @defgroup fm_speedview_animation Animation API
        */
/** @} */
//-----------------------------------------------------------------------------
/**
    @addtogroup fm_speedview_api
    @brief Creation, utilization and management of SPMO
    @deprecated This interface is deprecated since 5.3.
*/
//-----------------------------------------------------------------------------

#include "fm_speedview_defs.h"
#include "fm_speedview_spmo.h"
#include "fm_speedview_animation.h"
#include "fm_speedview_session.h"

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_SPEEDVIEW_H )
