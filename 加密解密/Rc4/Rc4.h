/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:Rc4
* @Author : angeltears-onter
* @Date : 18-11-1.
* @package : Crypto
*/

#ifndef CRYPTO_RC4_H
#define CRYPTO_RC4_H

#include <algorithm>
using namespace std;

void rc4_init(unsigned char S[256], unsigned char*key, int key_len);
void rc4_crypt(unsigned char S[256], unsigned char *data,int data_len);

void Rc4();

#endif //CRYPTO_RC4_H
