#include "stdafx.h"
#include "TilemapScene.h"

HRESULT TilemapScene::init(void)
{
	GameNode::init(true);
	_map = new MapMaker;
	start();
	SOUNDMANAGER->setUp("Resources/Sound/blueming.mp3", SOUND_BGM,true, true);
	SOUNDMANAGER->play(SOUND_BGM, 1.0f);

	return S_OK;
}

void TilemapScene::release(void)
{
	GameNode::release();
	_map->release();
	SAFE_DELETE(_map);
}

void TilemapScene::update(void)
{
	GameNode::update();
	_map->update();
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_map->boardReset();
		_map->release();
		start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SCENEMANAGER->changeScene("·ÎÄÏ¾À");
	}
	SOUNDMANAGER->update();
}

void TilemapScene::render(void)
{
	GameNode::render();
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	_map->render();

	this->getBackBuffer()->render(getHDC());
}

void TilemapScene::start(void)
{
	do
	{
		system("cls");
		cout << "Ä­¼ö¸¦ ÀÔ·ÂÇÏ½Ê½Ã¿À. (2~100Ä­±îÁö)" << endl;
		std::cin >> _number;
		system("cls");
	} while (_number > 100);
	cout << "¸ðÀÇ Å¸ÀÏ¸Ê Ä­¼ö : " << _number << endl;
	_map->init(_number);
}
