#include <iostream>
#include "../calc.h"
#include "../../socket.h"
#include <list>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

typedef struct cli_node
{
  char ip[16];
  uint16_t short port;
}cli_node;

typedef struct cli_info
{
  int cli_num;
  list<cli_node*> it;
}cli_info;
void* process_handler(void *);
void* Server_Seach(void *arg);
cli_info cli;

int main()
{
  cli.cli_num = 0;

  pthread_t tid;
  pthread_create(&tid, NULL, Server_Seach, &cli);

  int sockfd = start_up("127.0.0.1", 9090, TCP);
  struct sockaddr_in cli_addr;
  socklen_t len = sizeof(cli_addr);
  int resock;

  while(1)
  {
      resock = accept(sockfd, (struct sockaddr*)&cli_addr, &len);
      if (resock == -1)
      {
        perror("accept error");
        continue;
      }
      else
      {
        cli.cli_num++;
        cli_node *next = new cli_node;
        strcpy(next->ip, inet_ntoa(cli_addr.sin_addr));
        next->port = abs(ntohs(cli_addr.sin_port));
        cli.it.push_back(next);
      }

      pthread_create(&tid, NULL, process_handler, &resock);
  }

}




void* Server_Seach(void *arg)
{
    cli_info *info = (cli_info*)arg;
    int select = 1;
    while(select)
    {
        printf("***********************************\n");
        printf("* [1] Search Client Num           *\n");
        printf("* [2] Search Client Info          *\n");
        printf("* [0] Quit System                 *\n");
        printf("***********************************\n");
        printf("Input Choice:>");
        scanf("%d",&select);
        switch(select)
        {
        case 1:
            printf("client number:> %d\n",info->cli_num);
            break;
        case 2:
            {
                list<cli_node *>::iterator it = (info->it).begin();
                while(it != (info->it).end())
                {
                    cout<<"----------------------"<<endl;
                    cout<<"* client ip:>"<<(*it)->ip<<endl;
                    cout<<"* client port:>"<<abs((*it)->port)<<endl;
                    cout<<"----------------------"<<endl;
                    ++it;
                }
            }
            break;
        }
    }
}

void* process_handler(void *arg)
{
  int sockConn = *(int *)arg;
  int ret_byte_size;
  int result;
  calcst oper;
  struct sockaddr_in cli_addr;
  socklen_t len;
  while(1)
  {
      ret_byte_size = recv(sockConn, &oper, sizeof(oper), 0);
      if(ret_byte_size < 0)
      {
          perror("redv data error.");
          continue;
       }
       if(oper.op == ADD)
          result = oper.op1 + oper.op2;
       else if(oper.op == SUB)
          result = oper.op1 - oper.op2;
       else if(oper.op == MUL)
          result = oper.op1 * oper.op2;
       else if(oper.op == DIV)
          result = oper.op1 / oper.op2;
       else if(oper.op == MOD)
          result = oper.op1 % oper.op2;
       else if(oper.op == QUIT)
       {
          printf("Client Quit.\n");
          --cli.cli_num;
          getsockname(sockConn, (struct sockaddr*)&cli_addr, &len);
          list<cli_node *>::iterator it = (cli.it).begin();
          while(it != (cli.it).end())
          {
            if (!strcmp((*it)->ip, inet_ntoa(cli_addr.sin_addr)));
            cli.it.remove(*it);
          }
          break;
       }

       ret_byte_size = send(sockConn, &result, sizeof(result), 0);
       if(ret_byte_size < 0)
       {
          perror("send data error.");
          continue;
       }
 }
 close(sockConn);
}
