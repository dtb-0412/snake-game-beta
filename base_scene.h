#pragma once

#include"graphics.h"

class BaseScene {
public:
	static void Init(Graphics* gfx, HWND hwnd);

	virtual void Render() = 0;

protected:
	static Graphics*	s_gfx;
	static HWND			s_hwnd;
};