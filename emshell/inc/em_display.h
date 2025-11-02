/**
 * @file emshell_display.h
 * @author CYK-Dot
 * @brief CLI display APIs
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025 CYK-Dot, MIT License.
 */
#ifndef __emshell_display_H__
#define __emshell_display_H__

/* Header import ------------------------------------------------------------------*/
#include "em_types.h"

/* Config macros -----------------------------------------------------------------*/

/* Export macros -----------------------------------------------------------------*/

/* Exported typedef --------------------------------------------------------------*/

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported function -------------------------------------------------------------*/

/**
 * @brief clear screen
 * 
 * @param outBuf output buffer pointer
 * @param bufSize size of output buffer
 * @param writePos write position in output buffer
 * @return EM_ERRO 
 */
static inline EM_ERRO EM_DispClrScrn(char *outBuf, uint16_t bufSize, uint16_t *writePos)
{
    if (EM_UNLIKELY(*writePos + 4 >= bufSize)) {
        return EM_OUT_OF_MEMORY;
    }
    outBuf[*writePos] = '\033';
    outBuf[*writePos + 1] = '[';
    outBuf[*writePos + 2] = '2';
    outBuf[*writePos + 3] = 'J';
    *writePos += 4;
    return EM_OK;
}

/**
 * @brief clear line
 * 
 * @param outBuf output buffer pointer
 * @param bufSize size of output buffer
 * @param writePos write position in output buffer
 * @return EM_ERRO 
 */
static inline EM_ERRO EM_DispClrLine(char *outBuf, uint16_t bufSize, uint16_t *writePos)
{
    if (EM_UNLIKELY(*writePos + 4 >= bufSize)) {
        return EM_OUT_OF_MEMORY;
    }
    outBuf[*writePos] = '\033';
    outBuf[*writePos + 1] = '[';
    outBuf[*writePos + 2] = '2';
    outBuf[*writePos + 3] = 'K';
    *writePos += 4;
    return EM_OK;
}

/**
 * @brief backspace
 * 
 * @param outBuf output buffer pointer
 * @param bufSize size of output buffer
 * @param writePos write position in output buffer
 * @return EM_ERRO 
 */
static inline EM_ERRO EM_DispBackspace(char *outBuf, uint16_t bufSize, uint16_t *writePos)
{
    if (EM_UNLIKELY(*writePos + 2 >= bufSize)) {
        return EM_OUT_OF_MEMORY;
    }
    outBuf[*writePos] = '\b';
    outBuf[*writePos + 1] = ' ';
    *writePos += 2;
    return EM_OK;
}

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif