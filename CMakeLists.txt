cmake_minimum_required(VERSION 3.10)
project(rdest-compiler)
enable_testing()
set(CMAKE_CXX_STANDARD 17)



if (DEFINED ENV{GITHUB_WORKSPACE})
    set(PROJECT_ROOT $ENV{GITHUB_WORKSPACE})
else ()
    set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(compiler-rt)
    message(rt)
    
endif ()

# Compiler-assembler
add_subdirectory(compiler-assembler)

# Compiler-ast
add_subdirectory(compiler-ast)

# Compiler-memory
add_subdirectory(compiler-memory)

# Compiler-rt


# Compiler-utils
#include_directories(compiler-utils compiler-assembler)
add_subdirectory(compiler-utils)
add_subdirectory(googletest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/compiler-utils)

add_custom_target(ut
    COMMAND compilerAstTest
    DEPENDS compilerAstTest
    #COMMAND lib_tst
    #DEPENDS lib_tst
    WORKING_DIRECTORY ${MY_PROJECT_ROOT_DIR}
)
