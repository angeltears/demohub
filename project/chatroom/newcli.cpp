
#define _GNU_SOURCE  1
#include "utili.h"
#include <fcntl.h>
#include "data.h"
int main()
{
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(9090);
  address.sin_addr.s_addr = inet_addr(SERVER_IP);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  socklen_t len = sizeof(address);
  connect(sockfd, (struct sockaddr *)&address, len);

  struct sockaddr_in udpaddr;
  udpaddr.sin_family = AF_INET;
  udpaddr.sin_port = htons(9090);
  udpaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
  int udpfd = socket(AF_INET, SOCK_DGRAM, 0);
  bind(udpfd, (struct sockaddr *)&address, len);

  struct  pollfd fds[4];
  fds[0].fd = 0;
  fds[0].events = POLLIN;
  fds[0].revents = 0;
  fds[1].fd = sockfd;
  fds[1].events = POLLIN | POLLRDHUP;
  fds[1].revents = 0;
  fds[2].fd = udpfd;
  fds[2].events = POLLRDHUP;
  fds[2].revents = 0;
  fds[3].fd = 0;
  fds[3].events = 0;
  fds[3].revents = 0;

  data *cli_data = new data;
  int pipefd[2];
  int ret = pipe(pipefd);
  if (ret == -1)
  {
    perror("pipe error");
    exit(1);
  }
  int fd = 0;
  bool recvfile = false;
  bool sendfile = false;
  while (1)
  {
    int ret = poll(fds, 2, -1);
    if (ret < 0)
    {
      perror("poll error");
      break;
    }

    if (fds[1].revents & POLLRDHUP)
    {
      printf("ser has closed\n");
      break;
    }

    if (fds[1].revents & POLLIN)
    {
      memset(cli_data, 0, sizeof(cli_data));
      recv(sockfd, cli_data, sizeof(cli_data), 0);
      if (cli_data->flag == WRBUFF)
        printf("%s",  cli_data->buff);
      else if(cli_data->flag == WDFILE || recvfile == false)
      {
        fd = open(cli_data->buff, O_CREAT|O_EXCL|O_WRONLY);
        fds[2].events |= POLLIN;
        recvfile = true;
        sendfile = false;
      }
      else
      {
        printf("正在下载文件，请稍后重试！\n");
      }
    }

    if (fds[0].revents & POLLIN)
    {
        char buff[BUFF_SIZE];
        memset(buff, 0, BUFF_SIZE);
        scanf("%s", buff);
        int ret = strncmp(buff,"FILE:", 5);
        if (ret == 0)
        {
          char *ptr  = buff + 6 * sizeof(char);
          fd = open(ptr, O_CREAT|O_EXCL|O_WRONLY);
          fds[2].events |= POLLIN;
          sendfile = true;
          recvfile = false;
        }
        else
        {
          fputs(buff, stdin);
          ret = splice(0, NULL, pipefd[1], NULL, BUFFER_SIZE,  SPLICE_F_MOVE| SPLICE_F_MORE);
          ret = splice(pipefd[0], NULL, sockfd, NULL, BUFFER_SIZE,  SPLICE_F_MOVE| SPLICE_F_MORE);
        }
    }

    if (fds[2].revents & POLLIN & recvfile == true)
    {
      char *buff = new char[BUFF_SIZE];
      memset(buff, 0, BUFF_SIZE);
      int start = recvfrom(udpfd, buff, BUFF_SIZE, 0, nullptr, nullptr);
      write(fd, buff, start);
      while(start > 0)
      {
        memset(buff, 0, BUFF_SIZE);
        start = recvfrom(udpfd, buff, BUFF_SIZE, 0, nullptr, nullptr);
        write(fd, buff, start);
      }
      write(fd, nullptr, 0);
      fds[2].events = POLLRDHUP;
      recvfile = false;
    }
    else if (fds[2].revents & POLLIN & sendfile == true)
    {
        char *buff = new char[BUFF_SIZE];
        memset(buff, 0, BUFF_SIZE);
        int tmp = read(fd, buff, BUFF_SIZE);
        while (tmp > 0)
        {
          sendto(udpfd, buff, tmp, 0, nullptr, 0);
          memset(buff, 0, BUFF_SIZE);
          tmp = read(fd, buff, BUFF_SIZE);
        }
        sendto(udpfd, NULL, 0, 0, nullptr, 0);
        fds[2].events = POLLRDHUP;
        sendfile = false;
    }

  }
  close(sockfd);
  return 0;
}
