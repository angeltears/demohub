#include "sem.h"
int main(int argc, char *argv[])
{
    int semid, nsems, i;
    struct semid_ds seminfo;
    unsigned short *ptr;
    union semun arg;

    semid = Semget(Ftok(argv[1], 0xff), 1, CREAT_MODE);
    arg.buf = &seminfo;

    semctl(semid, 0, IPC_STAT, arg);
    nsems = arg.buf->sem_nsems;

    ptr = calloc(nsems, sizeof(unsigned short));
    arg.array = ptr;

    semctl(semid, 0, GETALL,arg);
    for(i = 0; i < nsems; i++)
        printf("semval[%d] = %d",i,ptr[i]);
    exit(0);
}
