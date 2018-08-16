cmake_minimum_required(VERSION 3.9)
project(muduo)

set(CMAKE_CXX_STANDARD 11)

set(CXX_FLAGS
        -g
        # -DVALGRIND
        # -DMUDUO_STD_STRING
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -Wextra
        -Werror
        -Wconversion
        -Wno-unused-parameter
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        -Wshadow
        -Wwrite-strings
        -march=native
        # -MMD
        # -std=c++0x
        -rdynamic
        -std=c++11
        )

add_executable(muduo
        muduo/base/copyable.h
        muduo/base/Timestamp.cc
        muduo/base/Timestamp.h
        muduo/base/Types.h
        muduo/base/Atomic.h
        muduo/base/Exception.cpp
        muduo/base/Exception.h
        muduo/test/base/Exception_unittest.cpp
        muduo/base/CurrentThread.h
        muduo/base/Thread.h
        muduo/base/Mutex.hpp
        muduo/base/Condition.hpp
        muduo/base/CountDownLatch.hpp
        muduo/base/Thread.cpp)

include_directories(${PROJECT_SOURCE_DIR})
TARGET_LINK_LIBRARIES(muduo pthread)