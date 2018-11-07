#pragma once

#include <string>
#include <vector>
#include <utility>
#include "ServiceWindow.h"
#include "TestMainWindow.h"

using namespace std;
// Класс теста
class Test
{
	string Name_;													// Название теста
	vector <pair<string, size_t>> Questions_;						// string - вопрос, size_t - номер правильного ответа
	size_t CurrentQuestionNumber_;									// Номер текущего вопроса
	size_t CurrentAnswerNumber_;									// Номер текущего ответа
	size_t CurrentCorrectAnswer_;									// Номер правильного ответа для текущего вопроса
	vector <vector<string>> Answers_;
	vector <short> AnswersPositions_;								// Положение курсора для каждого из ответов
	size_t TotalCorrectAnswers_;									// Количество правильных ответов
	string PathToDataFile_;											// Путь к файлу с данными (вопросы + ответы)
	size_t Rating_;													// Оценка за тест
	short CurrentCursorPosition_;									// Положение курсора (координата Y)
	TestMainWindow window_;											// Главное окно теста
	int WaitingForKey();											// Ожидание нажатия клавиши										
	void ShowCursor(bool colored);									// Показ текущего курсора (colored = true - выделение цветом)
	void ActionKeyDownArrow();
	void ActionKeyUpArrow();
	void ActionKeyEnter();
	void KeyProcessing();											// Обработка нажатия клавиш
	void PrintString(string str);									// Печать строки с форматированием
	void ShowResult();												// Показ результатов теста

public:
	Test(string Name, string PathToDataFile);
	void AddQuestion(ServiceWindow wind);
	void DeleteQuestion(size_t Number);
	void ShowQuestion(size_t Number);
	void SaveToFile();
	size_t PassTest();
	
};

