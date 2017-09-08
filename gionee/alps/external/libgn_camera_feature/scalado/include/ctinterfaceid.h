/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    © 2000-2010 Scalado AB. All rights reserved.                             .
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

#ifndef CTINTERFACEID_H
#define CTINTERFACEID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"


/**
    @brief
    Id of an interface, used in interface based designs.
*/
typedef struct CTInterfaceID
{
    const DCHAR * pName;    ///< Interface identifier.
} CTInterfaceID;

#define CTINTERFACEID_DEFINE( interfaceId ) \
    const CTInterfaceID interfaceId = { _D(#interfaceId) }

#define CTINTERFACEID_DECLARE( interfaceId ) \
    extern const CTInterfaceID interfaceId

/**
    @brief
    Test two CTInterfaceID objects for equality.

    @param id1
    An interface id.

    @param id2
    Another interface id.

    @return true iff the two interface ids are equal.

    @since 3.8.2 R01
*/
CTbool ctinterfaceid_equals( CTInterfaceID id1, CTInterfaceID id2 );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CTINTERFACEID_H
