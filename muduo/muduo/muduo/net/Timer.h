//
// Created by onter on 18-8-24.
//

#ifndef MUDUO_TIMER_H
#define MUDUO_TIMER_H


#include <boost/noncopyable.hpp>

#include "../base/Atomic.h"
#include "../base/Timestamp.h"
#include "Callbacks.h"

namespace jmuduo
{
    namespace net
    {
        class Timer: boost::noncopyable
        {
        public:
            Timer(const TimerCallback& cb, Timestamp when, double interval)
                    : callback_(cb),
                      expiration_(when),
                      interval_(interval),
                      repeat_(interval > 0.0),
                      sequence_(s_numCreated_.incrementAndGet())
            { }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
            Timer(TimerCallback&& cb, Timestamp when, double interval)
                    : callback_(std::move(cb)),
                      expiration_(when),
                      interval_(interval),
                      repeat_(interval > 0.0),
                      sequence_(s_numCreated_.incrementAndGet())
            { }
#endif
            void run() const
            {
                callback_();
            }

            Timestamp expiration() const
            { return expiration_; }
            bool repeat() const
            { return repeat_; }
            int64_t sequence() const
            { return sequence_; }
            void restart(Timestamp now);

            static  int64_t numCreated()
            { return s_numCreated_.get(); }
        private:
            const TimerCallback callback_;
            Timestamp expiration_;
            const double interval_;      /// for idenfiy once or Multiple timer
            const bool repeat_;
            const int64_t sequence_;

            static AtomicInt64 s_numCreated_;
        };
    }
}
#endif //MUDUO_TIMER_H
