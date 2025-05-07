#include "MyWindow.h"
#include "Tool.h"

int MyWindow::s_windowCount = 0;

MyWindow::MyWindow(std::wstring className) : 
	m_className(std::move(className)) {	// （成员变量）类名
	WNDCLASSEX wc = { 0 };	// 初始化窗口类
	wc.cbSize = sizeof(WNDCLASSEX);	// 窗口类大小
	wc.lpszClassName = m_className.c_str();	// 窗口类名
	wc.lpfnWndProc = MessageProc;	// 窗口过程函数
	wc.hbrBackground = CreateSolidBrush(RGB(56, 56, 56));	// 窗口背景颜色
	if (ATOM ret = RegisterClassEx(&wc); !ret) {
		Tool::FormatErrorMsg(GetLastError());
	}
}

MyWindow::~MyWindow() {
	DestroyWindow(m_hwnd);	// 销毁当前窗口
	UnregisterClass(m_className.c_str(), m_hinstance);	// 取消注册
}

std::optional<bool> MyWindow::Begin(const std::wstring& name) {
	auto wnd = CreateWindowExW(NULL, m_className.c_str(), name.c_str(), WS_OVERLAPPEDWINDOW,
		m_x, m_y,
		m_width, m_height,
		nullptr, nullptr,
		m_hinstance, this);	// 传入this指针以便静态的回调函数可访问
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
	static MyWindow* pWnd = nullptr;	// 该窗口所有的消息指针共用
	if (msg == WM_CREATE && pWnd == nullptr) {	// 首次创建
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lparam); 
		pWnd = static_cast<MyWindow*>(pCreate->lpCreateParams);	// 将窗口消息指针赋值至记录指针
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
		m_gdi.OnPaint(hwnd);	// 绘制
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);	// 仅关闭当前窗口
		return 0;
	case WM_DESTROY:
		if (--s_windowCount == 0) {	// 所有窗口关闭后执行退出
			PostQuitMessage(0);
		}
		break;
	default:
		break;
	}
	return DefWindowProcW(hwnd, msg, wparam, lparam);
}