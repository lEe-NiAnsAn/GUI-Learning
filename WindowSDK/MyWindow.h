#pragma once
#include <string>
#include <Windows.h>
#include <optional>
#include "GDI.h"

class MyWindow {
public:
	explicit MyWindow(std::wstring className);	// 有参构造，不允许隐式转换
	~MyWindow();	// 无参析构函数
	MyWindow(const MyWindow& other) = delete;	// 禁止浅拷贝构造
	MyWindow(MyWindow&& other) noexcept = delete;	// 禁止深拷贝构造
	MyWindow& operator=(const MyWindow& other) = delete;	// 禁止浅拷贝赋值
	MyWindow& operator=(MyWindow&& other) noexcept = delete;	// 禁止深拷贝赋值

public:
	// 定义、重载Begin函数
	std::optional<bool> Begin(const std::wstring& name);
	std::optional<bool> Begin(const std::wstring& name, int width, int height);
	std::optional<bool> Begin(const std::wstring& name, int x, int y, int width, int height);
	// 定义BeginAt函数
	std::optional<bool> BeginAt(const std::wstring& name, int x, int y);
	// 定义窗口过程函数
	static LRESULT CALLBACK MessageProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	// 定义处理过程函数
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	std::wstring m_className;	// 窗口类名
	HINSTANCE m_hinstance = GetModuleHandle(nullptr);	// 实例句柄
	HWND m_hwnd = nullptr;	//窗口句柄
	int m_x = CW_USEDEFAULT;	// 窗口X坐标
	int m_y = CW_USEDEFAULT;	//窗口Y坐标
	int m_width = CW_USEDEFAULT;	// 窗口宽度
	int m_height = CW_USEDEFAULT;	//窗口高度
	Gdi m_gdi;

public:
	static int s_windowCount;
};