#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/sem.h>

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *_buf;
};

//ftok的包裹
key_t Ftok(char *pathname, int proj_id)
{
  key_t key = ftok(pathname, proj_id);
  if (key == -1)
  {
    perror("ftok, ");
    exit(0);
  }
  return key;
}
 //semget
int Semget(key_t key, int nsems, int semflg)
 {
   int ret = semget(key, nsems, semflg);
   if (ret == -1)
   {
     perror("semget, ");
     exit(0);
   }
   return ret;
 }
