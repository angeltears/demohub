#define _GNU_SOURCE  1
#include "utili.h"
#include "socket.h"
#include "data.h"
#include <list>
#include <iostream>
#include <pthread.h>
#define FD_LIMIT 65535
#define BUFF_SIZE 1024
using namespace std;

typedef struct client_data
{
  struct sockaddr_in addr;
  data *tmp_data;
  data cli_data;
}client_data;

typedef struct file_list
{
  int fd_num;
  list<file_info *> it;
}file_list;



int main()
{
  int sockfd = start_up(SERVER_IP, 9090, TCP);
  int udpfd = start_up(SERVER_IP, 9090, UDP);
  struct sockaddr_in cli;
  socklen_t len;

  client_data *users = new client_data[FD_LIMIT];
  struct pollfd fds[LISTEN_QUEUE_SIZE + 2];
  int user_count = 0;
  for (int i = 2; i <= LISTEN_QUEUE_SIZE; i++)
  {
    fds[i].fd = -1;
    fds[i].events = 0;
  }
  fds[0].fd = sockfd;
  fds[0].events = POLLIN | POLLRDHUP;
  fds[0].revents = 0;
  fds[1].fd = udpfd;
  fds[1].events = POLLRDHUP;
  fds[1].revents = 0;

  file_list fd_list;
  fd_list.fd_num = 0;
  while (1)
  {
    int ret = Poll(fds, LISTEN_QUEUE_SIZE, -1);
    if (ret == -1)
    {
      continue;
    }

    for(int i = 0; i < user_count + 2; i++)
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

      else if ((fds[i].fd == udpfd) && (fds[i].revents & POLLIN))
      {
        lpthfd fd;
        fd.udpfd = udpfd;
        list<file_info *>::iterator it = (fd_list.it).begin();
        while(it != (fd_list.it).end())
        {
          if ((*it)->flag == UPDATE)
          {
            break;
          }
        }
        if (it == (fd_list.it).end())
        {
          fds[1].events = POLLRDHUP;
        }
        else
        {
          fd.fd = (*it)->fd;
          pthread_t pid;
          if (users[fd.fd].cli_data.flag == WDFILE)
          {
            pthread_create(&pid, NULL, recvfile, &fd);
          }
          else
          {
            pthread_create(&pid, NULL, recvfile, &fd);
          }
          (*it)->flag == FINSH;
        }
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
        memset(&users[connfd].cli_data, 0, sizeof(data));
        int ret = recv(connfd, &(users[connfd].cli_data), sizeof(data), 0);
        printf("get %d bytes of client[%d]:%s\n", ret, connfd, users[connfd].cli_data.buff);
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
        else if(users[connfd].cli_data.flag == WDFILE)
        {
            printf("打开文件：%s\n",users[connfd].cli_data.buff);
            int fd = open(users[connfd].cli_data.buff, O_CREAT|O_EXCL|O_WRONLY, 0755);
            file_info info;
            info.fd = fd;
            info.flag = UPDATE;
            fd_list.it.push_back(&info);
            fds[1].events |= POLLIN;
        }
        else
        {
          for(int j = 1; j <= user_count; j++)
          {
            if (fds[j].fd == connfd)
            {
              continue;
            }
            if (fds[j].fd == udpfd)
            {
              continue;
            }
            fds[j].events |= ~POLLIN;
            fds[j].events |= POLLOUT;
            users[fds[j].fd].tmp_data = &(users[connfd].cli_data);
          }
        }
      }
      else if (fds[i].revents & POLLOUT && fds[i].fd != sockfd && fds[i].fd != udpfd)
      {
        int connfd = fds[i].fd;
        if (!users[connfd].tmp_data->buff)
        {
          continue;
        }
        users[connfd].tmp_data->flag = WRBUFF;
        int ret = send(connfd, users[connfd].tmp_data, sizeof(data), 0);
        printf("send a messege %d bytes to cli[%d]\n", ret, connfd);
        users[connfd].tmp_data = NULL;
        fds[i].events = POLLIN || POLLRDHUP;
      }

    }
  }
  delete []users;
  close(sockfd);
  return 0;
}
