/**
 * @file em_internal.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */
#ifndef __em_internal_H__
#define __em_internal_H__

/* Header import ------------------------------------------------------------------*/

/* Config macros -----------------------------------------------------------------*/

/* Export macros -----------------------------------------------------------------*/

#define EM_TOKEN_TO_IMPL(tokenPtr) ((Em_TokenImpl *)(tokenPtr))
#define EM_PATTERN_TO_IMPL(ptnPtr) ((Em_PatternImpl *)(ptnPtr))

#define EM_IS_READABLE_ASCII(c) ((c) > ' ' && (c) <= '~')
#define EM_IS_STR_END(c) ((c) == '\0')
#define EM_IS_PARAM(c) ((c) == '$')

/* Exported typedef --------------------------------------------------------------*/

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported function -------------------------------------------------------------*/

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif