#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define COUNT 10
static int i = 1;

void *A_fun(void *arg)
{
    while(i <= COUNT)
    {
        pthread_mutex_lock();
        if (i % 2 != 0)
        {
            printf("A:%d\n", i);
            i++;
            pthread_cond_wait(&uneven);
        }
        else 
        {
            pthread_cond_wait(&even);
        }
        pthread_mutex_unlock();
    }
}


void *B_fun(void *arg)
{
    while(i <= COUTN)
    {
        pthread_mutex_lock();
        if(i % 2 == 0)
        {
            printf("B:%d\n",i);
            i++;
            pthread_cond_signal();
        }
        else
        {
            pthread_cond_wait()
        }
        pthread_mutex_unlock();
    }
}


int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1,NULL,A_fun,NULL);
    sleep(1);
    pthread_create(&tid2,NULL,B_fun,NULL);
    
    pthread
}
