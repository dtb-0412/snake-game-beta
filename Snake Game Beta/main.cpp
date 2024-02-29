// https://opengameart.org/forumtopic/snake-game-art-request
// https://ezgif.com/
// https://github.com/davidejones/winsnake/blob/master/main.cpp

#ifndef UNICODE
#define UNICODE
#endif // UNICODE

#include<windows.h>
#include"resource.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
			break;
		}

		case WM_CLOSE:
		{
			BOOL some_condition = TRUE;
			if (some_condition) {
				int choice = MessageBox(
					hwnd,
					L"Some condition text",
					L"Are you sure to quit?",
					MB_OKCANCEL
				);
				if (choice == IDCANCEL) break;
			}

			DestroyWindow(hwnd);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}
	}

	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	// Register the window class
	const wchar_t CLASS_NAME[] = L"Snake Game Window";
	HICON ICON = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = CLASS_NAME;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.hIcon = ICON;
	wc.hIconSm = ICON;

	if (!RegisterClassEx(&wc)) {
		MessageBox(
			NULL,
			L"Failed to create window!",
			L"Error",
			MB_ICONWARNING | MB_OK);
		return 1;
	}

	// Create the window
	HWND hwnd = CreateWindowEx(
		0,						// Optional window styles
		CLASS_NAME,				// Class name
		L"Snake Game",			// Window text
		WS_OVERLAPPEDWINDOW,	// Window style
		
		// Size & position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		
		NULL,		// Parent window
		NULL,		// Menu
		hInstance,	// Instance handle
		NULL		// Additional application data
	);

	if (!hwnd) {
		MessageBox(
			NULL,
			L"Failed to create window!",
			L"Error",
			MB_ICONWARNING | MB_OK);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Run the message loop
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}