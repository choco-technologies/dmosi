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

/**
 * @brief Create a process
 *
 * @param entry Entry function for the process
 * @param arg Argument to pass to the entry function
 * @param priority Process priority
 * @return dmod_process_t Created process handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_t, _process_create,    (void (*entry)(void*), void* arg, int priority) );

/**
 * @brief Destroy a process
 *
 * @param process Process handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,           _process_destroy,   (dmod_process_t process) );

/**
 * @brief Get current process
 *
 * @return dmod_process_t Current process handle
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_t, _process_current,   (void) );

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

/**
 * @brief Create a thread
 *
 * @param entry Entry function for the thread
 * @param arg Argument to pass to the entry function
 * @param priority Thread priority
 * @param stack_size Stack size for the thread
 * @return dmod_thread_t Created thread handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_thread_t, _thread_create,    (void (*entry)(void*), void* arg, int priority, size_t stack_size) );

/**
 * @brief Destroy a thread
 *
 * @param thread Thread handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,          _thread_destroy,   (dmod_thread_t thread) );

/**
 * @brief Join a thread (wait for it to finish)
 *
 * @param thread Thread handle to join
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _thread_join,      (dmod_thread_t thread) );

/**
 * @brief Get current thread
 *
 * @return dmod_thread_t Current thread handle
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_thread_t, _thread_current,   (void) );

/**
 * @brief Sleep for a specified time in milliseconds
 *
 * @param ms Time to sleep in milliseconds
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,          _thread_sleep,     (uint32_t ms) );

/** @} */ // end of DMOSI_THREAD_API

//==============================================================================
//                              Semaphore API
//==============================================================================
/**
 * @defgroup DMOSI_SEMAPHORE_API Semaphore API
 * @brief API for semaphore operations in DMOD OSI
 * This API provides functions to create, destroy, and use semaphores.
 * @{
 */

/**
 * @brief Opaque type for semaphore
 *
 * This type represents a semaphore in the DMOD OSI system.
 *
 * @note The actual implementation of the semaphore is hidden
 * from the user and is specific to the underlying OS.
 */
typedef struct dmosi_semaphore* dmosi_semaphore_t;

/**
 * @brief Create a semaphore
 *
 * @param initial_count Initial count for the semaphore
 * @param max_count Maximum count for the semaphore
 * @return dmosi_semaphore_t Created semaphore handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_semaphore_t, _semaphore_create,  (uint32_t initial_count, uint32_t max_count) );

/**
 * @brief Destroy a semaphore
 *
 * @param semaphore Semaphore handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,              _semaphore_destroy, (dmosi_semaphore_t semaphore) );

/**
 * @brief Wait on a semaphore (decrement)
 *
 * @param semaphore Semaphore handle
 * @param timeout_ms Timeout in milliseconds (0 = no wait, -1 = wait forever)
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,               _semaphore_wait,    (dmosi_semaphore_t semaphore, int32_t timeout_ms) );

/**
 * @brief Post to a semaphore (increment)
 *
 * @param semaphore Semaphore handle
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,               _semaphore_post,    (dmosi_semaphore_t semaphore) );

/** @} */ // end of DMOSI_SEMAPHORE_API

//==============================================================================
//                              Queue API
//==============================================================================
/**
 * @defgroup DMOSI_QUEUE_API Queue API
 * @brief API for queue operations in DMOD OSI
 * This API provides functions to create, destroy, and use queues.
 * @{
 */

/**
 * @brief Opaque type for queue
 *
 * This type represents a queue in the DMOD OSI system.
 *
 * @note The actual implementation of the queue is hidden
 * from the user and is specific to the underlying OS.
 */
typedef struct dmosi_queue* dmosi_queue_t;

/**
 * @brief Create a queue
 *
 * @param item_size Size of each item in the queue
 * @param queue_length Maximum number of items in the queue
 * @return dmosi_queue_t Created queue handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_queue_t, _queue_create,  (size_t item_size, uint32_t queue_length) );

/**
 * @brief Destroy a queue
 *
 * @param queue Queue handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,          _queue_destroy, (dmosi_queue_t queue) );

/**
 * @brief Send data to a queue
 *
 * @param queue Queue handle
 * @param item Pointer to the item to send
 * @param timeout_ms Timeout in milliseconds (0 = no wait, -1 = wait forever)
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _queue_send,    (dmosi_queue_t queue, const void* item, int32_t timeout_ms) );

/**
 * @brief Receive data from a queue
 *
 * @param queue Queue handle
 * @param item Pointer to buffer to receive the item
 * @param timeout_ms Timeout in milliseconds (0 = no wait, -1 = wait forever)
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _queue_receive, (dmosi_queue_t queue, void* item, int32_t timeout_ms) );

/** @} */ // end of DMOSI_QUEUE_API

//==============================================================================
//                              Timer API
//==============================================================================
/**
 * @defgroup DMOSI_TIMER_API Timer API
 * @brief API for timer operations in DMOD OSI
 * This API provides functions to create, destroy, and use timers.
 * @{
 */

/**
 * @brief Opaque type for timer
 *
 * This type represents a timer in the DMOD OSI system.
 *
 * @note The actual implementation of the timer is hidden
 * from the user and is specific to the underlying OS.
 */
typedef struct dmosi_timer* dmosi_timer_t;

/**
 * @brief Timer callback function type
 * 
 * This callback is invoked when the timer expires. For auto-reload timers,
 * it is called periodically at the specified interval. For one-shot timers,
 * it is called once when the timer expires.
 * 
 * @param arg User-provided argument passed to the callback
 * 
 * @note The callback is typically executed in timer/interrupt context.
 *       Keep the callback short and avoid blocking operations.
 */
typedef void (*dmosi_timer_callback_t)(void* arg);

/**
 * @brief Create a timer
 *
 * @param callback Callback function to execute when timer expires
 * @param arg Argument to pass to the callback function
 * @param period_ms Timer period in milliseconds
 * @param auto_reload Whether the timer should auto-reload
 * @return dmosi_timer_t Created timer handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_timer_t, _timer_create,  (dmosi_timer_callback_t callback, void* arg, uint32_t period_ms, bool auto_reload) );

/**
 * @brief Destroy a timer
 *
 * @param timer Timer handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,          _timer_destroy, (dmosi_timer_t timer) );

/**
 * @brief Start a timer
 *
 * @param timer Timer handle to start
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _timer_start,   (dmosi_timer_t timer) );

/**
 * @brief Stop a timer
 *
 * @param timer Timer handle to stop
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _timer_stop,    (dmosi_timer_t timer) );

/**
 * @brief Reset a timer
 *
 * @param timer Timer handle to reset
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _timer_reset,   (dmosi_timer_t timer) );

/** @} */ // end of DMOSI_TIMER_API

#endif // DMOSI_H
