#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#define Elem int

typedef struct Node {
	Elem data;
	struct Node* next;
} Node;
// 节点

typedef Node* LinkList;
// 链表

STATUS GetElem(LinkList L, int i, Elem* e);
// 从链表中获取第i个元素的值，保存在e中，并返回状态。

int LinkListLength(LinkList L);
// 获取链表长度

STATUS InsertElem(LinkList L, int i, Elem e);
// 向链表指定位置插入数据

STATUS GetElem(LinkList L, int i, Elem* e)
{
	if (L->next == NULL || i < 0)
		return ERROR;

	Node* node = L;

	while (i >= 0 && node)
	{
		node = node->next;
		i--;
	}

	if (!node) {
		return ERROR;
	}

	*e = node->data;
	return OK;
}

int LinkListLength(LinkList L) {
	if (L->next == NULL)
		return 0;
	int length = 0;
	Node* node = L;

	while (node)
	{
		node = node->next;
		length++;
	}

	return length;
}

STATUS InsertElem(LinkList L, int i, Elem e) {
	if (i < 0)
		return ERROR;
	int length = LinkListLength(L);
	printf("Length is %d\n", length);
	if ((length == 0 && i > 0) || (i + 1 > length))
		return ERROR;

	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		printf("内存分配失败!\n");
		exit(-1);
	}

	node->data = e;

	Node* prev = L;

	while (i > 0)
	{
		prev = prev->next;
	}


	node->next = prev->next;
	prev->next = node;

	return OK;
}

int main(void) {
	LinkList L = (LinkList)malloc(sizeof(Node));
	Elem e;
	STATUS res;

	if (L == NULL) {
		printf("内存分配失败!\n");
		exit(-1);
	}
	L->next = NULL;

	for (int i = 0; i < 10; i++) {
		InsertElem(L, i, i * 10);
	}

	//res = GetElem(L, 0, &e);

	printf("%d\n", LinkListLength(L));

	return 0;
}

