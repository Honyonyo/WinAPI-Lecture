#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Pattern.h"
#include "Bullets.h"

class Rocket;
class EnemyManager : public GameNode
{
private : 
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;
private:
	//부모를 참조하고 자식 재정의
	vEnemy _vMinion;
	viEnemy _viMinion;
	
	Bullet* _bullet;
	Rocket* _rocket;
	
	

	vector<Pattern*> _vPattern;
	vector<Pattern*>::iterator _viPattern;
	short _patternNumber;	

public:
	HRESULT init(void);
	HRESULT init(short);
	void release(void);
	void update(void);
	void update(vector<Bullets> bullet);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNum)
	{
		SAFE_DELETE(_vMinion[arrNum]);
		_vMinion.erase(_vMinion.begin() + arrNum);
	};

	void minionBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinion(void) { return _vMinion; }
	Bullet* getBullet(void) { return _bullet; }
	void setRocketMemoryAddress(Rocket* rk) { _rocket = rk; }




	void minionDamaged(RECT rc)
	{
		for(_viMinion = _vMinion.begin(); _viMinion!=_vMinion.end(); _viMinion++)
		{
			RECT tmp;
			if (IntersectRect(&tmp, &((*_viMinion)->getRC()), &rc))
			{
				(*_viMinion)->setLifeMinus();
			}
		}
	};


	int getMinionNumber() { return _vMinion.size(); }
	float* getMinionPx(int num) { return _vMinion[num]->getpX(); }
	float* getMinionPy(int num) { return _vMinion[num]->getpY(); }

	EnemyManager(){}
	~EnemyManager(){}
};

