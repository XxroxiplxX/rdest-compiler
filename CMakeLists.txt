cmake_minimum_required(VERSION 3.10)
project(rdest-compiler)
enable_testing()
set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(include)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(googletest)

if (DEFINED ENV{GITHUB_WORKSPACE})
    set(MY_PROJECT_ROOT_DIR $ENV{GITHUB_WORKSPACE})
else ()
    set(MY_PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif ()

# Domyślne cele
add_executable(rdest-compiler-main  ${MY_PROJECT_ROOT_DIR}/src/main.cpp)
add_executable(rdest-compiler-test  ${MY_PROJECT_ROOT_DIR}/tst/main.cpp)

# Zdefiniuj cele do kompilacji
target_link_libraries(rdest-compiler-test PRIVATE gtest)
target_link_libraries(rdest-compiler-test PRIVATE gtest_main)

# Domyślne cele do uruchamiania
add_custom_target(run
    COMMAND rdest-compiler-main
    DEPENDS rdest-compiler-main
    WORKING_DIRECTORY ${MY_PROJECT_ROOT_DIR}
)

add_custom_target(tst
    COMMAND rdest-compiler-test
    DEPENDS rdest-compiler-test
    WORKING_DIRECTORY ${MY_PROJECT_ROOT_DIR}
)

