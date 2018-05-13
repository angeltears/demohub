#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <cstdio>
using namespace std;
bool getPublicIp(string& ip)
{
    int    sock;
    char **pptr = NULL;
    struct sockaddr_in    destAddr;
    struct hostent    *ptr = NULL;
    char destIP[128];

    sock = socket(AF_INET,SOCK_STREAM,0);
    if( -1 == sock ){
        cout<<"creat socket failed"<<endl;
        return false;
    }
    bzero((void *)&destAddr,sizeof(destAddr));
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(80);
    ptr = gethostbyname("www.ip138.com");
    if(NULL == ptr){
        cout<<"gethostbyname error"<<endl;
        return false;
    }
    for(pptr=ptr->h_addr_list ; NULL != *pptr ; ++pptr){
        inet_ntop(ptr->h_addrtype,*pptr,destIP,sizeof(destIP));
        printf("addr:%s\n",destIP);
        ip = destIP;
        return true;
    }
    return true;
}

int main()
{
  string ip;
  getPublicIp(ip);
  cout << ip;
}
