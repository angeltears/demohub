//////////////////////////////////////////////////////
// ///////////////////////////////////////////////////
#include<netinet/in.h>                         // for sockaddr_in
#include<sys/types.h>                          // for socket
#include<sys/socket.h>                         // for socket
#include<stdio.h>                              // for printf
#include<stdlib.h>                             // for exit
#include<string.h>                             // for bzero
#include<unistd.h>
#include<arpa/inet.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<pthread.h>
#define HELLO_WORLD_SERVER_PORT       6666
#define BUFFER_SIZE                   1024
#define FILE_NAME_MAX_SIZE 512

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void translater_dir(char *dir_name, int client_socket);
void* send_file(void *info);

struct ds_info
{
  char *file_name;
  int client_socket;
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./%s ServerIPAddress\n", argv[0]);
        exit(1);
    }

    // 设置一个socket地址结构client_addr, 代表客户机的internet地址和端口
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET; // internet协议族
    client_addr.sin_addr.s_addr = htons(INADDR_ANY); // INADDR_ANY表示自动获取本机地址
    client_addr.sin_port = htons(0); // auto allocated, 让系统自动分配一个空闲端口

    // 创建用于internet的流协议(TCP)类型socket，用client_socket代表客户端socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }

    // 把客户端的socket和客户端的socket地址结构绑定
    if (bind(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr)))
    {
        printf("Client Bind Port Failed!\n");
        exit(1);
    }

    // 设置一个socket地址结构server_addr,代表服务器的internet地址和端口
    struct sockaddr_in  server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    // 服务器的IP地址来自程序的参数
    if (inet_aton(argv[1], &server_addr.sin_addr) == 0)
    {
        printf("Server IP Address Error!\n");
        exit(1);
    }

    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr);

    // 向服务器发起连接请求，连接成功后client_socket代表客户端和服务器端的一个socket连接
    if (connect(client_socket, (struct sockaddr*)&server_addr, server_addr_length) < 0)
    {
        printf("Can Not Connect To %s!\n", argv[1]);
        exit(1);
    }


    //发送目录名称
    char dir_name[FILE_NAME_MAX_SIZE + 1];
    bzero(dir_name, sizeof(dir_name));
    printf("Please Input DIR Name On Server.\t");
    scanf("%s", dir_name);
    send(client_socket, dir_name,FILE_NAME_MAX_SIZE,0);

    //传输目录内的文件名
    translater_dir(dir_name, client_socket);
    sleep(1);
    //结束标志
    send(client_socket, "Finished",FILE_NAME_MAX_SIZE,0);
    //接受服务器的响应传输文件的buffer
    printf("start send file_buffer\n");
    while(1)
    {
      char buffer[BUFFER_SIZE];
      int length = recv(client_socket, buffer, BUFFER_SIZE, 0);
      if (length < 0)
      {
          printf("Server Recieve Data Failed!\n");
          pthread_exit(NULL);
      }
      printf("start send file_name : %s\n",buffer);
      FILE *fp = fopen(buffer, "r");
      if (fp == NULL)
      {
        printf("error\n" );
        break;
      }
      bzero(buffer, BUFFER_SIZE);
      int file_block_length = 0;
      int ret;
      while(1)
      {
        file_block_length = fread(buffer, sizeof(char), BUFFER_SIZE, fp);
        printf("file_block_length = %d\n", file_block_length);
          // 发送buffer中的字符串到new_server_socket,实际上就是发送给客户端
        if(file_block_length == 0)
        {
          bzero(buffer, sizeof(buffer));
          snprintf(buffer, FILE_NAME_MAX_SIZE, "%s", "finish");
          while ((ret = send(client_socket, buffer, file_block_length, 0)) > 0)
              printf("send finish %d\n",ret);
          break;
        }
        if (ret = (send(client_socket, buffer, file_block_length, 0)) < 0)
        {
          break;
        }
        bzero(buffer, sizeof(buffer));
      }
      fclose(fp);
      printf("send finish\n");
    }




    printf("Send Dir:\t %s From Server[%s] Finished!\n", dir_name, argv[1]);

    // 传输完毕，关闭socket
    close(client_socket);
    return 0;

}


void translater_dir(char *dir_name, int client_socket)
{
  DIR *dp = opendir(dir_name);
  struct ds_info file_info;

  if (dp == NULL)
  {
    printf("Open Dir failed\n");
    exit(1);
  }
  char src_pre_dir[FILE_NAME_MAX_SIZE];
  char src_cur_dir[FILE_NAME_MAX_SIZE];

  strcpy(src_pre_dir, dir_name);
  strcpy(src_cur_dir, dir_name);
  struct dirent *ptr;

  while ((ptr = readdir(dp)))
  {
   if(!strcmp(ptr->d_name,".") || !strcmp(ptr->d_name,".."))
        continue;

    strcat(src_cur_dir, "/");
    strcat(src_cur_dir, ptr->d_name);
    struct stat info;
    if(stat(src_cur_dir, &info) < 0)
    {
       printf("Get Stat Fail\n");
       continue;
    }
    if(S_ISDIR(info.st_mode))
    {
        printf("FILE ERROR!");
        continue;
    }
    else
    {
      file_info.file_name = src_cur_dir;
      file_info.client_socket = client_socket;
      pthread_t pid;
      pthread_create(&pid, NULL, send_file, (void *)&file_info);
      pthread_join(pid, NULL);
    }
    strcpy(src_cur_dir, src_pre_dir);
  }
}


void* send_file(void *info)
{
  pthread_mutex_lock(&mutex);
  char *file_name = ((struct ds_info *)info)->file_name;
  int client_socket = ((struct ds_info *)info)->client_socket;
  char buffer[BUFFER_SIZE];
  bzero(buffer, sizeof(buffer));
  strncpy(buffer, file_name, strlen(file_name) > BUFFER_SIZE ? BUFFER_SIZE : strlen(file_name));
  // 向服务器发送buffer中的数据，此时buffer中存放的是客户端需要接收的文件的名字
  send(client_socket, buffer,FILE_NAME_MAX_SIZE, 0);
  printf("File:\t%s Transfer Start\n", file_name);
  pthread_mutex_unlock(&mutex);
}
