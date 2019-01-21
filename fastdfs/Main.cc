/**
* Copyright: Copyright (c) 2019 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 19-1-21.
* @package : fastdfs_demo
*/

#include <stdio.h>
#include "fdfs_api.h"


int main(int argc, char* argv[])
{
    char fileid[1024] = {0};
    fdfs_upload_file("/etc/fdfs/client.conf", "Makefile", fileid);
    printf("fileID = %s\n", fileid);
}