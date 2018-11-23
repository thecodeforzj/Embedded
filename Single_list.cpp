// new_list.cpp : �������̨Ӧ�ó������ڵ㡣
//������


#include "stdafx.h"
#include<stdlib.h>
#include<iostream>
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
	new_point->next = NULL;
	return new_point;
}

void AddDataToList(PONINT *head, data_type data)
{
	PONINT* new_point;
	new_point = CreatePoint();
	new_point->data = data;
	if (NULL == head->next)
	{
		head->next = new_point;
	}
	else
	{
		new_point->next = head->next;
		head->next = new_point;
	}
}

int DeletePoint(PONINT head, data_type delete_data)
{
	PONINT *temp_next = &head;
	PONINT *temp_delete = &head;

	while (NULL != temp_next->next)
	{
		if (delete_data == temp_next->next->data)
		{
			temp_delete = temp_next->next;
			temp_next->next = temp_next->next->next;
			free(temp_delete);
			std::cout << "ɾ���ɹ�������" << temp_next->next->data << std::endl;
			return 1;
		}
		else
		{
			if (NULL == temp_next->next->next)
			{
				std::cout << "������û�д˲���++++++" << std::endl;
			}
		}
		temp_next = temp_next->next;
	}
	std::cout << "������û�д˲���-----" << std::endl;//������ֻ���и�����ͷ
	return 0;
}
PONINT* FindDataToList(PONINT head, data_type find_data)
{
	PONINT* temp_point = head.next;
	while (NULL != temp_point)
	{
		if (find_data == temp_point->data)
		{
			std::cout << "���ҳɹ�������" << temp_point->data << std::endl;
			return temp_point;
		}
		else
		{
			if (NULL == temp_point->next)
			{
				return NULL;
			}
		}
		temp_point = temp_point->next;
	}
	return NULL;//������ֻ���и�����ͷ
}

void ModificationPoint(PONINT head, data_type old_data, data_type new_data)
{
	PONINT* temp_point = &head;
	temp_point = FindDataToList(head, old_data);
	if (NULL == temp_point)
	{
		std::cout << "����û�д�����" << std::endl;
	}
	else
	{
		temp_point->data = new_data;
	}
}

void ShowList(PONINT head)
{
	PONINT *temp_point = &head;
	if (NULL == temp_point->next)
	{
		std::cout << "������" << std::endl;
	}
	while (NULL != temp_point->next)
	{
		std::cout << temp_point->data << std::endl;
		temp_point = temp_point->next;
	}
}
int main()
{
	int num;
	PONINT* head = (PONINT *)malloc(sizeof(PONINT));
	head->next = NULL;
	head->data = -1;
	for (num = 0; num < 20; num++)
	{
		AddDataToList(head, num);
	}
	ShowList(*head);
	std::cout << "--------------------" << std::endl;
	FindDataToList(*head, 11);
	ModificationPoint(*head, 15, 20);
	DeletePoint(*head, 11);
	ShowList(*head);
	//	AddDataToList(head, 20);
	std::cin >> num;
	return 0;
}

