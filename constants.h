#pragma once

#include<memory>

#include<wingdi.h>

using Path = const wchar_t*;
using Pair2I = std::pair<int, int>;
using Pair2F = std::pair<float, float>;

namespace WinConstants {
	const wchar_t* const WIN_TITLE = L"Snake Game 1.0";

	// Fixed size
	const int WIN_W = 1000;
	const int WIN_H = 560;

	const int WIN_X = (GetSystemMetrics(SM_CXSCREEN) - WIN_W) / 2;	// Center screen horizontally
	const int WIN_Y = (GetSystemMetrics(SM_CYSCREEN) - WIN_H) / 2;	// Center screen vertically
}

namespace TestSceneConstants{
	const Path ICON_01_ICO = L".\\assets\\icon_01.ico";
	const Path BACKGROUND_PNG = L".\\assets\\background.png";
	const Path BLUE_BUTTON_UP_BMP = L".\\assets\\blue_button_up.bmp";

	const Pair2I BUTTON_UP = { 190, 49 };
	const Pair2I BUTTON_DOWN = { 190, 45 };
}

namespace MenuSceneConstants {

}

namespace GameSceneConstants {

}