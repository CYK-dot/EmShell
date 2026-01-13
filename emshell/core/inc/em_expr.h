/**
 * @file em_expr.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */
#ifndef __em_expr_H__
#define __em_expr_H__

/* Header import ------------------------------------------------------------------*/
#include <stdint.h>
#include "em_token_matcher.h"

/* Config macros -----------------------------------------------------------------*/

/* Export macros -----------------------------------------------------------------*/

/* Exported typedef --------------------------------------------------------------*/

typedef struct tagEm_Parameter {
    uint16_t *index;
    uint8_t maxCnt;
    uint8_t curCnt;
} Em_Parameter;

typedef enum tagEm_ExprResult {
    EM_EXPR_MATCH = 0,
    EM_EXPR_TOKEN_TOO_FEW = 1,
    EM_EXPR_TOKEN_TOO_MANY = 2,
    EM_EXPR_TOKEN_MISMATCH = 3,
    EM_EXPR_WRONG_INPUT = 4,
    EM_EXPR_HELP_LAST_TOKEN = 5,
    EM_EXPR_HELP_NEXT_TOKEN = 6,
} Em_ExprResult;

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported function -------------------------------------------------------------*/

Em_ExprResult Em_TryMatchExpr(const char *ptnExpr, const char *cmdExpr,
    Em_CmpType cmpType, Em_Parameter *param, uint16_t *wrongOffset);

Em_ExprResult Em_TryHelpExpr(const char *ptnExpr, const char *cmdExpr,
    Em_CmpType cmpType, uint16_t *helpPtnOffset, uint16_t *wrongOffset);

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif