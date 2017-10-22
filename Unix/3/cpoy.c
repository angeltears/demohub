#include<apue.h>
#include<string.h>
#include<fcntl.h>
int main(int argc, char argv[])
{
    int rec = 0;
    char *b_opt_arg;
    char ec;
    int numd;
    int nums;
    char buf[50];
    int num;

    while ((rec = getopt(argc, argv,"d:s:")) != -1)
    {
        switch(rec)
        {
        case 'd':
             b_opt_arg = optarg;
             numd = open(b_opt_arg, O_WRONLY | O_CREAT | O_EXCL,0755);
             if (numd == -1)
                 err_sys("creat fail!");
             break;
        case 's':
            b_opt_arg = optarg;
            nums = open(b_opt_arg, 0);
            if (nums == -1)
                err_sys("fail open src_file!");
             break;
        defult:
             break;
        }
    }



    while((num = read(nums, buf, 50)) > 0)
    {
        if(num != write(numd, buf, strlen(buf)))
            err_sys("write error");
    }
    if(num < 0)
        err_sys("read error");

    return 0;
}
