
#define _REGISTERSTUDENT_H

#pragma once
#include"console.h"
#include"lib.h"
#include"validation.h"
#include"student.h"
struct RegisterStudent {
	string idStudent;//13
	float point = -1;
};

typedef struct RegisterStudent REGISTER_STUDENT;

struct NodeRegisterStudent {
	REGISTER_STUDENT _registerStudent;
	struct NodeRegisterStudent* pNext;
};
typedef struct NodeRegisterStudent NODE_REGISTERSTUDENT;

struct ListRegisterStudent {
	int n = 0;
	NODE_REGISTERSTUDENT* pHead, * pTail;
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
void InsertOrder(LIST_REGISTERSTUDENT& l, NODE_REGISTERSTUDENT* ins) {
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = ins;
	}
	NODE_REGISTERSTUDENT* run;
	for (run = l.pHead; run != NULL && run->pNext != NULL; run = run->pNext) {
		if (run->pNext->_registerStudent.idStudent > ins->_registerStudent.idStudent) {
			break;
		}
	}
	ins->pNext = run->pNext;
	run->pNext = ins;
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
//lỗi
//void InsertOrderForListRegisterStudent(LIST_REGISTERSTUDENT& l, REGISTER_STUDENT data)
//{
//	if (l.pHead == NULL)
//	{
//		AddHeadListRegister(l, data);
//		return;
//	}
//
//	NODE_REGISTERSTUDENT *p, *pAfter, *pBefore;
//	p = InitNodeRegisterStudent(data);
//
//	for (pAfter = l.pHead; pAfter != NULL && (strcmp(pAfter->_registerStudent.idStudent, data.idStudent) < 0);
//		pBefore = pAfter, pAfter = pAfter->pNext);
//
//	if (pAfter == l.pHead)
//		AddHeadListRegister(l, p->_registerStudent);
//	else
//	{
//		p->pNext = pAfter;
//		pBefore->pNext = p;
//		++l.n;
//	}
//}
//
NODE_REGISTERSTUDENT* Middle_1(NODE_REGISTERSTUDENT* start, NODE_REGISTERSTUDENT* last)
{
	if (start == NULL)
		return NULL;
	NODE_REGISTERSTUDENT* slow = start;
	NODE_REGISTERSTUDENT* fast = start->pNext;

	while (fast != last)
	{
		fast = fast->pNext;
		if (fast != last)
		{
			slow = slow->pNext;
			fast = fast->pNext;
		}
	}
	return slow;
}
//
//
NODE_REGISTERSTUDENT* BinarySearchRegisterStudent(LIST_REGISTERSTUDENT l, char* id)
{
	NODE_REGISTERSTUDENT* start = l.pHead;
	NODE_REGISTERSTUDENT* last = NULL;
	if (l.pHead == NULL) return NULL;
	do
	{
		NODE_REGISTERSTUDENT* p = Middle_1(start, last);

		if (p == NULL) return NULL;

		if (p->_registerStudent.idStudent== id)
			return p;
		else if (p->_registerStudent.idStudent== id)
		{

			start = p->pNext;
		}
		else
		{

			last = p;
		}
	} while (start != last);
	return NULL; // value not present;
}
int InputCreditClass(LIST_REGISTERSTUDENT& list, REGISTER_STUDENT student , bool isEdited = false) {
	ShowCur(true);

	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;
	int ordinal = 0;
	string id_student;
	float point = -1;
	if (isEdited)
	{
		id_student = student.idStudent;
		point = student.point;
		gotoXY(X_ADD + 20 + 7, 0 * 3 + Y_ADD);
		cout << id_student;
		gotoXY(X_ADD + 17 + 7, 1 * 3 + Y_ADD);
		cout << point;	
	}
	int key = 0;
	while (true)
	{
		switch (ordinal)
		{
		case 0:
			if (isEdited) break;
			CheckMoveAndValidateID(id_student, isMoveUp, ordinal, isSave, 20 + 7, 12, key);
			if (FindStudent(l, id_student) == NULL)
			{
				idIsExist = false;
				break;
			}
			idIsExist = true;

			break;
		case 1:
			CheckMoveAndValidateNumber(point, isMoveUp, ordinal, isSave, 21 + 7, 2019, key);
			break;
		}
		if (key == KEY_ESC) {
			DeleteMenuAdd();
			return false;
			break;
		}
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;
		}
		else
		{
			if (ordinal == 5)
				isMoveUp = true;
			ordinal++;
		}
		if (isSave)
		{
			gotoXY(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			if (sex == 0 || firstName.empty() || lastName.empty() || yearJoin == 0 || phoneNumber.empty())
			{
				gotoXY(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if (idIsExist)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY);
				cout << "Ma sinh vien khong duoc trung";
			}
			else
			{
				StandarString(firstName);
				StandarString(lastName);

				st.idStudent = idStudent;
				st.firstName = firstName;
				st.lastName = lastName;
				st.phoneNumber = phoneNumber;
				st.gender = sex;

				st.yearJoin = yearJoin;
				StandarString(st.firstName);
				StandarString(st.lastName);

				if (isEdited)
				{
					NodeStudent* p = FindStudent(l, st.idStudent);
					p->data = st;
					return true;

				}
				else
				{

					InsertStudentInListTail(l, InitNodeStudent(st));
					return true;
				}
				//totalPageStudent = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;

			}
			isSave = false;
		}
		else
		{
			isSave = false;
		}
	}
	ShowCur(false);
}
