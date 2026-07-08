#include <errno.h>
#include "dmosi.h"

// Default values for spawned processes
#define DMOSI_DEFAULT_STACK_SIZE 1024
#define DMOSI_DEFAULT_PRIORITY 0

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, bool, _init,   (void) )
{
    return false;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, bool, _deinit, (void) )
{
    return false;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, bool, _is_started, (void) )
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

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 2.0, int, _semaphore_wait,    (dmosi_semaphore_t semaphore, uint32_t count, int32_t timeout_ms) )
{
    (void)semaphore;
    (void)count;
    (void)timeout_ms;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 2.0, int, _semaphore_post,    (dmosi_semaphore_t semaphore, uint32_t count) )
{
    (void)semaphore;
    (void)count;
    return -ENOSYS;
}

//==============================================================================
//                              Thread API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_thread_t, _thread_create,    (dmosi_thread_entry_t entry, void* arg, int priority, size_t stack_size, const char* name, dmosi_process_t process) )
{
    (void)entry;
    (void)arg;
    (void)priority;
    (void)stack_size;
    (void)name;
    (void)process;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _thread_destroy,   (dmosi_thread_t thread) )
{
    (void)thread;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _thread_join,      (dmosi_thread_t thread) )
{
    (void)thread;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _thread_kill,      (dmosi_thread_t thread, int status) )
{
    (void)thread;
    (void)status;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_thread_t, _thread_current,   (void) )
{
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _thread_sleep,     (uint32_t ms) )
{
    (void)ms;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _thread_get_name,  (dmosi_thread_t thread) )
{
    (void)thread;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _thread_get_module_name,  (dmosi_thread_t thread) )
{
    (void)thread;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _thread_get_priority,  (dmosi_thread_t thread) )
{
    (void)thread;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_t, _thread_get_process, (dmosi_thread_t thread) )
{
    (void)thread;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, size_t, _thread_get_all, (dmosi_thread_t* threads, size_t max_count) )
{
    (void)threads;
    (void)max_count;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, size_t, _thread_get_by_process, (dmosi_process_t process, dmosi_thread_t* threads, size_t max_count) )
{
    (void)process;
    (void)threads;
    (void)max_count;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _thread_get_info, (dmosi_thread_t thread, dmosi_thread_info_t* info) )
{
    (void)thread;
    if (info == NULL) {
        return -EINVAL;
    }
    info->stack_total   = 0;
    info->stack_current = 0;
    info->stack_peak    = 0;
    info->state         = DMOSI_THREAD_STATE_TERMINATED;
    info->cpu_usage     = 0.0f;
    info->runtime_ms    = 0;
    return -ENOSYS;
}

//==============================================================================
//                              Process API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_t, _process_create,    (const char* name, const char* module_name, dmosi_process_t parent) )
{
    (void)name;
    (void)module_name;
    (void)parent;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _process_destroy,   (dmosi_process_t process) )
{
    (void)process;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_kill,      (dmosi_process_t process, int status) )
{
    (void)process;
    (void)status;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_wait,      (dmosi_process_t process, int32_t timeout_ms) )
{
    (void)process;
    (void)timeout_ms;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_t, _process_current,   (void) )
{
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_current, (dmosi_process_t process) )
{
    (void)process;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_state_t, _process_get_state, (dmosi_process_t process) )
{
    (void)process;
    return DMOSI_PROCESS_STATE_TERMINATED;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_id_t, _process_get_id, (dmosi_process_t process) )
{
    (void)process;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_id,    (dmosi_process_t process, dmosi_process_id_t pid) )
{
    (void)process;
    (void)pid;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _process_get_name,  (dmosi_process_t process) )
{
    (void)process;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _process_get_module_name, (dmosi_process_t process) )
{
    (void)process;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_module_name, (dmosi_process_t process, const char* module_name) )
{
    (void)process;
    (void)module_name;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _process_get_allocator_name, (dmosi_process_t process) )
{
    (void)process;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_uid,   (dmosi_process_t process, dmosi_user_id_t uid) )
{
    (void)process;
    (void)uid;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_user_id_t, _process_get_uid,   (dmosi_process_t process) )
{
    (void)process;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_pwd,   (dmosi_process_t process, const char* pwd) )
{
    (void)process;
    (void)pwd;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _process_get_pwd,   (dmosi_process_t process) )
{
    (void)process;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_stream,   (dmosi_process_t process, dmosi_stream_index_t index, const char* path) )
{
    (void)process;
    (void)index;
    (void)path;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void*, _process_get_stream,   (dmosi_process_t process, dmosi_stream_index_t index) )
{
    (void)process;
    (void)index;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, const char*, _process_get_stream_path, (dmosi_process_t process, dmosi_stream_index_t index) )
{
    (void)process;
    (void)index;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_lock_stream,  (dmosi_process_t process, dmosi_stream_index_t index) )
{
    (void)process;
    (void)index;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_unlock_stream, (dmosi_process_t process, dmosi_stream_index_t index) )
{
    (void)process;
    (void)index;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_t, _process_find_by_name, (const char* name) )
{
    (void)name;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_t, _process_find_by_id,   (dmosi_process_id_t pid) )
{
    (void)pid;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_get_exit_status, (dmosi_process_t process) )
{
    (void)process;
    return 0;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_set_exit_status, (dmosi_process_t process, int exit_status) )
{
    (void)process;
    (void)exit_status;
    return -ENOSYS;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmosi_process_t, _process_get_parent, (dmosi_process_t process) )
{
    (void)process;
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
//                              Interrupt Handler API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _context_switch_handler, (void) )
{
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _syscall_handler,         (void) )
{
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _tick_handler,            (void) )
{
}

//==============================================================================
//                              System Time API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, uint32_t, _get_tick_count, (void) )
{
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
//                              DMOD Semaphore API Implementation
//==============================================================================
#if !defined(DMOSI_DONT_IMPLEMENT_DMOD_API)

void* Dmod_Semaphore_New(uint32_t InitialValue, uint32_t MaxCount)
{
    return (void*)dmosi_semaphore_create(InitialValue, MaxCount);
}

int Dmod_Semaphore_Wait(void* Semaphore, uint32_t Count)
{
    return dmosi_semaphore_wait((dmosi_semaphore_t)Semaphore, Count, -1);
}

int Dmod_Semaphore_Post(void* Semaphore, uint32_t Count)
{
    return dmosi_semaphore_post((dmosi_semaphore_t)Semaphore, Count);
}

void Dmod_Semaphore_Delete(void* Semaphore)
{
    dmosi_semaphore_destroy((dmosi_semaphore_t)Semaphore);
}

#endif // !DMOSI_DONT_IMPLEMENT_DMOD_API

//==============================================================================
//                              DMOD Environment API Implementation
//==============================================================================
#if !defined(DMOSI_DONT_IMPLEMENT_DMOD_API) && !defined(DMOSI_DONT_IMPLEMENT_DMOD_API_ENV)

/**
 * @brief DMOD environment API implementation using DMOSI
 *
 * This implementation provides the DMOD GetCurrentModuleNameEx API using the 
 * underlying DMOSI process operations. It is only compiled when 
 * DMOSI_DONT_IMPLEMENT_DMOD_API and DMOSI_DONT_IMPLEMENT_DMOD_API_ENV are not defined.
 *
 * @note This function gets the module name from the current process. If no current
 *       process is available or it has no module name, it returns the provided default.
 */

const char* Dmod_GetCurrentModuleNameEx(const char* Default)
{
    // Get the module name from the current thread's associated process
    dmosi_process_t current_process = dmosi_process_current();
    if (current_process != NULL) {
        const char* module_name = dmosi_process_get_module_name(current_process);
        if (module_name != NULL) {
            return module_name;
        }
    }
    return Default;
}

const char* Dmod_GetCurrentAllocatorNameEx(const char* Default)
{
    // Get the allocator name (process name + PID) from the current thread's associated process
    dmosi_process_t current_process = dmosi_process_current();
    if (current_process != NULL) {
        const char* allocator_name = dmosi_process_get_allocator_name(current_process);
        if (allocator_name != NULL) {
            return allocator_name;
        }
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
    dmosi_process_t current_process = dmosi_process_current();
    if (current_process != NULL) {
        dmosi_process_kill(current_process, Status);
    }
    
    // Log that the process is exiting
    DMOD_LOG_VERBOSE("Process exiting with status %d\n", Status);
    
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
    dmosi_process_t process;  // Process handle for this spawn
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

        // This thread owns unloading the context: the caller that spawned us (see
        // Dmod_SpawnModule/Dmod_RunModuleDetached) deliberately does not unload it
        // itself, since Dmod_Unload(..., false) only unloads when the module isn't
        // marked Running - and Dmod_Run() is what marks it Running, which only
        // happens once this thread actually starts executing. Unloading from the
        // caller right after spawning (before the scheduler necessarily gave this
        // thread any time to run) would see Running still false and destroy the
        // context out from under a module that hasn't run yet. By the time we get
        // here, Dmod_Run() has already cleared Running back to false on its way out,
        // so this unload is always safe.
        Dmod_Unload(spawn_args->context, false);

        // Free the structure before exiting (Exit never returns)
        Dmod_Free(spawn_args);

        // Exit the process with the result code
        // This allows Dmod_GetProcessResult to retrieve the exit status
        Dmod_Exit(result);
    }
}

/**
 * @brief Translate a DMOD standard stream handle to a DMOSI stream index
 *
 * @param StdHandle One of DMOD_STDIN/DMOD_STDOUT/DMOD_STDERR/DMOD_STDLOG
 * @param Index Output stream index, valid only when this function returns true
 * @return bool true if StdHandle is a well-known standard stream handle
 */
static bool dmod_resolve_stream_index(void* StdHandle, dmosi_stream_index_t* Index)
{
    if (StdHandle == DMOD_STDIN) {
        *Index = DMOSI_STREAM_STDIN;
    } else if (StdHandle == DMOD_STDOUT) {
        *Index = DMOSI_STREAM_STDOUT;
    } else if (StdHandle == DMOD_STDERR) {
        *Index = DMOSI_STREAM_STDERR;
    } else if (StdHandle == DMOD_STDLOG) {
        *Index = DMOSI_STREAM_STDLOG;
    } else {
        return false;
    }
    return true;
}

/**
 * @brief Apply the requested stream redirections to a freshly created process
 *
 * @param process Process to configure
 * @param module_name Module name, used for error logging only
 * @param Streams Stream redirections to apply, may be NULL or empty
 * @return int 0 on success, negative error code on failure
 */
static int dmod_apply_stream_redirections(dmosi_process_t process, const char* module_name, const Dmod_StreamRedirections_t* Streams)
{
    if (Streams == NULL) {
        return 0;
    }

    for (size_t i = 0; i < Streams->Count; i++) {
        const Dmod_StreamRedirection_t* entry = &Streams->Entries[i];

        dmosi_stream_index_t index;
        if (!dmod_resolve_stream_index(entry->StdHandle, &index)) {
            DMOD_LOG_ERROR("Failed to spawn module '%s': unknown stream handle at index %zu\n", module_name, i);
            return -EINVAL;
        }

        if (dmosi_process_set_stream(process, index, entry->Path) != 0) {
            DMOD_LOG_ERROR("Failed to spawn module '%s': could not redirect stream %d\n", module_name, (int)index);
            return -EIO;
        }
    }

    return 0;
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
 * @param Streams Stream redirections to apply to the new process, or NULL if none are needed
 * @return Dmod_Pid_t Process ID on success, negative error code on failure
 */
static Dmod_Pid_t dmod_spawn_module_internal(Dmod_Context_t* Context, int argc, char* argv[], dmosi_process_t parent, const Dmod_StreamRedirections_t* Streams)
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

    // Create a process, passing module_name directly for tracking and identification.
    // The process name and module name both use the module's name since the process
    // represents exactly this module.
    dmosi_process_t new_process = dmosi_process_create(module_name, module_name, parent);
    if (new_process == NULL) {
        DMOD_LOG_ERROR("Failed to create process for module '%s'\n", module_name);
        return -ENOMEM;
    }

    // Apply requested stream redirections before starting the module thread
    int stream_result = dmod_apply_stream_redirections(new_process, module_name, Streams);
    if (stream_result != 0) {
        dmosi_process_destroy(new_process);
        return (Dmod_Pid_t)stream_result;
    }

    // Get process ID
    dmosi_process_id_t pid = dmosi_process_get_id(new_process);

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

    // Get stack size from Context header and add overhead for thread/module startup
    uint64_t stack_size = Dmod_GetStackSize(Context);
    if (stack_size == 0) {
        stack_size = DMOSI_DEFAULT_STACK_SIZE;
    }
    stack_size += DMOSI_THREAD_STACK_OVERHEAD;

    // Inherit priority from current thread
    int priority = dmosi_thread_get_priority(NULL);
    if (priority == 0) {
        priority = DMOSI_DEFAULT_PRIORITY;
    }

    // Create a thread to run the module
    // The thread name uses the module's name since the thread is part of the new process/module.
    // The module name is stored in the process and retrieved via dmosi_thread_get_module_name.
    dmosi_thread_t thread = dmosi_thread_create(
        dmod_spawn_thread_entry,
        spawn_args,
        priority,
        (size_t)stack_size,
        module_name,  // Thread name: identifies the thread
        new_process   // Process: associate thread with the new process
    );

    if (thread == NULL) {
        DMOD_LOG_ERROR("Failed to create thread for module '%s'\n", module_name);
        Dmod_Free(spawn_args);
        dmosi_process_destroy(new_process);
        return -ENOMEM;
    }

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
 * @param Streams Stream redirections to apply to the spawned process, or NULL if none are needed
 * @return Dmod_Pid_t Process ID on success, negative error code on failure
 *
 * @warning The argv array and its contents must remain valid for the entire duration
 *          of the module's execution.
 */
Dmod_Pid_t Dmod_Spawn(Dmod_Context_t* Context, int argc, char* argv[], const Dmod_StreamRedirections_t* Streams)
{
    // Spawn with current process as parent
    dmosi_process_t current_process = dmosi_process_current();
    return dmod_spawn_module_internal(Context, argc, argv, current_process, Streams);
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
 * @param Streams Stream redirections to apply to the detached process, or NULL if none are needed
 * @return Dmod_Pid_t Process ID on success, negative error code on failure
 *
 * @warning The argv array and its contents must remain valid for the entire duration
 *          of the module's execution since this function returns immediately while
 *          the module runs in a detached process/thread.
 */
Dmod_Pid_t Dmod_RunDetached(Dmod_Context_t* Context, int argc, char* argv[], const Dmod_StreamRedirections_t* Streams)
{
    // Spawn with NULL parent (detached)
    return dmod_spawn_module_internal(Context, argc, argv, NULL, Streams);
}

Dmod_Pid_t Dmod_GetCurrentPid(void)
{
    dmosi_process_t current_process = dmosi_process_current();
    if (current_process == NULL) {
        return (Dmod_Pid_t)-ENOSYS;
    }
    return (Dmod_Pid_t)dmosi_process_get_id(current_process);
}

void* Dmod_ResolveStreamFile(Dmod_Pid_t Pid, void* StdHandle)
{
    dmosi_stream_index_t index;
    if (!dmod_resolve_stream_index(StdHandle, &index)) {
        // Not a well-known standard stream handle: pass it through unchanged
        return StdHandle;
    }

    dmosi_process_t process = dmosi_process_find_by_id((dmosi_process_id_t)Pid);
    if (process == NULL) {
        return NULL;
    }

    return dmosi_process_get_stream(process, index);
}

int Dmod_SetStreamFilePath(Dmod_Pid_t Pid, void* StdHandle, const char* Path)
{
    dmosi_stream_index_t index;
    if (!dmod_resolve_stream_index(StdHandle, &index)) {
        return -EINVAL;
    }

    dmosi_process_t process = dmosi_process_find_by_id((dmosi_process_id_t)Pid);
    if (process == NULL) {
        return -ESRCH;
    }

    return dmosi_process_set_stream(process, index, Path);
}

int Dmod_GetStreamRedirections(Dmod_Pid_t Pid, Dmod_StreamRedirection_t* OutEntries, size_t MaxEntries, size_t* OutCount)
{
    if (OutCount == NULL) {
        return -EINVAL;
    }
    *OutCount = 0;

    if (MaxEntries > 0 && OutEntries == NULL) {
        return -EINVAL;
    }

    dmosi_process_t process = dmosi_process_find_by_id((dmosi_process_id_t)Pid);
    if (process == NULL) {
        return -ESRCH;
    }

    static void* const known_handles[DMOSI_STREAM_COUNT] = { DMOD_STDIN, DMOD_STDOUT, DMOD_STDERR, DMOD_STDLOG };

    size_t count = 0;
    for (dmosi_stream_index_t index = 0; index < DMOSI_STREAM_COUNT; index++) {
        const char* path = dmosi_process_get_stream_path(process, index);
        if (path == NULL) {
            continue;
        }
        if (count >= MaxEntries) {
            DMOD_LOG_ERROR("Dmod_GetStreamRedirections: OutEntries buffer too small (capacity %zu)\n", MaxEntries);
            // Free whatever we already duplicated before bailing out
            for (size_t i = 0; i < count; i++) {
                Dmod_Free((void*)OutEntries[i].Path);
            }
            *OutCount = 0;
            return -ENOSPC;
        }

        char* path_copy = Dmod_StrDup(path);
        if (path_copy == NULL) {
            for (size_t i = 0; i < count; i++) {
                Dmod_Free((void*)OutEntries[i].Path);
            }
            *OutCount = 0;
            return -ENOMEM;
        }

        OutEntries[count].StdHandle = known_handles[index];
        OutEntries[count].Path      = path_copy;
        count++;
    }

    *OutCount = count;
    return 0;
}

void* Dmod_LockStdio(void* StdHandle)
{
    dmosi_stream_index_t index;
    if (dmod_resolve_stream_index(StdHandle, &index)) {
        dmosi_process_t current_process = dmosi_process_current();
        if (current_process == NULL) {
            return NULL;
        }

        // Nothing to protect when the stream has no real file bound - the kernel-write/read
        // fallback used in that case is designed to be safe without locking (raw,
        // interrupt-safe syscalls). Only take the lock when there's an actual FILE* that a
        // concurrent/re-entrant caller could otherwise race on.
        void* handle = dmosi_process_get_stream(current_process, index);
        if (handle == NULL) {
            return NULL;
        }

        if (dmosi_process_lock_stream(current_process, index) != 0) {
            return NULL;
        }
        return handle;
    }

    // Not a well-known standard stream handle: nothing to lock, pass it through unchanged
    return StdHandle;
}

void Dmod_UnlockStdio(void* StdHandle)
{
    dmosi_stream_index_t index;
    if (dmod_resolve_stream_index(StdHandle, &index)) {
        dmosi_process_t current_process = dmosi_process_current();
        if (current_process != NULL) {
            dmosi_process_unlock_stream(current_process, index);
        }
    }
}

#endif // !DMOSI_DONT_IMPLEMENT_DMOD_API && !DMOSI_DONT_IMPLEMENT_DMOD_API_PROC

//==============================================================================
//                              DMOD Time API Implementation
//==============================================================================
#if !defined(DMOSI_DONT_IMPLEMENT_DMOD_API) && !defined(DMOSI_DONT_IMPLEMENT_DMOD_API_TIME)

/**
 * @brief DMOD uptime implementation using DMOSI
 *
 * This implementation provides the DMOD GetUptime API using the underlying
 * DMOSI tick-count operation. It is only compiled when DMOSI_DONT_IMPLEMENT_DMOD_API
 * and DMOSI_DONT_IMPLEMENT_DMOD_API_TIME are not defined.
 *
 * @note The tick count is assumed to represent milliseconds, which is the
 *       typical RTOS configuration (1 ms per tick).
 */

Dmod_Timestamp_t Dmod_GetUptime(void)
{
    return (Dmod_Timestamp_t)dmosi_get_tick_count();
}

#endif // !DMOSI_DONT_IMPLEMENT_DMOD_API && !DMOSI_DONT_IMPLEMENT_DMOD_API_TIME
