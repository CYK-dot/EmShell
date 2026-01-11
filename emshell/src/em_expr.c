/**
 * @file em_expr.c
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include <string.h>
#include "em_expr.h"
#include "em_config.h"
#include "em_internal.h"
#include "em_token_matcher.h"

/* Private typedef ----------------------------------------------------------------*/

typedef struct tagEm_ExprItr {
    Em_Pattern ptn;
    Em_PatternImpl ptnImpl;
    Em_Token token;
    Em_TokenImpl tokenImpl;
} Em_ExprItr;

/* Private defines ----------------------------------------------------------------*/

/* Global variables ---------------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------------*/

/* Exported function prototypes --------------------------------------------------*/

/* Private function definitions --------------------------------------------------*/

static inline void prvEm_SafeAddNewParameter(Em_Parameter *param, uint16_t index)
{
    if (param == NULL) {
        return;
    }
    if (param->curCnt < param->maxCnt) {
        param->index[param->curCnt++] = index;
    }
}

static bool prvEm_SetupItr(const char *ptnExpr, const char *cmdExpr, Em_CmpType cmpType, Em_ExprItr *itr)
{
    itr->ptn = Em_GetFirstPattern(ptnExpr, cmpType, &itr->ptnImpl);
    if (itr->ptn == NULL) {
        return false;
    }
    itr->token = Em_GetFirstToken(cmdExpr, &itr->tokenImpl);
    if (itr->token == NULL) {
        return false;
    }
    return true;
}

static Em_ExprResult prvEm_ParsePrefixedTokens(Em_ExprItr *itr, Em_Parameter *param, uint16_t *wrongOffset)
{
    while (itr->ptn != NULL && itr->token != NULL) {
        if (Em_GetPatternType(itr->ptn) == EM_PATTERN_PARAMETER) {
            prvEm_SafeAddNewParameter(param, Em_GetTokenOffset(itr->token));
        } else {
            bool result = Em_TryMatchPatternToToken(itr->ptn, itr->token, wrongOffset);
            if (!result) {
                return EM_EXPR_TOKEN_MISMATCH;
            }
        }
        Em_SelfNextToken(&itr->token);
        Em_SelfNextPattern(&itr->ptn);
    }
    return EM_EXPR_MATCH;
}

/* Exported function definitions -------------------------------------------------*/

/**
 * @brief Try to match the expression with the command.
 * 
 * @param ptnExpr The expression pattern.
 * @param cmdExpr The command to match.
 * @param cmpType The compare type.
 * @param param The parameter to store the matched index.
 * @param wrongOffset The offset of the wrong token.
 * @return Em_ExprResult The result of the match.
 */
Em_ExprResult Em_TryMatchExpr(const char *ptnExpr, const char *cmdExpr,
    Em_CmpType cmpType, Em_Parameter *param, uint16_t *wrongOffset)
{
    if (EM_UNLIKELY(ptnExpr == NULL || cmdExpr == NULL || cmpType >= EM_CMP_UNSPECIFIED)) {
        return EM_EXPR_WRONG_INPUT;
    }
    /* setup expr iterator */
    Em_ExprItr itr = { 0 };
    if (!prvEm_SetupItr(ptnExpr, cmdExpr, cmpType, &itr)) {
        return EM_EXPR_WRONG_INPUT;
    }
    /* compare prefixed tokens */
    Em_ExprResult result = prvEm_ParsePrefixedTokens(&itr, param, wrongOffset);
    if (result != EM_EXPR_MATCH) {
        return result;
    }
    /* compare remained tokens */
    if (itr.ptn == NULL && itr.token != NULL) {
        EM_SAFE_WRITE(wrongOffset, Em_GetTokenOffset(itr.token));
        return EM_EXPR_TOKEN_TOO_MANY;
    } else if (itr.ptn != NULL && itr.token == NULL) {
        EM_SAFE_WRITE(wrongOffset, strlen(cmdExpr));
        return EM_EXPR_TOKEN_TOO_FEW;
    }
    return EM_EXPR_MATCH;
}

/**
 * @brief Try to match the expression with the command to get the help token.
 * 
 * @param ptnExpr The expression pattern.
 * @param cmdExpr The command to match.
 * @param cmpType The compare type.
 * @param helpToken The token to store the help token.
 * @param wrongOffset The offset of the wrong token.
 * @return Em_ExprResult The result of the match.
 */
Em_ExprResult Em_TryHelpExpr(const char *ptnExpr, const char *cmdExpr,
    Em_CmpType cmpType, uint16_t *helpPtnOffset, uint16_t *wrongOffset)
{
    if (EM_UNLIKELY(ptnExpr == NULL || cmdExpr == NULL || cmpType >= EM_CMP_UNSPECIFIED || helpPtnOffset == NULL)) {
        return EM_EXPR_WRONG_INPUT;
    }
    /* setup expr iterator */
    Em_ExprItr itr = { 0 };
    if (!prvEm_SetupItr(ptnExpr, cmdExpr, cmpType, &itr)) {
        return EM_EXPR_WRONG_INPUT;
    }
    /* last token help */
    Em_ExprResult result = prvEm_ParsePrefixedTokens(&itr, NULL, wrongOffset);
    if (result != EM_EXPR_MATCH) {
        Em_SelfNextToken(&itr.token);
        if (itr.token == NULL) {
            *helpPtnOffset = Em_GetPatternOffset(itr.ptn);
            return EM_EXPR_HELP_LAST_TOKEN;
        }
        return EM_EXPR_TOKEN_MISMATCH;
    }
    /* next token help */
    if (itr.ptn == NULL && itr.token != NULL) {
        EM_SAFE_WRITE(wrongOffset, Em_GetTokenOffset(itr.token));
        return EM_EXPR_TOKEN_TOO_MANY;
    } else if (itr.ptn != NULL && itr.token == NULL) {
        *helpPtnOffset = Em_GetPatternOffset(itr.ptn);
        return EM_EXPR_HELP_NEXT_TOKEN;
    }
    return EM_EXPR_MATCH;
}