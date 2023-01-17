#include "stdafx.h"
#include "Charactor.h"

HRESULT Charactor::init(void)
{
	_myImage.init("homework/Resourse/Image/Object/yellowrobot.bmp",840,600,6,3,true, RGB(255,0,255));
	cout << " _scarecrow->init()" << endl;
	_imgW = _myImage.getFrameX();
	_imgH = _myImage.getFrameY();
	_counter = 0;
	_indexX = _indexY = 0;
	_status = STANDING;
	_standImageCounter = (RND->getfloat(3)*10);

	_center = { WINSIZE_X - 3 / 2 * _imgW, WINSIZE_Y - 3 / 2 * _imgH };
	_life = 100;
	setImageRC();
	setHitboxRC();

	return S_OK;
}

void Charactor::release(void)
{
}

void Charactor::update(void)
{
	cout << " _scarecrow->update()" << endl;

	++_life > 100 ? _life-- : NULL;
	switch (_status) {
	case ATTACK:
		_indexY = 2;
		break;
	case DAMAGED:
		_indexY = 1;
		break;
	case STANDING :
	case MOVE :
	default :
		_indexY = 0;
		break;
	}
	if (++_counter % _standImageCounter == 0) {
		cout << "_index ÆÇº°±â" << endl;
		_standImageCounter = (RND->getfloat(3) * 10);
		++_indexX > _myImage.getMaxFrameX() ? _indexX = 0 : NULL;
		_myImage.setFrameX(_indexX);
		_myImage.setFrameY(_indexY);
		cout << _standImageCounter << endl;
	}

}

void Charactor::render(void)
{
	cout << " _scarecrow->render() start" << endl;
	_myImage.frameRender(getMemDC(), _rcImage.left, _rcImage.top);
	cout << " _scarecrow->render() end" << endl;
}

void Charactor::attack()
{
}
