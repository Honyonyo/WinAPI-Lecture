#pragma once
#include "GameNode.h"
class TempSoundScene : public GameNode
{
private :
	bool _bgmPlaying;
public :
	HRESULT init(void);
	void update(void);
};

