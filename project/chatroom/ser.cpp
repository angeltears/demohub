#define _GNU_SOURCE  1
#include "utili.h"
#include "socket.h"

#define FD_LIMIT 65535
#define BUFF_SIZE 1024

typedef struct client_data
{
  struct sockaddr_in addr;
  char *write_buff;
  char buff[BUFF_SIZE];
}client_data;


int main()
{
  int sockfd = start_up(SERVER_IP, 9090, TCP);
  struct sockaddr_in cli;
  socklen_t len;

  client_data *users = new client_data[FD_LIMIT];
  struct pollfd fds[LISTEN_QUEUE_SIZE + 1];
  int user_count = 0;
  for (int i = 1; i <= LISTEN_QUEUE_SIZE; i++)
  {
    fds[i].fd = -1;
    fds[i].events = 0;
  }
  fds[0].fd = sockfd;
  fds[0].events = POLLIN | POLLRDHUP;
  fds[0].revents = 0;

  while (1)
  {
    int ret = Poll(fds, LISTEN_QUEUE_SIZE, -1);
    if (ret == -1)
    {
      continue;
    }

    for(int i = 0; i < user_count + 1; i++)
    {
      if ((fds[i].fd == sockfd) && (fds[i].revents & POLLIN))
      {
        int clisock = accept(sockfd, (struct sockaddr*)&cli, &len);
        if (clisock < 0)
        {
          perror("connect error");
          continue;
        }
        if (user_count >= LISTEN_QUEUE_SIZE)
        {
          char *info = "too many cli";
          printf("%s\n",info);
          send(clisock, info, strlen(info)+1, 0);
          close(clisock);
          continue;
        }
        user_count++;
        setnoblocking(clisock);
        fds[user_count].fd = clisock;
        fds[user_count].events = POLLIN | POLLRDHUP | POLLERR;
        users[clisock].addr = cli;
        printf("a new user[%d] comming in\n", clisock);
      }
      else if (fds[i].revents & POLLERR)
      {
        printf("get an error from %d\n", fds[i].fd);
        char errors[100];
        memset(errors, 0, 100);
        socklen_t length = sizeof(errors);
        if ((getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length)) < 0)
        {
          perror("get socketopt error\n");
        }
        else
        {
          printf("%s\n",errors);
        }
        continue;
      }
      else if(fds[i].revents & POLLRDHUP)
      {
        users[fds[i].fd] = users[fds[user_count].fd];
        close(fds[i].fd);
        fds[i].fd = fds[user_count].fd;
        i--;
        user_count--;
        printf("a cli left \n");
      }
      else if(fds[i].revents & POLLIN)
      {
        int connfd = fds[i].fd;
        memset(users[connfd].buff, 0, BUFF_SIZE);
        int ret = recv(connfd, &users[connfd].buff, BUFF_SIZE, 0);
        printf("get %d bytes of client[%d]\n", ret, connfd);
        if (ret < 0)
        {
          if(errno != EAGAIN)
          {
            users[fds[i].fd] = users[fds[user_count].fd];
            close(fds[i].fd);
            fds[i].fd = fds[user_count].fd;
            i--;
            user_count--;
          }
        }
        else if(ret == 0)
        {
        }
        else
        {
          for(int j = 1; j <= user_count; j++)
          {
            if (fds[j].fd == connfd)
            {
              continue;
            }
            fds[j].events |= ~POLLIN;
            fds[j].events |= POLLOUT;
            users[fds[j].fd].write_buff = users[connfd].buff;
          }
        }
      }
      else if (fds[i].revents & POLLOUT)
      {
        int connfd = fds[i].fd;
        if (!users[connfd].write_buff)
        {
          continue;
        }
        send(connfd, users[connfd].write_buff, \
          strlen(users[connfd].write_buff)+1, 0);
        users[connfd].write_buff = NULL;
        fds[i].events |= POLLIN;
        fds[i].events |= ~POLLOUT;
      }

    }
  }
  delete []users;
  close(sockfd);
  return 0;
}
