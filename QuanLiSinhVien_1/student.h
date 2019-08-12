﻿#pragma once
#include"console.h"

#include"subject.h"
#define QUALITYSTUDENT 10
struct Student
{
	string idStudent; // tối đa 10 kí tự
	string firstName; // tối đa 15 kí tự
	string lastName; // tối đa 20 kí tự
	int gender; // tối đa 5 kí tự
	string phoneNumber; // tối đa 11 kí tự
	string idClass;
	int yearJoin;

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

STUDENT listStudent[MAXLISTSTUDENT];
int nStudent = 0;

NodeStudent* InitNodeStudent(STUDENT student)
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

NodeStudent* FindStudent(ListStudent l, string id)
{
	if (l.pHead == NULL) return NULL;

	for (NodeStudent* p = l.pHead; p != NULL; p = p->pNext)
		if (p->data.idStudent == id)
			return p;
	return NULL;
}
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
void InsertStudentInListTail(ListStudent& list_student, NodeStudent* ins)//insert order vào dslkd
{
	// nếu danh sách đang rỗng
	if (list_student.pHead == NULL)
	{
		list_student.pHead = list_student.pTail = ins;
	}
	else
	{
		/*list_student.pTail->pNext = ins;
		list_student.pTail = ins;*/
		/*
			lay vi tri can them (run)
		*/
		// trường hợp : thêm đầu - 
		if (list_student.pHead->data.idClass == ins->data.idClass) {
			if (list_student.pHead->data.idStudent > ins->data.idStudent) {  // nếu mà class trùng thì thêm theo msv nhỏ hơn thì thêm đầu       
				ins->pNext = list_student.pHead;
				list_student.pHead = ins;
				return;
			}
		}
		else if (list_student.pHead->data.idClass > ins->data.idClass) {  // class đưa vô nhỏ hơn thì thêm đầu
			ins->pNext = list_student.pHead;
			list_student.pHead = ins;
			return;
		}
		// thêm sau phần tử bất kì
		NodeStudent* run;
		for (run = list_student.pHead; run != NULL && run->pNext != NULL; run = run->pNext) {
			if (run->pNext->data.idClass == ins->data.idClass) {        // chạy đến khi thấy lớp trùng
				if (run->pNext->data.idStudent > ins->data.idStudent) {
					break;
				}
			}
			else if (run->pNext->data.idClass > ins->data.idClass) {   //class nhỏ hơn 
				break;
			}
		}
		ins->pNext = run->pNext; // thêm sau run
		run->pNext = ins;
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
bool DeleteStudent(ListStudent& list_student, string id_student)
{
	// nếu danh sách rỗng thì không làm gì hết
	if (list_student.pHead == NULL)
	{
		return false;
	}
	// nếu node cần xóa nằm đầu danh sách
	if (list_student.pHead->data.idStudent == id_student)
	{
		DeleteStudentHead(list_student);
		return true;
	}
	// nếu node cần xóa nằm ở cuối danh sách
	if (list_student.pTail->data.idStudent == id_student)
	{
		DeleteStudentTail(list_student);
		return true;
	}

	NodeStudent* prev = new NodeStudent; // node prev là node trỏ đến node nằm trước node cần xóa: x
	// duyệt danh sách liên kết đơn để tìm
	for (NodeStudent* run = list_student.pHead; run != NULL; run = run->pNext)
	{
		// phát hiện phần tử cần xóa
		if (run->data.idStudent == id_student)
		{
			prev->pNext = run->pNext; // cập nhật mối liên kết giữa node run với node sau node h
			delete run; // xóa node nằm sau node run	
			return true;
		}
		prev = run; // cho node g trỏ đến node run

	}

}
bool CheckIsExist(ListStudent list_student, string id_student)
{

	for (NodeStudent* run = list_student.pHead; run != NULL; run = run->pNext)
	{
		// mã sinh viên tồn tại
		if (run->data.idStudent == id_student)
		{
			STUDENT sv;
			sv = run->data;
			return true;
		}
	}
	return false;
}
STUDENT Lay_Thong_Tin_Sinh_Vien_Theo_Ma(ListStudent ds, char* masv)
{

	for (NodeStudent* run = ds.pHead; run != NULL; run = run->pNext)
	{
		// mã sinh viên tồn tại
		if (run->data.idStudent == masv)
		{
			STUDENT sv;
			sv = run->data;
			return sv;
		}
	}
}
//Đọc ghi file sinh viên ==============================================
void ReadStudent(ListStudent& list_student, ifstream& f)
{
	string line;
	getline(f, line);
	STUDENT student;
	int n;
	string temp;
	while (!f.eof()) {
		n = 0;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		student.idStudent = temp;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		student.firstName = temp;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		student.lastName = temp;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		student.gender = atoi(temp.c_str());
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		student.phoneNumber = temp;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		student.idClass = temp;
		temp = "";
		for (int i = 0; n < line.size(); i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		student.yearJoin = atoi(temp.c_str());

		InsertStudentInListTail(list_student, InitNodeStudent(student));
		getline(f, line);
	}
}
void ReadFileStudent(ListStudent& list_student)
{
	ifstream f("student.txt");
	if (f.is_open()) {
		/*	if (!f.peek() == EOF) {
				getline(f, pass);
				docCay(t, f);
				docSV(ds, f);
				f.close();
			}*/
		ReadStudent(list_student, f);
		f.close();
	}
}
void WriteFileStudent(ListStudent ds)
{
	/*
	string MaSV; // tối đa 10 kí tự
	string HoSV; // tối đa 15 kí tự
	string TenSV; // tối đa 20 kí tự
	int Phai; // tối đa 5 kí tự
	string SDT; // tối đa 11 kí tự
	string MaLop;
	int NamNhapHoc;
	*/
	ofstream f("student.txt");
	if (f.is_open()) {
		NodeStudent* student;
		for (student = ds.pHead; student != NULL; student = student->pNext) {
			f << student->data.idStudent << "," <<
				student->data.firstName << "," <<
				student->data.lastName << "," <<
				student->data.gender << "," <<
				student->data.phoneNumber << "," <<
				student->data.idClass << "," <<
				student->data.yearJoin << endl;
		}
		f.close();
	}
}
//=============================================================================================================

struct DisplayStudent {
	STUDENT* data;
	DisplayStudent* next = NULL;
	DisplayStudent* prev = NULL;
};
struct ListStudentDisplay {
	DisplayStudent* first = NULL;
	DisplayStudent* last = NULL;
};

void insertLast(ListStudentDisplay& l, STUDENT* data) {
	DisplayStudent* ins = new DisplayStudent({ data });
	if (l.first == NULL) {
		l.first = l.last = ins;
	}
	else {
		l.last->next = ins;
		ins->prev = l.last;
		l.last = ins;
	}
}

void insertListStudent(ListStudentDisplay& l, ListStudent ds) {

	for (NodeStudent* run = ds.pHead; run != NULL; run = run->pNext) {
		insertLast(l, &run->data);
	}
}

void clearAllStudentDisplay(ListStudentDisplay& l) {
	l.last = NULL;
	DisplayStudent* del;
	while (l.first != NULL) {
		del = l.first;
		l.first = l.first->next;
		delete del;
	}
}

DisplayStudent* endList(DisplayStudent* first) {
	DisplayStudent* run = first;
	for (int i = 0; i < QUALITYSTUDENT && run != NULL; i++, run = run->next) {
		if (run->next != NULL) {
			if (run->next->data->idClass != run->data->idClass) {
				break;
			}
		}
	}
	return run;
}

void displayStudentList(DisplayStudent* first, DisplayStudent* last, DisplayStudent* select) {
	SetBGColor(ColorCode_White);
	SetColor(ColorCode_Black);
	int i = 0;
	gotoXY(5, 6);
	cout << "Lop: ";
	if (first != NULL)
		cout << first->data->idClass;
	else
		cout << "Hien Khong Co Lop!!!";
	if (first != NULL) {
		for (DisplayStudent* run = first;; run = run->next) {
			if (run == select) {
				//to mau neu dang chon
				SetBGColor(ColorCode_Blue);
			}
			else {
				//mau binh thuong neu k chon
				SetBGColor(ColorCode_White);
			}
			//display tai day
			if (run != NULL) {
				gotoXY(5, 10 + i++);
				cout << " " << run->data->idStudent << string(10 - run->data->idStudent.size(), ' ') << char(186) << " " << run->data->firstName
					<< string(15 - run->data->firstName.size(), ' ') << char(186) << " " << run->data->lastName << string(20 - run->data->lastName.size(), ' ');
			}
			if (run == last)
				break;
		}
	}
	while (i < 11) {
		gotoXY(5, 10 + i++);
		SetBGColor(ColorCode_White);
		cout << string(11, ' ') << char(186) << string(16, ' ') << char(186) << string(21, ' ');
	}
}

bool nextStudent(DisplayStudent*& first, DisplayStudent*& last, DisplayStudent*& select) {
	if (select->next != NULL) {
		if (select->next->data->idClass == select->data->idClass) {
			select = select->next;
			return true;
		}
	}
	return false;
}

bool prevStudent(DisplayStudent*& first, DisplayStudent*& last, DisplayStudent*& select) {
	if (select->prev != NULL) {
		if (select->prev->data->idClass == select->data->idClass) {
			select = select->prev;
			return true;
		}
	}
	return false;
}

bool nextClass(DisplayStudent*& first, DisplayStudent*& last, DisplayStudent*& select) {
	DisplayStudent* temp = first;
	while (1) {
		first = first->next;
		if (first == NULL)
			break;
		else if (first->prev->data->idClass != first->data->idClass)
			break;
	}
	if (first == NULL) {
		first = temp;
		return true;
	}
	else {
		select = first;
		last = endList(first);
		return false;
	}
}

bool prevClass(DisplayStudent*& first, DisplayStudent*& last, DisplayStudent*& select) {
	DisplayStudent* temp = first;
	while (first->prev != NULL) {
		first = first->prev;
		if (first == NULL)
			break;
		if (first->prev != NULL) {
			if (first->prev->data->idClass != first->data->idClass)
				break;
		}
		else {
			if (first->next->data->idClass != first->data->idClass)
				break;
		}
	}
	if (first == NULL) {
		first = temp;
		return true;
	}
	else {
		select = first;
		last = endList(first);
		return false;
	}
}

void InputStudent(ListStudent& l, STUDENT& st, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;

	string idStudent, firstName, lastName, phoneNumber;
	int yearJoin = 0, sex = 0;

	if (isEdited)
	{
		idStudent = st.idStudent;
		firstName = st.firstName;
		lastName = st.lastName;
		phoneNumber = st.phoneNumber;
		yearJoin = st.yearJoin;
		sex = st.gender;


		gotoXY(X_ADD + 20 + 7, 0 * 3 + Y_ADD);
		cout << idStudent;
		gotoXY(X_ADD + 17 + 7, 1 * 3 + Y_ADD);
		cout << firstName;
		gotoXY(X_ADD + 18 + 7, 2 * 3 + Y_ADD);
		cout << lastName;
		gotoXY(X_ADD + 19 + 7, 3 * 3 + Y_ADD);
		cout << sex;
		gotoXY(X_ADD + 20 + 7, 4 * 3 + Y_ADD);
		cout << phoneNumber;
		gotoXY(X_ADD + 21 + 7, 5 * 3 + Y_ADD);
		cout << yearJoin;
	}

	while (true)
	{
		switch (ordinal)
		{
		case 0:
			if (isEdited) break;
			CheckMoveAndValidateID(idStudent, isMoveUp, ordinal, isSave, 20 + 7, 12);
			if (FindStudent(l, idStudent) == NULL)
			{
				idIsExist = false;
				break;
			}
			idIsExist = true;

			break;
		case 1:
			CheckMoveAndValidateNameSubject(firstName, isMoveUp, ordinal, isSave, 17 + 7, 20);
			break;
		case 2:
			CheckMoveAndValidateNameSubject(lastName, isMoveUp, ordinal, isSave, 18 + 7, 10);
			break;
		case 3:
			CheckMoveAndValidateNumber(sex, isMoveUp, ordinal, isSave, 19 + 7, 2);
			break;
		case 4:
			CheckMoveAndValidateID(phoneNumber, isMoveUp, ordinal, isSave, 20 + 7, 11);
			break;
		case 5:
			CheckMoveAndValidateNumber(yearJoin, isMoveUp, ordinal, isSave, 21 + 7, 2019);
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
				}
				else
				{
					InsertStudentInListTail(l, InitNodeStudent(st));
				}
				//totalPageStudent = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;
				DeleteMenuAdd();
				return;
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

int countStudentInClass(DisplayStudent* first, string idClass) {// chạy từ ngay trang của lớp đó 
	int i = 0;
	for (DisplayStudent* run = first; run != NULL && run->data->idClass == idClass; run = run->next, i++);
	return i;
}


void mainStudent(ListStudent& ds) {
	ListStudentDisplay l;
	DisplayStudent* first, * last, * select;
	int key;
	Xu_Li_Con_Tro_Chi_Vi(FALSE);
	do {
		insertListStudent(l, ds);
		select = first = l.first;
		last = endList(first);
		do {
			displayStudentList(first, last, select);
			key = _getch();
			if (key == KEY_CONTROL) {
				key = _getch();
				if (key == KEY_UP) {
					prevStudent(first, last, select);
				}
				else if (key == KEY_DOWN) {
					nextStudent(first, last, select);
				}
				else if (key == KEY_LEFT) {
					prevClass(first, last, select);
				}
				else if (key == KEY_RIGHT) {
					nextClass(first, last, select);
				}
			}
			else if (key == KEY_F2) {
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);
				DisplayEdit(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string), 35);
				STUDENT st;
				st.idClass = select->data->idClass;
				InputStudent(ds, st);

				/*st.gender = 1;
				st.phoneNumber = "1231242";
				st.yearJoin = 2;*/
				//InsertStudentInListTail(ds, InitNodeStudent(st));
				clearAllStudentDisplay(l);
				insertListStudent(l, ds);
				for (first = l.first; first != NULL && first->data->idClass != st.idClass; first = first->next);
				select = first;
				last = endList(first);
				Xu_Li_Con_Tro_Chi_Vi(FALSE);
				system("cls");
			}
			else if (key == KEY_F3) {
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);
				DisplayEdit(inputClass, sizeof(inputClass) / sizeof(string), 30);
				STUDENT st;
				gotoXY(159, 11);
				getline(cin, st.idClass);
				DisplayEdit(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string), 35);
				InputStudent(ds, st);
				clearAllStudentDisplay(l);
				insertListStudent(l, ds);
				for (first = l.first; first != NULL && first->data->idClass != st.idClass; first = first->next);
				select = first;
				last = endList(first);
				Xu_Li_Con_Tro_Chi_Vi(FALSE);
				system("cls");
			}
			else if (key == KEY_F4) {
				Xu_Li_Con_Tro_Chi_Vi(TRUE);
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);
				DisplayEdit(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string), 35);
				InputStudent(ds, *select->data, true);
				Xu_Li_Con_Tro_Chi_Vi(FALSE);
			}
			else if (key == KEY_F5) {
				if(countStudentInClass(first, select->data->idClass) > 1){// đếm xem còn sv ko 

					string idClass = select->data->idClass; // giữ lại class
					//DisplayStudent* temp = first;  // lưu lại first
					DeleteStudent(ds, select->data->idStudent); // xoá 
					clearAllStudentDisplay(l);
					insertListStudent(l, ds); // restore dữ liệu
					for (first = l.first; first != NULL && first->data->idClass != idClass; first = first->next);// chạy lại lp đó
					select = first;
					last = endList(first);
					//if (temp != NULL) {     //điều chỉnh lại con trỏ 
					//	if (first != NULL) {
					//		select = first;
					//		last = endList(first);
					//	}
					//	else {
					//		select = first = temp;
					//		last = endList(first);
					//	}
					//}
				}
			}
			else if (key == KEY_F6) {
				string idClass = select->data->idClass;
				while (first != NULL && first->data->idClass == idClass) {
					DeleteStudent(ds, first->data->idStudent);
					first = first->next;
				}
				clearAllStudentDisplay(l);
				break;
			}
		} while (key != KEY_ESC);
	} while (key != KEY_ESC);
}