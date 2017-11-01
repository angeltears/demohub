#include "sem.h"

int  main(int argc, char *argv[])
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
    for (i = 0; i < nsems; i++)
    {
        ptr[i] = atoi(argv[i+2]);
    }
    semctl(semid, 0, SETALL, arg);
    exit(0);
    return 0;
}
