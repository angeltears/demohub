#ifndef _MY_PTHREAD_RWLOCK_H
#define _MY_PTHREAD_RWLOCK_H

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>


#ifdef WR_LOCK
#else
#define RD_LOCK
#endif
typedef struct
{
    pthread_mutex_t rw_mutex;
    pthread_cond_t rw_condreaders;
    pthread_cond_t rw_condwriters;
    int rw_magic;
    int rw_nwaitreaders;
    int rw_nwaitwriters;
    int rw_refcount;       //-1 0  5>0
}my_pthread_rwlock_t;

#define RW_MAGIC 0x20171104

#define MY_PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER,\
                                    PTHREAD_COND_INITIALIZER,\
                                    PTHREAD_COND_INITIALIZER,\
                                    RW_MAGIC,0,0,0}
typedef int my_pthread_rwlockattr_t;
///////////////////////////////////////////////////////////////////////////////////
int my_pthread_rwlock_init(my_pthread_rwlock_t *rw, my_pthread_rwlockattr_t *attr);
int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_destroy(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *rw);
int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *rw);
void clean_up(void *arg);
//////////////////////////////////////////////////////////////////////////////////
void clean_up(void *arg)
{
    my_pthread_rwlock_t *rw = (my_pthread_rwlock_t*)arg;
    rw->rw_nwaitreaders--;
    pthread_mutex_unlock(&rw->rw_mutex);
}




int my_pthread_rwlock_init(my_pthread_rwlock_t *rw, my_pthread_rwlockattr_t *attr)
{
    int result;
    if (attr != NULL)
        return EINVAL;
    if ((result = pthread_mutex_init(&rw->rw_mutex, NULL)) != 0)
    {
        return result;
    }
    if ((result = pthread_cond_init(&rw->rw_condreaders,NULL)) != 0)
    {
        pthread_mutex_destroy(&rw->rw_mutex);
        return result;
    }
    if ((result = pthread_cond_init(&rw->rw_condwriters,NULL)) != 0)
    {
        pthread_cond_destroy(&rw->rw_condreaders);
        pthread_mutex_destroy(&rw->rw_mutex);
        return result;
    }
    rw->rw_nwaitreaders = 0;
    rw->rw_nwaitwriters = 0;
    rw->rw_refcount = 0;
    rw->rw_magic = RW_MAGIC;
}



int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;
#ifdef RD_LOCK
    while(rw->rw_refcount<0)
    {
        rw->rw_nwaitreaders++;
        pthread_cleanup_push(clean_up, rw);
        result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
        pthread_cleanup_pop(0);
        rw->rw_nwaitreaders--;
        if(result != 0)
            break;
    }
    if(result == 0)
        rw->rw_refcount++;
#endif
#ifdef WR_LOCK
    while (rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0)
    {
        rw->rw_nwaitreaders++;
        pthread_cleanup_push(clean_up, rw);
        result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
        pthread_cleanup_pop(0);
        rw->rw_nwaitreaders--;
        if (result != 0)
            break;
    }
    if (result == 0)
        rw->rw_refcount++;
#endif
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}



int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;
#ifdef RD_LOCK
    while(rw->rw_refcount != 0 || rw->rw_nwaitreaders != 0)
    {
        rw->rw_nwaitwriters++;
        pthread_cleanup_push(clean_up, rw);
        result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
        pthread_cleanup_pop(0);
        rw->rw_nwaitwriters--;
        if(result != 0)
            break;
    }
    if(result == 0)
        rw->rw_refcount = -1;
#endif
#ifdef WR_LOCK
    while(rw->rw_refcount != 0)
    {
        rw->rw_nwaitwriters++;
        pthread_cleanup_push(clean_up, rw);
        result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
        pthread_cleanup_pop(0);
        rw->rw_nwaitreaders--;
        if(result != 0)
            break;
    }
    if (result == 0)
        rw->rw_refcount = -1;
#endif
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}



  int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;

    if(rw->rw_refcount > 0)
        rw->rw_refcount--;
    else if(rw->rw_refcount == -1)
        rw->rw_refcount = 0;
    else
        printf("unlock rwlock error: rw_refcount = %d\n",rw->rw_refcount);
#ifdef RD_LOCK
    if (rw->rw_nwaitreaders > 0)
    {
        result = pthread_cond_broadcast(&rw->rw_condreaders);
    }
    else if (rw->rw_nwaitwriters > 0)
    {
        if (rw->rw_refcount == 0)
        {
            result = pthread_cond_signal(&rw->rw_condwriters);
        }
    }
#endif
#ifdef  WR_LOCK
    if(rw->rw_nwaitwriters > 0)
    {
        if(rw->rw_refcount == 0)
        {
            result = pthread_cond_signal(&rw->rw_condwriters);
        }
    }
    else if(rw->rw_nwaitreaders > 0)
    {
        result = pthread_cond_broadcast(&rw->rw_condreaders);
    }
#endif
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}



int my_pthread_rwlock_destroy(my_pthread_rwlock_t *rw)
{
    if (rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if (rw->rw_refcount != 0 || rw->rw_nwaitreaders != 0|| rw->rw_nwaitwriters != 0)
        return EBUSY;
    pthread_mutex_destroy(&rw->rw_mutex);
    pthread_cond_destroy(&rw->rw_condreaders);
    pthread_cond_destroy(&rw->rw_condwriters);
    rw->rw_magic = 0;
    return 0;
}



int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *rw)
{
    int result;

    if (rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if ((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;

    if (rw->rw_refcount != 0 || rw->rw_nwaitreaders > 0)
    {
        return EBUSY;
    }
    else
    {
        rw->rw_refcount = -1;
    }
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}




int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *rw)
{
    int result;

    if (rw->rw_magic != RW_MAGIC)
        return EINVAL;
    if ((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;

    if (rw->rw_refcount < 0 )
    {
        return EBUSY;
    }
    else
    {
        rw->rw_refcount++;
    }
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}
#endif // _MY_PTHREAD_RWLOCK_H
