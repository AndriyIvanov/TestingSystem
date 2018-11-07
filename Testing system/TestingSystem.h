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

// Класс тестовой системы
class TestingSystem
{
	string PathToLoginFile_;							// Путь к файлу с логинами и паролями
	string PathToTestResults_;							// Путь к файлу с результатами тестирования
	string PathtoTest_DiscreteMathematics_;				// Путь к файлу с тестами по дискретной математике
	string PathtoTest_MathematicalAnalysis_;			// Путь к файлу с тестами по математическому анализу
	string PathtoTest_Mechanics_;						// Путь к файлу с тестами по механике
	string PathtoTest_QuantumPhysics_;					// Путь к файлу с тестами по квантовой физике
	vector<Access> AccessInformation_;					// Информация по всем пользователям
	map<string, TestsResult> TestResults_;				// Результаты тестирования по всем пользователям, ключ - логин
	string CurrentUserLogin_;							// Логин текущего пользователя системы
	string CurrentUserPassword_;						// Пароль текущего пользователя системы
	string AdminLogin_;									// Логин администратора
	MainWindow window_;									// Главное окно
	void SaveInfoToFile();								// Сохранение информации в файл
	void ReadInfoFromFile();							// Чтение информации из файла
	string Coding(string str);							// Кодирование строки
	string Encoding(string str);						// Раскодирование строки
	void UserLogin();									// Вход в систему
	int WaitingForKey(vector<int> Keys);				// Ожидание нажатия клавиши
	void FirstInput();									// Первый вход в систему
	void NewUserRegistration();							// Регистрация нового пользователя
	void ChooseTest();									// Выбор тестов
	void Administration();								// Администрирование
	bool DeleteUser(string Login);						// Удаляет пользователя, возвращает true в случае успешного удаления


public:
	TestingSystem();
	~TestingSystem();
};

