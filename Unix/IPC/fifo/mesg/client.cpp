#include "mesg.h"

int main()
{
    client cl;
    int readfd, writefd;

    writefd = open(FIFO1, O_WRONLY, 0);
    readfd = open(FIFO2, O_RDONLY, 0);
        
    cl._client(readfd, writefd);

    close(readfd);
    close(writefd);

    unlink(FIFO1);
    unlink(FIFO2);
    exit(0);
}
