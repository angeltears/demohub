//
// Created by onter on 18-8-18.
//

//
// Created by onter on 18-8-18.
//
#include "../../base/ThreadLocal.h"
#include "../../base/CurrentThread.h"
#include "../../base/Thread.h"
#include <boost/noncopyable.hpp>
#include <stdio.h>



/***
 * 用了两个线程 证明了obj1 obj2为线程独有的全局变量
 */
class Test : boost::noncopyable
{
public:
    Test()
    {
        printf("tid=%d, constructing %p\n", jmuduo::CurrentThread::tid(), this);
    }

    ~Test()
    {
        printf("tid=%d, destructing %p %s\n", jmuduo::CurrentThread::tid(), this, name_.c_str());
    }

    const jmuduo::string& name() const { return name_; }
    void setName(const jmuduo::string& n) { name_ = n; }

private:
    jmuduo::string name_;
};

jmuduo::ThreadLocal<Test> testObj1;
jmuduo::ThreadLocal<Test> testObj2;

void print()
{
    printf("tid=%d, obj1 %p name=%s\n",
           jmuduo::CurrentThread::tid(),
           &testObj1.value(),
           testObj1.value().name().c_str());
    printf("tid=%d, obj2 %p name=%s\n",
           jmuduo::CurrentThread::tid(),
           &testObj2.value(),
           testObj2.value().name().c_str());
}

void threadFunc()
{
    print();
    testObj1.value().setName("changed 1");
    testObj2.value().setName("changed 2");
    print();
}

int main()
{
    testObj1.value().setName("main one");
    print();
    jmuduo::Thread t1(threadFunc);
    t1.start();
    t1.join();
    testObj2.value().setName("main two");
    print();
}

