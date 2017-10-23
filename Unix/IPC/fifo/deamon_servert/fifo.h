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
#include <readline/readline.h>
void client(int readfd, int writefd);
void server(int readfd, int writefd);

