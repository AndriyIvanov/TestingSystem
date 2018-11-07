#pragma once

class MainWindow
{
protected:
	size_t Height_;
	size_t Width_;
public:
	MainWindow(size_t Height=30, size_t Width=51) :  Height_(Height), Width_(Width)	{};
	void PrintWindow();
};

