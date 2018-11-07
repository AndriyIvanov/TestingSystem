#include "Button.h"

#include <windows.h>
#include <iostream>

Button::Button(short x, short y, string name)
{
	x_ = x;
	y_ = y;
	name_ = name;
}

void Button::PrintButton()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x_, y_ };
	SetConsoleCursorPosition(console, coord);
	SetConsoleTextAttribute(console, (WORD)((11 << 4) | 0)); //Установка цветов меню (черный шрифт на голубом фоне)
	cout << name_;
	SetConsoleTextAttribute(console, (WORD)((4 << 4) | 14));  //Возврат к цветам главного окна (желтый шрифт на бордовом фоне)
}
