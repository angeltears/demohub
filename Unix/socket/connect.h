#ifndef _CONNECT_H
#define _CONNECT_H

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
int setnoblocking(int fd);
int unblcok_connect(const char *ip, int port, int time);

int setnoblocking(int fd)
{
  int oldopt = fcntl(fd, F_GETFL);
  int newopt = oldopt | O_NONBLOCK;
  fcntl(fd, F_SETFL, newopt);
  return oldopt;
}

int unblcok_connect(const char *ip, int port, int time)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, sizeof(addr));
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int fdopt = setnoblocking(sockfd);

    int ret = connect(sockfd, (struct sockaddr *)&addr, len);
    if (ret == 0 )
    {
        printf("connect success immediately\n");
        fcntl(sockfd, F_SETFL, fdopt);
        return sockfd;
    }
    else if(errno != EINPROGRESS)
    {
        printf("unblock connect not support\n");
        return -1;
    }

    fd_set readfds;
    fd_set writefds;

    FD_ZERO(&writefds);
    FD_SET(sockfd, &writefds);

    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = select(sockfd +1, NULL , &writefds, NULL, &timeout);
    if (ret <= 0)
    {
      perror("select error");
      close(sockfd);
      return -1;
    }
    if (!FD_ISSET(sockfd, &writefds))
    {
      printf("no events on sockfd found\n");
      close(sockfd);
      return -1;
    }

    int error = 0;
    socklen_t length = sizeof(error);
    if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &length) < 0)
    {
      printf("get sockopt fail\n");
      close(sockfd);
      return -1;
    }
    if (error != 0)
    {
      printf("connect failed after select with error %d\n", error);
      close(sockfd);
      return -1;
    }
    printf("connect ready after select with socket %d\n", sockfd);
    fcntl(sockfd, F_SETFL, fdopt);
    return sockfd;
}

#endif
