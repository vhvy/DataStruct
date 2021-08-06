#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "status.h"
#define Elem int

typedef struct _Node
{
    Elem data;
    struct _Node *next;
    struct _Node *prev;
} Node;
// 节点

typedef Node *LinkList;
// 链表

STATUS GetElem(LinkList L, int i, Elem *e);
// 从链表中获取第i个元素的值，保存在e中，并返回状态。

void printLinkList(LinkList L);
// 打印链表内容

int LinkListLength(LinkList L);
// 获取链表长度

STATUS InsertElem(LinkList L, int i, Elem e);
// 向链表指定位置插入数据

STATUS DelElem(LinkList L, int i, Elem *e);
// 删除链表中指定位置元素，并将被删除元素值赋值给e

void CreateRandLinkList(LinkList *L, int length);
// 随机生成N个数据，并保存到链表中

void ClearList(LinkList L);
// 删除整表

void ClearList(LinkList L)
{
    Node *next, *current = L->next;
    while (current != L)
    {
        next = current->next;
        free(current);
        current = next;
    }
    L->next = NULL;
}

void CreateRandLinkList(LinkList *L, int length)
{
    *L = (LinkList)malloc(sizeof(Node));
    // 生成头节点

    if ((*L) == NULL)
    {
        printf("内存分配失败!\n");
        exit(-1);
    }

    srand(time(0));

    Node *node, *end = (*L);
    // 新节点，以及尾节点

    for (int i = 0; i < length; i++)
    {
        node = (Node *)malloc(sizeof(Node));
        node->data = rand() % 100 + 1;
        node->prev = end;
        end->next = node;
        // 插入到尾部

        end = node;
        // 新节点成为尾节点
    }
    end->next = (*L);
    (*L)->prev = end;
    // 尾节点指向NULL
}

void printLinkList(LinkList L)
{
    Node *node = L->next;
    int index = 0;
    while (node != L)
    {
        printf("Index: %d  Data: %d\n", index, node->data);
        node = node->next;
        index++;
    }
}

STATUS DelElem(LinkList L, int i, Elem *e)
{
    if (i < 0)
        return ERROR;
    // 删除位置小于0时返回ERROR

    int length = LinkListLength(L);
    if ((length == 0 && i > 0) || i + 1 > length)
        return ERROR;
    // 如果链表长度为空，且删除位置不为0（第一个节点）时返回ERROR
    // 如果删除位置超出链表长度时返回ERROR

    Node *prev = L, *current;

    while (i > 0)
    {
        // 拿出待删除位置的前一个节点(i - 1)
        prev = prev->next;
        i--;
    }

    *e = prev->next->data;
    // 保存被删除元素的值

    current = prev->next;

    prev->next = current->next;
    prev->next->prev = prev;
    // 将(i-1)指向(i+1)

    free(current);
    // 释放内存

    return OK;
}

STATUS GetElem(LinkList L, int i, Elem *e)
{
    if (L->next == NULL || i < 0)
        return ERROR;

    Node *node = L;

    while (i >= 0 && node)
    {
        node = node->next;
        i--;
    }

    if (!node)
    {
        return ERROR;
    }

    *e = node->data;
    return OK;
}

int LinkListLength(LinkList L)
{
    if (L->next == NULL)
        return 0;
    int length = 0;
    Node *node = L->next;

    while (node != L)
    {
        node = node->next;
        length++;
    }

    return length;
}

STATUS InsertElem(LinkList L, int i, Elem e)
{
    if (i < 0)
        return ERROR;
    // 插入位置小于0时返回ERROR

    int length = LinkListLength(L);
    if ((length == 0 && i > 0) || i > length)
        return ERROR;
    // 如果链表长度为空，且插入位置不为0（第一个节点）时返回ERROR
    // 如果插入位置超过链表长度时返回ERROR
    // 因为插入位置的最大值就是链表长度，即在链表尾部追加节点

    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("内存分配失败!\n");
        exit(-1);
    }

    node->data = e;

    Node *prev = L;

    while (i > 0)
    {
        // 拿出待插入位置的前一个节点(i - 1)
        prev = prev->next;
        i--;
    }

    node->prev = prev;
    node->next = prev->next;
    node->next->prev = node;
    // 要插入的节点指向原来位于i位置的节点

    prev->next = node;
    // 待插入位置的前一个节点指向新节点

    return OK;
}

int main(void)
{


    LinkList L;
    CreateRandLinkList(&L, 1);
    printLinkList(L);

    printf("clear before length: %d\n", LinkListLength(L));
    ClearList(L);
    printf("clear after length: %d\n", LinkListLength(L));

    return 0;
}
