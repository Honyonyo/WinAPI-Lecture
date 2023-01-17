#include "stdafx.h"
#include "Bullets.h"
#include "EnemyManager.h"

HRESULT Bullet::init(const char* imageName, int bulletMax, float range)
{
    _imageName = imageName;
    _range = range;
    _bulletMax = bulletMax;

    return S_OK;
}

void Bullet::release(void)
{
    _vBullet.clear();
}

void Bullet::update(void)
{
    move();
}

void Bullet::render(void)
{
    draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
    if (_bulletMax <= _vBullet.size()) return;

        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));
        bullet.img = IMAGEMANAGER->findImage(_imageName);
        bullet.speed = speed;
        bullet.angle = angle;
        bullet.x = bullet.fireX = x;
        bullet.y = bullet.fireY = y;
        bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
        
        _vBullet.push_back(bullet);    
}

void Bullet::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
{
    if (!_viBullet->fire) continue;

    _viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
}
}

void Bullet::move(void)
{
    _viBullet = _vBullet.begin();
    for (int i = 0; _viBullet != _vBullet.end();)
    {
        _viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
        _viBullet->x += -sinf(_viBullet->angle) * _viBullet->speed;
        _vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y, _vBullet[i].img->getWidth(), _vBullet[i].img->getHeight());

        if (getDistance(_viBullet->fireX,_viBullet->fireY, _viBullet->x, _viBullet->y) > _range)
        {
            ////수업후 추가코드////
            //혹시라도 있을 수 있는 오류를 방지하기위해서- 메모리누수와 댕글러.. 등등 방지
            _viBullet = _vBullet.erase(_viBullet);
            continue;
        }
    }
}

HRESULT Bullets::init(int bulletMax, float range)
{
    _range = range;
    _ticker = 0;

    for (int i = 0; i < bulletMax; i++)
    {
        tagBullet bullet;
        //첫 번째 인자가 가리키는 주소의 값을 0으로 초기화
        //인자 : 메모리 블록, 메모리 블록 사이즈
        //내부적으로 memset을 호출하고있다.
        ZeroMemory(&bullet, sizeof(tagBullet));
        bullet.fire = false;
        bullet.speed = 5.0f;

        _vBullet.push_back(bullet);
    }

    return S_OK;
}

void Bullets::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void Bullets::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire)
        {
            _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
            if (_viBullet->img->getFrameX() == _viBullet->img->getMaxFrameX())
                _viBullet->img->setFrameX(0);
            else _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        }
    }
}

#pragma region 미사일
HRESULT Missile::init(int bulletMax, float range)
{
    _range = range;
    _ticker = 0;
    _armaryCode = MISSILE;

    for (int i = 0; i < bulletMax; i++) 
    {
        tagBullet bullet;
        //첫 번째 인자가 가리키는 주소의 값을 0으로 초기화
        //인자 : 메모리 블록, 메모리 블록 사이즈
        //내부적으로 memset을 호출하고있다.
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new GImage;
        bullet.img->init("Resources/Images/Object/Missile.bmp", .0f, .0f,
            416, 64, 13, 1,
            true, RGB(255, 0, 255));

        bullet.fire = false;
        bullet.speed = 5.0f;

        bullet.type = MISSILE;
        bullet.immo = false;

        _vBullet.push_back(bullet);
    }
    cout << "무기 전환 : 미사일";

    return S_OK;
}

void Missile::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void Missile::update(void)
{
    move();
}

void Missile::render(void)
{
    draw();
}

void Missile::fire(float* x, float* y)
{
    if (MISSILE_COUNT + _ticker < GetTickCount64())
    {
        _ticker = GetTickCount64();
        for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
        {
            if (_viBullet->fire) continue;
            _viBullet->fire = true;
            _viBullet->x = _viBullet->fireX = *x;
            _viBullet->y = _viBullet->fireY = *y;
            _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

            cout << " missile 발사" << endl;
            break;
        }
    }
}

void Missile::draw(void)
{
    // 수업코드
    //for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    //{
    //    if (!_viBullet->fire) continue;
    //    _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
    //    _viBullet->count++;
    //    if (_viBullet->count % 5 == 0)
    //    {
    //        _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
    //        if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
    //        {
    //            _viBullet->img->setFrameX(0);
    //        }
    //        _viBullet->count = 0;
    //    }
    //}
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire)
        {
            _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
            if (_viBullet->img->getFrameX() == _viBullet->img->getMaxFrameX())
                _viBullet->img->setFrameX(0);
            else _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        }
    }
}

void Missile::move(void)
{
    //for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    //{
    //    if (!_viBullet->fire) continue;
    //    _viBullet->y -= _viBullet->speed;
    //    _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
    //        _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
    //    if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
    //    {
    //        _viBullet->fire = false;
    //    }
    //}
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->y -= _viBullet ->speed;
        if (_viBullet->fireY - _viBullet->y > _range)
        {
            _viBullet->fire = false;
            continue;
        }
        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
    }
}

void Missile::removeBullet(int arrNum)
{
    _vBullet[arrNum].fire = false;
        //SAFE_DELETE(_vBullet[arrNum].img);

        //_vBullet.erase(_vBullet.begin() + arrNum);
}

#pragma endregion
#pragma region 미사일M1
HRESULT MissileM1::init(int bulletMax, float range)
{
    _range = range;
    _bulletMax = bulletMax;
    _ticker = 0;

    return S_OK;
}

void MissileM1::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void MissileM1::update(void)
{
    move();
}

void MissileM1::render(void)
{
    draw();
}

void MissileM1::fire(float* x, float* y)
{
    // 최대 발사 갯수를 막는다.
    if (_bulletMax <= _vBullet.size()) return;
    if(MISSILEm1_COUNT+_ticker<GetTickCount64())
    {
        _ticker = GetTickCount64();
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));
        bullet.img = new GImage;
        bullet.img->init("Resources/Images/Object/Missile.bmp", .0f, .0f,
            416, 64, 13, 1,
            true, RGB(255, 0, 255));

        bullet.x = bullet.fireX = *x;
        bullet.y = bullet.fireY = *y;
        bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
        bullet.count = 0;
        bullet.speed = 3.0f;

        _vBullet.push_back(bullet);
        cout << "미사일 M1 발사!" << endl;
    }
}

void MissileM1::draw(void)
{
    //for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//{
//    if (!_viBullet->fire) continue;

//    _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

//    _viBullet->count++;
//    if (_viBullet->count % 3 == 0)
//    {
//        _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
//        if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
//        {
//            _viBullet->img->setFrameX(0);
//        }
//        _viBullet->count = 0;
//    }
//}


    for (int i = 0; i <_vBullet.size(); i++)
    {
        if (_vBullet[i].count % 5 == 0)
        {
            _vBullet[i].img->getFrameX() == 0 ?
                _vBullet[i].img->setFrameX(_vBullet[i].img->getMaxFrameX())
                : _vBullet[i].img->setFrameX(_vBullet[i].img->getFrameX() - 1);
        }
        _vBullet[i].img->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
        _vBullet[i].count++;
    }
}

void MissileM1::move(void)
{
    _viBullet = _vBullet.begin();
    for (int i = 0; _viBullet != _vBullet.end();)
    {
        if (_vBullet[i].fireY - _vBullet[i].y > _range)
        {
            ////수업후 추가코드////
            //혹시라도 있을 수 있는 오류를 방지하기위해서- 메모리누수와 댕글러.. 등등 방지
            SAFE_DELETE(_viBullet->img);
            ////수업후 추가코드////
            _viBullet = _vBullet.erase(_viBullet);
            continue;
        }
        ////수업후 추가코드////
        //좀 더 안정성을 위해 else{}로 감싸준다
        else {
            _vBullet[i].y -= _vBullet[i].speed;
            _vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y, _vBullet[i].img->getFrameWidth(), _vBullet[i].img->getFrameHeight());
            i++;
            _viBullet++;
        }
    }
}
#pragma endregion

// ===<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>===
// ===<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>===
// ===<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>======<<  SHOT GUN  >>===
#pragma region 샷건
HRESULT ShotGun::init(int bulletMax, float range)
{
    _range = range;
    _waveRange = range / 3;
    _ticker = 0;
    _armaryCode = SHOTGUN;

        tagBullet bullet;
        //첫 번째 인자가 가리키는 주소의 값을 0으로 초기화
        //인자 : 메모리 블록, 메모리 블록 사이즈
        //내부적으로 memset을 호출하고있다.
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new GImage;
        bullet.img->init("Resources/Images/Object/Shotgun.bmp", .0f, .0f,
           250, 22, 8, 1,
            true, RGB(0, 0, 0));

        bullet.fire = false;
        bullet.speed = 5.0f;
        bullet.count = 0;


        _vBullet.push_back(bullet);

    for (int i = 0; i < bulletMax; i++)
    {
        _vvBullet.push_back(_vBullet);
    }
    
    cout << "무기 전환 : 산탄총";
    return S_OK;
}

void ShotGun::release(void)
{
    for (_vivBullet = _vvBullet.begin(); _vivBullet != _vvBullet.end(); _vivBullet++)
    {
        for (_viBullet = _vivBullet->begin(); _viBullet != _vivBullet->end(); ++_viBullet)
        {
            SAFE_DELETE(_viBullet->img);
        }        
        _vivBullet->clear();
    }
    _vBullet.clear();
}

void ShotGun::update(void)
{
    move();
    division();
}

void ShotGun::render(void)
{
    draw();
}

bool ShotGun::isBulletEmpty()
{
    for (_vivBullet = _vvBullet.begin(); _vivBullet != _vvBullet.end(); _vivBullet++)
    {
        if (_vivBullet->front().fire) return false;
    }
    return true;
}

void ShotGun::draw(void)
{
    //cout << "샷건 draw" << endl;
    for (_vivBullet = _vvBullet.begin(); _vivBullet != _vvBullet.end(); _vivBullet++)
    {
        for (_viBullet = _vivBullet->begin(); _viBullet != _vivBullet->end(); ++_viBullet)
        {
            if (_viBullet->fire)
            {
                cout << _viBullet->rc.left << " " << _viBullet->rc.top << endl;

                _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
                if (_viBullet->img->getFrameX() == _viBullet->img->getMaxFrameX())
                    _viBullet->img->setFrameX(0);
                else _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
            }
        }
    }
}

void ShotGun::move(void)
{
    for (_vivBullet = _vvBullet.begin(); _vivBullet != _vvBullet.end(); _vivBullet++)
    {
        for (_viBullet = _vivBullet->begin(); _viBullet < _vivBullet->end();)
        { 
            _viBullet->y -= _viBullet->speed;
            if (_viBullet->fireY - _viBullet->y > _range)
            {
                if (_viBullet == _vivBullet->begin())
                {
                    _viBullet->fire = false;
                    _viBullet++;
                    continue;
                }
                else
                {
                    _viBullet = _vivBullet->erase(_viBullet);
                    cout << "지워짐" << endl;
                    continue;
                }
            }
            _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
            cout << _viBullet->rc.left << " " << _viBullet->rc.top << endl;
            
            _viBullet++;
        }
    }
}

void ShotGun::division(void)
{
      //  cout << "division 1" << endl;
    for (_vivBullet = _vvBullet.begin(); _vivBullet != _vvBullet.end(); _vivBullet++)
    {
        //cout << "division 2" << endl;
        if(_vivBullet->front().fire)
        {
            switch (_vivBullet->front().count)
            {
            case 0:

                if (_vivBullet->front().fireY - _vivBullet->front().y > _waveRange)
                {
                    cout << "비거리 "<<_vivBullet->front().fireY - _vivBullet->front().y << endl;
                    _vivBullet->front().count++;
                    _viBullet = _vivBullet->begin();
                    _vivBullet->push_back(*_viBullet);
                    _vivBullet->back().x -= _vivBullet->back().img->getFrameWidth();
                    cout << "division 2-1" << endl;
                    _vivBullet->push_back(_vivBullet->front());
                    cout << "division 2-2" << endl;
                    _vivBullet->back().x += _vivBullet->back().img->getFrameWidth();
                }

                break;

            case 1:
                if (_vivBullet->front().fireY - _vivBullet->front().y > _waveRange * 2)
                {
                    _vivBullet->front().count++;
                    cout << "비거리 " << _vivBullet->front().fireY - _vivBullet->front().y << endl;
                    int a = _vivBullet->size();
                    for (int i = 0; i < a; i++)
                    {
                        _viBullet = _vivBullet->begin() + i;
                        tagBullet tmp = (*_viBullet);
                        _vivBullet->push_back(tmp);
                        _vivBullet->back().x -= _vivBullet->back().img->getFrameWidth() * 3;
                        cout << "division 3-1" << endl;
                        _vivBullet->push_back(tmp);
                        cout << "division 3-2" << endl;
                        _vivBullet->back().x += _vivBullet->back().img->getFrameWidth() * 3;
                    }
                }
                break;

            case 2:
            default:
                break;
            }
        }
    }//end for
    //cout << "division 3" << endl;

}

void ShotGun::fire(float* x, float* y)
{
    if (MISSILEm1_COUNT + _ticker < GetTickCount64())
    {
        _ticker = GetTickCount64();
        for (_vivBullet = _vvBullet.begin(); _vivBullet != _vvBullet.end(); _vivBullet++)
        {
            _viBullet = _vivBullet->begin();

            if (_viBullet->fire) continue;
            else 
            {
                _viBullet->fire = true;
                _viBullet->x = _viBullet->fireX = *x;
                _viBullet->y = _viBullet->fireY = *y;
                _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
                    _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

                cout << " Shot Gun 발사" << endl;

            }
        }
        //for (_vivBullet = _vvBullet.begin(); _vivBullet != _vvBullet.end(); _vivBullet++)
        //{
        //    if ((*_vivBullet).front().fire) continue;
        //    (*_vivBullet).front().fire = true;
        //    (*_vivBullet).front().x = (*_vivBullet).front().fireX = x;
        //    (*_vivBullet).front().y = (*_vivBullet).front().fireY = y;
        //    (*_vivBullet).front().rc = RectMakeCenter((*_vivBullet).front().x, (*_vivBullet).front().y, 
        //                                (*_vivBullet).front().img->getFrameWidth(), (*_vivBullet).front().img->getFrameHeight());
        //    cout << " Shot Gun 발사" << endl;
        //    break;
        //}
    }

}
#pragma endregion

// ===<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>===
//   SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  
// >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD  >>======<<  SHIELD
#pragma region 실드
HRESULT Shield::init(int bulletMax, float range)
{
    _range = range;
    _ticker = 300;
    _armaryCode = SHIELD;

        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new GImage;
        bullet.img -> init("Resources/Images/Object/shield.bmp", .0f, .0f,
            524, 88, 6, 1,
            true, RGB(0, 0, 0));
         cout << "무기 전환 : 실드";
        bullet.fire = false;
        bullet.radius = _range / 2;

        _vBullet.push_back(bullet);


    return S_OK;
}

void Shield::update(void)
{
    move();
}

void Shield::render(void)
{
    draw();
}

void Shield::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
    {
        if (_viBullet->fire)
        {
            _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
            if(_viBullet->img->getFrameX() == _viBullet->img->getMaxFrameX())
                _viBullet->img->setFrameX(0);
            else _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        }
    }

}

void Shield::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
    {
        if (_viBullet->fire)
        {
            if (++(_viBullet->count) > SHIELD_COUNT)
            {
                _viBullet->fire = false;
                continue;
            }
            _viBullet->rc = RectMakeCenter(*_rocketX, *_rocketY, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
        }
    }
}

void Shield::fire(float* x, float* y)
{
    _rocketX = x;
    _rocketY = y;
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
    {
        if (_viBullet->fire) continue;
        
        _viBullet->fire = true;
        _viBullet->count = 0;
        _viBullet->rc = RectMakeCenter(*_rocketX, *_rocketY, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
        cout << "    실드 발동" << endl;
        break;
    }
}
#pragma endregion

// ===>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<===
//   MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  
// <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI  <<======>>  MINIMINI
#pragma region 미니미
HRESULT Minimi::init(int bulletMax, float range)
{
    _range = range;
    _ticker = 0;
    _armaryCode = MINIMI;
    _img = new GImage;
    _img->init("Resources/Images/Object/Rocket.bmp", 26, 32,
        true, RGB(255, 0, 255));
    _x = _y = 0;

    for (int i = 0; i < bulletMax; i++)
    {
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new GImage;
        bullet.img->init("Resources/Images/Object/Missile.bmp", .0f, .0f,
            208, 32, 13, 1,
            true, RGB(255, 0, 255));

        bullet.fire = false;
        bullet.speed = 5.0f;

        _vBullet.push_back(bullet);
    }
    cout << "미니미소환";

    return S_OK;
}

void Minimi::release(void)
{
    SAFE_DELETE(_img);
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void Minimi::update(void)
{
    move();
}

void Minimi::render(void)
{
    draw();
}

void Minimi::draw(void)
{
    _img->render(getMemDC(), *_rocketX - 60, *_rocketY);

    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire)
        {
            _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
            if (_viBullet->img->getFrameX() == _viBullet->img->getMaxFrameX())
                _viBullet->img->setFrameX(0);
            else _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        }
    }
}

void Minimi::move(void)
{
    _x = *_rocketX - 50;
    _y = *_rocketY;
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->y -= _viBullet->speed;
        if (_viBullet->fireY - _viBullet->y > _range)
        {
            _viBullet->fire = false;
            continue;
        }
        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
    }
}

void Minimi::fire(float* x, float* y)
{
    _rocketX = x;
    _rocketY = y;
    _x = *_rocketX - 50;
    _y = *_rocketY;

    if (MISSILE_COUNT + _ticker < GetTickCount64())
    {
        _ticker = GetTickCount64();
        for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
        {
            if (_viBullet->fire) continue;
            _viBullet->fire = true;
            _viBullet->x = _viBullet->fireX = _x;
            _viBullet->y = _viBullet->fireY = _y;
            _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

            cout << " missile 발사" << endl;
            break;
        }
    }
}
#pragma endregion

// ===<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>===
//   RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  
// >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER  >>======<<  RAISER
#pragma region 레이저
HRESULT Raiser::init(int bulletMax, float range)
{
    _range = range;
    _cor = 28;
    _ticker = 90 + (bulletMax * 10);
    _armaryCode = RAISER;

        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.fire = false;
        bullet.speed = 5.0f;
        bullet.type = RAISER;
        bullet.immo = true;

        _vBullet.push_back(bullet);
    cout << "무기 전환 : 레이저";

    return S_OK;
}

void Raiser::release(void)
{
    _vBullet.clear();
    vector<tagBullet> tmp;
    tmp.swap(_vBullet);
}

void Raiser::update(void)
{
    move();
}

void Raiser::render(void)
{
    draw();
}

void Raiser::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire)
        {
            DrawRectMake(getMemDC(), _viBullet->rc);
            //Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
            cout << _viBullet->rc.left << ", " << _viBullet->rc.top << endl;
        }
        else continue;
    }
}

void Raiser::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!(_viBullet->fire)) continue;
        else {
            _viBullet->count++;
            int raiserW = _viBullet->rc.right - _viBullet->rc.left;  

            if (_viBullet->count < _ticker)
            {
                if (raiserW <= _range / 10)
                {
                    _viBullet->rc = RectMakeCenter(*_rocketX, *_rocketY- _cor - _range / 2, raiserW + 2, _range);
                }
                else 
                    _viBullet->rc = RectMakeCenter(*_rocketX, *_rocketY- _cor - _range / 2, raiserW, _range);
            }
            else
            {
                if (raiserW < 1)
                {
                    _viBullet->fire = false;
                    continue;
                }
                else
                {
                    _viBullet->rc = RectMakeCenter(*_rocketX, *_rocketY- _cor - _range / 2, raiserW - 2, _range);
                }
            }//end else count
        }//end else fire
    }
}

void Raiser::fire(float* x, float* y)
{
    _rocketX = x;
    _rocketY = y;
    _viBullet = _vBullet.begin();

    if (!_viBullet->fire)
    {
        _viBullet->fire = true;
        _viBullet->count = 0;
        _viBullet->x = _viBullet->fireX = *x;
        _viBullet->y = _viBullet->fireY = *y;
        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y - _cor - _range / 2, 1, _range);

        cout << " raiser 발사" << endl;
    }
}
#pragma endregion

// >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE
//   G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  
// ===<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>======<<  G_MISSILE  >>===
HRESULT G_Missile::init(int bulletMax, float range)
{
    _range = range;
    _ticker = 0;
    _armaryCode = G_MISSILE;

    for (int i = 0; i < bulletMax; i++)
    {
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new GImage;
        bullet.img->init("Resources/Images/Object/Missile.bmp", .0f, .0f,
            416, 64, 13, 1,
            true, RGB(255, 0, 255));

        bullet.fire = false;
        bullet.speed = 5.0f;

        _vBullet.push_back(bullet);
    }
    cout << "무기 전환 : 유도탄";

    return S_OK;
}

void G_Missile::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void G_Missile::update(void)
{
    cout << "유업" << endl;
    move();
}

void G_Missile::render(void)
{
    cout << "render" << endl;
    draw();
}

void G_Missile::setTarget(float* tx, float* ty)
{
    _targetPx = tx;
    _targetPy = ty;
}

void G_Missile::fire(float* x, float* y)
{
    if (MISSILE_COUNT + _ticker < GetTickCount64())
    {
        _ticker = GetTickCount64();
        for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
        {
            if (_viBullet->fire) continue;
            _viBullet->fire = true;
            _viBullet->count = 0;
            _viBullet->x = _viBullet->fireX = *x;
            _viBullet->y = _viBullet->fireY = *y;
            _viBullet->tx = _targetPx;
            _viBullet->ty = _targetPy;
            _viBullet->angle = getAngle(_viBullet->x, _viBullet->y, *_viBullet->tx, *_viBullet->ty);
            _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

            cout << " missile 발사" << endl;
            break;
        }
    }
}

void G_Missile::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        cout << "유도탄그리기" << endl;
        if (_viBullet->fire)
        {
        cout << "유도탄 탄환그리기" << endl;
            _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
            if (_viBullet->img->getFrameX() == _viBullet->img->getMaxFrameX())
                _viBullet->img->setFrameX(0);
            else _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
        }
    }
}

void G_Missile::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        cout << 0 << endl;
        if (!_viBullet->fire) continue;
        cout << 1 << endl;
        _viBullet->count += 1;
        cout << 2 << endl;
        if (_viBullet->count * _viBullet->speed > _range)
        {
            _viBullet->fire = false;
            continue;
        }
        cout << 3 << endl;
        _viBullet->angle = getAngle(_viBullet->x, _viBullet->y, *_viBullet->tx, *_viBullet->ty);
        _viBullet->x = (_viBullet->speed)*cos(_viBullet->angle) + _viBullet->x;
        _viBullet->y = (_viBullet->speed)*sin(_viBullet->angle) + _viBullet->y;
        cout << 4 << endl;
        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());    }
    cout << _viBullet->rc.left << ", " << _viBullet->rc.top << endl;
        cout << 5 << endl;
    }

HRESULT BlackHole::init(int bulletMax, float range)
{
    _range = range;
    _ticker = 0;
    _armaryCode = BLACK_HOLE;
    _isFire = false;
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new GImage;
        bullet.img->init("Resources/Images/Object/BlackHole.bmp", .0f, .0f,
            1059, 135, 8, 1,
            true, RGB(0, 0, 0));

        bullet.fire = false;
        bullet.speed = 5.0f;

        _vBullet.push_back(bullet);
    cout << "무기 전환 : 블랙홀";

    return S_OK;
}

void BlackHole::release(void)
{
    SAFE_DELETE(_vBullet.front().img)
}

void BlackHole::update(void)
{
    if(_vBullet.front().fire)
    {
        if (_isFire)
            move();
        else
            push();
    }

    _isFire = false;
}

void BlackHole::render(void)
{
    draw();
}

void BlackHole::setTarget(EnemyManager* a)
{
    _enemyGrup.push_back(a);
}

void BlackHole::fire(float* x, float* y)
{   
    cout << " 블랙홀 발사";
        _vBullet.back().fire = true;
        _vBullet.back().x = _vBullet.back().fireX = *x;
        _vBullet.back().y = _vBullet.back().fireY = *y + WINSIZE_Y / 2;
        _vBullet.back().rc = RectMakeCenter(_vBullet.back().x, _vBullet.back().y, _vBullet.back().img->getFrameWidth(), _vBullet.back().img->getFrameHeight());
        cout << "rc left:" << _vBullet.back().rc.left << "  rc top:" << _vBullet.back().rc.top << endl;
        _isFire = true;
        cout << "블랙홀 isFire true" << endl;
}

void BlackHole::draw(void)
{
        if (_vBullet.back().fire)
        {
    cout << "블랙홀 :: draw ";
            _vBullet.back().img->frameRender(getMemDC(), _vBullet.back().rc.left, _vBullet.back().rc.top);
            if (_vBullet.back().img->getFrameX() == _vBullet.back().img->getMaxFrameX())
                _vBullet.back().img->setFrameX(0);
            else _vBullet.back().img->setFrameX(_vBullet.back().img->getFrameX() + 1);
        }
        cout << "완료" << endl;
}

void BlackHole::move(void)
{
    cout << "블랙홀 move";
    //if(_vBullet.back().count * _vBullet.back().speed < _range)
    //    _vBullet.back().count++;
    //for (int i = 0; i < _enemyGrup.back()->getMinionNumber(); i++)
    //{
    //    float angle = getAngle(*(_enemyGrup.back()->getMinionPx(i)), *(_enemyGrup.back()->getMinionPy(i)), _vBullet.back().x, _vBullet.back().y);
    //    cout << endl << angle;
    //    float distance = getDistance(*(_enemyGrup.back()->getMinionPx(i)), *(_enemyGrup.back()->getMinionPy(i)), _vBullet.back().x, _vBullet.back().y);
    //    cout << endl << distance;
    //    if(distance> _vBullet.back().speed)
    //    {
    //        *(_enemyGrup.back()->getMinionPx(i)) = _vBullet.back().x + cos(angle) * (distance -_vBullet.back().speed);
    //        *(_enemyGrup.back()->getMinionPy(i)) = _vBullet.back().y + sin(angle) * (distance -_vBullet.back().speed);
    //    }
    //}
    cout << " 완료" << endl;
}

void BlackHole::push(void)
{
    //for (int i = 0; i < _enemyGrup.back()->getMinionNumber(); i++)
    //{
    //    float angle = getAngle(*(_enemyGrup.back()->getMinionPx(i)), *(_enemyGrup.back()->getMinionPy(i)), _vBullet.back().x, _vBullet.back().y);
    //    float distance = getDistance(*(_enemyGrup.back()->getMinionPx(i)), *(_enemyGrup.back()->getMinionPy(i)), _vBullet.back().x, _vBullet.back().y);
    //        *(_enemyGrup.back()->getMinionPx(i)) = _vBullet.back().x + cos(angle) * (distance + _vBullet.back().speed);
    //        *(_enemyGrup.back()->getMinionPy(i)) = _vBullet.back().y + sin(angle) * (distance + _vBullet.back().speed);
    //}

    //if (--_vBullet.back().count <= 0)
    //    _vBullet.back().fire = false;
}







HRESULT Beam::init(int bulletMax, float range)
{
    _range = range;
    _bulletMax = bulletMax;
    return S_OK;
}

void Beam::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}


void Beam::update(void)
{
    move();
}

void Beam::render(void)
{
    draw();
}

void Beam::fire(float x, float y)
{
    if (_bulletMax <= _vBullet.size()) return;

    tagBullet bullet;
    ZeroMemory(&bullet, sizeof(tagBullet));
    bullet.img = new GImage;
    bullet.img->init("Resources/Images/Object/Beam.bmp", 0.0f, 0.0f, 412, 801, 4, 1, true, RGB(255, 0, 255)); // 바꾸기
    bullet.speed = 0.1f;
    bullet.x = bullet.fireX = x;
    bullet.y = bullet.fireY = y;
    bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
    bullet.count = 0;
    // 정적으로 주고있음
    _vBullet.push_back(bullet);

}

void Beam::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
        _viBullet->count++;

        _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

        if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
        {
            _viBullet->img->setFrameX(0);
        }
        _viBullet->count = 0;

    }
}

void Beam::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
    {
        _viBullet->x += _viBullet->angle;
        _viBullet->y -= _viBullet->speed;
        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
        {

            SAFE_DELETE(_viBullet->img);
            _viBullet = _vBullet.erase(_viBullet);

        }
        else ++_viBullet;

    }
}

void Beam::removeBullet(int arrNum)
{
    SAFE_DELETE(_vBullet[arrNum].img);

    _vBullet.erase(_vBullet.begin() + arrNum);
}
