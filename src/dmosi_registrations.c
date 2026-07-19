/*
 * Registers dmosi's Built-in API in the .dmod.inputs section so that a
 * system-side binary statically linking dmosi (via dmod_link_builtin) is
 * recognised by the loader as providing the "dmosi" system module (see
 * Dmod_Mgr_IsSystemModule() in dmod's src/system/private/dmod_mgr.c).
 *
 * This lives here - in dmosi, the package that declares the API - rather
 * than in a backend that merely implements part of it (dmosi-posix,
 * dmosi-freertos, dmosi-proc): dmosi.h declares dmosi's *entire* API
 * surface, so registering it is dmosi's responsibility alone. A backend
 * only ever provides hard definitions for some of those functions (the
 * rest fall back to dmosi.c's own weak defaults); if a backend also
 * carried its own copy of this file, linking two backends' registrations
 * together - or a backend's alongside dmosi's own - would multiply-define
 * every entry.
 *
 * This must live in its own translation unit, separate from dmosi.c: only
 * dmosi.h is included here (which itself only pulls in dmod_types.h, not
 * the full dmod.h), so defining DMOD_ENABLE_REGISTRATION only materialises
 * dmosi's own registration structs - it can't accidentally re-register
 * dmod's kernel Built-in APIs the way including the full dmod.h would.
 */
#define DMOD_ENABLE_REGISTRATION ON
#include "dmosi.h"
