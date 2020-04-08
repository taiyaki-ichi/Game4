#include"Event.hpp"
#include<Windows.h>


namespace GameLib
{
	bool PollEvent()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT ||
				msg.message == WM_DESTROY)
			{
				PostQuitMessage(0);
				return false;
			}
			else 
				DispatchMessage(&msg);
		}

		return true;
	}
}