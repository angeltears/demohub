/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:bit
* @Author : angeltears-onter
* @Date : 18-11-3.
* @package : dataCompression
*/

#include "bit.h"
/**
 *  @bits: 传入Bit流
 *  @pos: bit的下标
 */
int bit_get(const unsigned char* bits,int pos)
{
    unsigned char mask = 0x80;
    // 1000 0000
    // 计算机默认小端存储  数据的高字节保存在内存的高地址中，而数据的低字节保存在内存的低地址中
    // pos % 8 即取当前字节的第几位的
    for (int i = 0; i < (pos % 8);i++)
    {
        mask = mask >> 1;
    }
    return (((mask & bits[(int)(pos/8)]) == mask)? 1 : 0);
}
/**
 *  @bits: 传入Bit流
 *  @pos: bit的下标
 *  @state 设置值 0?1
 */
void bit_set(unsigned char  * bits, int pos, int state)
{
    unsigned char mask = 0x80;
    for (int i = 0; i < (pos % 8); i++)
        mask = mask >> 1;

    if(state)
        bits[pos/8]  |= mask;
    else
        bits[pos/8]  &=~mask;
}


/**
 *  @bits1 @bits2: 传入Bit流
 *  @bitsx: 传出参数，需要自己管理内存
 *  @size: bit流长度
 */
void bit_xor(const unsigned char* bits1, const unsigned char *bits2,
             unsigned char * bitsx, int size)
{
    for(int i = 0; i < size; i++)
    {
        /**
         * 1 xor 1 = 0 0 xor 0 = 0
         * 0 xor 1 = 1 1 xor 0 = 1
         */
        if (bit_get(bits1, i) != bit_get(bits2, i))
            bit_set(bitsx, i, 1);
        else
            bit_set(bitsx,i,0);
    }

}

/**
 *  @bits: 传入Bit流
 *  @size: bit流长度
 *  @count: 左移动位数
 */
void bit_rot_left(unsigned char *bits, int size, int count)
{
    int fbit = 0;
    int lbit = 0;
    if (size > 0)
    {
        for (int j = 0; j < count % size; j++)
        {
            for ( int i = 0; i <= ((size - 1) / 8); i++)
            {
                lbit = bit_get(&bits[i], 0);
                if (i == 0)
                {
                    fbit = lbit;   // 保留溢出位最后处理
                }
                else
                {
                    bit_set(&bits[i - 1], 7 , lbit); //将最左边的一位补到上一个字节的最后一位
                }
                bits[i] = bits[i] << 1;
            }
            bit_set(bits, size - 1, fbit);
        }

    }
}