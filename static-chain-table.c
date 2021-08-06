#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#define MAXSIZE 100

typedef int Elem;
typedef struct
{
    Elem data;
    int cur;
} Node, StaticLinkList[MAXSIZE];

STATUS initList(StaticLinkList L);
// 初始化

int MALLOC_SLL(StaticLinkList L);
// 获取一个可分配的节点下标

void printList(StaticLinkList L, int length);
// 打印列表

STATUS insertElem(StaticLinkList L, int i, Elem e);
// 插入数据

int ListLength(StaticLinkList L);
// 获取链表长度

STATUS delElem(StaticLinkList L, int i);
// 删除指定位置的元素

STATUS getElem(StaticLinkList L, int i, Elem *e);
// 获取指定位置的元素

void printList(StaticLinkList L, int length)
{
    int cur = L[MAXSIZE - 1].cur;
    for (int i = 0; i < length; i++)
    {
        printf("Idx: %d, Data: %d, Cur: %d\n", i + 1, L[cur].data, L[cur].cur);
        cur = L[cur].cur;
    }
}

int MALLOC_SLL(StaticLinkList L)
{
    int idx = L[0].cur;
    if (idx)
    {
        L[0].cur = L[idx].cur;
    }

    return idx;
}

int ListLength(StaticLinkList L)
{
    int nextCur = L[MAXSIZE - 1].cur;
    int count = 0;
    while (nextCur)
    {
        nextCur = L[nextCur].cur;
        count++;
    }

    return count;
}

STATUS delElem(StaticLinkList L, int i)
{
    int length = ListLength(L);
    if (i < 0 || i > length + 1)
    {
        // 删除位置超出范围时返回错误
        return ERROR;
    }

    int cur = MAXSIZE - 1;
    for (int j = 0; j < i; j++)
    {
        cur = L[cur].cur;
    }
    // 取出i - 1个元素的游标位置

    int delCur = L[cur].cur;
    // 将要被标记为删除的元素游标

    L[cur].cur = L[delCur].cur;
    // 将(i-1).cur 指向 (i+1).cur

    L[delCur].cur = L[0].cur;
    L[0].cur = delCur;
    // 将备用元素的游标指向被删除元素

    return OK;
}

STATUS insertElem(StaticLinkList L, int i, Elem e)
{
    int length = ListLength(L);
    if (i < 0 || i > length + 1)
    {
        // 插入位置超出范围时返回错误
        return ERROR;
    }

    int insertIdx = MALLOC_SLL(L);
    if (!insertIdx)
    {
        printf("链表容量已达上限！");
        return ERROR;
    }

    int cur = MAXSIZE - 1;
    for (int j = 0; j < i; j++)
    {
        cur = L[cur].cur;
    }
    // 取出i - 1个元素的游标位置

    L[insertIdx].data = e;
    // 储存数据

    L[insertIdx].cur = L[cur].cur;
    // new.cur -> (i).cur

    L[cur].cur = insertIdx;
    // (i-1).cur -> i.cur

    return OK;
}

STATUS initList(StaticLinkList L)
{
    for (int i = 0; i < MAXSIZE - 1; i++)
    {
        L[i].cur = i + 1;
    }

    L[MAXSIZE - 1].cur = 0;

    return OK;
}

STATUS getElem(StaticLinkList L, int i, Elem *e)
{
    int length = ListLength(L);
    if (i < 0 || i > length + 1)
    {
        // 位置超出范围时返回错误
        return ERROR;
    }

    int cur = MAXSIZE - 1;
    for (int j = 0; j <= i; j++)
    {
        cur = L[cur].cur;
    }
    // 取出i个元素的游标位置

    *e = L[cur].data;

    return OK;
}

int main(void)
{
    StaticLinkList L;

    initList(L);

    Elem e;

    for (int i = 0; i < 10; i++)
    {
        insertElem(L, i, i + 1);
    }

    getElem(L, 8, &e);

    printf("%d\n", e);

    return 0;
}