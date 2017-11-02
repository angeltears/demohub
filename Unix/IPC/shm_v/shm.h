#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/shm.h>
#define CREAT_MODE  IPC_CREAT|IPC_EXCL|0755
#define PATH_MAX 256

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *_buf;
};
key_t Ftok(char *pathname, int pojet_id)
{
    key_t ret = ftok(pathname, pojet_id);
    if (ret == -1)
    {
        perror("ftok, ");
        exit(1);
    }
    return ret;
}

int Semget(key_t key, int nsems, int oflg)
{
    int ret = semget(key, nsems, oflg);
    if (ret == -1)
    {
        perror("semget, ");
        exit(0);
    }
    return ret;
}


int Semop(int semid, struct sembuf *opsptr, size_t size)
{
    int ret = semop(semid, opsptr, size);
    if (ret == -1)
    {
        perror("semget, ");
        exit(0);
    }
    return ret;
}

int Munmap(void *addr, size_t len)
{
    int ret = munmap(addr, len);
    if (ret == -1)
    {
        perror("munmap :");
        exit(1);
    }
    return ret;
}

int Msync(void *addr, size_t len,int flag)
{
    int ret = msync(addr, len, flag);
    if (ret == -1)
    {
        perror("msync:");
        exit(1);
    }
    return ret;
}

int Close(int fd)
{
    int ret = close(fd);
    if (ret == -1)
    {
        perror("close:");
        exit(0);
    }
    return ret;
}

int Shmget(key_t key, size_t size, int oflag)
{
    int ret = shmget(key, size, oflag);
    if (ret == -1)
    {
        perror("shmget:");
        exit(0);
    }
    return ret;
}

int Shmdt(const void *shmaddr)
{
    int ret = shmdt(shmaddr);
    if (ret == -1)
    {
        perror("shmdt:");
        exit(0);
    }
    return ret;
}

int Shmctl(int shmid, int cmd, struct shmid_ds *buff)
{
    int ret = shmctl(shmid, cmd, buff);
    if (ret == -1)
    {
        perror("shmctl:");
        exit(0);
    }
    return ret;
}

char *px_ipc_name(const char *name)
{
        char    *dir, *dst, *slash;
        //分配的空间在哪里释放的哦！@deprecated 
        if ( (dst = malloc(PATH_MAX)) == NULL)
                return(NULL);

                /* 4can override default directory with environment variable */
        if ( (dir = getenv("PX_IPC_NAME")) == NULL) {
#ifdef  POSIX_IPC_PREFIX
                dir = POSIX_IPC_PREFIX;         /* from "config.h" */
#else
                dir = "/tmp";                           /* default */
#endif
        }
                /* 4dir must end in a slash */
        slash = (dir[strlen(dir) - 1] == '/') ? "" : "/";
        snprintf(dst, PATH_MAX, "%s%s%s", dir, slash, name);

        return(dst);                    /* caller can free() this pointer */
}
/* end px_ipc_name */

char *Px_ipc_name(const char *name)
{
        char    *ptr;
        // gcc -posix -E -dM - </dev/null >
#ifdef linux
        ptr = (char *)name;
#else
        if ( (ptr = px_ipc_name(name)) == NULL)
                err_sys("px_ipc_name error for %s", name);
#endif
        return(ptr);
}

