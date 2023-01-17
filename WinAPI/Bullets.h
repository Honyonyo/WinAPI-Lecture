#pragma once
#include "GameNode.h"
#define MISSILE_COUNT	300
#define MISSILEm1_COUNT	500
#define SHIELD_COUNT	100
#define RAISER_COUNT	100

enum ARMARY
{
	MISSILE = 0 ,
	SHOTGUN, MINIMI, SHIELD,
	G_MISSILE, RAISER, BLACK_HOLE, BEAM

	, ARMARY_COUNT
};

struct tagBullet
{
	GImage* img;
	RECT rc;
	int radius;
	int count;
	float* tx;
	float* ty;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
	ARMARY type;
	bool immo;
};
class EnemyManager;

class Bullet : public GameNode
{
protected:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	
	const char* _imageName;
	int _bulletMax;
	float _range;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y,float angle, float speed);
	void draw(void);
	void move(void);
	void removeBullet(int arrNum) {
		SAFE_DELETE(_vBullet[arrNum].img);

		_vBullet.erase(_vBullet.begin() + arrNum);
	}

	vector<tagBullet> getBullet() { return _vBullet; }
	Bullet(void){}
	virtual ~Bullet() {};
};


class Bullets : public GameNode
{
protected :
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	ARMARY _armaryCode;
	float* _rocketX;
	float* _rocketY;
	float _range;
	float _ticker;

public :
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void setTarget(float*, float*){};
	virtual void setTarget(void* a){};
	virtual void fire(float *x, float *y){};
	virtual void draw(void);
	virtual void move(void){};
	virtual bool isBulletEmpty(){
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
		{
			if (_viBullet->fire) return false;
		}
		return true;
	};
	virtual void removeBullet(int arrNum) {
			SAFE_DELETE(_vBullet[arrNum].img);

			_vBullet.erase(_vBullet.begin() + arrNum);
	}

	vector<RECT> getBulletRect() {
		vector<RECT> hitbox;
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
		{
			hitbox.push_back(_viBullet->rc);
		}
		return hitbox;
	}
	vector<tagBullet> getBullet() { return _vBullet; }
	vector<tagBullet>* getBulletP() { return &_vBullet; }

	virtual ARMARY getArmaryCode() { return _armaryCode; }
};

//배열처럼 미리 장전하고 발사하고싶어요. ->메모리소모는 크지만 발사때마다 있는 연산은 간소화됨
class Missile : public Bullets
{
private:
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float *x, float *y);
	void draw(void);
	void move(void);
	bool isBulletEmpty() {
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
		{
			if (_viBullet->fire) return false;
		}
		return true;
	};
	virtual ARMARY getArmaryCode() { return _armaryCode; }
	void removeBullet(int arrNum);

	Missile(){};
	~Missile(){};
};

class Beam : public GameNode
{
private:

	vector<tagBullet> _vBullet; // 백터
	vector<tagBullet>::iterator _viBullet; // 이터레이터
	typedef vector<tagBullet>::iterator iterBullet;
	float _range;
	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet() { return _vBullet; }
	void removeBullet(int arrNum);

	Beam() {}
	~Beam() {}

};

class ShotGun : public Bullets
{
private : 
	vector<vector<tagBullet>> _vvBullet;
	vector<vector<tagBullet>>::iterator _vivBullet;
	float _waveRange;

public : 
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void) override;
	void render(void) override;

	bool isBulletEmpty();

	void draw(void);
	void move(void);
	void division(void);
	void fire(float *x, float *y);

	ShotGun() {};
	~ShotGun() {};
};

class Minimi : public Bullets
{
private:
	GImage* _img;
	float _x, _y;
public : 
	HRESULT init(int bulletMax, float range);
	void release(void) override;
	void update(void) override;
	void render(void) override;

	void draw(void) override;
	void move(void) override;
	void fire(float* x, float* y);
};

class Shield : public Bullets
{
private:

public:
	HRESULT init(int bulletMax, float range);
	void update(void) override;
	void render(void) override;

	void draw(void) override;
	void move(void) override;
	void fire(float* x, float* y);
};

class G_Missile : public Bullets
{
private:
	float* _targetPx;
	float* _targetPy;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);
	void setTarget(float* tx, float* ty);
	void fire(float* x, float* y);
	void draw(void);
	void move(void);
	bool isBulletEmpty() {
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
		{
			if (_viBullet->fire) return false;
		}
		return true;
	};
};

class Raiser : public Bullets
{
private :
	float _cor;
public :
	HRESULT init(int bulletMax, float range);
	void release(void) override;
	void update(void) override;
	void render(void) override;

	void draw(void) override;
	void move(void) override;
	void fire(float *x, float *y);
};

class BlackHole : public Bullets
{
private:
	vector<EnemyManager*> _enemyGrup;
	bool _isFire;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);
	void setTarget(EnemyManager* a);
	void fire(float* x, float* y);
	void draw(void);
	void move(void);
	void push(void);

};

//쏠 때마다 만들고 삭제하고싶어요. ->메모리를 그때그때 할당하니까 절약이 되지만 할당하는데 런타임에 연산이 들어가용
class MissileM1 : public Bullets
{
protected:
	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float* x, float* y);
	void draw(void);
	void move(void);

	MissileM1(){};
	~MissileM1(){};
};