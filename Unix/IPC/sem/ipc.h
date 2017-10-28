#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/sem.h>

union semun
{
  int var;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *_buf;
};

//ftok的包裹
key_t Ftok(char *pathname, int proj_id);


//semget
int Semget(key_t key, int nsems, int semflg);
