#pragma once

#include<d2d1.h>

#include"utility.h"

class Graphics {
public:
	Graphics();
	~Graphics();

	ID2D1Factory* GetFactory();
	ID2D1HwndRenderTarget* GetRenderTarget();

	BOOL Init(HWND hwnd);

	void BeginDraw();
	void EndDraw();

private:
	ID2D1Factory* m_factory;
	ID2D1HwndRenderTarget* m_renderTarget;
};