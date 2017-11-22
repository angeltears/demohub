#include "../utili.h"
#include <readline/readline.h>
#define SERV_PORT 9877

void str_cli(FILE *fp, int socket);
int main(int argc, char *argv[])
{
  int socketfd;
  struct sockaddr_in seraddr;
  int ret = 0;
  if (argc != 2)
  {
      printf("usage tcpcli <IPaddress>");
      exit(1);
  }
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&seraddr, sizeof(seraddr));
  seraddr.sin_family = AF_INET;
  seraddr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, argv[1], &seraddr.sin_addr);

  connect(socketfd , (struct sockaddr *)&seraddr, sizeof(seraddr));
  str_cli(stdin, socketfd);

  exit(0);
}


void str_cli(FILE *fp, int socket)
{
  char sendline[MAXLINE], recline[MAXLINE];
  int n;
  while(fgets(sendline, MAXLINE, fp) != NULL)
  {
    Writen(socket, sendline, strlen(sendline) + 1);
    if ((n = Readline(socket, recline, MAXLINE)) == 0)
    {
      perror("read error");
      exit(1);
    }

    fputs(recline, stdout);
  }
}
