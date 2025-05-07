#include "GDI.h"
#include <format>

void Gdi::OnPaint(HWND hwnd) {
	OutputDebugString(L"[Message] WM_Paint\n");
	PAINTSTRUCT ps;	// 绘制属性结构体
	InvalidateRect(hwnd, NULL, true);	// 使整个窗口均划为无效区以刷新
	HDC hdc = BeginPaint(hwnd, &ps);	// 开始绘制并返回显示设备上下文句柄
	TEXTMETRICW tm;	// 字体属性结构体
	GetTextMetrics(hdc, &tm);	// 应用字体属性
	auto fontInfo = std::format(L"this font height is {}, width is {}\n", tm.tmHeight, tm.tmAveCharWidth);	// Debug输出字体属性
	OutputDebugString(fontInfo.c_str());
	SetTextColor(hdc, RGB(88, 124, 141));	// 文本颜色
	SetBkMode(hdc, TRANSPARENT);  // 设置背景透明
	// 参数：设备上下文、绘制点X坐标、绘制点Y坐标、
	TextOut(hdc, 0, 0, m_text.c_str(), m_text.length());
	EndPaint(hwnd, &ps);
}