#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <string.h>
#include <sys/stropts.h>
#define LISTEN_QUTE_SIZE 5
#define MAX_CLIENT_SIZE 5
#define BUFF_SIZE 1024
int main()
{
    int socketfd;
    struct sockaddr_in ser, cli;
    socklen_t len;
    int ret;
    unsigned long cli_num = 0;
    fd_set set;
    char buff[BUFF_SIZE];
    int n;
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    ser.sin_family = AF_INET;
    ser.sin_port = htons(9090);
    inet_pton(AF_INET, "127.0.0.1", &ser.sin_addr);
    len = sizeof(ser);
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, NULL, 0);
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, NULL, 0);
    ret = bind(socketfd, (struct sockaddr *)&ser, len);
    if (ret == -1)
    {
      perror("bind error:");
      exit(1);
    }

    ret = listen(socketfd, LISTEN_QUTE_SIZE);
    if (ret == -1)
    {
      perror("listen error:");
      exit(1);
    }

    int epolfd = epoll_create(MAX_CLIENT_SIZE+1);
    struct epoll_event events[MAX_CLIENT_SIZE + 1];
    struct epoll_event clievent;

    clievent.events = EPOLLIN|EPOLLET;
    clievent.data.fd = socketfd;
    epoll_ctl(epolfd ,EPOLL_CTL_ADD, socketfd, &clievent);
    int sockfd;

    while(1)
    {
      int nready = epoll_wait(epolfd, events, MAX_CLIENT_SIZE +1, -1);

      if (nready  == -1)
      {
        perror("epoll_wait :");
        continue;
      }
      else if(nready == 0)
      {
        perror("time out:");
        continue;
      }
      else
      {
          int i;
          for(i = 0; i < nready; i++)
          {
            if(events[i].data.fd  == socketfd)
            {
              printf("a new cli in\n");
              ret = accept(socketfd, (struct sockaddr *)&cli, &len);
              clievent.data.fd = ret;
              clievent.events = EPOLLIN|EPOLLET;
              epoll_ctl(epolfd ,EPOLL_CTL_ADD, ret, &clievent);
            }
            else if(events[i].events & EPOLLIN)
            {
              if (events[i].data.fd < 0)
              {
                perror("accept error:");
                continue;
              }
              else if ((n = read(events[i].data.fd, buff, BUFF_SIZE)) < 0)
              {
                perror("read error");
                continue;
              }
              else
              {
                sockfd = events[i].data.fd;
                if (!strcmp(buff, "quit"))
                {
                  clievent.data.fd = sockfd;
                  epoll_ctl(epolfd,EPOLL_CTL_DEL,sockfd,&clievent);
                  printf("one cli close\n");
                }
                write(sockfd, buff, strlen(buff)+1);
                clievent.data.fd = sockfd;
                clievent.events = EPOLLIN|EPOLLET;
                epoll_ctl(epolfd,EPOLL_CTL_MOD,sockfd,&clievent);
              }

            }
          }
        }
      }
    }
