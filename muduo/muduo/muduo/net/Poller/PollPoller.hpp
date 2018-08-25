//
// Created by onter on 18-8-23.
//

#ifndef MUDUO_POLLPOLLER_HPP
#define MUDUO_POLLPOLLER_HPP


#include "../Poller.hpp"
#include <vector>

struct pollfd;

namespace jmuduo
{
    namespace net
    {
        class PollPoller: public Poller
        {
        public:
            PollPoller(EventLoop *loop);

            virtual ~PollPoller();
            virtual Timestamp poll(int timeoutMS, ChannelList* activeChannels);
            virtual void updateChannel(Channel* channel);
            virtual void removeChannel(Channel* channel);
        private:
            void fillActiveChannels(int numEventsm, ChannelList * activeChannels) const;

            typedef std::vector<struct pollfd> PollFdList;
            PollFdList pollfds_;
        };
    }
}


#endif //MUDUO_POLLPOLLER_HPP
