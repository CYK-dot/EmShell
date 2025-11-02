/**
 * @file emshell_core.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025 CYK-Dot, MIT License.
 */
#ifndef __emshell_core_H__
#define __emshell_core_H__

/* Header import ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdbool.h>

#include "em_types.h"

/* Config macros -----------------------------------------------------------------*/

/* Export macros -----------------------------------------------------------------*/

/* Exported typedef --------------------------------------------------------------*/

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported function -------------------------------------------------------------*/

EM_ERRO EM_Send(EM_INST *instance, const char *inBuf, uint16_t len);

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif