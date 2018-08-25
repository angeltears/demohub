//
// Created by onter on 18-8-24.
//

#ifndef MUDUO_TIMERID_H
#define MUDUO_TIMERID_H


#include "../base/copyable.h"

namespace jmuduo
{
    namespace net
    {
        class Timer;


        /// an opaque identifier for canceling Timer
        class TimerId: public jmuduo::copyable
        {
        public:
            TimerId()
                    :timer_(NULL),
                    sequence_(0)
            {
            }

            TimerId(Timer* timer, int64_t seq)
                    : timer_(timer),
                      sequence_(seq)
            {
            }

            friend class TimerQueue;
        private:
            Timer* timer_;
            int64_t sequence_;
        };
    }
}
#endif //MUDUO_TIMERID_H
