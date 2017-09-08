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

#ifndef CTRENDER2D_H
#define CTRENDER2D_H

#include "scbdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

//==========================================================================
/**
    @file ctrender2d.h
    @brief This header defines the public interface for CTRender2D.
    @ingroup ctrender2d
*/
//==========================================================================
/**
    @addtogroup ctrender2d
    @brief The render object is responsible for allocation, reservation
    and destruction of textures, image rendering and substituion of transform
    matrix.

    @{
*/
//--------------------------------------------------------------------------
/**
    @brief Type representing CTRender2D objects.
*/
typedef struct CTRender2D CTRender2D;

//--------------------------------------------------------------------------
/**
    @brief Type representing CTTexture objects.
*/
typedef struct CTTexture CTTexture;

//--------------------------------------------------------------------------
/**
    @brief Destroys the underlying renderer.

    Releases internal allocations in the CTRender2D object, and the render
    object itself.

    @param pRenderer Pointer to CTRender2D object.
*/
void ctrender2d_destroy( CTRender2D *pRenderer );

//--------------------------------------------------------------------------
/**
    @brief Reserves a texture and loads the supplied image to the texture.

    @param pRenderer A valid pointer to a CTRender2D object.

    @param pImage The image to load.

    @param[in,out] pTexture The reserved texture where the image is loaded.

    @return A @c CERR_OK on success, or specific error code on failure.
*/
CRESULT ctrender2d_loadTexture( CTRender2D *pRenderer, 
                                CTImage *pImage, 
                                CTTexture *pTexture );

//--------------------------------------------------------------------------
/**
    @brief Releases a previously reserved texture.

    @param pRenderer A valid pointer to a CTRender2D object.

    @param pTexture The texture to release.

    @return A @c CERR_OK on success, or specific error code on failure.
*/
CRESULT ctrender2d_freeTexture( CTRender2D *pRenderer, CTTexture *pTexture );

//--------------------------------------------------------------------------
/**
    @brief Draws a textured Quad.

    The texture that is sent to this method must have been reserved by a call
    to ctrender2d_loadTexture().

    @param pRenderer A valid pointer to a CTRender2D object.

    @param pQuad The rectangle, in image coordinates, where the texture
    should be drawn.

    @param pTexture The texture to draw.

    @param pTextCoords The texture coordinates.

    @return @c CERR_OK on success, or specific error code on failure.
*/
CRESULT ctrender2d_drawQuad( CTRender2D *pRenderer, 
                             CTRect *pQuad, 
                             CTTexture *pTexture,
                             CTRectf *pTextCoords );

//--------------------------------------------------------------------------
/**
    @brief Returns the size of the texture struct for the renderer.

    @param pRenderer A valid pointer to a CTRender2D object.

    @return The texture struct size.
*/
CTuint32 ctrender2d_textureSize( CTRender2D *pRenderer );

//--------------------------------------------------------------------------
/**
    @brief Returns the color format used by the renderer.

    @param pRenderer A valid pointer to a CTRender2D object.

    @return The color format.
*/
CTColormode ctrender2d_colorMode( CTRender2D *pRenderer );

//--------------------------------------------------------------------------
/**
    @brief Sets the modelview matrix.

    Replaces the current modelview matrix with the provided matrix.

    @param pRenderer A valid pointer to a CTRender2D object.

    @param pMatrix Pointer to 16 consecutive values that are used as the elements of a		    
	               4x4 column-major matrix.

    @return A @c CERR_OK on success, or specific error code on failure.
*/
CRESULT ctrender2d_setModelMatrix( CTRender2D *pRenderer, CTfloat *pMatrix );

//--------------------------------------------------------------------------
/**
    @brief Returns the size of renderer object target.

    @param pRenderer A valid pointer to a CTRender2D object.
   
    @return A size of the target.
*/
CTSize ctrender2d_getTargetSize( CTRender2D *pRenderer );

//--------------------------------------------------------------------------
/**
    @brief Performs preparations needed before the rendering.

    This method is called once for each rendering pass. The method is called 
    prior to the first drawQuad call. 

    @param pRenderer A valid pointer to a CTRender2D object.
*/
void ctrender2d_beginRender( CTRender2D *pRenderer );

//--------------------------------------------------------------------------
/**
    @brief Performs post operations needed after the rendering.

    This method is called once for each rendering pass. The method is called 
    after the last drawQuad call.

    @param pRenderer A valid pointer to a CTRender2D object.
*/
void ctrender2d_endRender( CTRender2D *pRenderer );

//-----------------------------------------------------------------------------
/** @} */
// end of addtogroup 'scb_ctrender2d'

#ifdef __cplusplus
} // extern "C"
#endif


#endif // CTRENDER2D_H

