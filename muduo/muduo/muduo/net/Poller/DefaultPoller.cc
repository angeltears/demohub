//
// Created by onter on 18-8-23.
//

#include "../Poller.hpp"
#include "EPollPoller.h"
#include "PollPoller.hpp"


using namespace jmuduo;
using namespace jmuduo::net;


Poller* Poller::newDefaultPoller(EventLoop *loop)
{
    if (::getenv("MUDUO_USE_POLL"))
    {
        return new PollPoller(loop);
    }
    else
    {
        return new EPollPoller(loop);
    }
}