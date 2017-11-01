#include "sem.h"
#define LOCK_PATH "mesem"
#define MAX_TRIES 10

int semid, initflag = 0;
struct sembuf postop, waitop;

void my_lock(int fd)
{
    int oflag, i;
    union semun arg;
    struct semid_ds info;

    if (initflag == 0)
    {
        oflag = CREAT_MODE;
        if ((semid = semget(Ftok(LOCK_PATH, 0), 1, oflag)) >= 0)
        {
            arg.val = 1;
            semctl(semid, 0, SETVAL, arg);
        }
        else if (errno == EEXIST)
        {
            semid = semget(Ftok(LOCK_PATH, 0), 1, 0755);
            arg.buf = &info;
            for (i = 0; i < MAX_TRIES; i++)
            {
                if (arg.buf->sem_otime !=0)
                    goto init;
                sleep(1);
            }
            perror("semget ok,but semaphore:");
        }
        else 
            perror("semget:");
init:
        initflag = 1;
        postop.sem_num = 0;
        postop.sem_op = 1;
        postop.sem_flg = SEM_UNDO;
        waitop.sem_num = 0;
        waitop.sem_op = -1;
        waitop.sem_flg = SEM_UNDO;
    }
    semop(semid, &waitop, 1);
}

void my_unlock(int fd)
{
    semop(semid, &postop, 1);
}

int main()
{
    my_lock(0);
    semctl(semid, 0,IPC_RMID);
}
