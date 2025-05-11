// 采用多文件方式编写
#include <windows.h>
#include "MyWindow.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	MyWindow wnd1(L"classname1_");
	wnd1.Begin(L"window1");
	wnd1.Begin(L"window2");


	MSG msg;
	while (GetMessage(&msg, nullptr, NULL, NULL) != 0) {
		DispatchMessage(&msg);
	}

	return 0;	
}