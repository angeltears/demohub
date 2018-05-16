#include <iostream>
using namespace std;

struct A
{
    A(int i):d(i){}
    A(double f, int i, char *c){}
   A(double c = 2.4, int i = 3):d(i), c(c){}
    int d {0};
    double c{0};
};

struct B:A
{
    using A::A;
    
};
//可以通过显时的定义来解决冲突
//
int main()
{
    B b(213.2);
    B c;   //在没有默认值的构造函数时此语句不通过　在继承构造函数时，将会不提供默认构造函数
    cout << b.c<<endl;
    cout << b.d<<endl;
}



/*
struct Base
{
    void f(double i)
    {
        cout <<"Base:"<< i<<endl;
    }
};

struct Derived:Base
{
    using Base::f;
    void f(int i)
    {
        cout<<"Derived :"<<i<<endl;
    }
};

int main()
{
    Derived b;
    b.f(4.5);
    b.f(4);
}*/