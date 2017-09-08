/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    © 2000-2009 Scalado AB. All rights reserved.                             .
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

//----------------------------------------------------------------------------
//    Example of implementation of read functions for buffers.
//----------------------------------------------------------------------------

#ifndef CTSTREAM_BUFFER_H
#define CTSTREAM_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ctstream.h"

//=============================================================================
/**
    @ingroup scb_ctstream_buffer
    @file ctstream_buffer.h
    @brief Buffer based stream creation.
*/
//=============================================================================
/**
    @addtogroup scb_ctstream_buffer
    @brief Creation of buffer streams
    @{
*/
//-----------------------------------------------------------------------------
/**
    @brief
    Create a stream from a buffer.

    This function will create a stream object that uses a @c CTBuffer as 
    underlying resource. 

    For output streams, the buffer can grow to a max size expecified as a 
    parameter, which means that the internal pointer in the @c CTBuffer 
    object ( @c data member ), can be freed and allocated internally multiple 
    times.

    @param pBuffer The input buffer that will be used to read or write data to.
    The CTBuffer struct that pBuffer points to must be valid during the whole
    life time of the CTStream.
    @param maxBuffer max size the buffer can become when writing data to it. Zero means
    that it can grow as much as needed.

    @param[out] ppStream Pointer to an stream object.

    When the stream object (returned by this function) is no longer needed, it
    should be destroyed using: ctstream_destroy()

    @return
    @li @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8
*/
SCBIMPORT CRESULT 
ctstream_createBufferStream ( CTBuffer *pBuffer,
                                      CTuint32 maxBuffer,
                                      CTStream **ppStream );
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'scb_ctstream'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // CTSTREAM_BUFFER_H
