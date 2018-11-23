// Dotai_Arr.cpp : 定义控制台应用程序的入口点。
//动态数组

#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<string>
#include<stdlib.h>
#include<iostream>
#define ElemType int
#define LIST_INIT_SIZE	(100)
#define LISTINCREMENT	(10)
typedef struct
{
	ElemType  *elem;
	int		 length;
	int		 listsize;
}SqList;
int InitList_Sq(SqList *l)
{	
	 l->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//分配内存

	 if (! l->elem)//内存分配成功
	 {
		 printf("ERROR!!!");
		 exit(EOVERFLOW);
	 }
	 l->length = 0;
	 l->listsize = LIST_INIT_SIZE;
	 return 1;
}

void ReMallocMemory(SqList *l)
{
	int i;
	ElemType  *temp_elem;
	ElemType  *new_temp_elem;
	ElemType  *delete_elem;
	delete_elem = l->elem;
	if (l->length == l->listsize)
	{
		temp_elem = (ElemType *)malloc((l->listsize + LISTINCREMENT) * sizeof(ElemType));//分配内存
		new_temp_elem = temp_elem;
		for (i = 0; i < l->length; i++)
		{
			*temp_elem = *l->elem;
			temp_elem++;
			l->elem++;
		}
		free(delete_elem);
		l->elem = new_temp_elem;
		l->listsize = l->listsize + LISTINCREMENT;
	}
}

void AddDataToListSql(SqList *l, ElemType num)
{
	if (l->length < l->listsize)
	{
		*(l->elem + l->length) = num;
		l->length += 1;
	}
	else
	{
		ReMallocMemory(l);
		*(l->elem + l->length) = num;
		l->length += 1;
	}

}
int main()
{
	int i,num;
	SqList l;
	l.elem = NULL;
	l.length = 0;
	l.listsize = 0;

	num = InitList_Sq(&l);

	if (1 == num)
	{
		for (i = 0; i < 108; i++)
		{
			AddDataToListSql(&l, i);
		}
		for (i = 0; i < l.length; i++)
		{
			std::cout << *l.elem << std::endl;
			l.elem++;
		}
	}



	std::cin >> i;

    return 0;
}

