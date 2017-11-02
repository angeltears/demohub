#include "shm.h"

struct shared
{
    sem_t mutex;
    int count;
}shared;

int main(int argc, char* argv[])
{
    int fd;
    int i, nloop;
    struct shared *ptr;

    nloop = atoi(argv[2]);
    fd = open(argv[1], O_CREAT|O_RDWR, 0755);
    write(fd, &shared, sizeof(struct shared));

    ptr = mmap(NULL, sizeof(struct shared), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    Close(fd);
    
    sem_init(&ptr->mutex, 1, 1);

    setbuf(stdout, NULL);

    if (fork() == 0)
    {
        for (i = 0; i < nloop; i++)
        {
            sem_wait(&ptr->mutex);
            printf("child %d\n", ptr->count++);
            sem_post(&ptr->mutex);
        }
        exit(0);
    }

    for (i = 0; i < nloop; i++)
    {
        sem_wait(&ptr->mutex);
        printf("parent %d\n ", ptr->count++);
        sem_post(&ptr->mutex);
    }
    exit(0);
}
