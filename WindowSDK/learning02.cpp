#include <windows.h>
#include <string>

// 声明一个错误码字符串显示函数
void FormatErrorMsg(DWORD errorCode) {
	wchar_t* buf;   // 定义一个指向错误字符串的指针储存错误信息
	// 调用FormatMessage函数获取错误信息至buf字符串
	// 参数：控制信息、源句柄、错误码、语言ID、输出缓冲区、缓冲区大小、输入参数
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&buf,
        0, NULL);
	wchar_t titleName[] = L"Error";
    MessageBoxW(nullptr, buf, titleName, MB_ICONERROR);
    LocalFree(buf);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
    // 定义一个窗口结构体
    WNDCLASSEX wc = { 0 };
    // 初始化窗口类结构体，未赋值成员默认值为0
    wc.cbSize = sizeof(WNDCLASSEX); // 设置结构体大小
    std::wstring className = L"MyWindowClass";
    wc.lpszClassName = className.c_str(); // 设置窗口类名称
    wc.lpfnWndProc = DefWindowProc; // 设置窗口过程函数
    wc.hInstance = hInstance; // 设置实例句柄

    // 注册窗口类，并获取返回值
    ATOM ret = RegisterClassEx(&wc);
    ret = RegisterClassEx(&wc); // 重复注册（错误）
    if (!ret) {
        DWORD errorCode = GetLastError(); // 获取错误代码
		FormatErrorMsg(errorCode);  // 使用函数显示错误字符串
        return errorCode; // 注册失败(ret==0)，返回错误
    }
}