/******************************************************************************
 *                                                                            *
 *   © 2000-2010 Scalado AB. All rights reserved.                             *
 *                                                                            *
 *   Technologies used in this source code are patented or patent pending     *
 *   by Scalado AB Swedish Org. Number, 556594-6885.                          *
 *                                                                            *
 *   All Intellectual Property Rights related to this source code,            *
 *   belongs to Scalado AB.                                                   *
 *                                                                            *
 *   This source code is furnished under license agreement and may be used    *
 *   or copied only in accordance with terms of such license agreement.       *
 *                                                                            *
 *   Except as permitted by such license agreement, no part of this source    *
 *   code may be reproduced, stored in a retrieval system, or transmitted,    *
 *   in any form or by any means, electronic, mechanical, recording, or       *
 *   otherwise, without the prior written permission of Scalado.              *
 *                                                                            *
 *   Scalado assumes no responsibility or liability for any errors or         *
 *   inaccuracies in this source code or any consequential, incidental or     *
 *   indirect damage arising out of the use of this source code.              *
 *                                                                            *
 *   Scalado and the Scalado logo are either registered trademarks or         *
 *   trademarks of Scalado AB in Sweden and/or other countries.               *
 *                                                                            *
 ******************************************************************************/

#ifndef OSLTHREAD_H_
#define OSLTHREAD_H_

#include "scbdefs.h"
#include "scberror.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
/**
    @ingroup os_thread
    @file oslthread.h
    @brief Declares the virtual interface (used internally in CAPS), providing
    support for threads.
*/
//=============================================================================
/**
    @addtogroup os_thread
    @brief Mapping of basic OS thread functionality.

    These function declarations are found in the header file: @ref oslthread.h

    @{
*/
//-----------------------------------------------------------------------------

/**
    @brief
    The generic thread type. Can be used to create concurrent threads of
    execution.
 */
typedef struct CTThread CTThread;

/**
    @brief The generic mutex type. Provides a simple primitive for
    synchronization between cuncurrent threads.

    Only one thread can lock a mutex at a time, using @c ctmutex_lock. When a
    thread has finished its processing under the mutex lock it unlocks it using
    @c ctmutex_unlock and another thread can acquire the lock.

    @c CTMutex is non-recursive which means that the same thread cannot lock
    the same mutex two times.
*/
typedef struct CTMutex CTMutex;


/**
    @brief
    Generic reader writer lock type. One writer or multiple readers can own the lock.

    @c CTRWLock is non-recursive.

*/
typedef struct CTRWLock CTRWLock;

/**
    @brief The generic conditional variable type. Provides a simple primitive for
    conditional signaling between threads.
*/
typedef struct CTCond CTCond;

/**
    @brief
    Thread identifier. Each thread has an integer identifier from which the
    thread can be uniquely identified.
 */
typedef CTuint32 CTThreadId;

////////////////////////////////////////////////////////////////////////////////
// CTThread

/**
    @brief
    The user provided callback function acting as the entry point for
    the thread.

    @param pThread
    The CTThread object associated with the current (newly created) thread of
    execution.

    @param pUserData
    User defined context data passed to ctthread_create.
*/
typedef void (*CTThreadFunction)( CTThread *pThread, void *pUserData );

/**
    @brief
    Value representing an invalid thread identifer.
 */
#define OSLTHREAD_INVALID_THREAD_ID ((CTThreadId)0)

/**
    @brief
    Creates and starts a new thread with an associated CTThread object.

    @param callback
    Entry point for the created thread. "Thread-main".

    @param pUserData
    User defined context data to pass on to the entry point of the thread.
    Optional.

    @param ppThread
    The created thread. 0 on failure.

    @return
    - @c CERR_OK on success.
    - @c CERR_MEMALLOC_FAILED on failure to allocate memory.
    - @c CERR_CONSTRUCTION_FAILED if the thread could not be spawned.
    - @c CERR_INVALID_PARAMETER if the function was called with an illegal
         parameter value.
    .

    @sa
    ctthread_destroy
*/
CRESULT ctthread_create( CTThreadFunction callback,
                         void *pUserData,
                         CTThread **ppThread );

/**
    @brief
    Destroys a CTThread object.

    @param pThread
    CTThread object to destroy.

    @sa
    ctthread_create
    ctthread_join

    @remark
    Must not be called until the thread has finished.
*/
void ctthread_destroy( CTThread *pThread );

/**
    @brief
    Retrieves the unique identifier of the current thread.

    @return
    The unique identifier of the calling thread.

    @sa
    ctthread_id
 */
CTThreadId ctthread_currentThreadId( void );

/**
    @brief
    Retrieves the unique identifier of the thread associated with the specified
    CTThread object.

    @param pThread
    The thread to query for the id.

    @return
    The unique identifier associated with pThread or
    OSLTHREAD_INVALID_THREAD_ID.

    @sa
    ctthread_currentThreadId
*/
CTThreadId ctthread_id( CTThread *pThread );

/**
    @brief
    Checks if a thread is running.

    @param pThread
    The thread to check.

    @return
    true if the thread is running or false otherwise.
*/
CTbool ctthread_running( CTThread *pThread );

/**
    @brief
    Makes the calling thread wait for the thread associated with pThread to finish.

    @param pThread
    The thread to wait for.

    @return
    - @c CERR_OK on success.
    - @c CERR_OPERATION_FAILED if the thread could not be joined.
    - @c CERR_INVALID_PARAMETER if the function was called with an illegal
         parameter value.
    .
*/
CRESULT ctthread_join( CTThread *pThread );

/**
    @brief
    Makes the calling thread sleep for a specific amount of time.

    @param ms
    Number of milliseconds to sleep.
*/
void ctthread_sleep( CTuint32 ms );

/**
    @brief
    Makes ctthread_interruptRequested return true the next time it is called.

    @param pThread
    The thread to interrupt.

    @sa
    ctthread_interruptRequested
*/
void ctthread_interrupt( CTThread *pThread );

/**
    @brief
    Checks wether a request has been made to interrupt the thread associated
    with pThread.

    @param pThread
    The thread to check for interruption requests.

    @return
    - @c true if a request has been made to interrupt the thread.
    - @c false if no request has been made to interrupt the thread.
    .

    @remark
    This is not a typical get function. It is defined to return true if an
    interrupt request has been made, but it will be reset so that it returns
    false until ctthread_interrupt is called again.

    @code
    // Thread 1
    if ( ctthread_joinable( pThread 2 ) )
    {
        ctthread_interrupt( pThread2 );
        ctthread_join( pThread2 );
    }

    // Thread 2
    while ( !ctthread_interruptRequested( pThread2 ) && !workDone )
    {
        workDone = work(...);
    }
    @endcode

    @sa
    ctthread_interrupt
    ctthread_joinable
    ctthread_join
*/
CTbool ctthread_interruptRequested( CTThread *pThread );

////////////////////////////////////////////////////////////////////////////////
// CTMutex

/**
    @brief
    Creates a mutex.

    @param ppMutex [out] Double pointer to a @c CTMutex that will be created.
           Can not be null.

    @return
    - @c CERR_OK on success.
    - @c CERR_MEMALLOC_FAILED on failure.
    - @c CERR_INVALID_PARAMETER if the function was called with an illegal
         parameter value.
    .
 */
CRESULT ctmutex_create( CTMutex **ppMutex );


/**
    @brief
    Destroys a mutex and frees any internal resources held by the mutex.

    @param pMutex Pointer to the @c CTMutex object to destroy.
 */
void ctmutex_destroy( CTMutex *pMutex );


/**
    @brief
    The calling thread obtains a lock of a mutex.

    If no other thread has locked the mutex, the lock is obtained immediately.
    If another thread already has ownership of the lock, the function waits
    until the owning thread unlocks the mutex and the lock can be obtained
    by the calling thread.

    @remark
    A thread shall not attempt to lock the same mutex more than one time
    (without unlocking it in between). Doing so may result in undefined behavior.

    @param pMutex Pointer to the @c CTMutex object to lock. Must not be null.
 */
void ctmutex_lock( CTMutex *pMutex );


/**
    @brief
    The calling thread tries to obtain a lock of the mutex.

    If no other thread has locked the mutex, the lock is obtained immediately.
    If another thread already has ownership of the lock, the function
    immediately retrurns, indicating that the lock could not be obtained by
    the calling thread.

    @param pMutex Pointer to the @c CTMutex object to try to lock.
           Must not be null.

    @return
    - @c true if the lock was obtained.
    - @c false if the calling thread failed to obtain the lock. The lock is
         owned by another thread.
    .
 */
CTbool ctmutex_tryLock( CTMutex *pMutex );


/**
    @brief
    The calling thread unlocks the mutex and makes it available for locking
    by other threads.

    @param pMutex Pointer to the @c CTMutex object to unlock. Must not be null.
 */
void ctmutex_unlock( CTMutex *pMutex );

////////////////////////////////////////////////////////////////////////////////
// CTRWLock

/**
    @brief
    Creates a reader-writer lock. A reader-writer lock allows multiple read locks
    at the same time but only a single write lock.

    @param ppRWLock [out] Double pointer to a @c CTRWLock that will be created.
           Can not be null.

    @return
    - @c CERR_OK on success.
    - @c CERR_MEMALLOC_FAILED on failure.
    - @c CERR_INVALID_PARAMETER if the function was called with an illegal
         parameter value.
    .
 */
CRESULT ctrwlock_create( CTRWLock **ppRWLock );


/**
    @brief
    Destroys a reader-writer lock and frees any internal resources held by the lock.

    @param pRWLock Pointer to the @c CTRWLock object to destroy.
 */
void ctrwlock_destroy( CTRWLock *pRWLock );


/**
    @brief
    The calling thread obtains a read lock.

    If no other thread has a write lock, the read lock is obtained immediately.
    If another thread already has a write lock, the function waits
    until the owning thread unlocks the write-lock and the read lock can be obtained
    by the calling thread.

    @remark
    A thread shall not attempt to lock the same rwlock more than one time
    (without unlocking it in between). Doing so may result in undefined behavior.

    @param pRWLock Pointer to the @c CTRWLock object to lock. Must not be null.
 */
void ctrwlock_readerLock( CTRWLock *pRWLock );


/**
    @brief
    The calling thread tries to obtain a read lock of a reader-writer lock.

    If no other thread has a write lock, the read lock is obtained immediately.
    If another thread already has a write lock, the function returns immediately,
    indicating that the lock could not be obtained by the calling thread.

    @remark
    A thread shall not attempt to lock the same rwlock more than one time
    (without unlocking it in between). Doing so may result in undefined behavior.

    @param pRWLock Pointer to the @c CTRWLock object to try to lock. Must not be null.

    @return
    - @c true if the lock was obtained.
    - @c false if the calling thread failed to obtain the lock. The lock is
         owned by another thread.
    .
 */
CTbool ctrwlock_readerTryLock( CTRWLock *pRWLock );


/**
    @brief
    The calling thread unlocks the reader lock and makes the rwlock available for locking
    by other threads.

    @param pRWLock Pointer to the @c CTRWLock object to unlock. Must not be null.
 */
void ctrwlock_readerUnlock( CTRWLock *pRWLock );

/**
    @brief
    The calling thread obtains a write lock.

    If no other thread has a write or read lock, the write lock is obtained immediately.
    If another thread already has a write or read lock, the function waits
    until all owning threads has unlocked and the write lock can be obtained
    by the calling thread.

    @remark
    A thread shall not attempt to lock the same rwlock more than one time
    (without unlocking it in between). Doing so may result in undefined behavior.

    @param pRWLock Pointer to the @c CTRWLock object to lock. Must not be null.
 */
void ctrwlock_writerLock( CTRWLock *pRWLock );


/**
    @brief
    The calling thread tries to obtain a write lock.

    If no other thread has a write or read lock, the write lock is obtained immediately.
    If another thread already has a write or read lock, the function returns immediately,
    indicating that the lock could not be obtained by the calling thread.

    @remark
    A thread shall not attempt to lock the same rwlock more than one time
    (without unlocking it in between). Doing so may result in undefined behavior.

    @param pRWLock Pointer to the @c CTRWLock object to try to lock. Must not be null.

    @return
    - @c true if the lock was obtained.
    - @c false if the calling thread failed to obtain the lock. The lock is
         owned by another thread.
    .
 */
CTbool ctrwlock_writerTryLock( CTRWLock *pRWLock );


/**
    @brief
    The calling thread unlocks the write lock and makes the rwlock available for locking
    by other threads.

    @param pRWLock Pointer to the @c CTRWLock object to unlock. Must not be null.
 */
void ctrwlock_writerUnlock( CTRWLock *pRWLock );

////////////////////////////////////////////////////////////////////////////////
// CTCond

/**
    @brief
    Creates a conditional variable.

    @param ppCond [out] Double pointer to a @c CTCond that will be created.
           Can not be null.

    @return
    - @c CERR_OK on success.
    - @c CERR_MEMALLOC_FAILED on failure.
    - @c CERR_INVALID_PARAMETER if the function was called with an illegal
         parameter value.
    .
 */
CRESULT ctcond_create( CTCond **ppCond );


/**
    @brief
    Destroys a conditional variable and frees any internal resources held by it.

    @param pCond Pointer to the @c CTCond object to destroy.
 */
void ctcond_destroy( CTCond *pCond );


/**
    @brief
    The calling thread waits for a signal to continue execution.

    @param pCond Pointer to the @c CTCond object to wait for. Must not be null.
 */
void ctcond_wait( CTCond *pCond );


/**
    @brief
    The calling thread signals the conditional variable and lets waiting threads execute.

    @param pCond Pointer to the @c CTCond object to signal. Must not be null.
 */
void ctcond_signal( CTCond *pCond );


/**
    @}
*/ // end addtogroup 'os_thread'.
//-----------------------------------------------------------------------------

#ifdef __cplusplus
} // extern "C"
#endif

#endif //OSLTHREAD_H_
