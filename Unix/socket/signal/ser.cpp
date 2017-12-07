
#include "../socket.h"
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/epoll.h>
#include <assert.h>
#define MAX_EVENT_NUM 1024
#define ERROR_SIZE 1024

static int pipefd[2];

int setnoblocking(int fd)
{
  int oldopt = fcntl(fd,F_GETFL);
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

int addsig(int sig)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sig_handler;
  sa.sa_flags |= SA_RESTART;
  sigfillset(&sa.sa_mask);
  assert(sigaction(sig, &sa, NULL) != -1);
}


int main(int argc, char *argv[])
{
  int listenfd = start_up(argv[1], atoi(argv[2]), TCP);
  assert(listenfd != -1);

  epoll_event events[MAX_EVENT_NUM];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  addfd(epollfd,listenfd);

  int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
  assert(ret != -1);
  setnoblocking(pipefd[1]);
  addfd(epollfd, pipefd[0]);

  addsig(SIGHUP);
  addsig(SIGCHLD);
  addsig(SIGTERM);
  addsig(SIGINT);
  bool stop_server = false;

  while(!stop_server)
  {
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUM, -1);

    if ((number == -1) && (errno != EINTR))
    {
      perror("epoll_Wait error");
      break;
    }

    for (int i = 0; i < number; i++)
    {
      int sockfd = events[i].data.fd;

      if ((sockfd == listenfd) && (events[i].events & EPOLLIN))
      {
        printf("one cli coming in \n");
        struct sockaddr_in cli;
        socklen_t len = sizeof(cli);
        memset(&cli, 0, len);
        int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
        assert(connfd != -1);
        addfd(epollfd, connfd);
      }

      if ((sockfd == pipefd[0]) && (events[i].events & EPOLLIN))
      {
        int sig;
        char signals[ERROR_SIZE];
        ret = recv(pipefd[0], signals, ERROR_SIZE-1, 0);
        if (ret == -1)
        {
          continue;
        }
        else if(ret == 0)
        {
          continue;
        }
        else
        {
          for (int i = 0; i < ret ; ++i)
          {
            switch (signals[i]) {
              case SIGCHLD:
              case SIGHUP:
              {
                continue;
              }
              case SIGTERM:
              case SIGINT:
              {
                stop_server = true;
                break;
              }
            }
          }
        }
      }
      else if (events[i].events & EPOLLIN)
      {
          char buff[BUFFER_SIZE];
          ret = recv(sockfd, buff, BUFFER_SIZE -1, 0);
          if (ret == -1)
          {
            close(sockfd);
          }
          else if(ret == 0)
          {
            continue;
          }
          else
          {
            ret = send(sockfd, buff, strlen(buff)+1, 0);
            assert(ret != -1);
        }
      }

    }
  }
  printf("close fds\n");
  close(listenfd);
  close(pipefd[0]);
  close(pipefd[1]);
  return 0;
}
