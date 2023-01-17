#pragma once
class Animation
	/*
	�����ӷ����� �� �����־��
	�׷��� �� �ִϸ��̼��� �߰��ұ��?
	
	- ������Ʈ���� ���� �����۾��� �� �� render�� �ؾ���
	
	����1. : ���ϴ� ���� ������ ���, �����߶����, �ʴ� ������ ����Ƚ��
	����2. : ����� ���ð��� �����(������Ʈ������)
	(�Ⱓ : 28�ϱ���)
		- ���� �����Ͽ� ��������
		- ���ο� �̹��� �ʼ�
		- ��ŸƮ��, ���ӽ� ����
		- ���� ���̸� ������ ȹ���ϰ�, �÷��̾��� ü���� ���� ���Ϸ� �������� ���� ����
		- ���� ��� ���̸� ���������� �ٲ�鼭 ���� ����(�ڿ�������...)
		- ������ ���̸� ���� Ŭ����		
	*/
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int   _frameNum;		//�����Ӽ�
	int   _frameWidth;		//�����Ӱ���ũ��
	int   _frameHeight;		//�����Ӽ���ũ��
	int   _frameNumWidth;	//�����������߰���
	int   _frameNumHeight;	//�����������߰���

	float _frameUpdateSec;	//�ʴ� ������ ������Ʈ ��
	float _elapsedSec;		//�����Ӱ� ������ ������ �ð�

	bool  _isPlay;			//�÷������̴�?
	bool  _loop;			//�ݺ�����?
	DWORD _nowPlayIdx;		//���� �÷��� �ε���

public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);
	//��ü �����, �ݺ���� (������� �ܼ�������� �ƴ϶� �θ޶��� ����)
	void setDefPlayFrame(bool reverse = false, bool loop = false);
	//���ϴ� �����Ӹ� �� ����ϱ� ���� �������ε����迭���޴´�
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0,bool loop = false);
	//���������Ӱ� �������ӱ����� �����ݺ����
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	
	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);

	void aniStart(void);
	void aniStop(void);
	void aniPause(void);
	void aniResume(void);

	//�÷������ΰ�?
	inline bool isPlay(void) { return _isPlay; }
	//������ ��ġ get
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }
	//���� �ִϸ��̼��� ������ ������ ���´�
	inline int getFrameIdx(void) {
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	//������ ����ũ��
	inline int getFrameWidth(void) { return _frameWidth; }
	//������ ����ũ��
	inline int getFrameHeight(void) { return _frameHeight; }

	//���� ������ ���� �� ��°
	inline DWORD getNowFrameIdx(void) { return _nowPlayIdx; }	

	Animation(void);
	~Animation() {};
};