/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-11-4.
* @package : dataCompression
*/

#include "compress.h"
#include "bitree.h"
#include <malloc.h>
/**
 比较两棵霍夫曼树的根节点频率
 @param tree1 霍夫曼树1
 @param tree2 霍夫曼树2
 @return tree1 小于 tree1 返回1, tree1 大于 tree1 返回 -1, 相等返回0
 */
static int compare_freq(const void *tree1, const void* tree2)
{
    HuffNode *root1, *root2;

    root1 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree1));
    root2 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree2));

    if (root1->freq < root2->freq)
        return 1;
    if (root1->freq > root2->freq)
        return -1;
    return 0;
}
/**
 销毁霍夫曼树
 @param tree 霍夫曼树
 */
static void destroy_tree(void *tree)
{
    bitree_destroy((BiTree *)tree);
    free(tree);
}


/**
 通过字节频率建立霍夫曼树
 @param freqs 符号频率数组
 @param tree 构建后的霍夫曼树
 @return 成功返回 0, 否则返回 -1
 */
int huffman_compress(const unsigned char* original, unsigned char** compressed, int size)
{

}

