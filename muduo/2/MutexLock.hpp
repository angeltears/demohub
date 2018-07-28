#include <boost/noncopyable.hpp>
#include <muduo/base/CurrentThread.h>
#include <assert.h>
#include <pthread.h>
class MutexLock: boost::noncopyable
{
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex_,NULL);
    }
    ~MutexLock()
    {
        assert(holder_ == 0);
        pthread_mutex_destroy(&mutex_);
    }
    void lock()
    {
        holder_ = muduo::CurrentThread::tid();
        pthread_mutex_lock(&mutex_);
    }
    bool isLockByThisThread()
    {
        return holder_ == muduo::CurrentThread::tid();
    }
    void assertLocked()
    {
        assert(isLockByThisThread());
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
        holder_ = 0;
    }
    pthread_mutex_t* getPhtreadMutex()
    {
        return &mutex_;
    }
private:
    pthread_mutex_t  mutex_;
    pid_t holder_ = 0;
};

class MutexLockGuard : boost::noncopyable
{
public:
    explicit MutexLockGuard(MutexLock& mutex):mutex_(mutex)
    {
        mutex.lock();
    }
    ~MutexLockGuard()
    {
        mutex_.unlock();
    }
private:
    MutexLock& mutex_;
};

#define MutexLockGuard(x)  static_assert(false, "Missing mutex gurad var name");

class Condition : boost::noncopyable
{
public:
    explicit Condition(MutexLock& mutex)
    :mutex_(mutex)
    {
        pthread_cond_init(&pcond_, NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&pcond_);
    }
    void wait() 
    {
        pthread_cond_wait(&pcond_, mutex_.getPhtreadMutex());
    }
    void notify()
    {
        pthread_cond_signal(&pcond_);
    }
    void notifyAll()
    {
        pthread_cond_broadcast(&pcond_);
    }
private:
    MutexLock& mutex_;
    pthread_cond_t pcond_;
};

class CountDownLatch
{
public:
    CountDownLatch(int count)
    : mutex_(),
      condition_(mutex_),
      count_(count)
      {}
    void wait()
    {
        MutexLockGuard lock(mutex_);
        while (count_> 0)
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

