#include "GDI.h"
#include <format>

void Gdi::OnPaint(HWND hwnd) {
	OutputDebugString(L"[Message] WM_Paint\n");
	PAINTSTRUCT ps;	// �������Խṹ��
	InvalidateRect(hwnd, NULL, true);	// ʹ�������ھ���Ϊ��Ч����ˢ��
	HDC hdc = BeginPaint(hwnd, &ps);	// ��ʼ���Ʋ�������ʾ�豸�����ľ��
	TEXTMETRICW tm;	// �������Խṹ��
	GetTextMetrics(hdc, &tm);	// Ӧ����������
	auto fontInfo = std::format(L"this font height is {}, width is {}\n", tm.tmHeight, tm.tmAveCharWidth);	// Debug�����������
	OutputDebugString(fontInfo.c_str());
	SetTextColor(hdc, RGB(88, 124, 141));	// �ı���ɫ
	SetBkMode(hdc, TRANSPARENT);  // ���ñ���͸��
	// �������豸�����ġ����Ƶ�X���ꡢ���Ƶ�Y���ꡢ
	TextOut(hdc, 0, 0, m_text.c_str(), m_text.length());
	EndPaint(hwnd, &ps);
}