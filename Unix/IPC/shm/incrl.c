#include "shm.h"
#include <semaphore.h>
#define SEM_NAME "mysem"

int count = 0;

int main(int argc, char* argv[])
{
    int i, nloop;
    sem_t *mutex;

    nloop = atoi(argv[1]);

    mutex = sem_open(Px_ipc_name(SEM_NAME), CREAT_MODE, 1);
    sem_unlink(Px_ipc_name(SEM_NAME));

    setbuf(stdout, NULL);

    if (fork() == 0)
    {
        for (i = 0; i < nloop; i++)
        {
            sem_wait(mutex);
            printf("child %d\n", count++);
            sem_post(mutex);
        }
        exit(0);
    }

    for (i = 0; i < nloop; i++)
    {
        sem_wait(mutex);
        printf("parent %d\n ", count++);
        sem_post(mutex);
    }
    exit(0);
}
