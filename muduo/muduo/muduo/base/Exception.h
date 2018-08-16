//
// Created by onter on 18-8-4.
//

#ifndef MUDUO_EXCEPTION_H
#define MUDUO_EXCEPTION_H

#include "Types.h"
#include <exception>
#include <string>
using std::string;
namespace jmuduo
{
    class Exception: public std::exception
    {
    public:
        explicit Exception(const char* what);
        explicit Exception(const string& what);
        virtual ~Exception() throw();
        virtual const char* what() const throw();
        const char* stackTrace() const throw();

    private:
        void fillStackTrace();

        string message_;
        string stack_;

    };
};

#endif //MUDUO_EXCEPTION_H
