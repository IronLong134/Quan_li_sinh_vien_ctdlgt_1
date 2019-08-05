#pragma once
#include"console.h"
#include"display.h"
#include"validation.h"
#define MAXLISTSUBJECT 1000
struct Subject
{
	string IdSubject;
	string NameSubject;
	int NumberTheory;
	int NumberPratice;

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


SUBJECT listSubjectName[MAXLISTSUBJECT];
int nSubject = 0;
//struct ListSubjectName {
//	SUBJECT data[MAXLISTSUBJECT];
//	int nSubject = 0;
//};
//typedef struct ListSubjectName ListSubjectName;

void init(TREE_SUBJECT& t) {
	t = NULL;

}
void DeleteInListSubjectName(string id_subject) {
	
	for (int i = 0; i < nSubject; i++) {
		if (listSubjectName[i].IdSubject == id_subject) {
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
			if (subject.NameSubject < listSubjectName[n].NameSubject) {
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

		if (subject.IdSubject < t->data.IdSubject)
		{
			InsertSubjectToTree(t->pLeft, subject);
		}
		else if (subject.IdSubject > t->data.IdSubject)
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
void DeleteNode(TREE_SUBJECT& t, string id_subject) {
	// nếu như cây đang rỗng
	if (t == NULL)
	{
		return; // kết thúc hàm
	}
	else
	{
		// nếu như data nhỏ hơn node gốc
		if (t->data.IdSubject > id_subject)
		{
			DeleteNode(t->pLeft, id_subject); // duyệt sang nhánh trái của cây 
		}
		else if (t->data.IdSubject < id_subject)
		{
			DeleteNode(t->pRight, id_subject); // duyệt sang nhánh phải của cây 
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
		}
	}
}


void OutputOneSubject(SUBJECT subject, int locate) // vi tri == locate
{
	DeleteOldData(sizeof(keyDisplaySubject) / sizeof(string), locate);
	gotoXY(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << subject.IdSubject;
	gotoXY(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << subject.NameSubject;
	gotoXY(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); cout << subject.NumberTheory;
	gotoXY(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate); cout << subject.NumberPratice;
}
void OutputListSubject( int locationStart) {   // locationStart là vị trí bắt đầu xuất 
	for (int i = 0; i + locationStart < nSubject && i < 10; i++) {
		OutputOneSubject(listSubjectName[i+locationStart], i*2);
	}
}
NODE_SUBJECT* FindSubject(TREE_SUBJECT t, string id_subject) //return search = null if not found
{
	if (t != NULL)
	{
		NODE_SUBJECT* search = t;
		while (search != NULL)
		{
			if (id_subject == search->data.IdSubject)
				return search;
			else if (id_subject > search->data.IdSubject)
				search = search->pRight;
			else
				search = search->pLeft;
		}
	}
	return NULL;
}

void InputSubject(TREE_SUBJECT& t, SUBJECT& data,bool isEdited = false)
{
	//ShowCur(true);

	bool isMoveUp = false;
	bool isSave = false;
	int ordinal = 0;


	string id_subject, name_subject;
	int number_theory = 0, number_pratice = 0;

	bool IdIsExits = false; //biến có tác dụng xác định xem môn học đã có chưa . 

	if (isEdited)// nếu là chỉnh sửa thì bỏ data ra để sửa 
	{
		id_subject = data.IdSubject;
		name_subject = data.NameSubject;
		number_theory = data.NumberTheory;
		number_pratice = data.NumberPratice;

		gotoXY(X_ADD + 20 + 7, 0 * 3 + Y_ADD);
		cout << id_subject;
		gotoXY(X_ADD + 21 + 7, 1 * 3 + Y_ADD);
		cout << name_subject;
		gotoXY(X_ADD + 22 + 7, 2 * 3 + Y_ADD);
		cout << number_theory;
		gotoXY(X_ADD + 22 + 7, 3 * 3 + Y_ADD);
		cout << number_pratice;
	}

	while (true)
	{
		switch (ordinal)
		{
		case 0:     // case 01,2,3,4 là bắt sự kiện các trường. 
			if (isEdited) break;
			CheckMoveAndValidateID(id_subject, isMoveUp, ordinal, isSave, 20 + 7, 10);

			data.IdSubject=id_subject;

			if (FindSubject(t, data.IdSubject) == NULL)
			{
				IdIsExits = false;
				break;
			}
			IdIsExits = true;
			break;
		case 1:
			CheckMoveAndValidateTenMH(name_subject, isMoveUp, ordinal, isSave, 21 + 7, 25);
			break;
		case 2:
			CheckMoveAndValidateNumber(number_pratice, isMoveUp, ordinal, isSave, 22 + 7, 4);
			break;
		case 3:
			CheckMoveAndValidateNumber(number_theory, isMoveUp, ordinal, isSave, 22 + 7, 4);

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
				data.NumberTheory = number_theory;
				data.NumberPratice = number_pratice;
				data.IdSubject = id_subject;
				data.NameSubject = name_subject;
				if (isEdited)
				{

					NODE_SUBJECT* search = FindSubject(t,data.IdSubject);
					search->data = data;
				    //xoá rồi thêm vào mảng theo tên.
					DeleteInListSubjectName(search->data.IdSubject);
					insertOder(search->data);

				}
				else
				{
					InsertSubjectToTree(t, data);

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

	//ShowCur(false);
}
void ManagerSubject(TREE_SUBJECT& t) {
	OutputListSubject(0);
	Display(keyDisplaySubject, 4);
	int key;
	while (true) {
		while (kbhit) {
			key = _getch();
			if (key == KEY_F2) {
				DisplayEdit(keyDisplaySubject, 4, 35);
				SUBJECT mh;
				InputSubject(t, mh);
				OutputListSubject(0);
			}
			else if (key == KEY_ESC) {
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
	getline(f, line);

	SUBJECT subject;
	int n;
	string temp;
	while (!f.eof())
	{
		n = 0;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		subject.IdSubject = temp;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		subject.NameSubject = temp;
		temp = "";
		for (int i = 0; line[n] != ','; i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		subject.NumberTheory = atoi(temp.c_str());
		temp = "";
		for (int i = 0; n < line.size(); i++, n++) {
			temp.push_back(line[n]);
		}
		n++;
		subject.NumberPratice= atoi(temp.c_str());

		InsertSubjectToTree(t, subject);
		getline(f, line);
	}
}
void ReadFileSubject(TREE_SUBJECT& t)
{
	ifstream f("subject.txt");
	if (f.is_open()) {
		/*	if (!f.peek() == EOF) {
				getline(f, pass);
				docCay(t, f);
				docSV(ds, f);
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
		f << t->data.IdSubject << "," << t->data.NameSubject << "," << t->data.NumberTheory << "," << t->data.NumberPratice << endl;
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