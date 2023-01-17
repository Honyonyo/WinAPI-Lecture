#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
_currentFrameX(0), _currentFrameY(0),
_x(.0f), _y(.0f),
_rndTimeCount(.0f),
_worldTimeCount(.0f),
_life(1), _death(false),
_rndFireCount(0.0f),
_bulletFireCount(0.0f)
{
}

HRESULT Enemy::init(void)
{
    /* Do Nothing */
    return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
    _worldTimeCount = GetTickCount64();
    _rndTimeCount = RND->getFromFloatTo(50, 150);
    _image = IMAGEMANAGER->findImage(imageName);
    _x = position.x;
    _y = position.y;
    _rc = RectMakeCenter(position, _image->getFrameWidth(), _image->getFrameHeight());

    _bulletFireCount = TIMEMANAGER->gerWorldTime();
    _rndFireCount = RND->getFromFloatTo(.5f, 4.5f);

    return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
    move();
   _rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Enemy::render(void)
{
    draw();
    animation();
}

//자식에서 구현(다형성)
void Enemy::move(void)
{
}

void Enemy::draw(void)
{
    _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
{
    if (_rndTimeCount + _worldTimeCount <= GetTickCount64())
    {
        _worldTimeCount = GetTickCount64();
        _currentFrameX++;
        if(_image->getMaxFrameX()<_currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}

bool Enemy::bulletCountFire(void)
{
    if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->gerWorldTime())
    {
        _bulletFireCount = TIMEMANAGER->gerWorldTime();
        _rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);

        return true;
    }
    return false;
}

