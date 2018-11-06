/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:
* @Author : angeltears-onter
* @Date : 18-11-5.
* @package : dataCompression
*/

#include "bitree.h"
#include <memory.h>
#include <malloc.h>
void bitree_init(BiTree* tree, void (*destroy)(void *data))
{
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
}

void bitree_destroy(BiTree* tree)
{
    /// 删除所有树的结点
    bitree_rem_left(tree, NULL);
    /// 清理二叉树数据结构
    memset(tree, 0, sizeof(BiTree));
}


int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode* new_node, **position;

    /// 确定插入结点的位置
    if (node == NULL)
    {
        if (bitree_size(tree) > 0)
            return -1;
        position = &tree->root;
    }
    else
    {
        if(bitree_left(node) != NULL)
            return -1;
        position = &node->left;
    }
    /// 初始化结点存储空间
    if ((new_node = (BiTreeNode *)malloc(sizeof (BiTreeNode))) == NULL)
        return -1;
    /// 将结点插入到树中
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;
    tree->size++;

    return 0;
}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode    *new_node, **position;

    /// 确定插入结点的位置
    if (node == NULL)
    {
        if (bitree_size(tree) > 0)
            return -1;
        position = &tree->root;

    }
    else
    {
        /// 只有指定结点的右结点为空才允许插入
        if (bitree_right(node) != NULL)
            return -1;
        position = &node->right;
    }

    /// 初始化结点存储空间
    if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
        return -1;

    /// 将结点插入到树中
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    /// 更新树的 size
    tree->size++;

    return 0;
}


void bitree_rem_left(BiTree* tree, BiTreeNode* node)
{
    BiTreeNode **position;

    if (bitree_size(tree) == 0)
        return;
    if (node == NULL)
    {
        position = &tree->root;
    } else
    {
        position = &node->left;
    }

    if(!*position != NULL)
    {
        /// 递归删除左边
        bitree_rem_left(tree, *position);
        /// 递归删除右边
        bitree_rem_right(tree, *position);

        if(tree->destroy != NULL)
        {
            tree->destroy((*position)->data);
        }

        free(*position);
        position = NULL;
        tree->size--;
    }
}


void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode    **position;

    /// 不允许在空树中执行移除
    if (bitree_size(tree) == 0) return;

    /// 确定移除结点的位置
    if (node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->right;
    }

    /// 移除结点（按照后序遍历从参数 node 的左子结点开始依次移除）
    if (*position != NULL)
    {

        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL)
        {
            /// 执行用户指定的 destroy 函数
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        /// 更新树的 size
        tree->size--;
    }
}


int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
    bitree_init(merge, left->destroy);

    if (bitree_ins_left(merge, NULL, data) != 0)
    {
        bitree_destroy(merge);
        return -1;
    }
    /// 将两棵树合并到新树
    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);
    /// 设置新树的 size
    merge->size = merge->size + bitree_size(left) + bitree_size(right);
    /// 解除原来树中的结点关系并把 size 置为 0
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;
    return 0;
}