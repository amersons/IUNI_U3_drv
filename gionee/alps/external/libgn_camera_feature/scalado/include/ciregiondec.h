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

#ifndef CIREGIONDEC_H
#define CIREGIONDEC_H

#include "scbdefs.h"
#include "ctstream.h"
#include "caps_iterator.h"
#include "ctregiondec.h"
#include "ctimagechannels.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
/**
    @file ciregiondec.h
    @brief This header file contains the interface needed in order to create 
    implementations of CTRegionDec classes.
    @ingroup ciregiondecoder
*/
//==============================================================================

/**
    @addtogroup ciregiondecoder
    @brief The CIRegionDec interface is an interface describing extraction of
    pixel data from an image source.

    Normally a CTRegionDec is created from a parsed CTDecoder implementation, 
    but this is not necessarily the case.

    @{
*/
//------------------------------------------------------------------------------

/**
    @interface CIRegionDec
    @brief
    Region Decoder.

    This object provides the interface to do decoding of image regions.

    Since region decoding may need an initial preparation phase, a prepare
    method must be implemented.
*/
typedef struct
{
    /**
        @brief
        Releases internal allocations in the context, but not the memory 
        allocated for the context itself.

        @param pDecoder A pointer to a valid region decoder.

        @remarks Note that many decoder implementations may choose to not 
        instantiate a specific context for decoding, but reuse the main decoder
        context for pixel decoding. In that case, the deinit function must be
        left empty.
        \n
        However, the deinit function is not optional to implement.

    */
    void (*deinit)( CTRegionDec *pDecoder );

    /**
        @brief
        Prepares the image for decoding with a region decoder.

        This function is optional to implement, but if it is implemented,
        it must be executed before decoding.

        @param pContext A pointer to a valid context instance.
        @param[out] ppIterator A pointer to an iterator to be used for 
        preparing the decoder.

        @return
        @c CERR_OK if successful or an appropriate error code on failures.

        @remarks
        @li Unlike most iterators, the ppIterator argument to this function is not
            optional.

        @li Even if the image is corrupt, this function should return CERR_OK, as long as
        the image can be decoded using ctregiondec_decodeRegion(). If the image is corrupt
        but can be decoded, an appropriate error specification should be given in
        getDecodeResult().
    */
    CRESULT (*prepare)( CTRegionDec *pDecoder, CTIterator **ppIterator );
    
    /**
        @brief
        Decodes a downscaled region of the image.

        The requested rectangle, must be withing the boundaries of the image
        dimensions. The function does not check if this constraint is fulfilled
        to reduce overhead.
        
        @param pContext A pointer to a valid context instance.
        @param pRect A pointer to a valid rectangle object.
        @param downScale A downscaling factor. It must be a power of two.
        @param pImageChs A pointer to a valid image channels object.

        @remarks
        Only pImage with AYUV8888 and ARGB8888 formats should be supported at 
        the moment.
    */
    CRESULT (*decodeRegion)( CTRegionDec *pDecoder,
                             CTRect *pRect, 
                             CTuint32 downScale,
                             CTImageChannels *pImageChs );

    /**
        @brief
        Gets the decode result value from the region decoder.

        This function is optional to implement.

        @param pContext Region decoder context

        @return CRESULT indicating success of the call. CERR_OK if the function
        is not implemented.
    */
    CRESULT (*getDecodeResult)( CTRegionDec *pDecoder );

} CIRegionDec;

//------------------------------------------------------------------------------

/**
    @brief
    Creates a region decoder.

    This function is normally used in the specific constructor of the 
    decoder implementing the interface.

    @param pInterface A pointer to a valid region decoder interface.
    @param dims Width and height of the image
    @param sizeOfContext Size of the context to be created.
    @param[out] ppDecoder A pointer to the created region decoder.

    @return @c CERR_OK or a proper error code.

    @remarks The context has to be initialized by the caller and can be 
    retrieved by ctregiondec_context(). The context must be a context 
    compatible with this region decoder. Either it is created by the 
    main decoder or it is created by the factory creating this decoder instance. 
    \n
    Many implementations will choose to use the main decoder context.
    Such a relationship implies that the deinit function must be left empty.

    @since 3.8.2 R02
*/
SCBIMPORT CRESULT ctregiondec_create( const CIRegionDec *pInterface,
                                      CTSize dims,
                                      CTuint32 sizeOfContext, 
                                      CTRegionDec **ppDecoder );

/**
    @brief
    Retrieves the region decoder context
    
    @param pDecoder A pointer to a valid reference of an region decoder.
    
    @return The interface context for the region decoder object, or NULL if the
    decoder is invalid.

    @since 3.8.2 R02
*/
SCBIMPORT void* ctregiondec_context( CTRegionDec *pDecoder );

//==============================================================================
/** @} */
// end addtogroup ciregiondecoder

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif // CIREGIONDEC_H
