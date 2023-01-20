#include "stdafx.h"
#include "TilemapScene.h"

HRESULT TilemapScene::init(void)
{
	GameNode::init(true);
	_map = new MapMaker;
	start();

	SOUNDMANAGER->setUp("����", "Resources/Sound/blueming.mp3", SOUNDKIND::SOUND_BGM, true, true);
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
		SCENEMANAGER->changeScene("���Ͼ�");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("����", 1.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SOUNDMANAGER->pauseAndResume("����");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) 
	{
		SOUNDMANAGER->stop("����");
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
		cout << "ĭ���� �Է��Ͻʽÿ�. (2~100ĭ����)" << endl;
		std::cin >> _number;
		//system("cls");
	} while (_number > 100);
	cout << "���� Ÿ�ϸ� ĭ�� : " << _number << endl;
	_map->init(_number);
}
