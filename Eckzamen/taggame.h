#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
void Menu(int s, int choise_game, int choise_shuffle);
// Текстовый курсор в точку x,y
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость курсора
	structCursorInfo.dwSize = size; // изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int** pa = nullptr; //пустой указатель
string menu[6]{
{ "ИГРАТЬ" },{ "ВЫХОД" },{ "8(3x3)" },{ "15(4x4)" },{ "РУЧНОЕ РАЗМЕШИВАНИЕ" },{ "АВТОМАТИЧЕСКОЕ РАЗМЕШИВАНИЕ" }
};
char key;
int count_of_shift;
int pi, pj; //переменные для поиска нуля по индексу pi по индексу i и pj по индексу j
int** Create(int s) {
	int** arr = new int* [s];
	for (int i = 0; i < s; i++) {
		arr[i] = new int[s];
	}
	return arr;
}
void deletearr(int** arr, int row) {      //добавил так сказать че по кайфу чтоб удалять после победы
	for (int i = 0; i < row; i++) {
		delete[]arr[i];
	}
	delete[]arr;
}
int** Inicial(int** p, int s) {
	int n = 1;            //перевёл из глобальной в лок., ибо если в самой проге начать новую игру, то там он не то заполнял
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			p[i][j] = n;
			n++;
		}
	}
	return p;
}
void Print(int** p, int s) {
	cout << "\n\n\n\n\n\n\n\n\n\n";
	for (int i = 0; i < s; i++) {
		cout << setw(48);
		for (int j = 0; j < s; j++) {
			cout << p[i][j] << setw(5);
		}
		cout << endl << endl;
	}
	cout << endl;
}
void Shufl(int** p, int s) {
	srand(unsigned int(NULL));
	int i, j, len = s * s;
	int* mas = new int[len];//Вспомогательный массив
	//Тасование Фишера–Йетса, "вывернутый" алгоритм
	for (i = 0; i < len; i++) {
		j = rand() % (i + 1);
		mas[i] = mas[j];
		mas[j] = i + 1;
	}
	for (i = 0; i < s; i++)
		for (j = 0; j < s; j++)
			p[i][j] = mas[i * s + j];
	delete[] mas;
}
void findZero(int** p, int s) {
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			if (s == 3 && p[i][j] == 9) {
				p[i][j] = 0;
				pi = i; pj = j;
			}										//сделал отдельно по режимам ибо в 4х4 он 9 присваивает 0 и победы нет
			if (s == 4 && p[i][j] == 16) {
				p[i][j] = 0;
				pi = i; pj = j;

			}
		}
	}
}
bool Move(int** p, int s, int& pi, int& pj, int handShuffle = 0) {
	if (handShuffle == 1) {
		cout << setw(69) << "~~~Хорошей игры! =)~~~\n\n\n";
		cout << setw(70) << "~~~Esc - Выйти в главное меню~~~\n";
	}
	key = _getch();
	switch (key)
	{
	case 119: case 72:  //Вверх
		if (pi < s - 1) {
			swap(p[pi][pj], p[pi + 1][pj]);
			pi++;
			count_of_shift++;
			return true;
		}
		return false;
	case 115: case 80:  //Вниз
		if (pi > 0) {
			swap(p[pi][pj], p[pi - 1][pj]);
			pi--;
			count_of_shift++;
			return true;
		}
		return false;
	case 97: case 75:   //Влево
		if (pj < s - 1) {
			swap(p[pi][pj], p[pi][pj + 1]);
			pj++;
			count_of_shift++;
			return true;
		}
		return false;
	case 100: case 77:  //Вправо
		if (pj > 0) {
			swap(p[pi][pj], p[pi][pj - 1]);
			pj--;
			count_of_shift++;
			return true;
		}
		return false;
	}
}
bool Winn(int** p, int s) {
	bool game = false;
	int temp = 0;
	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++) {
			temp++;
			if (s == 3) {
				if (temp == 9) temp = 0;
			}
			if (s == 4) {
				if (temp == 16) temp = 0;
			}
			if (p[i][j] == temp && p[s - 1][s - 1] == 0) {
				continue;
			}
			else game = true;
		}
	return game;
}
void Game(int s, int choise_shuffle) {
	pa = Create(s);//к нулевому указателю присваиваем масив
	Inicial(pa, s);//инициализируем
	if (choise_shuffle == 0) {
		findZero(pa, s);
		do {
			system("cls");
			Print(pa, s);										//это если ручная мешалка
			cout << setw(64) << "~~~Размешивайте~~~" << endl << endl;
			cout << setw(69) << "~~~Начать играть - ENTER~~~" << endl;
			Move(pa, s, pi, pj);
		} while (key != 13);
	}
	if (choise_shuffle == 1) {                                 //если автомат мешает так
		Shufl(pa, s);//мешаем
	}
	findZero(pa, s);//ищем 0
	count_of_shift = 0;									//обнуление счетчика ходов
	clock_t start_time = clock();                          //начало таймера
	do {
		system("cls");
		Print(pa, s);											//сама игра
		Move(pa, s, pi, pj, 1);
	} while (key != 27 && Winn(pa, s));
	system("cls");
	if (key == 27) Menu(2, 0, 0);
	while (key != 27) {
		Print(pa, s);
		deletearr(pa, s);
		int waste_time = int(clock() - start_time) / CLOCKS_PER_SEC;
		int h, m, sec;
		h = waste_time / 60 / 60;
		m = (waste_time - h * 3600) / 60;
		sec = waste_time % 60;
		cout << setw(65) << "ВЫ ПОБЕДИЛИ!!!\n\n\n" << setw(67) << "Количество перестановок - " << count_of_shift << endl;
		cout << setw(58) << "Потраченое время - " << m << " минут " << sec << " секунд\n\n\n";
		cin.get();
		Menu(2, 0, 0);
	}
}
void Menu(int s, int choise_game, int choise_shuffle = 0) {
	int active_menu = s - 2;
	if (choise_game == 0 && s > 6) Game(3, choise_shuffle); //соответственно переходим к самой игре передавая значение мешалки и размер массива
	if (choise_game == 1 && s > 6) Game(4, choise_shuffle);
	do
	{
		system("cls");
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = s - 2; i < s; i++)
		{
			if (i > 5) break;									//если там s выйдет за пределы меню, он не будет выполнятся, лучше не придумал, но работает
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << menu[i] << " ";
		}
		//choise_game = 0;
		key = _getch();
		if (key == -32) key = _getch(); // Отлавливаем стрелочки
		switch (key)
		{
		case 72:case 119://верх
			if (active_menu > s - 2) {
				--active_menu;
				if (s <= 4)				//присваиваем выбор игры до выбора мешалки и потом не трогаем ибо потом он меняет значения в хлам
					choise_game = 0;
				if (s > 4)
					choise_shuffle = 0;
			}
			break;
		case 80:case 115://вниз
			if (active_menu < s - 1) {
				++active_menu;
				if (s <= 4)
					choise_game = 1;
				if (s > 4)                             //присвание значений мешалки и режима игры
					choise_shuffle = 1;
			}
			break;
		case 13:
			if (s) {
				switch (active_menu)
				{
				case 0:
					Menu(s + 2, choise_game);
					break;
				case 1:
					exit(0);
					break;
				default:									  //так же передаём выбор игры и режим мешалки
					Menu(s + 2, choise_game, choise_shuffle); // кароче если там s больше 2 будет то он будет просто это выполнять и проходить дальше по меню
					break;
				}
			}
		}
	} while (key != 27);
}
void main_game() {
	setlocale(LC_ALL, "");
	srand(unsigned int(NULL));
	SetConsoleTitle(L"Пятнашки"); //заголовок консоли
	ConsoleCursorVisible(false, 100);
	do {
		Menu(2, 0);
	} while (true);
}
