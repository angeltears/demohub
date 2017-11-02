#include "shm.h"
#define SEM_NAME "mysem"


int main(int argc, char* argv[])
{
    int i, nloop;
    sem_t *mutex;
    int *ptr;
    int fd;
    nloop = atoi(argv[1]);
    fd = open("/dev/zero", O_RDWR);
    ptr = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANON, fd, 0);

    mutex = sem_open(Px_ipc_name(SEM_NAME), O_CREAT|O_EXCL, 0755, 1);
    sem_unlink(Px_ipc_name(SEM_NAME));

    setbuf(stdout, NULL);

    if (fork() == 0)
    {
        for (i = 0; i < nloop; i++)
        {
            sem_wait(mutex);
            printf("child %d\n", (*ptr)++);
            sem_post(mutex);
        }
        exit(0);
    }

    for (i = 0; i < nloop; i++)
    {
        sem_wait(mutex);
        printf("parent %d\n ", (*ptr)++);
        sem_post(mutex);
    }
    exit(0);
}
