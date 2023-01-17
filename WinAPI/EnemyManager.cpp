#include "stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Rocket.h"

HRESULT EnemyManager::init(void)
{
    IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/Object/JellyFish.bmp",.0f, .0f, 1140, 47, 19, 1, true, RGB(255,0,255));
    IMAGEMANAGER->addImage("적미사일", "Resources/Images/Object/bullet.bmp", 7*2, 7*2, true, RGB(255, 0, 255));
    setMinion();

    _bullet = new Bullet;
    _bullet->init("적미사일", 30, 1000);

    _patternNumber = 1;
    return S_OK;
}
HRESULT EnemyManager::init(short a)
{
    IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/Object/JellyFish.bmp",.0f, .0f, 1140, 47, 19, 1, true, RGB(255,0,255));
    //IMAGEMANAGER->addFrameImage("피통", "Resources/Images/Object/lifeImg.bmp", .0f, .0f, 34, 24, 1, 6, true, RGB(255, 0, 255));
    _patternNumber = a;
    setMinion();
    return S_OK;
}

void EnemyManager::release(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); _viMinion++)
    {
        (*_viMinion)->release();
        SAFE_DELETE(*_viMinion);
    }
    for (_viPattern = _vPattern.begin(); _viPattern != _vPattern.end(); _viPattern++)
    {
        (*_viPattern)->release();
    }
}

void EnemyManager::update(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); _viMinion++)
    {
        if (!(*_viMinion)->isDead())
        {
            (*_viMinion)->update();
        }
    }
    for (_viPattern = _vPattern.begin(); _viPattern != _vPattern.end(); _viPattern++)
    {
        (*_viPattern)->update();
    }
    minionBulletFire();
    _bullet->update();
    //collision();
}

void EnemyManager::update(vector<Bullets> bullet)
{
    for(auto iter = bullet.begin(); iter!=bullet.end(); iter++)
    {
        //minionDamaged(*iter->);
    }
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); _viMinion++)
    {
        if (!(*_viMinion)->isDead())
        {
            (*_viMinion)->update();
        }
    }
    for (_viPattern = _vPattern.begin(); _viPattern != _vPattern.end(); _viPattern++)
    {
        (*_viPattern)->update();
    }
}

void EnemyManager::render(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); _viMinion++)
    {
        if (!(*_viMinion)->isDead())
        {
            (*_viMinion)->render();
           // IMAGEMANAGER->findImage("피통")->frameRender(getMemDC(), *(*_viMinion)->getpX() - IMAGEMANAGER->findImage("피통")->getFrameWidth() / 2,
           //     *(*_viMinion)->getpY() - (*_viMinion)->getHalfH() - 5 - IMAGEMANAGER->findImage("피통")->getFrameHeight(), 0, (*_viMinion)->getLife());
        }
    }
}

void EnemyManager::setMinion(void)
{
    switch (_patternNumber)
    {
    case 1:
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                Enemy* jellyFish;
                jellyFish = new Minion;
                jellyFish->init("해파리", PointMake(250 + j * 200, 100 + i * 100));
                _vMinion.push_back(jellyFish);
                Pattern* pattern;
                pattern = new Pattern;
                pattern->init(_vMinion.back()->getpX(), _vMinion.back()->getpY(), _patternNumber);
                _vPattern.push_back(pattern);
            }
        }//end for
        break;
    case 2:
        for (int i = 0; i < 20; i++)
        {
            Enemy* jellyFish;
            jellyFish = new Minion;
            jellyFish->init("해파리", PointMake(WINSIZE_X / 2 + 150 * cos(i * PI_2 / 20), WINSIZE_Y / 2 + 150 * sin(i * PI_2 / 20)));
            _vMinion.push_back(jellyFish);
            Pattern* pattern;               
            pattern = new Pattern;
            pattern->init(_vMinion.back()->getpX(), _vMinion.back()->getpY(), _patternNumber);
            _vPattern.push_back(pattern);
        }
        break;
    case 3:
        for (int j = 0; j < 15; j++)
        {
            Enemy* jellyFish;
            jellyFish = new Minion;
            jellyFish->init("해파리", PointMake(250 + j * 100, WINSIZE_Y/2-100));
            _vMinion.push_back(jellyFish);
            Pattern* pattern;
            pattern = new Pattern;
            pattern->init(_vMinion.back()->getpX(), _vMinion.back()->getpY(), _patternNumber);
            _vPattern.push_back(pattern);
        }
    }//end switch
}

void EnemyManager::minionBulletFire(void)
{
    for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); _viMinion++)
    {
        if ((*_viMinion)->bulletCountFire())
        {
            RECT rc = (*_viMinion)->getRC();
            _bullet->fire((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 + 30,
                getAngle((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2+30,
                    _rocket->getPosition().x, _rocket->getPosition().y),
                RND->getFromFloatTo(2.0f, 4.0f));
        }
    }
}

void EnemyManager::collision(void)
{
    for (int i = 0; i < _bullet->getBullet().size(); i++)
    {
        RECT rc;
        if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
            &_rocket->getRect()))
        {
            _bullet->removeBullet(i);
            _rocket->hitDamage(2.0f);
        }
    }
}

