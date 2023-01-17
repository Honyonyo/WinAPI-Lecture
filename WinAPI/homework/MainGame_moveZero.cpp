#include "Stdafx.h"
#include "MainGame_moveZero.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_bgImage = new GImage;
	_bgImage->init("Resources/Images/BackGround/spiritTreeCutsceneBackgroundC-sharedassets4.assets-4.bmp", 2048, 1024);

	_zero = new GImage;
	_zero->init("Resources/Images/Object/zero.bmp", WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200, 1048, 576, 8, 8, true, RGB(250, 0, 250));

	_isLeft = false;
	_count = _indexX = _indexY = 0;


	_miniBgImage = new GImage;
	_miniBgImage->init("Resources/Images/BackGround/spiritTreeCutsceneBackgroundC-sharedassets4.assets-4.bmp", 2048 / MAGNIFICATION, 1024 / MAGNIFICATION);

	_rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, PLAYERSIZE, PLAYERSIZE);
	_miniMap = { 0,0,MINIMAP_WIDTH, MINIMAP_HEIGHT };
	_minimi = { _rc.left / MAGNIFICATION, _rc.top / MAGNIFICATION, _rc.right / MAGNIFICATION, _rc.bottom / MAGNIFICATION };
	_alphaA = 150;
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_zero);
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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_isLeft = true;
		_zero->setX(_zero->getX() - 8.0f);
		if (_rc.left > 0) {
			_rc.left -= MOVEPOINT;
			_rc.right -= MOVEPOINT;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_isLeft = false;
		_zero->setX(_zero->getX() + 8.0f);

		if (_rc.right < WINSIZE_X) {
			_rc.left += MOVEPOINT;
			_rc.right += MOVEPOINT;
		}
	}

	if (_isLeft) {
		_count++;
		(_indexY < 4) ? (_indexY += 4) : NULL;
		if (_count % 3 == 0) {
			if (--_indexX < 0) {
				_indexX = 7;
				(++_indexY > 7) ? (_indexY = 4) : NULL;
			}
		}
		_zero->setFrameX(_indexX);
		_zero->setFrameY(_indexY);

	}
	else {
		_count++;
		(_indexY > 3) ? (_indexY -= 4) : NULL;
		if (_count % 3 == 0) {
			switch (_indexX) {
			case 7:
				_indexX = 0;
				(++_indexY > 3) ? (_indexY = 0) : NULL;
				break;
			default: _indexX++;
			}
			_zero->setFrameY(_indexY);
			_zero->setFrameX(_indexX);

			//if (_indexX++ > 8) {
			//	_indexX = 0;
			//	(++_indexY > 3) ? (_indexY = 0) : NULL;
			//}
		}
	}

	_minimi = { _rc.left / MAGNIFICATION, _rc.top / MAGNIFICATION, _rc.right / MAGNIFICATION, _rc.bottom / MAGNIFICATION };
}

void MainGame::render(HDC hdc)
{

	//백버퍼 얻어온다.
	HDC memDC = this->getBackBuffer()->getMemDC();
	//검은색 빈 비트맵
	// PatBit(): 사각형 영역에 주어진 브러시로 채우는 함수
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_bgImage->render(memDC, 0, 0);

	_zero->frameRender(memDC, _zero->getX(), _zero->getY());

	_miniBgImage->alphaRender(memDC, 0, 0, 0, 0, MINIMAP_WIDTH, MINIMAP_HEIGHT, _alphaA);

	char index[30];
	wsprintf(index, "sprite X:%d, Y:%d", _indexX, _indexY);
	TextOut(memDC, WINSIZE_X - 100, WINSIZE_Y - 20, index, strlen(index));

	DrawRectMake(memDC, _minimi);

	this->getBackBuffer()->render(hdc, 0, 0);
}