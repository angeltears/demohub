
#define _GNU_SOURCE  1
#include "utili.h"
#include <fcntl.h>
#include "data.h"
#include <sys/epoll.h>
#include <assert.h>
int main()
{
  data *cli_data = new data;
  struct sockaddr_in udpaddr;
  udpaddr.sin_family = PF_INET;
  udpaddr.sin_port = htons(8080);
  udpaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
  int udpfd = socket(PF_INET, SOCK_DGRAM, 0);
  socklen_t udplen = sizeof(udpaddr);
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(8080);
  address.sin_addr.s_addr = inet_addr(SERVER_IP);
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  socklen_t len = sizeof(address);
  int ret = connect(sockfd, (struct sockaddr *)&address, len);
  if (ret == -1)
    printf("can't connect ser\n");
  else
  {
    printf("log as:");
    scanf("%s",cli_data->buff);
    cli_data->flag = INIT;
    send(sockfd, cli_data, sizeof(data), 0);
  }
  int pipefd[2];
  ret = pipe(pipefd);
  if (ret == -1)
  {
    perror("pipe error");
    exit(1);
  }
  int fd = 0;
  int epollfd = epoll_create(LISTEN_QUEUE_SIZE + 2);
  struct epoll_event events[MAX_EVENT_NUM];
  struct epoll_event event;

  event.data.fd = sockfd;
  event.events = EPOLLIN | EPOLLERR | EPOLLET | EPOLLRDHUP;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &event);
  memset(&event, 0, sizeof(event));
  event.data.fd = 0;
  event.events = EPOLLIN;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, 0, &event);
  while (1)
  {

    ret = epoll_wait(epollfd, events, MAX_EVENT_NUM + 2, -1);
    if (ret < 0)
    {
      perror("poll error");
      break;
    }
    for(int i = 0; i < ret; i++)
    {
          if (events[i].data.fd == sockfd && events[i].events& POLLRDHUP)
          {
              printf("ser has closed\n");
              break;
          }

          else if (events[i].data.fd == sockfd && events[i].events & POLLIN)
          {
              memset(cli_data, 0, sizeof(data));
              int ret = recv(sockfd, cli_data, sizeof(data), 0);
              if (cli_data->flag == WRBUFF)
              {
                if (cli_data->buff == NULL)
                {
                  printf("NULL!!!\n");
                }
                printf("%s\n",  cli_data->buff);
              }
              else if(cli_data->flag == WDFILE)
              {
                printf("创建文件\n");
                fd = open(cli_data->buff, O_CREAT|O_EXCL|O_WRONLY);
                char *buff = new char[BUFF_SIZE];
                memset(buff, 0, BUFF_SIZE);
                int start = recvfrom(udpfd, buff, BUFF_SIZE, 0, (struct sockaddr *)&udpaddr, &udplen);
                write(fd, buff, start);
                while(start > 0)
                {
                  memset(buff, 0, BUFF_SIZE);
                  start = recvfrom(udpfd, buff, BUFF_SIZE, 0, (struct sockaddr *)&udpaddr, &udplen);
                  write(fd, buff, start);
                }
                write(fd, nullptr, 0);
              }
              else
              {
                printf("正在下载文件，请稍后重试！\n");
              }
            }
            else if (events[i].events & POLLIN)
            {
              char buff[BUFF_SIZE];
              memset(buff, 0, BUFF_SIZE);
              data *tmp = new data;
              memset(tmp, 0, sizeof(data));
              scanf("%s", buff);
              int ret = strncmp(buff,"FILE:", 5);
              if (ret == 0)
              {
                char *ptr  = buff + 5 * sizeof(char);
                fd = open(ptr, O_RDONLY);
                assert(fd != -1);
                if (fd > 0)
                {
                  printf("打开文件：%s FD: %d\n", ptr, fd);
                  tmp->flag = WDFILE;
                  strcpy(tmp->buff, ptr);
                  write(pipefd[1], tmp, sizeof(data));
                  ret = splice(pipefd[0], NULL, sockfd, NULL, BUFFER_SIZE,  SPLICE_F_MOVE| SPLICE_F_MORE);
                  printf("开始传输文件\n");
                  char *buff = new char[BUFF_SIZE];
                  memset(buff, 0, BUFF_SIZE);
                  int tmp = read(fd, buff, BUFF_SIZE);
                  perror("error:");
                  printf("tmp = %d\n", tmp);
                  while (tmp > 0)
                  {
                    ret = sendto(udpfd, buff, tmp, 0, (struct sockaddr *)&udpaddr, udplen);
                    memset(buff, 0, BUFF_SIZE);
                    tmp = read(fd, buff, BUFF_SIZE);
                    printf("ret = %d tmp = %d\n",ret, tmp);
                  }
                  sendto(udpfd, NULL, 0, 0, (struct sockaddr *)&udpaddr, udplen);
                }
                else
                {
                  std::cout<<"打开失败，请检查输入文件名字"<<std::endl;
                  continue;
                }
              }

              ret = strncmp(buff,"DOWN:", 5);
              if (ret == 0)
              {
                char *ptr  = buff + 5 * sizeof(char);
                fd = open(ptr, O_CREAT|O_EXCL|O_WRONLY, 0755);
                assert(fd != -1);
                if (fd > 0)
                {
                  printf("打开文件：%s FD: %d\n", ptr, fd);
                  tmp->flag = RDFILE;
                  strcpy(tmp->buff, ptr);
                  write(pipefd[1], tmp, sizeof(data));
                  ret = splice(pipefd[0], NULL, sockfd, NULL, sizeof(data),  SPLICE_F_MOVE| SPLICE_F_MORE);
                  printf("开始传输文件\n");
                  char *buff = new char[BUFF_SIZE];
                  memset(buff, 0, BUFF_SIZE);
                  int tmp = recvfrom(udpfd, buff, tmp, 0, (struct sockaddr *)&udpaddr, &udplen);
                  perror("error:");
                  printf("tmp = %d\n", tmp);
                  while (tmp > 0)
                  {
                    ret = recvfrom(udpfd, buff, tmp, 0, (struct sockaddr *)&udpaddr, &udplen);
                    memset(buff, 0, BUFF_SIZE);
                    tmp = write(fd, buff, BUFF_SIZE);
                    printf("ret = %d tmp = %d\n",ret, tmp);
                  }
                  tmp = write(fd, 0, 0);
                }
              }
              else
              {
                tmp->flag = WRBUFF;
                strcpy(tmp->buff, buff);
                write(pipefd[1], tmp, sizeof(data));
                ret = splice(pipefd[0], NULL, sockfd, NULL, sizeof(data),  SPLICE_F_MOVE| SPLICE_F_MORE);
              }
              delete tmp;
            }

        }
  }
  close(sockfd);
  return 0;
}
