#pragma once
#include"console.h"

struct Student
{
	string IdStudent; // tối đa 10 kí tự
	string FirstName; // tối đa 15 kí tự
	string LastName; // tối đa 20 kí tự
	int Gender; // tối đa 5 kí tự
	string PhoneNumber; // tối đa 11 kí tự
	string IdClass;
	int YearJoin;

	//DanhSachDiem dsDiem; // con trỏ trỏ đến danh sách điểm - Mỗi 1 thằng sinh viên sẽ có 1 danh sách điểm riêng
};
typedef struct Student STUDENT;
struct nodestudent
{
	STUDENT data; // dữ liệu của node
	struct nodestudent* pNext; // con trỏ liên kết
};
typedef struct nodestudent NodeStudent;
struct ListStudent
{
	NodeStudent* pHead = NULL;
	NodeStudent* pTail = NULL;
};
typedef struct ListStudent ListStudent;


NodeStudent* Init(STUDENT student)
{
	NodeStudent* p = new NodeStudent;
	if (p == NULL)
	{
		return NULL;
	}

	p->data = student;
	p->pNext = NULL;
	return p;
}
//void XuatDanhSachSv(ListStudent list_student) {
//	for (NodeStudent* student = list_student.pHead; student != NULL; student = student->pNext)
//	{
//		Xuat_Thong_tin_1sv(student->data);
//	}
//}
void InsertStudentToListHead(ListStudent& ds, NodeStudent* ins)
{
	// nếu danh sách đang rỗng
	if (ds.pHead == NULL)
	{
		ds.pHead = ds.pTail = ins;
	}
	else
	{
		ins->pNext = ds.pHead;
		ds.pHead = ins;
	}
}
void InsertStudentInListTail(ListStudent& list_student, NodeStudent* ins)
{
	// nếu danh sách đang rỗng
	if (list_student.pHead == NULL)
	{
		list_student.pHead = list_student.pTail = ins;
	}
	else
	{
		list_student.pTail->pNext = ins;
		list_student.pTail = ins;
	}
}
void DeleteStudentHead(ListStudent& list_student)
{
	// danh sách đang rỗng
	if (list_student.pHead == NULL)
	{
		return;
	}
	NodeStudent* del = list_student.pHead; // Cho node del giữ node đầu để tí ta xóa node p cũng chính là xóa node đầu
	list_student.pHead = list_student.pHead->pNext; // cập nhật lại pHead là thằng kế tiếp
	delete del; // xóa node đầu

	// nếu sau khi xóa mà pHead đang trỏ đến NULL thì pTail cũng trỏ đến NULL
	if (list_student.pHead == NULL)
	{
		list_student.pTail = NULL;
	}
}

// hàm xóa 1 node cuối danh sách 
void DeleteStudentTail(ListStudent& list_student)
{
	// nếu danh sách đang rỗng
	if (list_student.pHead == NULL)
	{
		return;
	}
	// duyệt tìm node cuối bằng cách dùng node kế cuối trỏ đến cuối
	for (NodeStudent* prev = list_student.pHead; prev != NULL; prev = prev->pNext)
	{
		// duyệt và tìm node cuối
		if (prev->pNext == list_student.pTail)
		{
			prev->pNext = NULL; // cập nhật lại node kế cuối sẽ là pTail
			delete list_student.pTail;
			list_student.pTail = prev;
			break; // kết thúc quá trình xóa
		}
	}

	// nếu sau khi xóa mà pHead đang trỏ đến NULL thì pTail cũng trỏ đến NULL
	if (list_student.pHead == NULL)
	{
		list_student.pTail = NULL;
	}
}
bool CheckIsExist(ListStudent list_student, string id_student)
{

	for (NodeStudent* run = list_student.pHead; run != NULL; run = run->pNext)
	{
		// mã sinh viên tồn tại
		if (run->data.IdStudent == id_student)
		{
			STUDENT sv;
			sv = run->data;
			return true;
		}
	}
	return false;
}
void DeleteStudent(ListStudent list_student, string id_student) {

}
STUDENT Lay_Thong_Tin_Sinh_Vien_Theo_Ma(ListStudent ds, char* masv)
{

	for (NodeStudent* run = ds.pHead; run != NULL; run = run->pNext)
	{
		// mã sinh viên tồn tại
		if (run->data.IdStudent == masv)
		{
			STUDENT sv;
			sv = run->data;
			return sv;
		}
	}
}

