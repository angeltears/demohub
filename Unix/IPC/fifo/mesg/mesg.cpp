#include "mesg.h"

mesg::mesg()
{
    _mesg = new struct mymesg;
    _size = setsize();
}
ssize_t mesg::setsize()
{
    return (sizeof(struct mymesg)-MAXDATA);
}
ssize_t mesg::mesg_send(int fd)
{
    return(write(fd, _mesg, _size));
}
ssize_t mesg::mese_recv(int fd)
{
    size_t len;
    ssize_t n;

    if ((n = read(fd, _mesg, _size)) == 0)
        return 0;
    else if (n != _size)
    {
        printf("message header: expected %d, got %d", _size, n);
        exit(0);
    }
    
    if ((len = _mesg->mesg_len) > 0)
        if((n = read(fd, _mesg->mesg_date, len)) != len)
           {
                printf("message date : expected %d, got %d", len,n);
                exit(0);
           }
    return len;
}

mesg::~mesg()
{
    delete _mesg;
    _mesg = NULL;
}

void client::_client(int readfd, int writefd)
{
    int len;
    int n;

    fgets(_mesg->mesg_date, MAXDATA, stdin);
    len = strlen(_mesg->mesg_date);
    if (_mesg->mesg_date[len - 1] = '\n')
    {
        len--;
    }
    _mesg->mesg_len = len;
    _mesg->mesg_type = 1;
    mesg::mesg_send(writefd, _mesg);

    while((n = mesg::mesg_recv(readfd, _mesg)) > 0)
        write(STDOUT_FILENO, _mesg->mesg_date, n);
}

void severt::_severt(int readfd, int writefd)
{
    FILE *fp;
    ssize_t n;
    
    _mesg->mesg_type = 1;
    if ((n = mesg::mesg_recv(readfd, _mesg)) == 0)
    {
            printf("missing pathname!");
            exit(0);
    }
    _mesg->mesg_date[n] = '\0';

    if((fp = fopen(_mesg->mesg_date, "r")) == NULL)
    {
        snprintf(_mesg->mesg_date, sizeof(_mesg->mesg_date)-n,
                 ": can't open, %s",strerror(errno));
        _mesg->mesg_len = strlen(_mesg->mesg_date);
        mesg::mesg_send(writefd, _mesg);
    }
    else 
    {
        while ((fgets(_mesg->mesg_date,MAXDATA, fp)) != NULL)
        {
            _mesg->mesg_len = strlen(_mesg->mesg_date);
            mesg::mesg_send(writefd, _mesg);
        }
    }
    fclose(fp);

    _mesg->mesg_len = 0;
    mesg::mesg_send(writefd, _mesg);
}
