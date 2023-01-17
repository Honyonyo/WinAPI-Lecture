#include "stdafx.h"
#include "MainGame_jump.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	_floor.rc = { 0,WINSIZE_Y - 20,WINSIZE_X,WINSIZE_Y };
	_wall.rc = { 500,_floor.rc.top - (PLAYERSIZE * 2),1000,_floor.rc.top };
	_rcPlayer.rc = RectMakeCenter(WINSIZE_X / 2, _floor.rc.top - PLAYERSIZE / 2, PLAYERSIZE, PLAYERSIZE);

	_rcPlayer.action = STANDING;
	_rcPlayer.leftFoward = true;

	vPlatform.push_back(_floor);
	vPlatform.push_back(_wall);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	//SAFE_DELETE(_routImageBackground);
	//SAFE_DELETE(_routImageObject);
}

void MainGame::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q')) {
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK) {
			PostQuitMessage(0);
		}
	}

	playerMove();
}

void MainGame::render(HDC hdc)
{

	//백버퍼 얻어온다.
	HDC memDC = this->getBackBuffer()->getMemDC();
	//검은색 빈 비트맵
	// PatBit(): 사각형 영역에 주어진 브러시로 채우는 함수
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	for (int i = 0; i < vPlatform.size(); i++) {
		DrawRectMake(memDC, vPlatform[i].rc);
	}

	DrawRectMake(memDC, _rcPlayer.rc);

	HPEN myPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hPrevPen = (HPEN)SelectObject(memDC, myPen);
	DrawRectMake(memDC, _rcPlayer.shadow);
	DeleteObject(myPen);
	SelectObject(memDC, hPrevPen);
	DeleteObject(hPrevPen);


	printAction(memDC);
	this->getBackBuffer()->render(hdc, 0, 0);
}




void MainGame::printAction(HDC hdc)
{
	char text[50];
	char action[20];
	switch (_rcPlayer.action) {
	case STANDING:
		strcpy_s(action, strlen("STANDING") + 1,
			"STANDING");
		break;
	case 	WALK:
		strcpy_s(action, strlen("WALK") + 1,
			"WALK");
		break;
	case 	JUMP:
		strcpy_s(action, strlen("JUMP") + 1,
			"JUMP");
		break;
	case 	MOVEJUMP:
		strcpy_s(action, strlen("MOVEJUMP") + 1,
			"MOVEJUMP");
		break;

	case 	HANGING_WALL:
		strcpy_s(action, strlen("HANGING_WALL") + 1,
			"HANGING_WALL");
		break;
	case 	SLIDEDOWN_WALL:
		strcpy_s(action, strlen("SLIDEDOWN_WALL") + 1,
			"SLIDEDOWN_WALL");
		break;

	}
	if (_rcPlayer.jump)	wsprintf(text, "현재동작 :%s %s", action, "JUMP");
	else wsprintf(text, "현재동작 :%s", action);
	TextOut(hdc, 5, 5, text, strlen(text));

	wsprintf(text, "플랫폼개수 :%d", (int)vPlatform.size());
	TextOut(hdc, 5, 25, text, strlen(text));

	wsprintf(text, "벡터개수 :%d", (int)tmpvPlatform.size());
	TextOut(hdc, 5, 45, text, strlen(text));

}

void MainGame::playerMove()
{
	_rcPlayer.action = STANDING;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_isLeft = true;
		_rcPlayer.action = WALK;
		if (_rcPlayer.rc.left > 0) {
			_rcPlayer.rc.left -= MOVEPOINT;
			_rcPlayer.rc.right -= MOVEPOINT;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_isLeft = false;
		_rcPlayer.action = WALK;
		if (_rcPlayer.rc.right < WINSIZE_X) {
			_rcPlayer.rc.left += MOVEPOINT;
			_rcPlayer.rc.right += MOVEPOINT;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && (_rcPlayer.action != JUMP)) {
		jumpstart();
	}

	if (_rcPlayer.jump == JUMP) {
		jump();
	}

	setPlyrShadow(_rcPlayer, vPlatform);

}
void MainGame::jumpstart()
{
	_rcPlayer.jump = JUMP;
	_rcPlayer.speed = 9.5f;
	_rcPlayer.weight = 1.0f;
	_rcPlayer.friction = 0.3f;
}

void MainGame::jump()
{
	_rcPlayer.rc.bottom -= _rcPlayer.speed * _rcPlayer.weight - _rcPlayer.friction;
	_rcPlayer.rc.top -= _rcPlayer.speed * _rcPlayer.weight - _rcPlayer.friction;
	_rcPlayer.speed -= _rcPlayer.friction;

	if (_rcPlayer.rc.bottom >= _rcPlayer.shadow.top) {
		_rcPlayer.jump = false;
		_rcPlayer.rc.bottom = _rcPlayer.shadow.top;
		_rcPlayer.rc.top = _rcPlayer.shadow.top - PLAYERSIZE;
	}
}
