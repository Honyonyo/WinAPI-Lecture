#pragma once
#include "GameNode.h"
enum STATUS{
	STANDING = 0,
	MOVE,
	ATTACK,
	DEFEND,
	DAMAGED,


	STATUS_SIZE
};

class Charactor :public GameNode
{
private:
	GImage _myImage;
	STATUS _status;
	short _life;
	POINT _center;
	RECT _rcImage;
	RECT _rcHitbox;
	int _imgW;
	int _imgH;

	int _counter;
	int _standImageCounter;
	int _indexX, _indexY;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void attack();
	void damaged();
	void move();
	void standing();

	POINT getCenter() { return _center; };
	RECT getHitbox() { return _rcHitbox; };
	short getLife() { return _life; };
	short getStatus() { return _status; };

	void setCenter(POINT newCenter) { _center = newCenter; };
	void setCenter(int x, int y) { _center.x = x; _center.y = y; };
	void setImageRC() { RectMakeCenter(_center, _imgW, _imgH); };
	void setHitboxRC() { RectMakeCenter(_center, _imgW * 9 / 10, _imgH * 9 / 10); };
	void setStatus(STATUS status) { this->_status = status; };
	
	void lifePlus() { _life++; };
	void lifeMinus() { _life--; };

};


class Player : Charactor
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void guard();
};

