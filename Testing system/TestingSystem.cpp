#include "TestingSystem.h"
#include "Test.h"
#include "TotalStatisticWindow.h"
#include "Button.h"

#include <windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

TestingSystem::TestingSystem()
{
	PathToLoginFile_= "access.dat";							
	PathtoTest_DiscreteMathematics_ = "Test_Discrete Mathematics.txt";	
	PathtoTest_MathematicalAnalysis_ = "Test_Mathematical Analysis.txt";
	PathtoTest_Mechanics_ = "Test_Mechanics.txt";
	PathtoTest_QuantumPhysics_ = "Test_Quantum Physics.txt";
	ifstream fin("access.dat");
	if (!fin.is_open())
	{
		FirstInput();
		Administration();
	}
	else
	{
		ReadInfoFromFile();
		UserLogin();
		if (CurrentUserLogin_ == AdminLogin_)
			Administration();
		else
			ChooseTest();
	}
}

TestingSystem::~TestingSystem()
{
	SaveInfoToFile();
}

void TestingSystem::FirstInput()
{
	Access AdminAccess;
	window_.PrintWindow();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	string Temp = "������ ���� � �������!";
	short X = short((50 - Temp.length()) / 2);
	COORD coord{ X, 2 };
	SetConsoleCursorPosition(console, coord);
	cout << Temp;

	Temp = "���������� ������� �������";
	X = short((50 - Temp.length()) / 2);
	coord={ X, 4 };
	SetConsoleCursorPosition(console, coord);
	cout << Temp;
	Temp = "������ ��������������!";
	X = short((50 - Temp.length()) / 2);
	coord = { X, 5 };
	SetConsoleCursorPosition(console, coord);
	cout << Temp;

	Temp = "������� Enter ��� �����������.";
	X = short((50 - Temp.length()) / 2);
	coord = { X, 10 };
	SetConsoleCursorPosition(console, coord);
	cout << Temp;
	int button;
	do
	{
		button = _getch();
	} while (button != 13);
	NewUserRegistration();
	AdminLogin_ = CurrentUserLogin_;
}

void TestingSystem::NewUserRegistration()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	bool Key;												// ������� ������� ����� � ���� (true - ��� ������� � ����)
	Access NewUser;
	COORD coord;
	do
	{
		Key = false;
		window_.PrintWindow();

		string Name{ "����������� ������ ������������" };
		short X = short((50 - Name.length()) / 2);
		coord={ X, 1 };
		SetConsoleCursorPosition(console, coord);
		cout << Name;

		coord = { 1, 3 };
		SetConsoleCursorPosition(console, coord);
		cout << "������� ��� ������������: ";
		string Temp;
		coord.Y++;
		SetConsoleCursorPosition(console, coord);
		cin >> Temp;
		for (auto it : AccessInformation_)
			if (it.Login == Temp) Key = true;				// ��� ������������ ��� ����������
		if (Key)
		{
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "����� ��� ��� ����������!";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "������� Enter ��� �����������.";
			int button;
			do
			{
				button = _getch();
			} while (button != 13);
		}
		else
		{
			NewUser.Login = Temp;
			
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "������� ������: ";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cin >> Temp;
			NewUser.Password = Temp;
			
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "������� ���: ";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, Temp);
			NewUser.Name = Temp;
			
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "������� �����: ";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, Temp);
			NewUser.Address = Temp;

			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "������� �������: ";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cin >> Temp;
			NewUser.Phone = Temp;
		}
	} while (Key);
	AccessInformation_.push_back(NewUser);
	CurrentUserLogin_ = NewUser.Login;
	CurrentUserPassword_ = NewUser.Password;
	SaveInfoToFile();
	TestResults_.insert(pair<string, TestsResult> (NewUser.Login,{ 0, 0, 0, 0 }));
	coord.Y+=5;
	SetConsoleCursorPosition(console, coord);
	cout << "������� Enter ��� �����������.";
	int button;
	do
	{
		button = _getch();
	} while (button != 13);
}

void TestingSystem::SaveInfoToFile()
{
	ofstream fout("access.dat");
	for (size_t i=0; i< AccessInformation_.size(); ++i)
	{
		fout << Coding(AccessInformation_[i].Login) << endl;
		fout << Coding(AccessInformation_[i].Password) << endl;
		fout << Coding(AccessInformation_[i].Name) << endl;
		fout << Coding(AccessInformation_[i].Address) << endl;
		fout << Coding(AccessInformation_[i].Phone) << endl;
		fout << TestResults_[AccessInformation_[i].Login].DiscrMath << endl;
		fout << TestResults_[AccessInformation_[i].Login].MathAnalys << endl;
		fout << TestResults_[AccessInformation_[i].Login].Mechanics << endl;
		fout << TestResults_[AccessInformation_[i].Login].QuantPhys << endl;
	}
	fout.close();
}

void TestingSystem::ReadInfoFromFile()
{
	ifstream fin("access.dat");
	if (!fin.is_open())
		cerr << "������ �������� �����!" << endl;
	string Temp;
	Access UserInfo;
	TestsResult UserResults;
	AccessInformation_.clear();
	while (!fin.eof())
	{
		getline(fin, Temp);
		if (Temp == "") break;
		Temp = Encoding(Temp);
		UserInfo.Login = Temp;

		getline(fin, Temp);
		Temp = Encoding(Temp);	
		UserInfo.Password = Temp;

		getline(fin, Temp);
		Temp = Encoding(Temp);
		UserInfo.Name = Temp;

		getline(fin, Temp);
		Temp = Encoding(Temp);
		UserInfo.Address = Temp;

		getline(fin, Temp);
		Temp = Encoding(Temp);
		UserInfo.Phone = Temp;

		AccessInformation_.push_back(UserInfo);

		getline(fin, Temp);
		UserResults.DiscrMath = stoi(Temp);

		getline(fin, Temp);
		UserResults.MathAnalys = stoi(Temp);

		getline(fin, Temp);
		UserResults.Mechanics = stoi(Temp);

		getline(fin, Temp);
		UserResults.QuantPhys = stoi(Temp);

		TestResults_.insert(pair<string, TestsResult>(UserInfo.Login, UserResults));
	}
	AdminLogin_ = AccessInformation_[0].Login;
	fin.close();
}

string TestingSystem::Coding(string str)
{
	string Temp;
	for (auto it : str)
		Temp.push_back(it + 1);	
	return Temp;
}

string TestingSystem::Encoding(string str)
{
	string Temp;
	for (auto it : str)
		Temp.push_back(it - 1);
	return Temp;
}

void TestingSystem::UserLogin()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	bool Key;
	do
	{
		Key = false;
		window_.PrintWindow();

		string Name{ "���� � �������" };
		short X = short((50 - Name.length()) / 2);
		coord={ X, 1 };
		SetConsoleCursorPosition(console, coord);
		cout << Name;

		coord = { 1, 3 };
		SetConsoleCursorPosition(console, coord);
		cout << "������� ��� ������������: ";
		string Temp;
		coord.Y++;
		SetConsoleCursorPosition(console, coord);
		cin >> Temp;
		for (auto it : AccessInformation_)
			if (it.Login == Temp)
			{
				Key = true;
				CurrentUserLogin_ = Temp;
				CurrentUserPassword_ = it.Password;
			}
		if (!Key)
		{
			Button ButtonF2(10, 28, "F2 New User");
			Button ButtonF10(25, 28, "F10 Exit");
			ButtonF2.PrintButton();
			ButtonF10.PrintButton();
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "����� ��� �� ����������!";
			coord.Y+=3;
			SetConsoleCursorPosition(console, coord);
			cout << "������� ������������ ���";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "��� ��������������� �����.";
			coord.Y+=3;
			SetConsoleCursorPosition(console, coord);
			cout << "������� Enter ��� �����������";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cout << "��� F2 ��� ����������� ������ ������������.";
			switch (WaitingForKey(vector<int>({ 13, 60, 68 })))
			{
				case 13:  //Enter
				{
					break;
				}
				case 60: //F2
				{
					NewUserRegistration();
					break;
				}
				case 68: //F10
				{
					exit(1);
				}
			}
		}
		else
		{
			coord.Y += 2;
			SetConsoleCursorPosition(console, coord);
			cout << "������� ������:";
			coord.Y++;
			SetConsoleCursorPosition(console, coord);
			cin >> Temp;
			if (CurrentUserPassword_ != Temp)
			{
				Button ButtonF2(10, 28, "F2 New User");
				Button ButtonF10(25, 28, "F10 Exit");
				ButtonF2.PrintButton();
				ButtonF10.PrintButton();
				coord.Y += 2;
				SetConsoleCursorPosition(console, coord);
				cout << "������������ ��� ������������ ��� ������!";
				coord.Y+=2;
				SetConsoleCursorPosition(console, coord);
				SetConsoleCursorPosition(console, coord);
				cout << "������� Enter ��� �����������";
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				cout << "��� F2 ��� ����������� ������ ������������.";
				switch (WaitingForKey(vector<int>({ 13, 60, 68 })))
				{
					case 13:  //Enter
					{
						break;
					}
					case 60: //F2
					{
						NewUserRegistration();
						break;
					}
					case 68: //F10
					{
						exit(1);
					}
				}
				Key = false;
			}
		}

	} while (!Key);

}


int TestingSystem::WaitingForKey(vector<int> Keys)
{
	int button;
	bool Key = true;
	while (Key)
	{
		button = _getch();
		for (auto it: Keys)
			if (button == it) Key = false;
	}
	return button;
}


void TestingSystem::ChooseTest()
{
	while (true)
	{
		window_.PrintWindow();
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		string Name{ "��� ������������: " };
		Name += CurrentUserLogin_;
		short X = short((50 - Name.length()) / 2);
		COORD coord{ X, 2 };
		SetConsoleCursorPosition(console, coord);
		cout << Name;
		coord.X = 1;
		coord.Y += 3;
		SetConsoleCursorPosition(console, coord);
		cout << "�������� ����: ";
		coord.Y += 2;
		SetConsoleCursorPosition(console, coord);
		Button buttonF1(coord.X, coord.Y, "F1 - ���������� ����������");
		buttonF1.PrintButton();
		coord.Y += 2;

		Button buttonF2(coord.X, coord.Y, "F2 - �������������� ������");
		buttonF2.PrintButton();
		coord.Y += 2;

		Button buttonF3(coord.X, coord.Y, "F3 - ��������             ");
		buttonF3.PrintButton();
		coord.Y += 2;

		Button buttonF4(coord.X, coord.Y, "F4 - ��������� ������     ");
		buttonF4.PrintButton();
		coord.Y += 4;

		Button buttonF8(coord.X, coord.Y, "F8 - ���������� ����������");
		buttonF8.PrintButton();
		coord.Y += 2;

		Button buttonF10(coord.X, coord.Y, "F10 - �����");
		buttonF10.PrintButton();
		switch (WaitingForKey(vector<int>({ 59, 60, 61, 62, 66, 68 })))
		{
			case 59: //F1
			{
				Test test1("���� �� ���������� ����������", "Test_Discrete Mathematics.txt");
				TestResults_[CurrentUserLogin_].DiscrMath = test1.PassTest();
				break;
			}
			case 60: //F2
			{
				Test test2("���� �� ��������������� �������", "Test_Mathematical Analysis.txt");
				TestResults_[CurrentUserLogin_].MathAnalys = test2.PassTest();
				break;
			}
			case 61: //F3
			{
				Test test3("���� �� ��������", "Test_Mechanics.txt");
				TestResults_[CurrentUserLogin_].Mechanics = test3.PassTest();
				break;
			}
			case 62: //F4
			{
				Test test4("���� �� ��������� ������", "Test_Quantum Physics.txt");
				TestResults_[CurrentUserLogin_].QuantPhys = test4.PassTest();
				break;
			}
			case 66: //F8
			{
				ServiceWindow ResultsWindow (5, 8, 13, 39, 9);
				ResultsWindow.PrintWindow();
				SetConsoleTextAttribute(console, (WORD)((ResultsWindow.getColor() << 4) | 15));
				coord = ResultsWindow.getCoord();
				coord.X += 10;
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				cout << "������� ����������:";
				coord.X -= 9;
				coord.Y+=2;
				SetConsoleCursorPosition(console, coord);
				cout << "���������� ����������: " << TestResults_[CurrentUserLogin_].DiscrMath;
				coord.Y += 2;
				SetConsoleCursorPosition(console, coord);
				cout << "�������������� ������: " << TestResults_[CurrentUserLogin_].MathAnalys;
				coord.Y += 2;
				SetConsoleCursorPosition(console, coord);
				cout << "��������             : " << TestResults_[CurrentUserLogin_].Mechanics;
				coord.Y += 2;
				SetConsoleCursorPosition(console, coord);
				cout << "��������� ������     : " << TestResults_[CurrentUserLogin_].QuantPhys;
				coord.Y += 2;
				coord.X += 4;
				SetConsoleCursorPosition(console, coord);
				cout << "������� Enter ��� �����������";
				WaitingForKey(vector<int>({ 13 }));
				SetConsoleTextAttribute(console, (WORD)((4 << 4) | 14));  //������� � ������ �������� ���� (������ ����� �� �������� ����)
				break;
			}
			case 68: //F10
			{
				SaveInfoToFile();
				if (CurrentUserLogin_ == AdminLogin_) Administration();
				else exit(1);
			}
		}
	}
}


void TestingSystem::Administration()
{
	while (true)
	{
		window_.PrintWindow();
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		string Name{ "�������������: " };
		Name += AdminLogin_;
		short X = short((50 - Name.length()) / 2);
		COORD coord{ X, 2 };
		SetConsoleCursorPosition(console, coord);
		cout << Name;
		coord.X = 1;
		coord.Y += 4;
		
		SetConsoleCursorPosition(console, coord);
		Button buttonF2(coord.X, coord.Y, "F2 - �������� ������������  ");
		buttonF2.PrintButton();
		coord.Y += 2;

		Button buttonF3(coord.X, coord.Y, "F3 - ������� ������������   ");
		buttonF3.PrintButton();
		coord.Y += 2;

		Button buttonF4(coord.X, coord.Y, "F4 - ������� ������������   ");
		buttonF4.PrintButton();
		coord.Y += 2;

		Button buttonF5(coord.X, coord.Y, "F5 - �������� ����� � ������");
		buttonF5.PrintButton();
		coord.Y += 2;

		Button buttonF6(coord.X, coord.Y, "F6 - �������� ����������    ");
		buttonF6.PrintButton();
		coord.Y += 2;

		Button buttonF7(coord.X, coord.Y, "F7 - ������� � ������       ");
		buttonF7.PrintButton();
		coord.Y += 4;

		Button buttonF10(coord.X, coord.Y, "F10 - �����");
		buttonF10.PrintButton();

		switch (WaitingForKey(vector<int>({ 60, 61, 62, 63, 64, 65, 68 })))
		{
			case 60: //F2 - �������� ������������
			{
				NewUserRegistration();
				break;
			}
			case 61: //F3 - ������� ������������
			{
				ServiceWindow ResultsWindow(5, 8, 13, 39, 9);
				ResultsWindow.PrintWindow();
				SetConsoleTextAttribute(console, (WORD)((ResultsWindow.getColor() << 4) | 15));
				coord = ResultsWindow.getCoord();
				coord.X++;
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				cout << "������� ����� ������������";
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				cout << "��� ��������: ";
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				string Temp;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, Temp);
				coord.Y += 2;
				SetConsoleCursorPosition(console, coord);
				if (Temp == AdminLogin_)
				{
					cout << "������������� �� �����";
					coord.Y++;
					SetConsoleCursorPosition(console, coord);
					cout << "���� ������!";
				}
				else
				{
					if (!DeleteUser(Temp))
					{
						cout << "����� ������������";
						coord.Y++;
						SetConsoleCursorPosition(console, coord);
						cout << "�� ����������!";
					}
					else
					{
						cout << "������������ � ������� ";
						coord.Y++;
						SetConsoleCursorPosition(console, coord);
						cout << Temp;
						coord.Y++;
						SetConsoleCursorPosition(console, coord);
						cout << "������!";
					}
				}
				coord.Y += 2;
				SetConsoleCursorPosition(console, coord);
				cout << "������� Enter ��� �����������";
				WaitingForKey(vector<int>({ 13 }));
				SetConsoleTextAttribute(console, (WORD)((4 << 4) | 14));  //������� � ������ �������� ���� (������ ����� �� �������� ����)
				break;
			}
			case 62: //F4 - ������� ������������
			{
				UserLogin();
				if (CurrentUserLogin_ != AdminLogin_)
					ChooseTest();
				break;
			}
			case 63: //F5 - �������� ����� � ������
			{
				ServiceWindow ResultsWindow(5, 8, 13, 39, 9);
				ResultsWindow.PrintWindow();
				SetConsoleTextAttribute(console, (WORD)((ResultsWindow.getColor() << 4) | 15));
				coord = ResultsWindow.getCoord();
				coord.X++;
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				cout << "������� ����� �����:";
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				string Temp;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, Temp);
				bool Flag = false;
				for (auto it: AccessInformation_)
					if (it.Login == Temp)
					{
						coord.Y+=2;
						SetConsoleCursorPosition(console, coord);
						cout << "����� ����� ��� ����������!";
						coord.Y ++;
						SetConsoleCursorPosition(console, coord);
						cout << "��������� ����������!";
						coord.Y += 4;
						SetConsoleCursorPosition(console, coord);
						Flag = true;									// ������� ������� ������ � ���� 
						cout << "������� Enter ��� �����������.";
						WaitingForKey(vector<int>({ 13 }));
					}
				if (Flag) break;
				AdminLogin_ = Temp;
				CurrentUserLogin_ = Temp;
				AccessInformation_[0].Login = AdminLogin_;

				ResultsWindow.PrintWindow();
				SetConsoleTextAttribute(console, (WORD)((ResultsWindow.getColor() << 4) | 15));
				coord = ResultsWindow.getCoord();
				coord.X++;
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				cout << "������� ����� ������:";
				coord.Y++;
				SetConsoleCursorPosition(console, coord);
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				getline(cin, Temp);
				AccessInformation_[0].Password = Temp;
				CurrentUserPassword_ = Temp;
				SaveInfoToFile();
				SetConsoleTextAttribute(console, (WORD)((4 << 4) | 14));  //������� � ������ �������� ���� (������ ����� �� �������� ����)
				break;
			}

			case 64: //F6 - �������� ����������
			{	
				TotalStatisticWindow wind;
				wind.PrintWindow();
				Name = "���������� �� ���� �������������";
				X = short((72 - Name.length()) / 2);
				coord = { X, 1 };
				SetConsoleCursorPosition(console, coord);
				cout << Name << endl << endl;
				cout << setw(70) << setfill('-') << "-" << endl;
				for (size_t i = 0; i < AccessInformation_.size(); ++i)
				{
					cout << "�����:\t" << AccessInformation_[i].Login;
					if (i == 0) cout << "\t\t\t - �������������" << endl;
					else cout << endl;
					cout << "������:\t" << AccessInformation_[i].Password << endl;
					cout << "���:\t" << AccessInformation_[i].Name << endl;
					cout << "�����:\t" << AccessInformation_[i].Address << endl;
					cout << "�������:\t" << AccessInformation_[i].Phone << endl;
					cout << "���������� ����������: " << TestResults_[AccessInformation_[i].Login].DiscrMath << endl;
					cout << "�������������� ������: " << TestResults_[AccessInformation_[i].Login].MathAnalys << endl;
					cout << "��������             : " << TestResults_[AccessInformation_[i].Login].Mechanics << endl;
					cout << "��������� ������     : " << TestResults_[AccessInformation_[i].Login].QuantPhys << endl;
					cout << setw(70) << setfill('-') << "-" << endl;
				}
				cout << "\n\n\n" << setw(50) << right << setfill(' ') << "������� Enter ��� �����������" << endl;
				WaitingForKey(vector<int>({ 13 }));
				break;
			}
			case 65: //F7 - ������� � ������
			{
				ChooseTest();
				break;
			}
			case 68: //F10
			{
				SaveInfoToFile();
				exit(1);
			}
		}
	}
}

bool TestingSystem::DeleteUser(string Login)
{
	for (size_t i = 0; i < AccessInformation_.size(); ++i)
		if (AccessInformation_[i].Login == Login)
		{
			string Temp = AccessInformation_[i].Login;
			AccessInformation_.erase(AccessInformation_.begin()+i);
			TestResults_.erase(Temp);
			SaveInfoToFile();
			return true;
		}
	return false;
}