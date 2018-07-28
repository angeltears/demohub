#ifndef MUDUO_BASE_TIMESTAMP_H
#define MUDUO_BASE_TIMESTAMP_H 

#include "copyable.h"
#include "Types.h"
#include <boost/operators.hpp>

namespace  jmuduo
{
    class Timestamp: public jmuduo::copyable,                     /// 见copyable.h
                     public boost::equality_comparable<Timestamp>,   /// less_than_comparable<>和equality_comparable<>
                     public boost::less_than_comparable<Timestamp>   /// 要求实现< ==，可自动实现>, <=,>=
    {
    public:
        Timestamp(): microSecondsSinceEpoch_(0) {}      /// 计时是从1970.1.1　00:00:00开始的UTC
        explicit Timestamp(int64_t mircoSecondSinceEpochArg):microSecondsSinceEpoch_(mircoSecondSinceEpochArg)
        {}
        void swap(Timestamp& that)
        {
            std::swap(microSecondsSinceEpoch_,that.microSecondsSinceEpoch_);
        }
        string toString() const;
        string toFormattedString(bool showMircroseconds = true) const;

        int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
        time_t secondsSinceEpoch() const
        { return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond); }
        bool valid() const
        {
            return microSecondsSinceEpoch_>0;
        }
        static  Timestamp now();
        static  Timestamp invalid()
        {
            return Timestamp();
        }

        static const int kMicroSecondsPerSecond = 1000 * 1000;
    private:
        int64_t  microSecondsSinceEpoch_;
    };

    inline bool operator<(Timestamp lhs,Timestamp rhs)
    {
        return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
    }

    inline bool operator==(Timestamp lhs, Timestamp rhs)
    {
        return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
    }
/// Gets time difference of two timestamps, result in seconds.
/// @return (high-low) in seconds
/// @c double has 52-bit precision, enough for one-microsecond
/// resolution for next 100 years.
    inline double  timeDifference(Timestamp high, Timestamp low)
    {
        int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
        return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
    }

    inline Timestamp addTime(Timestamp timestamp, double seconds)
    {
        int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
        return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
    }
}







#endif