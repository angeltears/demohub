#ifndef _CALC_H
#define _CALC_H
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef enum {QUIT, ADD, SUB, MUL, DIV, MOD}ENUM_CALC_TYPE;

//op1 op  op2  1 + 2

#define CMD_SIZE 5

typedef struct calcst
{
    int op1;
    int op2;
    ENUM_CALC_TYPE op;
}calcst;

#endif // _CALC_H
