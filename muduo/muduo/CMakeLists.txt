cmake_minimum_required(VERSION 3.9)
project(muduo)

set(CMAKE_CXX_STANDARD 11)

add_executable(muduo
        muduo/base/copyable.h
        muduo/base/Timestamp.cc
        muduo/base/Timestamp.h
        muduo/base/Types.h
        muduo/base/Atomic.h
        muduo/test/base/Atomic_unittest.cpp)
