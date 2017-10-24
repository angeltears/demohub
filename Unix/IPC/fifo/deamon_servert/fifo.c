#include "fifo.h"

void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buff[MAXLINE];

    fgets(buff, MAXLINE, stdin);
    len = strlen(buff);
    if (buff[len -1] == '\n')
        len --;
    
    write(writefd, buff, len);

    while((n = read(readfd, buff, MAXLINE)) > 0)
        write(STDOUT_FILENO, buff, n);
}


void server(int readfd, int writefd)
{
    int fd;
    ssize_t n;
    char buff[MAXLINE + 1];

    if((n = read(readfd, buff, MAXLINE)) == 0)
        printf("end-of-file while reading pathname");
    buff[n] = '\0';

    if ((fd = open(buff, O_RDONLY)) < 0)
    {
        snprintf(buff + n,sizeof(buff) - n, ": %s\n",
                 strerror(errno));
        n = strlen(buff);
        write(writefd, buff, n);
    }
    else 
    {
        while ((n = read(fd, buff, MAXLINE)) > 0)
            write(writefd, buff, n);
        close(fd);
    }
}
static ssize_t my_read(int fd, char *ptr)  
{  
    if (read_cnt <= 0) {  
        again:  
            if ((read_cnt = read(fd, read_buf, MAXLINE)) < 0) {  
                if (errno == EINTR) /*重试*/  
                    goto again;  
                return -1; /*read返回错误*/  
            } else if (read_cnt == 0) /*遇到EOF*/  
                return 0;  
            read_ptr = read_buf;  
    }  
    read_cnt--;  
    *ptr = *read_ptr++;  
    return 1;  
}  

ssize_t Readline(int fd, void *vptr, size_t maxlen)  
{  
    ssize_t n, rc;  
    char c, *ptr;  
      
    ptr = vptr;  
    for (n = 1; n < maxlen; n++) {  
        if ((rc = my_read(fd, &c)) == 1) { /*每次从buf中读取1字节*/  
            *ptr++ = c;  
            if (c == '\n') /*已经读取一行数据*/  
                break;  
        } else if (rc == 0) { /*buf中无数据*/  
            *ptr = 0;  
            return n - 1;  
        } else  
            return -1;  
    }  
    *ptr = 0;  
    return n;  
}  
 
