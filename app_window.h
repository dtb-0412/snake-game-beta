#pragma once

#include"base_window.h"

#include"test_scene.h"
#include"menu_scene.h"
#include"game_scene.h"

#include"utility.h"
#include"constants.h"

using namespace WinConstants;

class AppWindow : public BaseWindow {
public:
	AppWindow();
	~AppWindow();

	HRESULT Init();
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

protected:
	LRESULT HandleTestSceneMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMenuSceneMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleGameSceneMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void HandlePaint() override;

	LPCTSTR ClassName() const override {
		return L"App Window";
	}

	LPCTSTR WindowName() const override {
		return WIN_TITLE;
	}

	LPCTSTR MenuName() const override {
		return NULL;
	}

	Graphics*	m_gfx;
	
	BaseScene*	m_scene;

	TestScene*	m_testScene;
	MenuScene*	m_menuScene;
	GameScene*	m_gameScene;
};