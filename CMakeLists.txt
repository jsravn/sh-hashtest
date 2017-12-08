# standard
cmake_minimum_required(VERSION 3.8)
project(rpc)

# compiler options
set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -std=gnu99 -g3 -fno-omit-frame-pointer)

# client binaries
add_executable(hashtest hashtest.c)
