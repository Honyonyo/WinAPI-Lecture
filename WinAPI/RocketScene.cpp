#include "stdafx.h"
#include "RocketScene.h"

HRESULT RocketScene::init(void)
{
	GameNode::init(true);

	IMAGEMANAGER->addImage("ÀüÀå", "Resources/Images/Background/BattleField.bmp", WINSIZE_X, WINSIZE_Y);

	_enemy[1] = new EnemyManager;
	_enemy[1]->init(1);
	_enemy[2] = new EnemyManager;
	_enemy[2]->init(2);
	_enemy[0] = new EnemyManager;
	_enemy[0]->init(3);
	
	_rocket = new Rocket;
	_rocket->init(_enemy);
	_rocketHitBox = _rocket->getRocketBox();

	_at = new AnimationScene;
	_at->init();

	_enemy[1]->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_enemy[1]);

	//wsprintf();



	return S_OK;
}

void RocketScene::release(void)
{
	GameNode::release();
	_rocket->release();
	_enemy[1]->release();
	_enemy[2]->release();
	_enemy[0]->release();

	_at->release();
}

void RocketScene::update(void)
{
	GameNode::update();
	_rocket->update();
	//vector<RECT> tmp = _rocket->getBulletHitBox();
	_enemy[1]->update();
	_enemy[2]->update();
	_enemy[0]->update();
	collision();
	_at->update();
	_y -= 2.0f;


	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SCENEMANAGER->changeScene("¸ÊÅø¾À");
	}

}

void RocketScene::render(void)
{
	GameNode::render();
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	RECT rc = { 0,0,WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->findImage("ÀüÀå")->loopRender(getMemDC(),&rc,_x,_y);
	_rocket->render();
	_enemy[1]->render();
	_enemy[2]->render();
	_enemy[0]->render();
	_at->render();
	this->getBackBuffer()->render(getHDC());
}