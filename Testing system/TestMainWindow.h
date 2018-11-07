#pragma once

#include "MainWindow.h"

class TestMainWindow : public MainWindow
{
public:
	TestMainWindow(size_t Height = 35, size_t Width = 72);
	void PrintWindow();
};

