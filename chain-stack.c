#include <stdio.h>
#include <stdlib.h>
#include "./status.h"

typedef int El;
typedef struct StructNode
{
    El data;
    struct StructNode *next;
} StructNode, *NodePtr;

typedef struct LinkStack
{
    NodePtr top;
    int count;
} LinkStack;

void initStack(LinkStack *p);

void initStack(LinkStack *p)
{
    LinkStack *z = (LinkStack *)malloc(sizeof(LinkStack));
    if (p == NULL)
    {
        printf("内存分配失败!");
        exit(-1);
    }

    *p = *z;

    p->count = 0;
    p->top = NULL;
}

STATUS pushStack(LinkStack *p, El e);

STATUS pushStack(LinkStack *p, El e)
{
    NodePtr node = (NodePtr)malloc(sizeof(StructNode));
    if (node == NULL)
    {
        printf("内存分配失败!");
        exit(-1);
    }
    node->data = e;
    node->next = p->top;
    p->top = node;
    p->count++;
    return OK;
}

STATUS popStack(LinkStack *p, El *e);

STATUS popStack(LinkStack *p, El *e)
{
    if (p->count == 0)
        return ERROR;
    NodePtr node = p->top;
    *e = node->data;
    p->top = node->next;
    p->count--;
    free(node);
    return OK;
}

STATUS DestoryStack(LinkStack *p);

STATUS DestoryStack(LinkStack *p)
{
    if (p->count > 0)
    {
        NodePtr current = p->top;
        NodePtr last = NULL;
        while (current)
        {
            last = current;
            current = current->next;
            free(last);
        }
    }
    free(p);
    return OK;
}

void printStack(LinkStack *p);

void printStack(LinkStack *p)
{
    NodePtr node = p->top;
    while (node)
    {
        printf("Data: %d\n", node->data);
        node = node->next;
    }
}

int main(void)
{
    LinkStack Stack;
    El e = 5;

    initStack(&Stack);
    pushStack(&Stack, e);
    printf("Stack length is %d\n", Stack.count);
    printStack(&Stack);
    popStack(&Stack, &e);
    printf("Stack length is %d\n", Stack.count);

    DestoryStack(&Stack);
    return 0;
}