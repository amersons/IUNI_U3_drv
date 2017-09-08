/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    Copyright (c) 2000-2010 Scalado AB. All rights reserved.                 .
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
#ifndef CTRENDER2D_OPENGL_H
#define CTRENDER2D_OPENGL_H

#include "ctrender2d.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
    @addtogroup ctrender2d_opengl
    @brief An implementation of @ref ctrender2d using OpenGL ES 1.1
    @{
*/

/**
    @brief
    Creates a new @c CTRender2D object that implements the ::CIRender2D interface
    (see @ref cirender2d). The renderer uses OpenGL ES 1.1 to do the rendering to
    screen. A valid OpenGL contex must be active on the current thread before this
    method is called.
    
    The OpenGL context is missing as a parameter to this call because the OpenGL
    context is globally accessible on this thread. This function must not be 
    called before the OpenGL context has been set up.
    
    This function call will not set up windows, drawing surfaces, or anything
    else needed to do OpenGL rendering. It assumes that all those steps have
    already been performed prior to calling.
    
    All rendering performed by this object will be passed on to the target set 
    up by the OpenGL context.
    
    @param pScreenSize The size of the target we are rendering on.

    @param[out] ppRenderer Pointer to a newly created renderer.

    @return @c CERR_OK on success.
*/
CRESULT ctrender2d_createForOpenGL( CTSize *pScreenSize, CTRender2D **ppRenderer );


/**@} */
// end addtogroup 'ctrender2d_opengl'


#ifdef __cplusplus
} // extern "C"
#endif

#endif
