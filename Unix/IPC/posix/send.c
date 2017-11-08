#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define mq_name  "/tmp/mq_test"
int main()
{

    mqd_t qid = mq_open(mq_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH|S_IWGRP|S_IWOTH, NULL);
    struct mq_attr attr;
    attr.mq_maxmsg = 0;
    mq_getattr(qid, &attr);

    printf("attr mq_maxmsg = %ld",attr.mq_maxmsg);
    if (qid == -1)
        printf("error");


   
    
    
    
    mq_close(qid);
    mq_unlink(mq_name);

    exit(0);




}
