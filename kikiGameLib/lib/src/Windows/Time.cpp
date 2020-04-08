#include"Time.hpp"
#include<Windows.h>

#pragma comment(lib, "winmm.lib")

namespace GameLib
{
	unsigned long GetTime()
	{
		return static_cast<unsigned long>(timeGetTime());
	}

	void Wait(unsigned long preTime, unsigned long waitTime)
	{
		while (timeGetTime()<preTime+waitTime)
		{
			timeBeginPeriod(1);
			Sleep(1); 
			timeEndPeriod(1);  
		}
	}
}