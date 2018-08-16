//
// Created by onter on 18-8-5.
//

#ifndef MUDUO_COUNTDOWNLATCH_HPP
#define MUDUO_COUNTDOWNLATCH_HPP

#include "Condition.hpp"
#include "Mutex.hpp"

#include <boost/noncopyable.hpp>

namespace jmuduo
{
    class CountDownLatch : boost::noncopyable
    {
    public:
        CountDownLatch(int count)
                :mutex_(),condition_(mutex_), count_(count)
        {
        }

        void wait()
        {
            MutexLockGuard lock(mutex_);
            while( count_ > 0)
            {
                condition_.wait();
            }
        }


        void countDown()
        {
            MutexLockGuard lock(mutex_);
            --count_;
            if (count_ == 0)
            {
                condition_.notifyAll();
            }
        }

        int getCount() const
        {
            MutexLockGuard lock(mutex_);
            return count_;
        }

    private:
        mutable MutexLock mutex_;
        Condition condition_;
        int count_;
    };
}

#endif //MUDUO_COUNTDOWNLATCH_HPP
