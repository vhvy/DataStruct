#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./status.h"
#define QueueSize 5

typedef int Ele;

typedef struct Queue
{
    int front;
    int rear;
    Ele data[QueueSize];
} Queue, *Q;

void InitQueue(Q *q);

void InitQueue(Q *q)
{
    *q = (Q)malloc(sizeof(Queue));
    if (q == NULL)
    {
        printf("内存分配失败!");
        exit(-1);
    }
}

void DestoryQueue(Q *q);
void DestoryQueue(Q *q)
{
    if (q != NULL)
    {
        *q = NULL;
    }
}

void ClearQueue(Q q);
void ClearQueue(Q q)
{
    q->rear = 0;
    q->front = 0;
}

bool QueueEmpty(Q q);
bool QueueEmpty(Q q)
{
    return q->front == q->rear;
}

bool QueueFull(Q q);
bool QueueFull(Q q)
{
    return (q->rear + 1) % QueueSize == q->front;
}

int QueueLength(Q q);
int QueueLength(Q q)
{
    return (q->rear - q->front + QueueSize) % QueueSize;
}

STATUS pushQueue(Q q, Ele e);
STATUS pushQueue(Q q, Ele e)
{
    if (QueueFull(q))
        return ERROR;

    q->data[q->rear] = e;

    q->rear = (q->rear + 1) % QueueSize;

    return OK;
}

STATUS popQueue(Q q, Ele *e);
STATUS popQueue(Q q, Ele *e)
{
    if (QueueEmpty(q))
        return ERROR;

    *e = q->data[q->front];

    q->front = (q->front + 1) % QueueSize;

    return OK;
}

void printQueue(Q q)
{
    int length = QueueLength(q);
    if (length != 0)
    {
        int end = q->front > q->rear ? QueueSize : q->rear;
        for (int i = q->front; i < end; i++)
        {
            printf("Idx: %d, El: %d\n", i, q->data[i]);
            length--;
        }

        if (length > 0)
        {
            for (int i = 0; i < length; i++)
            {
                printf("Idx: %d, El: %d\n", i, q->data[i]);
            }
        }
    }
}

int main(void)
{
    Q queue;
    Ele e = 24;

    InitQueue(&queue);
    pushQueue(queue, e);
    pushQueue(queue, e);
    pushQueue(queue, e);
    printQueue(queue);
    // printf("Queue length is: %d\n", QueueLength(queue));
    // popQueue(queue, &e);
    // printf("Queue length is: %d\n", QueueLength(queue));
    // printf("Ele is: %d ptr: %p\n", e, &e);

    return 0;
}