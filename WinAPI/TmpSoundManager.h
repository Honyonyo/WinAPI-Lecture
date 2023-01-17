#pragma once
#include "SingletonBase.h"

//mmsystem.h : 윈도우 내장 재생 라이브러리
#include <mmsystem.h>

//mciapi.h : 장치관리자에서 가져옴
// Media Control Interface
//mciSendString() 사용 위함
#include <mciapi.h>

//Window MultiMedia
#pragma comment(lib, "Winmm.lib")


class TmpSoundManager :public SingletonBase <TmpSoundManager>
{
public:
	HRESULT init();
	void addMp3FileWithKey(string key, string filename);
	void addWaveFileWithKey(string key, string filename);
	void playEffectSoundWave(char* fileName);
	void playSoundWithKey(string key);
	void stopMp3WithKey(string key);

	//resume, pause 함수도 넣어보기
};

