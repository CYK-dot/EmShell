# project
cmake_minimum_required(VERSION 3.14)
project(emshell_test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

# sub-dir
enable_testing()
option(BUILD_TESTS "Build tests" ON)
add_subdirectory(gtest)
add_subdirectory(../emshell emshell_build)

# excutables
add_executable(core_test
    testcase/parser.cc
)
target_link_libraries(core_test PRIVATE
    gtest
    gtest_main
    emshell
)