#pragma once
#include"console.h"
#include"display.h"
#include"validation.h"

struct Subject
{
	string idSubject;
	string nameSubject;
	int numberTheory;
	int numberPratice;

};
typedef struct Subject SUBJECT;
struct NodeSubject
{
	SUBJECT data;
	struct NodeSubject* pLeft;
	struct NodeSubject* pRight;
};
typedef struct NodeSubject NODE_SUBJECT;
typedef NODE_SUBJECT* TREE_SUBJECT;
TREE_SUBJECT binaryTree = NULL;
TREE_SUBJECT rp;



SUBJECT listSubjectName[MAXLISTSUBJECT];
int nSubject = 0;
//struct ListSubjectName {
//	SUBJECT data[MAXLISTSUBJECT];
//	int nSubject = 0;
//};
//typedef struct ListSubjectName ListSubjectName;

void InitTreeSubject(TREE_SUBJECT& t) {
	t = NULL;

}
void DeleteInListSubjectName(string id_subject) {

	for (int i = 0; i < nSubject; i++) {
		if (listSubjectName[i].idSubject == id_subject) {
			for (int j = i + 1; j < nSubject; j++)
			{
				listSubjectName[j - 1] = listSubjectName[j];
			}
			nSubject--;
			break;
		}
	}

}
void insertOder(SUBJECT subject) // hàm cho mảng theo ten môn học
{
	if (nSubject < MAXLISTSUBJECT) {
		int n = 0;
		while (n < nSubject) { //chi de tang n neu du dk la tenMh lon hon ten mon hoc cuoi cung
			if (subject.nameSubject < listSubjectName[n].nameSubject) {
				break;
			}
			n++;
		}
		nSubject++;
		for (int i = nSubject - 1; i > n; i--) {
			listSubjectName[i] = listSubjectName[i - 1];
		}

		listSubjectName[n] = subject;
	}
}

void InsertSubjectToTree(TREE_SUBJECT& t, SUBJECT subject) {

	if (t == NULL)
	{
		NODE_SUBJECT* p = new NODE_SUBJECT;
		p->data = subject;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p;

		insertOder(subject);
	}
	else
	{

		if (subject.idSubject < t->data.idSubject)
		{
			InsertSubjectToTree(t->pLeft, subject);
		}
		else if (subject.idSubject > t->data.idSubject)
		{
			InsertSubjectToTree(t->pRight, subject);
		}
	}


}



void FindReplace(NODE_SUBJECT*& del, NODE_SUBJECT*& Y) { //del la not xoa , y là not thay the
	// CÁCH 1: TÌM NODE TRÁI NHẤT CỦA CÂY CON PHẢI
	// duyệt sang bên trái nhất
	if (Y->pLeft != NULL)
	{
		FindReplace(del, Y->pLeft);// tìm ra node trái nhất ?
	}
	else // tìm ra được node trái nhất rồi nek..
	{
		del->data = Y->data; // cập nhật cái data của node cần xóa chính là data của node thế mạng
		del = Y; // cho node X(là node mà chúng ta sẽ đi xóa sau này) trỏ đến node thế mạng ==> ra khỏi hàm thì ta sẽ xóa node X
		Y = Y->pRight; // bản chất chỗ này chính là cập nhật lại mối liên kết cho node cha của node thế mạng(mà chúng ta sẽ xóa) với node con của node thế mạng	
	}
}
bool DeleteNodeSubject(TREE_SUBJECT& t, string id_subject) {
	// nếu như cây đang rỗng
	if (t == NULL)
	{
		return false; // kết thúc hàm
	}
	else
	{
		// nếu như data nhỏ hơn node gốc
		if (t->data.idSubject > id_subject)
		{
			DeleteNodeSubject(t->pLeft, id_subject); // duyệt sang nhánh trái của cây 
		}
		else if (t->data.idSubject < id_subject)
		{
			DeleteNodeSubject(t->pRight, id_subject); // duyệt sang nhánh phải của cây 
		}
		else // data == list_subject->data - đã tìm ra cái node cần xóa
		{
			NODE_SUBJECT* X = t; // node X là node thế mạng -sẽ xóa
			// nếu như nhánh trái bằng NULL <=> đây là cây có 1 con chính là con phải
			if (t->pLeft == NULL)
			{
				// duyệt sang phải của cái node cần xóa để cập nhật mối liên kết giữa node 
				// cha của node cần xóa với node con của node cần xóa
				t = t->pRight;
			}
			else if (t->pRight == NULL)
			{
				// duyệt sang trái của cái node cần xóa để cập nhật mối liên kết giữa node 
				// cha của node cần xóa với node con của node cần xóa
				t = t->pLeft;
			}
			else // node cần xóa là node có 2 con
			{
				// CÁCH 1: Tìm node trái nhất của cây con phải(cây con phải của cái node cần xóa)
				FindReplace(X, t->pRight);
				// CÁCH 2: Tìm node phải nhất của cây con trái(cây con trái của cái node cần xóa)
				//DiTimNodeTheMang(X, list_subject->pLeft);
			}
			delete X; // xóa node cần xóa
			return true;
		}
	}
}

NODE_SUBJECT* FindSubject(TREE_SUBJECT t, string id_subject) //return search = null if not found
{
	if (t != NULL)
	{
		NODE_SUBJECT* search = t;
		while (search != NULL)
		{
			if (id_subject == search->data.idSubject)
				return search;
			else if (id_subject > search->data.idSubject)
				search = search->pRight;
			else
				search = search->pLeft;
		}
	}
	return NULL;
}
//Giao diện ======================================
void OutputOneSubject(SUBJECT subject, int locate) // vi tri == locate
{
	DeleteOldData(sizeof(keyDisplaySubject) / sizeof(string), locate);
	gotoXY(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << subject.idSubject;
	gotoXY(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << subject.nameSubject;
	gotoXY(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); cout << subject.numberTheory;
	gotoXY(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate); cout << subject.numberPratice;
}
void OutputListSubject(int locationStart) {   // locationStart là vị trí bắt đầu xuất 
	for (int i = 0; i + locationStart < nSubject && i < 10; i++) {
		OutputOneSubject(listSubjectName[i + locationStart], i * 2);
	}
}


void OutputListSubjectPerPage(TREE_SUBJECT t, int indexBegin)
{
	for (int i = 0; i + indexBegin < nSubject && i < QUANTITY_PER_PAGE; i++)// điều kiện, i là vị trí tại chỗ , + indexbegin phải nhỏ hơn số môn học, và vị trí đó ko lớn quá số trog 1 trang
	{


		NODE_SUBJECT* subject = FindSubject(t, listSubjectName[i + indexBegin].idSubject);
		//if(subject == NULL) cout << "Fail";

		OutputOneSubject(subject->data, i * 2);
	}
	gotoXY(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowSubject << "/" << totalPageSubject;
}


void SetDefaultChosenSubject(SUBJECT p, int ordinal)// ordinal : vị trí.. hàm xác định vị trí của phần tử tại trang đó 
{
	SetBGColor(ColorCode_Green);
	OutputOneSubject(p, ordinal % QUANTITY_PER_PAGE);
	SetBGColor(ColorCode_White);
}

void EffectiveMenuSubject(int index, SUBJECT newSubject, SUBJECT oldSubject)
{
	int current = index;//hiện tại

	SetBGColor(ColorCode_Green);
	OutputOneSubject(newSubject, (current % QUANTITY_PER_PAGE) * 2);  // để cho vị trí xuống ko bị chồng lên nhau 
	SetBGColor(ColorCode_White);
	OutputOneSubject(oldSubject, (currposPrecSubject % QUANTITY_PER_PAGE) * 2); // xuất môn cũ 
	currposPrecSubject = current;// lưu lại vị trí hiện tại là vị trí cũ 
}

void ChangePageSubject(TREE_SUBJECT t)
{
	currposSubject = (pageNowSubject - 1) * QUANTITY_PER_PAGE; // lấy vị trí đầu tiên trong 1 trang //curpos: lưu thay ms thay đổi,
	currposPrecSubject = (pageNowSubject - 1) * QUANTITY_PER_PAGE; // thay đổi chính key up key down
	//xíu sẽ thay đổi 
	clrscr();
	Display(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string));
	DeleteNote(sizeof(keyDisplaySubject) / sizeof(string));
}
NODE_SUBJECT* ChooseSubject(TREE_SUBJECT& t)
{
	if (t == NULL) return NULL;
	ShowCur(false);// hàm tương tự xử lí con trỏ chỉ vị 

	int key;
	int keyboard_read = 0;
	int PASS = 1;

	//QuickSort(0, nSubject, arrSubject);

	Display(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string)); // vẽ khung làm việc

	pageNowSubject = 1;   // page ban đầu 
	currposSubject = (pageNowSubject - 1) * QUANTITY_PER_PAGE;//  trong 1 trag
	currposPrecSubject = (pageNowSubject - 1) * QUANTITY_PER_PAGE;// làm việc thay đổi trang 

	NODE_SUBJECT* newSubject = FindSubject(t, listSubjectName[0].idSubject);

	//OutputListSubject(t);
	OutputListSubjectPerPage(t, 0);  // xuất page bắt đầu từ vị trí 0 
	SetDefaultChosenSubject(newSubject->data, currposSubject); // tô màu cho thàng đầu tiên 
	NODE_SUBJECT* oldSubject = NULL;

	gotoXY(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowSubject << "/" << totalPageSubject;

	while (PASS) // pass true
	{
		keyboard_read = _getch();//nhận kí tự
		if (keyboard_read == 0)
			keyboard_read = _getch();

		switch (keyboard_read)
		{


		case KEY_UP:
			if (currposSubject % QUANTITY_PER_PAGE > 0)// điều kiện ví dụ vị trí thứ 0 % 5==0 , ko thể lên đc nữa 
			{
				currposSubject = currposSubject - 1;// biến chạy trong 1 trang 
				oldSubject = newSubject;

				newSubject = FindSubject(t, listSubjectName[currposSubject].idSubject);
				EffectiveMenuSubject(currposSubject, newSubject->data, oldSubject->data); /// nó sẽ thay đổi ai thằng duy chyển cũ , ngay tại 2 điểm đó 
			}
			break;

		case KEY_DOWN:
			if (currposSubject % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposSubject < nSubject - 1)
			{
				currposSubject = currposSubject + 1;
				oldSubject = newSubject;

				newSubject = FindSubject(t, listSubjectName[currposSubject].idSubject);
				EffectiveMenuSubject(currposSubject, newSubject->data, oldSubject->data);
			}
			break;
		case KEY_RIGHT:
			if (pageNowSubject < totalPageSubject)
			{
				pageNowSubject++;
				ChangePageSubject(t);

				newSubject = FindSubject(t, listSubjectName[currposSubject].idSubject);// thay đổi vị trí chọn
				oldSubject = newSubject;

				OutputListSubjectPerPage(t, (pageNowSubject - 1) * QUANTITY_PER_PAGE);
				SetDefaultChosenSubject(newSubject->data, currposSubject);
			}
			break;
		case KEY_LEFT:
			if (pageNowSubject > 1)
			{
				pageNowSubject--;
				ChangePageSubject(t);

				newSubject = FindSubject(t, listSubjectName[currposSubject].idSubject);
				oldSubject = newSubject;

				OutputListSubjectPerPage(t, (pageNowSubject - 1) * QUANTITY_PER_PAGE);
				SetDefaultChosenSubject(newSubject->data, currposSubject);
			}
			break;
		case KEY_ENTER:  //enter
			PASS = 0;
			ShowCur(true);
			return newSubject;
			break;
		case KEY_ESC:
			ShowCur(true);
			return NULL;
			break;
		}
	}
}
void InputSubject(TREE_SUBJECT& t, SUBJECT& data, bool isEdited = false)
{
	ShowCur(true);

	bool isMoveUp = false;
	bool isSave = false;
	int ordinal = 0;


	string id_subject, name_subject;
	int number_theory = 0, number_pratice = 0;

	bool IdIsExits = false; //biến có tác dụng xác định xem môn học đã có chưa . 

	if (isEdited)// nếu là chỉnh sửa thì bỏ data ra để sửa 
	{
		id_subject = data.idSubject;
		name_subject = data.nameSubject;
		number_theory = data.numberTheory;
		number_pratice = data.numberPratice;

		gotoXY(X_ADD + 20 + 7, 0 * 3 + Y_ADD);
		cout << id_subject;
		gotoXY(X_ADD + 21 + 7, 1 * 3 + Y_ADD);
		cout << name_subject;
		gotoXY(X_ADD + 22 + 7, 2 * 3 + Y_ADD);
		cout << number_theory;
		gotoXY(X_ADD + 22 + 7, 3 * 3 + Y_ADD);
		cout << number_pratice;
	}
	int key = 0;
	while (true)
	{

		switch (ordinal)
		{
		case 0:     // case 01,2,3,4 là bắt sự kiện các trường. 
			if (isEdited) break;
			CheckMoveAndValidateID(id_subject, isMoveUp, ordinal, isSave, 20 + 7, 10, key);

			data.idSubject = id_subject;

			if (FindSubject(t, data.idSubject) == NULL)
			{
				IdIsExits = false;
				break;
			}
			IdIsExits = true;
			break;
		case 1:
			CheckMoveAndValidateNameSubject(name_subject, isMoveUp, ordinal, isSave, 21 + 7, 25, key);
			break;
		case 2:
			CheckMoveAndValidateNumber(number_pratice, isMoveUp, ordinal, isSave, 22 + 7, 4, key);
			break;
		case 3:
			CheckMoveAndValidateNumber(number_theory, isMoveUp, ordinal, isSave, 22 + 7, 4, key);

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
			if (ordinal == 4)
				isMoveUp = true;
			ordinal++;
		}
		if (isSave)
		{
			gotoXY(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			if (id_subject.empty() || name_subject.empty() || number_theory == 0 || number_pratice == 0)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY);
				cout << "Ban chua dien day du thong tin";
			}
			else if (IdIsExits)
			{
				gotoXY(X_NOTIFY, Y_NOTIFY);
				cout << "ma mon hoc(maMH) khong duoc trung";
			}


			else
			{


				//strcpy(data.id_subject, id.c_str());
				//strcpy(data.nameSubject, name.c_str());
				//data.nameSubject = name;
				data.numberTheory = number_theory;
				data.numberPratice = number_pratice;
				data.idSubject = id_subject;
				data.nameSubject = name_subject;
				if (isEdited)  // kiểm tra sửa
				{

					NODE_SUBJECT* search = FindSubject(t, data.idSubject);
					search->data = data;
					//xoá rồi thêm vào mảng theo tên.
					DeleteInListSubjectName(search->data.idSubject);
					insertOder(search->data);

				}
				else
				{
					InsertSubjectToTree(t, data);
					gotoXY(X_NOTIFY, Y_NOTIFY); cout << "Them thanh cong";
				}
				//DeleteMenuAdd();
				gotoXY(X_NOTIFY, Y_NOTIFY + 1);
				cout << "                    ";
				return;
			}
			isSave = false;
		}
		else
			isSave = false;
	}

	ShowCur(false);
}

//void ManagerSubject(TREE_SUBJECT& t) {
//	OutputListSubject(0);
//	Display(keyDisplaySubject, 4);
//	int key;
//	while (true) {
//		while (kbhit) {
//			key = _getch();
//			if (key == KEY_F2) {
//				DisplayEdit(keyDisplaySubject, 4, 35);
//				SUBJECT mh;
//				InputSubject(t, mh);
//				OutputListSubject(0);
//			}
//			else if (key == KEY_ESC) {
//				return;
//			}
//
//		}
//	}
//
//}

void MenuSubjectManager(TREE_SUBJECT& t)
{
backMenu:
	if (nSubject % QUANTITY_PER_PAGE == 0) {
		totalPageSubject = nSubject / QUANTITY_PER_PAGE;
	}
	else {
		totalPageSubject = nSubject / QUANTITY_PER_PAGE + 1;
	}

	pageNowSubject = 1;
	indexOutSubject = -1;
	Display(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string));
	if (nSubject != -1)
		OutputListSubjectPerPage(t, 0);
	gotoXY(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH MON HOC ";

	int key;
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();

			if (key == 0 || key == 224)
			{
				key = _getch();
				gotoXY(X_NOTIFY, Y_NOTIFY);
				cout << setw(35) << setfill(' ') << " ";

				if (key == KEY_F2)
				{
					SUBJECT ins;
					DisplayEdit(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string), 35);
					InputSubject(t, ins);
					//gotoXY(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH MON HOC ";

					totalPageSubject = nSubject / QUANTITY_PER_PAGE + 1;
					pageNowSubject = 1;
					//QuickSort(0, nSubject, arrSubject);
					OutputListSubjectPerPage(t, (pageNowSubject - 1) * QUANTITY_PER_PAGE);

				}
				else if (key == KEY_F3)
				{
					clrscr();
					SetBGColor(ColorCode_White);
					SetColor(ColorCode_Blue);
					gotoXY(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH MON HOC ";
					gotoXY(X_PAGE, Y_PAGE); cout << "Trang " << pageNowSubject << "/" << totalPageSubject;

					NODE_SUBJECT* del = ChooseSubject(t);
					if (del == NULL) goto backMenu;

					gotoXY(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chan chan xoa? ENTER == dong y";
					key = _getch();
					if (key == KEY_ENTER)
					{
						clrscr();
						gotoXY(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH MON HOC ";
						Display(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string));
						for (int i = 0; i <= nSubject; i++)
						{
							if (del->data.idSubject == listSubjectName[i].idSubject)
							{
								/*	for (int j = i; j < nSubject; j++)
										listSubjectName[j] = listSubjectName[j + 1];
									nSubject--;*/
								DeleteInListSubjectName(listSubjectName[i].idSubject);
								break;
							}
						}
						if (DeleteNodeSubject(t, del->data.idSubject))
						{
							//QuickSort(0, nSubject, arrSubject);
							OutputListSubjectPerPage(t, (pageNowSubject - 1) * QUANTITY_PER_PAGE);
							gotoXY(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
						}
					}
					else
						goto backMenu;
				}
				else if (key == KEY_F4)
				{
					NODE_SUBJECT* k = ChooseSubject(t);
					if (k == NULL) goto backMenu;
					DisplayEdit(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string), 35);
					InputSubject(t, k->data, true);
					gotoXY(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH MON HOC ";
					OutputListSubjectPerPage(t, (pageNowSubject - 1) * QUANTITY_PER_PAGE);


				}
				else if (key == KEY_RIGHT && pageNowSubject < totalPageSubject)
				{
					clrscr();
					pageNowSubject++;
					gotoXY(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH MON HOC ";
					Display(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string));
					OutputListSubjectPerPage(t, (pageNowSubject - 1) * QUANTITY_PER_PAGE);
				}
				else if (key == KEY_LEFT && pageNowSubject > 1)
				{
					clrscr();
					pageNowSubject--;
					gotoXY(X_TITLE, Y_TITLE); cout << " QUAN LY DANH SACH MON HOC ";
					Display(keyDisplaySubject, sizeof(keyDisplaySubject) / sizeof(string));
					OutputListSubjectPerPage(t, (pageNowSubject - 1) * QUANTITY_PER_PAGE);
				}
			}
			else if (key == KEY_ESC)
			{
				return;
			}

		}

	}
}

//ĐỌC GHI FILE MÔN HỌC.============================
//1=============== ĐỌC =================
void ReadTreeSubject(TREE_SUBJECT& t, ifstream& f)
{
	string line;
	//getline(f, line);
	SUBJECT subject;
	int n;
	string temp;
	while (f.eof() == false)
	{
		getline(f, line);
		if (line != "") {
			n = 0;
			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			subject.idSubject = temp;
			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			subject.nameSubject = temp;
			temp = "";
			for (int i = 0; line[n] != ','; i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			subject.numberTheory = atoi(temp.c_str());
			temp = "";
			for (int i = 0; n < line.size(); i++, n++) {
				temp.push_back(line[n]);
			}
			n++;
			subject.numberPratice = atoi(temp.c_str());

			InsertSubjectToTree(t, subject);
		}
		else {
			break;
		}
	}
}
void ReadFileSubject(TREE_SUBJECT& t)
{
	ifstream f("subject.txt");
	if (f.is_open()) {
		/*	if (!f.peek() == EOF) {
				getline(f, pass);
				docCay(t, f);
				ReadStudent(ds, f);
				f.close();
			}*/
		ReadTreeSubject(t, f);
		f.close();
	}
}
//2)=======GHI  FIle==============
void WriteFileNodeLeftRight(TREE_SUBJECT t, ofstream& f)
{
	if (t != NULL) {
		f << t->data.idSubject << "," << t->data.nameSubject << "," << t->data.numberTheory << "," << t->data.numberPratice << endl;
		WriteFileNodeLeftRight(t->pLeft, f);
		WriteFileNodeLeftRight(t->pRight, f);
	}
}
void WriteFileSubject(TREE_SUBJECT t)
{
	ofstream f("subject.txt");
	if (f.is_open()) {
		WriteFileNodeLeftRight(t, f);
		f.close();
	}
}
//==========================================================