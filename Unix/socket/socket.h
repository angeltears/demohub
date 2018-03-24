#ifndef _SOCKET_H
#define _SOCKET_H
#define TCP 0
#define UDP 1
#define LISTEN_QUEUE_SIZE 5
#include "utili.h"
int start_up(char *ip, short port, int mode)
{
  int sockfd;
  if (mode  == TCP)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
  else if (mode == UDP)
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  else
  {
        printf("mode error, mode is must TCP or UDP");
        return -1;
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip);

  socklen_t len = sizeof(struct sockaddr);

  int oflag = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &oflag, sizeof(int));
  int ret = bind(sockfd, (struct sockaddr *)&address, len);
  if (ret == -1)
  {
    perror("bind :");
    return -1;
  }

  if (mode == TCP)
  {
    ret = listen(sockfd, LISTEN_QUEUE_SIZE);
    if (ret == -1)
    {
      perror("listen :");
      return -1;
    }
  }
  return sockfd;
}

#endif
