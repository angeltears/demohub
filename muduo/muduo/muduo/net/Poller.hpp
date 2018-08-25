//
// Created by onter on 18-8-21.
//

#ifndef MUDUO_POLLER_HPP
#define MUDUO_POLLER_HPP


#include <map>
#include <vector>
#include <boost/noncopyable.hpp>

#include "../base/Timestamp.h"
#include "EventLoop.h"

namespace jmuduo
{
    namespace net
    {
        class Channel;

        /***
         * base class for IO multiplexing
         * this class doesn't own the Channel objects;
         */
        class Poller: boost::noncopyable
        {
        public:
            typedef std::vector<Channel*> ChannelList;

            Poller(EventLoop* loop);
            virtual ~Poller();

            /// Polls the I/O events
            virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

            /// Change the interested I/O events
            virtual void updateChannel(Channel* channel) = 0;

            ///Remove the Channel, when it destructs
            virtual  void removeChannel(Channel* channel) = 0;


            virtual bool hasChannel(Channel* channel) const;

            static  Poller * newDefaultPoller(EventLoop* loop);

            void assertInLoopThread() const
            {
                ownerLoop_->assertInLoopThread();
            }

        protected:
            typedef std::map<int, Channel*> ChannelMap;
            ///  key = fd  value = Channel
            ChannelMap channels_;
        private:
            EventLoop* ownerLoop_;
        };
    }
}


#endif //MUDUO_POLLER_HPP
