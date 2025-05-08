#include "Tool.h"
void Tool::FormatErrorMsg(DWORD errorCode) {
    wchar_t* buf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&buf,
        0, NULL);
    wchar_t titleName[] = L"ErrorInfoMessage";
    MessageBoxW(nullptr, buf, titleName, MB_ICONERROR);
    LocalFree(buf);
}