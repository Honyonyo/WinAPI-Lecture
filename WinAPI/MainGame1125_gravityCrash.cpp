#include "stdafx.h"
#include "MainGame1125_gravityCrash.h"
HRESULT MainGame::init(void)
{
	GameNode::init(true);

	IMAGEMANAGER->addImage("데드스페이스", "Resources/Images/Background/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("빙산의일각", "Resources/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	_centerCannon = { WINSIZE_X / 2, WINSIZE_Y };
	_gravity = GRAVITY;
	_cannonsize = 30;
	_radianCannon = -PI / 2;
	_endCannon = { (long)(2 * _cannonsize * cos(_radianCannon)) + _centerCannon.x,
				(long)(2 * _cannonsize * sin(_radianCannon)) + _centerCannon.y };
	_movepoint = CANNONRADIAN;
	_automaticCannonSwitch = false;
	_automaticCannonDirectionLeft = true;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

}

void MainGame::update(void)
{
	GameNode::update();

	_counter++;

	if (KEYMANAGER->isOnceKeyDown('S')) {
		if (_gravity) _gravity = 0;
		else _gravity = GRAVITY;
		//system("pause");
	}

	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _counter >= 20) {
		shootCannon();
		_counter = 0;
	}

	if (!_automaticCannonSwitch) {
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			moveCannonLeft();
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			moveCannonRight();
		}
	}
	else {
		_automaticCannonDirectionLeft ? moveCannonLeft() : moveCannonRight();
	}

	if (!_lBullet.empty())
	{
		for (_iter = _lBullet.begin(); _iter != _lBullet.end(); _iter++) {
			_iter->moving(_gravity);
		}
		if (GetTickCount64() - _lBullet.front().gentime >= BULLET_DELETETIME) {
			_lBullet.pop_front();
		}
	}
	crashBullet();
}

void MainGame::render(void)
{
	GameNode::render();

	//백버퍼 얻어온다.
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	IMAGEMANAGER->render("빙산의일각", getMemDC(), 0, 0);


	if (!_lBullet.empty())
	{
		char strListF[128];
		sprintf_s(strListF, "총알 중심점 [%d, %d], 발사각 %f, 태어난시간 %f",
			_lBullet.front().center.x, _lBullet.front().center.y, _lBullet.front().radian, _lBullet.front().gentime);
		TextOut(getMemDC(), 0, 18, strListF, strlen(strListF));

		for (_iter = _lBullet.begin(); _iter != _lBullet.end(); _iter++) {
			_iter->drawBullet(getMemDC());
		}
	}
	drawCannon(getMemDC());

	char strPt[128];
	sprintf_s(strPt, "포 [%d, %d] %f라디안, 발사체 수 %d",
		_centerCannon.x, _centerCannon.y, _radianCannon, (int)_lBullet.size());
	TextOut(getMemDC(), 0, 0, strPt, strlen(strPt));

	this->getBackBuffer()->render(getHDC());
}


void MainGame::setCannonDirection()
{
	_endCannon = { (long)(2 * _cannonsize * (cos(_radianCannon)) + _centerCannon.x),
				(long)(2 * _cannonsize * (sin(_radianCannon)) + _centerCannon.y) };
}

void MainGame::moveCannonLeft()
{
	_automaticCannonDirectionLeft = true;
	_radianCannon -= _movepoint;
	if (_radianCannon <= CANNONRADIAN_MIN)
	{
		_radianCannon = CANNONRADIAN_MIN;
		_automaticCannonDirectionLeft = false;
	}

	setCannonDirection();
}

void MainGame::moveCannonRight()
{
	_automaticCannonDirectionLeft = false;
	_radianCannon += _movepoint;
	if (_radianCannon >= CANNONRADIAN_MAX) {
		_radianCannon = CANNONRADIAN_MAX;
		_automaticCannonDirectionLeft = true;
	}

	setCannonDirection();
}

void MainGame::shootCannon()
{
	BULLET bullet;	//벡터에 넣을 구조체 만들기
	bullet.gentime = GetTickCount64();
	bullet.shoot(_endCannon, _radianCannon);
	this->_lBullet.push_back(bullet);
}

void MainGame::drawCannon(HDC hdc)
{
	HPEN newPen = CreatePen(PS_SOLID, 5, RGB(100, 100, 10));
	HPEN currentPen = (HPEN)SelectObject(hdc, newPen);
	EllipseMakeCenter(hdc, _centerCannon, _cannonsize, _cannonsize);
	LineMake(hdc, _centerCannon, _endCannon);

	SelectObject(hdc, currentPen);
	DeleteObject(newPen);
	DeleteObject(currentPen);
}

void MainGame::crashBullet()
{
	if (_lBullet.size()) {
		for (_iter = _lBullet.begin(); _iter != _lBullet.end(); _iter++) {
			for (list<BULLET>::iterator _B = _lBullet.begin(); _B != _lBullet.end(); _B++) {
				if (_iter == _B) continue;

				float dY = _iter->center.y - _B->center.y >= 0 ? _iter->center.y - _B->center.y : -(_iter->center.y - _B->center.y);
				float dX = _iter->center.x - _B->center.x >= 0 ? _iter->center.x - _B->center.x : -(_iter->center.x - _B->center.x);

				float centerSlop = atan((float)(_iter->center.y - _B->center.y) / (float)(_iter->center.x - _B->center.x));
				float diminishX = (_iter->radius + _B->radius) * cos(centerSlop) - (dX);
				/*	if (diminishX < 0) {
						_iter->center.x += diminishX * cos(centerSlop) / 2;
						_iter->center.y += (((_iter->radius + _B->radius) - (dY)) * sin(centerSlop)) / 2;

						_iter->radian = PI - centerSlop  - _iter->radian;
					}
					else*/ if (diminishX == 0)
	_iter->radian = 3 * PI / 2 - centerSlop - _iter->radian;

			}//for iterB end

			if (_iter->center.x - _iter->radius <= 0) {
				_iter->center.x = _iter->radius;
				_iter->radian = PI - _iter->radian;
			}
			if (_iter->center.x + _iter->radius >= WINSIZE_X)
			{
				_iter->center.x = WINSIZE_X - _iter->radius;
				_iter->radian = PI - _iter->radian;
			}
			if (_iter->center.y - _iter->radius <= 0) {
				_iter->center.y = _iter->radius;
				_iter->radian = -_iter->radian;
			}
			if (_iter->center.y + _iter->radius >= WINSIZE_Y)
			{
				_iter->center.y = WINSIZE_Y - _iter->radius;
				_iter->radian = -_iter->radian;
			}
		}//for iter end


	}
}//crashBullet end