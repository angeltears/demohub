#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    pid_t pid_1_child;
    pid_t pid_2_child;
    pid_t pid_child_child;
    pid_t pid;
    int stat;
    pid_1_child = fork();
    if (pid_1_child == 0)
    {
        printf ("pid_1_child : %d \n", getpid());
        sleep(2);
        pid_child_child = fork();
        if (pid_child_child> 0)
        {
           printf ("pid_child_child : %d \n", pid_child_child);
        }
        else
        {
            exit(0);
        }       
        exit(0);
    }
    else 
    {
        printf ("pid_parent : %d\n" ,getpid());
        pid_2_child = fork();
        if (pid_2_child > 0)
        {
            printf ("2 is runing\n");
        }
        else
        {
            sleep(2);
            printf("pid_2_child : %d \n", getpid());
            printf("My parent : %d \n", getppid());
            exit(0);
       }
    }
        pid = wait(&stat);
        printf("wait for pid : %d stat: %d \n",pid, stat);
        exit(0);
} 
