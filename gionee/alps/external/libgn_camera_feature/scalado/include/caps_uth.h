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

#ifndef CAPS_UTH_H
#define CAPS_UTH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "caps_base.h"

//=============================================================================
/** 
    @file caps_uth.h
    @brief This header defines advanced functions for tuning special behaviour.
    @ingroup caps_uthapi
*/
//=============================================================================
/**
    @addtogroup caps_uthapi
    @brief
    This is the CAPS Under-The-Hood API for advanced tuning and maintainance.

    The functions defined herein opens up the possibility to modify internal 
    mechanisms and behaviour which can produce severe damage to performance
    and quality if used incorrectly.

    @warning
    This API should never be used without carefully consulting Scalado AB
    about the situation and describing the problem(s) intended to be solved.

    @{
*/
//-----------------------------------------------------------------------------
/** 
    @brief 
    Disables the internal DSO mechanism which optimizes screen rendering
    performance when adjusting certain effects. If DSO is active when calling
    this function it is immediately deactivated.

    @param session
    A valid CTSession handle.

    @remarks
    The DSO mechanism is an important part of the internal optimization of
    screen output rendering. It heavily increases performance when adjusting
    effects such as clipart, spotlight etc. However, when for example using 
    CAPS with source data continously being updated, the DSO mechanism can do
    more harm than good since it behaves like a cache and prevents realtime
    reflection of changes in source data.

    @remarks
    It should be noted that apart from using this UTH function for indicating
    change in source data, the regular caps_signalSessionEvent() from the
    Base API can be used for the same purpose.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_uthDisableDSO( CTSession session );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the block cache size used internally by rajpeg to optimize decoding
    speed.

    @param session
    A valid @c CTSession handle.

    @param cacheSize
    The requested cache size in kilobytes. Default setting: 100 (kb).

    @return 
    @c CERR_OK if successful or a specific error code upon failure.
    @c CERR_ILLEGAL_CALL is returned if the session doesn't have a JPEG source 
    image loaded.

    @sa
    caps_uthGetOptimalRajpegCache()

    @since 3.1
*/
SCBIMPORT CRESULT caps_uthSetRajpegCacheSize( CTSession session, CTuint16 cacheSize);
//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the render session block size for the sipla subsystem.
    
    @htmlonly 
    <p class=warning>- NOTE -<br>This function must 
    not be used without consulting Scalado.</p> 
    @endhtmlonly

    @param session
    A valid @c CTSession handle.

    @param blockSize
    @c CTSize object specifying the new rendering block size. Width and 
    height must be from the ::CTRenderBlocksize enumeration.
    @n Default values:
    - width  = OPT_RENDER_BLOCKSIZE_128
    - height = OPT_RENDER_BLOCKSIZE_16

    @remarks
    Setting color spacing is just a hint to the encoder used to render, and
    other limitations and settings may invalidate the settings made in this
    call.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_uthSetRenderBlockSize( CTSession session, 
                                              CTSize blockSize );
//-----------------------------------------------------------------------------
/**
    @brief Render quality settings
*/
typedef enum
{
    /** Fast render performance but with lower image quality. */
    CAPS_RENDERMODE_OPTIMIZE_SPEED = 0,
    
    /** Medium render performance and image quality. */
    CAPS_RENDERMODE_NORMAL,

    /** Slower render performance but with high image quality. */
    CAPS_RENDERMODE_OPTIMIZE_QUALITY
    
} CAPS_RENDER_MODE;
//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the render session quality preference for the sipla subsystem.
    
    @param session A valid @c CTSession handle.

    @param quality
    The requested quality setting, can be one of the values from the 
    ::CAPS_RENDER_MODE enumeration. Default for regular sessions is:
    @c CAPS_RENDERMODE_OPTIMIZE_QUALITY, and for SPMO-initiated sessions:
    @c CAPS_RENDERMODE_NORMAL.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1
*/
SCBIMPORT CRESULT caps_uthSetRenderQuality( CTSession session, 
                                  CAPS_RENDER_MODE quality );
//-----------------------------------------------------------------------------
/**
    @brief Decode quality settings
*/
typedef enum
{
    /** Slower decoding performance but with highest possible image quality. */
    CAPS_DECODE_OPTIMIZE_HIGHEST_QUALITY = 0,
    /** Slower decoding speed but with high image quality. */
    CAPS_DECODE_OPTIMIZE_QUALITY,    
    /** Medium decoding performance and image quality. */
    CAPS_DECODE_NORMAL,
    /** Fast decoding speed but with lower image quality. */
    CAPS_DECODE_OPTIMIZE_SPEED
    
} CAPS_DECODE_MODE;
//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets options for the JPEG decoder.

    @param session
    A valid @c CTSession handle.

    @param mode
    The requested decode mode setting, can be one of the values from the 
    ::CAPS_DECODE_MODE enumeration. Default for regular sessions is:
    @c CAPS_DECODE_OPTIMIZE_QUALITY, and for SPMO-initiated sessions:
    @c CAPS_DECODE_NORMAL.

    @note
    This function is only applicable on JPEG sessions, CERR_ILLEGAL_CALL 
    will be returned otherwise.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4
*/
SCBIMPORT CRESULT caps_uthSetJpegDecodeMode( CTSession session, CAPS_DECODE_MODE mode );

//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the decoding quality of an spmo decoder

    @param session
    A valid @c CTSession handle.

    @param mode
    The requested decode mode setting, can be one of the values from the 
    ::CAPS_DECODE_MODE enumeration. Default is @c CAPS_DECODE_NORMAL.

    @note
    This function is only applicable on sessions created from spmo objects.
    On other sessions, the function has no effect.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.10.3

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_uthSetSpmoDecodeMode( CTSession session,
                                             CAPS_DECODE_MODE mode );

//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the prefetching option for the JPEG decoder or the BMP decoder.
    When disabling the prefetch option, the file will not be read into
    memory. Therefore the memory needed in the session will be reduced with approx.
    the file size.

    @param session
    A valid @c CTSession handle.

    @param enablePrefetch
    True, if the files should be read into memory. False, otherwise.
    Default value is true.

    @note
    This function is only applicable on sessions decoding JPEG or 24-bit 
    BMP, CERR_ILLEGAL_CALL will be returned otherwise.

    @note
    This function has no effect on progressive JPEG images.

    @note
    This function must be called after each call to caps_setSourceImage()
    if no prefetching is desired.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.6
*/
SCBIMPORT CRESULT caps_uthSetPrefetchFlag( CTSession session, 
                                 CTbool enablePrefetch );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the colorspacing to be used when rendering to JPEG format.

    @param session
    A valid @c CTSession handle.

    @param colorspacing
    A ::CTColorspacing value with the requested colorspacing. Default: CM_YUV420

    @remarks
    The current render block size will be altered if not compatible with the
    given colorspacing; see: caps_uthSetRenderBlockSize()

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4
*/
SCBIMPORT CRESULT 
caps_uthSetJpegColorspacing( CTSession session, 
                             CTColorspacing colorspacing );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the sampling mode for the sipla subsystem.

    @param session
    A valid @c CTSession handle.

    @param mode
    The requested sampling setting, can be one of the values from the 
    ::SCB_SAMPLING_MODE enumeration. Default value for a regular session
    is: SCB_SAMPLING_BILINEAR. Default value for a speedview session is:
    SCB_SAMPLING_BOX.

    @note
    Currently only SCB_SAMPLING_BOX or SCB_SAMPLING_BILINEAR
    is supported.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.4

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_uthSetSamplingMode( CTSession session,
                                 SCB_SAMPLING_MODE mode );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Sets the status of the cached panning feature.

    @param screen
    A valid @c CTScreen.

    @param status
    A CTbool parameter. If status is set to false the cached panning feature 
    will be disabled and the whole screen will be rendered for each pan. This
    is slower and is not recommended. If status is true the cached pan
    is enabled.\n\n

    The cached panning feature is enabled by default.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.5
*/
SCBIMPORT CRESULT caps_uthSetPanCacheStatus( CTScreen* screen,
                                   CTbool status );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Get the status of the cached panning feature.

    @param screen
    A valid @c CTScreen.

    @param[out] status
    A CTbool parameter. If the cached pan feature is disabled, the
    returned status parameter is false. If the returned status
    parameter is true the cached pan is enabled.\n\n

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.5
*/
SCBIMPORT CRESULT caps_uthGetPanCacheStatus( CTScreen* screen,
                                   CTbool* status );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Retrieves the product identifier.

    @return 
    The version as a static constant null-terminated string.

    @since 3.6.1
*/
SCBIMPORT const DCHAR* caps_uthGetProductIdentifier(void);
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'caps_uthapi'
//-----------------------------------------------------------------------------


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // !defined( CAPS_UTH_H )
