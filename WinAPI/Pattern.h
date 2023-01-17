#pragma once
#include "GameNode.h"

class Pattern : public GameNode
{
private:
	float _startX;
	float _startY;
	float* _px;
	float* _py;
	short _patternNumber;

	short _count;
	bool _moveLeft;
	bool _moveUp;

	float _distance;
	float _rad;

public:
	HRESULT init(float* x, float* y, short num);
	void release(void);
	void update(void);
};
