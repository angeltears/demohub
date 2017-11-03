#include "ls.h"

#define MAX_PATH 512
void dir_order(char *pathname)  
{  
    DIR *dfd;  
    char name[MAX_PATH];  
    struct dirent *dp;
    char c = '/';
    if ((dfd = opendir(pathname)) == NULL)  
    {  
        printf("dir_order: can't open %s\n %s", pathname,strerror(errno));  
        return;  
    }  
    while ((dp = readdir(dfd)) != NULL)  
    {  
        if (strncmp(dp->d_name, ".", 1) == 0)  
            continue; /* 跳过当前目录和上一层目录以及隐藏文件*/  
        if (strlen(pathname) + strlen(dp->d_name) + 2 > sizeof(name))  
        {  
            printf("dir_order: name %s %s too long\n", pathname, dp->d_name);  
        } else  
        {  
            memset(name, 0, sizeof(name));  
            sprintf(name, "%s%c%s", pathname, c, dp->d_name);  
            print_file_info(name);  
        }  
    }  
    closedir(dfd);  
  
}  
void print_file_info(char *pathname)  
{  
    struct stat filestat; 
    if (stat(pathname, &filestat) == -1)
    {
        printf("cannot open file %s\n", pathname);
        return;
    }
    print_file(pathname);
    if ((filestat.st_mode & S_IFMT) == S_IFDIR)  
    {  
       dir_order(pathname);  
    }
    
}  


void print_file(char *pathname)
{
    char *src_pathname = (char *)malloc(strlen(pathname) + 1);
    int temp = 0;
    int flag = 0;
    char *des_pathname = (char *)malloc(strlen(pathname) + 1);    
    strcpy(src_pathname, pathname);
    src_pathname[strlen(pathname) + 1] = '\0';
    while (*src_pathname != '\0')
    {
        src_pathname ++;
    }

    while (strcmp(src_pathname,pathname) != 0)
    {
        if(*src_pathname == '/')
        {
            temp++;
        }
        if (temp == 1 && flag == 0)
        {
            flag = 1;
            strcpy(des_pathname, src_pathname + 1);
            des_pathname[strlen(src_pathname)] = '\0';
        }
        src_pathname--;
    }
    
    while(temp != 1)
    {
        temp --;
        printf("——");
    }
    printf("%s\n", des_pathname);
}


