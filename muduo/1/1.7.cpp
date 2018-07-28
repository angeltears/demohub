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
class StockFactory: public std::enable_shared_from_this<StockFactory>,
                    boost::noncopyable
{
public:
    shared_ptr<Stock> get(const string &key)
    {
    shared_ptr<Stock> pStock;
    MutexLockGuard lock(mutex_);
    weak_ptr<Stock>& wkStock = stocks_[key];
    pStock = wkStock.lock();
    if (!pStock)
    {
        pStock.reset(new Stock(key), boost::bind(&StockFactory::deleteStock,weak_ptr<StockFactory>(shared_from_this()), _1));
        wkStock = pStock;
    }
    return pStock;
}
private:
    static void deleteStock(const weak_ptr<StockFactory>& wkFactory, Stock*stock)
    {
        shared_ptr<StockFactory> factroy(wkFactory.lock());
        
        if (factroy)
        {
            factroy->removeStock(stock);
        }
        delete stock;
    }
    void removeStock(Stock *stock)
    {
        if (stock)
        {
            MutexLockGuard lock(mutex_);
            stocks_.erase(stock->key());
        }
    }
private:
    mutable MutexLock mutex_;
    std::map<string, weak_ptr<Stock> > stocks_;
};
