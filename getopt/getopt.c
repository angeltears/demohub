#include <stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int rec = 0;
    char *b_opt_arg;   //选项参数字符串
    char ec;

    while((rec = getopt(argc, argv,":ngl:"))!=-1)
    {
        switch(rec)
        {
            case 'n':
                printf("My name is Yj\n");
                break;
            case'g':
                printf("Her name is tan90\n");
                break;
            case'l':
                b_opt_arg = optarg;
                printf("Our love is %s\n",optarg);
                break;
            case'?':
                ec = (char)optopt;
                printf("无效的选项字符\'%c\'!\n",ec);
                break;
            case':':
                printf("缺少选项参数！\n");
                break;
        }
    }
}
