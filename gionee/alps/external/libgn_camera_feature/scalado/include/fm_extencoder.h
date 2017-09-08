/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2010 Scalado AB. All rights reserved.                           .
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


#ifndef FM_EXTENCODER_H
#define FM_EXTENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "caps_base.h"

//=============================================================================
/**
    @ingroup fm_extencoder
    @file fm_extencoder.h
    @brief
    Defines the interface of the Caps Extension Module: @a External Encoder
*/
//=============================================================================
/**
    @addtogroup fm_extencoder External Encoder
    @brief
    Defines the interface of the Caps Extension Module: @a External Encoder

    @{
*/

/**
    @brief 
    The central handle type used by all external encoders.

    @since 3.5
*/
typedef struct CTExtEncoder CTExtEncoder;

/**
    @brief Configuration of an Encoding job.
*/
typedef struct CTEncodingJob CTEncodingJob;
//-----------------------------------------------------------------------------

/**
    @name Callbacks
    @brief Function prototype definitions for callbacks used
    with caps_createExternalEncoder().
*/
/*@{*/

/** @brief Invoked at initialization of encoding. */
typedef CRESULT(* func_extEncBeginEncode )( CTSession, 
                                            CTEncoder*, 
                                            CTEncodingJob* );

/** @brief Invoked for each block to be encoded. */
typedef CRESULT(* func_extEncEncodeBlock ) ( CTSession, 
                                             CTEncoder*, 
                                             CTPoint, 
                                             CTImage* );

/** @brief Invoked after all blocks have been processed. */
typedef CRESULT(* func_extEncEndEncode   ) ( CTSession, 
                                             CTEncoder* );

/*@}*/

//-----------------------------------------------------------------------------

struct CTEncodingJob
{
    /**
    Define the image format for the encoding job. The value should
    be above IMAGE_FORMAT_RANGE_MAX or below @e IMAGE_FORMAT_RANGE_MIN.
    @e IMAGE_FORMAT_RANGE_MIN and @e IMAGE_FORMAT_RANGE_MAX should never be used, 
    they are control points for the range of internal formats. 
    */
    IMAGE_FORMAT_SPEC format;

    /**
        Stream where the encoding data will be written.
    */
    CTStream *pStream;
    
    /**
        The width and height of the output image.
        See documentation of CTSize for more information.
    */
    CTSize size;
    
};
//-----------------------------------------------------------------------------

/**
    @brief
    Register an external encoder to a valid CTSession. This function has been
    deprecated because it is no longer needed. Use caps_renderToEncoder
    using the external encoder instead.

    @param session
    A valid instance of a CTSession.

    @param format
    The format the given encoder supports. This format should be the same
    as passed to any of the render functions in order to invoke the encoder.
    The value should be above @e IMAGE_FORMAT_RANGE_MAX or below 
    @e IMAGE_FORMAT_RANGE_MIN. Registering an external
    encoder on one of the values between @e IMAGE_FORMAT_RANGE_MIN and 
    @e IMAGE_FORMAT_RANGE_MAX will override the default encoder.

    @e IMAGE_FORMAT_RANGE_MIN and @e IMAGE_FORMAT_RANGE_MAX should never be used, 
    they are control points for the range of internal formats.

    @param pEncoder
    A pointer to a CTEncoder object.

    @remarks
    The registered external encoder may be used by the functions
    caps_renderToFile(), caps_renderToFileHandle() and
    caps_renderToBuffer() if the input from @e IMAGE_FORMAT_SPEC
    is not supported by CAPS.
    \n\n
    See documentation of ::IMAGE_FORMAT_SPEC for more information.\n\n
    Please contact scalado with help on porting external encoders to the
    new ctencoder interface.

    @return CERR_NOT_IMPLEMENTED

    @deprecated This function is deprecated. It will be removed in 5.4.
*/
SCBIMPORT CRESULT 
caps_registerExternalEncoder( CTSession session, 
                              IMAGE_FORMAT_SPEC format,
                              CTEncoder *pEncoder );
//-----------------------------------------------------------------------------

/**
    @brief
    Create an external encoder.

    @param pStream  A pointer to a a valid output stream.

    @param inputColormode
    The input colormode specified by this encoder.
    Supported colormodes are:
    - @c CM_ARGB8888
    - @c CM_BGRA8888
    - @c CM_RGBA8888 
    - @c CM_ABGR8888
    - @c CM_RGB888
    - @c CM_BGR888
    - @c CM_RGB565
    - @c CM_BGR565
    - @c CM_GBRG3553
    - @c CM_GRBG3553
    - @c CM_ARGB6666
    - @c CM_GBRGAR264462
    - @c CM_BGRA6666
    - @c CM_RGB444
    - @c CM_BGR444
    - @c CM_GRAY1
    - @c CM_GRAY2
    - @c CM_GRAY4
    - @c CM_GRAY8
    - @c CM_AYUV4444
    - @c CM_A8R8G8B8
    - @c CM_RGB565_G0
    - @c CM_BGR565_G0
    - @c CM_RGB666
    - @c CM_RGB666_G4B4R6G2Z6B2Z8
    - @c CM_YUV422_UY1VY2
    .

    @param inputBlocksizeWidth
    The input blocksize width specified by this encoder.
    See documentation of ::CTRenderBlocksize for more information.

    @param inputBlocksizeHeight
    The input blocksize height specified by this encoder.
    See documentation of ::CTRenderBlocksize for more information.\n\n\n
    
    @param onBeginEncode Callback function implementation of: func_extEncBeginEncode()

    @param onEncodeBlock Callback function implementation of: func_extEncEncodeBlock()

    @param onEndEncode Callback function implementation of: func_extEncEndEncode()

    @param pAux
    This parameter points to encoder specific information.

    @param[out] ppEncoder
    A resulting pointer to a CTEncoder struct.
    @n
    Returns CERR_OK if successful or one of @e CERR_MEMALLOC_FAILED, 
    @e CERR_MEMORY_OUT_OF_BOUNDS or @e CERR_INTERNAL_ERROR on failure.

    @remarks
    The registered external encoder may be used by the functions
    caps_renderToFile(), caps_renderToFileHandle() and caps_renderToBuffer() if 
    the input from IMAGE_FORMAT_SPEC is not supported by CAPS.\n\n

    See documentation of CTEncoder and ::IMAGE_FORMAT_SPEC for more 
    information.

    @return CERR_OK if successful or a specific error code upon failure.

    @deprecated This function is deprecated. It will be removed in 5.4.
*/
SCBIMPORT CRESULT 
caps_createExternalEncoder( CTStream *pStream, 
                            CTColormode inputColormode,
                            CTRenderBlocksize inputBlocksizeWidth,
                            CTRenderBlocksize inputBlocksizeHeight,
                            func_extEncBeginEncode onBeginEncode,
                            func_extEncEncodeBlock onEncodeBlock,
                            func_extEncEndEncode onEndEncode,
                            void *pAux, 
                            CTEncoder **ppEncoder );
//-----------------------------------------------------------------------------

/**
    @brief
    Get the auxiliary data of the External Encoder.

    @param pEncoder
    A valid instance of a CTEncoder.

    @param[out] pAux
    The auxiliary data specific to the External Encoder.

    @remarks
    This data is added to the encoder object at creation time.\n\n

    See documentation of caps_createExternalEncoder() for more information. \n
    Only encoders created through a call to caps_createExternalEncoder can 
    query an encoder object for aux data.

    @return CERR_OK if successful or a specific error code upon failure.

    @deprecated This function is deprecated. It will be removed in 5.4.
*/
SCBIMPORT CRESULT caps_getExternalEncoderAux( CTEncoder *pEncoder, 
                                              void** pAux );
//-----------------------------------------------------------------------------

/**
    @brief
    Destroy the External Encoder.

    @param pEncoder
    A valid instance of a CTEncoder.

    @remarks
    This function has void as return type. It does not return anything
    because it cannot fail.\n\n

    @deprecated This function is deprecated. It will be removed in 5.4.
*/
SCBIMPORT void caps_destroyExternalEncoder( CTEncoder *pEncoder );

/**
    @}
*/
// end 'fm_extencoder'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( FM_EXTENCODER_H )
