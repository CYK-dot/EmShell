/**
 * @file cli_parser.c
 * @author CYK-Dot
 * @brief token parser of EmShell
 * @version 0.1
 * @date 2026-01-10
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include "em_token_matcher.h"
#include "em_config.h"
#include "em_internal.h"

/* Private typedef ----------------------------------------------------------------*/

/* Private defines ----------------------------------------------------------------*/

/* Global variables ---------------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------------*/

/* Exported function prototypes --------------------------------------------------*/

/* Private function definitions --------------------------------------------------*/

/**
 * @note example
 *  itr = "hello"       --> ret = "hello"
 *  itr = "hello world" --> ret = "hello world"
 *  itr = "  hello"     --> ret = "hello"
 *  itr = "$"           --> ret = ""
 *  itr = "$number"     --> ret = "number"
 *  itr = "\n"          --> ret = NULL
 *  itr = " "           --> ret = NULL
 */
static inline char *prvEm_JumpToReadableAscii(char *itr)
{
    for (; !EM_IS_STR_END(*itr); itr++) {
        if (EM_IS_READABLE_ASCII(*itr)) {
            return itr;
        }
    }
    return NULL;
}

/**
 * @note example
 *  itr = "hello"       --> ret = ""
 *  itr = "hello world" --> ret = " world"
 *  itr = "  hello"     --> ret = "  hello"
 *  itr = "\n"          --> ret = "\n"
 *  itr = "$"           --> ret = NULL
 *  itr = ""            --> ret = NULL 
 */
static inline char *prvEm_JumpToTokenEnd(char *itr)
{
    for (; EM_IS_READABLE_ASCII(*itr); itr++);
    if (EM_IS_STR_END(*itr)) {
        return NULL;
    }
    return itr;
}

/**
 * @brief compare the prefix part of ptnToken and token
 * 
 * @param ptnToken pattern token
 * @param token token to be parsed
 * @param ptnTokenSuffix suffix part of ptnToken
 * @param tokenSuffix suffix part of token
 * @return true if prefix part of ptnToken is equal to token
 * @return false if prefix part of ptnToken is not equal to token
 */
static inline bool prvEm_ComparePrefixPart(Em_TokenImpl *ptnToken, Em_TokenImpl *token,
    char **tokenSuffix, char **ptnTokenSuffix)
{
    char *itrPtn = &(ptnToken->src[ptnToken->offset]);
    char *itrToken = &(token->src[token->offset]);
    while (EM_IS_READABLE_ASCII(*itrPtn) && EM_IS_READABLE_ASCII(*itrToken)) {
        if (*itrPtn != *itrToken) {
            *ptnTokenSuffix = itrPtn;
            *tokenSuffix = itrToken;
            return false;
        }
        itrPtn++;
        itrToken++;
    }
    *ptnTokenSuffix = itrPtn;
    *tokenSuffix = itrToken;
    return true;
}

/* Exported function definitions -------------------------------------------------*/

/**
 * @brief get the first token of srcStr
 * 
 * @param srcStr source string
 * @param staticHandle static token handle
 * @return Em_Token first token of srcStr
 */
Em_Token Em_GetFirstToken(const char *srcStr, Em_TokenImpl *staticHandle)
{
    if (EM_UNLIKELY(srcStr == NULL || staticHandle == NULL)) {
        return NULL;
    }
    char *itr = (char *)srcStr;
    itr = prvEm_JumpToReadableAscii(itr);
    if (itr == NULL) {
        return NULL;
    }
    staticHandle->src = (char *)srcStr;
    staticHandle->offset = (uint16_t)(itr - srcStr);
    return (Em_Token)staticHandle;
}

/**
 * @brief get the next token of srcToken
 * 
 * @param srcToken source token
 * @param staticHandle static token handle
 * @return Em_Token next token of srcToken
 */
Em_Token Em_GetNextToken(Em_Token srcToken, Em_TokenImpl *staticHandle)
{
    if (EM_UNLIKELY(srcToken == NULL || staticHandle == NULL)) {
        return NULL;
    }
    char *srcTokenStart = &(EM_TOKEN_TO_IMPL(srcToken)->src[EM_TOKEN_TO_IMPL(srcToken)->offset]);
    char *itr = prvEm_JumpToTokenEnd(srcTokenStart);
    if (itr == NULL) {
        return NULL;
    }
    itr = prvEm_JumpToReadableAscii(itr);
    if (itr == NULL) {
        return NULL;
    }
    staticHandle->src = EM_TOKEN_TO_IMPL(srcToken)->src;
    staticHandle->offset = (uint16_t)(itr - EM_TOKEN_TO_IMPL(srcToken)->src);
    return (Em_Token)staticHandle;
}

/**
 * @brief get the next token of srcToken
 * 
 * @param token token to be parsed
 * @param staticHandle static token handle
 * @return Em_Token next token of srcToken
 */
void Em_SelfNextToken(Em_Token *token)
{
    *token = Em_GetNextToken(*token, EM_TOKEN_TO_IMPL(*token));
}

/**
 * @brief get the offset of token in src
 * 
 * @param token token to be parsed
 * @return uint16_t offset of token in src
 */
uint16_t Em_GetTokenOffset(Em_Token token)
{
    if (EM_UNLIKELY(token == NULL)) {
        return 0;
    }
    return EM_TOKEN_TO_IMPL(token)->offset;
}

/**
 * @brief get the length of token
 * 
 * @param token token to be parsed
 * @return uint8_t length of token
 */
uint8_t Em_GetTokenLength(Em_Token token)
{
    if (EM_UNLIKELY(token == NULL)) {
        return 0;
    }
    char *tokenStart = &(EM_TOKEN_TO_IMPL(token)->src)[EM_TOKEN_TO_IMPL(token)->offset];
    char *tokenEnd = prvEm_JumpToTokenEnd(tokenStart);
    if (tokenEnd == NULL) {
        return 0;
    }
    return (uint8_t)(tokenEnd - tokenStart);
}

/**
 * @brief strip the token of whitespace characters
 * 
 * @param token token to be stripped
 * @param buffer buffer to store the stripped token
 * @param bufferMaxSize maximum size of buffer
 * @return true if success
 * @return false if failed
 */
bool Em_CopyTokenString(Em_Token token, char *buffer, uint8_t bufferMaxSize)
{
    if (EM_UNLIKELY(token == NULL || buffer == NULL || bufferMaxSize == 0)) {
        return false;
    }
    uint8_t index = 0;
    char *srcStr = EM_TOKEN_TO_IMPL(token)->src;
    uint16_t tokenOffset = EM_TOKEN_TO_IMPL(token)->offset;
    for (; index < bufferMaxSize - 1; index++) {
        char tokenChar = srcStr[index + tokenOffset];
        if (!EM_IS_READABLE_ASCII(tokenChar)) {
            break;
        }
        buffer[index] = tokenChar;
    }
    buffer[index] = '\0';
    return true;
}

/**
 * @brief get the first pattern of srcExpr
 * 
 * @param srcExpr source expression
 * @param cmpType comparison type
 * @param staticHandle static pattern handle
 * @return Em_Pattern first pattern of srcExpr
 */
Em_Pattern Em_GetFirstPattern(const char *srcExpr, Em_CmpType cmpType, Em_PatternImpl *staticHandle)
{
    if (EM_UNLIKELY(srcExpr == NULL || staticHandle == NULL || cmpType >= EM_CMP_UNSPECIFIED)) {
        return NULL;
    }
    Em_Token ptnToken = Em_GetFirstToken(srcExpr, &(staticHandle->tokenImpl));
    if (EM_UNLIKELY(ptnToken == NULL)) {
        return NULL;
    }
    staticHandle->token = ptnToken;
    staticHandle->cmpType = cmpType;
    return (Em_Pattern)staticHandle;
}

/**
 * @brief get the next pattern of srcPattern
 * 
 * @param srcPattern source pattern
 * @param staticHandle static pattern handle
 * @return Em_Pattern next pattern of srcPattern
 */
Em_Pattern Em_GetNextPattern(Em_Pattern srcPattern, Em_PatternImpl *staticHandle)
{
    if (EM_UNLIKELY(srcPattern == NULL || staticHandle == NULL)) {
        return NULL;
    }
    Em_Token ptnToken = Em_GetNextToken(EM_PATTERN_TO_IMPL(srcPattern)->token, &(staticHandle->tokenImpl));
    if (EM_UNLIKELY(ptnToken == NULL)) {
        return NULL;
    }
    staticHandle->token = ptnToken;
    staticHandle->cmpType = EM_PATTERN_TO_IMPL(srcPattern)->cmpType;
    return (Em_Pattern)staticHandle;
}

/**
 * @brief get the next pattern of srcPattern
 * 
 * @param pattern pattern to be parsed
 * @param staticHandle static pattern handle
 * @return Em_Pattern next pattern of srcPattern
 */
void Em_SelfNextPattern(Em_Pattern *pattern)
{
    *pattern = Em_GetNextPattern(*pattern, EM_PATTERN_TO_IMPL(*pattern));
}

/**
 * @brief copy the string of pattern to outBuf
 * 
 * @param pattern pattern to be parsed
 * @param outBuf buffer to store the string of pattern
 * @param outBufSize maximum size of outBuf
 * @return Em_Token token of pattern
 */
bool Em_CopyPatternString(Em_Pattern pattern, char *outBuf, uint8_t outBufSize)
{
    if (EM_UNLIKELY(pattern == NULL || outBuf == NULL || outBufSize == 0)) {
        return NULL;
    }
    Em_Token token = EM_PATTERN_TO_IMPL(pattern)->token;
    return Em_CopyTokenString(token, outBuf, outBufSize);
}

/**
 * @brief get the type of pattern
 * 
 * @param pattern pattern to be parsed
 * @return Em_PatternType type of pattern
 */
Em_PatternType Em_GetPatternType(Em_Pattern pattern)
{
    if (EM_UNLIKELY(pattern == NULL)) {
        return EM_PATTERN_UNKNOWN;
    }
    Em_TokenImpl tokenImpl = EM_PATTERN_TO_IMPL(pattern)->tokenImpl;
    if (EM_IS_PARAM(tokenImpl.src[tokenImpl.offset])) {
        return EM_PATTERN_PARAMETER;
    }
    return EM_PATTERN_KEY;
}

/**
 * @brief get the offset of pattern
 * 
 * @param pattern pattern to be parsed
 * @return uint16_t offset of pattern
 */
uint16_t Em_GetPatternOffset(Em_Pattern pattern)
{
    if (pattern == NULL) {
        return 0;
    }
    return Em_GetTokenOffset(EM_PATTERN_TO_IMPL(pattern)->token);
}

/**
 * @brief get the length of pattern
 * 
 * @param pattern pattern to be parsed
 * @return uint8_t length of pattern
 */
uint8_t Em_GetPatternLength(Em_Pattern pattern) 
{
    if (EM_UNLIKELY(pattern == NULL)) {
        return 0;
    }
    return Em_GetTokenLength(EM_PATTERN_TO_IMPL(pattern)->token);
}

/**
 * @brief parse token exactly with format
 * 
 * @param key token to be parsed
 * @param format format to be compared
 * @return Em_CompareRes comparison result
 */
bool Em_TryMatchPatternToToken(Em_Pattern pattern, Em_Token token, uint16_t *mismatchOffset)
{
    /* compare prefix part */
    char *tokenSuffix = NULL;
    char *ptnTokenSuffix = NULL;
    Em_TokenImpl *tokenHandle = EM_TOKEN_TO_IMPL(token);
    Em_TokenImpl *ptnTokenHandle = EM_PATTERN_TO_IMPL(pattern)->token;
    if (prvEm_ComparePrefixPart(ptnTokenHandle, tokenHandle, &tokenSuffix, &ptnTokenSuffix) == false) {
        EM_SAFE_WRITE(mismatchOffset, (uint16_t)(tokenSuffix - tokenHandle->src));
        return false;
    }
    /* compare suffix part(exact match) */
    if (EM_PATTERN_TO_IMPL(pattern)->cmpType == EM_CMP_EXACT) {
        if (!EM_IS_READABLE_ASCII(tokenSuffix[0]) && !EM_IS_READABLE_ASCII(ptnTokenSuffix[0])) {
            return true;
        }
        EM_SAFE_WRITE(mismatchOffset, (uint16_t)(tokenSuffix - tokenHandle->src));
        return false;
    }
    /* compare suffix part(prefix match) */
    if (EM_IS_READABLE_ASCII(tokenSuffix[0])) {
        EM_SAFE_WRITE(mismatchOffset, (uint16_t)(tokenSuffix - tokenHandle->src));
        return false;
    }
    return true;
}