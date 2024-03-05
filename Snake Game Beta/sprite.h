#pragma once

#include<wincodec.h> // WIC codec header for decoding image from file

#include"graphics.h"
#include"constants.h"

class Sprite {
public:
	Sprite(Path filename, Graphics* gfx);
	~Sprite();

	void Draw(Pair2F pos);
	void Draw(Pair2F pos, Pair2F size);

private:
	Graphics*		m_gfx;
	ID2D1Bitmap*	m_bmp; // Bitmap loaded file and converted to Direct2D format
};