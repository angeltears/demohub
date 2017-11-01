#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#define CREAT_MODE  IPC_CREAT|IPC_EXCL|0755


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



