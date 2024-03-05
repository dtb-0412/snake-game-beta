#pragma once

#include<windows.h>

class BaseWindow {
public:
	BaseWindow();
	virtual ~BaseWindow() {}

	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

	HRESULT Create(int x, int y, int nWidth, int nHeight,
		DWORD dwStyle = WS_OVERLAPPEDWINDOW, HWND hWndParent = NULL, HMENU hMenu = NULL, HINSTANCE hInstance = NULL, LPVOID lpParam = NULL
	);

	HRESULT Show(int mCmdShow);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

protected:
	HRESULT Register();

	virtual LPCTSTR ClassName() const = 0;
	virtual LPCTSTR WindowName() const = 0;

	virtual LPCTSTR MenuName() const = 0;

	virtual void HandlePaint() = 0;

	HWND		m_hwnd;
	HINSTANCE	m_hInstance;
};