#include <muduo/base/Mutex.h>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <map>
#include <string>
using muduo::MutexLock;
using muduo::MutexLockGuard;
using std::shared_ptr;
using std::weak_ptr;
using std::string;
class Stock{};
class StockFactory: boost::noncopyable
{
public:
    shared_ptr<Stock> get(const string &key);
private:
    mutable MutexLock mutex_;
    std::map<string, weak_ptr<Stock> > stocks_;
    void deleteStock(Stock *Stock)
    {
        if (Stock)
        {
            MutexLockGuard lock(mutex_);
            stocks_.erase(stock->key());
        }
        delete Stock;
    }
};


shared_ptr<Stock> StockFactory::get(const string &key)
{
    shared_ptr<Stock> pStock;
    MutexLockGuard lock(mutex_);
    weak_ptr<Stock>& wkStock = stocks_[key];
    pStock = wkStock.lock();
    if (!pStock)
    {
        pStock.reset(new Stock(key), boost::bind(&StockFactory::deleteStock, this, _1));
        wkStock = pStock;
    }
    return pStock;
}