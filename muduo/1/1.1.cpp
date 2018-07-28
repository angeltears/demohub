#include <boost/noncopyable.hpp>
#include <muduo/base/Mutex.h>
using namespace muduo;
class Counter: boost::noncopyable
{
public:
    Counter() = default;
    int64_t value() const;
    int64_t getAndIncrease();
private:
    int64_t value_ = 0;
    mutable MutexLock mutex_;
};
int64_t Counter::value() const
{
    MutexLockGuard lock(mutex_);
    return value_;
}
int64_t Counter::getAndIncrease()
{
    MutexLockGuard lock(mutex_);
    int64_t ret = value_++;
    return ret;
}