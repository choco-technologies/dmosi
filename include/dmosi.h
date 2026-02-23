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
typedef struct dmosi_thread* dmosi_thread_t;

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
typedef struct dmosi_process* dmosi_process_t;

/**
 * @brief Process ID type
 */
typedef uint32_t dmosi_process_id_t;

/**
 * @brief User ID type
 */
typedef uint32_t dmosi_user_id_t;

/**
 * @brief Process state enumeration
 */
typedef enum {
    DMOSI_PROCESS_STATE_CREATED,    /**< Process created but not started */
    DMOSI_PROCESS_STATE_RUNNING,    /**< Process is running */
    DMOSI_PROCESS_STATE_SUSPENDED,  /**< Process is suspended */
    DMOSI_PROCESS_STATE_TERMINATED, /**< Process has terminated */
    DMOSI_PROCESS_STATE_ZOMBIE      /**< Process terminated but not cleaned up */
} dmosi_process_state_t;

/**
 * @brief Create a process
 *
 * Creates a new process container. The process is a container for threads.
 *
 * @param name Name of the process (can be NULL)
 * @param module_name Module name to associate with the process (can be NULL)
 * @param parent Parent process (can be NULL for detached processes)
 * @return dmosi_process_t Created process handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_t, _process_create,    (const char* name, const char* module_name, dmosi_process_t parent) );

/**
 * @brief Destroy a process
 *
 * @param process Process handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,           _process_destroy,   (dmosi_process_t process) );

/**
 * @brief Kill a process
 *
 * Forcefully terminate a process and all its threads.
 *
 * @param process Process handle to kill
 * @param status Exit status code
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_kill,      (dmosi_process_t process, int status) );

/**
 * @brief Wait for a process to terminate
 *
 * @param process Process handle to wait for
 * @param timeout_ms Timeout in milliseconds (0 = no wait, -1 = wait forever)
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_wait,      (dmosi_process_t process, int32_t timeout_ms) );

/**
 * @brief Get current process
 *
 * @return dmosi_process_t Current process handle
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_t, _process_current,   (void) );

/**
 * @brief Set current process
 *
 * @param process Process handle to set as current
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_current, (dmosi_process_t process) );

/**
 * @brief Get process state
 *
 * @param process Process handle
 * @return dmosi_process_state_t Current state of the process
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_state_t, _process_get_state, (dmosi_process_t process) );

/**
 * @brief Get process ID
 *
 * @param process Process handle
 * @return dmosi_process_id_t Process ID, 0 on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_id_t, _process_get_id, (dmosi_process_t process) );

/**
 * @brief Set process ID
 *
 * @param process Process handle
 * @param pid Process ID to set
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_id,    (dmosi_process_t process, dmosi_process_id_t pid) );

/**
 * @brief Get process name
 *
 * @param process Process handle
 * @return const char* Process name, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,    _process_get_name,  (dmosi_process_t process) );

/**
 * @brief Get process module name
 *
 * @param process Process handle
 * @return const char* Module name associated with the process, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,    _process_get_module_name, (dmosi_process_t process) );

/**
 * @brief Set process module name
 *
 * @param process Process handle
 * @param module_name Module name to associate with the process
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_module_name, (dmosi_process_t process, const char* module_name) );

/**
 * @brief Set process user ID
 *
 * @param process Process handle
 * @param uid User ID to set
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_uid,   (dmosi_process_t process, dmosi_user_id_t uid) );

/**
 * @brief Get process user ID
 *
 * @param process Process handle
 * @return dmosi_user_id_t User ID, 0 on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_user_id_t, _process_get_uid,   (dmosi_process_t process) );

/**
 * @brief Set process working directory (pwd)
 *
 * @param process Process handle
 * @param pwd Working directory path
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_pwd,   (dmosi_process_t process, const char* pwd) );

/**
 * @brief Get process working directory (pwd)
 *
 * @param process Process handle
 * @return const char* Working directory path, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,    _process_get_pwd,   (dmosi_process_t process) );

/**
 * @brief Find a process by name
 *
 * @param name Process name to search for
 * @return dmosi_process_t Process handle, NULL if not found
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_t, _process_find_by_name, (const char* name) );

/**
 * @brief Find a process by process ID
 *
 * @param pid Process ID to search for
 * @return dmosi_process_t Process handle, NULL if not found
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_t, _process_find_by_id,   (dmosi_process_id_t pid) );

/**
 * @brief Get process exit status
 *
 * @param process Process handle
 * @return int Exit status of the process
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_get_exit_status, (dmosi_process_t process) );

/**
 * @brief Set process exit status
 *
 * @param process Process handle
 * @param exit_status Exit status to set
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,            _process_set_exit_status, (dmosi_process_t process, int exit_status) );

/**
 * @brief Get process parent
 *
 * @param process Process handle
 * @return dmosi_process_t Parent process handle, NULL if no parent
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_t, _process_get_parent, (dmosi_process_t process) );

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
typedef void (*dmosi_thread_entry_t)(void* arg);

/**
 * @brief Thread state enumeration
 */
typedef enum {
    DMOSI_THREAD_STATE_CREATED,     /**< Thread created but not started */
    DMOSI_THREAD_STATE_READY,       /**< Thread is ready to run */
    DMOSI_THREAD_STATE_RUNNING,     /**< Thread is currently running */
    DMOSI_THREAD_STATE_BLOCKED,     /**< Thread is blocked (waiting for resource) */
    DMOSI_THREAD_STATE_SUSPENDED,   /**< Thread is suspended */
    DMOSI_THREAD_STATE_TERMINATED   /**< Thread has terminated */
} dmosi_thread_state_t;

/**
 * @brief Thread information structure
 *
 * This structure holds auxiliary information about a thread, including
 * stack usage statistics, state, CPU usage, and runtime.
 */
typedef struct {
    size_t   stack_total;       /**< Total stack size in bytes */
    size_t   stack_current;     /**< Current stack usage in bytes */
    size_t   stack_peak;        /**< Peak stack usage in bytes */
    dmosi_thread_state_t state; /**< Current thread state */
    float    cpu_usage;         /**< CPU usage as a percentage (0.0 - 100.0) */
    uint64_t runtime_ms;        /**< Thread runtime in milliseconds */
} dmosi_thread_info_t;

/**
 * @brief Extra stack bytes reserved for thread and module startup overhead
 *
 * The thread entry wrapper and module loading infrastructure consume stack
 * before the module's own main function is invoked. This constant accounts
 * for that overhead so that the effective stack available to the module
 * matches the size declared in its header.
 */
#define DMOSI_THREAD_STACK_OVERHEAD 512

/**
 * @brief Create a thread
 *
 * @param entry Entry function for the thread
 * @param arg Argument to pass to the entry function
 * @param priority Thread priority
 * @param stack_size Stack size for the thread
 * @param name              Name of the thread (cannot be NULL)
 * @param process           Process to associate the thread with (NULL = current process)
 * @return dmosi_thread_t Created thread handle, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_thread_t, _thread_create,    (dmosi_thread_entry_t entry, void* arg, int priority, size_t stack_size, const char* name, dmosi_process_t process) );

/**
 * @brief Destroy a thread
 *
 * @param thread Thread handle to destroy
 */
DMOD_BUILTIN_API( dmosi, 1.0, void,          _thread_destroy,   (dmosi_thread_t thread) );

/**
 * @brief Join a thread (wait for it to finish)
 *
 * @param thread Thread handle to join
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _thread_join,      (dmosi_thread_t thread) );

/**
 * @brief Kill a thread
 *
 * Forcefully terminate a thread.
 *
 * @warning This operation may leave shared resources (mutexes, memory, etc.)
 *          in an inconsistent state. Use with caution and prefer cooperative
 *          shutdown mechanisms when possible.
 *
 * @param thread Thread handle to kill
 * @param status Exit status code passed to the underlying OS; may not be
 *               observable by other threads after termination
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,           _thread_kill,      (dmosi_thread_t thread, int status) );

/**
 * @brief Get current thread
 *
 * @return dmosi_thread_t Current thread handle
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_thread_t, _thread_current,   (void) );

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
DMOD_BUILTIN_API( dmosi, 1.0, const char*,   _thread_get_name,  (dmosi_thread_t thread) );

/**
 * @brief Get thread module name
 *
 * Returns the module name associated with the thread by retrieving it from
 * the thread's associated process.
 *
 * @param thread Thread handle (if NULL, returns module name of current thread)
 * @return const char* Module name of the process that owns the thread, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, const char*,  _thread_get_module_name,  (dmosi_thread_t thread) );

/**
 * @brief Get thread priority
 *
 * @param thread Thread handle (if NULL, returns priority of current thread)
 * @return int Thread priority, or 0 on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int,  _thread_get_priority,  (dmosi_thread_t thread) );

/**
 * @brief Get thread's associated process
 *
 * @param thread Thread handle (if NULL, returns process of current thread)
 * @return dmosi_process_t Process handle that the thread belongs to, NULL on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, dmosi_process_t, _thread_get_process, (dmosi_thread_t thread) );

/**
 * @brief Get an array of all threads
 *
 * Fills the provided array with handles of all existing threads.
 * If @p threads is NULL, the function returns the total number of threads
 * without writing anything, which is useful for determining the array size
 * needed before allocation.
 *
 * @param threads Pointer to array to fill with thread handles, or NULL to query count only
 * @param max_count Maximum number of handles to write into @p threads (ignored when @p threads is NULL)
 * @return size_t Number of threads (when @p threads is NULL) or number of handles written
 */
DMOD_BUILTIN_API( dmosi, 1.0, size_t, _thread_get_all, (dmosi_thread_t* threads, size_t max_count) );

/**
 * @brief Get an array of threads belonging to a specific process
 *
 * Fills the provided array with handles of all threads associated with @p process.
 * If @p threads is NULL, the function returns the number of threads in that process
 * without writing anything, which is useful for determining the array size needed
 * before allocation.
 *
 * @param process Process handle whose threads to retrieve
 * @param threads Pointer to array to fill with thread handles, or NULL to query count only
 * @param max_count Maximum number of handles to write into @p threads (ignored when @p threads is NULL)
 * @return size_t Number of threads in the process (when @p threads is NULL) or number of handles written
 */
DMOD_BUILTIN_API( dmosi, 1.0, size_t, _thread_get_by_process, (dmosi_process_t process, dmosi_thread_t* threads, size_t max_count) );

/**
 * @brief Get information about a thread
 *
 * Fills the provided @p info structure with auxiliary information about
 * @p thread, including stack usage statistics, state, CPU usage, and runtime.
 *
 * @param thread Thread handle (if NULL, returns info for the current thread)
 * @param info   Pointer to a dmosi_thread_info_t structure to fill
 * @return int 0 on success, negative error code on failure
 */
DMOD_BUILTIN_API( dmosi, 1.0, int, _thread_get_info, (dmosi_thread_t thread, dmosi_thread_info_t* info) );

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

//==============================================================================
//                              Interrupt Handler API
//==============================================================================
/**
 * @defgroup DMOSI_IRQ_API Interrupt Handler API
 * @brief Weak prototypes for RTOS-essential interrupt handlers
 *
 * These handlers represent the three interrupt roles that every RTOS requires
 * for correct operation. Each RTOS and each hardware architecture names these
 * interrupts differently; the dmosi names below are architecture-independent
 * and describe the functional role of the handler.
 *
 * An RTOS port provides strong implementations that forward to the
 * architecture-specific ISR names, for example:
 *
 * | dmosi handler               | ARM Cortex-M         | RISC-V                  |
 * |-----------------------------|----------------------|-------------------------|
 * | dmosi_context_switch_handler | PendSV_Handler       | software interrupt ISR  |
 * | dmosi_syscall_handler        | SVC_Handler          | ecall / machine-mode ISR|
 * | dmosi_tick_handler           | SysTick_Handler      | timer interrupt ISR     |
 * @{
 */

/**
 * @brief RTOS context-switch handler
 *
 * Invoked by the RTOS to perform a context switch between tasks/threads.
 * Override this weak (no-op) implementation with the RTOS-specific
 * context-switch routine.
 *
 * Architecture mapping examples:
 * - ARM Cortex-M: @c PendSV_Handler
 * - RISC-V: software interrupt handler
 */
DMOD_BUILTIN_API( dmosi, 1.0, void, _context_switch_handler, (void) );

/**
 * @brief RTOS system-call (supervisor-call) handler
 *
 * Invoked when user code requests privileged OS services via a trap/call
 * instruction. Override this weak (no-op) implementation with the
 * RTOS-specific system-call entry routine.
 *
 * Architecture mapping examples:
 * - ARM Cortex-M: @c SVC_Handler
 * - RISC-V: ecall / machine-mode trap handler
 */
DMOD_BUILTIN_API( dmosi, 1.0, void, _syscall_handler,         (void) );

/**
 * @brief RTOS periodic tick handler
 *
 * Invoked by the hardware timer that drives the RTOS time base. Used for
 * task scheduling, timeouts, and delay management. Override this weak (no-op)
 * implementation with the RTOS-specific tick routine.
 *
 * Architecture mapping examples:
 * - ARM Cortex-M: @c SysTick_Handler
 * - RISC-V: machine timer interrupt handler
 */
DMOD_BUILTIN_API( dmosi, 1.0, void, _tick_handler,            (void) );

/** @} */ // end of DMOSI_IRQ_API

//==============================================================================
//                              System Time API
//==============================================================================
/**
 * @defgroup DMOSI_SYSTIME_API System Time API
 * @brief API for reading the RTOS system clock (SysTick)
 *
 * This API provides a function to read the current RTOS tick count, which
 * is incremented by the hardware timer used as the RTOS time base (e.g.,
 * SysTick on ARM Cortex-M). The tick count can be used to measure elapsed
 * time and implement timeouts.
 * @{
 */

/**
 * @brief Get the current RTOS tick count
 *
 * Returns the number of RTOS ticks elapsed since the scheduler was started.
 * The tick period depends on the RTOS configuration (typically 1 ms per tick).
 *
 * @return uint32_t Current tick count
 */
DMOD_BUILTIN_API( dmosi, 1.0, uint32_t, _get_tick_count, (void) );

/** @} */ // end of DMOSI_SYSTIME_API

#endif // DMOSI_H
