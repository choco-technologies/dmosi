# DMOSI - DMOD Operating System Interface

DMOSI (DMOD Operating System Interface) is an abstraction layer for Real-Time Operating Systems (RTOS) and embedded operating systems. It provides a unified API that allows libraries and modules to interact with operating system primitives independently of the underlying RTOS implementation.

## Overview

This repository serves as:
- An **abstraction layer** for other libraries implementing specific RTOS functionality
- A **common interface** for modules that need OS services without being tied to a specific RTOS
- A **standardized API** for embedded systems targeting various RTOS platforms (FreeRTOS, ThreadX, Zephyr, etc.)

## Features

DMOSI provides weak implementations (stubs) for the following operating system primitives:

### 1. **Mutex API**
Thread synchronization through mutual exclusion locks:
- `dmosi_mutex_create()` - Create a mutex (recursive or non-recursive)
- `dmosi_mutex_destroy()` - Destroy a mutex
- `dmosi_mutex_lock()` - Lock a mutex
- `dmosi_mutex_unlock()` - Unlock a mutex

### 2. **Semaphore API**
Counting semaphores for resource management:
- `dmosi_semaphore_create()` - Create a semaphore with initial and max counts
- `dmosi_semaphore_destroy()` - Destroy a semaphore
- `dmosi_semaphore_wait()` - Wait on a semaphore (with timeout)
- `dmosi_semaphore_post()` - Post to a semaphore

### 3. **Thread API**
Thread creation and management:
- `dmosi_thread_create()` - Create a new thread
- `dmosi_thread_destroy()` - Destroy a thread
- `dmosi_thread_join()` - Wait for thread completion
- `dmosi_thread_current()` - Get current thread handle
- `dmosi_thread_sleep()` - Sleep for specified milliseconds

### 4. **Process API**
Process-level operations (for RTOS that support processes):
- `dmosi_process_create()` - Create a new process
- `dmosi_process_destroy()` - Destroy a process
- `dmosi_process_current()` - Get current process handle

### 5. **Queue API**
Inter-task message queues:
- `dmosi_queue_create()` - Create a queue with specified item size and length
- `dmosi_queue_destroy()` - Destroy a queue
- `dmosi_queue_send()` - Send data to queue (with timeout)
- `dmosi_queue_receive()` - Receive data from queue (with timeout)

### 6. **Timer API**
Software timers for periodic or one-shot callbacks:
- `dmosi_timer_create()` - Create a timer with callback
- `dmosi_timer_destroy()` - Destroy a timer
- `dmosi_timer_start()` - Start a timer
- `dmosi_timer_stop()` - Stop a timer
- `dmosi_timer_reset()` - Reset a timer

## Usage

### Basic Integration

Add DMOSI to your CMake project using FetchContent:

```cmake
include(FetchContent)

FetchContent_Declare(
    dmosi
    GIT_REPOSITORY https://github.com/choco-technologies/dmosi.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(dmosi)

target_link_libraries(your_target PRIVATE dmosi)
```

### Implementing RTOS-Specific Functions

To implement DMOSI for your specific RTOS, override the weak implementations by providing strong implementations in your library. Create a separate library or repository that links against DMOSI and provides the actual implementations for your target RTOS.

### Using DMOSI in Your Application

```c
#include "dmosi.h"

void my_task(void)
{
    // Create a mutex
    dmosi_mutex_t mutex = dmosi_mutex_create(false);
    
    // Lock the mutex
    dmosi_mutex_lock(mutex);
    
    // Critical section
    // ...
    
    // Unlock the mutex
    dmosi_mutex_unlock(mutex);
    
    // Create a thread (associated with current process)
    dmosi_thread_t thread = dmosi_thread_create(
        my_thread_function,
        NULL,           // argument
        5,              // priority
        2048,           // stack size
        "my_thread",    // thread name
        "my_module",    // module name
        NULL            // process (NULL = current process)
    );
    
    // Clean up
    dmosi_mutex_destroy(mutex);
}
```

## Configuration Options

### DMOSI_DONT_IMPLEMENT_DMOD_API

By default, DMOSI provides implementations of several DMOD SAL API functions that call the corresponding `dmosi_*` functions. If you want to provide your own implementation or don't need this bridge, set this option:

```cmake
set(DMOSI_DONT_IMPLEMENT_DMOD_API ON CACHE BOOL "Don't implement DMOD API" FORCE)
```

### DMOSI_DONT_IMPLEMENT_DMOD_API_MUTEX

This option provides more granular control over the DMOD API implementation. By default, DMOSI implements DMOD mutex API functions (`Dmod_Mutex_New`, `Dmod_Mutex_Delete`, `Dmod_Mutex_Lock`, `Dmod_Mutex_Unlock`) using DMOSI mutex functions. If you want to provide your own mutex implementation while still using other DMOD API implementations, set this option:

```cmake
set(DMOSI_DONT_IMPLEMENT_DMOD_API_MUTEX ON CACHE BOOL "Don't implement DMOD Mutex API" FORCE)
```

### DMOSI_DONT_IMPLEMENT_DMOD_API_ENV

By default, DMOSI implements the DMOD environment API function `Dmod_GetCurrentModuleNameEx` using DMOSI thread functions (`dmosi_thread_current` and `dmosi_thread_get_module_name`). If you want to provide your own implementation, set this option:

```cmake
set(DMOSI_DONT_IMPLEMENT_DMOD_API_ENV ON CACHE BOOL "Don't implement DMOD Environment API" FORCE)
```

### DMOSI_DONT_IMPLEMENT_DMOD_API_PROC

By default, DMOSI implements the DMOD process API function `Dmod_Exit` using DMOSI process functions (`dmosi_process_current` and `dmosi_process_kill`), with a fallback to the standard C library `exit()`. If you want to provide your own implementation, set this option:

```cmake
set(DMOSI_DONT_IMPLEMENT_DMOD_API_PROC ON CACHE BOOL "Don't implement DMOD Process API" FORCE)
```

**Note:** The global `DMOSI_DONT_IMPLEMENT_DMOD_API` option takes precedence. If it's set to ON, all DMOD API implementations (including mutex, environment, and process) will be disabled regardless of the granular settings.

## Building

### Build the library:

```bash
mkdir build
cd build
cmake ..
make
```

### Build with DMOD API bridge disabled:

```bash
mkdir build
cd build
cmake -DDMOSI_DONT_IMPLEMENT_DMOD_API=ON ..
make
```

### Build with only DMOD Mutex API disabled:

```bash
mkdir build
cd build
cmake -DDMOSI_DONT_IMPLEMENT_DMOD_API_MUTEX=ON ..
make
```

### Build with tests (if available):

```bash
mkdir build
cd build
cmake -DDMOSI_BUILD_TESTS=ON ..
make
ctest
```

## Architecture

```
┌─────────────────────────────────────────┐
│     Application / DMOD Modules          │
└─────────────────┬───────────────────────┘
                  │
                  │ Uses DMOSI API
                  │
┌─────────────────▼───────────────────────┐
│            DMOSI Library                │
│  (Weak implementations/stubs by default)│
└─────────────────┬───────────────────────┘
                  │
                  │ Overridden by
                  │
┌─────────────────▼───────────────────────┐
│    RTOS-Specific Implementation         │
│   (FreeRTOS, ThreadX, Zephyr, etc.)     │
└─────────────────┬───────────────────────┘
                  │
                  │
┌─────────────────▼───────────────────────┐
│         Hardware / RTOS Kernel          │
└─────────────────────────────────────────┘
```

## Weak Implementations

All functions have weak implementations that return error codes or NULL. This allows:
1. **Compilation without errors** even when no RTOS is linked
2. **Gradual implementation** - implement only what you need
3. **Testing** - stub behavior for unit tests
4. **Flexibility** - choose which functions to implement

## Error Handling

Functions that can fail return:
- `0` on success
- Negative error codes on failure (typically `-ENOSYS` for unimplemented functions)
- `NULL` for handle creation failures

## Contributing

When implementing DMOSI for a new RTOS:
1. Create a new repository or library (e.g., `dmosi-freertos`)
2. Link against DMOSI
3. Provide strong implementations for the functions your RTOS supports
4. Document any RTOS-specific limitations or behaviors

## License

See [LICENSE](LICENSE) file for details.

## Related Projects

- [DMOD](https://github.com/choco-technologies/dmod) - Dynamic Module System
- DMOSI implementations for specific RTOS (to be added)

## Support

For issues, questions, or contributions, please visit:
https://github.com/choco-technologies/dmosi/issues
