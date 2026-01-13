/**
 * @file em_resp_chain.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-12
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */
#ifndef __em_resp_chain_H__
#define __em_resp_chain_H__

#include <stdbool.h>
#include <stdint.h>

typedef bool (*RChainHandler)(uint8_t mngId, const void *request, void *response);

typedef struct tagRChain_Handler {
    void *id;
    RChainHandler handler;
} RChain_Handler;

typedef struct tagRChain_Desc {
    RChain_Handler *handleList;
    uint16_t count;
    uint8_t mngId;
} RChain_Desc;

typedef const RChain_Desc* RChain_Mng;

#ifdef __cplusplus
extern "C" {
#endif

RChain_Mng RChain_CreateStatic(const RChain_Desc *desc);
void *RChain_Process(RChain_Mng mng, const void *request, void *response);

#ifdef __cplusplus
}
#endif

#endif