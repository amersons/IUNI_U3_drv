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

#ifndef CTTEXTURECACHE_H
#define CTTEXTURECACHE_H

#include "ctrender2d.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @file cttexturecache.h
    @brief This header defines the public interface of the CTTextureCache object.
    @ingroup cttexturecache
*/
//=============================================================================
/**
    @addtogroup cttexturecache
    @brief The @c CTTextureCache object is a texture cache that handles temporary
    storage of decoded image data.
    
    The @c CTTextureCache object keeps track on allocated textures and makes sure
    to release the same. Cache object is used as input to @ref ctscreen2 which utilizes 
    cache for rendering purposes. Same cache object can be re-used while recreating
    Screen2 objects.
    
    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief Type representing CTTextureCache objects.
*/
typedef struct CTTextureCache CTTextureCache;


//-----------------------------------------------------------------------------
/**
    @brief Creates a CTTextureCache object dimensioned by cache size and connected to a renderer.

    @param cacheSizeInTiles
    The number of tiles the cache should hold. Max size is 32767.
    @n
    The minimum number of tiles needed depends on the resolution of the target screen. 
    The total pixel area covered by the tiles must be large enough to match target resolution.
    Use cttexturecache_getMinimumCacheSize() to get minimum required cache size.

    @param pRenderer
    A renderer responsible for rendering image data from cache to the target.

    @param[out] ppTextureCache
    Pointer to a variable of the type (CTTextureCache *).
    Will point to a newly allocated object after a successful call.
    
    @return @c CERR_OK on success.

*/
CRESULT cttexturecache_create(CTuint32 cacheSizeInTiles, CTRender2D *pRenderer, CTTextureCache **ppTextureCache);


//-----------------------------------------------------------------------------
/**
    @brief Releases allocated textures and resets cache. After call to this API
    cache is put to the same state as newly created.
    
    @param pTextureCache
    A texture cache that holds allocated textures.
 
    @return @c CERR_OK on success.

*/
CRESULT cttexturecache_releaseTextures(CTTextureCache *pTextureCache);

//-----------------------------------------------------------------------------
/**
    @brief Releases allocated textures and destroys cache.

    @param pTextureCache
    Existing texture cache that holds allocated textures.
 
    
*/
void cttexturecache_destroy(CTTextureCache *pTextureCache);


//-----------------------------------------------------------------------------
/**
    @brief Returns minimum cache size.

    Returns minimum required cache size for current configuration.

    @param tileDims
    Tile dimensions.

    @param screenSize
    Screen size.

    @return @c Minimum cache size in number of tiles.
*/
CTuint32 cttexturecache_getMinimumCacheSize(CTSize tileDims, CTSize screenSize);

/** @} */
// end addtogroup 'cttexturecache'
//==============================================================================

#ifdef __cplusplus
} // extern "C"
#endif
#endif // CTTEXTURECACHE_H
