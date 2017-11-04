#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *fun(void *arg)
{
    printf("my id is %o",pthread_self());

}

int main()
{
    pthread_t tid;
    int err;
    
    err = pthread_create(&tid, NULL, fun, NULL);
    if (err != 0)
    {
        perror("creat pthread:");
    }
    sleep(1);
    exit(0);
}
