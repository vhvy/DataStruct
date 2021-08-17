#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./status.h"

typedef int Ele;

typedef struct _Node
{
    Ele data;
    struct _Node *next;
} _Node, *Node;

typedef struct Queue
{
    Node head;
    Node end;
    int length;
} Queue, *Q;

void InitQueue(Q *q);
void InitQueue(Q *q)
{
    *q = (Q)malloc(sizeof(Queue));
    if (*q == NULL)
    {
        printf("内存分配失败!");
        exit(-1);
    }
    (*q)->head = NULL;
    (*q)->end = NULL;
    (*q)->length = 0;
}

void ClearQueue(Q q);
void ClearQueue(Q q)
{
    if (q->length > 0)
    {
        Node next = q->head;
        Node current = NULL;
        while (next)
        {
            current = next;
            next = current->next;
            q->length--;
            free(current);
        }
    }
    q->end = q->head = NULL;
}

void DestoryQueue(Q *q);
void DestoryQueue(Q *q)
{
    ClearQueue(*q);
    *q = NULL;
}

STATUS pushQueue(Q q, Ele e);
STATUS pushQueue(Q q, Ele e)
{
    Node node = (Node)malloc(sizeof(_Node));
    if (node == NULL)
    {
        printf("内存分配失败!");
        exit(-1);
    }

    node->data = e;
    node->next = NULL;

    if (q->head == NULL)
    {
        q->head = node;
    }
    else
    {
        q->end->next = node;
    }
    q->end = node;
    q->length++;

    return OK;
}

STATUS popQueue(Q q, Ele *e);
STATUS popQueue(Q q, Ele *e)
{
    if (q->length < 1)
        return ERROR;

    *e = q->head->data;
    Node head = q->head;
    q->head = head->next;
    free(head);
    q->length--;

    return OK;
}

void printQueue(Q q);
void printQueue(Q q)
{
    Node node = q->head;
    printf("Queue length is %d \n", q->length);
    while (node)
    {
        printf("Data is: %d\n", node->data);
        node = node->next;
    }
}

int main(void)
{
    Ele e = 20;
    Q queue;
    InitQueue(&queue);
    pushQueue(queue, e);
    pushQueue(queue, e);
    pushQueue(queue, e);
    printQueue(queue);
    // popQueue(queue, &e);
    // popQueue(queue, &e);
    ClearQueue(queue);
    printQueue(queue);

    return 0;
}