
#define _GNU_SOURCE  1
#include "socket.h"
#include <fcntl.h>
int main()
{
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(9090);
  address.sin_addr.s_addr = inet_addr(SERVER_IP);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  socklen_t len = sizeof(address);
  connect(sockfd, (struct sockaddr *)&address, len);
  struct  pollfd fds[2];
  fds[0].fd = 0;
  fds[0].events = POLLIN;
  fds[0].revents = 0;
  fds[1].fd = sockfd;
  fds[1].events = POLLIN | POLLRDHUP;
  fds[1].revents = 0;
  char buff[BUFFER_SIZE];
  int pipefd[2];
  int ret = pipe(pipefd);
  if (ret == -1)
  {
    perror("pipe error");
    exit(1);
  }

  while (1)
  {
    int ret = poll(fds, 2, -1);
    if (ret < 0)
    {
      perror("poll error");
      break;
    }

    if (fds[1].revents & POLLRDHUP)
    {
      printf("ser has closed\n");
      break;
    }

    if (fds[1].revents & POLLIN)
    {
      memset(buff, 0, BUFFER_SIZE);
      recv(sockfd, buff, BUFFER_SIZE, 0);
      printf("%s", buff);
    }


    if (fds[0].revents & POLLIN)
    {
        ret = splice(0, NULL, pipefd[1], NULL, BUFFER_SIZE,  SPLICE_F_MOVE| SPLICE_F_MORE);
        ret = splice(pipefd[0], NULL, sockfd, NULL, BUFFER_SIZE,  SPLICE_F_MOVE| SPLICE_F_MORE);
    }


  }
  close(sockfd);
  return 0;
}
