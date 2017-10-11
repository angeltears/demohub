#include"log.h"

int main()
{
    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL)
    {
        sys_log(LOG_ERR,__FILE__,__LINE__,"%m");
        return -1;
    }
    fclose(fp);
    return 0;
}
