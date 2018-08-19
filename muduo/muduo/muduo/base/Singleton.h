//
// Created by onter on 18-8-16.
//

#ifndef MUDUO_SINGLETON_H
#define MUDUO_SINGLETON_H



#endif //MUDUO_SINGLETON_H
#include <boost/noncopyable.hpp>
#include <assert.h>
#include <stdlib.h> // atexit
#include <pthread.h>

namespace jmuduo
{

    namespace detail
    {

        template<typename T>
        struct has_no_destroy
        {
#ifdef __GXX_EXPERIMENTAL_CXX0X__
            template <typename C> static char test(decltype(&C::no_destroy));
#else
            template <typename C> static char test(typeof(&C::no_destroy));
#endif
            template <typename C> static int32_t test(...);
            const static bool value = sizeof(test<T>(0)) == 1;
        }; 
    }

    template<typename T>
    class Singleton : boost::noncopyable
    {
    public:
        static T& instance()
        {
            pthread_once(&ponce_, &Singleton::init);           //只会初始化一次
            assert(value_ != NULL);
            return *value_;
        }

    private:
        Singleton();
        ~Singleton();

        static void init()
        {
            value_ = new T();
            if (!detail::has_no_destroy<T>::value)
            {
                ::atexit(destroy);                //注册一个销毁函数， 在程序结束的时候,对其进行销毁
            }
        }

        static void destroy()
        {
            typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];    //T如果没有实现  sizeof T == 0，在编译器就会报错
            T_must_be_complete_type dummy;
            (void) dummy;

            delete value_;
            value_ = NULL;
        }

    private:
        static pthread_once_t ponce_;
        static T*             value_;
    };

    template<typename T>
    pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;