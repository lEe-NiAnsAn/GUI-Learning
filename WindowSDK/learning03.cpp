#include <windows.h>
#include <string>

// ���崰�ڹ��̺���������ֵΪ��LRESULT��ʹ��CALLBACK��ʾ�ú���Ϊ�ص�����
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
    return DefWindowProc(hwnd, msg, wparam, lparam);    // ��ʾ���ֺ�ʹ��Ĭ�ϴ��ڹ��̺������д���
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    std::wstring className = L"MyWindowClass";
    wc.lpszClassName = className.c_str();
    wc.lpfnWndProc = MessageProc;   // ʹ���Զ��Ĵ��ڹ��̺���
    wc.hInstance = hInstance;
    ATOM ret = RegisterClassEx(&wc);
    if (!ret) {
        DWORD errorCode = GetLastError();
        return errorCode;
    }
    // ������������Ϊ��ģ�塱��������ʵ����ʹ��ͬһ����������"MyWindowClass"��
	// ��������չ��ʽ���������������ڱ��⡢��ʽ��λ�á���С�������ھ�����˵���ʵ����������Ӳ���
    HWND hwnd = CreateWindowEx(NULL, className.c_str(), L"Title", WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        480, 600, 
        nullptr, nullptr, 
        hInstance, nullptr);
	if(!hwnd) {
		DWORD errorCode = GetLastError();
		return errorCode;
	}
	ShowWindow(hwnd, SW_SHOW); // ��ʾ���ڣ����������ھ������ʾ��ʽ��

    // ������Ϣ�ṹ��
    MSG msg;
    while (GetMessage(&msg, nullptr, NULL, NULL) != 0) {    // ������ָ�롢��ϢԴ�����(��ȡ��Ϣ)����ֵ��(��ȡ��Ϣ)���ֵ
        DispatchMessage(&msg);  // ����Ϣ���ȵ����ڹ��̣�nullptrΪ�������д��ھ��(��������hwnd����)��ʵ�������ɡ�ģ�塱�����ʿ�ʹ�ù��̺���
    }
	return 0;
}