include(emshell.cmake)

## ==================================================================================
## @library
##      emshell_common
## @brief
##      commonly used headers
## ==================================================================================
add_library(emshell_common INTERFACE)
target_include_directories(emshell_common INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

## ==================================================================================
## @library
##      libemshell_util.a
## @brief
##      utilities
## ==================================================================================
emshell_add_library(
    TARGET
        emshell_util
    SRC_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/util/src/em_resp_chain.c
    INC_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/util/inc
    DEPEND_LIB
        emshell_common
)

## ==================================================================================
## @library
##      libemshell_core.a
## @brief
##      basic parser and editor
## ==================================================================================
emshell_add_library(
    TARGET
        emshell_core
    SRC_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/core/src/em_token_matcher.c
        ${CMAKE_CURRENT_SOURCE_DIR}/core/src/em_expr.c
    INC_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/core/inc
    PRV_INC_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/core/src
    DEPEND_LIB
        emshell_common
        emshell_util
)