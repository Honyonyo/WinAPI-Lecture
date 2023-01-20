#include "stdafx.h"
#include "TilemapScene.h"

HRESULT TilemapScene::init(void)
{
	GameNode::init(true);
	_map = new MapMaker;
	start();

	SOUNDMANAGER->setUp("블루밍", "Resources/Sound/blueming.mp3", SOUNDKIND::SOUND_BGM, true, true);
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
		SCENEMANAGER->changeScene("로켓씬");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("블루밍", 1.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SOUNDMANAGER->pauseAndResume("블루밍");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) 
	{
		SOUNDMANAGER->stop("블루밍");
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
		//system("cls");
		cout << "칸수를 입력하십시오. (2~100칸까지)" << endl;
		std::cin >> _number;
		//system("cls");
	} while (_number > 100);
	cout << "모의 타일맵 칸수 : " << _number << endl;
	_map->init(_number);
}
