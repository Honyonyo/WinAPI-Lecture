#pragma once

#pragma region Ÿ�̸�
/*

	�� Ÿ�̸�

	- ������ ����� API �����Լ�(���������δ� ȿ���� ���� ����...)
	�� GetTickCount();
	�� GetTickCount64();
	- �ð��� �����ϴ� �Լ����� �⺻������ �����찡 ���۵� ���� ���� �ð��� �и� ���� ������
	  ��ȯ�Ѵ�.
	- �и� �����庸�� �� �� ������ Ÿ�̸Ӹ� ���Ѵٸ� ������ Ÿ�̸Ӹ� �����ؾ� �Ѵ�.

	- ���� Ÿ�̸Ӹ� �����Ҷ��� 2������ �������
	�� 1. �ػ�
	�� 2. Ŭ��(������)


	�� �ػ󵵶�?
	- �پ��� �ð� �Լ����� �ð��� �����ϱ� ���� Tick ��� ������ �ִ�.
	  �� ���� 1���� �������� �󸶳� ���� ���������� ���� �� �ִ��� ���
	- 1�� ���� �󸶳� ���� Tick���� ������ �ð��� ��Ȯ���� ���̴��İ� ���ػ󵵿� ���ػ���
	���������� �Ǵ� ����

	�� Clock

	- Ÿ�̸ӿ��� ����ϴ� Ŭ���� ���� CPU Ŭ���� �ǹ��Ѵ�.
	- Ŭ���̶�?
	�� Ŭ���� ������ ȸ���� ������ ���� ���̸� Hz ������ ǥ��
	�� Ex: 1�ʿ� 1Hz�� ��ȣ�� �ѹ� �ش�.(0�Ǵ� 1)
	�� 1GHz�� 10�� 9���� -> 10���
	�� 2.9ghz -> 1�ʿ� 29��� ��Ʈ�� �ű��

	- Ÿ�̸� ����
	- Milli Second
	- 10 Milli Second
	- 100 Milli Second

	�� ������ Ÿ�̸��� ��� ��ø�� ��Ű�� ��ø�� ��Ų ��ŭ ȿ���� �ö󰣴�.

*/
#pragma endregion

class Timer
{
private:
	float		_timeScale;   // ����ð� ����
	float		_timeElapsed; // ������ �ð��� ����ð��� �����
	bool		_isHardware;   // ������ Ÿ�̸� ���� ����

	__int64		_curTime; //  ����ð� __int 32 or 64(�p��Ʈ ����ϴ���) �������Ϸ� �̾Ƴ����� 64 ,32 ���� __int64 32��Ʈ�� 64�� ������ �ٲ��ش� __ <- ǥ�ؾ�� �ƴ϶�°�
	__int64		_lastTime; // �����ð�
	__int64		_periodFrequency; // �ð� �ֱ�

	/*

	__int64 vs long

	- int vs lonng
	32��Ʈ���� ���� 4��Ʈ -> 64��Ʈ�������� 8��Ʈ
	*/

	unsigned long _frameRate;  //(�ʴ������Ӽ�)
	unsigned long   _FPSFrameCount; //fps ī��Ʈ
	float			_FPSTimeElapsed; //FPS �ð� �����
	float			_worldTime;		 // ������ ���۵� �� ����� ��ü�ð�


public:
	HRESULT init(void);
	void tick(float lockFPS = 0.0f);


	//���� FPS
	unsigned long gerFrameRate(char* str = nullptr) const; //?
	//������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; } //?
	// ��ü ��� �ð�
	inline float getWorldTime(void) const { return _worldTime; } //?
	// ����Լ��� ���� ����Ʈ�� �ڷ� ������ -> ����Լ��� ���ȭ�� �ǹ�
	// �� �� �Լ������� ��� ������ �� ������ ���´�.
	// �� ��������� ����� �� �ִ� ��ȸ�� ���� ������ ���� ���� ���� �Ұ�
	// �� ������ x
	// �ܺο��� �������� ���ϰ� �ϱ����� ������

	// Timer -> Timer manger�� �尥��

	// ���� -> ���Ӿ��迡���� UPDATE�� �Ⱦ� (������ ������� ���� ���ǹ��� ������� ���ϴ°�쵵����)
	// ���� Ÿ�̸ӷ� ������� �����ϰ� �̾Ƴ��� �ִ�


public:
	Timer() {};
	~Timer() {};
};
