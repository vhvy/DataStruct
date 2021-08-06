#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include <stdbool.h>
#define MAXSIZE 1000

typedef int Elem;
typedef struct
{
    Elem data[MAXSIZE];
    int top1;
    int top2;
} DualStack;

const int TOP1_END = MAXSIZE / 2;
const int TOP2_END = MAXSIZE / 2 + 1;

typedef DualStack *S;

void InitStack(S *stack_p);
// 初始化栈

STATUS DestoryStack(S *stack_p);
// 销毁栈

STATUS DestoryStack(S *stack_p)
{
    if (*stack_p == NULL)
        return ERROR;
    while ((*stack_p)->top1 >= 0)
    {
        (*stack_p)->data[(*stack_p)->top1] = 0;

        (*stack_p)->top1--;
        // 移动栈顶指针
    }

    while ((*stack_p)->top2 < MAXSIZE)
    {
        (*stack_p)->data[(*stack_p)->top2] = 0;

        (*stack_p)->top2++;
        // 移动栈顶指针
    }

    free(*stack_p);
    // 释放栈本体

    return OK;
}

STATUS ClearStack(S stack);
// 清空栈

STATUS ClearStack(S stack)
{
    if (stack == NULL)
        return ERROR;
    while (stack->top1 >= 0)
    {
        stack->data[stack->top1] = 0;

        stack->top1--;
        // 移动栈顶指针
    }

    while (stack->top2 < MAXSIZE)
    {
        stack->data[stack->top2] = 0;

        stack->top2++;
        // 移动栈顶指针
    }

    return OK;
}

bool StackEmpty(S stack, int num);
// 判断栈是否为空,空->true 非空->false

bool StackEmpty(S stack, int num)
{

    return num == 1 ? stack->top1 == -1 : stack->top2 == MAXSIZE;
}

bool StackFull(S stack, int num);
// 判断栈是否已满，满->true，非满->false

bool StackFull(S stack, int num)
{
    return num == 1 ? stack->top1 >= TOP1_END : stack->top2 <= TOP2_END;
}

STATUS GetTop(S stack, Elem *e, int num);
// 使用e获取栈顶元素

STATUS GetTop(S stack, Elem *e, int num)
{
    if (!stack || StackEmpty(stack, num))
        return ERROR;

    return num == 1 ? stack->data[stack->top1] : stack->data[stack->top2];
}

STATUS Push(S stack, Elem *e, int num);
// 入栈元素

STATUS Push(S stack, Elem *e, int num)
{
    if (!stack || StackFull(stack, num))
        return ERROR;
    if (num == 1)
    {
        stack->top1++;
        stack->data[stack->top1] = *e;
    }
    else
    {
        stack->top2--;
        stack->data[stack->top2] = *e;
    }

    return OK;
}

STATUS Pop(S stack, Elem *e, int num);
// 出栈元素

STATUS Pop(S stack, Elem *e, int num)
{
    if (!stack || StackEmpty(stack, num))
        return ERROR;

    if (num == 1)
    {
        *e = stack->data[stack->top1];
        stack->top1--;
    }
    else
    {
        *e = stack->data[stack->top2];
        stack->top2++;
    }

    return OK;
}

STATUS StackLength(S stack, int num);
// 获取栈元素个数

int StackLength(S stack, int num)
{
    if (!stack)
        return ERROR;

    switch (num)
    {
    case 1:
        return stack->top1 + 1;
    case 2:
        return MAXSIZE - stack->top2;
    default:
        return stack->top1 + 1 + (MAXSIZE - stack->top2);
    }
}

void InitStack(S *stack_p)
{
    *stack_p = (S)malloc(sizeof(DualStack));
    if (stack_p == NULL)
    {
        printf("内存分配失败!");
        exit(-1);
    }
    (*stack_p)->top1 = -1;
    (*stack_p)->top2 = MAXSIZE;
}

int main(void)
{
    S stack;
    InitStack(&stack);
    Elem e;

    printf("Stack 1 length: %d\n", StackLength(stack, 1));
    printf("Stack 2 length: %d\n", StackLength(stack, 2));

    for (e = 0; e < 10; e++)
    {
        Push(stack, &e, e % 2 + 1);
    }

    Pop(stack, &e, 1);
    printf("Elem e: %d \n", e);

    Pop(stack, &e, 2);
    printf("Elem e: %d \n", e);

    ClearStack(stack);

    printf("Stack 1 length: %d\n", StackLength(stack, 1));
    printf("Stack 2 length: %d\n", StackLength(stack, 2));

    DestoryStack(&stack);

    return 0;
}