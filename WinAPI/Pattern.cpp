#include "stdafx.h"
#include "Pattern.h"

HRESULT Pattern::init(float* x, float* y, short num)
{
	_px = x;
	_py = y;
    _startX = *x;
    _startY = *y;
	_patternNumber = num;
	if (num > 3) _patternNumber = 3;
	if (num < 1)_patternNumber = 1;

    _moveLeft = true;
    _moveUp = true;
    
    _distance = getDistance(*_px, *_py, WINSIZE_X / 2, WINSIZE_Y / 2);
    _rad = getAngle(*_px, *_py, WINSIZE_X / 2, WINSIZE_Y / 2);

	return S_OK;
}

void Pattern::release(void)
{
//	SAFE_DELETE(_px);
//	SAFE_DELETE(_py);
    _px = nullptr;
    _py = nullptr;
}

void Pattern::update(void)
{
    switch (_patternNumber)
    {
    case 1:
        if (_count > 30)_count = 0;
        if (_moveLeft)
        {
            if (++ * _px > WINSIZE_X)
                _moveLeft = false;
        }
        else
        {
            if (-- * _px < 0)
                _moveLeft = true;
        }

        if (_moveUp)
        {
            *_py += RND->getInt(2);
            if (*_py > WINSIZE_Y / 2)
                _moveUp = false;
        }
        else
        {
            *_py -= RND->getInt(2);
            if (*_py < 0)
                _moveUp = true;
        }
        _count++;
        break;
    case 2:
        _distance = getDistance(*_px, *_py, WINSIZE_X / 2, WINSIZE_Y / 2);
        _rad += 0.01;    
        *_px = _distance * cos(_rad) + WINSIZE_X / 2;
        *_py = _distance * sin(_rad) + WINSIZE_Y / 2;
        break;
    case 3:
    {
        if (_moveLeft)
        {
            *_px += 3;
            if (*_px > WINSIZE_X)
            {
                _moveLeft = false;
                _moveUp = true;
            }
        }
        else
        {
            *_px -= 3;
            if (*_px < 0)
            {
                _moveLeft = true;
                _moveUp = false;
            }
        }

        if (_moveUp)
        {
            *_py += 0.5;
        }
        else
        {
            *_py -= 0.5;
        }
        break;
    }
    }
}
