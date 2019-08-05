#include"console.h"
#include"subject.h"
int main() {
	SetColor(ColorCode_Blue);
	SetBGColor(ColorCode_White);
	fullScreen();
	TREE_SUBJECT t;
	
	init(t);
	//SUBJECT mh;
	//mh.IdSubject = "ctdl";
	//mh.NameSubject = "cautruc";
	//mh.NumberTheory = 1;
	//mh.NumberPratice = 3;
	//InsertSubjectToTree(t, mh);
	ReadFileSubject(t);
	ManagerSubject(t);
	WriteFileSubject(t);
	system("pause");
	return 0;
}