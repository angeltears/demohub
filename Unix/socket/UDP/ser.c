#include "../socket.h"
#include "../utili.h"

int main()
{
    int sockSer = start_up("127.0.0.1",9090, UDP);
    char sendbuf[128];
    char recvbuf[128];
    struct sockaddr_in addrCli;
    socklen_t len = sizeof(struct sockaddr );
    while (1)
    {
        recvfrom(sockSer, recvbuf, 128, 0, (struct sockaddr*)&addrCli, &len);
        printf("Cli > %s\n", recvbuf);
        printf ("Ser >");
        scanf("%s", sendbuf);
        sendto(sockSer, recvbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrCli, len);
    }
    close(sockSer);
    exit(0);
}
