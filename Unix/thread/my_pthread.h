#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


int Pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg)
{
    int err = pthread_create(tidp, attr, start_rtn, arg);
    if (err != 0)
    {
        perror("creat_pthread:");
        exit(0);
    }
}
