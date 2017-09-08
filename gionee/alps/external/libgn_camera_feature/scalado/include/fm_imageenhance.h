/*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2011 Scalado AB. All rights reserved.                           .
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

#ifndef FM_IMAGEENHANCE_H
#define FM_IMAGEENHANCE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAPS_BASE_XMIF_H
#include "caps_base.h"
#endif

//=============================================================================
/**
    @ingroup fm_imageenhance
    @file fm_imageenhance.h
    @brief Defines interfaces for the Caps Feature Module: @a ImageEnhance
*/
//=============================================================================
/**
    @addtogroup fm_imageenhance
    @brief Enhancement effects
*/
//-----------------------------------------------------------------------------
/**
    @addtogroup fxgroup_foundation
    @{
*/
/**
    @brief
    Applies a foundation effect on the current session image.

    @param[in] session
    Handle to a valid session.

    @param[in] pRegion
    (OPTIONAL) Pointer to a @c CTRect object specify a region in which the 
    effect is applied, for instance a face, given in current coordinates. 
    Set this argument to @c NULL if the effect should be applied to the 
    entire image.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8

    @deprecated This function is deprecated since 5.3.
    Use @ref fm_facebeautification instead.
*/
SCBIMPORT CRESULT caps_applyFoundation( CTSession session, CTRect* pRegion);

/** @} */
// end 'fxgroup_foundation'
//-----------------------------------------------------------------------------

/**
    @addtogroup fxgroup_noisereduction
    @copydoc begin_end_effects
    @{
*/
/**
    @brief
    Begin noise reduction on current session image.

    <b>Note</b> This function and @a NoiseReduction2 uses different
    algorithms.

    @param[in] session
    Handle to a valid session.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8 R4

    @deprecated This function is deprecated since 5.3.
    Use noisereduction2 instead.
*/
SCBIMPORT CRESULT caps_beginNoiseReduction( CTSession session );
//.............................................................................
/**
    @brief
    Applies noise reduction on the current session image.

    @param[in] session
    Handle to a valid session.

    @param[in] level
    The noise reduction adjustment level. Range 0.0 - 1.0, where 0.0 indicates 
    low noise reduction and 1.0 indicates high noise reduction.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8 R4

    @deprecated This function is deprecated since 5.3.
    Use noisereduction2 instead.
*/
SCBIMPORT CRESULT caps_setNoiseReduction( CTSession session, 
                                          CTfloat level );
//.............................................................................
/**
    @brief
    End noise reduction on the current session image.

    @param[in] session
    Handle to a valid session.

    @since 3.8 R4

    @deprecated This function is deprecated since 5.3.
    Use noisereduction2 instead.
*/
SCBIMPORT void caps_endNoiseReduction( CTSession session );

/** @} */
// end of group 'NoiseReduction'
//-----------------------------------------------------------------------------

/**
    @addtogroup fxgroup_whiteboard
    @copydoc begin_end_effects
    @{
*/
/**
    @brief

    @param session
    Handle to a valid session.

	@return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8 R4
*/
SCBIMPORT CRESULT caps_beginWhiteboardEnhancement( CTSession session );
//.............................................................................
/**
    @brief
    Effect should enhance text and drawings on an image of a whiteboard.

    @param[in] session
    Handle to a valid session.

    @param[in] soft
    If true, the effect will better preserve the colors on the whiteboard.
    If false, the image contrast will be enhanced and text should be easier
    to read.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.8 R4
*/
SCBIMPORT CRESULT caps_setWhiteboardEnhancement( CTSession session, 
                                                 CTbool soft );
//.............................................................................
/**
    @brief

    @param[in] session
    Handle to a valid session.

    @since 3.8 R4
*/
SCBIMPORT void caps_endWhiteboardEnhancement( CTSession session );

/** @} */
// end of group 'WhiteboardEnhancement'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif      // !defined( FM_IMAGEENHANCE_H )
