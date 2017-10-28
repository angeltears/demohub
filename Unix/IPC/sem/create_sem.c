#include "ipc.h"
int main(int argc, char* argv[])
{
  if (argc != 4)
  {

  }
  key_t sem_key = Ftok(argv[1], atol(argv[2]));
  printf("sem_key == %x\n", sem_key);

  int sem_id = Semget(sem_key, 1, IPC_CREAT|IPC_EXCL|0755);
  printf("sem_id = %d\n",sem_id);

}
