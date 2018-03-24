#define _GNU_SOURCE  1
#include "utili.h"
#include <iostream>
#include <assert.h>
#include <sys/epoll.h>
#include "data.h"
#include <pthread.h>
#include <list>
#define FD_LIMIT 65535
using namespace std;

pthread_mutex_t *mutex = new pthread_mutex_t;

typedef struct client_data
{
  struct sockaddr_in addr;
  data *tmp_data;
  data cli_data;
  char name[NAME_BUFF_SIZE];
}client_data;

typedef struct file_list
{
  int fd_num;
  list<file_info *> it;
}file_list;

void *sendfile(void *arg);
void *recvfile(void *arg);
void addfd(int epollfd, int fd)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  setnoblocking(fd);
}

void delfd(int epollfd, int fd)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);
  setnoblocking(fd);
}

void addout(int epollfd, int fd)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLOUT | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  setnoblocking(fd);
}

void delout(int epollfd, int fd)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLOUT | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);
  setnoblocking(fd);
}


typedef struct fd_data
{
    char name[20];
    int fd;
}fd_data;

int main()
{
  struct sockaddr_in ser;
  inet_pton(AF_INET, SERVER_IP, &ser.sin_addr);
  ser.sin_port = htons(8080);
  ser.sin_family = AF_INET;
  int tcpsock = socket(AF_INET, SOCK_STREAM, 0);
  assert(tcpsock > 0);
  socklen_t len = sizeof(ser);
  int oflag = 1;
  setsockopt(tcpsock, SOL_SOCKET, SO_REUSEADDR, &oflag, sizeof(int));
  int ret = bind(tcpsock, (struct sockaddr *)&ser, len);
  assert(ret != -1);
  ret = listen(tcpsock, 5);
  assert(ret != -1);

  memset(&ser, 0, len);
  int udpsock = socket(PF_INET, SOCK_DGRAM, 0);
  ser.sin_port = htons(8080);
  ser.sin_family = AF_INET;
  inet_pton(AF_INET, SERVER_IP, &ser.sin_addr);
  ret = bind(udpsock, (struct sockaddr *)&ser, len);
  assert(ret != -1);

  int epollfd = epoll_create(LISTEN_QUEUE_SIZE);
  assert(epollfd != -1);
  epoll_event events[MAX_EVENT_NUM];
  addfd(epollfd,tcpsock);
  struct sockaddr_in addr;


  client_data *users = new client_data[FD_LIMIT];
  int user_count = 0;
  file_list fd_list;
  fd_list.fd_num = 0;

  fd_data fds[FD_LIMIT];
  bzero(fds, sizeof(fds));
  data *cli_data = new data;
  pthread_mutex_init(mutex, nullptr);

  while (1)
  {
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUM+2, -1);
    if (number < 0)
    {
      perror("epoll error");
      break;
    }

    for (int i = 0; i < number; i++)
    {
      int sockfd = events[i].data.fd;
      if (sockfd == tcpsock)
      {
        int length = 0;
        len = sizeof(addr);
        bzero(&addr, len);
        int connfd = accept(tcpsock, (struct sockaddr *)&addr, &len);
        if (connfd < 0)
        {
          perror("accept error");
          continue;
        }

        if (user_count >= LISTEN_QUEUE_SIZE)
        {
          memset(cli_data, 0, sizeof(data));
          char *info = "too many cli";
          strcpy(cli_data->buff, info);
          cli_data->flag = WRBUFF;
          send(connfd, cli_data, sizeof(data), 0);
          close(connfd);
          continue;
        }
        memset(cli_data, 0, sizeof(data));
        ret = recv(connfd, cli_data, sizeof(data), 0);
        length = strlen(cli_data->buff);
        if (ret <= 0 && length > 0 && length < 20)
        {
          memset(cli_data, 0, sizeof(data));
          char *info = "error cli";
          strcpy(cli_data->buff, info);
          cli_data->flag = WRBUFF;
          send(connfd, cli_data, sizeof(data), 0);
          close(connfd);
          continue;
        }

        addfd(epollfd, connfd);
        users[connfd].addr = addr;
        fds[user_count].fd = connfd;
        user_count++;
        strcpy(users[connfd].name,cli_data->buff);
        printf("cli[%s] comming in\n",cli_data->buff);
      }

      else if(sockfd == udpsock)
      {
        printf("进入文件传输\n");
        lpthfd fd;
        fd.udpfd = udpsock;
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
          delfd(epollfd,udpsock);
        }
        else
        {
          strcpy(fd.name, (*it)->name);
          pthread_t pid;
          if (users[(*it)->fd].cli_data.flag == RDFILE)
          {
//          printf("开始发送文件\n");
//          pthread_create(&pid, NULL, sendfile, &fd);
          }
          else
          {
            printf("开始接受文件\n");
            pthread_create(&pid, NULL, recvfile, &fd);
          }
          (*it)->flag == FINSH;
          delfd(epollfd,udpsock);
        }
      }

      else if(events[i].events & EPOLLIN)
      {
        memset(&users[sockfd].cli_data, 0, sizeof(data));
        ret = recv(sockfd, &(users[sockfd].cli_data), sizeof(data), 0);
        if (ret < 0)
        {
          if(errno != EAGAIN)
          {
            bzero(&users[events[i].data.fd], sizeof(client_data));
            close(events[i].data.fd);
            user_count--;
          }
        }
        else if(ret == 0)
        {
        }
        else if(users[sockfd].cli_data.flag == WDFILE)
        {
            printf("接受文件：%s\n",users[sockfd].cli_data.buff);
            int length = strlen(users[sockfd].cli_data.buff);
            assert(length < 80);
            file_info info;
            memset(&info, 0, sizeof(info));
            strcpy(info.name, users[sockfd].cli_data.buff);
            info.flag = UPDATE;
            info.fd = sockfd;
            fd_list.it.push_back(&info);
            addfd(epollfd, udpsock);
            memset(&users[sockfd].cli_data, 0, sizeof(data));
        }
        else if(users[sockfd].cli_data.flag == RDFILE)
        {
          char *ptr  = users[sockfd].cli_data.buff;
          int ret;
          list<file_info *>::iterator it = (fd_list.it).begin();
          while(it != (fd_list.it).end())
          {
            ret = strncmp((*it)->name, ptr, strlen(ptr));
            if (ret == 0)
            {
              printf("找到文件%s\n", ptr);
              break;
            }
          }
          if (it == (fd_list.it).end() || ret != 0)
          {
            printf("文件寻找失败\n");
            memset(cli_data, 0, sizeof(data));
            char *info = "can't find file!";
            strcpy(cli_data->buff, info);
            cli_data->flag = WRBUFF;
            send(sockfd, cli_data, sizeof(data), 0);
            continue;
          }
          lpthfd fd;
          fd.udpfd = udpsock;
          strcpy(fd.name, users[sockfd].cli_data.buff);
          printf("name : %s yuanshi : %s", fd.name, ptr);
          pthread_t pid;
          printf("文件寻找成功\n");
          pthread_create(&pid, NULL, sendfile, &fd);
          sleep(1);
          memset(&users[sockfd].cli_data, 0, sizeof(data));
        }
        else
        {
          char tmp[BUFF_SIZE];
          strcpy(tmp,users[sockfd].cli_data.buff);
          snprintf(users[sockfd].cli_data.buff, BUFF_SIZE, "%s:%s", users[sockfd].name, tmp);
          for(int j = 0; j < user_count; j++)
          {
            if(fds[j].fd == sockfd)
                continue;
            delfd(epollfd, fds[j].fd);
            addout(epollfd, fds[j].fd);
            users[fds[j].fd].tmp_data = &(users[sockfd].cli_data);
          }
        }
      }
      else if(events[i].events & EPOLLOUT)
      {
        if (!users[sockfd].tmp_data->buff)
        {
          continue;
        }
        users[sockfd].tmp_data->flag = WRBUFF;
        int ret = send(sockfd, users[sockfd].tmp_data, sizeof(data), 0);
        printf("send a messege %d bytes to cli[%d]\n", ret, sockfd);
        users[sockfd].tmp_data = NULL;
        delout(epollfd, sockfd);
        addfd(epollfd, sockfd);
      }

    }
  }
  close(tcpsock);
  return 0;
}


void *recvfile(void *arg)
{
  pthread_mutex_lock(mutex);
  lpthfd *fd_data = (lpthfd *)arg;
  int fd = open(fd_data->name, O_CREAT|O_EXCL|O_WRONLY, 0755);
  char buff[BUFF_SIZE];
  while(1)
  {
    memset(buff, 0, BUFF_SIZE);
    int ret = recvfrom(fd_data->udpfd, buff, BUFF_SIZE, 0, nullptr, nullptr);
    printf("recv %d bytes from %d\n", ret, fd_data ->udpfd);
    if (ret == 0)
    {
      write(fd, 0, 0);
      break;
    }
    else
    {
      int wrt = write(fd, buff, ret);
      printf("write %d to file[%d]", wrt, fd);
    }
  }
  close(fd);
  pthread_mutex_lock(mutex);
}

void *sendfile(void *arg)
{
  printf("开始传输文件\n");
  int ret = pthread_mutex_trylock(mutex);
  if(ret < 0)
  {
    printf("加锁失败\n");
  }
  else
  {
    lpthfd *fd_data  = (lpthfd *)arg;
    char buff[BUFF_SIZE];
    printf("name %s\n", fd_data->name);
    int fd = open(fd_data->name, O_RDONLY);
    assert(fd > 0);
    while(1)
    {
      memset(buff, 0, BUFF_SIZE);
      int ret = read(fd, buff, BUFF_SIZE);
      printf("read %d bytes from fd %d\n", ret, fd);
      if (ret == 0)
      {
        sendto(fd_data ->udpfd, nullptr, 0, 0, nullptr, 0);
        break;
      }
      else if(ret < 0)
      {
        close(fd);
        perror("read error");
      }
      else
      {
        sendto(fd_data ->udpfd, buff, ret, 0, nullptr, 0);
        printf("send %d bytes to  %d\n", ret, fd_data->udpfd);
      }
    }
  close(fd);
  pthread_mutex_lock(mutex);
  }
}
