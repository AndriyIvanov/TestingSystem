#pragma once

#include <string>
#include <vector>
#include <utility>
#include "ServiceWindow.h"
#include "TestMainWindow.h"

using namespace std;
// ����� �����
class Test
{
	string Name_;													// �������� �����
	vector <pair<string, size_t>> Questions_;						// string - ������, size_t - ����� ����������� ������
	size_t CurrentQuestionNumber_;									// ����� �������� �������
	size_t CurrentAnswerNumber_;									// ����� �������� ������
	size_t CurrentCorrectAnswer_;									// ����� ����������� ������ ��� �������� �������
	vector <vector<string>> Answers_;
	vector <short> AnswersPositions_;								// ��������� ������� ��� ������� �� �������
	size_t TotalCorrectAnswers_;									// ���������� ���������� �������
	string PathToDataFile_;											// ���� � ����� � ������� (������� + ������)
	size_t Rating_;													// ������ �� ����
	short CurrentCursorPosition_;									// ��������� ������� (���������� Y)
	TestMainWindow window_;											// ������� ���� �����
	int WaitingForKey();											// �������� ������� �������										
	void ShowCursor(bool colored);									// ����� �������� ������� (colored = true - ��������� ������)
	void ActionKeyDownArrow();
	void ActionKeyUpArrow();
	void ActionKeyEnter();
	void KeyProcessing();											// ��������� ������� ������
	void PrintString(string str);									// ������ ������ � ���������������
	void ShowResult();												// ����� ����������� �����

public:
	Test(string Name, string PathToDataFile);
	void AddQuestion(ServiceWindow wind);
	void DeleteQuestion(size_t Number);
	void ShowQuestion(size_t Number);
	void SaveToFile();
	size_t PassTest();
	
};

