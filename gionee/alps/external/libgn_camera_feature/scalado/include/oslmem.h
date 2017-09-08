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

#ifndef OSLMEM_H
#define OSLMEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"

//=============================================================================
/**
    @ingroup os_memory
    @file oslmem.h
    @brief Declares the virtual interface (used internally in CAPS), providing
    support for memory management.
*/
//=============================================================================
/** 
    @addtogroup os_memory
    @brief Mapping of basic OS memory functionality.

    These function declarations are found in the header file: oslmem.h

    @{
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

#ifdef SCB_DBGMODE_MEMORY

#include "scbdbg.h"

// Memory debugging mode.
// Define allocation and free macros which actually references the debugging
// versions in the scbdbg library. Note that this redefinition only concerns
// the prototype declarations. Implementations of the regular functions are
// still present and available for link-time dependencies.

#ifndef oslmem_alloc
#define oslmem_alloc( /* CTuint32 */ size ) dbg_mdaAlloc( size, (const DCHAR*)__SCB_THISFILE__ , __LINE__ )
#endif

#ifndef oslmem_free
#define oslmem_free( /* void* */ p ) dbg_mdaFree( p )
#endif

#else // SCB_DBGMODE_MEMORY not defined

// No memory debugging mode, simply declare the ordinary allocation functions.

//-----------------------------------------------------------------------------
/**
    @brief
    Allocates memory from the heap.

    @param size Size in bytes of the memory to be allocated.

    @return A pointer to the allocated memory if succesful, or zero if the 
            allocation failed.
*/
void* oslmem_alloc( CTuint32 size );
//-----------------------------------------------------------------------------
/**
    @brief
    Frees a previously allocated block of memory.

    @param p Address of the memory to free. Can be zero.
*/
void oslmem_free( void*  p );
//-----------------------------------------------------------------------------

#endif

//-----------------------------------------------------------------------------
/**
    Allocates and reset memory from the heap.
    
    @param size Amount in bytes of the size of the object.
    @param ppObject Pointer where the object will be allocated.
    
    @return CERR_OK if no errors, CERR_MEMALLOC_FAILED otherwise.
 
    @note This function is implemented by Scalado, and does not need to be 
    implemented as part of the osil integration efforts.
    
*/
#ifdef SCB_DBGMODE_MEMORY
#define oslmem_allocReset( /* CTuint32 */ size, /* void** */ppObject ) dbg_mdaAllocReset( size, ppObject,(const DCHAR*)__SCB_THISFILE__ , __LINE__ )
#else
CRESULT oslmem_allocReset ( CTuint32 size, void **ppObject );
#endif


//-----------------------------------------------------------------------------

    
#if 1
#define oslmem_typedAlloc( type ) ( (type*) oslmem_alloc( sizeof(type) ) )
#else
/**
    @brief MACRO Allocates memory for the given type.

    @param type Type for which to allocate memory for.
    
    @remarks
    
    This function is currently implemented as a macro:
    
    <b><tt>( (type*) oslmem_alloc( sizeof(type) ) )</tt></b>
    
    Example usage:
    
    @code
    // Allocate memory for a CTint
    
    CTint32* p = oslmem_typedAlloc( CTint32 );
    oslmem_free( p );
    
    @endcode
    
    @return Address to the allocated memory of size \c sizeof(type).
*/
type* oslmem_typedAlloc( type ); Trick doxygen into generating doc for the above macro.
//-----------------------------------------------------------------------------
#endif

#define oslmem_arrayAlloc( type, size ) ((type*) oslmem_alloc( sizeof(type) * (size) ))







#include <string.h>
    
#define oslmem_copy( dest, src, length ) \
        memcpy( (dest), (src), (length) );
    
#define oslmem_move( dest, src, length ) \
        memmove( (dest), (src), (length) );
    
#define oslmem_reset( dest, length ) \
        oslmem_fill8( dest, 0, length );
    
#define oslmem_fill8( dest, value, length ) \
        memset( (dest), (value), (length) );
    
#define oslmem_compare( src1, src2, length ) \
        memcmp( (src1), (src2), (length) )
    

    
    
    
//-----------------------------------------------------------------------------
/**
    @}
*/ // end addtogroup 'os_memory'.
//-----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif // !defined( OSLMEM_H )
