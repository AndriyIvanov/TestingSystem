#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "MainWindow.h"

using namespace std;

struct Access 
{
	string Login;
	string Password;
	string Name;
	string Address;
	string Phone;
};

struct TestsResult
{
	size_t DiscrMath;
	size_t MathAnalys;
	size_t Mechanics;
	size_t QuantPhys;
};

// ����� �������� �������
class TestingSystem
{
	string PathToLoginFile_;							// ���� � ����� � �������� � ��������
	string PathToTestResults_;							// ���� � ����� � ������������ ������������
	string PathtoTest_DiscreteMathematics_;				// ���� � ����� � ������� �� ���������� ����������
	string PathtoTest_MathematicalAnalysis_;			// ���� � ����� � ������� �� ��������������� �������
	string PathtoTest_Mechanics_;						// ���� � ����� � ������� �� ��������
	string PathtoTest_QuantumPhysics_;					// ���� � ����� � ������� �� ��������� ������
	vector<Access> AccessInformation_;					// ���������� �� ���� �������������
	map<string, TestsResult> TestResults_;				// ���������� ������������ �� ���� �������������, ���� - �����
	string CurrentUserLogin_;							// ����� �������� ������������ �������
	string CurrentUserPassword_;						// ������ �������� ������������ �������
	string AdminLogin_;									// ����� ��������������
	MainWindow window_;									// ������� ����
	void SaveInfoToFile();								// ���������� ���������� � ����
	void ReadInfoFromFile();							// ������ ���������� �� �����
	string Coding(string str);							// ����������� ������
	string Encoding(string str);						// �������������� ������
	void UserLogin();									// ���� � �������
	int WaitingForKey(vector<int> Keys);				// �������� ������� �������
	void FirstInput();									// ������ ���� � �������
	void NewUserRegistration();							// ����������� ������ ������������
	void ChooseTest();									// ����� ������
	void Administration();								// �����������������
	bool DeleteUser(string Login);						// ������� ������������, ���������� true � ������ ��������� ��������


public:
	TestingSystem();
	~TestingSystem();
};

