//
// Created by onter on 18-8-19.
//

#ifndef MUDUO_FILEUTIL_H
#define MUDUO_FILEUTIL_H


#include "StringPiece.h"
#include <boost/noncopyable.hpp>
#include <sys/types.h>

namespace jmuduo
{
    namespace FileUtil
    {

        /// read small file < 64kb
        class ReadSmallFile: boost::noncopyable
        {
        public:
            ReadSmallFile(StringArg filename);
            ~ReadSmallFile();

            template <typename String>
            int readToString(int        maxSize,
                             String     *content,
                             int64_t    *filesize,
                             int64_t    *modifyTime,
                             int64_t    *createtime);

            int readToBuffer(int *size);

            const char* buffer() const { return buf_; }

            static const int kBuffSize = 64 * 1024;
        private:
            int fd_;
            int err_;
            char buf_[kBuffSize];
        };
        template <typename String>
        int readFile(StringArg filename,
                     int        maxSize,
                     String     content,
                     int64_t* fileSize = NULL,
                     int64_t* modifyTime = NULL,
                     int64_t* createTime = NULL)
        {
            ReadSmallFile file(filename);
            return file.readToString(maxSize, content, fileSize, modifyTime, createTime);
        }
        class AppendFile : boost::noncopyable
        {
        public:
            AppendFile(StringArg filename);
            ~AppendFile();

            void append(const char *logline, const size_t len);

            void flush();

            off_t writtenBytes() const
            {   return writtenBytes_; }

        private:
            size_t write(const char* logline, size_t len);

            FILE* fp_;
            char buffer_[64*1024];
            off_t writtenBytes_;
        };
    }
}



#endif //MUDUO_FILEUTIL_H
