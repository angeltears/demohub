cmake_minimum_required(VERSION 3.9)
project(sha_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(sha_1
        main.cc sha.cc sha.h)
