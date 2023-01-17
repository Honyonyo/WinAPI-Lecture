#include "stdafx.h"
#include "AnimationScene.h"

HRESULT AnimationScene::init(void)
{
    _image = IMAGEMANAGER->addImage("ÄÚ³¢¸®", "Resources/Images/Object/kokiri.bmp", 660, 268, true, RGB(255, 0, 255));
    _animationA = new Animation;
    _animationA->init(_image->getWidth(), _image->getHeight(),110,67);
    _animationA->setDefPlayFrame(false, true);
    //_animationA->setPlayFrame(5, 10, false, true);

    //int a[10] = { 1,3,5,7,9,11,13,15,17,19 };
    //_animationA->setPlayFrame(a, 10, true);
    _animationA->setFPS(12);
    return S_OK;
}

void AnimationScene::release(void)
{
    _animationA->release();
    SAFE_DELETE(_animationA);
}

void AnimationScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('B'))
    {
        _animationA->aniStart();
    }

    _animationA->frameUpdate(TIMEMANAGER->gerElapsedTime() * 1);
//    cout << _animationA->getFramePos().x << ", " << _animationA->getFramePos().y<<endl;
    cout << _animationA->getNowFrameIdx() << endl;
}

void AnimationScene::render(void)
{
    _image->aniRender(getMemDC(), WINSIZE_X/2-50, WINSIZE_Y/2, _animationA);
}
