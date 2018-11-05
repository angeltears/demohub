/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-11-4.
* @package : dataCompression
*/

#ifndef DATACOMPRESSION_HUFFMAN_H
#define DATACOMPRESSION_HUFFMAN_H
///
typedef struct HuffNode_
{
    unsigned char   symbol;
    int             freq;
}HuffNode;
/// 编码表
typedef struct HuffCode_
{
    unsigned char used;
    unsigned short code;
    unsigned char size;
};
int huffman_commiess(const unsigned char* original, unsigned char** compressed, int size);
int huffman_uncompress(const unsigned char *compressed, unsigned char** original);

#endif //DATACOMPRESSION_HUFFMAN_H
