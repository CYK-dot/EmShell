/**
 * @file em_resp_chain.c
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include "em_resp_chain.h"
#include "em_config.h"

/* Private typedef ----------------------------------------------------------------*/

/* Private defines ----------------------------------------------------------------*/

/* Global variables ---------------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------------*/

/* Exported function prototypes --------------------------------------------------*/

/* Private function definitions --------------------------------------------------*/

/* Exported function definitions -------------------------------------------------*/

/**
 * @brief Create a RChain object from a const descriptor.
 * 
 * @param desc The const descriptor of the RChain.
 * @return RChain_Mng The RChain object.
 */
RChain_Mng RChain_CreateStatic(const RChain_Desc *desc)
{
    if (EM_UNLIKELY(!desc || !desc->handleList || !desc->count)) {
        return NULL;
    }
    return desc;
}

/**
 * @brief Process a request through the RChain.
 * 
 * @param mng The RChain object.
 * @param request The request to be processed.
 * @param response The response to be processed.
 * @return void* The pointer to the handler ID that processed the request.
 */
void *RChain_Process(RChain_Mng mng, const void *request, void *response)
{
    if (EM_UNLIKELY(!mng || !request || !response)) {
        return NULL;
    }
    int32_t ret = 0;
    for (; ret < mng->count; ret++) {
        if (mng->handleList[ret].handler(mng->mngId, request, response)) {
            return mng->handleList[ret].id;
        }
    }
    return NULL;
}