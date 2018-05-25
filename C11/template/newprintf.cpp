#include <iostream>
#include <stdexcept>
#include <cstdio>
using namespace std;

void Printf(const char *s)
{
    while (*s)
    {
        if (*s == '%' && *++s != '%')
        {
            throw runtime_error("invalid format string: missing arguments");
        }
        cout << *s++;
    }
}


template<typename T, typename ...Arg>
void Printf(const char *s, T value, Arg ... args)
{
    while(*s)
    {
        if (*s == '%' && *++s != '%')
        {
            cout << value;
            return Printf(++s, args...);
        }
        cout << *s++;
    }
    throw runtime_error("invalid format string: missing arguments");
}

int main()
{
    Printf("hello %s\n", string("world"));
}