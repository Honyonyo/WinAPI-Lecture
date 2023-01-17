#pragma once
#include "SingletonBase.h"

//mmsystem.h : ������ ���� ��� ���̺귯��
#include <mmsystem.h>

//mciapi.h : ��ġ�����ڿ��� ������
// Media Control Interface
//mciSendString() ��� ����
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

	//resume, pause �Լ��� �־��
};

