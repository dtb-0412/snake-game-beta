#include"base_scene.h"

Graphics* BaseScene::s_gfx;
HWND BaseScene::s_hwnd;

void BaseScene::Init(Graphics* gfx, HWND hwnd) {
	s_gfx	= gfx;
	s_hwnd	= hwnd;
}