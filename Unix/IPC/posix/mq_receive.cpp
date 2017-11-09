#include <iostream>
#include <stdlib.h>
#include <mqueue.h>
using namespace std;
#define path "/test.1"

int main(int argc, char *argv[])
{
    mqd_t mqd;
    ssize_t n;
    unsigned int prio;
    char *buff;
    struct mq_attr attr;

    mqd = mq_open(path, O_RDONLY);
    if (mqd == -1)
    {
        cout << mqd << " "<<"error"<<endl;
        exit(1);
    }
    mq_getattr(mqd, &attr);

    buff = (char*)malloc(attr.mq_msgsize);

    n = mq_receive(mqd, buff, attr.mq_msgsize, &prio);

    printf("receive :%s", (char *)buff);

    exit(0);
}
