#include "stdafx.h"
#include "Rocket.h"
#include "EnemyManager.h"

HRESULT Rocket::init(EnemyManager* enemy[])
{
    cout << "===== 로켓 로드 =====" << endl;

    _image = IMAGEMANAGER->addImage("로켓", "Resources/Images/Object/Rocket.bmp", 52, 64,true, Tcolor);
    _flame = new Flame;
    _flame->init("Flame.bmp", &_x, &_y);

    _hpBar = new ProgressBar;
    _hpBar->init(&_x, &_y, 52, 5);

    _missile = new MissileM1;
    _missile->init(30,600);
    _raiser = new Raiser;
    _raiser->init(20,700);
    _weapon = MISSILE;

    _x = WINSIZE_X/2;
    _y = WINSIZE_Y*3/4;
    _rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
    _isDown = false;
    _speed = 2;
    cout << "===== 로켓 로드 완료 =====" << endl;;
    return S_OK;
}

vector<RECT> Rocket::getBulletHitBox(void)
{
    switch (_weapon)
    {
    case MISSILE:
        return _missile->getBulletRect();

    case RAISER:
        return _raiser->getBulletRect();
    default:
        cout << "뭐가 없다" << endl;
        return _missile->getBulletRect();
    }
}

void Rocket::release(void)
{
    _flame->release();
    _image->release();

    SAFE_DELETE(_image);
    SAFE_DELETE(_flame);
}

void Rocket::update(void)
{

    if (KEYMANAGER->isStayKeyDown(VK_SPACE))
    {
        switch (_weapon)
        {
        case MISSILE:
            _missile->fire(&_x, &_y);
            break;
        case RAISER:
            _raiser->fire(&_x, &_y);
            break;
        }
    }

    if (KEYMANAGER->isOnceKeyDown(VK_F1))
    {
        _weapon = MISSILE;
    }

    if (KEYMANAGER->isOnceKeyDown(VK_F2))
    {
        _weapon = RAISER;
    }

    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _x = _x - _speed < 0 ? 0 : _x - _speed;
    }
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _x = _x + _speed > WINSIZE_X ? WINSIZE_X : _x + _speed;

    }
    if (KEYMANAGER->isStayKeyDown(VK_UP))
    {
        _y = _y - _speed < 0 + _image->getHeight()/_speed
            ? _image->getHeight() / _speed : _y - _speed;
    }
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        _y = _y + _speed > WINSIZE_Y - _image->getHeight() / _speed
            ? WINSIZE_Y - _image->getHeight() / _speed : _y + _speed;
    }
    _rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
//    printf("로켓 _x %f, _y %f\n", _x, _y);
    _flame->update();

    _missile->update();
    _raiser->update();

    //collision();
}

void Rocket::render(void)
{
    _flame->render();
    _raiser->render();
    _missile->render();

    _image->render(getMemDC(), _rc.left, _rc.top);
}

void Rocket::collision(void)
{
    for (int i = 0; i < getBullets().size(); i++)
    {
        for (int j = 0; j < _em->getMinion().size(); j++)
        {
            RECT rc;
            if (IntersectRect(&rc, &getBullets()[i].rc,
                &CollisionAreaResizing(_em->getMinion()[j]->getRC(), 40, 30)))
                //&_enemy[0]->getMinion()[j]->getRect()))
            {
                if (!getBullets()[i].immo)
                {
                    removeMissile(i);
                }
                break;
            }//end if collision
        }//end for minion
    }
}