#include <boost/noncopyable.hpp>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <muduo/base/Mutex.h>
class CustomerData : boost::noncopyable
{
public:
    CustomerData() :data_(new Map) {}
    int query(const std::string& customer, const std::string& stock) const;
private: 
    typedef std::pair<std::string, int> Enter;
    typedef std::vector<Enter> EntryList;
    typedef std::map<std::string,EntryList> Map;
    typedef std::shared_ptr<Map>  MapPtr;
    void update(const std::string& customer, const EntryList& entries);
    void update(const std::string& message);
    static int findEntry(const EntryList& entries, const std::string & stock);
    static MapPtr parseData(const std::string& message);
    MapPtr getData() const
    {
        muduo::MutexLockGuard lock(mutex_);
        return data_;
    }
    mutable muduo::MutexLock mutex_;
    MapPtr data_;
};

int CustomerData::query(const std::string& customer, const std::string& stock) const
{
    MapPtr data = getData();
    auto entries = data->find(customer);
    if (entries != data->end())
        return findEntry(entries->second, stock);
    else
        return -1;
}

void CustomerData::update(const std::string& customer, const EntryList& entries)
{
    muduo::MutexLockGuard Lock(mutex_);
    if (!data_.unique())
    {
        MapPtr newData(new Map(*data_));
        data_.swap(newData);
    }
    assert(data_.unique());
    (*data_)[customer] = entries;
}

void CustomerData::update(const std::string& message)
{
  MapPtr newData = parseData(message);
  if (newData)
  {
    muduo::MutexLockGuard lock(mutex_);
    data_.swap(newData);
  }
}