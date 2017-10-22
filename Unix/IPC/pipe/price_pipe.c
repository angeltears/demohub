#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
////////////////////////////////////////////////////////////////////////////////////
//很遗憾　ubuntu 并不支持双工管道　这个程序　失败。

int main()
{
    int fd[2];
    int n;
    pid_t pid;
    char c;
    
    if ((n = pipe(fd)) == -1)
        perror("pipe fail:");
    if ((n == fork()) == 0)
    {
        sleep(3);
        if ((n == read(fd[0], &c, 1)) != 1)
            printf("child: read %d\n", n);
        printf("child read %c\n",c);
        write(fd[0], "c", 1);
        exit(0);
    }
    else
    {
        write(fd[1], "p", 1);
        if ((n = read(fd[1], &c, 1)) != 1)
            printf("parent read %d\n",n);
        printf("parent read %c\n", c);
        waitpid(pid, NULL, 0);
        exit(0);
    }
}
