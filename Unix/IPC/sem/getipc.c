#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    struct stat stats;
    if (argc != 2)
        perror("usage : ftok <pathname>");
    stat(argv[1], &stats);
    printf("st_dev : %lx, st_ino: %lx, key: %x", (u_long)stats.st_dev, 
           (u_long)stats.st_ino, ftok(argv[1], 0xff));
    exit(0);
}
