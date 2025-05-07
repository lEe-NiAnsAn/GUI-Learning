#include <windows.h>
/* Win32程序入口函数
 * 参数一为当前程序的实例句柄
 * 参数二为上一个实例的句柄，通常为NULL
 * 参数三为命令行参数，默认为NULL
 * 参数四为窗口显示方式，默认为SW_SHOW */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR pCmdLine, int nCmdShow) { 
    /* 显示一个消息框
     * 参数一为父窗口句柄，通常为NULL
     * 参数二为消息框的内容，使用wchar_t字符串
     * 参数三为消息框的标题，使用wchar_t字符串
     * 参数四为消息框的类型，使用MB_OK即显示一个OK按钮 */
    MessageBox(nullptr, L"Hello, World!", L"Title", MB_OK);
    
}