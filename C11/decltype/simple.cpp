#include <type_traits>
#include <iostream>
using namespace std;

int(*( *pf() ) () )();

auto pf1() -> auto (*)() -> int (*)()
{
    return nullptr;
}

int main()
{
    cout << is_same<decltype(pf), decltype(pf1)>::value << endl; 
}r