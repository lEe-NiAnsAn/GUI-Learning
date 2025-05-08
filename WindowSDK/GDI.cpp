#include "GDI.h"
#include <format>

void Gdi::drawTextWithFont(HWND hwnd) {
	OutputDebugString(L"[Message] WM_Paint\n");
	PAINTSTRUCT ps;	// 绘制属性结构体
	InvalidateRect(hwnd, NULL, true);	// 使整个窗口均划为无效区以刷新
	HDC hdc = BeginPaint(hwnd, &ps);	// 开始绘制并返回显示设备上下文句柄

	TEXTMETRICW tm;	// 字号属性结构体
	GetTextMetrics(hdc, &tm);	// 应用字号属性
	auto fontInfo = std::format(L"this font height is {}, width is {}\n", tm.tmHeight, tm.tmAveCharWidth);
	OutputDebugString(fontInfo.c_str());	// Debug输出字体属性
	/* 自订字体参数：	磅值、宽度、文本旋转角、基线旋转角、粗细、斜体、下划线、
	 *				删除线、字符集、输出精度、裁剪精度、
	 *				渲染质量、字体族、字体名 */
	HFONT hFont = CreateFont(48, 0, 0, 0, 0, FALSE, FALSE, 
		TRUE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, 
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
	SetTextColor(hdc, RGB(88, 124, 141));	// 文本颜色
	SetBkMode(hdc, TRANSPARENT);  // 设置背景透明
	auto holdFont = SelectObject(hdc, hFont);	// 替换字体至设备上下文
	// 参数：设备上下文、绘制点X坐标、绘制点Y坐标、字符串指针、字符串长度
	TextOut(hdc, 0, 0, m_text.c_str(), m_text.length());	// 左上角
	// 参数：设备上下文、字符串指针、字符串长度、绘制框指针、格式
	DrawText(hdc, m_text.c_str(), m_text.length(), &ps.rcPaint, DT_RIGHT);	// 右对齐

	SelectObject(hdc, hFont);	// 从设备上下文中重新选择字体
	DeleteObject(hFont);	// 卸载字体
	EndPaint(hwnd, &ps);	// 结束绘制
}