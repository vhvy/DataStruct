#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include <stdbool.h>
#define MAXSIZE 1000

typedef int Elem;
typedef struct
{
    Elem data[MAXSIZE];
    int top;
} Stack;

typedef Stack *S;

void InitStack(S *stack_p);
// 初始化栈

STATUS DestoryStack(S *stack_p);
// 销毁栈

STATUS DestoryStack(S *stack_p)
{
    if (*stack_p == NULL)
        return ERROR;
    while ((*stack_p)->top >= 0)
    {
        (*stack_p)->data[(*stack_p)->top] = 0;

        (*stack_p)->top--;
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
    while (stack->top >= 0)
    {
        stack->data[stack->top] = 0;

        stack->top--;
        // 移动栈顶指针
    }

    return OK;
}

bool StackEmpty(S stack);
// 判断栈是否为空,空->true 非空->false

bool StackEmpty(S stack)
{
    return stack->top == -1;
}

bool StackFull(S stack);
// 判断栈是否已满，满->true，非满->false

bool StackFull(S stack)
{
    return stack->top + 1 >= MAXSIZE;
}

STATUS GetTop(S stack, Elem *e);
// 使用e获取栈顶元素

STATUS GetTop(S stack, Elem *e)
{
    if (!stack || StackEmpty(stack))
        return ERROR;

    return stack->data[stack->top];
}

STATUS Push(S stack, Elem *e);
// 入栈元素

STATUS Push(S stack, Elem *e)
{
    if (!stack || StackFull(stack))
        return ERROR;
    stack->top++;
    stack->data[stack->top] = *e;

    return OK;
}

STATUS Pop(S stack, Elem *e);
// 出栈元素

STATUS Pop(S stack, Elem *e)
{
    if (!stack || StackEmpty(stack))
        return ERROR;
    *e = stack->data[stack->top];
    stack->top--;

    return OK;
}

STATUS StackLength(S stack);
// 获取栈元素个数

int StackLength(S stack)
{
    if (!stack)
        return ERROR;

    return stack->top + 1;
}

void InitStack(S *stack_p)
{
    *stack_p = (S)malloc(sizeof(Stack));
    if (stack_p == NULL)
    {
        printf("内存分配失败!");
        exit(-1);
    }
    (*stack_p)->top = -1;
}

int main(void)
{
    S stack;
    InitStack(&stack);
    Elem e;

    printf("Stack length: %d\n", StackLength(stack));

    for (e = 0; e < 10; e++)
    {
        Push(stack, &e);
    }

    Pop(stack, &e);

    printf("Elem e: %d \n", e);

    ClearStack(stack);

    printf("Stack length: %d\n", StackLength(stack));

    DestoryStack(&stack);

    return 0;
}