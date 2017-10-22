#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 512
int main()
{
    size_t n;
    char buff[MAXLINE], command[MAXLINE];
    FILE *fp;

    fgets(buff, MAXLINE, stdin);
    n = strlen(buff);
    if (buff[n-1] == '\n')
        n--;

    snprintf(command, MAXLINE, "%s", buff);
    fp = popen(command,"r");

    while(fgets(buff, MAXLINE, fp) != NULL)
        fputs(buff, stdout);
    
    pclose(fp);
    exit(0);

}
