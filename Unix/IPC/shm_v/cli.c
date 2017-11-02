#include "shm.h"

int main(int argc, char *argv[])
{
    key_t key = Ftok(argv[1], atoi(argv[2]));

    int shm_id = Shmget(key, 0, 0);
    char *addr = shmat(shm_id, NULL, 0);

    int sem_id = Semget(key, 0, 0);
    union semun init;
    init.val = 0;

    semctl(sem_id, 0, SETVAL, &init);
    semctl(sem_id, 1, SETVAL, &init);

    struct sembuf p;
    struct sembuf v;
    p.sem_num = 1;
    p.sem_op = -1;
    p.sem_flg = 0;
    v.sem_num = 0;
    v.sem_op = 1;
    v.sem_flg = 0;

    while (1)
    {
        semop(sem_id, &p, 1);
        printf("ser>%s\n", addr);
        
        printf("cli>");
        scanf("%s", addr);
        semop(sem_id, &v, 1);
    }

    exit(0);
    
}
