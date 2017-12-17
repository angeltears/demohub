#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <sys/socket.h>
typedef enum option{WRBUFF, WDFILE, RDFILE}opt;
typedef enum stats{FINSH, UPDATE}stats;
#define BUFF_SIZE 512
typedef struct data
{
  opt flag;
  char buff[BUFF_SIZE];
}data;

typedef struct file_info
{
  int fd;
  char *name;
  stats flag;
}file_info;

typedef struct lpthfd
{
  int udpfd;
  int fd;
}lpthfd;

void *recvfile(void *arg)
{
  lpthfd *fds = (lpthfd *)arg;
  char buff[BUFF_SIZE];
  while(1)
  {
    memset(buff, 0, BUFF_SIZE);
    int ret = recvfrom(fds->udpfd, buff, BUFF_SIZE, 0, nullptr, nullptr);
    if (ret == 0)
    {
      write(fds->fd, 0, 0);
      break;
    }
    else
    {
      write(fds->fd, buff, ret);
    }
  }
}

void *sendfile(void *arg)
{
  lpthfd *fds = (lpthfd *)arg;
  char buff[BUFF_SIZE];
  while(1)
  {
    memset(buff, 0, BUFF_SIZE);
    int ret = read(fds->fd, buff, BUFF_SIZE);
    if (ret == 0)
    {
      sendto(fds->udpfd, nullptr, 0, 0, nullptr, 0);
      break;
    }
    else
    {
      sendto(fds->udpfd, buff, ret, 0, nullptr, 0);
    }
  }
}
#endif
