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

// ��List�е�i��Ԫ�ظ�ֵ��e��������״̬
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
	// ����Ϊ�ա�Ԫ���±�С��0����Ԫ���±곬�����鳤��ʱ���ش���
	if (L->length == 0 || i < 0 || i + 1 > L->length)
		return ERROR;

	*e = L->data[i];

	// �Ƿ����һ��Ԫ��
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
		printf("�ڴ����ʧ��!");
		exit(-1);
	}
	L->length = 0;
	Elem e = 2;

	for (int s = 0; s < 10; s++) {
		e = s * 2;
		InsertElem(L, s, &e);
	}
	// ����

	for (int s = 0; s < 10; s++) {
		GetElem(L, s, &e);
		printf("No %d is: %d \n", s, e);
	}
	// ��ӡ

	DelElem(L, 4, &e);
	
	printf("----------------\n");

	for (int s = 0; s < 10; s++) {
		GetElem(L, s, &e);
		printf("No %d is: %d \n", s, e);
	}
	// ��ӡ


	free(L);
	return 0;
}