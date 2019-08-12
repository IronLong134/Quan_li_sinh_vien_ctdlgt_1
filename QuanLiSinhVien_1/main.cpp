#pragma once
#include"subject.h"
#include "student.h"
#include"creditclass.h"
int main() {
	system("color F0");

	fullScreen();
	TREE_SUBJECT t;
	
	InitTreeSubject(t);
	////SUBJECT mh;
	////mh.idSubject = "ctdl";
	////mh.nameSubject = "cautruc";
	////mh.numberTheory = 1;
	////mh.numberPratice = 3;
	////InsertSubjectToTree(t, mh);
	ReadFileSubject(t);
	//MenuSubjectManager(t);
	//WriteFileSubject(t);
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
	ReadFileStudent(ds);
	mainStudent(ds);
	WriteFileStudent(ds);
	//PTR_LISTCREDITCLASS list_credit_class = new LIST_CREDITCLASS;
	//MenuManageCreditClass(list_credit_class,t);
	//cout << "Aaaaaaaa" << endl;

	system("pause");
	return 0;
}