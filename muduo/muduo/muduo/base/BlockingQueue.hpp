//
// Created by onter on 18-8-16.
//
#ifndef MUDUO_BLOCKINGQUEUE_HPP
#define MUDUO_BLOCKINGQUEUE_HPP

#include "Condition.hpp"
#include "Mutex.hpp"

#include <boost/noncopyable.hpp>
#include <deque>
#include <assert.h>
#include <thread_db.h>


namespace jmuduo
{
    template <typename T>
    class BlockingQueue : boost::noncopyable
    {
    public:
        BlockingQueue():mutex_(), notEmpty_(mutex_), queue_()
        {}

        void put(const T& x)    // 生产T， 生产者
        {
            MutexLockGuard lock(mutex_);
            queue_.push_back(x);
            notEmpty_.notify();          //唤醒正在等待的消费者
        }

#ifdef __GXX_EXPERIMENTAL_CXX0X__
        void put(T&& x)
        {
            MutexLockGuard lock(mutex_);
            queue_.push_back(std::move(x));
            notEmpty_.notify();
        }
#endif
        T take()           //获取T, 消费者
        {
            MutexLockGuard lock(mutex_);
            while(queue_.empty())
            {
                notEmpty_.wait();
            }
            assert(!queue_.empty());
#ifdef __GXX_EXPERIMENTAL_CXX0X__             // 相比拷贝构造，转化成右值移动更节省空间
            T front(std::move(queue_.front()));
#else
            T fornt(queue_.front());
#endif
            queue_.pop_front();
            return front;
        }
    private:
        mutable MutexLock   mutex_;
        Condition           notEmpty_;
        std::deque<T>       queue_;
    };
}

#endif //MUDUO_BLOCKINGQUEUE_HPP
