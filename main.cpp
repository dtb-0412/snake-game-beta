// https://opengameart.org/forumtopic/snake-game-art-request
// https://ezgif.com/
// https://github.com/davidejones/winsnake/blob/master/main.cpp

#include"app_window.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	AppWindow myApp;

	myApp.Init();
	myApp.Show(nCmdShow);

	// Run the message loop
	MSG msg{};
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}