#include <errno.h>
#include "dmosi.h"

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

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_thread_t, _thread_system,    (void) )
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

//==============================================================================
//                              Process API
//==============================================================================
DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, dmod_process_t, _process_create,    (const char* name) )
{
    (void)name;
    return NULL;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, void, _process_destroy,   (dmod_process_t process) )
{
    (void)process;
}

DMOD_INPUT_WEAK_API_DECLARATION( dmosi, 1.0, int, _process_kill,      (dmod_process_t process) )
{
    (void)process;
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
#ifndef DMOSI_DONT_IMPLEMENT_DMOD_API

/**
 * @brief DMOD mutex implementation using DMOSI
 *
 * This implementation provides the DMOD mutex API using the underlying
 * DMOSI mutex operations. It is only compiled when DMOSI_DONT_IMPLEMENT_DMOD_API
 * is not defined.
 *
 * @note These functions assume dmosi_mutex_t is pointer-compatible with void*.
 *       The opaque dmosi_mutex_t type is defined as 'struct dmosi_mutex*', which
 *       is safely castable to/from void*.
 */

void* Dmod_Mutex_Create(bool recursive)
{
    return (void*)dmosi_mutex_create(recursive);
}

void Dmod_Mutex_Destroy(void* mutex)
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

#endif // DMOSI_DONT_IMPLEMENT_DMOD_API

