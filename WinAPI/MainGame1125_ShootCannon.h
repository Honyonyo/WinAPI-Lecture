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
* 조작법 :
*		A : 대포형 / 탄막형 버전 전환하기
*
*	대포형
		SPACE_BAR : 포 발사
		S : 포 자동 회전 켜기/끄기
		← → 방향키 : 자동회전 꺼진 경우 포 방향 조절

	탄막형 전방위포
		SPACE_BAR : 좌/우 회전방향 전환
		방향키 : 탄막의 중심이 되는 포신을 이동할 수 있습니다.

* 발사된 총알은 일정 시간이 지나면 사라집니다.
* 탄막형 전방위포 상태에서 이동한 후, 대포형으로 전환하면
* 이동한 곳에 대포가 자리하게 됩니다.
*
*
* vector 말고 다른 자료형도을 써보고싶어서 list를 사용해보았습니다.
* 충돌은 픽셀충돌을 이용했습니다.
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
