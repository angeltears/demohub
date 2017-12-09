
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <assert.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include "time_wheel.h"
#include "../../socket.h"
#define FD_LIMIT 65535
#define MAX_EVENT_NUMBER 1024
#define TIMESLOT 5

static int pipefd[2];
static time_wheel timer_wheel;
static int epollfd = 0;

int setnoblocking(int fd)
{
  int oldopt = fcntl(fd, F_GETFL);
  int newopt = oldopt | O_NONBLOCK;
  fcntl(fd, F_SETFL, newopt);
  return oldopt;
}

void addfd(int epollfd, int fd)
{
  epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  setnoblocking(fd);
}

void sig_handler(int sig)
{
  int save_errno = errno;
  int msg = sig;
  send(pipefd[1], (char *)&msg, 1, 0);
  errno = save_errno;
}
void addsig(int sig)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sig_handler;
  sa.sa_flags |= SA_RESTART;
  sigfillset(&sa.sa_mask);
  assert(sigaction(sig, &sa, NULL) != -1);
}
void timer_handler()
{
  timer_wheel.tick();
  alarm(1);
}

void cb_func(client_data * user_data)
{
  epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
  assert(user_data);
  close(user_data->sockfd);
  printf("close fd %d\n", user_data->sockfd);
}


int main(int argc, char *argv[])
{
  int listenfd = start_up(argv[1], atoi(argv[2]), TCP);
  assert(listenfd != -1);

  epoll_event events[MAX_EVENT_NUMBER];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  addfd(epollfd, listenfd);

  int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
  assert(ret != -1);
  addfd(epollfd, pipefd[0]);
  setnoblocking(pipefd[1]);

  addsig(SIGALRM);
  addsig(SIGTERM);
  bool stop_server = false;

  client_data *user = new client_data[FD_LIMIT];
  bool timeout = false;
  alarm(TIMESLOT);


  while (!stop_server)
  {
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if ((number < 0) && (errno != EINTR))
    {
      perror("epoll_wait error");
      break;
    }

    for (int i = 0; i < number; i++)
    {
      int sockfd = events[i].data.fd;
      if (sockfd == listenfd)
      {
        struct sockaddr_in cli;
        socklen_t len = sizeof(cli);
        bzero(&cli, len);
        int connfd = accept(listenfd, (sockaddr *)&cli, &len);
        assert(connfd != -1);
        addfd(epollfd, connfd);
        user[connfd].address = cli;
        user[connfd].sockfd = connfd;
        tw_timer *timer = timer_wheel.add_timer(TIMESLOT);
        timer->cb_func = cb_func;
        timer->user_data = &user[connfd];
        user[connfd].timer = timer;
      }

      else if ((sockfd == pipefd[0])&&(events[i].events & EPOLLIN))
      {
        int sig;
        char signals[1024];
        ret = recv(pipefd[0], signals, sizeof(signals), 0);
        if (ret == -1)
        {
          continue;
        }
        else if (ret == 0)
        {
          continue;
        }
        else
        {
          for (int i = 0; i < ret; ++i)
          {
            switch (signals[i])
            {
              case SIGALRM:
              {
                timeout = true;
                break;
              }
              case SIGTERM:
              {
                stop_server = true;
              }
            }
          }
        }
      }
      else if (events[i].events & EPOLLIN)
      {
        memset(user[sockfd].buff, 0, sizeof(user[sockfd].buff));
        ret = recv(sockfd, user[sockfd].buff, BUFF_SIZE, 0);
        printf("get %d bytes from sockfd %d\n", ret, sockfd);

        tw_timer *timer = user[sockfd].timer;
        if (ret < 0)
        {
          if (errno != EAGAIN)
          {
            cb_func(&user[sockfd]);
            if (timer)
            {
              timer_wheel.del_timer(timer);
            }
          }
        }
        else if (ret == 0)
        {
          cb_func(&user[sockfd]);
          if (timer)
          {
            timer_wheel.del_timer(timer);
          }
        }
        else
        {
          send( sockfd, user[sockfd].buff, strlen(user[sockfd].buff), 0 );
          if(timer)
          {
            timer_wheel.del_timer(timer);
            timer = timer_wheel.add_timer(TIMESLOT);
            user[sockfd].timer = timer;
            timer->cb_func = cb_func;
            timer->user_data = &user[sockfd];
          }
        }
      }
    }
    if (timeout)
    {
      timer_handler();
      timeout = false;
    }
  }
  close(listenfd);
  close(pipefd[0]);
  close(pipefd[1]);
  delete[]user;
  return 0;
}
