#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#define MAXLINE 512

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
    int pipe1[2], pipe2[2];
    pid_t pid;
    int ret;
    if ((ret = pipe(pipe1)) == -1)
    {
        printf("creat pipe1");
    }
    if ((ret = pipe(pipe2)) == -1)
    {
        printf("creat pipe2");
    }

    pid = fork();
    if (pid > 0)
    {
        close(pipe1[0]);
        close(pipe2[1]);
        client(pipe2[0], pipe1[1]);
        waitpid(pid, NULL, 0);
        exit(0);
    }
    else if(pid == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);
        server(pipe1[0], pipe2[1]);
        exit(0);
    }
    else 
        printf("fork pid");
}
