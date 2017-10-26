#pragma once
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <new>
#define PIPE_BUF 2048
#define MAXDATA (PIPE_BUF - 2*sizeof(long))
#define FIFO1 "/home/fire/桌面/fifo.1"
#define FIFO2 "/home/fire/桌面/fifo.2"
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
struct mymesg
{
    long mesg_len;
    long mesg_type;
    char mesg_date[PIPE_BUF - 2*sizeof(long)];
};

class mesg
{
public:
    mesg();
    ssize_t setsize();
    ssize_t mesg_send(int fd);
    ssize_t mesg_recv(int fd);
    void Mesg_send(int fd);
    void Mesg_recv(int fd);
    ~mesg();
protected:
    struct mymesg* _mesg;
    ssize_t _size;
};

class client:public mesg
{
public:
    client();
    void _client(int, int);
    ~client(){};
};

class severt:public  mesg
{
public:
    severt();
    void _severt(int, int);
    ~severt(){};
};
