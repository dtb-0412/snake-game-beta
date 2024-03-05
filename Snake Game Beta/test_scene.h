#pragma once

#include"base_scene.h"
#include"sprite.h"
#include"constants.h"

using namespace WinConstants;
using namespace TestSceneConstants;

class TestScene : public BaseScene {
public:
	TestScene();
	~TestScene();

	void Render() override;

private:
	Sprite* m_bg;
	HWND	m_playButton;
	// Could be any thing in the window scene: images, sounds, ui components, ...
};