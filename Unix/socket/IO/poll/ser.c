#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <poll.h>
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
    struct pollfd cli_fd[MAX_CLIENT_SIZE];
    unsigned long cli_num = 0;
    fd_set set;
    char buff[BUFF_SIZE];
    int n;
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    int socket_clifd;
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

    cli_fd[0].fd = socketfd;
    cli_fd[0].events = POLLRDNORM;
    int i;
    for(i = 1; i < MAX_CLIENT_SIZE; i++)
    {
      cli_fd[i].fd = -1;
    }
    cli_num = 0;


    while(1)
    {
      int nready = poll(cli_fd, cli_num + 1, -1);
      if (nready  == -1)
      {
        perror("select :");
        continue;
      }
      else if(nready == 0)
      {
        perror("time out:");
        continue;
      }
      else
      {
          if(cli_fd[0].revents & POLLRDNORM)
          {
            ret = accept(socketfd, (struct sockaddr*)&cli, &len);
            if (ret == -1)
            {
              perror("accept error");
              continue;
            }
            printf("A New Client Come Baby.\n");

            for (i = 0; i< MAX_CLIENT_SIZE; ++i)
            {
              if(cli_fd[i].fd == -1)
              {
                cli_fd[i].fd = ret;
                break;
              }
            }
            if (i >= MAX_CLIENT_SIZE)
            {
              printf("Server Over Load.\n");
              continue;
            }
            cli_fd[i].events = POLLRDNORM;

            if (i > cli_num)
              cli_num = i;
            if (--nready  <= 0)
              continue;
          }
          for (i = 1; i< MAX_CLIENT_SIZE; ++i)
          {

              if((socket_clifd= cli_fd[i].fd) < 0)
              {
                  continue;
              }
              if(cli_fd[i].revents & (POLLRDNORM | POLLERR))
              {
                if ((n = read(socket_clifd, buff, BUFF_SIZE)) < 0)
                {
                  if(errno == ECONNRESET)
                  {
                    close(socket_clifd);
                    cli_fd[i].fd = -1;
                  }
                  else
                  {
                    perror("read error");
                    continue;
                  }
                }
                else if(n == 0)
                {
                    close(socket_clifd);
                    cli_fd[i].fd = -1;
                }
                else
                {
                  if (!strcmp(buff, "quit"))
                  {
                    for (i = 1; i< MAX_CLIENT_SIZE; ++i)
                    {
                        if(socket_clifd == cli_fd[i].fd)
                        {
                           cli_fd[i].fd = -1;
                           cli_fd[i].events = 0;
                           cli_num--;
                        }
                    }
                  }
                  else
                    write(socketfd, buff, strlen(buff)+1);
                }
                if (--nready <= 0)
                {
                  break;
                }


              }
            }
          }
        }
}
