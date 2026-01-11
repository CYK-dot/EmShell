### EmShell library =================================================================
add_library(emshell STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/em_token_matcher.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/em_expr.c
)
target_include_directories(emshell PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
target_compile_options(emshell PRIVATE $<$<CONFIG:Debug>:-g>)
if(CODE_COVERAGE)
    target_compile_options(emshell PRIVATE --coverage)
    target_link_options(emshell PRIVATE --coverage)
endif()