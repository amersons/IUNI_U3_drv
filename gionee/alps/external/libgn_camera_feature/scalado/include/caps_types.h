/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    © 2000-2010 Scalado AB. All rights reserved.                             .
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

#ifndef CAPS_TYPES_H
#define CAPS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "oslfile.h"

//=============================================================================
/**
    @file caps_types.h
    @brief This header defines the public types of the CAPS Base API.
    @ingroup types_n_defs
*/
//=============================================================================
/**
    @addtogroup types_n_defs
    @{
*/
//-----------------------------------------------------------------------------

/**
    @brief
    The central handle type used for all editing sessions.

    A session is the environment surrounding the task of decoding-encoding and
    optionally manipulating a source image with a number of effects.

    @since 3.0
*/
typedef struct cips* CTSession;

//-----------------------------------------------------------------------------
/**
    @brief
    The screen type used for output during rendering sessions.

    One or more screens can be created within the same session and thus have
    to be destroyed before destroying the session.

    @since 3.0
*/
typedef struct CTScreen CTScreen;

//-----------------------------------------------------------------------------
/**
    @brief
    Defines the image formats which CAPS internally support. 
    @c IMAGE_FORMAT_RANGE_MIN and @c IMAGE_FORMAT_RANGE_MAX should never be
    used, they are control points for internal formats.

    @deprecated CAPS_IMAGE_FORMAT is deprecated, use CTImageFormat instead.

    @since 3.0
*/
typedef CTImageFormat CAPS_IMAGE_FORMAT;

//-----------------------------------------------------------------------------
/**
    @brief
    Image format specification type. 

    This type can be used in favor of @ref CTImageFormat in order to allow 
    specifications of image formats not included in CAPS' internal codec 
    support.

    @since 3.0
*/
typedef CTint32 IMAGE_FORMAT_SPEC;
//-----------------------------------------------------------------------------
/**
    @brief
    Defines the output options used when rendering to disk or buffer.

    Note that these options don't apply to screen output, only output through
    basic render methods like caps_renderToFile() and similar.

    @since 3.0
*/
typedef enum 
{
    /**
    Fits the image data within the output dimensions as well as possible,
    preserving aspect ratio. If the image is fit smaller than the bounding
    box formed by the output dimensions, the remaining borders will be
    padded with the currently set background color.
    See caps_setBackgroundColor() for details.
    */
    CAPS_OUTPUT_PRESERVE_AR = 0,

    /**
    Stretches the image data to fit the specified output dimensions. This
    option allows the image to be distorted.
    */
    CAPS_OUTPUT_STRETCH

} CAPS_OUTPUT_OPTION;
//-----------------------------------------------------------------------------
/**
    @brief
    Defines the event signals which can be sent to the session using
    caps_signalSessionEvent() to trigger various responses.

    @since 3.1
*/
typedef enum
{
    /**
    Signals the session that the source data contents has changed, which
    will cause any internal cache or state related to the source data to be
    invalidated. This is for instance useful when creating a session with 
    caps_newSessionWithRaw(), and then continously updating the contents of the 
    source buffer.
    */
    EVENT_SOURCEDATA_CHANGE = 1,

    /**
    Signals the session that the state of an external plugin has changed and
    will need a full rendering process in order to synchronize its behaviour.
    */
    EVENT_PLUGINSTATE_CHANGE = 2

} CTSessionEvent;
typedef CTSessionEvent SESSION_EVENT;
//-----------------------------------------------------------------------------
/**
    @brief
    Defines different ways to handle ownership of objects and memory between 
    CAPS and the caller. 

    When the user provides an API function with an object or memory buffer, the 
    option is in some cases available to keep ownership on the caller's side or
    to transfer it to CAPS. The options defined within this enumeration are 
    used in such situations to indicate how the API should proceed.

    @since 3.2
*/
typedef enum
{
    /**
    Causes CAPS to take ownership over the object or memory buffer in question.
    When the item is no longer needed it is destroyed, which may occur anytime
    during the life cycle of a session. 
    The method used to destroy an object and/or deallocate heap memory is
    further described where the option is available. 
    IMPORTANT: When heap memory is involved either directly or indirectly 
    (indirectly for instance when being part of an object like CTBuffer) it 
    will be deallocated using oslmem_free(), which is part of the OS 
    integration layer (OSIL). This should be carefully considered when 
    transferring ownership to CAPS since there's a risk that memory can be 
    allocated with a different API than the one being used in OSIL. Such a 
    risk may lead to errors in diagnostic tool reports or leak detectors.
    */
    OWNERSHIP_CAPS,

    /**
    Signals that ownership is NOT transferred to CAPS. Responsibility to 
    destroy the object or deallocate heap memory stays with the caller. The
    safest place to make such cleanup tasks is directly after destroying the
    corresponding session. Before that point the object or memory buffer may
    still be in use.
    */
    OWNERSHIP_EXTERNAL

} OWNERSHIP_POLICY;
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'types_n_defs'.
//-----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CAPS_TYPES_H
