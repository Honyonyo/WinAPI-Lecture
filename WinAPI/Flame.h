#pragma once
#include "GameNode.h"

#define Tcolor	RGB(255,0,255)
#define FLAME_COUNT 70.0f

class Flame : public GameNode
{
private:
	GImage* _image;
	RECT _rc;

	float* _x;
	float* _y;
	float _flameTick;

public:
	HRESULT init(const char* imageName, float* x, float* y) 
	{//������ ��뿡 �ͼ�������
			_x = x;
			_y = y;
			_image = IMAGEMANAGER->addFrameImage("�ν���", "Resources/Images/Object/Flame.bmp", 432, 297, 9, 1, true, RGB(255,0,255));
			_rc = RectMakeCenter((int)*_x, (int)*_y, _image->getFrameWidth(), _image->getFrameHeight());
			_flameTick = 7.0f;
			cout << "	�÷��� �غ� �Ϸ�" << endl;
			return S_OK;
	};
	void update(void) {
		if (FLAME_COUNT + _flameTick <= GetTickCount64())
		{
			_flameTick = GetTickCount64();
			_image->setFrameX(_image->getFrameX() + 1);

			if (_image->getFrameX() >= _image->getMaxFrameX()) 
			{
				_image->setFrameX(0);
			}
		}
		_rc = RectMakeCenter((int)*_x, (int)*_y+178, _image->getFrameWidth(), _image->getFrameHeight());
		//printf("�÷����� ���� _x %f, _y %f\n", *_x, *_y);
		//printf("�÷��� _rc left %d, _rc top %d\n", _rc.left, _rc.top);
	}
	void release(void) {
		SAFE_DELETE(_image);
	};
	void render(void) {
		IMAGEMANAGER->frameRender("�ν���", getMemDC(), _rc.left, _rc.top);
	}
};

