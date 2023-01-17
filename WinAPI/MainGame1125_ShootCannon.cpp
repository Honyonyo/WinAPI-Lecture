#include "stdafx.h"
#include "MainGame1125_ShootCannon.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	_centerCannon = { WINSIZE_X / 2, WINSIZE_Y };
	_cannonsize = 30;
	_endCannon = { (long)(2 * _cannonsize * cos(CANNONRADIAN_MIN)) + _centerCannon.x,
				(long)(2 * _cannonsize * sin(CANNONRADIAN_MIN)) + _centerCannon.y };
	_movepoint = CANNONRADIAN;
	_radianCannon = CANNONRADIAN_MIN;
	_automaticCannonSwitch = false;
	_automaticCannonDirectionLeft = true;
	_allDirectionCannon = false;
	_counter = 0;
	_vBullet.clear();

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

}

void MainGame::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isOnceKeyDown('S')) {
		_automaticCannonSwitch = !_automaticCannonSwitch;
		_movepoint = _automaticCannonSwitch ? CANNONRADIAN_AD : CANNONRADIAN;
	}

	if (KEYMANAGER->isOnceKeyDown('A')) {
		_allDirectionCannon = !_allDirectionCannon;
		_movepoint = CANNONRADIAN_AD;
	}

	if (_allDirectionCannon)
	{
		allDirectionCannonMove();
		allDirectionCannonShooing();

		if (!_vBullet.empty())
		{
			for (_iter = _vBullet.begin(); _iter != _vBullet.end(); _iter++) {
				_iter->moving();
			}
			if (GetTickCount64() - _vBullet.front().gentime >= BULLET_DELETETIME) {
				_vBullet.erase(_vBullet.begin());
			}
		}

	}
	else
	{
		if (KEYMANAGER->isStayKeyDown(VK_SPACE)) {
			shootCannon();
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

		if (!_vBullet.empty())
		{
			for (_iter = _vBullet.begin(); _iter != _vBullet.end(); _iter++) {
				_iter->moving();
			}
			if (GetTickCount64() - _vBullet.front().gentime >= BULLET_DELETETIME) {
				_vBullet.erase(_vBullet.begin());
			}
		}

	}
}

void MainGame::render(HDC hdc)
{
	GameNode::render();

	//백버퍼 얻어온다.
	HDC memDC = this->getBackBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	if (!_vBullet.empty())
	{
		char strListF[128];
		sprintf_s(strListF, "총알 중심점 [%d, %d], 발사각 %f, 태어난시간 %f",
			_vBullet.front().center.x, _vBullet.front().center.y, _vBullet.front().radian, _vBullet.front().gentime);
		TextOut(memDC, 0, 18, strListF, strlen(strListF));

		for (_iter = _vBullet.begin(); _iter != _vBullet.end(); _iter++) {
			_iter->drawBullet(memDC);
		}
	}

	drawCannon(memDC);

	char strPt[128];
	sprintf_s(strPt, "포 [%d, %d] %f라디안, 발사체 수 %d",
		_centerCannon.x, _centerCannon.y, _radianCannon, (int)_vBullet.size());
	TextOut(memDC, 0, 0, strPt, strlen(strPt));

	this->getBackBuffer()->render(hdc);
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
	if (_allDirectionCannon)
	{
		bullet.shoot(_centerCannon, _radianCannon, _allDirectionCannon, _automaticCannonDirectionLeft);
	}
	else
	{
		bullet.shoot(_endCannon, _radianCannon, _allDirectionCannon, _automaticCannonDirectionLeft);
	}
	_vBullet.push_back(bullet);
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

void MainGame::allDirectionCannonMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		(_centerCannon.x -= CANNONMOVEPOINT) <= 0
			? _centerCannon.x -= CANNONMOVEPOINT : NULL;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		(_centerCannon.x += CANNONMOVEPOINT) <= WINSIZE_X
			? _centerCannon.x += CANNONMOVEPOINT : NULL;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		(_centerCannon.y -= CANNONMOVEPOINT) <= 0
			? _centerCannon.y -= CANNONMOVEPOINT : NULL;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		(_centerCannon.y += CANNONMOVEPOINT) >= WINSIZE_Y
			? _centerCannon.y += CANNONMOVEPOINT : NULL;
	}
	setCannonDirection();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		_automaticCannonDirectionLeft = !_automaticCannonDirectionLeft;
	}
}

void MainGame::allDirectionCannonShooing()
{
	_automaticCannonDirectionLeft
		? _radianCannon -= CANNONRADIAN_AD : _radianCannon += CANNONRADIAN_AD;
	setCannonDirection();

	_counter++;
	_counter % 8 == 0 ? shootCannon() : NULL;
}