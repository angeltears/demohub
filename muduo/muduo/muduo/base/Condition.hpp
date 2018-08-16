//
// Created by onter on 18-8-5.
//
#ifndef MUDUO_CONDITION_HPP
#define MUDUO_CONDITION_HPP

#include "Mutex.hpp"
#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <errno.h>

namespace jmuduo
{
    class Condition : boost::noncopyable
    {
    public:
        explicit Condition(MutexLock &mutex) : mutex_(mutex)
        {
            MCHECK(pthread_cond_init(&pcond_, NULL));
        }

        ~Condition()
        {
            MCHECK(pthread_cond_destroy(&pcond_));
        }

        void wait()
        {
            MutexLock::UnassignGuard ug(mutex_);
            MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
        }

        void notify()
        {
            MCHECK(pthread_cond_signal(&pcond_));
        }

        void notifyAll()
        {
            MCHECK(pthread_cond_broadcast(&pcond_));
        }

        bool waitForSeconds(double seconds)
        {
            struct timespec abstime;
            clock_gettime(CLOCK_REALTIME, &abstime);

            const int64_t  kNanoSecondsPerSecond = 1000000000;
            int64_t nanoseconds = static_cast<int64_t >(seconds * kNanoSecondsPerSecond);

            abstime.tv_sec += static_cast<time_t>((abstime.tv_nsec + nanoseconds) / kNanoSecondsPerSecond);
            abstime.tv_nsec = static_cast<long>((abstime.tv_nsec + nanoseconds) % kNanoSecondsPerSecond);

            MutexLock::UnassignGuard ug(mutex_);
            return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime);
        }
    private:
        MutexLock& mutex_;
        pthread_cond_t pcond_;
    };
}

#endif //MUDUO_CONDITION_HPP
