#include "fifo.h"

int main()
{
    int readfd,writefd;

    if((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
        perror("mkfifo fail:");
    if((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST))
    {
        unlink(FIFO1);
        perror("mkfifo fail:");
    }

    readfd = open(FIFO1, O_RDONLY, 0);
    writefd = open(FIFO2, O_WRONLY, 0);

    server(readfd, writefd);
    exit(0);
}
