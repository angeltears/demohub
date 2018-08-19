//
// Created by onter on 18-8-16.
//

#ifndef MUDUO_THREADPOOL_H
#define MUDUO_THREADPOOL_H

#include "Condition.hpp"
#include "Mutex.hpp"
#include "Thread.h"
#include "Types.h"


#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <deque>

namespace jmuduo
{
    class ThreadPool : boost::noncopyable
    {
    public:
        typedef boost::function<void ()> Task;

        explicit ThreadPool(const string& nameArg = string("ThreadPool"));
        ~ThreadPool();

        // Must be called before start().
        void setMaxQueueSize(int maxSize)
        { maxQueueSize_ = maxSize; }
        void setThreadInitCallback(const Task& cb)
        { threadInitCallback_ = cb; }

        void start(int numThreads);
        void stop();

        const string& name() const
        { return name_; }

        size_t queueSize() const;

        // Could block if maxQueueSize > 0
        void run(const Task& f);
#ifdef __GXX_EXPERIMENTAL_CXX0X__
        void run(Task&& f);
#endif
    private:
        bool isFull() const;
        void runInThread();
        Task take();

        mutable MutexLock                   mutex_;
        Condition                           notEmpty_;
        Condition                           notFull_;
        string                              name_;
        Task                                threadInitCallback_;
        boost::ptr_vector<jmuduo::Thread>   threads_;
        std::deque<Task>                    queue_;
        size_t                              maxQueueSize_;
        bool                                running_;
    };
};

#endif //MUDUO_THREADPOOL_H
