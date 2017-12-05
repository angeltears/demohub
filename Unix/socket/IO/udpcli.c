#include"../utili.h"

int main()
{
    int sockCli = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockCli == -1)
    {
        perror("socket.");
        return -1;
    }
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(9090);
    addrSer.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t len = sizeof(struct sockaddr);
    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while(1)
    {
        printf("Cli:>");
        scanf("%s",sendbuf);
        if(!strcmp(sendbuf,"quit"))
        {
            sendto(sockCli, sendbuf, strlen(sendbuf)+1, 0, \
                  (struct sockaddr *)&addrSer, len);
            break;
        }
        sendto(sockCli, sendbuf, strlen(sendbuf)+1, 0, \
              (struct sockaddr *)&addrSer, len);

        recvfrom(sockCli, recvbuf, BUFFER_SIZE, 0,\
              (struct sockaddr *)&addrSer, &len);
        printf("From Slef Msg:>%s\n",recvbuf);
    }
    close(sockCli);
    return 0;
}
