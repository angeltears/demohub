#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#define MAXLINE 512
#define FIFO1 "/home/fire/桌面/fifo.1"
#define FIFO2 "/home/fire/桌面/fifo.2"
#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void client(int readfd, int writefd);
void server(int readfd, int writefd);

void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buff[MAXLINE];

    fgets(buff, MAXLINE, stdin);
    len = strlen(buff);
    if (buff[len -1] == '\n')
        len --;
    
    write(writefd, buff, len);

    while((n = read(readfd, buff, MAXLINE)) > 0)
        write(STDOUT_FILENO, buff, n);
}


void server(int readfd, int writefd)
{
    int fd;
    ssize_t n;
    char buff[MAXLINE + 1];

    if((n = read(readfd, buff, MAXLINE)) == 0)
        printf("end-of-file while reading pathname");
    buff[n] = '\0';

    if ((fd = open(buff, O_RDONLY)) < 0)
    {
        snprintf(buff + n,sizeof(buff) - n, ": %s\n",
                 strerror(errno));
        n = strlen(buff);
        write(writefd, buff, n);
    }
    else 
    {
        while ((n = read(fd, buff, MAXLINE)) > 0)
            write(writefd, buff, n);
        close(fd);
    }
}


int main()
{
    int readfd, writefd;
    pid_t pid;
    int ret;
    if ( ((ret = mkfifo(FIFO1, 0755)) < 0) && (errno != EEXIST))
        perror("creat fifo1 fail");
    if ( ((ret = mkfifo(FIFO2, 0755)) < 0 )&& (errno != EEXIST))
    {
        unlink(FIFO1);
        perror("creat fifo2 fail");
    }
    pid = fork();
    if (pid == 0)
    {
        readfd = open(FIFO1, O_RDONLY, 0755);
        writefd = open(FIFO2,O_WRONLY, 0755);
        printf("child");
        server(readfd, writefd);
        exit(0);
    }
    else if(pid > 0)
    {
        readfd = open(FIFO2, O_RDONLY, 0755);
        writefd = open(FIFO1, O_WRONLY, 0755);
        printf("parent");
        client(readfd, writefd);
        waitpid(pid, NULL, 0);
        
        close(readfd);
        close(writefd);

        unlink(FIFO1);
        unlink(FIFO2);
        exit(0);
    }
    else 
    {
        perror("fork error");
    }

}
