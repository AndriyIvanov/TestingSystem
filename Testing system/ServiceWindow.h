#pragma once

#include <windows.h>

class ServiceWindow
{
	size_t Height_;
	size_t Width_;
	short X_;		//Координата Х левого верхнего угла
	short Y_;		//Координата Y левого верхнего угла
	short color_;	//Цвет фона окна
public:
	ServiceWindow(short X, short Y, size_t Height, size_t Width, short color) : Height_(Height), Width_(Width), X_(X), Y_(Y), color_(color) { };
	COORD getCoord();
	short getColor();
	void PrintWindow();
};

