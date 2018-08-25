//
// Created by onter on 18-8-21.
//

#ifndef MUDUO_EVENTLOOP_HPP
#define MUDUO_EVENTLOOP_HPP


#include <vector>

#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "../base/Mutex.hpp"
#include "../base/CurrentThread.h"
#include "../base/Timestamp.h"
#include "Callbacks.h"
#include "TimerId.h"

namespace jmuduo
{
    namespace net
    {

        class Channel;
        class Poller;
        class TimerQueue;

        /// Reactor, at  most one per thread
        class EventLoop : boost::noncopyable
        {
        public:
            typedef boost::function<void()> Functor;
            EventLoop();
            ~EventLoop();

            /// loops must be called in the same thread as creation of the objecets
            void loop();

            /// Quits loop.
            void quit();

            /// Time when poll returns, usually means data arrival.
            Timestamp pollReturnTime() const
            { return pollReturnTime_; }

            int64_t iteration() const
            { return iteration_; }


            /// Runs callback immediately in the loop thread.
            /// It wakes up the loop, and run the cb.
            /// If in the same loop thread, cb is run within the function.
            /// Safe to call from other threads.
            void runInLoop(const Functor& cb);

            /// Queues callback in the loop thread.
            /// Runs after finish pooling.
            /// Safe to call from other threads.
            void queueInLoop(const Functor& cb);

            size_t queueSize() const;

#ifdef __GXX_EXPERIMENTAL_CXX0X__
            /// use c11 to reduce copy construction cost
            void runInLoop(Functor&& cb);
            void queueInLoop(Functor&& cb);
#endif
            /// runs callback at time
            /// safe to call form other thread.
            TimerId runAt(const Timestamp& time, const TimerCallback& cb);

            /// Runs callback after @c delay seconds.
            /// Safe to call from other threads.
            TimerId runAfter(double delay, const TimerCallback& cb);

            /// Runs callback every @c interval seconds.
            /// Safe to call from other threads.
            TimerId runEvery(double interval, const TimerCallback& cb);

            void cancel(TimerId timerId);

#ifdef __GXX_EXPERIMENTAL_CXX0X__
            TimerId runAt(const Timestamp& time, TimerCallback&& cb);
            TimerId runAfter(double delay, TimerCallback&& cb);
            TimerId runEvery(double interval, TimerCallback&& cb);
#endif
            /// awake IO event thread by  wakeupFd_
            void wakeup();
            void updateChannel(Channel* channel);
            void removeChannel(Channel* channel);
            bool hasChannel(Channel *channel);


            void assertInLoopThread()
            {
                if (!isInLoopThread())
                {
                    abortNotInLoopThread();
                }
            }
            bool isInLoopThread() const
            { return threadId_ == CurrentThread::tid(); }

            bool eventHandling() const
            { return eventHandling_; }

            const boost::any& getContext() const
            { return context_; }

            boost::any* getMutableContext()
            { return &context_; }

            static EventLoop* getEventLoopOfCurrentThread();
        private:
            void abortNotInLoopThread();
            void handleRead();            ///  waked up
            void doPendingFunctors();       ///  handing other thread IO events

            void printActiveChannels() const;      /// DEBUG

            typedef std::vector<Channel*> ChannelList;

            bool looping_;          /// atomic
            bool quit_;             /// atomic
            bool eventHandling_;    /// atomic  thread in  handleRead()
            bool callingPendingFunctors_;     /// thread in dePendingFunctors()
            int64_t iteration_;
            const pid_t threadId_;
            Timestamp pollReturnTime_;
            boost::scoped_ptr<Poller> poller_;
            boost::scoped_ptr<TimerQueue> timerQueue_;
            int wakeupFd_;          /// for process to process communication
            // unlike in TimerQueue, which is an internal class,
            // we don't expose Channel to client.
            boost::scoped_ptr<Channel> wakeupChannel_;
            boost::any context_;

            // scratch variables
            ChannelList activeChannels_;
            Channel* currentActiveChannel_;

            mutable  MutexLock mutex_;
            std::vector<Functor> pendingFunctors_;
        };
    }
}

#endif //MUDUO_EVENTLOOP_HPP
