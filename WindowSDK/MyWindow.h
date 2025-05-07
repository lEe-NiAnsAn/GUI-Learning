#pragma once
#include <string>
#include <Windows.h>
#include <optional>
#include "GDI.h"

class MyWindow {
public:
	explicit MyWindow(std::wstring className);	// �вι��죬��������ʽת��
	~MyWindow();	// �޲���������
	MyWindow(const MyWindow& other) = delete;	// ��ֹǳ��������
	MyWindow(MyWindow&& other) noexcept = delete;	// ��ֹ�������
	MyWindow& operator=(const MyWindow& other) = delete;	// ��ֹǳ������ֵ
	MyWindow& operator=(MyWindow&& other) noexcept = delete;	// ��ֹ�����ֵ

public:
	// ���塢����Begin����
	std::optional<bool> Begin(const std::wstring& name);
	std::optional<bool> Begin(const std::wstring& name, int width, int height);
	std::optional<bool> Begin(const std::wstring& name, int x, int y, int width, int height);
	// ����BeginAt����
	std::optional<bool> BeginAt(const std::wstring& name, int x, int y);
	// ���崰�ڹ��̺���
	static LRESULT CALLBACK MessageProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	// ���崦����̺���
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	std::wstring m_className;	// ��������
	HINSTANCE m_hinstance = GetModuleHandle(nullptr);	// ʵ�����
	HWND m_hwnd = nullptr;	//���ھ��
	int m_x = CW_USEDEFAULT;	// ����X����
	int m_y = CW_USEDEFAULT;	//����Y����
	int m_width = CW_USEDEFAULT;	// ���ڿ��
	int m_height = CW_USEDEFAULT;	//���ڸ߶�
	Gdi m_gdi;

public:
	static int s_windowCount;
};