#ifndef _UTILI_H
#define _UTILI_H

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#define SERVER_IP   "127.0.0.1"
#define LISTEN_QUEUE_SIZE 5
#define BUFFER_SIZE 1024
#define MAXLINE 4096
///////////////////////////////////////////////////
ssize_t Readn(int fd, void *vptr, size_t n);
ssize_t Writen(int fd, void *vptr, size_t n);
ssize_t Readline(int fd, void *vptr, size_t n);
ssize_t Readlinebuf(void **vptrptr);
void Listen(int fd, int backlog);
///////////////////////////////////////////////////
ssize_t Readn(int fd, void *vptr, size_t n)
{
  size_t nleft;
  size_t nread;
  char *ptr;

  ptr = (char *)vptr;
  nleft = n;

  while(nleft > 0)
  {
    if ((nread = read(fd, ptr, nleft)) < 0)
    {
      if(errno == EINTR)
      {
        nread = 0;
      }
      else
      {
        return -1;
      }
    }
    else if(nread == 0)
    {
        break;
    }

    nleft = nleft - nread;
    ptr += nread;
  }
  return (n - nleft);
}
////////////////////////////////////////////////////////////////
ssize_t Writen(int fd, void *vptr, size_t n)
{
  size_t nleft;
  size_t nwrite;
  char *ptr;

  ptr = (char *)vptr;
  nleft = n;

  while(nleft > 0)
  {
    if ((nwrite = write(fd, ptr, nleft)) <= 0)
    {
      if(errno == EINTR && nwrite < 0)
      {
        nwrite = 0;
      }
      else
      {
        return -1;
      }
    }

    nleft = nleft - nwrite;
    ptr += nwrite;
  }
    return (n - nleft);
}
///////////////////////////////////////////////////////////
static int read_cnt;
static char *read_ptr;
static char read_buff[MAXLINE];
static ssize_t my_read(int fd, char *ptr);
static ssize_t my_read(int fd, char *ptr)
{
  if (read_cnt <= 0)
  {
    again:
      if((read_cnt = read(fd, read_buff, sizeof(read_buff))) < 0)
      {
        if(errno = EINTR)
        {
          goto again;
        }
        return -1;
      }
      else if(read_cnt == 0)
      {
        return 0;
      }
      read_ptr = read_buff;
  }

  read_cnt--;
  *ptr = *read_ptr++;
  return(1);
}

ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
  ssize_t n, rc;
  char c, *ptr;

  ptr = (char *)vptr;
  for(n = 1; n < maxlen; n++)
  {
    if (rc = my_read(fd ,&c) == 1)
    {
      *ptr++ = c;
      if (c == '\n')
      {
        break;
      }
      else if(rc == 0)
      {
        *ptr = '\0';
        return (n-1);
      }
      else
      {
        return -1;
      }
    }
  }
  *ptr = 0;
  return (n);
}

ssize_t Readlinebuf(void **vptrptr)
{
  if (read_cnt)
  {
    *vptrptr = read_ptr;
  }
  return read_cnt;
}

////////////////////////////////////////////////////////////
void Listen(int fd, int backlog)
{
    char *ptr;

    if ((ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
    {
        perror("Listen error");
        exit(1);
    }
}


#endif // _UTILI_H
