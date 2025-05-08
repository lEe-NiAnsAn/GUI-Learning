#pragma once
#include <string>
#include <Windows.h>
class Gdi {
public:
	Gdi() = default;
	~Gdi() = default;
	Gdi(const Gdi& other) = delete;
	Gdi(Gdi&& other) noexcept = delete;
	Gdi operator=(const Gdi& other) = delete;
	Gdi operator=(Gdi&& other) noexcept = delete;

public:
	void drawTextWithFont(HWND hwnd);

private:
	std::wstring m_text = L"Hello Win32 Window!";
};