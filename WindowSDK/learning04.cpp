// 采用多文件方式编写
#include <windows.h>
#include "MyWindow.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	MyWindow wnd(L"classname_");
	wnd.Begin(L"window1");
	wnd.Begin(L"window2");

	MSG msg;
	while (GetMessage(&msg, nullptr, NULL, NULL) != 0) {
		DispatchMessage(&msg);
	}

	return 0;	
}