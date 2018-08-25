//
// Created by onter on 18-8-24.
//

#include "Timer.h"

using namespace jmuduo;
using namespace jmuduo::net;

AtomicInt64 Timer::s_numCreated_;

void Timer::restart(Timestamp now)
{
    if (repeat_)
    {
        expiration_ = addTime(now, interval_);
    }
    else
    {
        expiration_ = Timestamp::invalid();
    }
}
