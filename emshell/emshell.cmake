## ==================================================================================
## @function 
##      emshell_add_library
## @brief 
##      Create an static library target
## @param 
##      TARGET
##      SRC_LIST
##      INC_LIST
##      PRV_INC_LIST
##      DEPEND_LIB
## ==================================================================================
function(emshell_add_library)
    set(options "")
    set(oneValueArgs TARGET)
    set(multiValueArgs SRC_LIST INC_LIST PRV_INC_LIST DEPEND_LIB)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library(${ARG_TARGET} STATIC
        ${ARG_SRC_LIST}
    )
    target_include_directories(${ARG_TARGET} PUBLIC
        ${ARG_INC_LIST}
    )
    target_include_directories(${ARG_TARGET} PRIVATE
        ${ARG_PRV_INC_LIST}
    )
    target_link_libraries(${ARG_TARGET} PRIVATE
        ${ARG_DEPEND_LIB}
    )
    target_compile_options(${ARG_TARGET} PRIVATE
        $<$<CONFIG:Debug>:-g>
    )
    if(CODE_COVERAGE)
        target_compile_options(${ARG_TARGET} PRIVATE --coverage)
        target_link_options(${ARG_TARGET} PRIVATE --coverage)
    endif()
endfunction()