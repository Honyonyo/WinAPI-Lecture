#pragma once
#include "GameNode.h"

#define BULLET_RADIUS		30
#define BULLET_DELETETIME	50000
#define BULLET_MOVEPOINT	5

#define BULLETCOLOR			RGB(0,255,255)
#define OBJECTCOLOR			RGB(255,0,255)

#define CANNONRADIAN_MAX	6.0f
#define CANNONRADIAN_MIN	3.5f
#define CANNONRADIAN		0.03f
#define CANNONRADIAN_AD		0.02f

#define GRAVITY				1

struct BULLET {
	POINT center;
	int radius;
	int counter;
	float movepoint;
	float gentime;
	float radian;
	short bouncecount;
	COLORREF color;

	void shoot(POINT center, float radian) {
		this->center = center;
		radius = BULLET_RADIUS;
		this->movepoint = BULLET_MOVEPOINT;
		this->radian = radian;
		counter = 0;

		color = BULLETCOLOR;
	}
	void moving(float gravity) {
		center.x += (BULLET_MOVEPOINT) * (cos(radian));
		center.y += (movepoint) * (sin(radian)) + counter * gravity / 10;
		if (gravity) {
			movepoint -= gravity / 10;
			counter++;
		}
	}

	void drawBullet(HDC hdc) {
		HPEN newPen = CreatePen(PS_SOLID, 3, BULLETCOLOR);
		HPEN currentPen = (HPEN)SelectObject(hdc, newPen);
		EllipseMakeCenter(hdc, center, BULLET_RADIUS, BULLET_RADIUS);
		SelectObject(hdc, currentPen);
		DeleteObject(newPen);
		DeleteObject(currentPen);
	}

};

/*
* README
*
* ���۹� :
		SPACE_BAR : �� �߻�
		S : �߷� �ѱ�/����
		�� �� ����Ű : �ڵ�ȸ�� ���� ��� �� ���� ����
* �߻�� �Ѿ��� ���� �ð��� ������ ������ϴ�.
*
* vector ���� �ٸ� �ڷ����� �Ẹ��; list�� ����߽��ϴ�.
* �浹�� �ȼ��浹�� �̿��߽��ϴ�.
*/


class MainGame : public GameNode
{
private:

	//int _bulletcounter;
	int _counter;
	float _gravity;
	float _movepoint;
	POINT _centerCannon;
	POINT _endCannon;
	float _radianCannon;
	short _cannonsize;
	bool _automaticCannonSwitch;
	bool _automaticCannonDirectionLeft;

	list<BULLET> _lBullet;
	list<BULLET>::iterator _iter;

	SYSTEMTIME _st;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setCannonDirection();
	void moveCannonLeft();
	void moveCannonRight();
	void shootCannon();
	void crashBullet();

	void drawCannon(HDC hdc);


	MainGame() {}
	~MainGame() {}
};

