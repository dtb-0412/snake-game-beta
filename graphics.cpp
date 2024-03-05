#include"graphics.h"

Graphics::Graphics()
	: m_factory(NULL),
	  m_renderTarget(NULL) {}

Graphics::~Graphics() {
	SafeReleaseCom(&m_factory);
	SafeReleaseCom(&m_renderTarget);
}

ID2D1Factory* Graphics::GetFactory() {
	return m_factory;
}

ID2D1HwndRenderTarget* Graphics::GetRenderTarget() {
	return m_renderTarget;
}

BOOL Graphics::Init(HWND hwnd) {
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
	if (hr != S_OK) return FALSE;

	RECT rect;
	GetClientRect(hwnd, &rect);

	hr = m_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rect.right, rect.bottom)),
		&m_renderTarget
	);
	if (hr != S_OK) return FALSE;
	return TRUE;
}

void Graphics::BeginDraw() {
	m_renderTarget->BeginDraw();
}

void Graphics::EndDraw() {
	m_renderTarget->EndDraw();
}