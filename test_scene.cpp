#include"test_scene.h"

TestScene::TestScene()
	: m_bg(NULL),
	  m_playButton(NULL) {

	m_bg = new Sprite(BACKGROUND_PNG, s_gfx); // Initialize objects

	// Create button
	m_playButton = CreateWindowEx(
		NULL,
		L"Button",	// Predefined Button class
		L"",		// Text on button

		// Button styles
		WS_CHILD | WS_VISIBLE | BS_BITMAP,
		
		// Position & size
		100, 100, BUTTON_UP.first, BUTTON_UP.second,

		s_hwnd, // Parent window
		NULL,
		(HINSTANCE)GetWindowLongPtr(s_hwnd, GWLP_HINSTANCE), // Important!
		NULL
	);

	// Set button image (.bmp file)
	HBITMAP hBitmap = (HBITMAP)LoadImage(
		NULL,
		BLUE_BUTTON_UP_BMP,
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_DEFAULTSIZE
	);
	SendMessage(m_playButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
}

TestScene::~TestScene() {
	SafeReleasePointer(&m_bg); // Release memory of all objects
}

void TestScene::Render() {
	m_bg->Draw({ 0, 0 }); // Draw sample background
}