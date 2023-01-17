#pragma once
#include "GameNode.h"

//부모클래스양 : 이 클래스를 기반으로 보스, 일반 몬스터등을 만들 수 있다.
class Enemy :public GameNode
{
protected:
	GImage* _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	int _life;
	bool _death;

	float _x, _y;
	float _rndTimeCount;		// 프레임속도를 다 다르게 해서 다양한 움직임을 보여주기 위함
	float _worldTimeCount;		// 

	float _rndFireCount;
	float _bulletFireCount;

public : 
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	void draw(void);
	void animation(void);

	bool bulletCountFire(void);

	float* getpX() { return &_x; }
	float* getpY() { return &_y; }

	int getLife() { return _life; }
	void setLifePlus() { ++_life; }
	void setLifeMinus() { if (--_life <= 0)_death = true; }
	bool isDead() { return _death; }

	float getHalfH() { return _image->getFrameHeight() / 2; }
	RECT getRC() { return _rc; }


	//자식들에게 초기값 든든히 챙겨준 후 안전하게 넘겨주겠다
	Enemy(void);
	~Enemy(void) {

	}
};

