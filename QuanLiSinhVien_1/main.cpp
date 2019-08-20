#pragma once
#include"subject.h"
#include "student.h"
#include"creditclass.h"

string Menu[8] = { "HIEU CHINH MON HOC","HIEU CHINH SINH VIEN","HIEU CHINH LOP TIN CHI","DANG KI MON HOC CHO SINH VIEN","DANH SACH DANG KI","IN DANH SACH DIEM TB","IN DANH SACH TONG HOP","THOAT" };

void menuMain() {

	//Ve_Khung(50, 14, 60, 60);

}


void init(string* logo) {
	drawLogo(getYScreen(), logo);
	if (_getch() == KEY_CONTROL) {
		_getch();
	}
	int  screen = getXScreen() - 2;
	for (int i = getYScreen(); i > 2; i--) {
		drawLogo(i, logo);
		gotoXY(1, i + 6);
		cout << string(screen, ' ');
		Sleep(10);
	}

}
void main() {
	system("color F0");

	fullScreen();
	TREE_SUBJECT t;
	InitTreeSubject(t);
	//menuMain();
	////SUBJECT mh;
	////mh.idSubject = "ctdl";
	////mh.nameSubject = "cautruc";
	////mh.numberTheory = 1;
	////mh.numberPratice = 3;
	////InsertSubjectToTree(t, mh);

	/*
	string idStudent; // tối đa 10 kí tự
	string firstName; // tối đa 15 kí tự
	string lastName; // tối đa 20 kí tự
	int gender; // tối đa 5 kí tự
	string phoneNumber; // tối đa 11 kí tự
	string idClass;
	int yearJoin;
	*/

	ListStudent ds;

	//mainStudent(ds);
	//WriteFileStudent(ds);
	LIST_CREDITCLASS list_credit_class;
	////ReadFileCreditClass(list_credit_class);
	//MenuManageCreditClass(list_credit_class,t);
	//cout << "Aaaaaaaa" << endl;

	int select = 0;//biến chọn
	int key = 0;
	ReadFileSubject(t);
	ReadFileStudent(ds);
	ReadFileCreditClass(list_credit_class);
	string *logo = new string[6];
	Xu_Li_Con_Tro_Chi_Vi(0);
	logoName(logo);
	init(logo);
	while (true)
	{
		ShowCur(false);
		drawLogo(3, logo);
		//clrscr();
		Ve_Khung((getXScreen() - 55) / 2, 14, 55, 25);
		loadMenu(Menu, select, 8, (getXScreen() - 40) / 2, 20, ColorCode_White, ColorCode_Blue);

		//hienThiMenu(thongTinMenuMonHoc, 0, 2, 4, 25, ColorCode_White, ColorCode_Cyan);
		//hienThiThongTinMonHoc(mhtt, 0, 0, ColorCode_Cyan);
		key = _getch();
		changeSelectMenu(select, 8, key);
		if (key == KEY_ENTER) {
			if (select == 7) {
				break;
			}
			else if (select == 0) {


				/*loadMenu(Menu, select, 6, 4, 11, ColorCode_White, ColorCode_Cyan);*/
				clrscr();
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);

				MenuSubjectManager(t);
				WriteFileSubject(t);
			}
			else if (select == 1) {
				clrscr();
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);

				mainStudent(ds);
				WriteFileStudent(ds);

			}
			else if (select == 2) {
				clrscr();
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);

				//MenuManageCreditClass(list_credit_class, t);
				ManagerListCreditClassMain(list_credit_class, t);
				WriteFileCreditClass(list_credit_class);
			}
			else if (select == 3) {
				clrscr();
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);
				managerRegisterCreditClass(list_credit_class,ds,t);
				//OutputListChooseCreditClass(list_credit_class, t,1 ,1, "N14DCCN300" );
			}
			else if (select == 4) {
				clrscr();
				SetColor(ColorCode_Blue);
				SetBGColor(ColorCode_White);

				managerAddScore(list_credit_class,t,ds);
			}
			else if (select == 5) {
				clrscr();
				OutputAverageScore(list_credit_class, ds);
			}
			else if (select == 6) {
				clrscr();
				OutputSum(list_credit_class, ds);
			}
			SetBGColor(ColorCode_White);
			clrscr();
		}
	}
	WriteFileCreditClass(list_credit_class);
	return;
}