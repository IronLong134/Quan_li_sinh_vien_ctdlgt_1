#pragma once

#include"subject.h"
//#include"registerstudent.h"


struct CreditClass {
	unsigned int idClass;
	string idSubject; // ma mon hoc // key
	string nameSubject;
	int shoolYear; // nien khoa
	int semester; // hoc ki
	int group; // nhom
	int studentMax;
	int studentMin;

	//LIST_REGISTERSTUDENT listRegisterStudent;
};
typedef struct CreditClass CREDITCLASS;
typedef CREDITCLASS* PTR_CREDITCLASS;

struct ListCreaditClass {

	int n = 0;
	PTR_CREDITCLASS listCreditClass[5000] = { NULL };
};
typedef struct ListCreaditClass LIST_CREDITCLASS;


int totalPageCreditClass = 0;// tổng trang 
int pageNowCreditClass = 1;// page hiện tại
int currposPrecCreditClass = 0;//biến tính toán
int currposCreditClass = 0;//  biến chạy trong 1 trang

void InsertCreditClass(LIST_CREDITCLASS& l, CREDITCLASS data) {
	if (l.n < 5000) {
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

PTR_CREDITCLASS BinarySearchCreditClass(LIST_CREDITCLASS l, int n, unsigned int id)
{ // Ph?m vi ban d?u tìm ki?m là t? left=0 ?right =n-1
	int left = 0;
	int right = n;
	int j;
	while (left <= right)
	{
		j = (left + right) / 2;
		if (l.listCreditClass[j]->idClass == id) return l.listCreditClass[j];
		if (id > l.listCreditClass[j]->idClass)
			left = j + 1;
		else right = j - 1;
	}
	return NULL;
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
void DeleteCreditClass(LIST_CREDITCLASS& l, unsigned int id)
{
	int index = FindIndexClass(l, id);
	delete l.listCreditClass[index];
	if (index == -1)return;
	//if (l.listCreditClass[index]->listRegisterStudent.pHead != NULL) return;

	for (int i = index; i < l.n; i++)
	{
		l.listCreditClass[i] = l.listCreditClass[i + 1];

	}

	l.n--;

}

bool DeleteCreditClassIsSuccess(LIST_CREDITCLASS& l, unsigned int id)
{
	int index = FindIndexClass(l, id);

	if (index == -1)return false;
	//if (l.listCreditClass[index]->listRegisterStudent.pHead != NULL) return false;

	for (int i = index; i < l.n; i++)
	{
		l.listCreditClass[i] = l.listCreditClass[i + 1];

	}
	l.n--;
	return true;
}
PTR_CREDITCLASS FindCrediClassWithCondition(LIST_CREDITCLASS l, string idSubject, int shoolYear, int semester, int group)
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

//hàm input 

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
		if (key == KEY_ESC)break;
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

				cc.nameSubject = p->data.nameSubject;
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
					cc.idClass = l.listCreditClass[l.n - 1]->idClass + 1;
					////InitListRegisterStudent(cc->listRegisterStudent);
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

void OutputListCreditClassPerPage(LIST_CREDITCLASS l, TREE_SUBJECT t, int indexBegin)
{
	if (l.n == 0) return;
	for (int i = 0; i + indexBegin < l.n && i < QUANTITY_PER_PAGE; i++)
	{
		OutputCreditClass(l.listCreditClass[indexBegin + i], t, i * 2);
	}
	gotoXY(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowCreditClass << "/" << totalPageCreditClass;
}

void SetDefaultChosenCreditClass(LIST_CREDITCLASS l, TREE_SUBJECT t, int ordinal)
{
	SetBGColor(ColorCode_Green);
	OutputCreditClass(l.listCreditClass[ordinal], t, (ordinal % QUANTITY_PER_PAGE) * 2);
	SetBGColor(ColorCode_White);
}

void EffectiveMenuCreditClass(int ordinal, LIST_CREDITCLASS l, TREE_SUBJECT t)
{
	int current = ordinal;
	SetDefaultChosenCreditClass(l, t, current);
	OutputCreditClass(l.listCreditClass[currposPrecCreditClass], t, (currposPrecCreditClass % QUANTITY_PER_PAGE) * 2);
	currposPrecCreditClass = current;
}

void ChangePageCreditClass(LIST_CREDITCLASS l)
{
	clrscr();
	Display(keyDisplayCreditClass, sizeof(keyDisplayCreditClass) / sizeof(string));
	DeleteNote(sizeof(keyDisplayCreditClass) / sizeof(string));
	currposCreditClass = (pageNowCreditClass - 1) * QUANTITY_PER_PAGE;
	currposPrecCreditClass = (pageNowCreditClass - 1) * QUANTITY_PER_PAGE;

	gotoXY(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowCreditClass << "/" << totalPageCreditClass;
}

int ChooseCreditClass(LIST_CREDITCLASS l, TREE_SUBJECT t)
{
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	pageNowCreditClass = 1;
	currposCreditClass = 0;
	currposPrecCreditClass = 0;

	Display(keyDisplayCreditClass, sizeof(keyDisplayCreditClass) / sizeof(string));



	OutputListCreditClassPerPage(l, t, 0);
	SetDefaultChosenCreditClass(l, t, currposCreditClass);

	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 224)
			keyboard_read = _getch(); {
			switch (keyboard_read)
			{
			case KEY_UP:
				if (currposCreditClass % QUANTITY_PER_PAGE > 0)
				{
					currposCreditClass = currposCreditClass - 1;
					EffectiveMenuCreditClass(currposCreditClass, l, t);
				}
				break;
			case KEY_DOWN:
				if (currposCreditClass % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposCreditClass < l.n - 1)
				{
					currposCreditClass = currposCreditClass + 1;
					EffectiveMenuCreditClass(currposCreditClass, l, t);
				}
				break;
			case KEY_LEFT:
				if (pageNowCreditClass > 1)
				{
					pageNowCreditClass--;
					ChangePageCreditClass(l);
					OutputListCreditClassPerPage(l, t, (pageNowCreditClass - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenCreditClass(l, t, currposCreditClass);
				}
				break;
			case KEY_RIGHT:
				if (pageNowCreditClass < totalPageCreditClass)
				{
					pageNowCreditClass++;
					ChangePageCreditClass(l);
					OutputListCreditClassPerPage(l, t, (pageNowCreditClass - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenCreditClass(l, t, currposCreditClass);
				}
				break;
			case KEY_ESC:
				ShowCur(false);
				return -1;
				break;
			case KEY_ENTER:
				ShowCur(false);
				return currposCreditClass;
				break;
			}
		}
	}
}

void ChangePageManageCreaditClass(LIST_CREDITCLASS l, TREE_SUBJECT t)
{
	clrscr();
	gotoXY(X_TITLE, Y_TITLE); cout << "QUAN LY DANH SACH LOP TIN CHI";
	OutputListCreditClassPerPage(l, t, (pageNowCreditClass - 1) * QUANTITY_PER_PAGE);
	Display(keyDisplayCreditClass, sizeof(keyDisplayCreditClass) / sizeof(string));
}

void MenuManageCreditClass(LIST_CREDITCLASS& l, TREE_SUBJECT& t)
{
backMenu:
	clrscr();
	pageNowCreditClass = 1;
	totalPageCreditClass = 0;
	OutputListCreditClassPerPage(l, t, 0);

	Display(keyDisplayCreditClass, sizeof(keyDisplayCreditClass) / sizeof(string));
	int key;

	gotoXY(X_TITLE, Y_TITLE); cout << "QUAN LY DANH SACH LOP TIN CHI";
	gotoXY(X_PAGE, Y_PAGE);
	if (l.n % QUANTITY_PER_PAGE == 0) {
		totalPageCreditClass = l.n / QUANTITY_PER_PAGE ;
	}
	else {
		totalPageCreditClass = l.n / QUANTITY_PER_PAGE+1;
	}
	
	cout << "Trang " << pageNowCreditClass << "/" << totalPageCreditClass;
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				switch (key)
				{
				case KEY_LEFT:
					if (pageNowCreditClass > 1)
					{
						pageNowCreditClass--;
						ChangePageCreditClass(l);
						OutputListCreditClassPerPage(l, t, (pageNowCreditClass - 1) * QUANTITY_PER_PAGE);
						//SetDefaultChosenCreditClass(l, t, currposCreditClass);
					}
					break;
				case KEY_RIGHT:
					if (pageNowCreditClass < totalPageCreditClass)
					{
						pageNowCreditClass++;
						ChangePageCreditClass(l);
						OutputListCreditClassPerPage(l, t, (pageNowCreditClass - 1) * QUANTITY_PER_PAGE);
						//SetDefaultChosenCreditClass(l, t, currposCreditClass);
					}
					break;
				}
				if (key == KEY_F2)
				{
					CREDITCLASS cc;
					DisplayEdit(keyDisplayCreaditClassEdit, sizeof(keyDisplayCreaditClassEdit) / sizeof(string), 35);
					InputCreditClass(l, cc, t);

					totalPageCreditClass = l.n / QUANTITY_PER_PAGE + 1;
					pageNowCreditClass = 1;
					ChangePageManageCreaditClass(l, t);
				}
				else if (key == KEY_F3)
				{

					int k = ChooseCreditClass(l, t);
					if (k == -1) goto backMenu;

					key = _getch();

					gotoXY(X_NOTIFY, Y_NOTIFY);
					cout << setw(50) << setfill(' ') << " ";

					if (key == KEY_ENTER)
					{
						bool isDeleted = DeleteCreditClassIsSuccess(l, l.listCreditClass[k]->idClass);
						if (!isDeleted)
						{
							gotoXY(X_NOTIFY + 10, Y_NOTIFY);
							cout << "Xoa that bai." << endl;
							gotoXY(X_NOTIFY + 10, Y_NOTIFY + 1);
							cout << "Nhap phim bat ky de tiep tuc ";
							getch();
							goto backMenu;
						}
						else
						{
							clrscr();
							if ((l.n + 1) % QUANTITY_PER_PAGE == 0) pageNowCreditClass--;
							totalPageCreditClass = l.n / QUANTITY_PER_PAGE + 1;
							ChangePageManageCreaditClass(l, t);
							gotoXY(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
						}
					}
					else
						goto backMenu;
				}
				else if (key == KEY_F4)
				{
					int k = ChooseCreditClass(l, t);
					if (k == -1) goto backMenu;
					gotoXY(X_ADD, 40);
					DisplayEdit(keyDisplayCreaditClassEdit, sizeof(keyDisplayCreaditClassEdit) / sizeof(string), 35);
					InputCreditClass(l, *l.listCreditClass[k], t, true);

					ChangePageManageCreaditClass(l, t);
					gotoXY(X_NOTIFY + 10, Y_NOTIFY);
					cout << "SUA THANH CONG";
				}
				else if (key == PAGE_DOWN && pageNowCreditClass < totalPageCreditClass)
				{
					pageNowCreditClass++;
					ChangePageManageCreaditClass(l, t);
				}
				else if (key == PAGE_UP && pageNowCreditClass > 1)
				{
					pageNowCreditClass--;
					ChangePageManageCreaditClass(l, t);
				}
			}
			else if (key == KEY_ESC)
				return;
		}
	}
}

//đọc ghi file 

void ReadCreditClass(LIST_CREDITCLASS& list_credit_class, ifstream& f)
{
	string line;
	CreditClass credit_class;
	int n;
	string temp;
	while (!f.eof()) {
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
			credit_class.nameSubject = temp;
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
			for (int i = 0; n < line.size(); i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			credit_class.studentMin = atoi(temp.c_str());
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
		/*	if (!f.peek() == EOF) {
				getline(f, pass);
				docCay(t, f);
				ReadStudent(ds, f);
				f.close();
			}*/
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
		for (int i = 0; i<list.n; i++) {
			f <<list.listCreditClass[i]->idClass<<","<<
				list.listCreditClass[i]->idSubject << "," <<
				list.listCreditClass[i]->nameSubject << "," <<
				list.listCreditClass[i]->shoolYear << "," <<
				list.listCreditClass[i]->semester << "," <<
				list.listCreditClass[i]->group<< "," <<
				list.listCreditClass[i]->studentMax << "," <<
				list.listCreditClass[i]->studentMin << endl;
		}
		f.close();
	}
}