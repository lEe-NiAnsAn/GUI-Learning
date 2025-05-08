#include <windows.h>
#include <string>

// 定义窗口过程函数：返回值为：LRESULT，使用CALLBACK表示该函数为回调函数
LRESULT CALLBACK MessageProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_CREATE:
        OutputDebugString(L"window is created\n");
        break;
    case WM_PAINT:
        OutputDebugString(L"window needs repaint\n");
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);    // 显示文字后使用默认窗口过程函数进行处理
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    std::wstring className = L"MyWindowClass";
    wc.lpszClassName = className.c_str();
    wc.lpfnWndProc = MessageProc;   // 使用自定的窗口过程函数
    wc.hInstance = hInstance;
    ATOM ret = RegisterClassEx(&wc);
    if (!ret) {
        DWORD errorCode = GetLastError();
        return errorCode;
    }
    // 以上述窗口类为“模板”创建窗口实例：使用同一类名关联（"MyWindowClass"）
	// 参数：扩展样式、窗口类名、窗口标题、样式、位置、大小、父窗口句柄、菜单、实例句柄、附加参数
    HWND hwnd = CreateWindowEx(NULL, className.c_str(), L"Title", WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        480, 600, 
        nullptr, nullptr, 
        hInstance, nullptr);
	if(!hwnd) {
		DWORD errorCode = GetLastError();
		return errorCode;
	}
	ShowWindow(hwnd, SW_SHOW); // 显示窗口（参数：窗口句柄、显示方式）

    // 定义消息结构体
    MSG msg;
    while (GetMessage(&msg, nullptr, NULL, NULL) != 0) {    // 参数：指针、消息源句柄、(获取消息)最少值、(获取消息)最大值
        DispatchMessage(&msg);  // 将消息调度到窗口过程：nullptr为检索所有窗口句柄(即包括了hwnd窗口)，实例窗口由“模板”创建故可使用过程函数
    }
	return 0;
}