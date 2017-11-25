#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/select.h>
#include <string.h>
#define LISTEN_QUTE_SIZE 5
#define MAX_CLIENT_SIZE 5
#define BUFF_SIZE 1024
int main()
{
    int socketfd;
    struct sockaddr_in ser, cli;
    socklen_t len;
    int ret;
    int cli_socketfd[MAX_CLIENT_SIZE] = {0};
    int cli_num = 0;
    int maxfd;
    fd_set set;
    char buff[BUFF_SIZE];
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
    maxfd = socketfd;

    while(1)
    {
      int i;
      FD_ZERO(&set);
      FD_SET(socketfd, &set);

      for (i = 0; i< MAX_CLIENT_SIZE; ++i)
      {
        if(cli_socketfd[i] != 0)
        {
          FD_SET(cli_socketfd[i], &set);
        }
      }

      ret = select(maxfd+1, &set, NULL, NULL, NULL);
      if (ret == -1)
      {
        perror("select :");
        continue;
      }
      else if(ret == 0)
      {
        perror("time out:");
        continue;
      }
      else
      {
          if(FD_ISSET(socketfd,&set))
          {
            ret =  accept(socketfd, (struct sockaddr*)&cli, &len);
            if (ret == -1)
            {
              perror("accept error");
              continue;
            }
            printf("A New Client Come Baby.\n");
            cli_num++;
            for (i = 0; i< MAX_CLIENT_SIZE; ++i)
            {
              if(cli_socketfd[i] == 0)
              {
                cli_socketfd[i] = ret;
                break;
              }
            }
            if (i >= maxfd)
            {
              printf("Server Over Load.\n");
              continue;
            }
            else if(ret > maxfd)
            {
              maxfd = ret;
            }
          }
          else
          {
            for (i = 0; i< MAX_CLIENT_SIZE; ++i)
            {
              if(FD_ISSET(cli_socketfd[i],&set))
              {
                  int recvbyte = recv(cli_socketfd[i], buff, 1024, 0);
                  if(recvbyte <= 0)
                  {
                      printf("Recv DataError.\n");
                      continue;
                  }
                  if(!strcmp(buff,"quit"))
                  {
                      cli_socketfd[i] = 0;
                      if(cli_socketfd[i] == maxfd)
                      {
                        maxfd = 0;
                        int j;
                        for(i = 0; i < MAX_CLIENT_SIZE; i++)
                        {
                          for(j = i; j < MAX_CLIENT_SIZE; j++)
                          {
                            if (cli_socketfd[i] > maxfd )
                            {
                              maxfd = cli_socketfd[i];
                            }
                          }
                        }
                      }
                      break;
                  }
                  send(cli_socketfd[i], buff, strlen(buff)+1, 0);
                }
              }
            }
          }
        }
}
