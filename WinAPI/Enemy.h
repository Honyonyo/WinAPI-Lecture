#pragma once
#include "GameNode.h"

//�θ�Ŭ������ : �� Ŭ������ ������� ����, �Ϲ� ���͵��� ���� �� �ִ�.
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
	float _rndTimeCount;		// �����Ӽӵ��� �� �ٸ��� �ؼ� �پ��� �������� �����ֱ� ����
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


	//�ڽĵ鿡�� �ʱⰪ ����� ì���� �� �����ϰ� �Ѱ��ְڴ�
	Enemy(void);
	~Enemy(void) {

	}
};

