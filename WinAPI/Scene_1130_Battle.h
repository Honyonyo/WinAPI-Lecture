#pragma once
#include "GameNode.h"
#include "Charactor.h"
/*
과제2.캐릭터 공격 / 방어
필수 : 이미지, 배경, 체력바, 플레이어(대기 공격 방어), 적(대기, 공격, 피격)
기본형식은 대전게임처럼 배치한다. (+체력바)
플레이어(1p)는 공격 및 방어를 할 수 있고, 적은 허수아비로 설정한다.
허수아비는 공격 및 피격 모션이 존재한다. (+대기)
플레이어는 상시조종 < ->적은 공격 on / off기능만(이동x)
	공격, 방어, 피격등이 발생하면 상황에 맞는 결과를 화면에 렌더링
	(맞기 빗나감 치명타 등)
	데미지 표기한다.
*/


class HomeWork : public GameNode
{
private:
	Charactor _scarecrow;
	Player* _plyr;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

