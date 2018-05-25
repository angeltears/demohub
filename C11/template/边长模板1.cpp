#include <iostream>
using namespace std;

template <long...nums> struct Multipiy;

template<long first, long...last>
struct Multipiy<first, last...>
{
    static const long val = first * Multipiy<last...>::val;
};


template<>
struct Multipiy<>
{
    static const long val = 1;
};


int main() 
{
    cout << Multipiy<2,3,4,5>::val <<endl;
    return 0;
}


//递归调用 不断解包 加上边界条件 ；