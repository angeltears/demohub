/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-12-19.
* @package : thread
*/

#include <cstdio>
#include <thread>
#include <iostream>

void f(int i, std::string buf)
{
   std::cout << buf<< std::endl;
}

void  oops(int n)
{
    char buffer[1024];
    sprintf(buffer, "%d test", n);
    std::thread t(f, 3, buffer);
    t.detach();
}

int main()
{
    oops(5);
}