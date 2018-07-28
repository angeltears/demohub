// observer
#include <memory>
#include <muduo/base/Mutex.h>
#include <vector>
using std::weak_ptr;
using std::shared_ptr;
using muduo::MutexLock;
using muduo::MutexLockGuard;
class Observer{};

class Observable
{
public:
    void register_(weak_ptr<Observer> s){}
    void notifyObservers();
private:
    mutable MutexLock mutex_;
    std::vector< weak_ptr<Observer> > Observers_;
    typedef std::vector< weak_ptr<Observer> >::iterator iterator;
};

void Observable::notifyObservers()
{
    MutexLockGuard lock(mutex_);
    iterator it = Observers_.begin();
    while (it != Observers_.end())
    {
        shared_ptr<Observer> obj(it->lock());
        if(obj)
        {
            obj->update();
            ++it;
        }
        else
        {
            it = observers_.erase(it);
        }
    }
}
