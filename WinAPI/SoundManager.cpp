#include "stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init(void)
{
    //사운드 시스템 생성
    System_Create(&_system);

    //시스템 초기화
    _system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

    //채널수와 메모리버퍼 및 사운드를 생성하겠다.
    //(채널수와 사운드 수는 맞춰주는 것이 좋다.]
    _sound = new Sound*[TOTAL_SOUND_CHANNEL];
    _channel = new Channel*[TOTAL_SOUND_CHANNEL];

    //메모리 초기화
    memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
    memset(_sound, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

    return S_OK;
}

void SoundManager::release(void)
{
    //사운드 삭제
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
    //FMOD 시스템 갱신
    //사운드 시스템 업데이트
    //볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는 등 다양한 작업을 자동으로 처리
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
            //동시에 여러음원 재생 가능
            _system->createSound(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
        }//end effect loop
    }//end if loop
    else
    {
        _system->createSound(fileName, DMDFO_DEFAULT, 0, & _sound[soundKind]);
    }//end loop else
}

//프로그래스바, 사운드, 이펙트, 애니메이션 계열
// 0.0~1.0
void SoundManager::play(int soundKind, float volume)
{
    _system->playSound(FMOD_CHANNEL_FREE, _sound[soundKind], 0, &_channel[soundKind]);
    _channel[soundKind]->setVolume(volume);
}

SoundManager::SoundManager()
{}
