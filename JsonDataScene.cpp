#include "stdafx.h"
#include "JsonDataScene.h"

HRESULT JsonDataScene::init(void)
{
	_questSample = new QuestSample;
	_questSample->init();

	return S_OK;
}

void JsonDataScene::release(void)
{
}

void JsonDataScene::update(void)
{
}

void JsonDataScene::render(void)
{
	questPopUp();
}

void JsonDataScene::questPopUp()
{
	char str[256];
	queue<Quest*>* tmp = _questSample->getQuest();
	Quest* node = tmp->front();

	sprintf_s(str, "이름 : %s", node->GetName().c_str());
	TextOut(getMemDC(), 200, 150, str, strlen(str));
	sprintf_s(str, "몬스터 이름 : %s", node->GetMonsterName().c_str());
	TextOut(getMemDC(), 200, 200, str, strlen(str));
	sprintf_s(str, "%d", node->GetExp());
	TextOut(getMemDC(), 200, 250, str, strlen(str));
	//sprintf(str, "%s", node->GetName().c_str());
	//TextOut(getMemDC(), 200, 300, str, strlen(str));
	//sprintf(str, "%s", node->GetName().c_str());
	//TextOut(getMemDC(), 200, 350, str, strlen(str));
	//sprintf(str, "%s", node->GetName().c_str());
	//TextOut(getMemDC(), 200, 400, str, strlen(str));
	//sprintf(str, "%s", node->GetName().c_str());
	//TextOut(getMemDC(), 200, 450, str, strlen(str));
	//sprintf(str, "%s", node->GetName().c_str());
	//TextOut(getMemDC(), 200, 500, str, strlen(str));
	//sprintf(str, "%s", node->GetName().c_str());
	//TextOut(getMemDC(), 200, 550, str, strlen(str));
}

void JsonDataScene::currentQuest()
{
}
