#pragma once
#include "GameNode.h"

#define BULLET_RADIUS		10
#define BULLET_DELETETIME	10000
#define BULLET_MOVEPOINT	5

#define BULLETCOLOR			RGB(0,255,255)
#define OBJECTCOLOR			RGB(255,0,255)

#define CANNONRADIAN_MAX	6.0f
#define CANNONRADIAN_MIN	3.5f
#define CANNONRADIAN	0.03f
#define CANNONRADIAN_AD	0.01f
#define CANNONMOVEPOINT		1


struct BULLET {
	POINT centerCannon;
	POINT center;
	int radius;
	int counter;
	float gentime;
	float radian;
	short bouncecount;
	bool autoBullet;
	bool autoLeft;
	COLORREF color;

	void shoot(POINT center, float radian, bool isAuto, bool direction) {
		this->center = this->centerCannon = center;
		radius = BULLET_RADIUS;
		this->radian = radian;
		this->autoBullet = isAuto;
		this->autoLeft = direction;
		this->counter = 0;

		color = BULLETCOLOR;
	}
	void moving() {
		if (autoBullet) {
			this->counter++;
			this->radian += autoLeft ? -acos(CANNONRADIAN_AD / this->counter) / 90 : +acos(CANNONRADIAN_AD / this->counter) / 90;
			center.x = centerCannon.x + this->counter * (cos(radian));
			center.y = centerCannon.y + this->counter * (sin(radian));
		}
		else
		{
			center.x += (BULLET_MOVEPOINT) * (cos(radian));
			center.y += (BULLET_MOVEPOINT) * (sin(radian));
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
*		A : ������ / ź���� ���� ��ȯ�ϱ�
*
*	������
		SPACE_BAR : �� �߻�
		S : �� �ڵ� ȸ�� �ѱ�/����
		�� �� ����Ű : �ڵ�ȸ�� ���� ��� �� ���� ����

	ź���� ��������
		SPACE_BAR : ��/�� ȸ������ ��ȯ
		����Ű : ź���� �߽��� �Ǵ� ������ �̵��� �� �ֽ��ϴ�.

* �߻�� �Ѿ��� ���� �ð��� ������ ������ϴ�.
* ź���� �������� ���¿��� �̵��� ��, ���������� ��ȯ�ϸ�
* �̵��� ���� ������ �ڸ��ϰ� �˴ϴ�.
*
*
* vector ���� �ٸ� �ڷ������� �Ẹ��; list�� ����غ��ҽ��ϴ�.
* �浹�� �ȼ��浹�� �̿��߽��ϴ�.
*/


class MainGame : public GameNode
{
private:

	POINT _centerCannon;
	POINT _endCannon;
	int _counter;
	float _movepoint;
	float _radianCannon;
	short _cannonsize;
	bool _automaticCannonSwitch;
	bool _automaticCannonDirectionLeft;
	bool _allDirectionCannon;

	vector<BULLET> _vBullet;
	vector<BULLET>::iterator _iter;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void setCannonDirection();
	void moveCannonLeft();
	void moveCannonRight();
	void shootCannon();

	void allDirectionCannonMove();
	void allDirectionCannonShooing();

	void drawCannon(HDC hdc);


	MainGame() {}
	~MainGame() {}
};
