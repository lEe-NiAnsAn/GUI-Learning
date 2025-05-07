#include <windows.h>
#include <string>

// ����һ���������ַ�����ʾ����
void FormatErrorMsg(DWORD errorCode) {
	wchar_t* buf;   // ����һ��ָ������ַ�����ָ�봢�������Ϣ
	// ����FormatMessage������ȡ������Ϣ��buf�ַ���
	// ������������Ϣ��Դ����������롢����ID���������������������С���������
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
    // ����һ�����ڽṹ��
    WNDCLASSEX wc = { 0 };
    // ��ʼ��������ṹ�壬δ��ֵ��ԱĬ��ֵΪ0
    wc.cbSize = sizeof(WNDCLASSEX); // ���ýṹ���С
    std::wstring className = L"MyWindowClass";
    wc.lpszClassName = className.c_str(); // ���ô���������
    wc.lpfnWndProc = DefWindowProc; // ���ô��ڹ��̺���
    wc.hInstance = hInstance; // ����ʵ�����

    // ע�ᴰ���࣬����ȡ����ֵ
    ATOM ret = RegisterClassEx(&wc);
    ret = RegisterClassEx(&wc); // �ظ�ע�ᣨ����
    if (!ret) {
        DWORD errorCode = GetLastError(); // ��ȡ�������
		FormatErrorMsg(errorCode);  // ʹ�ú�����ʾ�����ַ���
        return errorCode; // ע��ʧ��(ret==0)�����ش���
    }
}