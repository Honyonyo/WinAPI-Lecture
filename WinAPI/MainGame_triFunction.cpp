#include "stdafx.h"
#include "MainGame_triFunction.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	_radian = 3.141592653f;
	_degree = 180;

	for (int i = 0; i < 5; i++)
	{
		//90�� : �ʱⰢ��. 72 : �� ������ ������ ��. 200 : �������� �� �������� �Ÿ�. WINSIZE_ : �߽���x, y  
		_star[i].x = cosf(((i * 72) - 90) * PI / 180.0f) * 200 + WINSIZE_X / 2;
		_star[i].y = sinf(((i * 72) - 90) * PI / 180.0f) * 200 + WINSIZE_Y / 2;
	}
	GetLocalTime(&_st);

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

}

void MainGame::render(HDC hdc)
{
	GameNode::render(hdc);

	//����� ���´�.
	HDC memDC = this->getBackBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	// 
	//������ �� ��Ʈ��
	// PatBit(): �簢�� ������ �־��� �귯�÷� ä��� �Լ�
	char strRadian[128];
	char strDgree[128];
	char strTime[128];
	sprintf_s(strRadian, "%.2f���� ���� %.2f ��׸� ���� ����.", _radian, _radian * (180.0f / M_PI));
	sprintf_s(strDgree, "%.2f��׸� ���� %.2f ���� ���� ����.", _degree, _degree / (180.0f / M_PI));
	sprintf_s(strTime, "%2d�� %2d��  %2d�� %2d�� %2d��", _st.wMonth, _st.wDay, _st.wHour, _st.wMinute, _st.wSecond);


	TextOut(memDC, 5, WINSIZE_Y / 2 - 100, strRadian, strlen(strRadian));
	TextOut(memDC, 5, WINSIZE_Y / 2 - 80, strDgree, strlen(strDgree));
	TextOut(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2 - 300, strTime, strlen(strTime));

	SetPixel(memDC, _star[0].x, _star[0].y, RGB(255, 0, 0));

	for (int i = 0; i < 5; i++)
	{
		EllipseMakeCenter(memDC, _star[i].x, _star[i].y, 10, 10);
	}

	HPEN starPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	_currentStarPen = (HPEN)SelectObject(memDC, starPen);
	for (int i = 0; i < 5; i++)
	{
		LineMake(memDC, _star[i % 5].x, _star[i % 5].y, _star[(i + 1) % 5].x, _star[(i + 1) % 5].y);
	}
	for (int i = 0; i < 5; i++)
	{
		LineMake(memDC, _star[i % 5].x, _star[i % 5].y, _star[(i + 2) % 5].x, _star[(i + 2) % 5].y);
	}
	DeleteObject(starPen);

	this->getBackBuffer()->render(hdc);
}


