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
  char sendline[BUFFER_SIZE], recline[BUFFER_SIZE];
  int n;
  while(fgets(sendline, BUFFER_SIZE, fp) != NULL)
  {
    write(socket, sendline, strlen(sendline) + 1);

    if ((n = read(socket, recline, BUFFER_SIZE)) == -1)
    {
      perror("read error");
      exit(1);
    }

    fputs(recline, stdout);
  }
}
