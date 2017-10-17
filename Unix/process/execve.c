#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char *argv[], char **environ)
{
    pid_t pid;
    int stat_val;

    pid = fork();
    if (pid == 0)
    {
        printf("child process is running\n");
        printf("Pid = %d, PPid = %d\n", getpid(),getppid());
        printf("Uid = %d, Gid = %d\n", getuid(), getgid());
        execve("processimage", argv, environ);
        printf("tan90");
        exit(0);
    }
    else 
    {
        printf("parent process is running\n");
    }

    wait(&stat_val);
    printf("exit: %d", stat_val);
    exit(0);
}
