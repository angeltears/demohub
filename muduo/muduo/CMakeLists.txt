cmake_minimum_required(VERSION 3.5.1)
project(muduo)

enable_testing()

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

set(base_SRCS
        muduo/base/Thread.cpp
        muduo/base/Thread.h
        muduo/base/Exception.h
        muduo/base/Exception.cpp
        muduo/base/ThreadLocal.h
        muduo/base/Timestamp.cc
        muduo/base/Types.h
        muduo/base/ThreadPoll.cpp
        muduo/base/ThreadPool.h
        muduo/base/Timestamp.h
        muduo/base/Atomic.h
        muduo/base/Condition.hpp
        muduo/base/copyable.h
        muduo/base/Mutex.hpp
        muduo/base/BlockingQueue.hpp
        muduo/base/BoundedBlockingQueue.hpp
        muduo/base/CountDownLatch.hpp
        muduo/base/CurrentThread.h
        muduo/base/ThreadLocalSingletion.h
        muduo/base/StringPiece.h
        muduo/base/ProcessInfo.h
        muduo/base/ProcessInfo.cc
        muduo/base/FileUtil.h
        muduo/base/FileUtil.cc
        muduo/base/LogStream.h
        muduo/base/LogStream.cc
        muduo/base/Loggin.h
        muduo/base/Loggin.cc
        muduo/base/TimeZone.h
        muduo/base/TimeZone.cc
        muduo/base/Date.h
        muduo/base/Date.cc
        muduo/base/LogFile.cpp
        muduo/base/LogFile_test.hpp muduo/base/WeakCallback.h)

add_library(muduo_base ${base_SRCS})
target_link_libraries(muduo_base pthread rt)

install(TARGETS muduo_base DESTINATION lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/muduo/base)

set(net_SRCS
        muduo/net/Poller.cpp
        muduo/net/Poller.hpp
        muduo/net/EventLoop.cc
        muduo/net/EventLoop.h
        muduo/net/Channel.cc
        muduo/net/Channel.h
        muduo/net/Poller/DefaultPoller.cc
        muduo/net/Poller/PollPoller.cpp
        muduo/net/Poller/PollPoller.hpp
        muduo/net/Poller/EPollPoller.cc
        muduo/net/Poller/EPollPoller.h
        muduo/net/Callbacks.h
        muduo/net/TimerQueue.cc
        muduo/net/TimerQueue.h
        muduo/net/TimerId.h
        muduo/net/Timer.cc
        muduo/net/Timer.h
        muduo/net/EventLoopThread.cc
        muduo/net/EventLoopThread.h
        muduo/net/SocketsOpt.cc
        muduo/net/SocketsOpt.h
        muduo/net/Endian.h
        muduo/net/Socket.cc
        muduo/net/Socket.h
        muduo/net/InetAddress.cc
        muduo/net/InetAddress.h
        muduo/net/Connector.cc
        muduo/net/Connector.h
        muduo/net/TcpConnection.cc
        muduo/net/TcpConnection.h
        muduo/net/Buffer.cc
        muduo/net/Buffer.h muduo/net/EventLoopThreadPool.cc muduo/net/EventLoopThreadPool.h muduo/net/TcpServer.cc muduo/net/TcpServer.h muduo/net/Acceptor.cc muduo/net/Acceptor.h muduo/net/TcpClient.cc muduo/net/TcpClient.h)


add_library(muduo_net ${net_SRCS})
target_link_libraries(muduo_net muduo_base)

add_executable(ThreadLocal_test
       muduo/test/base/TheadLocal_test.cc)
target_link_libraries(ThreadLocal_test muduo_base)


add_executable(Atomic_unittest
        muduo/test/base/Atomic_unittest.cpp )
target_link_libraries(Atomic_unittest muduo_base)


add_executable(ThreadLocalSingle_test
        muduo/test/base/ThreadLocalSingle_test.cc)
target_link_libraries(ThreadLocalSingle_test muduo_base)

add_executable(LogStream_test
        muduo/test/base/LogStream_test.cc)
target_link_libraries(LogStream_test  muduo_base)


add_executable(Logging_test
        muduo/test/base/Logging_test.cc)
target_link_libraries(Logging_test muduo_base)

add_executable(LogFile_test
        muduo/test/base/LogFile_test.cc)
target_link_libraries(LogFile_test muduo_base)

add_executable(EventLoop_test
        muduo/test/net/EventLoop_unittest.cc)
target_link_libraries(EventLoop_test muduo_net)

add_executable(EventLoopThread_test
        muduo/test/net/EventLoopThread_unittest.cc)
target_link_libraries(EventLoopThread_test muduo_net)

add_executable(Buffer_test
        muduo/test/net/Buffer_unittest.cc)
target_link_libraries(Buffer_test muduo_net)

add_executable(EventLoopThreadPoll_test
        muduo/test/net/EventLoopThreadPoll_test.cc)
target_link_libraries(EventLoopThreadPoll_test muduo_net)

add_executable(TcpClient_reg1
        muduo/test/net/TcpClient_reg1.cc)
target_link_libraries(TcpClient_reg1 muduo_net)

add_executable(TcpClient_reg2
        muduo/test/net/TcpClient_reg2.cc)
target_link_libraries(TcpClient_reg2 muduo_net)

add_executable(TcpClient_reg3
        muduo/test/net/TcpClient_reg3.cc)
target_link_libraries(TcpClient_reg3 muduo_net)

add_executable(EchoServer_unittest
        muduo/test/net/EchoServer_unittest.cc)
target_link_libraries(EchoServer_unittest muduo_net)
