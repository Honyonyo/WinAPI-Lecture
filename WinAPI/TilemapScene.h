#pragma once
#include "GameNode.h"
#include "MapMaker.h"

class TilemapScene : public GameNode
{
private:
	MapMaker* _map;
	int _number;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void start(void);
};