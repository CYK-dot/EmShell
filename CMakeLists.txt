### project configurations ==========================================================
cmake_minimum_required(VERSION 3.14)
project(EmShell VERSION 1.0.0 LANGUAGES C CXX)

### cmake imports ===================================================================
include(./test_framework/test_framework.cmake)

### global cmake configs ============================================================
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
enable_test_framework()
enable_code_coverage()

### subdir imports ==================================================================
add_subdirectory(./emshell)

### EmShell testcases ===============================================================
file(GLOB_RECURSE
    TESTCASE_SOURCES 
        "${CMAKE_SOURCE_DIR}/testcases_ut/*.cpp"
        "${CMAKE_SOURCE_DIR}/testcases_ct/*.cpp"
)
add_test_executable(
    TARGET test_emshell
    TESTCASE_SOURCES ${TESTCASE_SOURCES}
    PRODUCT_LIBS
        emshell_util 
        emshell_core
)
add_coverage_target(
    TARGET cov
    TEST_TARGET test_emshell
    REPORT_DIR ${CMAKE_BINARY_DIR}/coverage
    INCLUDE_PATTERNS "emshell/*"
    EXCLUDE_PATTERNS "testcases/*"
)
