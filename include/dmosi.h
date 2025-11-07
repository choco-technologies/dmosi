#ifndef DMOSI_H
#define DMOSI_H

#include "dmod.h"


DMOD_BUILTIN_API( dmosi, 1.0, bool, _init,   (void) );
DMOD_BUILTIN_API( dmosi, 1.0, bool, _deinit, (void) );

//==============================================================================
//                              MUTEX API
//==============================================================================

/**
 * @brief Opaque type for mutex
 *
 * This type represents a mutex in the DMOD OSI system.
 *
 * @note The actual implementation of the mutex is hidden
 * from the user and is specific to the underlying OS.
 */
typedef struct dmosi_mutex* dmosi_mutex_t;

/**
 * @defgroup DMOSI_MUTEX_API Mutex API
 * @brief API for mutex operations in DMOD OSI
 *
 * This API provides functions to create, destroy, lock, and unlock mutexes.
 * @{
 */
/**
 * @brief Create a mutex
 *
 * @param recursive Whether the mutex should be recursive
 *
 * @return dmosi_mutex_t Created mutex handle
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_mutex_t, _mutex_create,    (bool recursive) );

/**
 * @brief Destroy a mutex
 *
 * @param mutex Mutex handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,          _mutex_destroy,   (dmosi_mutex_t mutex) );

/**
 * @brief Lock a mutex
 *
 * @param mutex Mutex handle to lock
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _mutex_lock,      (dmosi_mutex_t mutex) );

/**
 * @brief Unlock a mutex
 *
 * @param mutex Mutex handle to unlock
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _mutex_unlock,    (dmosi_mutex_t mutex) );

/** @} */ // end of DMOSI_MUTEX_API

//==============================================================================
//                              Process API
//==============================================================================
/**
 * @defgroup DMOSI_PROCESS_API Process API
 * @brief API for process operations in DMOD OSI
 * This API provides functions to create and manage processes.
 * @{
 */

/**
 * @brief Opaque type for process
 *
 * This type represents a process in the DMOD OSI system.
 * @note The actual implementation of the process is hidden
 * from the user and is specific to the underlying OS.
 */
typedef struct dmod_process* dmod_process_t;

/** @} */ // end of DMOSI_PROCESS_API

//==============================================================================
//                              Thread API
//==============================================================================
/**
 * @defgroup DMOSI_THREAD_API Thread API
 * @brief API for thread operations in DMOD OSI
 * This API provides functions to create and manage threads.
 * @{
 */

/**
 * @brief Opaque type for thread
 *
 * This type represents a thread in the DMOD OSI system.
 *
 * @note The actual implementation of the thread is hidden
 * from the user and is specific to the underlying OS.
 */
typedef struct dmod_thread* dmod_thread_t;


/** @} */ // end of DMOSI_THREAD_API

#endif // DMOSI_H
