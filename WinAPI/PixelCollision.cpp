#include "stdafx.h"
#include "PixelCollision.h"

HRESULT PixelCollision::init(void)
{
	GameNode::init(true);
	_pixelTank = IMAGEMANAGER->addImage("ÇÈ¼¿ÅÊÅ©", "Resources/Images/Object/Thank.bmp",70,60, true, RGB(255,0,255));
	_x = WINSIZE_X / 2 + 250;
	_y = WINSIZE_Y / 2 + 100;
	_rc = RectMakeCenter(_x, _y, _pixelTank->getWidth(), _pixelTank->getHeight());
	//yÃà Å½Áö
	_probeY = _y + _pixelTank->getHeight() / 2;

	return S_OK;
}

void PixelCollision::release(void)
{
	SAFE_DELETE(_pixelTank);
}

void PixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))_x -= 2.0f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))_x += 2.0f;

	_probeY = _y + _pixelTank->getHeight() / 2;
	for (int i = _probeY - 30; i < _probeY + 30; i++) {
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("¿ïÅüºÒÅü")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (!(r == 255 && g == 0 && b == 255)) {
			_y = i - _pixelTank->getHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _pixelTank->getWidth(), _pixelTank->getHeight());
	//printf("_rc.x = %d, _rc.y = %d\n", _rc.left, _rc.top);
}

void PixelCollision::render(void)
{
	//std::cout << "ÇÈ¼¿Ãæµ¹ ·»´õ ½ÃÀÛ" << std::endl;
	_pixelTank->render(getMemDC(), _rc.left, _rc.top);
	//std::cout << "ÇÈ¼¿Ãæµ¹ ÅÊÅ© ·»´õ ¿Ï·á" << std::endl;
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		Rectangle(getMemDC(), _x, _probeY, _x + 10, _probeY + 10);
	}
}
