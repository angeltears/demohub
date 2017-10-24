#include "fifo.h"

int main()
{
    int readfd, writefd;
    size_t len;
    ssize_t n;
    char *ptr, fifoname[MAXLINE], buff[MAXLINE];
    pid_t  pid;

    pid = getpid();
    snprintf(fifoname, sizeof(fifoname), "/home/fire/桌面/fifo.%ld", (long)pid);
    if ((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST)) 
        perror("mkfifo fail:");
    snprintf(buff, sizeof(buff), "%ld ", (long)pid);
    len = strlen(buff);
    ptr = buff + len;
    fgets(ptr, MAXLINE - len, stdin);
    len = strlen(buff);

    writefd = open(FIFO1, O_WRONLY, 0);
    write(writefd, buff, len);

    readfd = open(fifoname, O_RDONLY, 0);
    while((n = read(readfd, buff, MAXLINE)) > 0)
        write(STDOUT_FILENO, buff, n);
    
    close(readfd);
    unlink(fifoname);
    exit(0);
}
