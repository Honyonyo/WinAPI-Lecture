#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"
#include "AnimationScene.h"

class RocketScene : public GameNode
{
	private:
		Rocket* _rocket;
		EnemyManager* _enemy[3];

		AnimationScene* _at;
		float _x, _y;

		char* _text[64];

		RECT* _rocketHitBox;
	public:
		HRESULT init(void);
		void release(void);
		void update(void);
		void render(void);

		virtual void collision();

		RocketScene() {}
		~RocketScene() {}
};

