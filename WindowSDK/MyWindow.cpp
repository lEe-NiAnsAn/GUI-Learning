#include "MyWindow.h"
#include "Tool.h"

int MyWindow::s_windowCount = 0;

MyWindow::MyWindow(std::wstring className) : 
	m_className(std::move(className)) {	// ����Ա����������
	WNDCLASSEX wc = { 0 };	// ��ʼ��������
	wc.cbSize = sizeof(WNDCLASSEX);	// �������С
	wc.lpszClassName = m_className.c_str();	// ��������
	wc.lpfnWndProc = MessageProc;	// ���ڹ��̺���
	wc.hbrBackground = CreateSolidBrush(RGB(56, 56, 56));	// ���ڱ�����ɫ
	if (ATOM ret = RegisterClassEx(&wc); !ret) {
		Tool::FormatErrorMsg(GetLastError());
	}
}

MyWindow::~MyWindow() {
	DestroyWindow(m_hwnd);	// ���ٵ�ǰ����
	UnregisterClass(m_className.c_str(), m_hinstance);	// ȡ��ע��
}

std::optional<bool> MyWindow::Begin(const std::wstring& name) {
	auto wnd = CreateWindowExW(NULL, m_className.c_str(), name.c_str(), WS_OVERLAPPEDWINDOW,
		m_x, m_y,
		m_width, m_height,
		nullptr, nullptr,
		m_hinstance, this);	// ����thisָ���Ա㾲̬�Ļص������ɷ���
	if (!wnd) {
		Tool::FormatErrorMsg(GetLastError());
		return false;
	}
	if (m_hwnd == nullptr) {
		m_hwnd = wnd;
	}
	ShowWindow(wnd, SW_SHOW);
	s_windowCount++;
	return {};
}

std::optional<bool> MyWindow::Begin(const std::wstring& name, int width, int height) {
	m_width = width;
	m_height = height;
	return Begin(name);
}

std::optional<bool> MyWindow::Begin(const std::wstring& name, int x, int y, int width, int height) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	return Begin(name);
}

std::optional<bool> MyWindow::BeginAt(const std::wstring& name, int x, int y) {
	m_x = x;
	m_y = y;
	return Begin(name);
}

LRESULT CALLBACK MyWindow::MessageProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	static MyWindow* pWnd = nullptr;	// �ô������е���Ϣָ�빲��
	if (msg == WM_CREATE && pWnd == nullptr) {	// �״δ���
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lparam); 
		pWnd = static_cast<MyWindow*>(pCreate->lpCreateParams);	// ��������Ϣָ�븳ֵ����¼ָ��
	}
	if (pWnd != nullptr) {
		return pWnd->HandleMessage(hwnd, msg, wparam, lparam);
	}
	return DefWindowProcW(hwnd, msg, wparam, lparam);
}

LRESULT CALLBACK MyWindow::HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_CREATE:
		OutputDebugString(L"window is created\n");
		break;
	case WM_PAINT:
		m_gdi.OnPaint(hwnd);	// ����
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);	// ���رյ�ǰ����
		return 0;
	case WM_DESTROY:
		if (--s_windowCount == 0) {	// ���д��ڹرպ�ִ���˳�
			PostQuitMessage(0);
		}
		break;
	default:
		break;
	}
	return DefWindowProcW(hwnd, msg, wparam, lparam);
}