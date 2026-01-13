/**
 * @file em_config.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-10
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */
#ifndef __em_config_H__
#define __em_config_H__

/* Header import ------------------------------------------------------------------*/
#include <stdlib.h>

/* Config macros -----------------------------------------------------------------*/

#define EM_MALLOC(size) malloc((size))
#define EM_FREE(ptr) free((ptr))

#define EM_UNLIKELY(x) (__builtin_expect(!!(x), 0))
#define EM_LIKELY(x) (__builtin_expect(!!(x), 1))

#define EM_SAFE_WRITE(ptr, value) do { \
    if ((ptr) != NULL) {               \
        *(ptr) = (value);              \
    }                                  \
} while (0)

#endif