#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static int globVat = 0;
int main()
{
    pid_t pid;
    int var = 1, i;
    
    //pid = fork();
     pid = vfork();
    switch (pid) 
    {
    case 0:
        i = 3;
        while(i-- > 0)
        {
            printf("Child process is running \n");
            var ++;
            globVat++;
            sleep(1);
        }
        printf("Child's globe : %d , var : %d\n", globVat, var);
        break;
    default:
        i = 5;
        int j = 0;
        while (i-- > 0)
         {
            j++;
            printf("Parent process is running \n");
            var ++;
            globVat++;
            sleep(1);
        }
        printf("Parent's globe : %d , var : %d, J: %d\n", globVat, var, j);
        _exit(0);
    }
} 
