#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13
#define RIGHT 77
#define LEFT 75
#define BACKSPACE 8
#define SIZE 4
#define SIZE1 3

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

char key;
int count_of_shift;//счетчик перестановок(увеличивается в каждом сдвиге)
int arr2[SIZE][SIZE]{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15,0 },
};
int arr[SIZE][SIZE]{
		{ 1, 2, 3, 4 },
		{ 5, 6, 7, 8 },
		{ 9, 10, 11, 12 },
		{ 13, 14, 15,0 },
};
int arr3[SIZE1][SIZE1]{
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 0},
};
int arr4[SIZE1][SIZE1]{
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 0},
};

string Menu[] = { "ИГРАТЬ","ВЫХОД" };
int active_menu = 0;
string MenuRejim[] = { "8(3x3)","15(4x4)" };
string MenuShufle[] = { "РУЧНОЕ РАЗМЕШИВАНИЕ","АВТОМАТИЧЕСКОЕ РАЗМЕШИВАНИЕ" };


//15(4x4)
void Print() {
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < SIZE; i++) {
		cout << setw(50);
		for (int j = 0; j < SIZE; j++) {

			cout << arr[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void func() {
	int* p = &arr[0][0];
	//random_shuffle(p, p + 16);
	Print();
}
bool funcwin() {
	bool game = false;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (arr[i][j] == arr2[i][j] && arr[3][3] == 0) {
				continue;
			}
			else game = true;
		}
	}
	return game;
}
//ходы для массива 4 на 4
void funcRun(int run) {
	int temp = 0;
	int t = 0;
	if (run == 1) {
		
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
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
		count_of_shift++;
	}
	else if (run == 2) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
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
		count_of_shift++;
	}
	else if (run == 3) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
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
		count_of_shift++;
	}
	else if (run == 4) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
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
		count_of_shift++;
	}
	Print();
}
void funcGameNew_() {
	system("cls");
	func();
	count_of_shift = 0;
	clock_t start_time = clock();
	do
	{
		key = _getch();
		if (key == -32)key = _getch();
		system("cls");
		switch (key)
		{
		case UP:
			funcRun(1);
			break;
		case DOWN:
			funcRun(2);
			break;
		case LEFT:
			funcRun(3);
			break;
		case RIGHT:
			funcRun(4);
			break;
		default:
			break;
		}
	} while (funcwin());
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	int waste_time = int(clock() - start_time) / CLOCKS_PER_SEC;
	int h, m, s;
	h = waste_time / 60 / 60;
	m = (waste_time - h * 3600) / 60;
	s = waste_time % 60;
	cout << setw(60) << "ВЫ ПОБЕДИЛИ!!!\n\n\n" << setw(63) << "Количество перестановок - " << count_of_shift << endl;
	cout << setw(53) << "Потраченое время - " << m << " минут " << s << " секунд";
	_getch();
}
void funcGameNew_1() {
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
			funcRun(1);
			break;
		case DOWN:
			funcRun(2);
			break;
		case LEFT:
			funcRun(3);
			break;
		case RIGHT:
			funcRun(4);
			break;
		default:
			break;
		}
	} while (key!=ENTER);
	funcGameNew_();
}

//8(3x3)
void Print1() {
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < SIZE1; i++) {
		cout << setw(50);
		for (int j = 0; j < SIZE1; j++) {

			cout << arr4[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void func1() {
	int* p1 = &arr4[0][0];
	//random_shuffle(p1, p1 + 9);
	Print1();
}
bool funcwin1() {
	bool game = false;
	for (int i = 0; i < SIZE1; i++) {
		for (int j = 0; j < SIZE1; j++) {
			if (arr4[i][j] == arr3[i][j] && arr4[2][2] == 0) {
				continue;
			}
			else game = true;
		}
	}
	return game;
}
//ходы для массива 3 на 3
void funcRun1(int run) {
	int temp = 0;
	int t = 0;
	if (run == 1) {
		for (int i = 0; i < SIZE1; i++) {
			for (int j = 0; j < SIZE1; j++) {
				if (arr4[i][j] == temp && temp != arr4[2][j]) {
					t = i;
					if (t == 0) {
						temp = arr4[t + 1][j];
						arr4[t + 1][j] = arr4[t][j];
						arr4[t][j] = temp;
					}
					else if (t == 1) {
						temp = arr4[t + 1][j];
						arr4[t + 1][j] = arr4[t][j];
						arr4[t][j] = temp;
					}
					else if (t == 2) {
						arr4[t][j] = arr4[t + 1][j];
						arr4[t + 1][j] = temp;
					}
				}
			}
		}
		count_of_shift++;
	}
	else if (run == 2) {
		for (int i = 0; i < SIZE1; i++) {
			for (int j = 0; j < SIZE1; j++) {
				if (arr4[i][j] == temp && temp != arr4[0][j]) {
					t = i;
					if (t == 1) {
						temp = arr4[t - 1][j];
						arr4[t - 1][j] = arr4[t][j];
						arr4[t][j] = temp;
					}
					else if (t == 2) {
						arr4[t][j] = arr4[t - 1][j];
						arr4[t - 1][j] = temp;
					}
					else if (t == 3) {
						temp = arr4[t - 1][j];
						arr4[t - 1][j] = arr4[t][j];
						arr4[t][j] = temp;
					}
				}
			}
		}
		count_of_shift++;
	}
	else if (run == 3) {
		for (int i = 0; i < SIZE1; i++) {
			for (int j = 0; j < SIZE1; j++) {
				if (arr4[i][j] == temp && temp != arr4[i][2]) {
					t = j;
					if (t == 0) {
						temp = arr4[i][t + 1];
						arr4[i][t + 1] = arr4[i][t];
						arr4[i][t] = temp;
					}
					else if (t == 1) {
						temp = arr4[i][t + 1];
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
		count_of_shift++;
	}
	else if (run == 4) {
		for (int i = 0; i < SIZE1; i++) {
			for (int j = 0; j < SIZE1; j++) {
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
						temp = arr4[i][t - 1];
						arr4[i][t - 1] = arr4[i][t];
						arr4[i][t] = temp;
					}
				}
			}
		}
		count_of_shift++;
	}
	Print1();
}
void funcGameNew1() {
	srand(time(NULL));
	system("cls");
	func1();
	count_of_shift = 0;
	clock_t start_time = clock();
	do
	{
		key = _getch();
		if (key == -32)key = _getch();
		system("cls");
		switch (key)
		{
		case UP:
			funcRun1(1);
			break;
		case DOWN:
			funcRun1(2);
			break;
		case LEFT:
			funcRun1(3);
			break;
		case RIGHT:
			funcRun1(4);
			break;
		default:
			break;
		}
	} while (funcwin1());
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	int waste_time = int(clock() - start_time) / CLOCKS_PER_SEC;
	int h, m, s;
	h = waste_time / 60 / 60;
	m = (waste_time - h * 3600) / 60;
	s = waste_time % 60;
	cout << setw(60) << "ВЫ ПОБЕДИЛИ!!!\n\n\n" << setw(63) << "Количество перестановок - " << count_of_shift << endl;
	cout << setw(53) << "Потраченое время - " << m << " минут " << s << " секунд";
	_getch();
}
void funcGameNew11() {
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
			funcRun1(1);
			break;
		case DOWN:
			funcRun1(2);
			break;
		case LEFT:
			funcRun1(3);
			break;
		case RIGHT:
			funcRun1(4);
			break;
		default:
			break;
		}
	} while (key!=ENTER);
	funcGameNew1();
}
void funcMenu() {
	int choise = 0;
	while (key != ESC)
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
			if (active_menu > 0) { --active_menu; choise = active_menu;}break;	
		case DOWN:
			if (active_menu < size(MenuRejim) - 1) { ++active_menu; choise = active_menu;}break;
		case ENTER:
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
				while (key != BACKSPACE && key !=ESC)
				{
					system("cls");
					int x = 50, y = 12;
					GoToXY(x, y);
					for (int i = 0; i < size(MenuShufle); i++)
					{
						if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
						GoToXY(x, y++);
						cout << MenuShufle[i] << " ";
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
						if (active_menu < size(MenuShufle) - 1)
							++active_menu;
						break;
					case ENTER:
						switch (active_menu)
						{
						case 0:
							if (choise == 0) funcGameNew11();
							else if (choise == 1) funcGameNew_1();
							//тут надо будет сделать функцию для ручного мешания
							break;
						case 1:
							if (choise == 0) funcGameNew1();
							else if (choise == 1) funcGameNew_();
							break;
						default:
							break;
						}
						break;
					}
				}
				continue;
				break;
			}
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	SetConsoleTitle(L"Пятнашки");//заголовок консоли
	//system("cls");
	ConsoleCursorVisible(false, 100);
	do
	{
		system("cls");
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
				funcMenu();
				break;
			case 1:
				exit(0);
				break;
			}
		}
	} while (true);
}
