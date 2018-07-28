//
// Created by onter on 18-7-28.
//

#ifndef MUDUO_ATOMIC_H
#define MUDUO_ATOMIC_H


#include <boost/noncopyable.hpp>
#include <stdint.h>
#include <atomic>
namespace jmuduo
{
    namespace detail
    {
        template<typename T>
        class AtomicIntegerT :boost::noncopyable
        {
        public:
            AtomicIntegerT():value_(0) {}
            T get()
            {
                return __atomic_load_n(&value_, __ATOMIC_SEQ_CST);
            }

            T getAndAdd(T x)
            {
                return __atomic_fetch_add(&value_, x, __ATOMIC_SEQ_CST);
            }

            T addAndGet(T x)
            {
                return getAndAdd(x) + x;
            }
            //后＋＋
            T incrementAndGet()
            {
                return addAndGet(1);
            }
            //后－－
            T decrementAndGet()
            {
                return addAndGet(-1);
            }

            void add(T x)
            {
                getAndAdd(x);
            }
            //后＋＋
            void increment()
            {
                incrementAndGet();
            }
            //后－－
            void decrement()
            {
                decrementAndGet();
            }

            T getAndSet(T newvalue)
            {
                return __atomic_exchange_n(&value_, newvalue, __ATOMIC_SEQ_CST);
            }
        private:
            volatile T value_;
        };
    };
    typedef detail::AtomicIntegerT<int32_t> AtomicInt32;
    typedef detail::AtomicIntegerT<int64_t> AtomicInt64;
};

#endif //MUDUO_ATOMIC_H
