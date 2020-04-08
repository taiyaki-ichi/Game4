#include"Window.hpp"
#include"lib/src/DataImpl.hpp"
#include<Windows.h>

namespace GameLib
{
    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
            break;

        }

        return 0;
    }


	bool CreateAppWindow(const WindowData& windowData)
	{
        DataImpl::SetWindowHeight(windowData.WindowHeight);
        DataImpl::SetWindowWidth(windowData.WindowWidth);

		HWND hwnd;
        HINSTANCE hInstance = GetModuleHandle(NULL);
        if (!hInstance)
            return false;
        
        
        // シンプルウィンドウクラス設定
        WNDCLASSEX wcex = {
            sizeof(WNDCLASSEX),	//構造体のサイズ
            CS_HREDRAW | CS_VREDRAW,
            WndProc,
            0,								// 補助メモリ
            0,								// 補助メモリ
            hInstance,		// このプログラムのインスタンスハンドル
            LoadIcon(NULL, IDI_APPLICATION),// アイコン画像
            LoadCursor(NULL, IDC_ARROW),	// カーソル画像
            NULL,							// 背景ブラシ(背景色)
            NULL,							// メニュー名
            WINDOW_CLASS_NAME,							// クラス名									
            NULL	// 小さいアイコン
        };
        

      
        if (!RegisterClassEx(&wcex))
            return false;
       

        hwnd = CreateWindowEx(
            0,
            WINDOW_CLASS_NAME,
            TEXT(windowData.WindowName.c_str()),
            (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE ,
            //WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
            CW_USEDEFAULT,// static_cast<int>(windowData.TopleftX),
            0,//static_cast<int>(windowData.TopleftY),
            static_cast<int>(windowData.WindowWidth),
            static_cast<int>(windowData.WindowHeight),
            NULL,
            NULL,
            hInstance, 
            NULL);

        if (!hwnd)
            return false;
        
        RECT window_rect;
        RECT client_rect;

        GetWindowRect(hwnd, &window_rect);
        GetClientRect(hwnd, &client_rect);

        int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
        int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

        SetWindowPos(hwnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT,
            frame_size_x + static_cast<int>(windowData.WindowWidth),
            frame_size_y + static_cast<int>(windowData.WindowHeight),
            SWP_NOMOVE);

        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
       
		

        return true;
	}

 
}