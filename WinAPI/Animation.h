#pragma once
class Animation
	/*
	프레임랜더를 잘 쓰고있어요
	그런데 왜 애니메이션을 추가할까요?
	
	- 업데이트에서 여러 선행작업을 한 후 render를 해야함
	
	과제1. : 원하는 구간 프레임 재생, 구간잘라서재생, 초당 프레임 갱신횟수
	과제2. : 비행기 슈팅게임 만들기(세미포트폴리오)
	(기간 : 28일까지)
		- 팀간 상의하여 일정조율
		- 새로운 이미지 필수
		- 스타트씬, 게임신 구성
		- 적을 죽이면 점수를 획득하고, 플레이어의 체력이 일정 이하로 떨어지면 게임 오버
		- 적을 모두 죽이면 스테이지가 바뀌면서 보스 출현(자연스럽게...)
		- 보스를 죽이면 게임 클리어		
	*/
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int   _frameNum;		//프레임수
	int   _frameWidth;		//프레임가로크기
	int   _frameHeight;		//프레임세로크기
	int   _frameNumWidth;	//가로프레임중갯수
	int   _frameNumHeight;	//세로프레임중갯수

	float _frameUpdateSec;	//초당 프레임 업데이트 수
	float _elapsedSec;		//프레임과 프레임 사이의 시간

	bool  _isPlay;			//플레이중이니?
	bool  _loop;			//반복도니?
	DWORD _nowPlayIdx;		//현재 플레이 인덱스

public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);
	//전체 역재생, 반복재생 (역재생이 단순역재생이 아니라 부메랑을 말함)
	void setDefPlayFrame(bool reverse = false, bool loop = false);
	//원하는 프레임만 찍어서 재생하기 위한 프레임인덱스배열을받는다
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0,bool loop = false);
	//시작프레임과 끝프레임까지를 구간반복재생
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	
	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);

	void aniStart(void);
	void aniStop(void);
	void aniPause(void);
	void aniResume(void);

	//플레이중인가?
	inline bool isPlay(void) { return _isPlay; }
	//프레임 위치 get
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }
	//현재 애니메이션의 프레임 순서를 얻어온다
	inline int getFrameIdx(void) {
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	//프레임 가로크기
	inline int getFrameWidth(void) { return _frameWidth; }
	//프레임 세로크기
	inline int getFrameHeight(void) { return _frameHeight; }

	//현재 프레임 순서 몇 번째
	inline DWORD getNowFrameIdx(void) { return _nowPlayIdx; }	

	Animation(void);
	~Animation() {};
};