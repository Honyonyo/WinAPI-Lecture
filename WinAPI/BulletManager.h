#pragma once
#include "GameNode.h"
#include "Bullets.h"
class EnemyManager;
class BulletManager : public GameNode
{
private:
	vector<EnemyManager*> _enemyGrup;

	vector<Bullets*> _vArmary;
	vector<Bullets*>::iterator _viArmary;

	Minimi* _minimi;
	bool _minimi_on;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void armarySwap(int bulletMax, int range, float* x, float* y);
	void fire(float* x, float* y);

	BulletManager(EnemyManager* enemyGrup[])
	{
		for(int i =0 ; i<3; i++)
		{
			_enemyGrup.push_back(enemyGrup[i]);
		}
	}
};

