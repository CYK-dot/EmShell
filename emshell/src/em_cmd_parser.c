/**
 * @file em_cmd_parser.c
 * @author CYK-Dot
 * @brief parse command input from raw byte stream
 * @version 0.1
 * @date 2025-11-02
 * ----------------------------------------------------------------------------------
 * supported ASCII control bytes:
 * - \b: backspace
 * - \x7f: delete
 * - \r: enter
 * - \t: tab
 * - ctrl+c: interrupt
 * 
 * supported ESC sequences:
 * - \033[D: left arrow
 * - \033[C: right arrow
 * - \033[A: up arrow
 * - \033[B: down arrow
 * ----------------------------------------------------------------------------------
 * @copyright Copyright (c) 2025 CYK-Dot, MIT License.
 */

/* Header import ------------------------------------------------------------------*/
#include "em_core.h"

/* Private typedef ----------------------------------------------------------------*/

/* Private defines ----------------------------------------------------------------*/

#define PARSE_STAT_HEAD_SPACE 0
#define PARSE_STAT_ASCII 1
#define PARSE_STATE_INTER_SPACE 2
#define PARSE_STAT_ESC_HEAD 3
#define PARSE_STAT_ESC_INIT 4

/* Global variables ---------------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------------*/

/* Exported function prototypes --------------------------------------------------*/

/* Private function definitions --------------------------------------------------*/

/**
 * @addtogroup utils
 * @brief Check if the byte is a valid ASCII character.
 */
static inline bool EM_ParseUtil_IsAsciiStr(char byte)
{
    bool isAlpha  = (byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z');
    bool isNum    = (byte >= '0' && byte <= '9');
    bool isSymbol = (byte == '_' || byte == '-');
    return isAlpha || isNum || isSymbol;
}

/**
 * @addtogroup utils
 * @brief Check if the byte is a valid tail character of an escape sequence.
 */
static inline bool EM_ParseUtil_IsEscTail(char byte)
{
    return (byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z');
}

/**
 * @addtogroup excutors
 * @brief Execute the ASCII control character.
 * 
 * @param instance The instance of the shell.
 * @param byte The ASCII control character.
 */
static inline void EM_ParseExcutor_AsciiCtrl(EM_INST *instance, char byte)
{
    switch (byte) {
        // backspace
        case '\b':
            break;
        // delete
        case '\x7f':
            break;
        // enter
        case '\r':
            break;
        // tab
        case '\t':
            break;
        // ctrl+c
        case '\x03':
            break;
    }
}

/**
 * @addtogroup excutors
 * @brief Execute the ASCII string character.
 * 
 * @param instance The instance of the shell.
 * @param byte The ASCII string character.
 */
static inline void EM_ParseExcutor_AsciiStr(EM_INST *instance, char byte)
{
    instance->parseBuf[instance->parsePos++] = byte;
}

/**
 * @addtogroup excutors
 * @brief Execute the ASCII character, includes string and control character.
 * 
 * @param instance The instance of the shell.
 * @param byte The ASCII character.
 */
static inline void EM_ParseExcutor_Ascii(EM_INST *instance, char byte)
{
    if (EM_ParseUtil_IsAsciiStr(byte)) {
        EM_ParseExcutor_AsciiStr(instance, byte);
    } else {
        EM_ParseExcutor_AsciiCtrl(instance, byte);
    }
}

/**
 * @addtogroup excutors
 * @brief Execute the escape sequence character.
 * 
 * @param instance The instance of the shell.
 * @param byte The escape sequence character.
 */
static inline void EM_ParseExcutor_EscSeq(EM_INST *instance, char byte)
{
    
}

/**
 * @addtogroup FSM-Functors
 * @brief FSM state-function of PARSE_STAT_HEAD_SPACE
 * 
 * @param instance The instance of the shell.
 * @param byte The head space character.
 * @return uint8_t The next state of the parse machine.
 */
static inline uint8_t EM_ParseFsmFunctor_HeadSpace(EM_INST *instance, char byte)
{
    if (byte == ' ') {
        return PARSE_STAT_HEAD_SPACE;
    } else if (byte == '\033') {
        return PARSE_STAT_ESC_HEAD;
    } else {
        return PARSE_STAT_ASCII;
    }
}

/**
 * @addtogroup FSM-Functors
 * @brief FSM state-function of PARSE_STAT_ASCII
 * 
 * @param instance The instance of the shell.
 * @param byte The ASCII character.
 * @return uint8_t The next state of the parse machine.
 */
static inline uint8_t EM_ParseFsmFunctor_Ascii(EM_INST *instance, char byte)
{
    if (EM_ParseUtil_IsAsciiStr(byte)) {
        EM_ParseExcutor_AsciiStr(instance, byte);
        return PARSE_STAT_ASCII;
    } else if (byte == ' ') {
        return PARSE_STATE_INTER_SPACE;
    } else if (byte == '\033') {
        return PARSE_STAT_ESC_HEAD;
    } else {
        EM_ParseExcutor_AsciiCtrl(instance, byte);
        return PARSE_STAT_ASCII;
    }
}

/**
 * @addtogroup FSM-Functors
 * @brief FSM state-function of PARSE_STATE_INTER_SPACE
 * 
 * @param instance The instance of the shell.
 * @param byte The inter space character.
 * @return uint8_t The next state of the parse machine.
 */
static inline uint8_t EM_ParseFsmFunctor_InterSpace(EM_INST *instance, char byte)
{
    if (byte == ' ') {
        return PARSE_STATE_INTER_SPACE;
    } else if (byte == '\033') {
        return PARSE_STAT_ESC_HEAD;
    } else {
        EM_ParseExcutor_Ascii(instance, byte);
        return PARSE_STAT_ASCII;
    }
}

/**
 * @addtogroup FSM-Functors
 * @brief FSM state-function of PARSE_STAT_ESC_HEAD
 * 
 * @param instance The instance of the shell.
 * @param byte The esc head character.
 * @return uint8_t The next state of the parse machine.
 */
static inline uint8_t EM_ParseFsmFunctor_EscHead(EM_INST *instance, char byte)
{
    if (byte == '[') {
        instance->parseStat = PARSE_STAT_ESC_INIT; 
        instance->escSeqPosStart = instance->pkg->inNextPos;
        instance->escSeqPosEnd = instance->pkg->inNextPos;
        return PARSE_STAT_ESC_INIT;
    } else {
        return PARSE_STAT_ASCII;
    }
}

/**
 * @addtogroup FSM-Functors
 * @brief FSM state-function of PARSE_STAT_ESC_INIT
 * 
 * @param instance The instance of the shell.
 * @param byte The esc init character.
 * @return uint8_t The next state of the parse machine.
 */
static inline uint8_t EM_ParseFsmFunctor_EscInit(EM_INST *instance, char byte)
{
    if (instance->escSeqPosEnd - instance->escSeqPosStart < EM_CONFIG_ESC_SEQUENCE_MAX_LEN) {
        instance->escSeqPosEnd++;
        return PARSE_STAT_ESC_INIT;
    } else if (EM_ParseUtil_IsEscTail(byte)) {
        EM_ParseExcutor_EscSeq(instance, byte);
        return PARSE_STAT_ASCII;
    }
}

/**
 * @addtogroup FSM-Main
 * @brief Parse the input byte stream to the parse buffer.
 * 
 * @param instance The instance of the shell.
 * @param byte The input byte stream.
 * @return EM_ERRO The error code.
 */
static inline EM_ERRO EM_ParseFsm(EM_INST *instance, char byte)
{
    EM_ERRO retVal = EM_OK;
    switch (instance->parseStat) {
        case PARSE_STAT_HEAD_SPACE:
            instance->parseStat = EM_ParseFsmFunctor_HeadSpace(instance, byte);
            break;
        case PARSE_STAT_ASCII:
            instance->parseStat = EM_ParseFsmFunctor_Ascii(instance, byte);
            break;
        case PARSE_STATE_INTER_SPACE:
            instance->parseStat = EM_ParseFsmFunctor_InterSpace(instance, byte);
            break;
        case PARSE_STAT_ESC_HEAD:
            instance->parseStat = EM_ParseFsmFunctor_EscHead(instance, byte);
            break;
        case PARSE_STAT_ESC_INIT:
            instance->parseStat = EM_ParseFsmFunctor_EscInit(instance, byte);
            break;
    }
    return EM_OK;
}

/* Exported function definitions -------------------------------------------------*/

/**
 * @brief asynchronously send byte stream to EM-Shell and excute command
 * 
 * @param instance EM-Shell instance
 * @param inBuf input buffer pointer
 * @param len length of input buffer
 * @return EM_ERRO 
 */
EM_ERRO EM_Send(EM_INST *instance, const char *inBuf, uint16_t len)
{
    if (EM_UNLIKELY(instance == NULL || instance->pkg == NULL || inBuf == NULL)) {
        return EM_INVALID_PARAM;
    }
    if (EM_UNLIKELY(len > instance->pkg->inSize - instance->pkg->inNextPos)) {
        return EM_OUT_OF_MEMORY;
    }
    for (uint16_t i = 0; i < len; i++) {
        if (EM_UNLIKELY(EM_ParseFsm(instance, inBuf[i]) != EM_OK)) {
            return EM_FAIL;
        }
    }
    return EM_OK;
}
