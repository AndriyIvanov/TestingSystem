#include "ServiceWindow.h"


#include <iostream>
#include <iomanip>

using namespace std;

COORD ServiceWindow::getCoord()
{	
	return COORD{ X_, Y_ };
}

short ServiceWindow::getColor()
{
	return color_;
}

void ServiceWindow::PrintWindow()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (WORD)((color_ << 4) | 15));  //Установка основного цвета окна (белый шрифт на фоне color_)

	COORD coord = { X_, Y_ };	

	SetConsoleOutputCP(866);
	SetConsoleCP(866);

	SetConsoleCursorPosition(console, coord);
	for (size_t i = 0; i < Height_; ++i)
	{
		SetConsoleCursorPosition(console, coord);
		cout << " " << setw(Width_-2) << setfill(' ') << " " << endl;
		coord.Y++;
	}
	SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));  //Возврат к цветам главного окна (желтый шрифт на зеленом фоне)

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
}
