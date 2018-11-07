#pragma once

#include <windows.h>

class ServiceWindow
{
	size_t Height_;
	size_t Width_;
	short X_;		//���������� � ������ �������� ����
	short Y_;		//���������� Y ������ �������� ����
	short color_;	//���� ���� ����
public:
	ServiceWindow(short X, short Y, size_t Height, size_t Width, short color) : Height_(Height), Width_(Width), X_(X), Y_(Y), color_(color) { };
	COORD getCoord();
	short getColor();
	void PrintWindow();
};

