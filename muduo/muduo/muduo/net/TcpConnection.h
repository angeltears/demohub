//
// Created by onter on 18-8-27.
//

#ifndef MUDUO_TCPCONNECTION_H
#define MUDUO_TCPCONNECTION_H
#include "../base/StringPiece.h"
#include "../base/Types.h"
#include "Callbacks.h"
#include "Buffer.h"
#include "InetAddress.h"

#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

struct tcp_info;


namespace jmuduo
{
    namespace net
    {
        class Channel;
        class EventLoop;
        class Socket;

        class TcpConnection:boost::noncopyable,
                            public boost::enable_shared_from_this<TcpConnection>
        {
        public:

            TcpConnection(EventLoop* loop,
                          const string& name,
                          int sockfd,
                          const InetAddress& localAddr,
                          const InetAddress& peerAddr);
            ~TcpConnection();

            EventLoop* getLoop() const { return loop_; }
            const string& name() const { return name_; }
            const InetAddress& localAddress() const { return localAddr_; }
            const InetAddress& peerAddress() const { return peerAddr_; }
            bool connected() const { return state_ == kConnected; }
            bool disconnected() const { return state_ == kDisconnected; }
            // return true if success.
            bool getTcpInfo(struct tcp_info*) const;
            string getTcpInfoString() const;


            // void send(string&& message); // C++11
            void send(const void* message, int len);
            void send(const StringPiece& message);
            // void send(Buffer&& message); // C++11
            void send(Buffer* message);  // this one will swap data
            void shutdown(); // NOT thread safe, no simultaneous calling
            // void shutdownAndForceCloseAfter(double seconds); // NOT thread safe, no simultaneous calling

            void forceClose();
            void forceCloseWithDelay(double seconds);
            void setTcpNoDelay(bool on);
            // reading or not
            void startRead();
            void stopRead();
            bool isReading() const { return reading_; }; // NOT thread safe, may race with start/stopReadInLoop


            void setContext(const boost::any& context)
            { context_ = context; }

            const boost::any& getContext() const
            { return context_; }

            boost::any* getMutableContext()
            { return &context_; }

            void setConnectionCallback(const ConnectionCallback& cb)
            { connectionCallback_ = cb; }

            void setMessageCallback(const MessageCallback& cb)
            { messageCallback_ = cb; }

            void setWriteCompleteCallback(const WriteCompleteCallback& cb)
            { writeCompleteCallback_ = cb; }

            void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t highWaterMark)
            { highWaterMarkCallback_ = cb; highWaterMark_ = highWaterMark; }

            /// Advanced interface
            Buffer* inputBuffer()
            { return &inputBuffer_; }

            Buffer* outputBuffer()
            { return &outputBuffer_; }

            /// Internal use only.
            void setCloseCallback(const CloseCallback& cb)
            { closeCallback_ = cb; }

            // called when TcpServer accepts a new connection
            void connectEstablished();   // should be called only once
            // called when TcpServer has removed me from its map
            void connectDestroyed();  // should be called only once

        private:
            enum StateE { kDisconnected, kConnecting, kConnected,kDisconnecting };
            void handleRead(Timestamp receiveTime);
            void handleWrite();
            void handleClose();
            void handleError();
            // void sendInLoop(string&& message);
            void sendInLoop(const StringPiece& message);
            void sendInLoop(const void* message, size_t len);
            void shutdownInLoop();
            // void shutdownAndForceCloseInLoop(double seconds);
            void forceCloseInLoop();
            void setState(StateE s) { state_ = s; }
            const char* stateToString() const;
            void startReadInLoop();
            void stopReadInLoop();


            EventLoop* loop_;
            const string name_;
            StateE state_;
            bool reading_;
            boost::scoped_ptr<Socket> socket_;
            boost::scoped_ptr<Channel> channel_;
            const InetAddress localAddr_;
            const InetAddress peerAddr_;
            ConnectionCallback connectionCallback_;
            MessageCallback messageCallback_;
            WriteCompleteCallback writeCompleteCallback_;
            HighWaterMarkCallback highWaterMarkCallback_;
            CloseCallback closeCallback_;
            size_t highWaterMark_ ;
            Buffer inputBuffer_;
            Buffer outputBuffer_;
            boost::any context_;
        };
        typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
    }
}

#endif //MUDUO_TCPCONNECTION_H
