#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <unistd.h>
#include "socket.h"

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFF_SIZE 512
#define UDP_BUFF_SIZE 1024

int setnoblocking(int fd)
{
  int oldopt = fcntl(fd, F_GETFL);
  int newopt = oldopt | O_NONBLOCK;
  fcntl(fd, F_SETFL, newopt);
  return oldopt;
}

void addfd(int epollfd, int fd)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  setnoblocking(fd);
}

void delfd(int epollfd, int fd)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);
  setnoblocking(fd);
}

int main(int argc, char *argv[])
{
  int port = atoi(argv[2]);
  int tcpfd = start_up(argv[1], port, TCP);
  int udpfd = start_up(argv[1], port, UDP);

  int epollfd = epoll_create(LISTEN_QUEUE_SIZE);
  assert(epollfd != -1);
  epoll_event events[MAX_EVENT_NUMBER];
  addfd(epollfd,tcpfd);
  addfd(epollfd,udpfd);
  struct sockaddr_in addr;
  socklen_t len;
  while (1)
  {
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if (number < 0)
    {
      perror("epoll error");
      break;
    }

    for (int i = 0; i < number; i++)
    {
      int sockfd = events[i].data.fd;
      if (sockfd == tcpfd)
      {
        len = sizeof(addr);
        bzero(&addr, len);
        int connfd = accept(tcpfd, (struct sockaddr *)&addr, &len);
        if (connfd < 0)
        {
          perror("accept error");
          continue;
        }
        addfd(epollfd, connfd);
      }
      else if(sockfd == udpfd)
      {
        char buf[UDP_BUFF_SIZE];
        memset(buf, '\0', sizeof(buf));
        len = sizeof(addr);
        bzero(&addr, len);
        int ret = recvfrom(sockfd, buf, UDP_BUFF_SIZE-1, 0,\
              (struct sockaddr *)&addr, &len);
        if (ret > 0)
        {
          sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr *)&addr, len);
        }
      }
      else if(events[i].events & EPOLLIN)
      {
        char buf[TCP_BUFF_SIZE];
        while (1)
        {
          memset(buf, '\0', sizeof(buf));
          int ret = recv(sockfd, buf, TCP_BUFF_SIZE, 0);
          if (ret < 0)
          {
              if((errno == EAGAIN) || (errno == EWOULDBLOCK))
              {
                  break;
              }
              delfd(epollfd, sockfd);
              close(sockfd);
              break;
          }
          else if(ret == 0)
          {
              close(sockfd);
          }
          else
          {
            send(sockfd, buf, TCP_BUFF_SIZE, 0);
          }
        }
      }
    }
  }
  close(tcpfd);
  return 0;
}
