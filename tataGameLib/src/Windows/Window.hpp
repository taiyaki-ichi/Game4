#pragma once
#include"include/App.hpp"
#include<Windows.h>

#define WINDOW_CLASS_NAME "Window"

namespace GameLib
{

	bool CreateAppWindow(const WindowData& windowData);
}