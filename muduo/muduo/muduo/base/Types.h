#ifndef MUDUO_BASE_TYPES_H
#define MUDUO_BASE_TYPES_H

#include <stdint.h>
#ifdef MUDUO_STD_STRING
#include <string>
#else
#include <ext/vstring.h>
#include <ext/vstring_fwd.h>
#endif

#ifndef NDEBUG
#include <assert.h>
#endif

namespace jmuduo
{

#ifdef MUDUO_STD_STRING
using std::string;
#else
typedef __gnu_cxx::__sso_string string;
#endif


// 这个在c++11中已经实现了，而且提供的更加全面，但是为了程序的快捷，这样做也未尝不可
template<typename To, typename From>
inline To implicit_case(From const &f)
{
    return f;
}

//　不适用dynamic_cast 可以节省时间和bug
template <typename To, typename From>
inline To down_cast(From *f)
{
    if (false)
    {
        implicit_case<From*, To>(0);
    }
#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
    assert(f == NULL || dynamic_cast<To>(f) != NULL );
#endif
    return static_cast<To>(f);
}

    
};




#endif