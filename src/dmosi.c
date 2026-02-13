#include <errno.h>
#include "dmosi.h"

// Default values for spawned processes
#define DMOSI_DEFAULT_PRIORITY 0
#define DMOSI_DEFAULT_STACK_SIZE 1024

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, bool, _init,   (void) )
{
    return false;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, bool, _deinit, (void) )
{
    return false;
}

//==============================================================================
//                              MUTEX API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_mutex_t, _mutex_create,    (bool recursive) )
{
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _mutex_destroy,   (dmosi_mutex_t mutex) )
{
    (void)mutex;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _mutex_lock,      (dmosi_mutex_t mutex) )
{
    (void)mutex;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _mutex_unlock,    (dmosi_mutex_t mutex) )
{
    (void)mutex;
    return -ENOSYS;
}

//==============================================================================
//                              Semaphore API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_semaphore_t, _semaphore_create,  (uint32_t initial_count, uint32_t max_count) )
{
    (void)initial_count;
    (void)max_count;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _semaphore_destroy, (dmosi_semaphore_t semaphore) )
{
    (void)semaphore;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _semaphore_wait,    (dmosi_semaphore_t semaphore, int32_t timeout_ms) )
{
    (void)semaphore;
    (void)timeout_ms;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _semaphore_post,    (dmosi_semaphore_t semaphore) )
{
    (void)semaphore;
    return -ENOSYS;
}

//==============================================================================
//                              Thread API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_thread_t, _thread_create,    (dmod_thread_entry_t entry, void* arg, int priority, size_t stack_size, const char* name, const char* module_name) )
{
    (void)entry;
    (void)arg;
    (void)priority;
    (void)stack_size;
    (void)name;
    (void)module_name;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _thread_destroy,   (dmod_thread_t thread) )
{
    (void)thread;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _thread_join,      (dmod_thread_t thread) )
{
    (void)thread;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_thread_t, _thread_current,   (void) )
{
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _thread_sleep,     (uint32_t ms) )
{
    (void)ms;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _thread_get_name,  (dmod_thread_t thread) )
{
    (void)thread;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _thread_get_module_name,  (dmod_thread_t thread) )
{
    (void)thread;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _thread_get_priority,  (dmod_thread_t thread) )
{
    (void)thread;
    return 0;
}

//==============================================================================
//                              Process API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_process_t, _process_create,    (const char* name, dmod_process_t parent) )
{
    (void)name;
    (void)parent;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _process_destroy,   (dmod_process_t process) )
{
    (void)process;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_kill,      (dmod_process_t process, int status) )
{
    (void)process;
    (void)status;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_wait,      (dmod_process_t process, int32_t timeout_ms) )
{
    (void)process;
    (void)timeout_ms;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_process_t, _process_current,   (void) )
{
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_current, (dmod_process_t process) )
{
    (void)process;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_process_state_t, _process_get_state, (dmod_process_t process) )
{
    (void)process;
    return DMOSI_PROCESS_STATE_TERMINATED;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_process_id_t, _process_get_id, (dmod_process_t process) )
{
    (void)process;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_id,    (dmod_process_t process, dmod_process_id_t pid) )
{
    (void)process;
    (void)pid;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _process_get_name,  (dmod_process_t process) )
{
    (void)process;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_uid,   (dmod_process_t process, dmod_user_id_t uid) )
{
    (void)process;
    (void)uid;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_user_id_t, _process_get_uid,   (dmod_process_t process) )
{
    (void)process;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_pwd,   (dmod_process_t process, const char* pwd) )
{
    (void)process;
    (void)pwd;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _process_get_pwd,   (dmod_process_t process) )
{
    (void)process;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_add_thread,    (dmod_process_t process, dmod_thread_t thread) )
{
    (void)process;
    (void)thread;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_remove_thread, (dmod_process_t process, dmod_thread_t thread) )
{
    (void)process;
    (void)thread;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, bool, _process_has_thread,    (dmod_process_t process, dmod_thread_t thread) )
{
    (void)process;
    (void)thread;
    return false;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_process_t, _process_find_by_name, (const char* name) )
{
    (void)name;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_process_t, _process_find_by_id,   (dmod_process_id_t pid) )
{
    (void)pid;
    return NULL;
}

//==============================================================================
//                              Queue API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_queue_t, _queue_create,  (size_t item_size, uint32_t queue_length) )
{
    (void)item_size;
    (void)queue_length;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _queue_destroy, (dmosi_queue_t queue) )
{
    (void)queue;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _queue_send,    (dmosi_queue_t queue, const void* item, int32_t timeout_ms) )
{
    (void)queue;
    (void)item;
    (void)timeout_ms;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _queue_receive, (dmosi_queue_t queue, void* item, int32_t timeout_ms) )
{
    (void)queue;
    (void)item;
    (void)timeout_ms;
    return -ENOSYS;
}

//==============================================================================
//                              Timer API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_timer_t, _timer_create,  (dmosi_timer_callback_t callback, void* arg, uint32_t period_ms, bool auto_reload) )
{
    (void)callback;
    (void)arg;
    (void)period_ms;
    (void)auto_reload;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _timer_destroy, (dmosi_timer_t timer) )
{
    (void)timer;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _timer_start,   (dmosi_timer_t timer) )
{
    (void)timer;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _timer_stop,    (dmosi_timer_t timer) )
{
    (void)timer;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _timer_reset,   (dmosi_timer_t timer) )
{
    (void)timer;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _timer_set_period, (dmosi_timer_t timer, uint32_t period_ms) )
{
    (void)timer;
    (void)period_ms;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, uint32_t, _timer_get_period, (dmosi_timer_t timer) )
{
    (void)timer;
    return 0;
}

//==============================================================================
//                              DMOD Mutex API Implementation
//==============================================================================
#if !defined(DMOSI_DONT_IMPLEMENT_DMOD_API) && !defined(DMOSI_DONT_IMPLEMENT_DMOD_API_MUTEX)

/**
 * @brief DMOD mutex implementation using DMOSI
 *
 * This implementation provides the DMOD mutex API using the underlying
 * DMOSI mutex operations. It is only compiled when DMOSI_DONT_IMPLEMENT_DMOD_API
 * and DMOSI_DONT_IMPLEMENT_DMOD_API_MUTEX are not defined.
 *
 * @note These functions assume dmosi_mutex_t is pointer-compatible with void*.
 *       The opaque dmosi_mutex_t type is defined as 'struct dmosi_mutex*', which
 *       is safely castable to/from void*.
 */

void* Dmod_Mutex_New(bool recursive)
{
    return (void*)dmosi_mutex_create(recursive);
}

void Dmod_Mutex_Delete(void* mutex)
{
    dmosi_mutex_destroy((dmosi_mutex_t)mutex);
}

int Dmod_Mutex_Lock(void* mutex)
{
    return dmosi_mutex_lock((dmosi_mutex_t)mutex);
}

int Dmod_Mutex_Unlock(void* mutex)
{
    return dmosi_mutex_unlock((dmosi_mutex_t)mutex);
}

#endif // !DMOSI_DONT_IMPLEMENT_DMOD_API && !DMOSI_DONT_IMPLEMENT_DMOD_API_MUTEX

//==============================================================================
//                              DMOD Environment API Implementation
//==============================================================================
#if !defined(DMOSI_DONT_IMPLEMENT_DMOD_API) && !defined(DMOSI_DONT_IMPLEMENT_DMOD_API_ENV)

/**
 * @brief DMOD environment API implementation using DMOSI
 *
 * This implementation provides the DMOD GetCurrentModuleNameEx API using the 
 * underlying DMOSI thread operations. It is only compiled when 
 * DMOSI_DONT_IMPLEMENT_DMOD_API and DMOSI_DONT_IMPLEMENT_DMOD_API_ENV are not defined.
 *
 * @note This function gets the module name from the current thread. If no current
 *       thread is available or it has no module name, it returns the provided default.
 */

const char* Dmod_GetCurrentModuleNameEx(const char* Default)
{
    // dmosi_thread_get_module_name accepts NULL and returns current thread's module name
    const char* module_name = dmosi_thread_get_module_name(NULL);
    if (module_name != NULL) {
        return module_name;
    }
    return Default;
}

#endif // !DMOSI_DONT_IMPLEMENT_DMOD_API && !DMOSI_DONT_IMPLEMENT_DMOD_API_ENV

//==============================================================================
//                              DMOD Process API Implementation
//==============================================================================
#if !defined(DMOSI_DONT_IMPLEMENT_DMOD_API) && !defined(DMOSI_DONT_IMPLEMENT_DMOD_API_PROC)

/**
 * @brief DMOD process API implementation using DMOSI
 *
 * This implementation provides the DMOD Exit API using the underlying
 * DMOSI process operations. It is only compiled when DMOSI_DONT_IMPLEMENT_DMOD_API
 * and DMOSI_DONT_IMPLEMENT_DMOD_API_PROC are not defined.
 *
 * @note This function attempts to kill the current process using dmosi_process_kill.
 *       For embedded systems without stdlib, it falls back to an infinite loop.
 */

void Dmod_Exit(int Status)
{
    dmod_process_t current_process = dmosi_process_current();
    if (current_process != NULL) {
        dmosi_process_kill(current_process, Status);
    }
    
    // Log that the process is exiting from main thread
    DMOD_LOG_VERBOSE("Process exiting from main thread with status %d\n", Status);
    
    // For embedded systems without exit(), enter infinite loop
    // Note: Status value is passed to dmosi_process_kill if available
    while(1) {
        // Infinite loop as fallback for embedded systems
    }
}

/**
 * @brief Thread entry structure for spawned modules
 *
 * This structure holds the context and arguments needed to run a module
 * in a separate thread.
 */
typedef struct {
    Dmod_Context_t* context;
    int argc;
    char** argv;
    dmod_process_t process;  // Process handle for this spawn
} dmod_spawn_args_t;

/**
 * @brief Thread entry function for spawned modules
 *
 * This function is called in a new thread to run a module.
 *
 * @param arg Pointer to dmod_spawn_args_t structure
 */
static void dmod_spawn_thread_entry(void* arg)
{
    dmod_spawn_args_t* spawn_args = arg;
    if (spawn_args != NULL && spawn_args->context != NULL) {
        // Run the module and get result
        int result = Dmod_Run(spawn_args->context, spawn_args->argc, spawn_args->argv);
        
        // Free the structure before exiting (Exit never returns)
        Dmod_Free(spawn_args);
        
        // Exit the process with the result code
        // This allows Dmod_GetProcessResult to retrieve the exit status
        Dmod_Exit(result);
    }
}

/**
 * @brief Helper function to spawn a module in a new process/thread
 *
 * This internal function handles the common logic for both Spawn and RunDetached.
 *
 * @param Context Module context to spawn
 * @param argc Number of arguments
 * @param argv Argument array
 * @param parent Parent process (NULL for detached, current for spawn)
 * @return Dmod_Pid_t Process ID on success, negative error code on failure
 */
static Dmod_Pid_t dmod_spawn_module_internal(Dmod_Context_t* Context, int argc, char* argv[], dmod_process_t parent)
{
    if (Context == NULL) {
        DMOD_LOG_ERROR("Failed to spawn module: Context is NULL\n");
        return -EINVAL;
    }

    // Get module name from Context - it's an error if not available
    const char* module_name = Dmod_GetName(Context);
    if (module_name == NULL) {
        DMOD_LOG_ERROR("Failed to spawn module: module name is NULL\n");
        return -EINVAL;
    }

    // Create a process
    dmod_process_t new_process = dmosi_process_create(module_name, parent);
    if (new_process == NULL) {
        DMOD_LOG_ERROR("Failed to create process for module '%s'\n", module_name);
        return -ENOMEM;
    }

    // Get process ID
    dmod_process_id_t pid = dmosi_process_get_id(new_process);

    // Allocate spawn args on heap using MallocEx for better tracking
    // Note: We create the process first to get the PID, then allocate spawn_args.
    // If allocation fails, we properly clean up the process before returning.
    dmod_spawn_args_t* spawn_args = Dmod_MallocEx(sizeof(dmod_spawn_args_t), module_name);
    if (spawn_args == NULL) {
        DMOD_LOG_ERROR("Failed to allocate spawn args for module '%s'\n", module_name);
        dmosi_process_destroy(new_process);
        return -ENOMEM;
    }

    spawn_args->context = Context;
    spawn_args->argc = argc;
    spawn_args->argv = argv;
    spawn_args->process = new_process;

    // Get stack size from Context header
    uint64_t stack_size = Dmod_GetStackSize(Context);
    if (stack_size == 0) {
        stack_size = DMOSI_DEFAULT_STACK_SIZE;
    }

    // Inherit priority from current thread
    int priority = dmosi_thread_get_priority(NULL);
    if (priority == 0) {
        priority = DMOSI_DEFAULT_PRIORITY;
    }

    // Create a thread to run the module
    // Both name and module_name parameters use the spawned module's name since
    // the thread is part of the new process/module, not the parent.
    // This ensures proper tracking and identification of the thread.
    dmod_thread_t thread = dmosi_thread_create(
        dmod_spawn_thread_entry,
        spawn_args,
        priority,
        (size_t)stack_size,
        module_name,  // Thread name: identifies the thread
        module_name   // Module name: for allocation tracking
    );

    if (thread == NULL) {
        DMOD_LOG_ERROR("Failed to create thread for module '%s'\n", module_name);
        Dmod_Free(spawn_args);
        dmosi_process_destroy(new_process);
        return -ENOMEM;
    }

    // Add thread to process
    dmosi_process_add_thread(new_process, thread);

    // Return PID immediately without waiting
    return (Dmod_Pid_t)pid;
}

/**
 * @brief Spawn a module in a new process/thread
 *
 * This function creates a new process and thread to run the specified module context.
 * It returns immediately with the process ID, without waiting for completion.
 *
 * @param Context Module context to spawn
 * @param argc Number of arguments
 * @param argv Argument array (MUST remain valid for the lifetime of the module execution)
 * @return Dmod_Pid_t Process ID on success, negative error code on failure
 * 
 * @warning The argv array and its contents must remain valid for the entire duration
 *          of the module's execution.
 */
Dmod_Pid_t Dmod_Spawn(Dmod_Context_t* Context, int argc, char* argv[])
{
    // Spawn with current process as parent
    dmod_process_t current_process = dmosi_process_current();
    return dmod_spawn_module_internal(Context, argc, argv, current_process);
}

/**
 * @brief Run a module in a detached process/thread
 *
 * This function creates a new detached process and thread to run the specified module context.
 * It returns immediately with the process ID, without waiting for completion.
 * The process has no parent.
 *
 * @param Context Module context to run detached
 * @param argc Number of arguments
 * @param argv Argument array (MUST remain valid for the lifetime of the module execution)
 * @return Dmod_Pid_t Process ID on success, negative error code on failure
 * 
 * @warning The argv array and its contents must remain valid for the entire duration
 *          of the module's execution since this function returns immediately while
 *          the module runs in a detached process/thread.
 */
Dmod_Pid_t Dmod_RunDetached(Dmod_Context_t* Context, int argc, char* argv[])
{
    // Spawn with NULL parent (detached)
    return dmod_spawn_module_internal(Context, argc, argv, NULL);
}

#endif // !DMOSI_DONT_IMPLEMENT_DMOD_API && !DMOSI_DONT_IMPLEMENT_DMOD_API_PROC


