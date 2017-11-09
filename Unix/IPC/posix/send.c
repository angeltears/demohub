#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "pr_ipc_name.h"
#define mq_name  "mq_test.1"
int main()
{
    char *name = px_ipc_name(mq_name);
    printf("%s\n",name);
    mqd_t qid = mq_open(mq_name, O_RDONLY);
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
