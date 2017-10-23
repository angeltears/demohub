#include "fifo.h"

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

