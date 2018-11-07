#pragma once

#include "MainWindow.h"

class TotalStatisticWindow : public MainWindow
{
public:
	TotalStatisticWindow (size_t Height = 35, size_t Width = 72);
	void PrintWindow();
};

