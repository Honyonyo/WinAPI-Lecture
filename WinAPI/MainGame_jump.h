#pragma once
#include "GameNode.h"

#define PLAYERSIZE		120
#define MAGNIFICATION	8
#define MINIMAP_WIDTH	(WINSIZE_X/MAGNIFICATION)
#define MINIMAP_HEIGHT	(WINSIZE_Y/MAGNIFICATION)
#define MOVEPOINT		3

enum PLYRACTION {
	JUMP = 1,
	STANDING = 10,
	WALK,
	MOVEJUMP,
	HANGING_WALL,
	SLIDEDOWN_WALL
};

struct Platform {
	RECT rc;
};

struct Player {
	RECT rc;
	RECT shadow;
	short action;
	float speed;
	float weight;
	float friction;
	bool jump;
	bool leftFoward;

	void setShadow(int left, int top, int right, int bottom) {
		shadow = { left, top, right, bottom };
	}
};
class MainGame : public GameNode
{
private:
	Player _rcPlayer;
	Platform _floor;
	Platform _wall;
	vector<Platform> vPlatform;
	vector<Platform> tmpvPlatform;

	int _count;
	bool _isLeft;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void printAction(HDC hdc);

	void playerMove();
	void setPlyrShadow(vector<Platform> vPlatform) {
		_rcPlayer.setShadow(_rcPlayer.rc.left, _rcPlayer.rc.bottom - 1,
			_rcPlayer.rc.right, _rcPlayer.rc.bottom);

	}//setPlyrShadow end

	void jumpstart();
	void jump();

	MainGame() {}
	~MainGame() {}
};

