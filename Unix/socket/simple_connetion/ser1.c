

#include"../utili.h"

int main()
{
    int sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockSer == -1)
    {
        perror("socket.");
        return -1;
    }

    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY

    socklen_t len = sizeof(struct sockaddr);

    int yes = 1;
    setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }


    ret = listen(sockSer, LISTEN_QUEUE_SIZE);
    if(ret == -1)
    {
        perror("listen");
        return -1;
    }

    int sockConn ;
    /* while((sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len)) == -1)
       {
       printf("Server Accept Client Connect Error.\n");
       }

       printf("Server Accept Clent Connect Success.\n");
       printf("Client IP:> %s\n", inet_ntoa(addrCli.sin_addr));
       printf("Client Port:> %d\n",ntohs(addrCli.sin_port));
       */

    while(1)
    {
        sockConn = accept(sockSer,(struct sockaddr*)&addrCli, &len);
        if(sockConn == -1)
            continue;
        else
        {
            printf("Server Accept Clent Connect Success.\n");
            printf("Client IP:> %s\n", inet_ntoa(addrCli.sin_addr));
            printf("Client Port:> %d\n",ntohs(addrCli.sin_port));
            pid_t pid = fork();
            if (pid == 0)
            {
              char sendbuf[BUFFER_SIZE];
              while(1)
              {
                recv(sockConn, sendbuf, BUFFER_SIZE, 0);
                printf("Cli:>%s\n",sendbuf);
                send(sockConn, sendbuf, strlen(sendbuf)+1, 0);
                printf("Ser:>%s\n",sendbuf);
              }
            }
            else
            {
              continue;
            }
        }
    }
    close(sockSer);
    return 0;
}
