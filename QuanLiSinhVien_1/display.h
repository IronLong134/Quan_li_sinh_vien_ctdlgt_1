#pragma once
#include"console.h"
using namespace std;
#include"lib.h"
string keyDisplaySubject[4] = { "Ma MH:", "Ten MH:", "So TCLT:", "So TCTH:" };
string keyDisplayCreditClass[8] = { "Ma LopTC:","Ten MH:","Ma MH:","Nien khoa:","Hoc ki:","Nhom:","SVMax:","SVMin:" };
string keyDisplayCreaditClassEdit[6] = { "Ma MH:", "NK:", "Hoc Ki:", "Nhom:", "SVMax:", "SVMin:" };
string keyDisplayStudent[6] = { "Ma SV:", "Ho:", "ten:", "gioi","SDT","khoa" };
string KeyInputClass[1] = { "ma lop:" };
string keyInputIdStudent[1] = { "ma sv:" };
int xKeyDisplay[9] = { 5,25,65,85,100, 110, 120, 140, 150 };//20 40 70 80 90 120 150 

void logoName()
{
	/*
	.___                       .____
|   |______  ____   ____   |    |    ____   ____    ____
|   \_  __ \/  _ \ /    \  |    |   /  _ \ /    \  / ___\
|   ||  | \(  <_> )   |  \ |    |__(  <_> )   |  \/ /_/  >
|___||__|   \____/|___|  / |_______ \____/|___|  /\___  /
					   \/          \/          \//_____/
	*/
	int batDau = (getXScreen() - 55) / 2;
	SetColor(ColorCode_Blue);
	SetBGColor(ColorCode_White);
	gotoXY(batDau, 3);
	cout << ".___                       .____                       ";
	gotoXY(batDau, 4);
	cout << "|   |______  ____   ____   |    |    ____   ____    ____  ";
	gotoXY(batDau, 5);
	cout << "|   \\_  __ \\/  _ \\ /    \\  |    |   /  _ \\ /    \\  / ___\\";
	gotoXY(batDau, 6);
	cout << "|   ||  | \\(  <_> )   |  \\ |    |__(  <_> )   |  \\/ /_/  >";
	gotoXY(batDau, 7);
	cout << "|___||__|   \\____/|___|  / |_______ \\____/|___|  /\\___  / ";
	gotoXY(batDau, 8);
	cout << "                       \\/          \\/          \\//_____/   ";
}
void Logo() {
	int Start = (getXScreen() - 65) / 2;
	
	gotoXY(Start, 3);
	cout << "                        ___       _      __          _ ";
	gotoXY(Start, 4);
	cout << " ___ ___ _____ ____    / (_) ___ (_)__  / /    _  __(_)__ ___ ";
	gotoXY(Start, 5);
	cout << "/ _ `/ // / _ `/ _ \\  / / / (_-</ / _ \\/ _ \\  | |/ / / -_) _ \\";
	gotoXY(Start, 6);
	cout << "\\_, /\\_,_/\\_,_/_//_/ /_/_/ /___/_/_//_/_//_/  |___/_/\\__/_//_/";
	gotoXY(Start, 7);
	cout << " /_/ ";
}
void changeSelectMenu(int& select, int max, int key) { // thay đổi lựa chọn
	if (key == KEY_CONTROL) {
		key = _getch();
		if (key == KEY_UP) {
			if (select == 0) {
				select = max - 1;
			}
			else {
				select--;
			}
		}
		else if (key == KEY_DOWN) {
			if (select == max - 1) {
				select = 0;
			}
			else {
				select++;
			}
		}
	}
}
void loadMenu(string menu[], int select, int n, int x, int y, int textColor, int bgColor) { // hiển thị menu
	//int n= sizeof(menu) / sizeof(string);
	for (int i = 0; i < n; i++) {
		gotoXY(x, y + i);
		if (i == select) {
			SetColor(textColor);
			SetBGColor(bgColor);
		}
		else {
			SetColor(ColorCode_Black);
			SetBGColor(ColorCode_White);
		}
		cout << canGiuaChuoi(menu[i], 40);
	}
}

void DeleteNote(int nColumn) // xoá ảo
{
	gotoXY(xKeyDisplay[0] + 1, Y_DISPLAY + 40);
	cout << setw(xKeyDisplay[nColumn] - xKeyDisplay[0] - 1) << " " << setfill(' ');
}
void CreateBox(int x, int y, string text, int length)
{
	gotoXY(x - 2, y - 1);
	cout << char(201) << setw(length) << setfill(char(205)) << char(205) << char(187);

	gotoXY(x - 2, y);
	cout << char(186) << text << setw(length - text.length() + 1) << setfill(' ') << char(186);

	gotoXY(x - 2, y + 1);
	cout << char(200) << setw(length) << setfill(char(205)) << char(205) << char(188);
}
void Display(string key[], int nKey)
{
	SetColor(ColorCode_Blue);
	SetBGColor(ColorCode_White);
	Logo();

	
	//show key
	for (int i = 0; i < nKey; i++)
	{
		gotoXY(xKeyDisplay[i] + 3, Y_DISPLAY + 1);
		cout << key[i];
	}

	//show column 2 side
	for (int j = Y_DISPLAY; j <= Y_DISPLAY + 40; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoXY(xKeyDisplay[i], j);
			cout << char(186);
		}
	}

	//border left->right
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nKey]; i++)
	{
		//border top (key)
		gotoXY(i, Y_DISPLAY);
		if (i == xKeyDisplay[1] || i == xKeyDisplay[2] || i == xKeyDisplay[3] || i == xKeyDisplay[4])
			cout << char(203);//nga 3
		else if (i == xKeyDisplay[0])
		{
			cout << char(201); //moc phai
		}
		else if (i == xKeyDisplay[nKey])
		{
			cout << char(187);//moc trai
		}
		else
		{
			cout << char(205); //duong thang ngang
		}

		//border bottom(key)
		gotoXY(i, Y_DISPLAY + 2);
		if (i == xKeyDisplay[1] || i == xKeyDisplay[2] || i == xKeyDisplay[3] || i == xKeyDisplay[4])
			cout << char(206); //nga 4
		else if (i == xKeyDisplay[0])
		{
			cout << char(204); //nga 3 sang phai
		}
		else if (i == xKeyDisplay[nKey])
		{
			cout << char(185);//nga 3 sang trai
		}
		else
		{
			cout << char(205); //duong thang ngang
		}


		//border top (note)
		gotoXY(i, Y_DISPLAY + 39);
		if (i == xKeyDisplay[nKey])
		{
			cout << char(185); //nga 3 sang trai
		}
		else if (i == xKeyDisplay[1] || i == xKeyDisplay[2] || i == xKeyDisplay[3] || i == xKeyDisplay[4])
			cout << char(202);
		else if (i == xKeyDisplay[0])
			cout << char(204); //nga 3 sang phai
		else
		{
			cout << char(205); //duong thang ngang
		}


		//border bottom (note)
		gotoXY(i, Y_DISPLAY + 41);
		if (i == xKeyDisplay[0])
		{
			cout << char(200); //qeo sang phai
		}
		else if (i == xKeyDisplay[nKey])
		{
			cout << char(188); //qeo sang trai
		}
		else
		{
			cout << char(205); //duong thang ngang
		}
	}
	// SHOW note
	gotoXY(xKeyDisplay[0] + 1, Y_DISPLAY + 40);
	cout << setw(xKeyDisplay[nKey] - xKeyDisplay[0] - 1) << "F2: them F3: Xoa F4: Hieu Chinh F10: Save" << setfill(' ');
}
void DeleteOldData(int nKey, int locate)
{
	for (int i = 0; i < nKey; i++)
	{
		gotoXY(xKeyDisplay[i] + 1, Y_DISPLAY + 3 + locate);
		cout << setw(xKeyDisplay[i + 1] - xKeyDisplay[i] - 2) << setfill(' ') << " ";
	}
}
void DisplayEdit(string key[], int nKey, int length)
{
	int yAdd = Y_ADD;
	for (int i = 0; i < nKey; i++)
	{
		CreateBox(X_ADD + 15 + 7, yAdd, key[i], length);
		yAdd += 3;
	}
}
void TutorialStudent() {
	Ve_Khung(X_ADD-2, Y_ADD+25, 65, 40);
	gotoXY(X_ADD, Y_ADD + 27); cout << string(26,' ')<<"HUONG DAN";
	gotoXY(X_ADD, Y_ADD + 30); cout << "F1:tim kiem lop";
	gotoXY(X_ADD, Y_ADD + 30+2); cout << "F2:Them sinh vien vao lop hien tai";
	gotoXY(X_ADD, Y_ADD + 30+4); cout << "F3:Them lop moi";
	gotoXY(X_ADD, Y_ADD + 30+6); cout << "F4:Xoa sinh vien trong lop do(khong the xoa het ds)";
	gotoXY(X_ADD, Y_ADD + 30 + 8); cout << "F5:Xoa mot lop, tat ca sinh vien trong lp se mat ";
	gotoXY(X_ADD, Y_ADD + 30 + 10); cout << "F10: Luu them va sua ";
	gotoXY(X_ADD, Y_ADD + 30 + 12); cout << "ESC: Huy bo thao tac ";
}
void DeleteMenuAdd()
{

	for (int i = 0; i < 20; i++)
	{
		gotoXY(X_ADD + 2, Y_ADD + i - 1);
		cout << setw(60) << setfill(' ') << " ";
	}
}