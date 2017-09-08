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


#ifndef CAPS_UREXT_H
#define CAPS_UREXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "caps_base.h"

//=============================================================================
/**
    @file caps_urext.h
    @copydoc caps_unredoext
    @ingroup caps_unredoext
*/
//=============================================================================
/**
    @addtogroup caps_unredoext
    @brief  Defines the interface of the @a Undo/Redo Extension module.

    @{
*/

/** 
    @brief
    Callback signature for customized undo/redo operations.

    @param session
    Handle to the session within which the custom undo operation was added.
    This handle will be identical to the one passed as first argument to
    caps_addCustomUndoOperation().

    @param opData
    The custom operation data originally passed as argument to
    caps_addCustomUndoOperation(). This value is never referenced or altered by
    the system.

    @remarks
    This is the generic function signature for callback handlers used with
    custom undo operations. All custom undo events uses the same signature.

    @return
    If successful the event should return CERR_OK. Otherwise an appropriate 
    return code from the ::CRESULT enumeration.
*/
typedef CRESULT (*CustomUndoCallback )(CTSession session, void* opData);
//-----------------------------------------------------------------------------
/** 
    @brief 
    Adds a custom undo operation to the given session.

    @param session
    Handle to a valid session.

    @param onUndo
    Function address of a custom <i>undo</i> handler. This handler is invoked 
    when the CAPS base API function caps_undo() is called and the custom undo 
    operation is the next segment on the undo stack of the session. The handler
    function must be declared and used as described by the ::CustomUndoCallback
    documentation.
    
    @param onRedo
    Function address of a custom <i>redo</i> handler. This handler is invoked 
    when the function caps_redo() is called and the custom undo operation is 
    at the top of the redo stack. The operation is after the call moved back to
    the top of the undo stack. \n
    This handler function must be declared and used as described by the 
    ::CustomUndoCallback documentation.
    
    @param onRemoved
    Function address of the event callback invoked by the undo system when the
    custom <i>undo</i> operation is removed from the session. After this event
    has been called for a certain operation, no more callbacks will be invoked
    (until the operation is added again using caps_addCustomUndoOperation()).
    A custom undo operation is removed from the session as a consequence of the
    following actions:\n\n
    @li - When the session is destroyed and all operations are purged from the
        undo stack.
    @li - When an operation is located on the <i>redo</i> stack and a new 
        operation is executed and added to the <i>undo</i> stack (in which
          case all operations are purged from the <i>redo</i> stack).\n\n
    After a call to this handler the internal data associated with the
    operations is also cleaned up.
    This handler function must be declared and used as described by the 
    ::CustomUndoCallback documentation. However, result codes returned from 
    this particular event are ignored as it may be part of a shutdown sequence.
    
    @param opData
    A custom user value which is stored with the operation and is later passed
    as argument to the custom undo callbacks. This is commonly where the 
    operation data is stored. The value is never referenced or altered by the
    system.
    
    @remarks

    This function makes it possible to mix standard operations performed on a
    session with custom ones. When this function is called successfully, the
    operation is placed on the top of the undo stack and its event handlers are
    invoked when it is moved within or removed from the system.
        
    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @sa 
    caps_undo()\n
    caps_canUndo()\n

    @since 3.1
*/
SCBIMPORT CRESULT caps_addCustomUndoOperation( CTSession session, 
                                     CustomUndoCallback onUndo, 
                                     CustomUndoCallback onRedo,
                                     CustomUndoCallback onRemoved, 
                                     void* opData );
//-----------------------------------------------------------------------------
/**
    @since 3.1
*/
SCBIMPORT CRESULT caps_redo( CTSession session );
//-----------------------------------------------------------------------------
/**
    @}
*/ // end of addtogroup 'caps_unredoext'.
//-----------------------------------------------------------------------------


#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus

#endif      // !defined( CAPS_UREXT_H )
