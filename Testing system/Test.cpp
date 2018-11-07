#include "Test.h"

#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

Test::Test(string Name, string PathToDataFile)
{
	
	Name_ = Name;
	Rating_ = 0;
	CurrentQuestionNumber_ = 0;
	TotalCorrectAnswers_ = 0;
	PathToDataFile_ = PathToDataFile;
	fstream fin (PathToDataFile_, ios::in);
	if (!fin)
	{
		fin.open(PathToDataFile_, ios::out);
		fin.close();
	}
	else
	{
		while (!fin.eof())
		{
			string Question, Temp, Temp1;
			size_t CorrectAnswer, AnswerNumber;
			getline(fin, Question);
			if (Question != Temp1)
			{
				getline(fin, Temp);
				AnswerNumber = Temp[0] - '0';
				CorrectAnswer = Temp[2] - '0';
				Questions_.push_back(pair<string, size_t>(Question, CorrectAnswer));
				vector<string> Answers;
				for (size_t i = 0; i < AnswerNumber; ++i)
				{
					string Answer;
					getline(fin, Answer);
					Answers.push_back(Answer);
				}
				Answers_.push_back(Answers);
			}
		}
		fin.close();
	}
}

void Test::AddQuestion(ServiceWindow wind)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = wind.getCoord();
	coord.X++;
	coord.Y++;
	SetConsoleTextAttribute(console, (WORD)((wind.getColor() << 4) | 15));

	string Question, Answer;
	vector<string> Answers;
	size_t CorrectAnswerNumber, TotalAnswers;

	SetConsoleCursorPosition(console, coord);
	cout << "Введите вопрос:";
	coord.Y++;
	SetConsoleCursorPosition(console, coord);
	coord.Y--;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, Question);
	wind.PrintWindow();
	SetConsoleCursorPosition(console, coord);
	SetConsoleTextAttribute(console, (WORD)((wind.getColor() << 4) | 15));
	cout << "Укажите количество ответов: ";
	cin >> TotalAnswers;
	for (size_t i = 0; i < TotalAnswers; ++i)
	{
		wind.PrintWindow();
		SetConsoleCursorPosition(console, coord);
		SetConsoleTextAttribute(console, (WORD)((wind.getColor() << 4) | 15));
		cout << "Введите ответ №" << i + 1 << ":";
		coord.Y++;
		SetConsoleCursorPosition(console, coord);
		coord.Y--;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, Answer);
		Answers.push_back(Answer);
	}
	wind.PrintWindow();
	SetConsoleCursorPosition(console, coord);
	SetConsoleTextAttribute(console, (WORD)((wind.getColor() << 4) | 15));
	cout << "Укажите номер правильного ответа: ";
	cin >> CorrectAnswerNumber;
	Questions_.push_back(pair<string, size_t>(Question, CorrectAnswerNumber));
	Answers_.push_back(Answers);
	SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));  //Возврат к цветам главного окна (желтый шрифт на зеленом фоне)
}

void Test::DeleteQuestion(size_t Number)
{
	if (Number >= 0 && Number < Questions_.size())
	{
		Questions_.erase(Questions_.begin() + Number);
		Answers_.erase(Answers_.begin() + Number);
	}
	else
		cerr << "Неправильный индекс!\n";

}

void Test::ShowQuestion(size_t Number)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	short X = short((69 - Name_.length()) / 2);
	COORD coord{ X, 2 };
	SetConsoleCursorPosition(console, coord);
	SetConsoleTextAttribute(console, (WORD)((2 << 4) | 10));			//Цвет выделения строки (салатовый шрифт на зеленом фоне)
	cout << Name_;		
	SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));			//Возврат к цветам главного окна (желтый шрифт на зеленом фоне)
	coord={ 1, 6 };
	if (Number >= 0 && Number < Questions_.size())
	{
		SetConsoleCursorPosition(console, coord);
		SetConsoleTextAttribute(console, (WORD)((2 << 4) | 10));		//Цвет выделения строки (салатовый шрифт на зеленом фоне)
		cout << "Вопрос:";
		SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));		//Возврат к цветам главного окна (желтый шрифт на зеленом фоне)
		coord.Y = 8;
		CurrentCursorPosition_ = coord.Y;
		SetConsoleCursorPosition(console, coord);
		PrintString(Questions_[Number].first);
		coord.Y = 15;
		short deltaY = 2;
		SetConsoleCursorPosition(console, coord);
		SetConsoleTextAttribute(console, (WORD)((2 << 4) | 10));		//Цвет выделения строки (салатовый шрифт на зеленом фоне)
		cout << "Варианты ответов:";
		SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));		//Возврат к цветам главного окна (желтый шрифт на зеленом фоне)
		coord.Y += deltaY;
		CurrentCursorPosition_ = coord.Y;
		SetConsoleCursorPosition(console, coord);
		AnswersPositions_.clear();
		for (size_t j = 0; j < Answers_[Number].size(); ++j)
		{		
			AnswersPositions_.push_back(CurrentCursorPosition_);
			PrintString(Answers_[Number][j]);
			CurrentCursorPosition_ += deltaY;
		}
		coord.Y = 32;
		coord.X = 2;
		SetConsoleCursorPosition(console, coord);
		SetConsoleTextAttribute(console, (WORD)((2 << 4) | 10));		//Цвет выделения строки (салатовый шрифт на зеленом фоне)
		cout << "Выберите правильный ответ при помощи стрелок курсора и нажмите Enter";
		SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));		//Возврат к цветам главного окна (желтый шрифт на зеленом фоне)
	}
	else
		cerr << "Неправильный индекс!\n";
}

void Test::SaveToFile()
{
	fstream fout(PathToDataFile_, ios::out);
	for (size_t i = 0; i < Questions_.size(); ++i)
	{
		fout << Questions_[i].first << endl;
		size_t CorrectAnswerNumber = Questions_[i].second;
		size_t TotalAnswers = Answers_[i].size();
		string Temp;
		Temp.push_back('0' + TotalAnswers);
		Temp.push_back(',');
		Temp.push_back('0' + CorrectAnswerNumber);
		fout << Temp << endl;							//Вывод в файл общего кол-ва ответов и номера правильного ответа (через запятую)
		for (size_t j=0; j<Answers_[i].size(); ++j)
			fout << Answers_[i][j] << endl;
	}
}

size_t Test::PassTest()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	window_.PrintWindow();
	for (size_t i = 0; i < Questions_.size(); ++i)
	{
		ShowQuestion(i);
		CurrentQuestionNumber_ = i;
		CurrentAnswerNumber_ = 1;
		CurrentCorrectAnswer_ = Questions_[i].second;
		CurrentCursorPosition_ = AnswersPositions_[0];			 //Курсор на первый ответ
		ShowCursor(true);
		KeyProcessing();
	}
	ShowResult();
	return TotalCorrectAnswers_ * 12 / Questions_.size();
}

int Test::WaitingForKey()
{
	while (true)
	{
		int button = _getch();
		if (button == 72 || button == 80 ||									 // Стрелки курсора (вверх/вниз)
			button == 13)													 // Enter
			return button;
	}
}

void Test::KeyProcessing()
{
	while (true)
	{
		int button = WaitingForKey();
		switch (button)
		{
			case 13:  //Enter
			{
				ActionKeyEnter();
				return;
			}
			case 72: //Стрелка вверх
			{
				ActionKeyUpArrow();
				break;
			}
			case 80: //Стрелка вниз
			{
				ActionKeyDownArrow();
				break;
			}
		}
	}
}


void Test::ActionKeyDownArrow()
{
	CurrentCursorPosition_ = AnswersPositions_[CurrentAnswerNumber_ - 1];
	ShowCursor(false);
	if (CurrentAnswerNumber_ == Answers_[CurrentQuestionNumber_].size())
	{
		CurrentAnswerNumber_ = 1;
	}
	else
	{
		CurrentAnswerNumber_++;	
	}
	CurrentCursorPosition_ = AnswersPositions_[CurrentAnswerNumber_ - 1];
	ShowCursor(true);
}

void Test::ActionKeyUpArrow()
{
	CurrentCursorPosition_ = AnswersPositions_[CurrentAnswerNumber_ - 1];
	ShowCursor(false);
	if (CurrentAnswerNumber_ == 1)
	{
		CurrentAnswerNumber_ = Answers_[CurrentQuestionNumber_].size();
	}
	else
	{
		CurrentAnswerNumber_--;
	}
	CurrentCursorPosition_ = AnswersPositions_[CurrentAnswerNumber_ - 1];
	ShowCursor(true);
}

void Test::ActionKeyEnter()
{
	if (CurrentAnswerNumber_ == CurrentCorrectAnswer_) TotalCorrectAnswers_++;
	window_.PrintWindow();
}

void Test::ShowCursor(bool colored)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 1, AnswersPositions_[CurrentAnswerNumber_-1] };
	SetConsoleCursorPosition(console, coord);
	if (colored) SetConsoleTextAttribute(console, (WORD)((14 << 4) | 0));	//Цвет выделения строки (черный шрифт на желтом фоне)
	PrintString(Answers_[CurrentQuestionNumber_][CurrentAnswerNumber_ - 1]);
	if (colored) SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));	//Возврат к цветам главного окна (желтый шрифт на зеленом фоне)
}

void Test::PrintString(string str)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 1, CurrentCursorPosition_ };
	SetConsoleCursorPosition(console, coord);
	if (str.length() < 68)
	{
		cout << str;
	}
	else
	{
		short count = 68;
		string Temp = str.substr(0, count);
		while (Temp.back() != ' ')				//Нахождение конца последнего слова для разбиения строки
		{
			Temp.pop_back();
			count--;
		}
		cout << Temp;
		CurrentCursorPosition_++;
		PrintString(str.substr(count, -1));
	}
}

void Test::ShowResult()
{
	ServiceWindow servWindow(10, 10, 10, 48, 9);
	servWindow.PrintWindow();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = servWindow.getCoord();
	coord.X=25;
	coord.Y++;
	SetConsoleCursorPosition(console, coord);
	SetConsoleTextAttribute(console, (WORD)((servWindow.getColor() << 4) | 15));
	cout << "Тест завершен!";
	coord.X = 17;
	coord.Y+=3;
	SetConsoleCursorPosition(console, coord);
	cout << "Набрано баллов из 12 возможных: " << TotalCorrectAnswers_*12 / Questions_.size();
	coord.X = 19;
	coord.Y += 4;
	SetConsoleCursorPosition(console, coord);
	cout << "Нажмите Enter для продолжения";
	int button;
	do
	{
		button = _getch();
	} while (button != 13);
	SetConsoleTextAttribute(console, (WORD)((2 << 4) | 14));
}

