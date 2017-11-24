#include "../utili.h"
#define SERV_PORT 9877

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
    if ((pid = fork()) == 0)
    {
      printf("fork suceess\n");
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
  char buff[MAXLINE];

again:
  while((n = Readn(socket, buff, MAXLINE)) > 0)
  {
    printf("rec messege\n");
      Writen(socket, buff, n);
    printf("send messege\n");
  }
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
