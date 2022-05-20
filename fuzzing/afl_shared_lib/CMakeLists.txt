cmake_minimum_required(VERSION 3.10)
project(afl_shared_lib)

option(BUILD_SHARED_LIBS "Create as a shared library" ON)

add_library(foo foo.c)
add_library(foo2 foo2.c)

add_executable(bar bar.c)
target_link_libraries(bar foo foo2)
