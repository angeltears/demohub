#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        printf("usage : prpeconf <pathname>");
    printf("PIPE_BUFF = %ld, OPEN_MAX = %ld\n",pathconf(argv[1], _PC_PIPE_BUF),sysconf(_SC_OPEN_MAX));
}
