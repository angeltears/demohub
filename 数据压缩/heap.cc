/**
* Copyright: Copyright (c) 2018 angeltears-hyj, All right reserved.
* 
* @Functional description:heap
* @Author : angeltears-onter
* @Date : 18-11-5.
* @package : dataCompression
*/

#include "heap.h"
#include <cstdlib>
#include <cstring>

/**
 获取父结点位置 (i-1)/2
 @param npos 当前结点位置
 @return 父结点位置
 */
#define heap_parent(npos) ((int)(((npos) - 1) / 2))

/**
 获取左子结点位置 i*2+1
 @param npos 当前结点位置
 @return 左子结点位置
 */
#define heap_left(npos) (((npos) * 2) + 1)

/**
 获取右子结点位置 i*2+2
 @param npos 当前结点位置
 @return 右子结点位置
 */
#define heap_right(npos) (((npos)*2) + 2)


void heap_init(Heap *heap,
               int (*compare)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = nullptr;
}

void heap_destroy(Heap* heap)
{
    if (heap->destroy != nullptr)
    {
        for (int i = 0; i < heap_size(heap); i++)
        {
            heap->destroy(heap->tree[i]);
        }
    }

    free(heap->tree);
    memset(heap, 0, sizeof Heap);
}

int heap_insert(Heap *heap, const void *data)
{
    void **temp;
    if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof (void *))) == NULL)
        return -1;
    heap->tree = temp;
    heap->tree[heap_size(heap)] = (void *)data;

    /// 上滤
    int ipos = heap_size(heap);
    int ppos = heap_parent(ipos);
    void * tmp = nullptr;
    /// 交换当前结点与父结点内容
    while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0)
    {
        tmp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;

        ipos = ppos;
        ppos = heap_parent(ipos);
    }
}

int heap_extract(Heap *heap, void **data)
{
    if (heap_size(heap) == 0)
        return -1;

    /// 释放堆中的顶部节点
    *data = heap->tree[0];

    /// 调整堆的存储空间
    void *save = heap->tree[heap_size(heap) - 1];
    void **temp;
    if(heap_size(heap) - 1 > 0)
    {
        if ((temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *))) == NULL)
            return -1;
        heap->tree = temp;
        heap->size--;
    }
    else
    {
        //当释放最后一个结点
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    /// 下滤操作
    heap->tree[0] = save;
    int ipos = 0;
    int lpos = heap_left(ipos);
    int rpos = heap_right(ipos);
    int mpos = 0;
    void *tmp;
    while(1)
    {
        /// 选择与当前结点交换的子结点
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);

        if (lpos < heap_size(heap) && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0)
        {

            mpos = lpos;

        }
        else
        {

            mpos = ipos;
        }

        if (rpos < heap_size(heap) && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0)
        {

            mpos = rpos;
        }

        /// 当 mpos 就是 ipos 时，堆已经完成调整
        if (mpos == ipos)
        {

            break;

        }
        else
        {

            /// 交换当前结点与选择的子结点内容
            tmp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = tmp;

            /// 将结点向下移动一层保障树的平衡
            ipos = mpos;
        }
    }


}