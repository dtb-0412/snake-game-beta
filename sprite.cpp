#include"sprite.h"

Sprite::Sprite(Path filename, Graphics* gfx)
	: m_gfx(gfx),
	  m_bmp(NULL) {

	IWICImagingFactory* wicFactory = NULL;

	HRESULT hr;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,	// CLS ID of the WIC factory
		NULL,						// Not part of an aggregate
		CLSCTX_INPROC_SERVER,		// DLL runs in the same process
		IID_IWICImagingFactory,		// Ref to interface th at communicates with the WIC factory
		(LPVOID*)&wicFactory
	);

	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,						// The file name
		NULL,							// No preferred vendor
		GENERIC_READ,					// We're reading the file, not writing
		WICDecodeMetadataCacheOnLoad,	// Cache on load
		&wicDecoder
	);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,						// Frame
		GUID_WICPixelFormat32bppPBGRA,	// Pixel format
		WICBitmapDitherTypeNone,		// Irrelevant
		NULL,							// No palette needed
		0.0,							// Alpha transparency
		WICBitmapPaletteTypeCustom		// Irrelevant
	);

	hr = m_gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,	// Converter
		NULL,			// D2D1_BITMAP_PROPERTIES
		&m_bmp			// Destination D2D1 bitmap
	);

	SafeReleaseCom(&wicFactory);
	SafeReleaseCom(&wicDecoder);
	SafeReleaseCom(&wicFrame);
	SafeReleaseCom(&wicConverter);
}

Sprite::~Sprite() {
	SafeReleaseCom(&m_bmp);
}

void Sprite::Draw(Pair2F pos) {
	Draw(pos, Pair2F{ m_bmp->GetSize().width, m_bmp->GetSize().height });
}

void Sprite::Draw(Pair2F pos, Pair2F size) {
	m_gfx->GetRenderTarget()->DrawBitmap(
		m_bmp, // Bitmap

		// Destination rectangle
		D2D1::RectF(pos.first, pos.second, size.first, size.second),

		1.0f, // Opacity

		// Interpolation
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,

		// Source rectangle
		D2D1::RectF(0.0f, 0.0f, m_bmp->GetSize().width, m_bmp->GetSize().height)
	);
}