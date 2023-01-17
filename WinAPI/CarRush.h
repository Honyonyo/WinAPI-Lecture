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
* ����	WINSIZE_X = 800
*		WINSIZE_Y = 1000
* 
* ��ų
	<ȸ��>
	PŰ�� ������ ������� 1 ȸ���մϴ�.
	 (���� �� 3�� �ȿ� ������ ��Ȱ�� �����մϴ�.)
	<��ȣ��>
	SŰ�� ������ ��ȣ���� �����˴ϴ�.
	 (�浹�ÿ��� 1.5�� ��ȣ���� ����ϴ�.)
	<ȫ�ذ�����>
	�����̽��ٸ� ������ ȫ�ذ����� �մϴ�.


����, �̹��� ����, �⺻���� ��� ��� ����� �ȵ� �̼��ϰ� �̼��� ���Դϴ�.
��ų�� �÷��̾� ����ü�� ���� maingame�� ������ ���������ؼ� ������ ���� �������ϴ�..

�̹��� �Ѹ� ������ hitbox�� ���� ��������ϴ�.

SetTimer, OnTimer, KillTimer�� �̿��ؼ� ���� �ҷ����������,
GameNode�� ��ġ�� �ʰ� ��� �� �� ������ ���� ã�� ���߽��ϴ�.
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

		IMAGEMANAGER->addImage("����", "Resources/Images/Object/CarOrange.bmp", 120, 280, true, OPACITY_RGB);
		IMAGEMANAGER->addImage("����", "Resources/Images/Object/shield.bmp", 300, 300, true, OPACITY_RGB);
		IMAGEMANAGER->addFrameImage("�����", "Resources/Images/Object/lifeImg.bmp", 170, 140, 1, 7, true, OPACITY_RGB);
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

