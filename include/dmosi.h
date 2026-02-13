#ifndef DMOSI_H
#define DMOSI_H

#include "dmod.h"

/**
 * @brief String used as the module name for the system allocations
 */
#define DMOSI_SYSTEM_MODULE_NAME    "system"

//==============================================================================
//                              Initialization API
//==============================================================================

/**
 * @brief Initialize the DMOD OSI system
 *
 * This function initializes the DMOD OSI system and must be called before
 * using any other DMOD OSI APIs.
 *
 * @return bool true on successful initialization, false on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, bool, _init,   (void) );

/**
 * @brief Deinitialize the DMOD OSI system
 *
 * This function deinitializes the DMOD OSI system and should be called when
 * the system is no longer needed. After calling this function, no other DMOD
 * OSI APIs should be used until _init is called again.
 *
 * @return bool true on successful deinitialization, false on failure
 */
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
//                              Forward declarations
//==============================================================================
/**
 * @brief Forward declaration for thread type
 *
 * This forward declaration allows Process API to reference threads
 * before the Thread API section.
 */
typedef struct dmod_thread* dmod_thread_t;

//==============================================================================
//                              Process API
//==============================================================================
/**
 * @defgroup DMOSI_PROCESS_API Process API
 * @brief API for process operations in DMOD OSI
 *
 * Processes are containers for threads. This API provides functions to create
 * and manage processes, including state management, thread management, and
 * process identification.
 * @{
 */

/**
 * @brief Opaque type for process
 *
 * This type represents a process in the DMOD OSI system.
 * A process is a container for threads and has its own state, ID, and properties.
 *
 * @note The actual implementation of the process is hidden
 * from the user and is specific to the underlying OS.
 */
typedef struct dmod_process* dmod_process_t;

/**
 * @brief Process ID type
 */
typedef uint32_t dmod_process_id_t;

/**
 * @brief User ID type
 */
typedef uint32_t dmod_user_id_t;

/**
 * @brief Process state enumeration
 */
typedef enum {
    DMOSI_PROCESS_STATE_CREATED,    /**< Process created but not started */
    DMOSI_PROCESS_STATE_RUNNING,    /**< Process is running */
    DMOSI_PROCESS_STATE_SUSPENDED,  /**< Process is suspended */
    DMOSI_PROCESS_STATE_TERMINATED, /**< Process has terminated */
    DMOSI_PROCESS_STATE_ZOMBIE      /**< Process terminated but not cleaned up */
} dmod_process_state_t;

/**
 * @brief Create a process
 *
 * Creates a new process container. The process is a container for threads.
 *
 * @param name Name of the process (can be NULL)
 * @param parent Parent process (can be NULL for detached processes)
 * @return dmod_process_t Created process handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_t, _process_create,    (const char* name, dmod_process_t parent) );

/**
 * @brief Destroy a process
 *
 * @param process Process handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,           _process_destroy,   (dmod_process_t process) );

/**
 * @brief Kill a process
 *
 * Forcefully terminate a process and all its threads.
 *
 * @param process Process handle to kill
 * @param status Exit status code
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_kill,      (dmod_process_t process, int status) );

/**
 * @brief Wait for a process to terminate
 *
 * @param process Process handle to wait for
 * @param timeout_ms Timeout in milliseconds (0 = no wait, -1 = wait forever)
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_wait,      (dmod_process_t process, int32_t timeout_ms) );

/**
 * @brief Get current process
 *
 * @return dmod_process_t Current process handle
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_t, _process_current,   (void) );

/**
 * @brief Set current process
 *
 * @param process Process handle to set as current
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_current, (dmod_process_t process) );

/**
 * @brief Get process state
 *
 * @param process Process handle
 * @return dmod_process_state_t Current state of the process
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_state_t, _process_get_state, (dmod_process_t process) );

/**
 * @brief Get process ID
 *
 * @param process Process handle
 * @return dmod_process_id_t Process ID, 0 on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_id_t, _process_get_id, (dmod_process_t process) );

/**
 * @brief Set process ID
 *
 * @param process Process handle
 * @param pid Process ID to set
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_id,    (dmod_process_t process, dmod_process_id_t pid) );

/**
 * @brief Get process name
 *
 * @param process Process handle
 * @return const char* Process name, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,    _process_get_name,  (dmod_process_t process) );

/**
 * @brief Set process user ID
 *
 * @param process Process handle
 * @param uid User ID to set
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_uid,   (dmod_process_t process, dmod_user_id_t uid) );

/**
 * @brief Get process user ID
 *
 * @param process Process handle
 * @return dmod_user_id_t User ID, 0 on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_user_id_t, _process_get_uid,   (dmod_process_t process) );

/**
 * @brief Set process working directory (pwd)
 *
 * @param process Process handle
 * @param pwd Working directory path
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_pwd,   (dmod_process_t process, const char* pwd) );

/**
 * @brief Get process working directory (pwd)
 *
 * @param process Process handle
 * @return const char* Working directory path, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,    _process_get_pwd,   (dmod_process_t process) );

/**
 * @brief Find a process by name
 *
 * @param name Process name to search for
 * @return dmod_process_t Process handle, NULL if not found
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_t, _process_find_by_name, (const char* name) );

/**
 * @brief Find a process by process ID
 *
 * @param pid Process ID to search for
 * @return dmod_process_t Process handle, NULL if not found
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_t, _process_find_by_id,   (dmod_process_id_t pid) );

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
 * @brief Thread entry function type
 *
 * This is the signature for thread entry functions. The function receives
 * a user-provided argument.
 *
 * @param arg User-provided argument passed to the thread
 */
typedef void (*dmod_thread_entry_t)(void* arg);

/**
 * @brief Create a thread
 *
 * @param entry Entry function for the thread
 * @param arg Argument to pass to the entry function
 * @param priority Thread priority
 * @param stack_size Stack size for the thread
 * @param name              Name of the thread (cannot be NULL)
 * @param module_name       Name of the module creating the thread (for tracking allocations)
 * @param process           Process to associate the thread with (NULL = current process)
 * @return dmod_thread_t Created thread handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_thread_t, _thread_create,    (dmod_thread_entry_t entry, void* arg, int priority, size_t stack_size, const char* name, const char* module_name, dmod_process_t process) );

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

/**
 * @brief Get thread name
 *
 * @param thread Thread handle (if NULL, returns name of current thread)
 * @return const char* Thread name, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,   _thread_get_name,  (dmod_thread_t thread) );

/**
 * @brief Get thread module name
 *
 * @param thread Thread handle (if NULL, returns module name of current thread)
 * @return const char* Module name that created the thread, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,  _thread_get_module_name,  (dmod_thread_t thread) );

/**
 * @brief Get thread priority
 *
 * @param thread Thread handle (if NULL, returns priority of current thread)
 * @return int Thread priority, or 0 on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,  _thread_get_priority,  (dmod_thread_t thread) );

/**
 * @brief Get thread's associated process
 *
 * @param thread Thread handle (if NULL, returns process of current thread)
 * @return dmod_process_t Process handle that the thread belongs to, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmod_process_t, _thread_get_process, (dmod_thread_t thread) );

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

/**
 * @brief Change timer period
 *
 * @param timer Timer handle
 * @param period_ms New timer period in milliseconds
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _timer_set_period, (dmosi_timer_t timer, uint32_t period_ms) );

/**
 * @brief Get timer period
 *
 * @param timer Timer handle
 * @return uint32_t Timer period in milliseconds, 0 on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, uint32_t,      _timer_get_period, (dmosi_timer_t timer) );

/** @} */ // end of DMOSI_TIMER_API

#endif // DMOSI_H
