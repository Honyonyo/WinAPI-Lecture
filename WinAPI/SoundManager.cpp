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
	_sound = new Sound * [TOTAL_SOUND_CHANNEL];
	_channel = new Channel * [TOTAL_SOUND_CHANNEL];

	//�޸� �ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	memset(_channel, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

	return S_OK;
}

void SoundManager::release(void)
{
	//���� ����
	auto iter = _mapSC.begin();
	for (; iter != _mapSC.end();) 
	{
		if (iter->second != nullptr) {
			if (iter->second->channel != nullptr)
				iter->second->channel->stop();
			if (iter->second->sound != nullptr)
			{
				if (iter->second->sound != nullptr)
					iter->second->sound->release();
			}
		}
		SAFE_DELETE(iter->second);
		iter = _mapSC.erase(iter);
	}

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

void SoundManager::setUp(string key, string fileName, SOUNDKIND soundKind, bool backGround, bool loop)
{
	scGroup* soundGroup;
	soundGroup = new scGroup;
	memset(&soundGroup->sound, 0, sizeof(Sound*));
	memset(&soundGroup->channel, 0, sizeof(Channel*));
	cout << "���ֱ���"<<soundGroup->sound << endl;

	soundGroup->soundkind = soundKind;

	if (loop)
	{
		if (backGround)
		{
			_system->createStream(fileName.c_str(), FMOD_LOOP_NORMAL, 0, &soundGroup->sound);
		}//end background loop
		else
		{
			//���ÿ� �������� ��� ����
			_system->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, 0, &soundGroup->sound);
		}//end effect loop
	}//end if loop
	else
	{
		_system->createSound(fileName.c_str(), DMDFO_DEFAULT, 0, &soundGroup->sound);
	}//end loop else

	_mapSC.insert(make_pair(key, soundGroup));
	cout << soundGroup->sound << endl;
}
	
//���α׷�����, ����, ����Ʈ, �ִϸ��̼� �迭
// 0.0~1.0
void SoundManager::play(string key, float volume)
{
	scGroup* sc = findSound(key);
	if (sc == nullptr)
	{
		return;
	}
	_system->playSound(FMOD_CHANNEL_FREE, (sc->sound), 0, &(sc->channel));
	sc->channel->setVolume(volume);
}

bool SoundManager::pauseAndResume(string key)
{
	scGroup* sc = findSound(key);
	if (sc == nullptr)
	{
		return false;
	}

	bool isPaused;
	sc->channel->getPaused(&isPaused);
	isPaused = !isPaused;
	sc->channel->setPaused(isPaused);

	return isPaused;
}

void SoundManager::pauseAndResume(string key, bool paused)
{
	scGroup* sc = findSound(key);
	if (sc == nullptr)
	{
		return;
	}

	sc->channel->setPaused(true);
}

void SoundManager::stop(string key)
{
	scGroup* sc = findSound(key);
	if (sc == nullptr)
	{
		return;
	}

	sc->channel->stop();
}

SoundManager::SoundManager()
{}
