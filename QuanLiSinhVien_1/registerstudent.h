﻿
#define _REGISTERSTUDENT_H

#pragma once
#include"student.h"
struct RegisterStudent {
	string idStudent;//13
	float point = 0.0;
};

typedef struct RegisterStudent REGISTER_STUDENT;

struct NodeRegisterStudent {
	REGISTER_STUDENT _registerStudent;
	struct NodeRegisterStudent* pNext;
};
typedef struct NodeRegisterStudent NODE_REGISTERSTUDENT;

struct ListRegisterStudent {
	int n = 0;
	NODE_REGISTERSTUDENT* pHead = NULL, * pTail = NULL;
};
typedef struct ListRegisterStudent LIST_REGISTERSTUDENT;

NODE_REGISTERSTUDENT* InitNodeRegisterStudent(REGISTER_STUDENT data)
{
	NODE_REGISTERSTUDENT* p = new NODE_REGISTERSTUDENT;
	if (p == NULL)
		return NULL;
	p->_registerStudent = data;
	p->pNext = NULL;

	return p;
}

void InitListRegisterStudent(LIST_REGISTERSTUDENT& l)
{
	l.pHead = l.pTail = NULL;
}

//----------------------------------

bool ListRegisterStudentIsEmty(LIST_REGISTERSTUDENT l)
{
	return l.pHead == NULL;
}
//
void InsertTailRegisterStudentToList(LIST_REGISTERSTUDENT& l, NODE_REGISTERSTUDENT* ins) {
	l.n++;
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = ins;
	}
	else
	{
		ins->pNext = l.pHead;
		l.pHead = ins;
	}
}
void InsertOrderToListRegister(LIST_REGISTERSTUDENT& l, NODE_REGISTERSTUDENT* ins) {
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = ins;
	}
	else {
		NODE_REGISTERSTUDENT* run;
		for (run = l.pHead; run != NULL && run->pNext != NULL; run = run->pNext) {
			if (run->pNext->_registerStudent.idStudent > ins->_registerStudent.idStudent) {
				break;
			}
		}
		ins->pNext = run->pNext;
		run->pNext = ins;
	}
}
void AddHeadListRegister(LIST_REGISTERSTUDENT& l, REGISTER_STUDENT data)
{
	NODE_REGISTERSTUDENT* p = InitNodeRegisterStudent(data);
	p->pNext = l.pHead;
	l.pHead = p;
	++l.n;
}
//
void AddTailListRegister(LIST_REGISTERSTUDENT& l, REGISTER_STUDENT data)
{
	NODE_REGISTERSTUDENT* p = InitNodeRegisterStudent(data);
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	++l.n;
}
//
NODE_REGISTERSTUDENT* FindRegisterStudent(LIST_REGISTERSTUDENT l, string id)
{
	if (l.pHead == NULL) return NULL;
	for (NODE_REGISTERSTUDENT* p = l.pHead; p != NULL; p = p->pNext)
	{
		if (p->_registerStudent.idStudent == id)
			return p;
	}
	return NULL;
}
//
NODE_REGISTERSTUDENT* FindRegisterStudentByOrdinal(LIST_REGISTERSTUDENT l, int ordinal)
{
	if (l.pHead == NULL) return NULL;
	if (l.n - 1 < ordinal) return NULL;
	if (l.n - 1 == ordinal) return l.pTail;
	if (ordinal == 0) return l.pHead;

	NODE_REGISTERSTUDENT* p = l.pHead;
	int count = 0;
	while (count != ordinal)
	{
		p = p->pNext;
		count++;
	}
	return p;
}
//
int FindIndexRegister(LIST_REGISTERSTUDENT l, string id)
{
	int index = -1;
	if (l.pHead == NULL) return -1;
	for (NODE_REGISTERSTUDENT* p = l.pHead; p != NULL; p = p->pNext)
	{
		++index;
		if (p->_registerStudent.idStudent == id)
			return index;
	}
	return 0;
}
//
bool ClearListRegisterStudent(LIST_REGISTERSTUDENT& l)
{
	if (l.pHead) return false;
	NODE_REGISTERSTUDENT* temp;
	while (l.pHead != NULL)
	{
		temp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete temp;
	}
	return true;
}
