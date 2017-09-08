/*****************************************************************************
 * © 2000-2009 Scalado AB. All rights reserved.                              *
 *                                                                           *
 * Technologies used in this source code are patented or patent pending      *
 * by Scalado AB Swedish Org. Number, 556594-6885.                           *
 *                                                                           *
 * All Intellectual Property Rights related to this source code,             *
 * belongs to Scalado AB.                                                    *
 *                                                                           *
 * This source code is furnished under license agreement and may be used     *
 * or copied only in accordance with terms of such license agreement.        *
 *                                                                           *
 * Except as permitted by such license agreement, no part of this source     *
 * code may be reproduced, stored in a retrieval system, or transmitted,     *
 * in any form or by any means, electronic, mechanical, recording, or        *
 * otherwise, without the prior written permission of Scalado.               *
 *                                                                           *
 * Scalado assumes no responsibility or liability for any errors or          *
 * inaccuracies in this source code or any consequential, incidental or      *
 * indirect damage arising out of the use of this source code.               *
 *                                                                           *
 * Scalado and the Scalado logo are either registered trademarks or          *
 * trademarks of Scalado AB in Sweden and/or other countries.                *
 *                                                                           *
 *****************************************************************************/

#ifndef OSLCLOCK_H
#define OSLCLOCK_H

#include "scbdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/** 
    @ingroup os_clock
    @file oslclock.h
    @brief
    Declares the virtual interface providing support for time management.
*/
//=============================================================================
/** 
    @addtogroup os_clock

    @brief
    Mapping of basic OS clock functionality.

    These function declarations are found in the header file: oslclock.h
    
    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief
    Returns the numer of milliseconds that has passed since a fixed point in
    time.
*/
CTuint32 oslclock_getMilliseconds( void );

//-----------------------------------------------------------------------------

/** @} */
// end addtogroup 'os_clock'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif // OSLCLOCK_H
