#include <iostream>
using namespace std;

template<typename ... T>
void DummyWrapper(T ... t){}

template<typename T>
T pr(T t)
{
     cout << t;
     return t;
}

template <typename ... A>
void VTPrint(A... a)
{
    DummyWrapper(pr(a)...);    //依次解包为pr(1), pr(".")....
}

int main()
{
    VTPrint(1, ",", 1.2, ", abc\n");
}

//注意不可以同时声明两个可变参数