//
// Created by onter on 18-8-23.
//

#include "PollPoller.hpp"
#include "../../base/Loggin.h"
#include "../../base/Types.h"
#include "../Channel.h"


#include <assert.h>
#include <errno.h>
#include <poll.h>

using namespace jmuduo;
using namespace jmuduo::net;


PollPoller::PollPoller(EventLoop *loop)
:Poller(loop)
{

}

PollPoller::~PollPoller()
{
}


Timestamp PollPoller::poll(int timeoutMs, ChannelList* activeChannels)
{
    int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);
    int savedErrno = errno;                       /// this use for reenterability
    Timestamp now(Timestamp:: now());

    if (numEvents > 0)
    {
        LOG_TRACE << numEvents << " events happened";
        fillActiveChannels(numEvents, activeChannels);
    }
    else if (numEvents == 0)
    {
        LOG_TRACE << " nothing happened";
    }
    else
    {
        if (savedErrno != EINTR)
        {
            errno = savedErrno;
            LOG_SYSERR << "PollPoller::poll()";
        }
    }
    return now;

}

void PollPoller::updateChannel(Channel *channel)
{
    Poller::assertInLoopThread();
    LOG_TRACE << "fd = " << channel->fd() << " events = " << channel->events();
    if (channel->index() < 0)
    {
        assert(channels_.find(channel->fd()) == channels_.end());
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        pollfds_.push_back(pfd);
        int idx = static_cast<int>(pollfds_.size()) - 1;
        channel->set_index(idx);
        channels_[pfd.fd] = channel;
    }
    else
    {
        assert(channels_.find(channel->fd()) == channels_.end());
        assert(channels_[channel->fd()] == channel);
        int idx = channel->index();
        assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
        struct pollfd& pfd = pollfds_[idx];
        assert(pfd.fd == channel->fd() || pfd.fd == -channel->fd()-1);
        pfd.fd = channel->fd();
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        if (channel->isNoneEvent())
        {
            // ignore this pollfd
            pfd.fd = -channel->fd()-1;
        }
    }
}

void PollPoller::removeChannel(Channel *channel)
{
    Poller::assertInLoopThread();
    LOG_TRACE << "fd = " << channel->fd() << " events = " << channel->events();
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] == channel);
    assert(channel->isNoneEvent());
    int idx = channel->index();
    assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
    const struct pollfd& pfd = pollfds_[idx]; (void) pfd;
    assert(pfd.fd == -channel->fd()-1 && pfd.events == channel->events());
    size_t n = channels_.erase(channel->fd());
    assert(n == 1); (void)n;
    if (implicit_cast<size_t>(idx) == pollfds_.size()-1)
    {
        pollfds_.pop_back();
    }
    else               /// is not the end , can swap to the end and pop!
    {
        int channelAtEnd = pollfds_.back().fd;
        iter_swap(pollfds_.begin()+idx, pollfds_.end()-1);
        if (channelAtEnd < 0)
        {
            channelAtEnd = -channelAtEnd-1;       /// some noe evnet fd = -fd -1  we must recover it;
        }
        channels_[channelAtEnd]->set_index(idx);
        pollfds_.pop_back();
    }
}

void PollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const
{
    for(PollFdList::const_iterator it = pollfds_.begin();
            it != pollfds_.end() && numEvents > 0; ++it)
    {
        if (it->revents > 0)      /// only work for revents not identify
        {
            --numEvents;
            ChannelMap::const_iterator ch = channels_.find(it->fd);
            assert(ch != channels_.end());
            Channel* channel = ch->second;
            assert(channel->fd() == it->fd);
            channel->set_revents(it->revents);
            activeChannels->push_back(channel);
        }

    }
}