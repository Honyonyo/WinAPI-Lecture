#include "stdafx.h"
#include "MainGame1125_timer.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_clockRadius = WINSIZE_Y / 2 - 100;
	_clockCenterPt = { WINSIZE_X / 2, WINSIZE_Y / 2 };
	GetLocalTime(&_st);

	/*
	* 	POINT endpt;
	* 	int length;
	* 	int time;
	* 	long double radian;
	*/
	_hour.setRadian(hourDgre(_st));
	_hour.setEndPt(_clockCenterPt);
	_hour.length = _clockRadius / 3;

	_min.setRadian(minDgre(_st));
	_min.setEndPt(_clockCenterPt);
	_min.length = _clockRadius / 2;

	_sec.setRadian(secDgre(_st));
	_sec.setEndPt(_clockCenterPt);
	_sec.length = _clockRadius *2 /3;

	_switch = false;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

}

void MainGame::update(void)
{
	GameNode::update();
	GetLocalTime(&_st);
	_hour.setRadian(hourDgre(_st));
	_hour.setEndPt(_clockCenterPt);
	_min.setRadian(minDgre(_st));
	_min.setEndPt(_clockCenterPt);
	_sec.setRadian(secDgre(_st));
	_sec.setEndPt(_clockCenterPt);

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) { _switch = !_switch; }

}

void MainGame::render(HDC hdc)
{
	GameNode::render(hdc);

	//백버퍼 얻어온다.
	HDC memDC = this->getBackBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// 
	//검은색 빈 비트맵
	// PatBit(): 사각형 영역에 주어진 브러시로 채우는 함수
	char strTime[128];
	sprintf_s(strTime, "%2d월 %2d일  %2d시 %2d분 %2d초", _st.wMonth, _st.wDay, _st.wHour, _st.wMinute, _st.wSecond);
	TextOut(memDC, WINSIZE_X / 2 - 100, 50, strTime, strlen(strTime));


	HPEN starPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	_currentTimerPen = (HPEN)SelectObject(memDC, starPen);
	EllipseMakeCenter(memDC, _clockCenterPt.x, _clockCenterPt.y, _clockRadius, _clockRadius);
	DeleteObject(starPen);
	printTriangle(memDC);

		SetStretchBltMode(memDC, HALFTONE);
	StretchBlt(memDC, 0,0,256, 160, memDC, 1280, 800, -1280, -800, WHITENESS);


	//LineMake(memDC, _clockCenterPt, _hour.endpt);
	//LineMake(memDC, _clockCenterPt, _min.endpt);
	//LineMake(memDC, _clockCenterPt, _sec.endpt);


	this->getBackBuffer()->render(hdc);
}


