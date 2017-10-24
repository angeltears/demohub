#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#define MAXLINE 512
#define FIFO1 "/home/fire/桌面/fifo.1"
#define FIFO2 "/home/fire/桌面/fifo.2"
#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
static char read_buf[MAXLINE]; /*4096字节大小的全局缓冲区*/  
static int read_cnt; /*read_buf中待读取的字节数*/
static char *read_ptr; /*read_buf的读指针*/  
void client(int readfd, int writefd);
void server(int readfd, int writefd);
static ssize_t my_read(int fd, char *ptr);  
ssize_t Readline(int fd, void *vptr, size_t maxlen);
