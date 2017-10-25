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
#define PIPE_BUF 2048
#define MAXDATA (PIPE_BUF - 2*sizeof(long))
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
    ssize_t mese_recv(int fd);
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
    void _client(int, int);
};

class severt:public  mesg
{
public:
    void _severt(int, int);
};
