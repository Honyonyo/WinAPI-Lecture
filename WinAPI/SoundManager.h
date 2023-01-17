#pragma once
#include "SingletonBase.h"

/*
 FMOD
 - sound engine lib
 - �𸮾�� ����Ƽ���� ���̼��� ������� �⺻ ����Ǿ��ִ�
	�̿� ��κ��� �÷��������� ����ϱ� ���� ����ó���� �ʿ��ϴ�.
		(CoCos2dx)
*/

/*
1. ����Ŵ��� �Լ� �߰�
 - stl 1�� �̻� ���
 �߰��� �Լ� : ����, �Ͻ�����, �簳
 ���� - ���, p - �Ͻ�����, �����̽� - ����
 ���Ǽ� ����Ͽ� �ۼ�

 2. MP3�÷��̾� ����� - 7��
 - �����ư�� ������ ����� �ȴ�.
 - ����� ������ ��ư�� �Ͻ������� �ٲ��.
 - �Ͻ������� ������ �Ͻ����� �ȴ�. ��ư ������� �ٲ��.
 - ����� Ŭ���� �߰����� ���
 - �� ����ð��� ǥ���Ѵ�. (���� / ��ü)
 - �� ���� ����� ������ �ڵ����� ���� ������ �Ѿ��.

 ������ư �����ư �������ư �������ư ����� ������ð�
 ���������ʿ�
 �ٹ��̹��� ����

*/

enum class SOUNDKIND : UINT8
{
	SOUND_BGM = 0,
	SOUND_EFFECT_1,
	SOUND_EFFECT_2,
	SOUND_END
};


#define EXTRA_SOUND_CHANNEL 5		//������ ä�� ����
#define TOTAL_SOUND_CHANNEL (static_cast<int>(SOUNDKIND::SOUND_END)) + EXTRA_SOUND_CHANNEL		//�� ���� ����

using namespace FMOD;

struct scGroup
{
	Sound* sound;
	Channel* channel;
	SOUNDKIND soundkind;
};

class SoundManager : public SingletonBase <SoundManager>
{
private:
	System* _system;	//�ѱ����
	Sound** _sound;		//��ü���� ��������
	Channel** _channel;	//������ä��, �޸𸮹���

	map<string, Sound*> _mapSound;
	map<string, Channel*> _mapChannel;
	map<string, scGroup*> _mapSC;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void setUp(string key, char* fileName, SOUNDKIND soundKind, bool backGround, bool loop);
	void play(string key, float volume);
	bool pauseAndResume(string key);
	void pauseAndResume(string key, bool paused);
	void stop(string key);

	scGroup* findSound(string key)
	{
		auto findkey = _mapSC.find(key);

		if (findkey != _mapSC.end())
		{
			return findkey->second;
		}
		else
		{
			return nullptr;
			cout << "�ش��ϴ� �뷡�� ����. key : " << key << endl;
		}
	}

	SoundManager();
};

