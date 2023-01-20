#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "RocketScene.h"
#include "TilemapScene.h"
#include "JsonDataScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	SCENEMANAGER->addScene("·ÎÄÏ¾À", new RocketScene);
	SCENEMANAGER->addScene("¸ÊÅø¾À", new TilemapScene);
	SCENEMANAGER->addScene("Á¦ÀÌ½¼", new JsonDataScene);

	SCENEMANAGER->changeScene("Á¦ÀÌ½¼");
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	GameNode::render();
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}