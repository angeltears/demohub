/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:Rc4
* @Author : angeltears-onter
* @Date : 18-11-1.
* @package : Crypto
*/

#include <string.h>
#include "Rc4.h"
void rc4_init(unsigned char S[256], unsigned char* key, int key_len)
{
    unsigned char T[256];
    for(int i = 0; i < 256; i++)
    {
        S[i] = i;
        T[i] = key[i % key_len];
    }
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + T[i]) % 256;
        swap(S[i], S[j]);
    }
}

void rc4_crypt(unsigned char S[256], unsigned char *data,int data_len)
{
    int i = 0;
    int j = 0;
    int t = 0;
    for(int r = 0; r < data_len; r++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        t = (S[i] + S[j]) % 256;
        data[r] ^= S[t];
    }
}


void Rc4()
{
    unsigned char S[256];
    unsigned char key[] = "abcdnfnfnfmfc";
    unsigned char data[] = "adsadasdasdasdasdasd";
    int key_len = strlen((const char*)key);
    int data_len = strlen((const char*)data);

    rc4_init(S,key,key_len);
    rc4_crypt(S,data,data_len);
    printf("密文:> %s\n",data);

    rc4_init(S,key,key_len);
    rc4_crypt(S,data,data_len);
    printf("解密明文:> %s\n",data);
}