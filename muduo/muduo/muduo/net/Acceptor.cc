//
// Created by onter on 18-8-30.
//

#include "Acceptor.h"
#include "../base/Loggin.h"
#include "InetAddress.h"
#include "SocketsOpt.h"
#include "EventLoop.h"

#include <boost/bind.hpp>
#include <fcntl.h>
#include <unistd.h>


using namespace jmuduo;
using namespace jmuduo::net;

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport)
                  :loop_(loop),
                   acceptSocket_(sockets::createNonblockingOrDie(listenAddr.family())),
                   acceptChannel_(loop, acceptSocket_.fd()),
                   listenning_(false),
                   idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
    assert(idleFd_ >= 0);
    acceptSocket_.setReuseAddr(true),
    acceptSocket_.setReusePort(reuseport),
    acceptSocket_.bindAddress(listenAddr),
    acceptChannel_.setReadCallback(
            boost::bind(&Acceptor::handleRead, this));

}

Acceptor::~Acceptor()
{
    acceptChannel_.disableAll();
    acceptChannel_.remove();
    ::close(idleFd_);
}

void Acceptor::listen()
{
    loop_->assertInLoopThread();
    listenning_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableReading();
}

void Acceptor::handleRead()
{
    loop_->assertInLoopThread();
    InetAddress peerAddr;

    int connfd = acceptSocket_.accept(&peerAddr);
    if (connfd >= 0)
    {
        if (newConnectionCallback_)
        {
            newConnectionCallback_(connfd, peerAddr);
        }
        else
        {
            sockets::close(connfd);
        }
    }
    else
    {
        LOG_SYSERR << "in Acceptor::handleRead";
        // Read the section named "The special problem of
        // accept()ing when you can't" in libev's doc.
        // By Marc Lehmann, author of libev.
        if (errno == EMFILE)
        {
            ::close(idleFd_);
            idleFd_ = ::accept(acceptSocket_.fd(), NULL, NULL);
            ::close(idleFd_);
            idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
        }
    }
}