/**
 * @file em_editor.c
 * @author CYK-Dot
 * @brief Implementation of a simple editor buffer
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include "em_editor.h"
#include <string.h>
#include <ctype.h>

/* Private macro -----------------------------------------------------------------*/

/* Private typedef ---------------------------------------------------------------*/

typedef enum tagEm_EditorState {
    EM_EDITOR_STATE_NORMAL = 0,
    EM_EDITOR_STATE_ESC = 1,
} Em_EditorState;

/* Private variables -------------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------------*/

/* Exported function -------------------------------------------------------------*/

/**
 * @brief Create a static editor instance
 * @param buf Pointer to the buffer to use
 * @param bufSize Size of the buffer
 * @param staticHandle Pointer to pre-allocated handle
 * @return Editor instance
 */
Em_Editor Em_EditorCreateStatic(char *buf, uint16_t bufSize, Em_EditorImpl *staticHandle)
{
    if (!buf || !staticHandle || bufSize == 0) {
        return NULL;
    }
    staticHandle->buf = buf;
    staticHandle->bufSize = bufSize;
    staticHandle->cursor = 0;
    staticHandle->escStatus = 0;
    memset(buf, 0, bufSize);
    return staticHandle;
}