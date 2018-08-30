//
// Created by onter on 18-8-30.
//

#ifndef MUDUO_TCPCLIENT_H
#define MUDUO_TCPCLIENT_H


#include <boost/noncopyable.hpp>
#include "../base/Mutex.hpp"
#include "TcpConnection.h"


namespace jmuduo
{
    namespace net
    {
        class Connector;
        typedef boost::shared_ptr<Connector> ConnectorPtr;

        class TcpClient : boost::noncopyable
        {
        public:
            TcpClient(EventLoop* loop, const InetAddress& serverAddr, const string& nameArg);
            ~TcpClient();

            void connect();
            void disconnect();
            void stop();

            TcpConnectionPtr connection() const
            {
                MutexLockGuard lock(mutex_);
                return connection_;
            }

            EventLoop* getLoop() const { return loop_; }
            bool retry() const { return retry_; }
            void enableRetry() { retry_ = true; }

            const string& name() const
            { return name_; }
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

#ifdef __GXX_EXPERIMENTAL_CXX0X__
            void setConnectionCallback(ConnectionCallback&& cb)
            { connectionCallback_ = std::move(cb); }
            void setMessageCallback(MessageCallback&& cb)
            { messageCallback_ = std::move(cb); }
            void setWriteCompleteCallback(WriteCompleteCallback&& cb)
            { writeCompleteCallback_ = std::move(cb); }
#endif
        private:
            /// not thread safe but in loop
            void newConnnection(int sockfd);
            /// not thread safe but in loop
            void removeConnection(const TcpConnectionPtr& conn);

            EventLoop* loop_;
            ConnectorPtr connector_;
            const string name_;
            ConnectionCallback connectionCallback_;
            MessageCallback messageCallback_;
            WriteCompleteCallback writeCompleteCallback_;
            bool retry_;
            bool connect_;
            int nextConnId_;
            mutable MutexLock mutex_;
            TcpConnectionPtr connection_;
        };
    }
}
#endif //MUDUO_TCPCLIENT_H
