#include "TotalStatisticWindow.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

TotalStatisticWindow::TotalStatisticWindow(size_t Height, size_t Width)
{
	Height_ = Height;
	Width_ = Width;
}

void TotalStatisticWindow::PrintWindow()
{
	system("color 4E");								//Установка основных цветов окна (желтый шрифт на бордовом фоне)
	string WindowSize = "mode con cols=";
	WindowSize += to_string(Width_);
	WindowSize += " lines=";
	WindowSize += to_string(Height_);
	system(WindowSize.c_str());						//Установка размера окна
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord{ 72, 80 };
	SetConsoleScreenBufferSize(console, coord);		//Увеличиваем буфер консоли окна
	CONSOLE_CURSOR_INFO cursor = { 1, false };
	SetConsoleCursorInfo(console, &cursor);			//Делаем невидимым курсор
}
