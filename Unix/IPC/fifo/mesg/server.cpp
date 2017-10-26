#include "mesg.h"

int main()
{
    severt svt;
         
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

    svt._severt(readfd, writefd);
    exit(0);
}
