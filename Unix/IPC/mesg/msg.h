#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE 256
#define SER_SND 100
#define CLI_SND 200
#define SER_REC 200
#define CLI_REC 100

struct mesg
{
  long mesg_tpye;
  char mesg_date[BUF_SIZE];
};

key_t Ftok(const char *pathname, int proj_id)
{
  key_t key = ftok(pathname, proj_id);
  if (key == -1)
  {
    perror("ftok,");
    exit(1);
  }
  return key;
}


int Msgget(key_t key, int msgflg)
{
  int id = msgget(key, msgflg);
  if (id == -1)
  {
    perror("msgget, ");
    exit(1);
  }
  return id;
}

int Msgsnd(int msqid, const void *ptr, size_t length, int flag)
{
  int ret = msgsnd(msqid, ptr, length, flag);
  if (ret == -1)
  {
    perror("msgsnd, ");
    exit(1);
  }
  return ret;
}

ssize_t Msgrcv(int msqid, void *ptr, size_t length, long type, int flag)
{
  ssize_t ret = msgrcv(msqid, ptr, length, type, flag);
  if (ret == -1)
  {
    perror("msgrcv, ");
    exit(0);
  }
  return ret;
}
