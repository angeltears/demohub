//
// Created by onter on 18-8-19.
//

#include "FileUtil.h"
#include "Loggin.h"

#include <boost/static_assert.hpp>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace jmuduo;

FileUtil::ReadSmallFile::ReadSmallFile(StringArg filename)
    :fd_(open(filename.c_str(), O_RDONLY | O_CLOEXEC)),
     err_(0)
{
    buf_[0] = '\0';
    if (fd_ < 0)
    {
        err_ = errno;
    }
}

FileUtil::ReadSmallFile::~ReadSmallFile()
{
    if (fd_ >= 0 )
    {
        ::close(fd_);
    }
}

/***
 * @maxsize 读入最大字节数
 * @content 传出string
 * @filesize 传入传出参数文件大小
 * @modifyTime 传出参数修改时间
 * @createTime 传出参数创建事件
 * @return 返回err,没有就是0
 */
template <typename String>
int FileUtil::ReadSmallFile::readToString(int maxSize,
                                          String *content,
                                          int64_t *filesize,
                                          int64_t *modifyTime,
                                          int64_t *createTime)
{
    BOOST_STATIC_ASSERT(sizeof(off_t) == 8);
    assert(content != nullptr);
    int err = err_;
    if (fd_ > 0)
    {
        content->clear();
        if (filesize)
        {
            struct stat statbuf;
            if (::fstat(fd_, &statbuf) == 0)
            {
                if (S_ISREG(statbuf.st_mode))
                {
                    *filesize = statbuf.st_size;
                    content->reserve(static_cast<int>(std::min(implicit_cast<int64_t>(maxSize), *filesize)));
                }
                else if (S_ISDIR(statbuf.st_mode))
                {
                    err = EISDIR;
                }
                if (modifyTime)
                {
                    *modifyTime = statbuf.st_mtime;
                }
                if (createTime)
                {
                    *createTime = statbuf.st_ctime;
                }
            }
            else
            {
                err = errno;
            }

        }
    }

    while (content-> size() <  implicit_cast<size_t>(maxSize))
    {
        size_t toRead = std::min(implicit_cast<size_t>(maxSize) - content->size(), sizeof(buf_));
        ssize_t n = ::read(fd_, buf_, toRead);
        if (n > 0)
        {
            content->append(buf_, n);
        }
        else
        {
            if (n < 0)
            {
                err = errno;
            }
            break;
        }
    }
    return err;
}

int FileUtil::ReadSmallFile::readToBuffer(int *size)
{
    int err = err_;
    if (fd_ > 0)
    {
        ssize_t n = ::pread(fd_, buf_, sizeof(buf_) - 1, 0);
        if (n >= 0)
        {
            if (size)
            {
                *size = static_cast<int>(n);
            }
            buf_[n] ='\0';
        }
        else
        {
            err = errno;
        }
    }
    return err;
}

/// 模板特化
template int FileUtil::readFile(StringArg filename,
                                int maxSize,
                                string* content,
                                int64_t*, int64_t*, int64_t*);

template int FileUtil::ReadSmallFile::readToString(
        int maxSize,
        string* content,
        int64_t*, int64_t*, int64_t*);

#ifndef MUDUO_STD_STRING
template int FileUtil::readFile(StringArg filename,
                                int maxSize,
                                std::string* content,
                                int64_t*, int64_t*, int64_t*);

template int FileUtil::ReadSmallFile::readToString(
        int maxSize,
        std::string* content,
        int64_t*, int64_t*, int64_t*);
#endif


FileUtil::AppendFile::AppendFile(StringArg filename)
    :fp_(fopen(filename.c_str(), "we")),         // e for   O_CLOEXEC
     writtenBytes_(0)
{
    assert(fp_);
    ::setbuffer(fp_, buffer_, sizeof buffer_);
}

FileUtil::AppendFile::~AppendFile()
{
    ::fclose(fp_);
}

void FileUtil::AppendFile::flush()
{
    ::fflush(fp_);
}

void FileUtil::AppendFile::append(const char *logline, const size_t len)
{
    size_t n = write(logline, len);
    size_t remain  = len - n;
    while (remain > 0)
    {
        size_t x = write(logline + n, remain);
        if (x == 0)
        {
            int err = ferror(fp_);
            if (err)
            {
                fprintf(stderr, "AppendFile::append() failed %s\n", strerror(err));
            }
            break;
        }
        n += x;
        remain = len - n;
    }
    writtenBytes_ += len;
}

size_t FileUtil::AppendFile::write(const char *logline, size_t len)
{
    return ::fwrite_unlocked(logline, 1 , len, fp_);
}