/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:bit
* @Author : angeltears-onter
* @Date : 18-11-3.
* @package : dataCompression
*/

#ifndef DATACOMPRESSION_BIT_H
#define DATACOMPRESSION_BIT_H

int bit_get(const unsigned char* bits, int pos);
void bit_set(unsigned char* bit, int pos, int state);
void bit_xor(const unsigned char* bit1, const unsigned char* bit2, unsigned char* bitxor, int size);
void bit_rot_left(unsigned char* bits, int size, int count);

#endif //DATACOMPRESSION_BIT_H
