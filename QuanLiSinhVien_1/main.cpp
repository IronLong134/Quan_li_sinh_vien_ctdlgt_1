﻿#pragma once
#include"subject.h"
#include "student.h"
#include"creditclass.h"

string Menu[5] = { "Hieu chinh mon hoc","Hieu chinh sinh vien","Hieu chinh lop tin chi","Dang ki mon hoc cho sv","Thoat" };

void menuMain() {

	//Ve_Khung(50, 14, 60, 60);

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
	PTR_LISTCREDITCLASS list_credit_class = new LIST_CREDITCLASS;
	////ReadFileCreditClass(list_credit_class);
	//MenuManageCreditClass(list_credit_class,t);
	//cout << "Aaaaaaaa" << endl;

	int select = 0;//biến chọn
	int key = 0;
	while (true)
	{
        
		logoName();
		Xu_Li_Con_Tro_Chi_Vi(0);
		loadMenu(Menu, select, 5, (getXScreen() - 40) / 2, 20, ColorCode_White, ColorCode_Blue);
		
		//hienThiMenu(thongTinMenuMonHoc, 0, 2, 4, 25, ColorCode_White, ColorCode_Cyan);
		//hienThiThongTinMonHoc(mhtt, 0, 0, ColorCode_Cyan);
		key = _getch();
		changeSelectMenu(select, 6, key);
		if (key == KEY_ENTER) {
			if (select == 4) {
				return ;
			}
			else if (select == 0) {
				/*loadMenu(Menu, select, 6, 4, 11, ColorCode_White, ColorCode_Cyan);*/
				clrscr();
				ReadFileSubject(t);
				MenuSubjectManager(t);
				WriteFileSubject(t);
				clrscr();
			}
			else if (select == 1) {
				clrscr();
				ReadFileStudent(ds);
				mainStudent(ds);
				WriteFileStudent(ds);
				clrscr();

			}
			else if (select == 2) {
				clrscr();
				MenuManageCreditClass(list_credit_class,t);
				ReadFileCreditClass(list_credit_class);
				clrscr();
			}
		}
	}
	system("pause");
	return ;
}