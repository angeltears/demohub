/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-11-9.
* @package : dataCompression
*/
#include "compress.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <malloc.h>
using namespace std;
int main()
{
    int fd = open("rise", O_RDONLY);
    unsigned long filesize = -1;
    struct stat statbuff;
    if (stat("rise", &statbuff) < 0)
    {
        return -1;
    }
    else
    {
        filesize = statbuff.st_size;
    }
    unsigned char *buff = new unsigned char[filesize];
    int rdsize = 0;
    int temp = filesize;
    while(temp  > 0)
    {
        rdsize = read(fd, buff, temp);
        temp  = temp  - rdsize;
    }
    unsigned  char*outbuf = NULL;
    int length = lz77_compress(buff, &outbuf, filesize);
    int fd1 = open("rise_cmpression", O_WRONLY|O_CREAT, 0755);
    temp = length;
    rdsize = 0;
    while(temp > 0)
    {
        rdsize  = write(fd1, outbuf, temp);
        temp = temp -rdsize;
    }
    delete buff;
    unsigned char *rebuff = NULL;
    length = lz77_uncompress(outbuf, &rebuff);
    int fd2 = open("rise_uncmpression.txt", O_WRONLY|O_CREAT, 0755);
    temp = length;
    rdsize = 0;
    while(temp > 0)
    {
        rdsize  = write(fd2, rebuff, temp);
        temp = temp -rdsize;
    }
    free(outbuf);
}
