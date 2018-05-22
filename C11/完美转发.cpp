#include <iostream>
using namespace std;

void Runcode(int && m)
{
    cout << "rvalue ref" << endl;
}
void Runcode(int & m)
{
    cout << "lvalue ref" << endl;
}
void Runcode(const int && m)
{
    cout << "const rvalue ref" << endl;
}
void Runcode(const int & m)
{
    cout << "const rvalue ref" << endl;
}

//折叠规律 定义中一旦出现了左值引用，引用折叠总是优先将其折叠为左值引用
/*
以下等价于
void PerfectForward(T && t)
{
    Runcode(static_casst<T&&>(t));
}
当传入一个左值引用时
void PerfectForward(T& && t)
{
    Runcode(static_casst<T& &&>(t));
}
折叠后
void PerfectForward(T& t)
{
    Runcode(static_casst<T& >(t));
}
同理 传入右值引用
void PerfectForward(T&& t)
{
    Runcode(static_casst<T&& >(t));
}
所以可以做到完美转发
*/
template<typename T>
void PerfectForward(T && t)
{
    Runcode(forward<T>(t));
}

int main()
{
    int a;
    int b;
    const int c = 1;
    const int d = 0;

    PerfectForward(a);
    PerfectForward(move(b));
    PerfectForward(c);
    PerfectForward(move(c));
}                                                                        