#include "my_pthread.h"

void *fun1(void *arg)
{
    printf("thread 1 return\n");
    return ((void *)1);
}

void *fun2(void *arg)
{
    printf("thread 2 return\n");
    pthread_exit((void *)2);
}


int main()
{
    pthread_t tid[2];
    void *pret;
    int err;
    pthread_create(&tid[1], NULL, fun1, NULL);
    pthread_create(&tid[0], NULL, fun2, NULL);
    
    err = pthread_join(tid[1], &pret);
    printf("thread 1 returns %d",*(int*)pret);

    err = pthread_join(tid[0], &pret);
    printf("thread 2 returns %d",*(int*)pret); 

}
