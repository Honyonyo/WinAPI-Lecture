#pragma once
#include"SingletonBase.h"
#include"Timer.h"

class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* _timer;

public:
	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(HDC hdc);
	// ������ �̹����� �̷��� �������ʿ䰡 ���� ������ ���ӳ�� ���x
	// �׷��Ƿ� �ڵ� �Ծุ ���缭 ����

	inline float gerWorldTime(void) const { return _timer->getWorldTime(); }
	inline float gerElapsedTime(void) const { return _timer->getElapsedTime(); }

	TimeManager() {}
	~TimeManager() {}
};

