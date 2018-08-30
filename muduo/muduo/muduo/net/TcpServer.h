//
// Created by onter on 18-8-28.
//

#ifndef MUDUO_TCPSERVER_H
#define MUDUO_TCPSERVER_H

#include "../base/Atomic.h"
#include "../base/Types.h"
#include "TcpConnection.h"

#include <map>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace jmuduo
{
    namespace net
    {
        class Acceptor;
        class EventLoop;
        class EventLoopThreadPool;

        class TcpServer: boost::noncopyable
        {
        public:
            typedef boost::function<void(EventLoop *)> ThreadInitCallback;
            enum Option
            {
                kNoReusePort,
                kReusePort,
            };
            //TcpServer(EventLoop* loop, const InetAddress& listenAddr);
            TcpServer(EventLoop* loop,
                      const InetAddress& listenAddr,
                      const string& nameArg,
                      Option option = kNoReusePort);
            ~TcpServer();  // force out-line dtor, for scoped_ptr members.

            const string& ipPort() const { return ipPort_; }
            const string& name() const { return name_; }
            EventLoop* getLoop() const { return loop_; }

            /// Set the number of threads for handling input.
            ///
            /// Always accepts new connection in loop's thread.
            /// Must be called before @c start
            /// @param numThreads
            /// - 0 means all I/O in loop's thread, no thread will created.
            ///   this is the default value.
            /// - 1 means all I/O in another thread.
            /// - N means a thread pool with N threads, new connections
            ///   are assigned on a round-robin basis.
            void setThreadNum(int numThreads);
            void setThreadInitCallback(const ThreadInitCallback& cb)
            { threadInitCallback_ = cb; }
            boost::shared_ptr<EventLoopThreadPool> threadPool()
            { return threadPool_; }

            /// Starts the server if it's not listenning.
            ///
            /// It's harmless to call it multiple times.
            /// Thread safe.
            void start();

            /// Set connection callback.
            /// Not thread safe.
            void setConnectionCallback(const ConnectionCallback& cb)
            { connectionCallback_ = cb; }

            /// Set message callback.
            /// Not thread safe.
            void setMessageCallback(const MessageCallback& cb)
            { messageCallback_ = cb; }

            /// Set write complete callback.
            /// Not thread safe.
            void setWriteCompleteCallback(const WriteCompleteCallback& cb)
            { writeCompleteCallback_ = cb; }
        private:
            /// Not thread safe but in loop
            void newConnection(int sockfd, const InetAddress& peerAddr);
            /// Thread safe
            void removeConnection(const TcpConnectionPtr& conn);
            /// Not thread safe, but in loop
            void removeConnectionInLoop(const TcpConnectionPtr& ptr);

            typedef std::map<string, TcpConnectionPtr> ConnectionMap;
            EventLoop* loop_;
            const string ipPort_;
            const string name_;
            boost::scoped_ptr<Acceptor> acceptor_;
            boost::shared_ptr<EventLoopThreadPool> threadPool_;
            ConnectionCallback connectionCallback_;
            MessageCallback messageCallback_;
            ThreadInitCallback threadInitCallback_;
            WriteCompleteCallback writeCompleteCallback_;
            AtomicInt32 started_;
            int nextConnId_;
            ConnectionMap connections_;
        };
    }
}
#endif //MUDUO_TCPSERVER_H
