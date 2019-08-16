#pragma once
#pragma once
#include<iostream>
#include <stdio.h>
#include <conio.h>
#include<string>
#include<string.h>
#include<cmath>
#include <windows.h>
#include<iomanip>
#include <fstream>

using namespace std;
#pragma warning(disable:4996) // bỏ qua lỗi 4996 - lỗi bảo mật


#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


//key
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8
#define KEY_DELETE 83
#define KEY_TAB 9
#define KEY_INS 82
#define KEY_CONTROL 224
#define KEY_HOME 71
#define BELL 7
#define SPACE  32

#define PAGE_UP 73
#define PAGE_DOWN 81

#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67
#define KEY_F10 68

//vị trí sẽ hiển thị

#define X_ADD 130
#define Y_ADD 11

#define X_NOTIFY 120
#define Y_NOTIFY 40

#define X_TITLE 30
#define Y_TITLE 9



#define X_PAGE 20
#define Y_PAGE 46

#define X_DISPLAY 4
#define Y_DISPLAY 10
#define QUANTITY_PER_PAGE 5
 

int indexOutSubject = -1;
int currposSubject = 1;
int pageNowSubject = 0;
int currposPrecSubject = 0;
int totalPageSubject = 0;

#define MAXLISTSUBJECT 1000
#define MAXLISTSTUDENT 5000

#define MAX_STUDENT 10
#define MIN_STUDENT 2
