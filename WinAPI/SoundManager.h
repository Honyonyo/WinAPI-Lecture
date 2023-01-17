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

//enum class SOUNDKIND : UINT8
//{
//	SOUND_BGM = 0,
//	SOUND_EFFECT_1,
//	SOUND_EFFECT_2,
//	SOUND_END
//};
enum SOUNDKIND
{
	SOUND_BGM = 0,
	SOUND_EFFECT_1,
	SOUND_EFFECT_2,
	SOUND_END
};
using namespace FMOD;

#define EXTRA_SOUND_CHANNEL 5		//������ ä�� ����
#define TOTAL_SOUND_CHANNEL (SOUND_END) + EXTRA_SOUND_CHANNEL		//�� ���� ����

class SoundManager : public SingletonBase <SoundManager>
{
private:
	System* _system;	//�ѱ����
	Sound** _sound;		//��ü���� ��������
	Channel** _channel;	//������ä��, �޸𸮹���

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void setUp(char* fileName, int soundKind, bool backGround, bool loop);
	void play(int soundKind, float volume);

	SoundManager();
};

