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

