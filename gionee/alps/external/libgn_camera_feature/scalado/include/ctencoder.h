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


#ifndef CTENCODER_H
#define CTENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctstream.h"
#include "ctinterfaceid.h"
#include "ctimagechannels.h"

//==============================================================================
/**
    @file ctencoder.h
    @brief This header file defines the public interface for accessing a 
    CTEncoder object.
    @ingroup ctencoder
*/
//==============================================================================

/**
    @addtogroup ctencoder
    @brief A CTEncoder object handles encoding of pixel data sent to it as a 
    sequence of tiles.

    It also handles tile specification, in order to support optimal use of
    caching or other needed mechanisms of the underlying encoder implementation.

    @{
*/
//------------------------------------------------------------------------------

/**
    @brief
    CTEncoder provides a generic image encoding interface. 

*/
typedef struct CTEncoder CTEncoder;

/**
    @brief
    Preferred direction of tiles coming in to the encoder.
*/
typedef enum
{
    TILE_ORDER_DOWN = 0 ///< Left to right primarily, then top to bottom.
} CTTileOrder;

/**
    @brief
    Tile Specification.
    
    This structure specifies the constraints to be fulfilled when feeding
    the encoder with pixel data.

*/
typedef struct
{
    CTuint32 maxWidth; ///< Largest possible width of a block of pixels to encode.
    CTuint32 maxHeight; ///< Largest allowed height of a block to encode.
    CTuint32 minWidth; ///< Smallest width of a block to encode.
    CTuint32 minHeight; ///< Smallest allowed height of a block of pixels to encode.
    CTuint32 widthGranularity; ///< All allowed block widths must be a multiple of widthGranularity.
    CTuint32 heightGranularity; ///< All allowed block heights must be a multiple of heightGranularity.
    CTColormode colorMode; ///< Color mode for pixel data.
    CTTileOrder order; ///< Order of tiles to be encoded.
} CTTileSpec;

/**
    @brief
    Default tile specification.

    This variable is used to initialize a tile 
    specification prior to negotiations.
*/
extern const CTTileSpec gDefaultTileSpec;

/**
    @brief
    Begins the encoding process, preparing the necessary structures.

    This function will also output the header if needed, and return
    a CTTileSpec object with the required specifications of the input
    pixel data.
    
    @param pEncoder A pointer to a valid encoder instance.
    @param dims Dimensions of the image to be encoded.
    @param[out] pTileSpec A pointer to a tile specification.
    
    @return CERR_OK, a proper error or status code. Since the
    encoder encodes to a stream, it could also delay.
    @c CERR_OPERATION_FAILED if the encoder is not ready to begin encoding
    pixel data, or has already started.
    @c CERR_STREAM_DELAYED if the stream delayed the write operation.

    @remarks
    The tile specification does not indicate suggested values for tiles, and
    must be strictly followed with a few exceptions (that are documented in
    ctencoder_encodeTiles).

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctencoder_beginEncoding( CTEncoder *pEncoder, 
                         CTSize dims, 
                         CTTileSpec *pTileSpec );

/**
    @brief
    Encodes a tile of pixel data.
    
    The tiles must follow the tile specification returned in the begin
    function.
    
    @param pEncoder A pointer to a valid encoder instance.
    @param pTile A CTImageChannels object representing a tile of pixel data.
    
    @return CERR_OK, a proper error or status code. Since the
    encoder encodes to a stream, it could also delay.
    @c CERR_OPERATION_FAILED if the encoder is not ready to encode pixel data.
    @c CERR_STREAM_DELAYED if the stream delayed the write operation.

    @remarks The tile parameter expects to follow the pTileSpec returned
    by the encoder in ::ctencoder_beginEncoding except for a few cases.
    @li At the end of a scan line, the tiles may violate the minimum width
    specified by the tile specification. Similarly, if the encoder has reached
    the top or bottom of the image, the minimum height value may be ignored.
    This condition is true for height and width granularity as well.
    @li The encoder is free to ignore extra data passed to it, if that data 
    exceeds the image dimensions.
    @li If the encoder needs extra data past the image dimensions, it is free
    to invents its own pixel data for those regions.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctencoder_encodeTile( CTEncoder *pEncoder, CTImageChannels *pTile );

/**
    @brief
    End encoding.
    
    Finalizes the encoding, freeing resources and writing a footer if
    needed.
    
    @param pEncoder A pointer to a valid encoder instance.
    
    @return CERR_OK, a proper error or status code. Since the
    encoder encodes to a stream, it could also delay.
    @c CERR_OPERATION_FAILED if the encoder has not begun to encode, or has
    already stopped.
    @c CERR_STREAM_DELAYED if the stream delayed the write operation.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctencoder_endEncoding( CTEncoder *pEncoder );

/**
    @brief
    Destroys an instance of a CTEncoder.
    
    @param pEncoder A pointer to a valid encoder instance or NULL.
    
    @since 3.8.2 R01
*/
SCBIMPORT void ctencoder_destroy( CTEncoder *pEncoder );

/**
    @brief
    Returns the interface context related to the interface id.

    This interface is implementation specific and in its simplest form, may
    return a pointer to the underlying context (ie. returns a reference to
    pContext). The caller is responsible for casting the returned pointer 
    to the correct type.

    This operation may be thought of as upcasting an interface.

    @param pEncoder Encoder to use for this call.
    @param interfaceId Interface id to query for a context.
    @param[out] ppInterfaceContext Pointer to the returned context. The 
    caller does not own the reference, and so must not attempt to free
    it.

    @return 
    @c CERR_OK if successful, or an error code on failure.
    @c CERR_NOT_IMPLEMENTED if this operation is not implemented by the
    encoder implementation.
    @c CERR_INVALID_PARAMETER if the particular requested interface is not
    available.

    @remarks This method is optional to implement. If not implemented, it 
    will return an appropriate error code.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctencoder_interfaceContext( CTEncoder *pEncoder, 
                            CTInterfaceID interfaceId, 
                            void **ppInterfaceContext );

/**
    @brief
    Negotiates the tile specification with the encoder.

    @param pEncoder A pointer to a valid encoder instance.
    @param dims Dimensions of the image to be encoded.
    @param[in,out] pTileSpec A pointer to a tile specification to negotiate.

    @return CERR_OK if the encoder could negotiate the tile spec. In this 
    case, the pTileSpec variable with new constraints or accepted as is.
    CERR_NOT_IMPLEMENTED is returned if the negotiate function isn't 
    implemented.

    @remarks The encoder may chose to reject all incoming suggestions
    regardless of how reasonable they would be to fulfill (for instance
    lowering the range of allowed widths). If, however, the encoder returns
    CERR_OK, this tile spec can be expected to appear in beginEncoding, if
    that function is called directly after negotiations have finished.

    If this function is not called, the encoder may choose any tile spec
    in the call to beginEncode.

    @since 3.8.2 R01
*/
SCBIMPORT CRESULT 
ctencoder_negotiateTileSpec( CTEncoder *pEncoder, 
                             CTSize dims, 
                             CTTileSpec *pTileSpec );


/**
    @brief
    Encodes an image of pixel data.

    @param pEncoder A pointer to a valid encoder instance.
    @param pImage A CTImage object representing the image.

    @return CERR_OK, a proper error code.
    @since 5.3 
*/
SCBIMPORT CRESULT 
ctencoder_encodeImage(CTEncoder *pEncoder, CTImage *pImage);

//==============================================================================
/** @} */
// end addtogroup ctencoder


#ifdef __cplusplus
}       // extern "C"
#endif  // __cplusplus
#endif // CTENCODER_H
