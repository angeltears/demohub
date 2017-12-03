#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "socket.h"
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

int setnoblocking(int fd)
{
  int oldopt = fcntl(fd, F_GETFL);
  int newopt = oldopt | O_NONBLOCK;
  fcntl(fd, F_SETFL, newopt);
  return newopt;
}

void addfd(int epollfd, int fd, bool enable_et)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN;
  if (enable_et)
  {
    event.events |= EPOLLET;
  }
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  setnoblocking(fd);
}

void lt(epoll_event* events, int number, int epollfd, int listenfd)
{
    char buff[BUFFER_SIZE];
    for (int i = 0; i < number; i++)
    {
      int sockfd = events[i].data.fd;
      if (sockfd == listenfd)
      {
        struct sockaddr_in addr;
        socklen_t len;
        int connfd = accept(listenfd, (struct sockaddr *)&addr, &len);
        addfd(epollfd, connfd, false);
      }
      else if (events[i].events & EPOLLIN)
      {
        printf("event trigger once\n");
        memset(buff, 0, BUFFER_SIZE);
        int ret = recv(sockfd, buff, BUFFER_SIZE, 0);
        if (ret <= 0)
        {
          close(sockfd);
          continue;
        }
        printf("get %d bytes of content : %s\n", ret, buff);
      }
      else
      {
        printf("something else happend\n");
      }
    }
}
void et(epoll_event* events, int number, int epollfd, int listenfd)
{
    char buff[BUFFER_SIZE];
    for (int i = 0; i < number; i++)
    {
      int sockfd = events[i].data.fd;
      if (sockfd == listenfd)
      {
        struct sockaddr_in addr;
        socklen_t len;
        int connfd = accept(listenfd, (struct sockaddr *)&addr, &len);
        addfd(epollfd, connfd, true);
      }
      else if (events[i].events & EPOLLIN)
      {
        printf("event trigger once\n");
        while(1)
        {
          memset(buff, 0, BUFFER_SIZE);
          int ret = recv(sockfd, buff, BUFFER_SIZE, 0);
          if (ret < 0)
          {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
              printf("read later\n");
              break;
            }
            close(sockfd);
            break;
          }
          else if (ret == 0)
          {
            close(sockfd);
          }
          else
          {
            printf("get %d bytes of content : %s\n", ret, buff);
          }
        }
      }
      else
      {
        printf("something else happend\n");
      }
    }
}

int main(int argc, char *argv[])
{
  int listenfd = start_up(argv[1], atoi(argv[2]), TCP);
  epoll_event events[MAX_EVENT_NUMBER];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  addfd(epollfd, listenfd, true);

  while (1)
  {
    int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);

    if (ret < 0)
    {
      perror("epoll error");
      break;
    }
    et(events, ret, epollfd, listenfd);
  //  lt(events, ret, epollfd, listenfd);
  }
  close(listenfd);
  return 0;
}
