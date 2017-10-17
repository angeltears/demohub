#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[], char **enriron)
{
    int i;
    printf("My pid : %d, My parent pid : %d\n ", getpid(), getppid());
    printf("uid = %d, gid = %d\n",getuid(), getgid());

    for (i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}

