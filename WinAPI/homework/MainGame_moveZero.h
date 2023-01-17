#pragma once
#include "GameNode.h"

#define PLAYERSIZE		150
#define MAGNIFICATION	8
#define MINIMAP_WIDTH	(WINSIZE_X/MAGNIFICATION)
#define MINIMAP_HEIGHT	(WINSIZE_Y/MAGNIFICATION)
#define MOVEPOINT		3

class MainGame : public GameNode
{
private:
	GImage* _bgImage;
	GImage* _miniBgImage;
	GImage* _zero;
	RECT _rc;
	RECT _minimi;
	RECT _miniMap;

	int _count;
	int _indexX;
	int _indexY;
	bool _isLeft;



	int _alphaA, _alphaB;
	int _alphaNum;

	bool _isAlphaIncrease;

	int coordinateX[3][3];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};

