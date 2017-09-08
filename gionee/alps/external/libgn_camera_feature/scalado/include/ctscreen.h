/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    Copyright (c) 2000-2011 Scalado AB. All rights reserved.                 .
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

#ifndef CTSCREEN_H
#define CTSCREEN_H

#include "scbdefs.h"
#include "ctdecoder.h"
#include "ctrender2d.h"
#include "ctviewport.h"
#include "cttexturecache.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @file ctscreen.h
    @brief This header defines the public interface of the CTScreen2 object.
    @ingroup ctscreen2
*/
//=============================================================================
/**
    @addtogroup ctscreen2
    @brief The @c CTScreen2 object is a tile based image renderer capable of
    utilizing hardware accelerated rendering support (e.g. OpenGL).

    The @c CTScreen2 object performs a tile based rendering. It renders only those
    tiles that are visible within a screen's current viewport. Tiles are rendered
    to the target (display) from a tile cache. Image data associated with the tiles
    are decoded and added to the the tile cache, whenever the iterator, returned
    from ctscreen2_preRender(), is run; i.e. whenever caps_doNextIteration() is
    called. In order to quickly display a complete image, tiles from a downscaled
    version of the image are first rendered. When continuously running the iterator,
    higher resolution tiles will be rendered until optimal quality has been reached,
    and the iterator terminates.
    
    The @ref ctrender2d object, provided to a CTScreen2 object via texture cache,
    is completely responsible for drawing the content of the viewport.
    This means that it has to encapsulate all parts of the rendering, such as the
    display surface, any OpenGL context or other needed resources. Note that OpenGL
    encapsualtes its own context in the current thread, so for OpenGL rendering,
    the rendering object will contain no additional state beyond itself.
    
    The @ref ctviewport object is used to point the screen to a proper viewing area,
    and to make it easy to specify this area without using matrix transformations.

    The purpose of the split of the architecture into these three major components
    is to clearly separate rendering, coordinate specification and decoding from 
    each other. This allows custom implementations to override, or alter, the
    behavior without affecting other parts of the system.

    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief Type representing CTScreen2 objects.
*/
typedef struct CTScreen2 CTScreen2;

                     
//-----------------------------------------------------------------------------
/**
    @brief Creates a screen object with cache and tile settings.

    @param pTileDims
    The size of the tiles used when rendering the screen.
    @n
    The valid range depends on the renderer used and the platform, but minimum
    dimensions are 64x64, and maximum dimensions are 2048x2048.

    @param pDecoder
    A decoder that delivers image data to this screen.

    @param pTextureCache
    A texture cache that stores temporary image data.

    @param[out] ppScreen
    Pointer to a variable of the type (CTScreen2 *).
    Will point to a newly allocated object after a successful call.

    @return @c CERR_OK on success.

    @see @ref ctrender2d
*/
CRESULT ctscreen2_create(CTSize *pTileDims, 
                         CTDecoder *pDecoder,
                         CTTextureCache *pTextureCache,
                         CTScreen2 **ppScreen);

                                
//-----------------------------------------------------------------------------
/**
    @brief Destroys a screen.

    @param pScreen
    A valid pointer to a screen object, or @c NULL.
*/
void ctscreen2_destroy(CTScreen2 *pScreen);

//-----------------------------------------------------------------------------
/**
    @brief Renders the screen's current representation.

    The screen uses its @c CTRender2D object to render the tiles from 
    the internal tile cache.

    Note that the target/destination (e.g. some back-buffer) for the renderer
    is implementation specific and depends entirely on the CTRender2D object
    used.

    @param pScreen
    A valid pointer to a screen object.

    @return @c CERR_OK on success.
*/
CRESULT ctscreen2_render(CTScreen2 *pScreen);

//-----------------------------------------------------------------------------
/**
    @brief Retrieves the screen's @c CTViewport object.

    @param pScreen
    A valid pointer to a screen object.

    @return
    Pointer to the screens @c CTViewport object.
    The Viewport object is owned by the screen and must NOT be freed by the caller.
*/
CTViewport *ctscreen2_viewport(CTScreen2 *pScreen);

//-----------------------------------------------------------------------------
/**
    @brief Retrieves the screen's @c CTRender2D object.

    @param pScreen
    A valid pointer to a screen object.

    @return
    Pointer to the screens @c CTRender2D object.
*/
CTRender2D *ctscreen2_renderer(CTScreen2 *pScreen);

//-----------------------------------------------------------------------------
/**
    @brief Applies a dithering filter to prevent gradient errors.

    @param pScreen
    A valid pointer to a screen object.

    @param status
    Set status to true if dithering should be enabled.

    @note
    Currently only screens with colormode ::CM_RGB565 and ::CM_BGR565 are
    supported by this function. There will not be any effect with any other
    colormode.

    @return @c CERR_OK on success.
*/
CRESULT ctscreen2_setApplyDithering(CTScreen2 *pScreen, CTbool status);

//-----------------------------------------------------------------------------
/**
    @brief Retrieves an iterator, which on subsequent calls will decode tiles and
    fill up the screen's cache.

    The retrieved iterator needs to be run, by calling caps_doNextIteration(),
    to supply the screen with image data to render. (See: @ref iterative_operations)

    For each run of the iterator, the quality of the image will gradually improve
    (until optimal quality is reached). While there remains work the iterator to
    execute, it will return: ::CERR_OK. When optimal image quality has been reached,
    the itearator will return ::CRES_TASK_COMPLETE.

    The retrieved iterator does not have to be destroyed when finished, but may reused
    when new image data is needed. That is, whenever the viewport is changed, the same
    iterator will be reactivated and can be called again, even if it previously has
    returned ::CRES_TASK_COMPLETE.

    If the @c ppIterator argument is @c NULL, the screen will process all tiles,
    neccessary for rendering the viewport in optimal quality, before the function
    returns.

    Note that if ctscreen2_render() is called before running the (pre-render) iterator,
    nothing will be rendered to the screen.

    @param pScreen
    A valid pointer to a screen object.

    @param[out] ppIterator
    Pointer to a variable of the type (CTIterator *).
    Will point to a newly allocated object after a successful call.
    @n
    If @c NULL is passed, the entire viewport will be rendered, in final quality,
    into the cache before the function returns.

    @return @c CERR_OK on success.
*/
CRESULT ctscreen2_preRender(CTScreen2 *pScreen, CTIterator **ppIterator);

/** @} */
// end of addtogroup 'ctscreen2'
//==============================================================================

#ifdef __cplusplus
} // extern "C"
#endif

#endif
