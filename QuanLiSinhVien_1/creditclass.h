#pragma once

#include"subject.h"
#include"registerstudent.h"


struct CreditClass {
	unsigned int idClass = 0;
	string idSubject; // ma mon hoc // key	
	int shoolYear; // nien khoa
	int semester; // hoc ki
	int group; // nhom
	int studentMax;
	int studentMin;
	//nameSubject; //tìm kiếm
	LIST_REGISTERSTUDENT listRegisterStudent;
};
typedef struct CreditClass CREDITCLASS;
typedef CREDITCLASS* PTR_CREDITCLASS;

struct ListCreaditClass {

	int n = 0;
	PTR_CREDITCLASS listCreditClass[MAXLISTSTUDENT] = { NULL };//5000
};
typedef struct ListCreaditClass LIST_CREDITCLASS;





int totalPageCreditClass = 0;// tổng trang 
int pageNowCreditClass = 1;// page hiện tại
int currposPrecCreditClass = 0;//biến tính toán
int currposCreditClass = 0;//  biến chạy trong 1 trang

void InsertCreditClass(LIST_CREDITCLASS& l, CREDITCLASS data) {
	if (l.n < MAXLISTSTUDENT) {
		l.listCreditClass[l.n++] = new CREDITCLASS(data);
	}
}

//hàm kiểm tra
bool dataCreditClassIsEmty(PTR_CREDITCLASS temp)
{
	if (temp->group == 0 || temp->semester == 0 || temp->shoolYear == 0 || temp->studentMax == 0 || temp->studentMin == 0) return true;
	if (temp->idSubject.empty()) return true;
	return false;
}



// hàm tìm kiếm 
PTR_CREDITCLASS FindCreditClassWithBinariSearch(LIST_CREDITCLASS l, unsigned int id)
{
	if (l.n < 0) return NULL;
	for (int i = 0; i < l.n; i++)
	{
		if (l.listCreditClass[i]->idClass == id)
			return l.listCreditClass[i];
		return NULL;
	}
}

int FindCreditClassWithIdSubject(LIST_CREDITCLASS l, string idSubject)
{
	if (l.n < 0) return NULL;
	for (int i = 0; i <= l.n; i++)
	{
		if (l.listCreditClass[i]->idSubject == idSubject)
			return i;
		return NULL;
	}
}

// find index of class -- tim kiem index cua class
int FindIndexClass(LIST_CREDITCLASS l, unsigned int idClass)
{
	if (l.n < 0) return -1;
	for (int i = 0; i <= l.n; i++)
	{
		if (l.listCreditClass[i]->idClass == idClass)
			return i;
	}
	return -1;
}

// các hàm xoá 
bool DeleteCreditClass(LIST_CREDITCLASS& l, unsigned int id)
{
	int index = FindIndexClass(l, id);
	delete l.listCreditClass[index];
	if (index == -1)return false;
	//if (l.listCreditClass[index]->listRegisterStudent.pHead != NULL) return;

	for (int i = index; i < l.n; i++)
	{
		l.listCreditClass[i] = l.listCreditClass[i + 1];

	}

	l.n--;
	return true;
}

bool DeleteCreditClassIsSuccess(LIST_CREDITCLASS& l, unsigned int id)
{
	int index = FindIndexClass(l, id);

	if (index == -1)return false;
	//if (l.listCreditClass[index]->listRegisterStudent.pHead != NULL) return false;
	if (index != -1) {
		PTR_CREDITCLASS del = l.listCreditClass[index];
		ClearListRegisterStudent(del->listRegisterStudent);
		for (int i = index; i < l.n; i++)
		{
			l.listCreditClass[i] = l.listCreditClass[i + 1];

		}
		l.n--;
		l.listCreditClass[l.n] = NULL;// cho cái này là NULL

		delete del;
		return true;
	}

}
PTR_CREDITCLASS FindCrediClassWithConditionReturn(LIST_CREDITCLASS l, string idSubject, int shoolYear, int semester, int group)
{

	for (int i = 0; i < l.n; i++)
	{
		if (l.listCreditClass[i]->idSubject == idSubject &&
			l.listCreditClass[i]->shoolYear == shoolYear && l.listCreditClass[i]->semester == semester && l.listCreditClass[i]->group == group)
		{
			return l.listCreditClass[i];
		}
	}
	return NULL;
}
bool FindCrediClassWithCondition(LIST_CREDITCLASS l, string idSubject, int shoolYear, int semester, int group)
{

	for (int i = 0; i < l.n; i++)
	{
		if (l.listCreditClass[i]->idSubject == idSubject &&
			l.listCreditClass[i]->shoolYear == shoolYear && l.listCreditClass[i]->semester == semester && l.listCreditClass[i]->group == group)
		{
			return true;
		}
	}
	return false;
}
bool FindCrediClassWithConditionRegister(LIST_CREDITCLASS l, int shoolYear, int semester)
{

	for (int i = 0; i < l.n; i++)
	{
		if (l.listCreditClass[i]->shoolYear == shoolYear && l.listCreditClass[i]->semester == semester)
		{
			return true;

		}
	}
	return false;
}
//hàm input 
bool CheckRegisterIsExist(PTR_CREDITCLASS cc, string id_student) {
	LIST_REGISTERSTUDENT list_register = cc->listRegisterStudent;

	if (list_register.pHead == NULL) return NULL;
	for (NODE_REGISTERSTUDENT* p = list_register.pHead; p != NULL; p = p->pNext)
	{
		if (p->_registerStudent.idStudent == id_student) {
			return true;
		}

	}
	return false;
}
void InputCreditClass(LIST_CREDITCLASS& l, CREDITCLASS& cc, TREE_SUBJECT t, bool isEdited = false) // nhap  Lop TC
{
	ShowCur(true);

	// cac flag dieu khien qua trinh cap nhat
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;


	string idSubject; // ma mon hoc
	int shoolYear = 0; // nien khoa
	int semester = 0; // hoc ki 
	int group = 0; // nhom
	int studentMax = 0;
	int studentMin = 0;



	if (isEdited)
	{
		idSubject = cc.idSubject;
		shoolYear = cc.shoolYear;
		semester = cc.semester;
		studentMin = cc.studentMin;
		studentMax = cc.studentMax;
		group = cc.group;

		// binding data;

		gotoXY(X_ADD + 20 + 7, 0 * 3 + Y_ADD);
		cout << idSubject;

		gotoXY(X_ADD + 17 + 7, 1 * 3 + Y_ADD);
		cout << shoolYear;

		gotoXY(X_ADD + 21 + 7, 2 * 3 + Y_ADD);
		cout << semester;

		gotoXY(X_ADD + 19 + 7, 3 * 3 + Y_ADD);
		cout << group;

		gotoXY(X_ADD + 20 + 7, 4 * 3 + Y_ADD);
		cout << studentMax;

		gotoXY(X_ADD + 20 + 7, 5 * 3 + Y_ADD);
		cout << studentMin;
	}

	int key = 0;
	while (true)
	{
		switch (ordinal)
		{

		case 0:
			if (isEdited) break;
			CheckMoveAndValidateID(idSubject, isMoveUp, ordinal, isSave, 27, 10, key);
			break;

		case 1:
			CheckMoveAndValidateNumber(shoolYear, isMoveUp, ordinal, isSave, 24, 2019, key);
			break;
		case 2:
			CheckMoveAndValidateNumber(semester, isMoveUp, ordinal, isSave, 28, 3, key);
			break;
		case 3:
			CheckMoveAndValidateNumber(group, isMoveUp, ordinal, isSave, 26, 3, key);
			break;
		case 4:
			CheckMoveAndValidateNumber(studentMax, isMoveUp, ordinal, isSave, 27, MAX_STUDENT, key);
			break;
		case 5:
			CheckMoveAndValidateNumber(studentMin, isMoveUp, ordinal, isSave, 27, MIN_STUDENT, key);
			break;
		}
		if (key == KEY_ESC) {
			DeleteMenuAdd();
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
			gotoXY(X_NOTIFY + 10, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";

			PTR_CREDITCLASS temp = new CREDITCLASS;
			temp->idSubject = idSubject;
			temp->idClass = 0;
			temp->semester = semester;
			temp->shoolYear = shoolYear;
			temp->studentMax = studentMax;
			temp->studentMin = studentMin;
			temp->group = group;

			if (dataCreditClassIsEmty(temp))
			{
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Cac truong du lieu khong duoc de trong";
			}
			else if (FindCrediClassWithCondition(l, idSubject, shoolYear, semester, group) != NULL)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Lop tin chi da ton tai";
			}
			else if (studentMax < studentMin)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "So luong sinh vien khong hop le";
			}
			else if (FindSubject(t, temp->idSubject) == NULL) {
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Ma mon hoc khong ton tai, nhap ma khac ";
			}
			else
			{
				cc.idSubject = idSubject;
				NODE_SUBJECT* p = FindSubject(t, cc.idSubject);

				//cc.nameSubject = p->data.nameSubject;
				//cc->idClass = ++l.n;
				cc.group = group;
				cc.shoolYear = shoolYear;
				cc.studentMax = studentMax;
				cc.studentMin = studentMin;
				cc.semester = semester;

				if (isEdited)
				{
					int index = FindIndexClass(l, cc.idClass);
					*l.listCreditClass[index] = cc;

				}
				else
				{
					if (l.n != 0)
						cc.idClass = l.listCreditClass[l.n - 1]->idClass + 1;
					//InitListRegisterStudent(cc->listRegisterStudent);
					//l.listCreditClass[l.n] = new CREDITCLASS;
					//l.listCreditClass[l.n] = cc;

					InsertCreditClass(l, cc);


				}
				DeleteMenuAdd();
				totalPageCreditClass = l.n / QUANTITY_PER_PAGE + 1;
				return;
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	if (isSave) {
		gotoXY(X_NOTIFY + 10, Y_NOTIFY);
		cout << "THEM THANH CONG!";
	}
	ShowCur(false);


}

//giao diện

void OutputCreditClass(PTR_CREDITCLASS cc, TREE_SUBJECT t, int ordinal) // ordinal == thu tu
{
	DeleteOldData(sizeof(keyDisplayCreditClass) / sizeof(string), ordinal);
	gotoXY(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + ordinal); cout << cc->idClass;
	gotoXY(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + ordinal); cout << FindSubject(t, cc->idSubject)->data.nameSubject;
	gotoXY(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + ordinal); cout << cc->idSubject;
	gotoXY(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + ordinal); cout << cc->shoolYear;
	gotoXY(xKeyDisplay[4] + 1, Y_DISPLAY + 3 + ordinal); cout << cc->semester;
	gotoXY(xKeyDisplay[5] + 1, Y_DISPLAY + 3 + ordinal); cout << cc->group;
	gotoXY(xKeyDisplay[6] + 1, Y_DISPLAY + 3 + ordinal); cout << cc->studentMax;
	gotoXY(xKeyDisplay[7] + 1, Y_DISPLAY + 3 + ordinal); cout << cc->studentMin;
}


void InputSearchCreditClass(LIST_CREDITCLASS list, int& year, int& semester, bool& isSave) {
	ShowCur(true);
	// cac flag dieu khien qua trinh cap nhat
	int ordinal = 0;
	bool isMoveUp = false;
	int key = 0;
	while (key != KEY_ESC)
	{

		switch (ordinal)
		{
		case 0:
			CheckMoveAndValidateNumber(year, isMoveUp, ordinal, isSave, 30, 3000, key);
			break;
		case 1:
			CheckMoveAndValidateNumber(semester, isMoveUp, ordinal, isSave, 27, 4, key);
			break;
		}
		if (key == KEY_ESC)break;
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;

		}
		else
		{
			if (ordinal == 2)
				isMoveUp = true;
			ordinal++;
		}
		if (key == KEY_ENTER)
		{
			gotoXY(X_NOTIFY + 10, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";

			if (year == NULL || semester == NULL)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Cac truong du lieu khong duoc de trong";
			}
			else if (FindCrediClassWithConditionRegister(list, year, semester) == false)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Khong co lop tin chi nao thoa man dieu kien";
			}
			else {
				isSave = true;
				return;
			}

		}
		else
			isSave = false;
	}


}
void InputSearchListRegister(LIST_CREDITCLASS list, string& id_subject, int& year, int& semester, int& group, bool& isSave, int& key) {
	ShowCur(true);
	// cac flag dieu khien qua trinh cap nhat
	int ordinal = 0;
	bool isMoveUp = false;
	//int key = 0;
	while (key != KEY_ESC)
	{
		//key = _getch();
		switch (ordinal)
		{
		case 0:
			CheckMoveAndValidateID(id_subject, isMoveUp, ordinal, isSave, 29, 10, key);
			break;
		case 1:
			CheckMoveAndValidateNumber(year, isMoveUp, ordinal, isSave, 30, 3000, key);
			break;
		case 2:
			CheckMoveAndValidateNumber(semester, isMoveUp, ordinal, isSave, 27, 4, key);
			break;
		case 3:
			CheckMoveAndValidateNumber(group, isMoveUp, ordinal, isSave, 29, 4, key);
			break;
		}
		if (key == KEY_ESC) {
			isSave = false;
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
			if (ordinal == 4)
				isMoveUp = true;
			ordinal++;
		}
		if (isSave)
		{
			gotoXY(X_NOTIFY + 10, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";

			if (year == NULL || semester == NULL)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Cac truong du lieu khong duoc de trong";
			}
			else if (FindCrediClassWithCondition(list, id_subject, year, semester, group) == false)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Khong co lop tin chi nao thoa man dieu kien";
			}
			else {
				isSave = true;
				return;
			}

		}
		else
			isSave = false;
	}
}
// CHOOESE CREDIT CLASS
void AddToListTemp(LIST_CREDITCLASS& list_temp, PTR_CREDITCLASS credit_class) {
	if (list_temp.n < 5000) {
		list_temp.listCreditClass[list_temp.n++] = credit_class;
	}
}

void ViewCreditClass(LIST_CREDITCLASS l, TREE_SUBJECT t, int select) {
	if (l.listCreditClass[0] != NULL) {
		PTR_CREDITCLASS c;
		gotoXY(X_DISPLAY, Y_DISPLAY - 5);
		SetColor(ColorCode_Blue);
		SetBGColor(ColorCode_White);
		cout << l.listCreditClass[0]->shoolYear;
		for (int i = 0; i < l.n; i++) {
			if (i == select) {
				//chỉnh màu
				SetBGColor(ColorCode_Blue);
				SetColor(ColorCode_White);
			}
			else {
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);
				//chỉnh màu
			}
			c = l.listCreditClass[i];
			//them gotoXY
			//gotoXY(X_DISPLAY, Y_DISPLAY + i);
			//cout << c.idClass << " - " << c.nameSubject;
			OutputCreditClass(c, t, i);
		}
	}
}

void OutputListChooseCreditClass(LIST_CREDITCLASS& l, TREE_SUBJECT t, int year, int semester, string id_student) {
	LIST_CREDITCLASS listTemp;
	for (int i = 0; i < l.n; i++) {
		if ((l.listCreditClass[i]->shoolYear == year) && (l.listCreditClass[i]->semester == semester)) {
			AddToListTemp(listTemp, l.listCreditClass[i]);
		}
	}
	gotoXY(X_DISPLAY, Y_DISPLAY - 3); cout << "MSSV : " << id_student;
	int select = 0, key = 0;
	if (listTemp.n != 0) {
		while (key != KEY_ESC) {
			ViewCreditClass(listTemp, t, select);
			key = _getch();
			if (key == KEY_CONTROL) {
				key = getch();
				if (key == KEY_UP) {
					if (select != 0) {
						select--;
					}
				}
				else if (key == KEY_DOWN) {
					if (select != listTemp.n - 1) {
						select++;
					}
				}
			}
			if (key == KEY_ENTER) {
				if (CheckRegisterIsExist(listTemp.listCreditClass[select], id_student) == true) {
					gotoXY(X_NOTIFY, Y_NOTIFY);
					cout << "BAN DA DANG KI LOP TIN CHI NAY";

				}
				else if (listTemp.listCreditClass[select]->studentMax == listTemp.listCreditClass[select]->listRegisterStudent.n) {
					gotoXY(X_NOTIFY, Y_NOTIFY);
					cout << "LOP TIN CHI NAY DA DAY, BAN KHONG THE DANG KI";
				}
				else {
					InsertOrderToListRegister(listTemp.listCreditClass[select]->listRegisterStudent, InitNodeRegisterStudent({ id_student , 0.0 }));
					listTemp.listCreditClass[select]->listRegisterStudent.n++;
					gotoXY(X_NOTIFY, Y_NOTIFY);
					cout << "DANG KI THANH CONG";
				}

				//while (_getch() != KEY_ESC)break;
				//clrscr();
			}
			if (key == KEY_ESC) {
				clrscr();
				return;
			}
			/*	else if (key == KEY_ENTER) {
					if (CheckRegisterIsExist(listTemp.listCreditClass[select], id_student) == true) {
						gotoXY(X_NOTIFY, Y_NOTIFY);

					}
					InsertOrderToListRegister(listTemp.listCreditClass[select]->listRegisterStudent, InitNodeRegisterStudent({ id_student , 0.0 }));
				}*/
		}

	}
}
void managerRegisterCreditClass(LIST_CREDITCLASS& l, ListStudent list_student, TREE_SUBJECT t) {
	clrscr();
	int key = 0;
	bool isSave = false;
	clrscr();
	//key = _getch();
	while (key != KEY_ESC) {


		SetColor(ColorCode_Blue);
		gotoXY(getXScreen() / 2 - 30, 10);

		cout << "NHAP MA SINH VIEN CAN DANG KI TIN CHI" << endl;
		gotoXY(getXScreen() / 2 - 30, 12);
		cout << "========================";
		//DisplayEdit(keyInputIdStudent, 1, 30);

		string id_student = "";
		gotoXY(getXScreen() / 2 - 30, 11);
		ShowCur(true);


		//bool isSave = false;
		InputSearchStudent(id_student, isSave);
		if (isSave == true) {

			if (SearchStudentById(list_student, id_student)) {
				clrscr();
				int year = 0, semester = 0;
				DisplayEdit(keySearchCredit, 2, 30);
				gotoXY(X_ADD + 2, Y_ADD - 3);
				cout << "NHAP DIEU KIEN DE DANG KI , BAM F10 DE TIM" << endl;
				Display(keyDisplayCreditClass, 8);
				InputSearchCreditClass(l, year, semester, isSave);
				if (isSave == true) {
					//clrscr();
					OutputListChooseCreditClass(l, t, year, semester, id_student);
				}
			}
			else {
				gotoXY(getXScreen() / 2 - 30, 11);
				cout << setw(50) << setfill(' ') << " ";
				gotoXY(getXScreen() / 2 - 30, 30);
				SetColor(ColorCode_Red);
				cout << "MA SINH VIEN KHONG TON TAI , MOI BAN NHAP LAI, NHAN ENTER DE NHAP LAI";
				if (key == KEY_ESC) {
					break;
				}
			}
		}
		else {
			clrscr();
			break;
		}
		if (key == KEY_ESC) {
			clrscr();
			break;
		}

	}
}

// OUTPUT LIST REGISTER

//REGISTER _DS liên kết kép .




//REGISTER_STUDENT* ListRegister[100];
//int nRegister = 0;
//
//
//void InsertCreditClassToTemp(REGISTER_STUDENT data) {
//	if (nRegister < 100) {
//		ListRegister[nRegister++] = new REGISTER_STUDENT(data);
//	}
//}
struct DisplayNodeRegister {

	REGISTER_STUDENT* data;
	DisplayNodeRegister* next = NULL;
	DisplayNodeRegister* prev = NULL;
};
struct ListRegisterDisplay {
	int nStudent = 0;
	DisplayNodeRegister* first = NULL;
	DisplayNodeRegister* last = NULL;
};

void insertLast(ListRegisterDisplay& l, REGISTER_STUDENT* data) {
	DisplayNodeRegister* ins = new DisplayNodeRegister;
	ins->data = data;
	if (l.first == NULL) {
		l.first = l.last = ins;
	}
	else {
		l.last->next = ins;
		ins->prev = l.last;
		l.last = ins;
	}
	l.nStudent++;
}

void insertListRegisterTemp(ListRegisterDisplay& l, LIST_REGISTERSTUDENT ds) {

	for (NODE_REGISTERSTUDENT* run = ds.pHead; run != NULL; run = run->pNext) {
		insertLast(l, &run->_registerStudent);//lay dia chi
	}
}

void clearAllRegisterDisplay(ListRegisterDisplay& l) {
	l.last = NULL;
	DisplayNodeRegister* del;
	while (l.first != NULL) {
		del = l.first;
		l.first = l.first->next;
		delete del;
	}
}

DisplayNodeRegister* endList(DisplayNodeRegister* first) {
	DisplayNodeRegister* run = first;
	for (int i = 0; i < QUALITYSTUDENT && run != NULL; i++, run = run->next) {
		if (run->next != NULL) {
			break;
		}
	}
	return run;
}


bool checkDot(string score) {
	for (int i = 0; i < score.size(); i++) {
		if (score[i] == '.')
			return false;
	}
	return true;
}

void InputAddScore(string& score, int& key, int line, DisplayNodeRegister* select) {
	SetBGColor(ColorCode_Blue);
	SetColor(ColorCode_White);
	string scoreTemp = score;
	gotoXY(xKeyDisplay[2] + 1, Y_DISPLAY + line);
	cout << string(string("Chua nhap diem").size(), ' ');
	do {
		gotoXY(xKeyDisplay[2] + 1, Y_DISPLAY + line);
		cout << score << " \b";
		key = _getch();
		if (key == KEY_BACKSPACE) {
			if (scoreTemp.size()) {
				scoreTemp = scoreTemp.substr(0, scoreTemp.size() - 1);
			}
		}
		else if (scoreTemp.size() < 3) {
			if ((key >= '0' && key <= '9') || (key == '.' && scoreTemp.size() != 0 && checkDot(scoreTemp))) {
				scoreTemp.push_back(key);
			}
		}
		if (atof(scoreTemp.c_str()) <= 10) {
			score = scoreTemp;
		}
		else {
			scoreTemp = score;
		}
		if (key == KEY_ENTER && score != "") {
			select->data->point = atof(score.c_str());
			break;
		}
	} while (key != KEY_ESC);
	key = 0;
}

void displayRegisterTemp(ListRegisterDisplay l, DisplayNodeRegister* select, ListStudent list_student, int& line) {
	DisplayNodeRegister* run = l.first;
	for (int i = 0; run != NULL; run = run->next, i++) {
		if (run == select) {
			SetColor(ColorCode_White);
			SetBGColor(ColorCode_Blue);
			line = i;
		}
		else {
			//mau neu khong chon
			SetColor(ColorCode_Blue);
			SetBGColor(ColorCode_White);
		}
		//gotoXY(X_DISPLAY, Y_DISPLAY +i++);
		//xuat
		DeleteOldData(sizeof(keyAddScore) / sizeof(string), i);
		gotoXY(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + i); cout << run->data->idStudent;
		NodeStudent* a = FindStudent(list_student, run->data->idStudent);
		gotoXY(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + i); cout << a->data.firstName << " " << a->data.lastName;
		gotoXY(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + i);
		if (run->data->point == -1) {
			cout << "Chua nhap diem";
		}
		else {
			cout << run->data->point;
		}

	}
}

void ControlChooseAddScore(LIST_CREDITCLASS& list, TREE_SUBJECT t, ListStudent list_student, string id_student, int year, int semester, int group) {
	PTR_CREDITCLASS cc = FindCrediClassWithConditionReturn(list, id_student, year, semester, group);

	int key = 0;
	ListRegisterDisplay l;
	insertListRegisterTemp(l, cc->listRegisterStudent);
	if (l.first != NULL) {
		int line;
		
		DisplayNodeRegister* select = l.first;
		while (key != KEY_ESC) {
			//OutputListRegister(cc->listRegisterStudent, list_student, select);
			displayRegisterTemp(l, select, list_student, line);
			key = _getch();
			if (key == KEY_CONTROL) {
				key = getch();
				if (key == KEY_UP) {
					if (select->prev != NULL) {
						select = select->prev;
					}
				}
				else if (key == KEY_DOWN) {
					if (select->next != NULL) {
						select = select->next;
					}
				}
			}
			else if (key == KEY_ENTER) {
				string score = "";
				InputAddScore(score, key, line + 3, select);
			}
			if (key == KEY_ESC) {
				clrscr();
				return;
			}
		}
	}
	else {
		SetColor(ColorCode_Red);
		while (key != KEY_ESC){
			gotoXY(X_NOTIFY, Y_NOTIFY); cout << "KHONG CO SINH VIEN NAO DK ";
			key = getch();
		
		}
	}




}
void managerAddScore(LIST_CREDITCLASS& list, TREE_SUBJECT t, ListStudent list_student) {
	clrscr();
	int key = 0;
	bool isSave = false;
	Logo();
	Display(keyAddScore, 3);
	int select = 0;
	gotoXY(X_ADD + 2, Y_ADD - 3);
	cout << "NHAP DIEU KIEN DE XUAT DANH SACH, BAM F10 DE TIM" << endl;
	string id_subject = "";
	int year = 0, semester = 0, group = 0;
	DisplayEdit(keySearchOnlyCredit, 4, 40);
	InputSearchListRegister(list, id_subject, year, semester, group, isSave, key);
	if (key != KEY_ESC) {
		gotoXY(X_DISPLAY, Y_DISPLAY - 2);
		cout << "Mon hoc: " << FindSubject(t, id_subject)->data.nameSubject << " | " << "Nien khoa: " << year << " | " << "Nhom :" << group << " | " << "Hoc ki: " << semester;
		ControlChooseAddScore(list, t, list_student, id_subject, year, semester, group);
	}

}


///=========================================@@@@@@@@@@@@@@@@@@2
void ManagerListCreditClassMain(LIST_CREDITCLASS& l, TREE_SUBJECT t) {

	int select = 0, key = 0;
	if (l.n != 0) {
		while (key != KEY_ESC) {
			ShowCur(false);
			Display(keyDisplayCreditClass, 8);
			ViewCreditClass(l, t, select);
			key = _getch();
			if (key == KEY_CONTROL) {
				key = getch();
				if (key == KEY_UP) {
					if (select != 0) {
						select--;
					}
				}
				else if (key == KEY_DOWN) {
					if (select != l.n - 1) {
						select++;
					}
				}
			}
			if (key == KEY_F2) {
				CREDITCLASS cc;
				DisplayEdit(keyDisplayCreaditClassEdit, sizeof(keyDisplayCreaditClassEdit) / sizeof(string), 35);
				InputCreditClass(l, cc, t);
				/*if (key == KEY_ESC) {
					break;
				}*/
			}
			else if (key == KEY_F3) {
				gotoXY(X_NOTIFY, Y_NOTIFY);
				//cout << setw(50) << setfill(' ') << " ";							
				bool isDeleted = DeleteCreditClassIsSuccess(l, l.listCreditClass[select]->idClass);
				if (!isDeleted)
				{
					gotoXY(X_NOTIFY + 10, Y_NOTIFY);
					cout << "Xoa that bai." << endl;
					gotoXY(X_NOTIFY + 10, Y_NOTIFY + 1);
					//cout << "Nhap phim bat ky de tiep tuc ";
					//_getch();
					break;
				}
				else
				{
					clrscr();
					gotoXY(X_NOTIFY, Y_NOTIFY);
					cout << "Xoa thanh cong";
				}

			}
			else if (key == KEY_F4) {
				gotoXY(X_ADD, 40);
				DisplayEdit(keyDisplayCreaditClassEdit, sizeof(keyDisplayCreaditClassEdit) / sizeof(string), 35);
				InputCreditClass(l, *l.listCreditClass[select], t, true);
				gotoXY(X_ADD + 10, Y_ADD);
				cout << "SUA THANH CONG ROI";
			}
			if (key == KEY_ESC) {
				clrscr();
				return;
			}
			/*	else if (key == KEY_ENTER) {
					if (CheckRegisterIsExist(listTemp.listCreditClass[select], id_student) == true) {
						gotoXY(X_NOTIFY, Y_NOTIFY);

					}
					InsertOrderToListRegister(listTemp.listCreditClass[select]->listRegisterStudent, InitNodeRegisterStudent({ id_student , 0.0 }));
				}*/
		}

	}
}



float getAverageScore(LIST_CREDITCLASS list, string id_student) {
	float sumScore = 0, count = 0;
	for (int i = 0; i < list.n; i++) {
		for (NODE_REGISTERSTUDENT* run = list.listCreditClass[i]->listRegisterStudent.pHead; run != NULL; run = run->pNext) {
			if (run->_registerStudent.idStudent == id_student) {
				count++;
				sumScore += run->_registerStudent.point;
			}
		}
	}
	if (count == 0) {
		return 0;
	}
	return sumScore / count;
}

void OutputAverageScore(LIST_CREDITCLASS list, ListStudent list_student) {
	clrscr();
	int key = 0;
	bool isSave = false;

	//key = _getch();
	while (key != KEY_ESC) {


		SetColor(ColorCode_Blue);
		gotoXY(getXScreen() / 2 - 30, 10);

		cout << "NHAP LOP CAN XUAT DANH SACH" << endl;
		gotoXY(getXScreen() / 2 - 30, 12);
		cout << "========================";
		//DisplayEdit(keyInputIdStudent, 1, 30);

		string id_class = "";
		gotoXY(getXScreen() / 2 - 30, 11);
		ShowCur(true);


		//bool isSave = false;
		InputSearchClass(id_class, isSave);
		if (isSave == true) {
			//clrscr();

			if (SearchClassById(list_student, id_class)) {
				system("cls");
				ShowCur(false);
				int i = 0;
				Display(keyAverageScore, 5);
				for (NodeStudent* run = list_student.pHead; run != NULL; run = run->pNext, i++) {
					if (run->data.idClass == id_class) {
						DeleteOldData(sizeof(keyAverageScore) / sizeof(string), i);
						gotoXY(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + i); cout << i;
						gotoXY(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + i); cout << run->data.idStudent;
						//NodeStudent* a = FindStudent(list_student, run->data->idStudent);
						gotoXY(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + i); cout << run->data.firstName;
						gotoXY(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + i); cout << run->data.lastName;
						gotoXY(xKeyDisplay[4] + 1, Y_DISPLAY + 3 + i); cout << getAverageScore(list, run->data.idStudent);

					}
				}
			}
			else {
				gotoXY(getXScreen() / 2 - 30, 11);
				cout << setw(50) << setfill(' ') << " ";
				gotoXY(getXScreen() / 2 - 30, 30);
				SetColor(ColorCode_Red);
				cout << "MA LOP KHONG TON TAI HOAC BAN NHAP SAI, MOI BAN NHAP LAI, NHAN ENTER DE NHAP LAI";
				if (key == KEY_ESC) {
					break;
				}
			}
		}
		else {
			clrscr();
			break;
		}
		if (key == KEY_ESC) {
			clrscr();
			break;
		}

	}

}
//đọc ghi file 
void ReadCreditClass(LIST_CREDITCLASS& list_credit_class, ifstream& f)
{
	string line;
	int n;
	string temp;
	while (!f.eof()) {
		CreditClass credit_class;
		getline(f, line);
		if (line != "") {
			n = 0;
			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.idClass = atoi(temp.c_str());

			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.idSubject = temp;

			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.shoolYear = atoi(temp.c_str());

			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.semester = atoi(temp.c_str());
			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.group = atoi(temp.c_str());
			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.studentMax = atoi(temp.c_str());
			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.studentMin = atoi(temp.c_str());
			while (line.size() > n) {
				temp = "";
				REGISTER_STUDENT data;
				for (int i = 0; line[n] != ','; i++, n++) {
					temp.push_back(line[n]);
				}
				n++;
				data.idStudent = temp;
				temp = "";
				for (int i = 0; line[n] != ','; i++, n++) {
					temp.push_back(line[n]);
				}
				n++;
				data.point = atof(temp.c_str());
				temp = "";
				InsertOrderToListRegister(credit_class.listRegisterStudent, InitNodeRegisterStudent(data));
			}
			InsertCreditClass(list_credit_class, credit_class);
		}
		else {
			break;
		}
	}
}
void ReadFileCreditClass(LIST_CREDITCLASS& list)
{
	ifstream f("creditclass.txt");
	if (f.is_open()) {

		ReadCreditClass(list, f);
		f.close();
	}
}
void WriteFileCreditClass(ListCreaditClass list)
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
	ofstream f("creditclass.txt");
	if (f.is_open()) {
		PTR_CREDITCLASS* credit_class;
		for (int i = 0; i < list.n; i++) {
			f << list.listCreditClass[i]->idClass << "," <<
				list.listCreditClass[i]->idSubject << "," <<
				list.listCreditClass[i]->shoolYear << "," <<
				list.listCreditClass[i]->semester << "," <<
				list.listCreditClass[i]->group << "," <<
				list.listCreditClass[i]->studentMax << "," <<
				list.listCreditClass[i]->studentMin << ",";
			for (NodeRegisterStudent* run = list.listCreditClass[i]->listRegisterStudent.pHead; run != NULL; run = run->pNext) {
				f << run->_registerStudent.idStudent << "," << run->_registerStudent.point << ",";
			}
			f << endl;
		}
		f.close();
	}
}