//
// Created by onter on 18-8-21.
//

#include "Poller.hpp"
#include "Channel.h"


using namespace jmuduo;
using namespace jmuduo::net;


Poller::Poller(EventLoop *loop)
    :ownerLoop_(loop)
{
}

Poller::~Poller()
{
}

bool Poller::hasChannel(Channel *channel) const
{
    assertInLoopThread();
    ChannelMap::const_iterator it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}