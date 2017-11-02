#include "shm.h"
#define SEM_NAME "mysem"


int main(int argc, char* argv[])
{
    int fd;
    int i, nloop;
    int zero = 0;
    sem_t *mutex;
    int *ptr;

    nloop = atoi(argv[2]);
    fd = open(argv[1], O_CREAT|O_RDWR, 0755);
    write(fd, &zero, sizeof(int));

    ptr = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    Close(fd);
    
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
