/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2009 Scalado AB. All rights reserved.                           .
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

#ifndef CAPS_ITERATOR_H
#define CAPS_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"

//=============================================================================
/** 
    @ingroup caps_iterators
    @file caps_iterator.h
    @brief This header defines the public interface of the iterator in
    CAPS Base API.
*/
//=============================================================================
/**
    @addtogroup caps_iterators
    @brief
    Functions providing support for iterative (incremental) processing,
    via an @c CTIterator object.

    @{
*/
//-----------------------------------------------------------------------------

    /*
      The page 'iterative_operations' documentation block below is
       referenced from each render function in order to prevent duplication.
    */
    /**
        @page iterative_operations Iterative Operations

        If a valid iterator object pointer is passed to a render function, an
        iterative render operation is started, which means the operation has to
        be concluded by repetitively calling caps_doNextIteration() on the
        iterator.

        The following should be noted:
        - Overlapping iterative render operations are not allowed.
        - Undo calls are blocked until conclusion.
        - If an iterator object that operates against an open input stream is
        terminated early, using caps_destroyIterator(), the input stream
        may be left in a bad state. It can be restored by calling ctstream_abort(),
        and then ctstream_seek() to the beginning of the  stream. The output
        stream  must be recreated since data may have been permanently stored
        already.
        .
    */
//-----------------------------------------------------------------------------
/** 
    @brief 
    Generic function which performs the next iteration in a sequence.

    @param it
    Pointer to a @c CTIterator object which has been previously created as start
    of an iterative operation.

    @return 
    @c CERR_OK if the iteration was performed successfully and more iterations
    are pending. If no more iterations remain @c CRES_TASK_COMPLETE is returned.
    If none of the above values are returned an error has occurred which is
    described by the error code in itself.

    @code

    CTSession sess;
    CRESULT res = CERR_OK;
    CTSize dims = {1600, 1200};
    CTiterator* it = 0;

    res = caps_newSessionWithFile(_D("jpeg.jpg"), IMAGE_FORMAT_JPEG, &sess);
    res = caps_renderToFile(sess, _D("jpeg_out.jpg"), dims, 
    CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, &it);
    res = caps_doNextIteration(it);
    while (res == CERR_OK)
    {
    res = caps_doNextIteration(it);
    }
    caps_destroyIterator(it);
    caps_destroySession(sess);
    if (res != CRES_TASK_COMPLETE)
    {
    //An error code is returned
    HANDLE_ERROR(res);
    }

    @endcode

    @since 3.0

    @deprecated This function is deprecated since 5.3.
    Iterators will not be used in the future.
*/
SCBIMPORT CRESULT caps_doNextIteration( CTIterator* it );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Retrieves the number of iterations performed on an iterator so far.

    @param it
    Pointer to a @c CTIterator object which has been previously created as start
    of an iterative operation.

    @param count
    Address of @c CTuint32 variable which will receive the number of iterations 
    which, up to the point of this call, has been performed on the iterator.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_getCurIterationCount( const CTIterator* it, CTuint32* count );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Estimates how many iterations an operation is comprised of.

    @param it
    Pointer to a @c CTIterator object which has been previously created as start
    of an iterative operation.

    @param count
    Pointer to a @c CTuint32 variable which will receive the estimated number of 
    total iterations required to conclude the operation associated with the 
    iterator.

    @remarks

    Note that the estimation performed by this function is of the total 
    iterations required from start to finish to conclude the operation.
    \n\n
    The number of iterations reported by this function should be treated as
    nothing more than an estimation which may lack the accuracy requried
    for using it in certain contexts. 
    The accuracy of the estimation is mostly affected by the complexity of 
    the operation which the iterator reresents. When used for render operations
    the accuracy is in some cases undermined by the fact that the iteration
    count required to conclude the operation can change incrementally during
    its progress. 
    \n\n
    The iterations estimate is recommended to be used for progress reports 
    and/or time span estimations etc. Tasks like how many times to iterate
    over an operation should never be guided by the estimate returned from this
    function.

    @htmlonly 
    <p class=warning>- NOTE -<br>This function is currently not working for iterative Spmo generation.</p> 
    @endhtmlonly

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0
	
	@deprecated This function has been deprecated since 3.9.
*/
SCBIMPORT CRESULT caps_estimateIterationCount( CTIterator* it, CTuint32* count );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Retrieves auxillary data associated with the most recent iteration.

    @param it
    Pointer to a @c CTIterator object which has been previously created as start
    of an iterative operation.

    @param out_data
    Pointer to a @c CTuint32 variable which will receive the iteration
    data.

    @remarks

    This is an auxillary function provided for iterators to be used when 
    information of any kind needs to be communicated from the iterator back to 
    the user after performing an iteration. If a particular kind of operation
    will make use of this service, it is always noted in the documentation of
    the function initiating the operation and creating the iterator object.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.1

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_getIterationData( CTIterator* it, CTuint32* out_data );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Unconditionally aborts an iterative operation.

    @param it
    Pointer to a @c CTIterator object which has been previously created as start
    of an iterative operation.

    @remarks

    Calling this function on an iterator which already is "finished", or has 
    been aborted before, will be ignored without indication of an error.

    @return 
    @c CERR_OK if successful or a specific error code upon failure.

    @since 3.0

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT CRESULT caps_abortIterator( CTIterator* it );
//-----------------------------------------------------------------------------
/** 
    @brief 
    Destroys an iterator.

    @param it
    Pointer to a @c CTIterator object which has been previously created as start
    of an iterative operation.

    @remarks

    This function ignores whether or not the iterator is idle or currently
    associated with an operation.

    @since 3.0

    @deprecated This function is deprecated since 5.3.
*/
SCBIMPORT void caps_destroyIterator( CTIterator* it );
//-----------------------------------------------------------------------------
/**
    @}
*/
// end of addtogroup 'caps_iterators'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}           // extern "C"
#endif      // __cplusplus
#endif // CAPS_ITERATOR_H
