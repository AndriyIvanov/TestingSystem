#pragma once
#include <string>

using namespace std;

class Button
{
	short x_;		//���������� ������ �� �����������
	short y_;		//���������� ������ �� ���������
	string name_;	//������� ������
public:
	Button(short x, short y, string name);
	void PrintButton();
};

