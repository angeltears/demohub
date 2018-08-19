//
// Created by onter on 18-8-18.
//

#ifndef MUDUO_THREADLOCAL_H
#define MUDUO_THREADLOCAL_H


#include "Mutex.hpp"
#include <boost/noncopyable.hpp>
#include <pthread.h>

/**
 *当线程的私有数据为pod类型时候，可以通过__pthread来声明其为一个线程的私有数据
 * 如果不是，即TSD类型的时候，就需要用pthread_key_t的变量来关联相关的数据。
 *创建一个类型为 pthread_key_t 类型的变量。
 *调用 pthread_key_create() 来创建该变量。从Linux的TSD池中分配一项，将其值赋给key供以后访问使用，它的第一个参数key为指向键值的指针，第二个参数为一个函数指针，如果指针不为空，则在线程退出时将以key所关联的数据为参数调用destructor（）释放分配的缓冲区。key一旦被创建，所有线程都可以访问它，但各线程可以根据自己的需要往key中填入不同的值，这就相当于提供了一个同名而不同值的全局变量，一键多值。
 *当线程中需要存储特殊值的时候，可以调用 pthread_setspcific()。该函数有两个参数，第一个为前面声明的 pthread_key_t 变量，第二个为 void* 变量，这样你可以存储任何类型的值。函数将value的值（不是内容）与key相关联。用pthread_setspecific为一个键指定新的线程数据时，线程必须先释放原有的线程数据用以回收空间。
 *如果需要取出所存储的值，调用 pthread_getspecific() 。该函数的参数为前面提到的 pthread_key_t 变量，该函数返回 void * 类型的值。
 *pthread_key_delete：该函数用来删除一个键，键所占用的内存将被释放。需要注意的是，键占用的内存被释放，与该键关联的线程数据所占用的内存并不被释放。因此，线程数据的释放必须在释放键之前完成。
 */

namespace jmuduo
{

    template <typename T>
    class ThreadLocal: boost::noncopyable
    {
    public:
        ThreadLocal()
        {
            MCHECK(pthread_key_create(&pkey_, &ThreadLocal::destructor));
        }
        ~ThreadLocal()
        {
            MCHECK(pthread_key_delete(pkey_));
        }
        T& value()
        {
            T *perThreadValue = static_cast<T *>(pthread_getspecific(pkey_));
            if (!perThreadValue)
            {
                T* newObj = new T();
                MCHECK(pthread_setspecific(pkey_, newObj));
                perThreadValue = newObj;
            }
            return *perThreadValue;
        }
    private:
        // 因为公用一个，所以就可以申明为静态的。
        static void destructor(void * x)
        {
            T * obj = static_cast<T*>(x);
            typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
            T_must_be_complete_type dummy;
            (void) dummy;
            delete obj;
        }

        pthread_key_t pkey_;
    };
}
#endif //MUDUO_THREADLOCAL_H
