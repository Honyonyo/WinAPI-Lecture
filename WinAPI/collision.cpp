#include "stdafx.h"
#include "RocketScene.h"

void RocketScene::collision(void)
{
	cout << _rocket->getBullets().front().rc.top << endl;
	for (int i = 0; i < _rocket->getBullets().size(); i++)
	{
		for (int j = 0; j < _enemy[0]->getMinion().size(); j++)
		{
			RECT rc;
				if (IntersectRect(&rc, &_rocket->getBullets()[i].rc,
					&CollisionAreaResizing(_enemy[0]->getMinion()[j]->getRC(), 40, 30)))
					//&_enemy[0]->getMinion()[j]->getRect()))
				{
					if (!_rocket->getBullets()[i].immo)
					{
						_rocket->removeMissile(i);
					}
					_enemy[0]->getMinion()[j]->setLifeMinus();
					if (_enemy[0]->getMinion()[j]->isDead())
					{
						_enemy[0]->removeMinion(j);
					}
					break;
				}//end if collision
		}//end for minion
		for (int j = 0; j < _enemy[1]->getMinion().size(); j++)
		{
				RECT rc;
				if (IntersectRect(&rc, &_rocket->getBullets()[i].rc,
					&CollisionAreaResizing(_enemy[1]->getMinion()[j]->getRC(), 40, 30)))
					//&_enemy[1]->getMinion()[j]->getRect()))
				{
					if (!_rocket->getBullets()[i].immo)
					{
						_rocket->removeMissile(i);
					}
					_enemy[1]->getMinion()[j]->setLifeMinus();
					if (_enemy[1]->getMinion()[j]->isDead())
					{
						_enemy[1]->removeMinion(j);
					}
					break;
				}//end if collision
		}//end for minion
		for (int j = 0; j < _enemy[2]->getMinion().size(); j++)
		{
				RECT rc;
				if (IntersectRect(&rc, &_rocket->getBullets()[i].rc,
					&CollisionAreaResizing(_enemy[2]->getMinion()[j]->getRC(), 40, 30)))
					//&_enemy[2]->getMinion()[j]->getRect()))
				{
					if (!_rocket->getBullets()[i].immo)
					{
						_rocket->removeMissile(i);
					}
					_enemy[2]->getMinion()[j]->setLifeMinus();
					if (_enemy[2]->getMinion()[j]->isDead())
					{
						_enemy[2]->removeMinion(j);
					}
					break;
				}//end if collision
		}//end for minion

	}//end for bullet

	//for (int i = 0; i < _rocket->getRaiser()->getBullet().size(); i++)
	//{
	//	for (int j = 0; j < _enemy[0]->getMinion().size(); i++)
	//	{
	//		RECT rc;
	//		if (IntersectRect(&rc, &_rocket->getRaiser()->getBullet()[i].rc,
	//			&CollisionAreaResizing(_enemy[0]->getMinion()[j]->getRC(), 40, 30)))
	//		{
	//			_enemy[0]->getMinion()[j]->setLifeMinus();
	//			//_enemy[0]->removeMinion(j);
	//			break;
	//		}
	//	}
	//}
}