/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-10-25.
* @package : muduo
*/
#include "../../base/BlockingQueue.hpp"
#include "../../base/Thread.h"

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "../../base/Loggin.h"
using namespace boost;
using namespace jmuduo;


void Produce(shared_ptr<BlockingQueue<int>> queue)
{
    while (1)
    {
        int product = rand() % 1000+ 1;
        LOG_INFO << "Produce: " << product ;
        queue->put(product);
        sleep(1);
    }
}

void Consome(shared_ptr<BlockingQueue<int>> queue)
{
    while(1)
    {
        int product = queue->take();
        LOG_INFO <<"id : " <<CurrentThread::tid();
        LOG_INFO<< "Consome : " << product;
    }
}

int main()
{
    shared_ptr<BlockingQueue<int>> blockingqueue(new BlockingQueue<int>);
    Thread t1(bind(Produce, blockingqueue));
    Thread t2(bind(Consome, blockingqueue));
    Thread t3(bind(Consome, blockingqueue));
    t1.start();
    t2.start();
    t3.start();
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
