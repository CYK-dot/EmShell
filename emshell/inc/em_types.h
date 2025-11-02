/**
 * @file emshell_types.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2025-11-02
 *
 * @copyright Copyright (c) 2025 CYK-Dot, MIT License.
 */
#ifndef __emshell_types_H__
#define __emshell_types_H__

/* Header import ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

/* Config macros -----------------------------------------------------------------*/

#define EM_CONFIG_ADDRESS_ALIGN (4) ///< 4 for MCUs like STM32
#define EM_CONFIG_ESC_SEQUENCE_MAX_LEN (4) ///< max length of escape sequence

/* Export macros -----------------------------------------------------------------*/

#define EM_LIKELY(x)      __builtin_expect(!!(x), 1)
#define EM_UNLIKELY(x)    __builtin_expect(!!(x), 0)

#define EM_ALIGN(x) \
    (((x) + EM_CONFIG_ADDRESS_ALIGN - 1) & ~(EM_CONFIG_ADDRESS_ALIGN - 1))

/* Exported typedef --------------------------------------------------------------*/

typedef struct tagEM_PKG {
    char *inBuf;
    uint16_t inSize;
    uint16_t inNextPos;
    bool isInBufAcquired;
} EM_PKG;

typedef struct tagEM_INST {
    EM_PKG *pkg;

    char *parseBuf;
    uint8_t parseStat;
    uint8_t parsePos;
    
    uint8_t escSeqPosStart;
    uint8_t escSeqPosEnd;
} EM_INST;

typedef enum tagEM_ERRORO {
    EM_OK = 0,
    EM_FAIL,
    EM_INVALID_PARAM,
    EM_OUT_OF_MEMORY,
    EM_NOT_ALLOWED
} EM_ERRO;

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