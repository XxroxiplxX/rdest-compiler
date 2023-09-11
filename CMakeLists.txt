cmake_minimum_required(VERSION 3.10)
project(rdest-compiler)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(include)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(googletest)