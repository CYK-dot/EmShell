/**
 * @file em_editor.h
 * @author CYK-Dot
 * @brief Brief description
 * @version 0.1
 * @date 2026-01-11
 *
 * @copyright Copyright (c) 2026 CYK-Dot, MIT License.
 */
#ifndef __em_editor_H__
#define __em_editor_H__

/* Header import ------------------------------------------------------------------*/
#include <stdint.h>

/* Config macros -----------------------------------------------------------------*/

/* Export macros -----------------------------------------------------------------*/

/* Exported typedef --------------------------------------------------------------*/

typedef enum tagEm_EditorEvent {
    EM_EDITOR_EVENT_NONE = 0,
    EM_EDITOR_EVENT_OVERFLOW = 1,
    EM_EDITOR_EVENT_COMMIT = 2,
} Em_EditorEvent;

typedef struct tagEm_EditorImpl {
    char *buf;
    uint16_t bufSize;
    uint16_t cursor;
    uint8_t escStatus;
} Em_EditorImpl;
typedef Em_EditorImpl* Em_Editor;

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* Exported function -------------------------------------------------------------*/

Em_Editor Em_EditorCreateStatic(char *buf, uint16_t bufSize, Em_EditorImpl *staticHandle);
Em_EditorEvent Em_EditorFeed(Em_Editor editor, char c);

/* C++ ---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif