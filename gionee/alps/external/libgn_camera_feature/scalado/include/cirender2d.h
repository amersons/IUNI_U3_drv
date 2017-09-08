/* . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
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

#ifndef CIRENDER2D_H
#define CIRENDER2D_H

#include "scbdefs.h"
#include "ctrender2d.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CIRender2D CIRender2D;
    
//==========================================================================
/**
    @file cirender2d.h
    @brief This header defines the interface CIRender2D.
    @ingroup cirender2d
 */
//==========================================================================
/**
    @addtogroup cirender2d
    @brief Interface for 2d rendering primitives.

    @{
 */
//--------------------------------------------------------------------------
/**
    @brief
    Creates a @c CTRender2D object.

    Creates a @c CTRender2D object using the provided interface.

    @param pInterface Pointer to an renderer interface. @sa CIRender2D.

    @param pContext Pointer to user data related to one specific renderer.

    @param pTargetSize The size of the target we are rendering on.

    @param[out] ppRenderer Pointer to a newly created renderer.

    When the renderer object (returned by this function) is no longer needed, it
    should be destroyed using: ctrenderer_destroy()

    @return @c CERR_OK on success.

    @since 5.0
*/
SCBIMPORT CRESULT 
ctrender2d_create ( const CIRender2D *pInterface,
                    void *pContext,
                    CTSize *pTargetSize,
                    CTRender2D **ppRenderer );

//--------------------------------------------------------------------------
/**
    @interface CIRender2D
    @brief Low level renderer interface.

    This interface provides a mean to extend renderer handling to generic types.

    The CIRender2D interface is the virtual low-level renderer interface. To add
    support for a new renderer type, an implementation of this interface must be
    provided. It is the responsibility of the provider of this implementation
    to assure that each function executes the @em proper operation on the
    underlying data (renderer); i.e. @em proper meaning that it exactly match
    the description/behavior specified below.

    @since 5.0
*/
struct CIRender2D
{    
    /**
     @brief Deinit the underlying renderer.
     Releases internal allocations in the context, but not the memory 
     allocated for the context itself.
     
     @param pContext Pointer to user specific data for this render object.
     */
    void (*deinit) ( void *pContext );

    /**
     @brief Draws a textured Quad.

     The texture that is sent to this method must have been reserved by a call to 
     reserveTexture().
              
     @param pContext Pointer to user specific data for this renderer.

     @param pQuad The rectangle, in image coordinates,  where the texture should 
             be drawn.
     @param pTexture The texture to draw.

     @param pTextureCoords The texture coordinates.
     
     @return @c CRESULT
     */
    CRESULT (*drawQuad) ( void *pContext, 
                          CTRect *pQuad, 
                          CTTexture *pTexture, 
                          CTRectf *pTextureCoords );
           
    
    //......................................................................
    /**
     @brief Reserves a texture for the supplied image.

     The image is loaded to the texture for later usage.
     
     @param pContext Pointer to user specific data for this renderer.

     @param pImage The image to load.

     @param pTexture[in,out] The reserved texture where the image is loaded.
     
     @return A @c CRESULT result code.
     */
    CRESULT (*reserveTexture) ( void *pContext, 
                                CTImage *pImage, 
                                CTTexture *pTexture );
    
    //......................................................................
    /**
     @brief Releases a previously reserved texture.
     
     @param pContext Pointer to user specific data for this renderer.

     @param pTexture The texture to release.
     
     @return A @c CRESULT result code.
     */
    CRESULT (*releaseTexture)( void *pContext, CTTexture *pTexture );
    //......................................................................
    
    /**
     @brief returns the size of the texture struct for the renderer.
     
     @param pContext Pointer to user specific data for this render object.

     @return the texture struct size.
     */
    CTuint32 (*textureSize) ( void *pContext );

    /**
     @brief returns the color format used by the renderer.
     
     @param pContext Pointer to user specific data for this render object.

     @return the color format.
     */
    CTColormode (*colorMode) ( void *pContext );

    /**
        @brief Sets the modelview matrix.

        Replaces the current modelview matrix with the provided matrix.

        @param pContext Pointer to user specific data for this render object.

        @param pMatrix Pointer to 16 consecutive values that are used as the elements of a		    
		4x4 column-major matrix.

        @return A @c CRESULT result code.
    */
    CRESULT (*setModelMatrix)(  void *pContext, CTfloat *pMatrix );

    /**
        @brief Performs preparations needed before the rendering.

        This method is called once for each rendering pass. The method is called 
        prior to the first drawQuad call. If you need to apply the model matrix prior
        to the drawQuad calls this is the place to do it.

        @param pContext Pointer to user specific data for this render object.
    */
    void (*beginRender) ( void *pContext );

    /**
        @brief Performs post operations needed after the rendering.

        This method is called once for each rendering pass. The method is called 
        after the last drawQuad call.

        @param pContext Pointer to user specific data for this render object.
    */
    void (*endRender) ( void *pContext );
};
// end of 'struct CIRender2D'
//-----------------------------------------------------------------------------
/**
 @}
 */ // end of addtogroup 'cirender2d'
//-----------------------------------------------------------------------------
    
#ifdef __cplusplus
} // extern "C"
#endif

#endif
