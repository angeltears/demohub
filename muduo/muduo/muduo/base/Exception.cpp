//
// Created by onter on 18-8-4.
//
#include <execinfo.h>
#include <stdlib.h>
#include "Exception.h"
using namespace jmuduo;

void Exception::fillStackTrace()
{
    const int len = 200;
    void *buf[100];
    int nptrs = ::backtrace(buf, len);
    char **string = ::backtrace_symbols(buf, nptrs);
    if (string != nullptr)
    {
        for (int i = 0; i < nptrs; i++)
        {
            stack_.append(string[i]);
            stack_.push_back('\n');
        }
        free(string);
    }
}


Exception::Exception(const char *what)
:message_(what)
{
    fillStackTrace();
}

Exception::Exception(const string &what)
:message_(what)
{
    fillStackTrace();
}

const char* Exception::what() const throw()
{
    return message_.c_str();
}

const char* Exception::stackTrace() const throw()
{
    return stack_.c_str();
}

Exception::~Exception() throw()
{

}