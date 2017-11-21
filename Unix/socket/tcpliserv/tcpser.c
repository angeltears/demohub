#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define SERV_PORT 9877
#define BUFFER_SIZE 1024
void Listen(int fd, int backlog);
void str_echo(int socket);
int main(int argc, char *argv[])
{
  int listenfd, connfd;
  pid_t pid;
  socklen_t serlen, clilen;
  struct sockaddr_in cliaddr, seraddr;
  int ret = 0;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1)
  {
      perror("socket error");
      exit(1);
  }

  bzero(&seraddr, sizeof(seraddr));
  seraddr.sin_family = AF_INET;
  seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  seraddr.sin_port = htons(SERV_PORT);

  serlen = sizeof(seraddr);
  ret = bind(listenfd, (struct sockaddr*)&seraddr, serlen);
  if (ret == -1)
  {
      perror("bind error");
      exit(1);
  }

  Listen(listenfd, 0);

  while(1)
  {
    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

    if ((pid = fork()) < 0)
    {
      close(listenfd);
      str_echo(connfd);
      exit(0);
    }
    close(connfd);
  }
}

void str_echo(int socket)
{
  ssize_t n;
  char buff[BUFFER_SIZE];

again:
  while((n = read(socket, buff, BUFFER_SIZE)) > 0)
  {
      write(socket, buff, strlen(buff) + 1);

      if (n < 0 && errno == EINTR)
      {
        goto again;
      }
      else if(n < 0)
      {
        perror("str_echo read error");
        exit(1);
      }
  }
}
void Listen(int fd, int backlog)
{
    char *ptr;
    if ((ptr = getenv("LISTENQ")) != NULL)
    {
        backlog = atoi(ptr);
    }

    if (listen(fd, backlog) < 0)
    {
        perror("Listen error");
        exit(1);
    }
}
