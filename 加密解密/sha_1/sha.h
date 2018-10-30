/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:sha_1
* @Author : angeltears-onter
* @Date : 18-10-29.
* @package : Crypto
*/

#ifndef CRYPTO_SHA_H
#define CRYPTO_SHA_H
#include <cstdio>
#include <cstring>
typedef unsigned char uint8;
typedef unsigned long int uint32;

struct sha1_contxt
{
    uint32 total[2];      // total[0] 处理数据长度　total未处理数据长度
    uint32 state[5];
    uint8  buffer[64];    // 64 * 8 =  512
};

void sha1_starts(struct sha1_contxt *ctx);
void sha1_update(struct sha1_contxt *ctx, uint8* input, uint32 length);
void sha1_finish(struct sha1_contxt* ctx, uint8 digest[20]);


unsigned char* Sha(const char * plaintext);
void show_ciphertext(unsigned char ciphertext[20]);
#endif //CRYPTO_SHA_H
