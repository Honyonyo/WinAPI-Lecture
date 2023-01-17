#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "RocketScene.h"
#include "TilemapScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	SCENEMANAGER->addScene("���Ͼ�", new RocketScene);
	SCENEMANAGER->addScene("������", new TilemapScene);

	SCENEMANAGER->changeScene("������");
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
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}