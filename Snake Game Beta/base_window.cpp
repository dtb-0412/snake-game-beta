#include"base_window.h"

BaseWindow::BaseWindow()
	: m_hwnd(NULL),
	  m_hInstance(NULL) {}

HRESULT BaseWindow::Create(int x, int y, int nWidth, int nHeight, DWORD dwStyle,
	HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
	m_hInstance = hInstance;

	HRESULT hr = Register();
	if (SUCCEEDED(hr)) {
		RECT rect = { 0, 0, nWidth, nHeight };
		AdjustWindowRect(&rect, dwStyle, false);

		HWND hwnd = CreateWindow(
			ClassName(),
			WindowName(),
			dwStyle,
			x, y, rect.right - rect.left, rect.bottom - rect.top,
			hWndParent,
			hMenu,
			hInstance,
			this
		);

		if (m_hwnd == 0) {
			hr = __HRESULT_FROM_WIN32(GetLastError());
		}
	}
	return hr;
}

HRESULT BaseWindow::Show(int nCmdShow) {
	ShowWindow(m_hwnd, nCmdShow);
	UpdateWindow(m_hwnd);
	return S_OK;
}

LRESULT CALLBACK BaseWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BaseWindow* pWin = NULL;
	if (uMsg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
		pWin = (BaseWindow*)lpcs->lpCreateParams;
		pWin->m_hwnd = hwnd;

		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pWin);
	} else {
		pWin = (BaseWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}

	if (pWin) {
		return pWin->HandleMessage(uMsg, wParam, lParam);
	} else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

LRESULT BaseWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_NCDESTROY:
		{
			SetWindowLongPtr(m_hwnd, GWLP_USERDATA, 0);
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}

		case WM_PAINT:
		{
			HandlePaint();
			return 0;
		}
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

HRESULT BaseWindow::Register() {
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInstance;
	wcex.lpfnWndProc	= WindowProc;
	wcex.lpszClassName	= ClassName();
	wcex.lpszMenuName	= MenuName();
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hIcon			= NULL;
	wcex.hIconSm		= NULL;

	ATOM atom = RegisterClassEx(&wcex);
	if (atom == 0) {
		return __HRESULT_FROM_WIN32(GetLastError());
	} else {
		return S_OK;
	}
}