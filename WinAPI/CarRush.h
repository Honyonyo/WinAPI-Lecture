#pragma once
#include "GameNode.h"

#define COLOR_POINTYELLOW		RGB(255,171,3)
#define RAD_ZEROSPEED			PI-0.5
#define RAD_180SPEED			PI+2.2
#define RAD_NOWSPEED(a)			( (PI-0.5) + ((2.7/180) * a))

#define OPACITY_RGB				RGB(255,0,255)

#define CAR_SIZE_X				120
#define CAR_SIZE_Y				240
#define CAR_MOVEPOINT			5

/*
* README
* 설정	WINSIZE_X = 800
*		WINSIZE_Y = 1000
* 
* 스킬
	<회복>
	P키를 누르면 생명력을 1 회복합니다.
	 (죽은 후 3초 안에 누르면 부활도 가능합니다.)
	<보호막>
	S키를 누르면 보호막이 가동됩니다.
	 (충돌시에도 1.5초 보호막이 생깁니다.)
	<홍해가르기>
	스페이스바를 누르면 홍해가르기 합니다.


설계, 이미지 구현, 기본적인 기능 모두 제대로 안된 미숙하고도 미숙한 작입니다.
스킬을 플레이어 구조체에 줄지 maingame에 줄지도 오락가락해서 마음이 많이 안좋습니다..

이미지 뿌릴 영역과 hitbox를 따로 만들었습니다.

SetTimer, OnTimer, KillTimer를 이용해서 적을 불러오고싶은데,
GameNode를 망치지 않고 어떻게 할 수 있을지 답을 찾지 못했습니다.
*/
struct OBJCar {
	float speed;
	short sizeW;
	short sizeH;
	RECT rc;
	RECT hitBox;
	POINT center;
	short line;

	OBJCar(short line) {
		this->line = line;
		sizeW = 80;
		sizeH = 160;
		speed = RND->getFromFloatTo(2, 20);
		center = { (line * 2 - 1) * WINSIZE_X / 8, -sizeH };
	}

	void move(float mySpeed);
	void rcMake();
	void draw(HDC hdc);

};

struct MyCar {
	float speed;
	RECT rc;
	RECT hitBox;
	POINT center;
	short life;

	int shieldSkillTime;
	int shieldCrushTime;
	int shieldcount;


	void setRc();
	void move();
	void draw(HDC hdc);
	void crush();

	MyCar() {
		speed = 5;
		center = { WINSIZE_X / 2 ,WINSIZE_Y - CAR_SIZE_Y / 2 - 60 };
		setRc();
		life = 5;

		shieldSkillTime = 5000;
		shieldCrushTime = 1500;
		shieldcount = 0;

		IMAGEMANAGER->addImage("내차", "Resources/Images/Object/CarOrange.bmp", 120, 280, true, OPACITY_RGB);
		IMAGEMANAGER->addImage("쉴드", "Resources/Images/Object/shield.bmp", 300, 300, true, OPACITY_RGB);
		IMAGEMANAGER->addFrameImage("생명력", "Resources/Images/Object/lifeImg.bmp", 170, 140, 1, 7, true, OPACITY_RGB);
	}
};

class MainGame : public GameNode
{
private:
	HGDIOBJ original = NULL;

	MyCar _me;
	vector<OBJCar> _enemy;

	int _alphaA;
	bool _isAlphaIncrease;

	int _offsetX, _offSetY;
	float _bgSpeed;
	int _endCountdown;
	int _score;

	int _genTimer[4];

	bool _hongheaOn;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void accident(void);

	void genEnemy(short line);
	void moveAndDistroyEnemy();
	void honghea();


	void drawEnemy(HDC hdc);

	void drawUI(HDC hdc);

	void drawDashboard(HDC hdc);
	void drawDashboardFrame(HDC hdc, POINT dbCenter);
	void drawDashboardSpit(HDC hdc, POINT dbCenter);

	MainGame() {}
	~MainGame() {}
};

