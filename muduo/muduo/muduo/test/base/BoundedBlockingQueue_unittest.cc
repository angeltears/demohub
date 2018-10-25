/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-10-25.
* @package : muduo
*/
#include "../../base/BoundedBlockingQueue.hpp"
#include "../../base/Thread.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
using namespace jmuduo;

using namespace boost;

void Produce(shared_ptr<BoundedBlockingQueue<int> > queue)
{
    while(true)
    {
        int product=rand()%1000+1;
        std::cout<<"Produce: "<<product<<std::endl;
        queue->put(product);
        sleep(rand()%5);
    }

}
void Consome(shared_ptr<BoundedBlockingQueue<int> > queue)
{
    while(true)
    {
        int product=queue->take();
        std::cout<<"Consome: "<<product<<std::endl;
        sleep(rand()%5);
    }
}
int main()
{
    shared_ptr<BoundedBlockingQueue<int> > boundedBlockingQueue(new BoundedBlockingQueue<int>(2));
    Thread t1(boost::bind(Produce, boundedBlockingQueue));
    Thread t2(boost::bind(Consome, boundedBlockingQueue));

    t1.start();
    t2.start();

    t1.join();
    t2.join();

    return 0;
}
