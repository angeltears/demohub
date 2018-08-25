//
// Created by onter on 18-8-25.
//

#ifndef MUDUO_EVENTLOOPTHREAD_H
#define MUDUO_EVENTLOOPTHREAD_H

#include "../base/Condition.hpp"
#include "../base/Mutex.hpp"
#include "../base/Thread.h"

#include <boost/noncopyable.hpp>

namespace jmuduo
{
    namespace net
    {
        class EventLoop;

        class EventLoopThread: boost::noncopyable
        {
        public:
            typedef boost::function<void(EventLoop*)> ThreadInitCallback;

            EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                            const string& name = string());
            ~EventLoopThread();
            EventLoop* startLoop();
        private:
            void threadFunc();
            EventLoop* loop_;
            bool exiting_;
            Thread thread_;
            MutexLock mutex_;
            Condition cond_;
            ThreadInitCallback callback_;
        };
    }
}


#endif //MUDUO_EVENTLOOPTHREAD_H
