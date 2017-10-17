#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>


int init_daemon(void);

int init_deamon(void)
{
    pid_t pid;
    int i;

    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);

    pid = fork();
    if (pid > 0)
    {
        _exit(0);
    }
    else if (pid < 0)
    {
        return 0;
    }

    setsid();

    pid = fork();
    if (pid > 0)
    {
        _exit(0);
    }
    else if (pid < 0)
    {
        return 0;
    }

    for (i = 0; i < NOFILE;close(i++));

    chdir("/");

    umask(0);

    signal(SIGCHLD, SIG_IGN);

    return 0;
}

int main()
{
    time_t now_time;
    init_deamon();

    syslog(LOG_USER|LOG_INFO, "Test for deamon\n");
    while (1)
    {
        sleep(60);
        time(&now_time);
        syslog(LOG_USER|LOG_INFO, "系统时间：　\t%s\t\t\n",ctime(&now_time));
    }
}

