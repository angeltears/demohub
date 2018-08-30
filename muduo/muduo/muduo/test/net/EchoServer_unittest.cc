//
// Created by onter on 18-8-30.
//

#include "../../net/TcpServer.h"

#include "../../base/Loggin.h"
#include "../../base/Thread.h"
#include "../../net/EventLoop.h"
#include "../../net/InetAddress.h"

#include <boost/bind.hpp>

#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace jmuduo;
using namespace jmuduo::net;

int numThreads = 0;

class EchoServer
{
public:
    EchoServer(EventLoop* loop, const InetAddress& listenAddr)
            : loop_(loop),
              server_(loop, listenAddr, "EchoServer")
    {
        server_.setConnectionCallback(
                boost::bind(&EchoServer::onConnection, this, _1));
        server_.setMessageCallback(
                boost::bind(&EchoServer::onMessage, this, _1, _2, _3));
        server_.setThreadNum(numThreads);
    }

    void start()
    {
        server_.start();
    }
    // void stop();

private:
    void onConnection(const TcpConnectionPtr& conn)
    {
        LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
                  << conn->localAddress().toIpPort() << " is "
                  << (conn->connected() ? "UP" : "DOWN");
        LOG_INFO << conn->getTcpInfoString();

        conn->send("hello\n");
    }

    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
    {
        string msg(buf->retrieveAllAsString());
        LOG_TRACE << conn->name() << " recv " << msg.size() << " bytes at " << time.toString();
        if (msg == "exit\n")
        {
            conn->send("bye\n");
            conn->shutdown();
        }
        if (msg == "quit\n")
        {
            loop_->quit();
        }
        conn->send(msg);
    }

    EventLoop* loop_;
    TcpServer server_;
};

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
    LOG_INFO << "sizeof TcpConnection = " << sizeof(TcpConnection);
    if (argc > 1)
    {
        numThreads = atoi(argv[1]);
    }
    bool ipv6 = argc > 2;
    EventLoop loop;
    InetAddress listenAddr(2000, false, ipv6);
    EchoServer server(&loop, listenAddr);

    server.start();

    loop.loop();
}

