#include"app_window.h"

AppWindow::AppWindow()
	: BaseWindow(),
	  m_gfx(NULL),
	  m_scene(NULL),
	  m_testScene(NULL),
	  m_gameScene(NULL),
	  m_menuScene(NULL) {}

AppWindow::~AppWindow() {
	SafeReleasePointer(&m_gfx);
	SafeReleasePointer(&m_testScene);
	SafeReleasePointer(&m_menuScene);
	SafeReleasePointer(&m_gameScene);

	m_scene = NULL;
}

HRESULT AppWindow::Init() {
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	Create(WIN_X, WIN_Y, WIN_W, WIN_H, dwStyle);

	HICON hIcon = (HICON)LoadImage(
		NULL,
		ICON_01_ICO,
		IMAGE_ICON,
		0, 0,
		LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED
	);
	SendMessage(m_hwnd, WM_SETICON, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);

	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		return __HRESULT_FROM_WIN32(GetLastError());
	}

	m_gfx = new Graphics();
	if (!m_gfx->Init(m_hwnd)) {
		return __HRESULT_FROM_WIN32(GetLastError());
	}

	BaseScene::Init(m_gfx, m_hwnd);
	m_testScene = new TestScene();
	m_menuScene = new MenuScene();
	m_gameScene = new GameScene();

	m_scene = m_testScene;
	return S_OK;
}

LRESULT AppWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE:
		{
			/*int choice = MessageBox(NULL, L"Confirm quit?", L"Warning", MB_OKCANCEL);
			if (choice == MB_OK) {
				DestroyWindow(m_hwnd);
			}*/

			DestroyWindow(m_hwnd);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(NULL);
			break;
		}

		case WM_PAINT:
		{
			HandlePaint();
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}

		default:
		{
			if (m_scene == m_testScene) {
				return HandleTestSceneMessage(uMsg, wParam, lParam);
			} else if (m_scene == m_menuScene) {
				return HandleMenuSceneMessage(uMsg, wParam, lParam);
			} else if (m_scene == m_gameScene) {
				return HandleGameSceneMessage(uMsg, wParam, lParam);
			} else {
				// Do nothing
			}
		}
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

LRESULT AppWindow::HandleTestSceneMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

LRESULT AppWindow::HandleMenuSceneMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

LRESULT AppWindow::HandleGameSceneMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void AppWindow::HandlePaint() {
	m_gfx->BeginDraw();
	m_scene->Render();
	m_gfx->EndDraw();
}