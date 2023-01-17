#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#include "ProgressBar.h"

class EnemyManager;

class Rocket : public GameNode
{
private:
	GImage* _image;
	Flame* _flame;
	
	ARMARY _weapon;
	Raiser* _raiser;
	MissileM1* _missile;
	EnemyManager* _em;

	float _x, _y;
	float _currentHp;
	float _maxHp;
	int _speed;
	bool _isDown;
	RECT _rc;


	ProgressBar* _hpBar;
	float _currentHP;
	float _maxHP;

public:
	HRESULT init(EnemyManager* enemy[]);
	RECT* getRocketBox(void) {
		return &_rc;
	}
	vector<RECT> getBulletHitBox(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }
	void removeMissile(int arrNum) {
		_missile->removeBullet(arrNum);
	}

	MissileM1* getMissileM1() { return _missile; }
	Raiser* getRaiser() { return _raiser; }

	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }
	RECT getRect(void) { return _rc; }

	// ↓ ↓ ↓ ↓ ↓ 내가 만든거 ↓ ↓ ↓ ↓ ↓ ↓
	vector<tagBullet> getBullets() {
		vector<tagBullet> tmp;
		tmp = _missile->getBullet();
		tmp.push_back(_raiser->getBullet().back());
		return tmp;
	}

	inline void hitDamage(float damage){
		if (_currentHP <= 0)
		{
			_currentHP = 0;
			return;
		}

		_currentHP -= damage;
	}

};

