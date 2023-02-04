#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <string>

//#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13
#define RIGHT 77
#define LEFT 75

using namespace std;


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли

// Текстовый курсор в точку x,y
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость курсора
	structCursorInfo.dwSize = size; // изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

const int r = 4;
const int c = 4;
int arr2[r][c]{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15,0 },
};
int arr[r][c]{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 11, 14, 12 },
		{ 13, 10, 15,0 },
};
int arr3[3][3]{
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 0},
};
int arr4[3][3]{
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 0},
};
int* p = &arr[0][0];
char key;
void func() {
	random_shuffle(p, p + 16);
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r; i++) {
		cout << setw(50);
		for (int j = 0; j < c; j++) {

			cout << arr[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
bool funcwin() {
	bool game = false;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == arr2[i][j] && arr[3][3] == 0) {
				continue;
			}
			else game = true;
		}
	}
	return game;
}

void funcup() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == temp && temp != arr[3][j]) {
				t = i;
				if (t == 0) {
					temp = arr[t + 1][j];
					arr[t + 1][j] = arr[t][j];
					arr[t][j] = temp;
				}
				else if (t == 1) {
					temp = arr[t + 1][j];
					arr[t + 1][j] = arr[t][j];
					arr[t][j] = temp;
				}
				else if (t == 2) {
					arr[t][j] = arr[t + 1][j];
					arr[t + 1][j] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r; i++) {
		cout << setw(50);
		for (int j = 0; j < c; j++) {

			cout << arr[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void funcdown() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == temp && temp != arr[0][j]) {
				t = i;
				if (t == 1) {
					temp = arr[t - 1][j];
					arr[t - 1][j] = arr[t][j];
					arr[t][j] = temp;
				}
				else if (t == 2) {
					arr[t][j] = arr[t - 1][j];
					arr[t - 1][j] = temp;
				}
				else if (t == 3) {
					temp = arr[t - 1][j];
					arr[t - 1][j] = arr[t][j];
					arr[t][j] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r; i++) {
		cout << setw(50);
		for (int j = 0; j < c; j++) {

			cout << arr[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void funcleft() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == temp && temp != arr[i][3]) {
				t = j;
				if (t == 0) {
					temp = arr[i][t + 1];
					arr[i][t + 1] = arr[i][t];
					arr[i][t] = temp;
				}
				else if (t == 1) {
					temp = arr[i][t + 1];
					arr[i][t + 1] = arr[i][t];
					arr[i][t] = temp;
				}
				else if (t == 2) {
					arr[i][t] = arr[i][t + 1];
					arr[i][t + 1] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r; i++) {
		cout << setw(50);
		for (int j = 0; j < c; j++) {

			cout << arr[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void funcright() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == temp && temp != arr[i][0]) {
				t = j;
				if (t == 1) {
					temp = arr[i][t - 1];
					arr[i][t - 1] = arr[i][t];
					arr[i][t] = temp;
				}
				else if (t == 2) {
					arr[i][t] = arr[i][t - 1];
					arr[i][t - 1] = temp;
				}
				else if (t == 3) {
					temp = arr[i][t - 1];
					arr[i][t - 1] = arr[i][t];
					arr[i][t] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r; i++) {
		cout << setw(50);
		for (int j = 0; j < c; j++) {

			cout << arr[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}

int* p1 = &arr4[0][0];
const int r1 = 3;
const int c1 = 3;

void func1() {
	random_shuffle(p1, p1 + 9);

	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r1; i++) {
		cout << setw(50);
		for (int j = 0; j < c1; j++) {

			cout << arr3[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
bool funcwin1() {
	bool game = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr4[i][j] == arr3[i][j] && arr4[3][3] == 0) {
				continue;
			}
			else game = true;
		}
	}
	return game;
}

void funcup1() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			if (arr4[i][j] == temp && temp != arr4[2][j]) {
				t = i;
				if (t == 0) {
					temp = arr[t + 1][j];
					arr4[t + 1][j] = arr4[t][j];
					arr4[t][j] = temp;
				}
				else if (t == 1) {
					temp = arr[t + 1][j];
					arr3[t + 1][j] = arr3[t][j];
					arr3[t][j] = temp;
				}
				else if (t == 2) {
					arr3[t][j] = arr3[t + 1][j];
					arr3[t + 1][j] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r1; i++) {
		cout << setw(50);
		for (int j = 0; j < c1; j++) {

			cout << arr4[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void funcdown1() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			if (arr4[i][j] == temp && temp != arr4[0][j]) {
				t = i;
				if (t == 1) {
					temp = arr[t - 1][j];
					arr4[t - 1][j] = arr4[t][j];
					arr4[t][j] = temp;
				}
				else if (t == 2) {
					arr4[t][j] = arr4[t - 1][j];
					arr4[t - 1][j] = temp;
				}
				else if (t == 3) {
					temp = arr3[t - 1][j];
					arr4[t - 1][j] = arr4[t][j];
					arr4[t][j] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r1; i++) {
		cout << setw(50);
		for (int j = 0; j < c1; j++) {

			cout << arr4[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void funcleft1() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			if (arr4[i][j] == temp && temp != arr4[i][2]) {
				t = j;
				if (t == 0) {
					temp = arr[i][t + 1];
					arr4[i][t + 1] = arr4[i][t];
					arr4[i][t] = temp;
				}
				else if (t == 1) {
					temp = arr[i][t + 1];
					arr4[i][t + 1] = arr4[i][t];
					arr4[i][t] = temp;
				}
				else if (t == 2) {
					arr4[i][t] = arr4[i][t + 1];
					arr4[i][t + 1] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r1; i++) {
		cout << setw(50);
		for (int j = 0; j < c1; j++) {

			cout << arr4[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void funcright1() {
	int temp = 0;
	int t = 0;
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			if (arr4[i][j] == temp && temp != arr4[i][0]) {
				t = j;
				if (t == 1) {
					temp = arr4[i][t - 1];
					arr4[i][t - 1] = arr4[i][t];
					arr4[i][t] = temp;
				}
				else if (t == 2) {
					arr4[i][t] = arr4[i][t - 1];
					arr4[i][t - 1] = temp;
				}
				else if (t == 3) {
					temp = arr[i][t - 1];
					arr4[i][t - 1] = arr4[i][t];
					arr4[i][t] = temp;
				}
			}
		}
	}
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < r1; i++) {
		cout << setw(50);
		for (int j = 0; j < c1; j++) {

			cout << arr4[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}

//15(4x4)
void funcGameNew() {
	system("cls");
	func();
	do
	{
		key = _getch();
		if (key == -32)key = _getch();
		system("cls");
		switch (key)
		{
		case UP:
			funcup();
			break;
		case DOWN:
			funcdown();
			break;
		case LEFT:
			funcleft();
			break;
		case RIGHT:
			funcright();
			break;
		default:
			break;
		}
	} while (funcwin());
	cout << "Вы победили";
}
//8(3x3)
void funcGameNew1() {
	srand(time(NULL));
	system("cls");
	func1();
	do
	{
		key = _getch();
		if (key == -32)key = _getch();
		system("cls");
		switch (key)
		{
		case UP:
			funcup1();
			break;
		case DOWN:
			funcdown1();
			break;
		case LEFT:
			funcleft1();
			break;
		case RIGHT:
			funcright1();
			break;
		default:
			break;
		}
	} while (funcwin1());
	cout << "Вы победили";
}

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	SetConsoleTitle(L"Пятнашки");//заголовок консоли
	system("cls");
	ConsoleCursorVisible(false, 100);
	string Menu[] = { "ИГРАТЬ","ВЫХОД" };
	int active_menu = 0;
	string MenuRejim[] = { "8(3x3)","15(4x4)" };
	//int active_menu_rej = 0;
	char key;
	while (true)
	{
		int x = 50, y = 12;
		GoToXY(x, y);

		for (int i = 0; i < size(Menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << Menu[i] << " ";
		}
		key = _getch();
		if (key == -32) key = _getch(); // Отлавливаем стрелочки
		switch (key)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				while (true)
				{
					system("cls");
					int x = 50, y = 12;
					GoToXY(x, y);
					for (int i = 0; i < size(MenuRejim); i++)
					{
						if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
						GoToXY(x, y++);
						cout << MenuRejim[i] << " ";
					}
					key = _getch();
					if (key == -32) key = _getch(); // Отлавливаем стрелочки
					switch (key)
					{
					case UP:
						if (active_menu > 0)
							--active_menu;
						break;
					case DOWN:
						if (active_menu < size(MenuRejim) - 1)
							++active_menu;
						break;
					case ENTER:
						switch (active_menu)
						{
						case 0:
							funcGameNew1();
						case 1:
							funcGameNew();
							break;
						}
					}
					//break;
				}
			case 1:
				exit(0);
				break;
			}
		}
	}


}