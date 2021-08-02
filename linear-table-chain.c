#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#define Elem int

typedef struct Node {
	Elem data;
	struct Node* next;
} Node;
// �ڵ�

typedef Node* LinkList;
// ����

STATUS GetElem(LinkList L, int i, Elem* e);
// �������л�ȡ��i��Ԫ�ص�ֵ��������e�У�������״̬��

int LinkListLength(LinkList L);
// ��ȡ������

STATUS InsertElem(LinkList L, int i, Elem e);
// ������ָ��λ�ò�������

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
		printf("�ڴ����ʧ��!\n");
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
		printf("�ڴ����ʧ��!\n");
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

