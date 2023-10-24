cmake_minimum_required(VERSION 3.10)
project(rdest-compiler)
enable_testing()
set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(include)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(googletest)
if (CMAKE_BUILD_TYPE STREQUAL "compiler")
    set(COMP_ON true)
else ()
    set(COMP_ON false)
endif ()
set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
configure_file( ${CMAKE_SOURCE_DIR}/src/CMakeLists.txt  ${CMAKE_SOURCE_DIR}/src/CMakeLists.txt)
# Domyślne cele
add_executable(rdest-compiler-main  ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_executable(rdest-compiler-test  ${CMAKE_SOURCE_DIR}/tst/main.cpp)
#add_executable(rdest-compiler-comp src/parsery.cpp)

# Zdefiniuj cele do kompilacji
target_link_libraries(rdest-compiler-test PRIVATE gtest)
target_link_libraries(rdest-compiler-test PRIVATE gtest_main)

# Domyślne cele do uruchamiania
add_custom_target(run
    COMMAND rdest-compiler-main
    DEPENDS rdest-compiler-main
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(tst
    COMMAND rdest-compiler-test
    DEPENDS rdest-compiler-test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_custom_target(compiler
    COMMAND rdest-compiler-comp
    DEPENDS rdest-compiler-comp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
