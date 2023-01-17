#include "stdafx.h"
#include "BulletManager.h"
#include "EnemyManager.h"

//MISSILE = 0,
//SHOTGUN, MINIMI, SHIELD,
//G_MISSILE, RAISER, BLACK_HOLE
//
//, ARMARY_COUNT


HRESULT BulletManager::init(int bulletMax, float range)
{
    Missile* basicMissile;
    basicMissile = new Missile;
    basicMissile->init(bulletMax, range);
    _vArmary.push_back(basicMissile);
    
    _minimi = new Minimi;
    _minimi->init(bulletMax, range);
    _minimi_on = false;

    return S_OK;
}

void BulletManager::release(void)
{
    for (_viArmary = _vArmary.begin(); _viArmary != _vArmary.end(); _viArmary++)
    {
        (*_viArmary)->release();
    }
}

void BulletManager::update(void)
{
   for (_viArmary = _vArmary.begin(); _viArmary != _vArmary.end();)
   {
       (*_viArmary)->update();

       if(_vArmary.size()>1)
       {
               if((*_viArmary) != _vArmary.back())
               {
                   if ((*_viArmary)->isBulletEmpty())
                   {
                       (*_viArmary)->release();
                       _viArmary = _vArmary.erase(_viArmary);
               cout << "     청소완료" << endl;
                       continue;
                   }//end if empty
               }
           _viArmary++;
       }//end if size
        else 
        { 
            _viArmary++; 
        }
    }

   if (_minimi_on)   _minimi->update();
}

void BulletManager::render(void)
{
    cout << "weapon render";
    for (_viArmary = _vArmary.begin(); _viArmary != _vArmary.end(); _viArmary++)
    {
        (*_viArmary)->render();
    }
    if (_minimi_on)   _minimi->render();
    cout << " 완료" << endl;
}

void BulletManager::armarySwap(int bulletMax, int range, float*x, float* y)
{
    if (KEYMANAGER->isOnceKeyDown(VK_F1))
    {
        if (_vArmary.back()->getArmaryCode() != MISSILE)
        {
            Missile* missile;
            missile = new Missile;
            missile->init(bulletMax, range);
            _vArmary.push_back(missile);
        }
        cout << " OK" << endl;
    }//end if F1

    if (KEYMANAGER->isOnceKeyDown(VK_F2))
    {
        if (_vArmary.back()->getArmaryCode() != SHOTGUN)
        {
           ShotGun* shotGun;
           shotGun = new ShotGun;
            shotGun->init(bulletMax, range);
            _vArmary.push_back(shotGun);
        }
        cout << " OK" << endl;
    }//end if F2

    if (KEYMANAGER->isToggleKey(VK_F3))
    {
        _minimi_on = true;
        _minimi->fire(x, y);
    }//end if F3

    if (KEYMANAGER->isOnceKeyDown(VK_F4))
    {
        if (_vArmary.front()->getArmaryCode() != SHIELD)
        {
            Shield* shield;
            shield = new Shield;
            shield->init(bulletMax, range);
            _vArmary.insert(_vArmary.begin(), shield);
            _vArmary.front()->fire(x, y);
        }
        cout << " OK" << endl;
    }//end if F4

    //채워ㅑㅇ해
    if (KEYMANAGER->isOnceKeyDown(VK_F5))
    {
        if (_vArmary.front()->getArmaryCode() != G_MISSILE)
        {
            G_Missile* gM;
            gM = new G_Missile;
            gM->init(bulletMax, range);
            _vArmary.push_back(gM);
        }
        cout << " OK" << endl;
    }//end if F5

    if (KEYMANAGER->isOnceKeyDown(VK_F6))
    {
        if (_vArmary.back()->getArmaryCode() != RAISER)
        {
            Raiser* raiser;
            raiser = new Raiser;
            raiser->init(bulletMax, range);
            _vArmary.push_back(raiser);
        }
        cout << " OK" << endl;
    }//end if F6

        //채워ㅑㅇ해
    if (KEYMANAGER->isOnceKeyDown(VK_F7))
    {
        if (_vArmary.front()->getArmaryCode() != BLACK_HOLE)
        {
            BlackHole* bh;
            bh= new BlackHole;
            bh->init(bulletMax, range);
            _vArmary.push_back(bh);
        }
        cout << " OK" << endl;
    }
}

void BulletManager::fire(float* x, float* y)
{
    cout << "fire" << endl;
    if (_vArmary.back()->getArmaryCode() == G_MISSILE)
    {
        cout << " 유도탄 세팅" << endl;
        int a = RND->getInt(3);
        int b = RND->getInt(_enemyGrup[1]->getMinionNumber());
        cout << a << ", " << b << endl;
        _vArmary.back()->setTarget(_enemyGrup[1]->getMinionPx(b), _enemyGrup[1]->getMinionPy(b));
    }
    if (_vArmary.back()->getArmaryCode() == BLACK_HOLE)
    {
        cout << " 블랙홀 세팅";
        _vArmary.back()->setTarget(&_enemyGrup[1]);
        cout << " 완료" << endl;
    }
    _vArmary.back()->fire(x,y);
}
