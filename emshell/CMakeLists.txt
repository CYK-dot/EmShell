file(GLOB_RECURSE src_c ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE src_cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(emshell 
    STATIC 
    ${src_c}
    ${src_cpp}
)

target_include_directories(emshell
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:inc>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)