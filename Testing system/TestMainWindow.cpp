#include "TestMainWindow.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

TestMainWindow::TestMainWindow(size_t Height, size_t Width)
{
	Height_ = Height; 
	Width_ = Width;
}

void TestMainWindow::PrintWindow()
{
	system("color 2E");								//Установка основных цветов окна (желтый шрифт на зеленом фоне)
	string WindowSize = "mode con cols=";
	WindowSize += to_string(Width_);
	WindowSize += " lines=";
	WindowSize += to_string(Height_);
	system(WindowSize.c_str());						//Установка размера окна
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, false };
	SetConsoleCursorInfo(console, &cursor);			//Делаем невидимым курсор
													
	SetConsoleOutputCP(866);
	SetConsoleCP(866);

	short length = 70;								//Ширина окна

	cout << char(201) << setw(length) << setfill(char(205)) << char(187) << endl;
	for (size_t i = 0; i < 4; ++i)
		cout << char(186) << setw(length) << setfill(' ') << char(186) << endl;
	cout << char(204) << setw(length) << setfill(char(205)) << char(185) << endl;
	for (size_t i = 0; i < 8; ++i)
		cout << char(186) << setw(length) << setfill(' ') << char(186) << endl;
	cout << char(204) << setw(length) << setfill(char(205)) << char(185) << endl;
	for (size_t i = 0; i < 15; ++i)
		cout << char(186) << setw(length) << setfill(' ') << char(186) << endl;
	cout << char(200) << setw(length) << setfill(char(205)) << char(188) << endl;

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
}

