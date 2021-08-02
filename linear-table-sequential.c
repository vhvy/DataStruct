#include <stdio.h>
#include <stdlib.h>
#include "status.h"

#define Elem int
#define MAXSIZE 10

typedef struct
{
	Elem data[MAXSIZE];
	int length;
} List;

// 将List中第i个元素赋值给e，并返回状态
STATUS GetElem(List* L, int i, Elem* e);
STATUS InsertElem(List* L, int i, Elem* e);
STATUS DelElem(List* L, int i, Elem* e);

STATUS GetElem(List* L, int i, Elem* e)
{
	if (L->length == 0 || i < 0 || i > L->length + 1)
		return ERROR;
	*e = L->data[i];
	return OK;
}

STATUS InsertElem(List* L, int i, Elem* e)
{
	if (L->length == MAXSIZE || i > MAXSIZE - 1 || i < 0)
		return ERROR;

	if (i <= L->length - 1)
	{
		for (int z = L->length - 1; z >= 0; z--)
		{
			L->data[z + 1] = L->data[z];
		}
	}

	L->data[i] = *e;
	L->length++;
	return OK;
}

STATUS DelElem(List* L, int i, Elem* e)
{
	// 数组为空、元素下标小于0或者元素下标超出数组长度时返回错误
	if (L->length == 0 || i < 0 || i + 1 > L->length)
		return ERROR;

	*e = L->data[i];

	// 是否最后一个元素
	if (i < L->length - 1) {
		for (int z = i; z < L->length - 1; z++) {
			L->data[z] = L->data[z + 1];
		}
	}
	L->length--;

	return OK;
}

int main(void)
{
	List* L = (List*)malloc(sizeof(List));
	if (L == NULL) {
		printf("内存分配失败!");
		exit(-1);
	}
	L->length = 0;
	Elem e = 2;

	for (int s = 0; s < 10; s++) {
		e = s * 2;
		InsertElem(L, s, &e);
	}
	// 插入

	for (int s = 0; s < 10; s++) {
		GetElem(L, s, &e);
		printf("No %d is: %d \n", s, e);
	}
	// 打印

	DelElem(L, 4, &e);
	
	printf("----------------\n");

	for (int s = 0; s < 10; s++) {
		GetElem(L, s, &e);
		printf("No %d is: %d \n", s, e);
	}
	// 打印


	free(L);
	return 0;
}