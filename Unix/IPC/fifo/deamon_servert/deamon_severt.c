#include "fifo.h"

int main()
{
    int readfd, writefd, dummyfd, fd;
    char *ptr, buff[MAXLINE+1], fifoname[MAXLINE];
    pid_t pid;
    ssize_t n;
    int ret;

    if (((ret = mkfifo(FIFO1, FILE_MODE)) < 0) && (errno != EEXIST))
        perror("mkfifo fail:");

    readfd = open(FIFO1, O_RDONLY, 0);
    dummyfd = open(FIFO1, O_WRONLY, 0);
    while(1)
    {
        while ((n = Readline(readfd, buff, MAXLINE)) > 0)
        {
            if (buff[n -1] == '\n')
               n--;
            buff[n] = '\0';

            if ((ptr = strchr(buff, ' ')) == NULL)
            {
                printf("can not open:%s", buff);
                continue;
            }

            *ptr++ =0;
            pid = atol(buff);   //atol 可以将字符串转化成数
            snprintf(fifoname, sizeof(fifoname),"/home/fire/桌面/fifo.%ld",(long)pid);
            if ((writefd = open(fifoname, O_WRONLY, 0)) < 0)
            {
                printf("can not open : %s", fifoname);
                continue;
            }
            if ((fd = open(ptr, O_RDONLY)) < 0)
            {
                snprintf(buff + n, sizeof(buff) - n, ": can't open,  %s\n",
                        strerror(errno));
                n = strlen(ptr);
                write(writefd, ptr, n);
                close(writefd);
            }
            else
            {
                while ((n = read(fd, buff, MAXLINE)) > 0)
                    write(writefd, buff, n);
                close(fd);
                close(writefd);
            }
        }
    }
    exit(0);
}
