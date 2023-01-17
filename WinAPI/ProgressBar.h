#pragma once
#include "GameNode.h"
class ProgressBar : public GameNode
{
private:
	GImage* _progressBarUp;
	GImage* _progressBarDown;

	RECT _rc;
	float* _x;
	float* _y;

	float _width;

public:
	HRESULT init(float* x, float* y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float maxScore);

	void setX(float* x) { _x = x; }
	void setY(float* y) { _y = y; }


	virtual ~ProgressBar(){}
};

