#include "my_pthread.h"


void cleanup(void *arg)
{
    printf("cleanup : %s\n", (char *)arg);
}


void *fun1(void *arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler\n");
    pthread_cleanup_push(cleanup, "thread 1 second handler\n");
    printf("thread 1 push complete\n");
    if (arg)
    {
        return ((void *)1);
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void *)1);
}

void *fun2(void *arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler\n");
    pthread_cleanup_push(cleanup, "thread 2 second handler\n");
    printf("thread 1 push complete\n");
    if (arg)
    {
        pthread_exit((void *)2);
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void *)2);
}


int main(void)
{
  int err;
  pthread_t tid1, tid2;
  void *tret;

  Pthread_create(&tid1, NULL, fun1, (void *)1);
  Pthread_create(&tid2, NULL, fun2, (void *)2);

  pthread_join(tid1, &tret);
  printf("thread 1 return %d\n", (int)tret);
  pthread_join(tid2, &tret);
  printf("thread 1 return %d\n", (int)tret);
}
