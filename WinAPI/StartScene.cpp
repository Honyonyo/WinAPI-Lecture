#include "stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addImage("시작화면", "Resources/Images/Background/StartBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("텍스트 알파", "Resources/Images/Object/StartText.bmp", 1000, 100);

	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	_alpha -= 1.0f;
	if (_alpha <= 0) _alpha = 255;

	_bgAlpha += 5.0f;
	if (_bgAlpha >= 255) _bgAlpha = 0;
}

void StartScene::render(void)
{
	IMAGEMANAGER->alphaRender("시작화면", getMemDC(), 0, 0, _bgAlpha);

	if (_bgAlpha >= 160) {
		IMAGEMANAGER->alphaRender("텍스트 알파", getMemDC(), 130, WINSIZE_Y / 2 + 220, _alpha);
	}
}
