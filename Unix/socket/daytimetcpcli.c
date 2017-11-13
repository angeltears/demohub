#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 512

int main(int argc, char *argv[])
{
    int socketfd, n;
    char recbuff[MAX_LINE + 1];
    struct sockaddr_in servaddr;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    n = 0;
    n = read(socketfd, recbuff, MAX_LINE);
    recbuff[n] = 0;
    fputs(recbuff, stdout);

    exit(0);


    
}
