#include "calc.h"

int main(int argc, char *argv[])
{
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if(socketfd == -1)
   {
       perror("socket");
       return -1;
   }
   struct sockaddr_in ser;
   ser.sin_family = AF_INET;
   ser.sin_port = htons(atoi(argv[2]));

   inet_pton(AF_INET, argv[1], &ser.sin_addr);
   socklen_t len = sizeof(struct sockaddr);
   int ret = connect(socketfd, (struct sockaddr*)&ser, len);
   if(ret == -1)
   {
      perror("connect");
      close(socketfd);
      return -1;
   }
   else
   {
      printf("Connect Server Success.\n");
   }
   calcst oper;
   char cmd[CMD_SIZE];
   int ret_byte_size;
   int result;
   while(1)
   {
       printf("please input cmd:>");
       scanf("%s", cmd);
       printf("please input op1 and op2:>");
       scanf("%d %d", &oper.op1, &oper.op2);
       if(strcmp(cmd,"add") == 0)
           oper.op = ADD;
       else if(strcmp(cmd,"sub") == 0)
           oper.op = SUB;
       else if(strcmp(cmd, "mul") == 0)
           oper.op = MUL;
       else if(strcmp(cmd, "div") == 0)
           oper.op = DIV;
       else if(strcmp(cmd, "mod") == 0)
           oper.op = MOD;
       else if(strcmp(cmd, "quit") == 0)
       {
           oper.op = QUIT;
           send(socketfd, &oper, sizeof(oper), 0);
           break;
       }

       ret_byte_size = send(socketfd, &oper, sizeof(oper), 0);
       if(ret_byte_size < 0)
       {
           perror("send data error.");
           continue;
       }
       ret_byte_size = recv(socketfd, &result, sizeof(result), 0);
       if(ret_byte_size < 0)
       {
           perror("recv data error.");
           continue;
       }
       printf("result = %d\n",result);
   }

   close(socketfd);
   printf("System Quit......\n");
   exit(0);
}
