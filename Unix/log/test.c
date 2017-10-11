#include<stdio.h>
#include<unistd.h>
#include<syslog.h>
#include<errno.h>

int main()
{
    FILE *fp = fopen("test.txt","r");
    if (fp == NULL)
    {
        openlog("Mytestlog", LOG_PID|LOG_CONS, LOG_USER);
        syslog(LOG_INFO, "%m\n");
        closelog();
        return -1;
    }
    fclose(fp);
    return 0;
}
/*
int main()
{
    FILE *fp = fopen("test.txt","r");
    if (fp == NULL)
    {
        syslog(LOG_INFO, "%m\n");
        return -1;
    }
    fclose(fp);
    return 0;
}
*/
