#include "stdafx.h"
#include "Scene_1130_Battle.h"

HRESULT HomeWork::init(void)
{
    IMAGEMANAGER->addImage("배경_으시시", "homework/Resourse/Image/Background/game_bg_16.bmp", (int)1600, (int)800, false);
    _scarecrow.init();
    return S_OK;
}

void HomeWork::release(void)
{
    _scarecrow.release();
}

void HomeWork::update(void)
{
    _scarecrow.update();
}

void HomeWork::render(void)
{
    IMAGEMANAGER->findImage("배경_으시시")->render(getMemDC());
}
