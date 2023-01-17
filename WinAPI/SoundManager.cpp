#include "stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init(void)
{
    //���� �ý��� ����
    System_Create(&_system);

    //�ý��� �ʱ�ȭ
    _system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

    //ä�μ��� �޸𸮹��� �� ���带 �����ϰڴ�.
    //(ä�μ��� ���� ���� �����ִ� ���� ����.]
    _sound = new Sound*[TOTAL_SOUND_CHANNEL];
    _channel = new Channel*[TOTAL_SOUND_CHANNEL];

    //�޸� �ʱ�ȭ
    memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
    memset(_sound, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

    return S_OK;
}

void SoundManager::release(void)
{
    //���� ����
    if (_channel != nullptr || _sound != nullptr)
    {
        for (int i = 0; i < TOTAL_SOUND_CHANNEL; i++)
        {
            if (_channel != nullptr)
            {
                if (_channel[i]) _channel[i]->stop();
            }
            if (_sound != nullptr)
            {
                if (_sound != nullptr) _sound[i]->release();
            }
        }
    }

    SAFE_DELETE_ARRAY(_channel);
    SAFE_DELETE_ARRAY(_sound);

    if (_system != nullptr)
    {
        _system->release();
        _system->close();
    }
}

void SoundManager::update(void)
{
    //FMOD �ý��� ����
    //���� �ý��� ������Ʈ
    //������ �ٲ�ų� ����� ���� ���带 ä�ο��� ���� �� �پ��� �۾��� �ڵ����� ó��
    _system->update();
}

void SoundManager::setUp(char* fileName, int soundKind, bool backGround, bool loop)
{
    if (loop)
    {
        if (backGround)
        {
            _system->createStream(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
        }//end background loop
        else
        {
            //���ÿ� �������� ��� ����
            _system->createSound(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
        }//end effect loop
    }//end if loop
    else
    {
        _system->createSound(fileName, DMDFO_DEFAULT, 0, & _sound[soundKind]);
    }//end loop else
}

//���α׷�����, ����, ����Ʈ, �ִϸ��̼� �迭
// 0.0~1.0
void SoundManager::play(int soundKind, float volume)
{
    _system->playSound(FMOD_CHANNEL_FREE, _sound[soundKind], 0, &_channel[soundKind]);
    _channel[soundKind]->setVolume(volume);
}

SoundManager::SoundManager()
{}
