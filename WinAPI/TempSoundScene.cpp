#include "stdafx.h"
#include "TempSoundScene.h"

HRESULT TempSoundScene::init(void)
{
	_bgmPlaying = false;
	TMPSOUNDMANAGER->addMp3FileWithKey("배경음", "Resources/Sound/endingBgm_01.mp3");
	PlaySound("Resources/Sound/endingBgm_01.wav", NULL, SND_ASYNC);
	return S_OK;
}

void TempSoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F10)) {
		if (!_bgmPlaying)
		{
			TMPSOUNDMANAGER->playSoundWithKey("배경음");
			_bgmPlaying = true;
		}
		else _bgmPlaying = false;
	}
	if(KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		TMPSOUNDMANAGER->playEffectSoundWave("Resources/Sound/09_Emergency1.wav");
	}
}
