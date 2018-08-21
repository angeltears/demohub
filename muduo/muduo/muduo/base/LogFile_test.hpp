//
// Created by onter on 18-8-20.
//

#ifndef MUDUO_LOGFILE_HPP
#define MUDUO_LOGFILE_HPP

#include "Mutex.hpp"
#include "Types.h"

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>


namespace jmuduo
{
    namespace FileUtil
    {
        class AppendFile;
    }


    /***
     * 有两个机制　滚动日志
     * 　一个是文件的大小
     * 　一个是时间　时间一般为一天　　即从每天的零点更新一个日志
     */
    class LogFile: boost::noncopyable
    {
    public:
        LogFile(const string& basename,
                off_t rollSize,
                bool threadSafe = true,
                int flushInterval = 3,
                int checkEveryN = 1024);
        ~LogFile();

        void append(const char *logline, int len);
        void flush();
        bool rollFile();
    private:
        void append_unlocked(const char * logline, int len);
        static string getLogFileName(const string& basename, time_t* now);

        const string basename_;    /// 文件名
        const off_t rollSize_;      /// 滚动大小
        const int flushInterval_;   /// 写入周期
        const int checkEveryN_;     /// 检测时间的写入次数

        int count_;                 /// 写入次数

        boost::scoped_ptr<MutexLock> mutex_;
        time_t startOfPeriod_;
        time_t lastRoll_;
        time_t lastFlush_;
        boost::scoped_ptr<FileUtil::AppendFile> file_;

        const static int kRollPerSecond_ = 60*60*24;
    };
}

#endif //MUDUO_LOGFILE_HPP
