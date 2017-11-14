#include "../socket.h"
#include "../utili.h"

int main()
{
    int sockSer = start_up("192.168.1.171",9090, UDP);
    char sendbuf[128];
    char recvbuf[128];
    struct sockaddr_in addrCli;
    socklen_t len = sizeof(struct sockaddr );
    while (1)
    {
      printf ("Cli >");
      scanf("%s", sendbuf);
      sendto(sockSer, recvbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrCli, len);
      recvfrom(sockSer, recvbuf, 128, 0, (struct sockaddr*)&addrCli, &len);
      printf("Ser > %s\n", recvbuf);
    }
    close(sockSer);
    exit(0);
}
