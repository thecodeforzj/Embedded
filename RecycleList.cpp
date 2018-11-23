// RecycleList.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include<stdlib.h>
#include<iostream>
/*
循环链表
*/
#define data_type int
typedef struct point
{
	data_type data;
	struct point *next;
}PONINT;



PONINT* CreatePoint(void)
{
	PONINT* new_point;
	new_point = (PONINT *)malloc(sizeof(PONINT));
	if (!new_point)
	{
		exit(EOVERFLOW);
	}
	new_point->next = new_point;
	return new_point;
}

void AddDataToList(PONINT *head, data_type data)
{
	PONINT* new_point;
	new_point = CreatePoint();
	new_point->data = data;
	if (head == head->next)//循环链表只有一个节点
	{
		head->next = new_point;
		new_point->next = head;
	}
	else
	{
		new_point->next = head->next;
		head->next = new_point;
	}
}

int DeletePoint(PONINT *head, data_type delete_data)
{
	PONINT *temp_next = head;
	PONINT *temp_delete = head;
	PONINT *temp_point = head;

	if (head == temp_next->next)//循环链表只有一个节点
	{
		if (head->data == delete_data)
		{
			free(head);
			std::cout << "此链表已经删除完了！！！" << std::endl;
			return -1;
		}
	}
	else
	{

		while (temp_point->next != temp_next->next->next)
		{
			if (delete_data == temp_next->next->data)
			{
				temp_delete = temp_next->next;
				temp_next->next = temp_next->next->next;
				free(temp_delete);
				std::cout << "删除成功！！！" << temp_next->next->data << std::endl;
				return 1;
			}
			temp_next = temp_next->next;
		}
	}
	std::cout << "链表中没有此参数-----" << std::endl;//此链表只含有个链表头
	return 0;
}
PONINT* FindDataToList(PONINT *head, data_type find_data)
{
	PONINT* temp_point = head;
	do
	{
		if (find_data == temp_point->data)
		{
			std::cout << "查找成功！！！" << temp_point->data << std::endl;
			return temp_point;
		}
		temp_point = temp_point->next;
	} while (head != temp_point->next);
	return NULL;//此链表不含此数据
}

void ModificationPoint(PONINT *head, data_type old_data, data_type new_data)
{
	PONINT* temp_point = head;
	temp_point = FindDataToList(head, old_data);
	if (NULL == temp_point)
	{
		std::cout << "链表没有此数据" << std::endl;
	}
	else
	{
		temp_point->data = new_data;
	}
}

void ShowList(PONINT *Phead)
{
	PONINT *temp_point = Phead;
	PONINT *temp_comp_point = temp_point;
	if (temp_comp_point == temp_point->next)
	{
		std::cout << temp_point->data << std::endl;
	}
	else
	{
		while (Phead != temp_point->next)
		{
			std::cout << temp_point->data << std::endl;
			temp_point = temp_point->next;
		}
	}

}
int main()
{
	int num;
	PONINT* head = (PONINT *)malloc(sizeof(PONINT));
	head->next = head;
	head->data = -1;
//	ShowList(head);
	//for (num = 0; num < 20; num++)
	//{
	//	AddDataToList(head, num);
	//}
//	ShowList(head);
	std::cout << "--------------------" << std::endl;
	FindDataToList(head, -1);
	ModificationPoint(head, -1, 20);
	ShowList(head);
	DeletePoint(head, 20);
	//ShowList(head);
	//AddDataToList(head, 20);
	std::cin >> num;
	return 0;
}


