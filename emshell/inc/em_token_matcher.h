/**
 * @file cli_parser.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-10
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */
#ifndef __em_token_matcher_H__
#define __em_token_matcher_H__

/* Header import ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Config macros -----------------------------------------------------------------*/

/* Export macros -----------------------------------------------------------------*/

/* Exported typedef --------------------------------------------------------------*/

typedef enum tagEm_CmpType {
    EM_CMP_EXACT = 0,
    EM_CMP_WITH_PREFIX = 1,
    EM_CMP_UNSPECIFIED = 2,
} Em_CmpType;

typedef enum tagEm_PatternType {
    EM_PATTERN_KEY = 0,
    EM_PATTERN_PARAMETER = 1,
    EM_PATTERN_UNKNOWN,
} Em_PatternType;

typedef struct tagEm_TokenImpl {
    char *src;
    uint16_t offset;
} Em_TokenImpl;
typedef Em_TokenImpl* Em_Token;

typedef struct tagEm_PatternImpl {
    Em_TokenImpl tokenImpl;
    Em_Token token;
    Em_CmpType cmpType;
} Em_PatternImpl;
typedef Em_PatternImpl* Em_Pattern;


/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported function -------------------------------------------------------------*/

/**
 * @addtogroup token constructor
 */
Em_Token Em_GetFirstToken(const char *srcExpr, Em_TokenImpl *staticHandle);
Em_Token Em_GetNextToken(Em_Token srcToken, Em_TokenImpl *staticHandle);
void Em_SelfNextToken(Em_Token *token);

/**
 * @addtogroup token method
 */
bool Em_CopyTokenString(Em_Token token, char *outBuf, uint8_t outBufSize);
uint16_t Em_GetTokenOffset(Em_Token token);
uint8_t Em_GetTokenLength(Em_Token token);

/**
 * @addtogroup pattern constructor
 */
Em_Pattern Em_GetFirstPattern(const char *srcExpr, Em_CmpType cmpType, Em_PatternImpl *staticHandle);
Em_Pattern Em_GetNextPattern(Em_Pattern srcPattern, Em_PatternImpl *staticHandle);
void Em_SelfNextPattern(Em_Pattern *pattern);

/**
 * @addtogroup pattern method
 */
bool Em_CopyPatternString(Em_Pattern pattern, char *outBuf, uint8_t outBufSize);
Em_PatternType Em_GetPatternType(Em_Pattern pattern);
uint16_t Em_GetPatternOffset(Em_Pattern pattern);
uint8_t Em_GetPatternLength(Em_Pattern pattern);
bool Em_TryMatchPatternToToken(Em_Pattern pattern, Em_Token token, uint16_t *mismatchOffset);

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif