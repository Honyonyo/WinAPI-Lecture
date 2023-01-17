#include "stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(float* x, float* y, int width, int height)
{
    cout << "   프로그레스바 준비 완료" << endl;
    _x = x;
    _y = y;
    
    _rc = RectMakeCenter(*_x, *_y, width, height);
    _progressBarDown = IMAGEMANAGER->addImage("BarDown", "Resources/Images/Object/HpBarDown.bmp",0,0,width, height,false);
    _progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resources/Images/Object/HpBarUp.bmp",0,0,width, height,false);
    
    return S_OK;
}

void ProgressBar::release(void)
{
    SAFE_DELETE(_progressBarDown);
    SAFE_DELETE(_progressBarUp);
}

void ProgressBar::update(void)
{
    _rc = RectMakeCenter(*_x - _progressBarDown->getWidth()/2, *_y-30, _progressBarDown->getWidth(), _progressBarDown->getHeight());
}

void ProgressBar::render(void)
{
    _progressBarDown->render(getMemDC(),
        _rc.left + _progressBarDown->getWidth() / 2,
        *_y + _progressBarDown->getHeight() / 2,
        0, 0,
        _progressBarDown->getWidth(),
        _progressBarDown->getHeight());
    
    _progressBarUp->render(getMemDC(),
        _rc.left + _progressBarDown->getWidth() / 2,
        *_y + _progressBarDown->getHeight() / 2,
        0, 0,
        _width,
        _progressBarDown->getHeight());
}

void ProgressBar::setGauge(float currentScore, float maxScore)
{
    _width = (currentScore / maxScore) * _progressBarDown->getWidth();
}
