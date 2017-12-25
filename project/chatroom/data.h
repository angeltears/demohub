#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <sys/socket.h>
typedef enum option{WRBUFF, WDFILE, RDFILE, INIT}opt;
typedef enum stats{FINSH, UPDATE}stats;
#define BUFF_SIZE 512
#define FILE_NAME_SIZE 80
#define NAME_BUFF_SIZE 20
typedef struct data
{
  opt flag;
  char buff[BUFF_SIZE];
}data;

typedef struct file_info
{
  int fd;
  char name[FILE_NAME_SIZE];
  stats flag;
}file_info;

typedef struct lpthfd
{
  int udpfd;
  char name[FILE_NAME_SIZE];
}lpthfd;


#endif
