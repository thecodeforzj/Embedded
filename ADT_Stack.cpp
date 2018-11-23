
// ADT_Stack.cpp : 定义控制台应用程序的入口点。
//栈实现

#include "stdafx.h"
#include<stdio.h>
#include<malloc.h>
#include<string>
#include<stdlib.h>
#include<iostream>
#define ElemType int
#define LIST_INIT_SIZE	(15)
#define LISTINCREMENT	(10)
typedef struct
{
	ElemType  *base;
	ElemType  *top;
	int		 listsize;
}SqList;
int InitList_Sq(SqList *l)
{
	l->base = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));//分配内存
	if (!l->base)//内存分配成功
	{
		printf("ERROR!!!");
		exit(EOVERFLOW);
	}
	l->top = l->base;
	l->listsize = LIST_INIT_SIZE;
	return 1;
}

void ReMallocMemory(SqList *l)
{
	int i;
	ElemType  *temp_base;
	ElemType  *new_temp_base;
	ElemType  *delete_base;
	delete_base = l->base;
	int arr_length = l->top - l->base;
	if (arr_length == l->listsize)
	{
		temp_base = (ElemType *)malloc((l->listsize + LISTINCREMENT) * sizeof(ElemType));//分配内存
		new_temp_base = temp_base;
		for (i = 0; i < arr_length; i++)
		{
			*temp_base = *l->base;
			temp_base++;
			l->base++;
		}
		free(delete_base);
		l->top = temp_base;
		l->base = new_temp_base;
		l->listsize = l->listsize + LISTINCREMENT;
	}
}

void AddDataToListSql(SqList *l, ElemType num)
{
	if ((l->top - l->base) < l->listsize)
	{
		*(l->top) = num;
		l->top++;
	}
	else
	{
		ReMallocMemory(l);
		*(l->top) = num;
		l->top++;
	}

}

void Clear_Stack(SqList *l)
{
	if (l->top == l->base)
	{
		printf("空栈");
	}
	else
	{
		free(l->base);
		printf("栈释放成功");
	}
}

bool Stack_Empty(SqList *l)
{
	if (l->top == l->base)
	{
		printf("空栈");
		return false;
	}
	else
	{
		free(l->base);
		printf("栈释放成功");
		return true;
	}
}

int Stack_Length(SqList *l)
{
	int num;
	num = l->top - l->base;
	return num;
}

int Get_Top(SqList l,int *temp)
{
	int num;
	if (l.top == l.base)
	{
		printf("空栈~~~");
		return 0;
	}
	else
	{
		num = *(l.top - 1);
		return 1;
	}


}

int Pop(SqList *l,int *temp)
{
	int num;
	if (l->base == l->top)
	{
		printf("栈空了");
		return 0;
	}
	else
	{
		num = *(l->top - 1);
		l->top--;
		return 1;
	}
}

int main()
{
	int i, num;
	SqList l;
	num = InitList_Sq(&l);
	ElemType  *show_top_arr;
	ElemType  *show_base_arr;
	if (1 == num)
	{
		for (i = 0; i < 1; i++)
		{
			AddDataToListSql(&l, i);
		}
		show_base_arr = l.base;
		show_top_arr = l.top;
		num = l.top - l.base;
		for (i = 0; i < num; i++)
		{
			std::cout << *show_base_arr << std::endl;
			show_base_arr++;
		}

		std::cout << "*****************************" << std::endl;

		for (i = 0; i < num; i++)
		{
			std::cout << *(show_top_arr - 1) << std::endl;
			show_top_arr--;
		}
		Clear_Stack(&l);
	}



	std::cin >> i;

	return 0;
}

