cmake_minimum_required(VERSION 3.9)
project(md5)

set(CMAKE_CXX_STANDARD 11)

add_executable(md5
        md5.cc md5.h main.cc)