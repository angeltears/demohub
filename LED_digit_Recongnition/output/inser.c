////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#define HELLO_WORLD_SERVER_PORT    6666
#define LENGTH_OF_LISTEN_QUEUE     20
#define BUFFER_SIZE                1024
#define FILE_NAME_MAX_SIZE         512


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct file_name
{
  char buffer[FILE_NAME_MAX_SIZE];
  struct file_name *next;
};

void *translater(void *arg);
void *translater(void *arg)
{
  int new_server_socket = *(int *)arg;
  if (new_server_socket < 0)
  {
      printf("Server Accept Failed!\n");
      pthread_exit(NULL);
  }

  char dir_name[BUFFER_SIZE];
  bzero(dir_name, sizeof(dir_name));
  int length = recv(new_server_socket, dir_name, BUFFER_SIZE, 0);
  if (length < 0)
  {
      printf("Server Recieve Dir Failed!\n");
      pthread_exit(NULL);
  }
  char file_dir_name[BUFFER_SIZE];
  bzero(file_dir_name, sizeof(file_dir_name));
  snprintf(file_dir_name, FILE_NAME_MAX_SIZE, "%s%s/", "photo/",dir_name);
  int ret = mkdir(file_dir_name, 0755);
  if (ret == -1)
  {
    printf("Server Mkdir Failed\n");
    pthread_exit(NULL);
  }
  //传输文件名字

  char buffer[BUFFER_SIZE];
  struct file_name names;
  struct file_name *ptr;
  ptr = &names;
  while((length = recv(new_server_socket, buffer, BUFFER_SIZE, 0)) > 0)
  {
    pthread_mutex_lock(&mutex);
    printf("buffer %s\n", buffer );
    char file_name[FILE_NAME_MAX_SIZE + 1];
    bzero(file_name, sizeof(file_name));

    snprintf(file_name, FILE_NAME_MAX_SIZE, "%s%s", "photo/", buffer);
    if((ret = strcmp(buffer,"Finished")) == 0)
    {
      bzero(buffer, BUFFER_SIZE);
      pthread_mutex_unlock(&mutex);
      break;
    }
    strcpy(ptr->buffer, buffer);
    ptr->next = (struct file_name *)malloc(sizeof(struct file_name));
    ptr= ptr->next;
    int ret = creat(file_name, 0777);
    if (ret == -1)
    {
      printf("Server Create %s Failed\n",file_name);
    }
    bzero(buffer, sizeof(buffer));
    pthread_mutex_unlock(&mutex);
  }
  printf("names translater success\n");
  ptr->next = NULL;


  //发送文件名，接受文件。

  ptr = &names;
  while(ptr->next != NULL)
  {
    send(new_server_socket, ptr->buffer, BUFFER_SIZE, 0);
    printf("start recv %s\n", ptr->buffer);
    char buffer[BUFFER_SIZE];
    bzero(buffer, sizeof(buffer));
    char file_name[FILE_NAME_MAX_SIZE + 1];
    snprintf(file_name, FILE_NAME_MAX_SIZE, "%s%s", "photo/", ptr->buffer);
    // 发送数据到服务器
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL)
    {
        printf("File:\t%s Not Found!\n", file_name);
    }
    else
    {
      while(1)
      {
        length = recv(new_server_socket, buffer, BUFFER_SIZE, 0);
        printf("recv a buffer length : %d\n", length);
        if(length < 0)
        {
            printf("Recieve Data From Server %s Failed!\n", file_name);
            break;
        }
        int write_length = fwrite(buffer, sizeof(char), length, fp);
        printf("write_length :%d\n", write_length);
        if (write_length < length)
        {
            printf("File:\t%s Write Failed!\n", file_name);
            break;
        }
        bzero(buffer, BUFFER_SIZE);
        }
      }
      printf("recv %s success\n", ptr->buffer);
      ptr = ptr->next;
    }
  close(new_server_socket);
  int pid = vfork();
  //python 程序的进口
  if (pid == 0)
  {

//      execle("cli", "cli", "192.168.1.131", NULL, NULL);
  }
  else if (pid > 0)
  {
     waitpid(pid, NULL, 0);
  }

  pthread_exit(NULL);
}




int main(int argc, char **argv)
{
    // set socket's address information
    // 设置一个socket地址结构server_addr,代表服务器internet的地址和端口
    struct sockaddr_in   server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

    // create a stream socket
    // 创建用于internet的流协议(TCP)socket，用server_socket代表服务器向客户端提供服务的接口
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }

    // 把socket和socket地址结构绑定
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
        printf("Server Bind Port: %d Failed!\n", HELLO_WORLD_SERVER_PORT);
        exit(1);
    }

    // server_socket用于监听
    if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
    {
        printf("Server Listen Failed!\n");
        exit(1);
    }

    // 服务器端一直运行用以持续为客户端提供服务
    while(1)
    {
        // 定义客户端的socket地址结构client_addr，当收到来自客户端的请求后，调用accept
        // 接受此请求，同时将client端的地址和端口等信息写入client_addr中
        struct sockaddr_in client_addr;
        socklen_t          length = sizeof(client_addr);
        pthread_t pid;
        // 接受一个从client端到达server端的连接请求,将客户端的信息保存在client_addr中
        // 如果没有连接请求，则一直等待直到有连接请求为止，这是accept函数的特性，可以
        // 用select()来实现超时检测
        // accpet返回一个新的socket,这个socket用来与此次连接到server的client进行通信
        // 这里的new_server_socket代表了这个通信通道
        int new_server_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);

        pthread_create(&pid, NULL, translater, (void *)&new_server_socket);
    }

    close(server_socket);

    return 0;
  }
