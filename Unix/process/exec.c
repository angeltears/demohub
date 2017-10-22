#include <stdio.h>
#include <apue.h>
#include <sys/wait.h>

char *env_init[] ={"UEAR=unknown", "PATH=/tmp", NULL};

int main()
{
    pid_t pid;
    if (pid = fork() < 0 )
        err_sys("fork error");
    else if (pid == 0)
    {
        if (execle("/bin/echoall", "echoall", "myargl", "MY ARG2", (char *)0, env_init) < 0);
            err_sys("execle error");
    }
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");
    else if (pid == 0)
    {
        if(execlp("echonall", "echonall", "only 1 arg", (char *)0) < 0)
            err_sys("execlp error");
    }
    return 0;
}
