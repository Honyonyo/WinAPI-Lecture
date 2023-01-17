#pragma once
#include "GameNode.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define PI 3.141592653f
//각도 -> 라디안
#define DEGREE_TO_RADIAN(_dgr) (M_PI * (_dgr) / 180.0f )
//라디안 -> 각도
#define RADIAN_TO_DEGREE(_rdn) (M_PI / (_rdn) * 180.0f )

#pragma region 삼각함수
/*
	각도를 줄 때 쓴다!
	거리를 구할때 쓴다!

	▶ 삼각함수란?
	직각삼각형의 각을 직각 삼각형 변들의 길이비로 나타내는 함수
	게임개발을 하는 관점에서는 각도를이용할 때 삼각함수를 이용하면 아주 좋다,
		- 발사체의 각도, 캐릭터의 대각선 이동(3d에서 필수), 스킬범위설정 등등.

	※삼각함수 하면 기억할 세가지!
	 * 빗변		l
	 ** 대변		h
	 *** 밑변	b
	sin cos tan
		1. sin : 빗변과 높이의 비율을 구해주는 함수
			sinθ=대변 / 빗면= h/l
		2. cos : 빗변과 밑변의 비율을 계산해주는 함수
			cosθ = 밑변 / 빗면
		3. tan : 밑변과 대변의 비율을 구해준다.
			tanθ = 밑변 / 대변
	기,,본,, 0 30 45 60 90
			https://t1.daumcdn.net/cfile/tistory/99184D445B7ED68B0D

	▶ 프로그래밍에서의 삼각함수
	- API에서는 윈도우 좌표계를 사용한다.
	- 윈도우 좌표계는 데카르트 좌표계와는 달리 y축이 아래로 갈수록 증가되기 때문에
		y축 좌표를 구하기 위해서는 별다른 처리를 하지 않은 sin 앞에 -를 붙이거나 각에 +180을 넣는다.

	▷ 기억해야 할 개념
	- 호도법 : 각도를 나타내는 표현방법중 하나로, 호의 길이로 각도를 표현하는 방법
		PI를 사용해 180도 각도를 표시하는 것
		컴퓨터는 각도를 인식할 때 *도를 사용할 수 없다.
		*반지름의 길이와 같은 호에 대한 중심각 = 1호도(라디안)

	- 라디안 : 호도법을 사용할 때 표기하는 각의 단위
		반지름과 호의길이가 같아지는 각도를 1라디안이라고 한다,
		(대략 1라디안 = 57.3도)

	- 도 : 대중적으로 사용되는 각의 단위
		도수법 / 각도표기라고 불린다.
		한바퀴 = 360도

	- 60분법
		원의 둘레를 360등분하여 각의 크기를 나타내는 방법
		PI = 3.14
		원의 둘레 = r*2*PI
		원의 넓이 = r^2 * PI

				>>PI의 라디안값은 180도.
				(아래와 같은 공식이 성립할 수 있다.)
				-Degree
				 180 Degree		= PI Radian
				 1	Degree		= PI /180 Radian
				 x	Degree		= x * PI / 180 Radian

				 - Radian
				  PI Radian		= 180 Degree
				  1 Radian		= 180 / PI Degree
				  x Radian		= x * 180 / PI Degree

				 ->부채꼴 모양에서 반지름, 호, 중심각 3가지중에 2가지를 알 수 있다면 나머지 하나도 구할 수 있다.

	※ 알면 좋은 수학식들
		▷ 두 점 사이의거리
			- 두 점을 안다 -> 서로의 거리를 안다 -> 목표지점에서 시작지점을 뺀다
			- 위 공식으로 각 점 (x, y) 사이의 델타량을 구한다.
				DeltaX, DeltaY (변이량)

		▷ 대각선 (빗변)의 거리
			Distance (빗변) = sqrt(DeltaX^2 + DeltaY^2)
				*sqrt(a) = a의 제곱근
		▷ 각을 구한다. (공식을 사용하자)
			float angle = acos (DeltaX/Distance);
				삼각함수 : 각도를 넣어서 각도계산
				역삼각함수 : 결과값을 넣어서 각도를 계산
				*역삼각함수는 arc또는 a를 앞에 표기함.

			- 각도에 대한 변이량을 구한다.
				float DeltaX = cas(Radian) * Distance(이동량);
				float DeltaY = -sin(Radian) * Distance(이동량);

		▷ x축 좌표구하기
			x = cosθ(radian) * 속도

		▷ y축 좌표구하기
			y = -sinθ(radian) * 속도

*/

#pragma endregion


struct TIMEHAND {
	POINT endpt;
	int length;
	int time;
	long double radian;

	void startset() {
		time = 0;
		radian = 0;
	}
	void setRadian(float degree) {
		this->radian = DEGREE_TO_RADIAN((degree)-90);
	}
	void setEndPt(POINT clockCenter) {
		endpt.x = clockCenter.x + cos(radian) * length;
		endpt.y = clockCenter.y + sin(radian) * length;
	}
};

class MainGame : public GameNode
{
private:
	int _clockRadius;
	bool _switch; 
	POINT _clockCenterPt;

	//시분초 각각 -30 -20 -10

	TIMEHAND _hour;
	TIMEHAND _min;
	TIMEHAND _sec;

	HPEN _currentTimerPen;

	SYSTEMTIME _st;			//시간관련 구조체

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	inline float hourDgre(SYSTEMTIME st) {
		return (st.wHour % 12 * 30 + st.wMinute * 0.5 + st.wSecond * (360 / (12 * 60 * 60)));
	}
	inline float minDgre(SYSTEMTIME st) {
		return (st.wMinute * 6 + st.wSecond % 60 * 0.1);
	}
	inline float secDgre(SYSTEMTIME st) {
		return (st.wSecond * 6);
	}



	void printClock(HDC hdc) {
		
	}

	void printTriangle(HDC hdc) {

		for (int i = 180; i <= 270; i+=10)
		{
		HPEN starPen = CreatePen(PS_SOLID, 1, RGB(225-(i - 90) * 20, (i-90)*20, 0));
		_currentTimerPen = (HPEN)SelectObject(hdc, starPen);
			POINT a = { _clockCenterPt.x + _clockRadius * (sin(DEGREE_TO_RADIAN(i))), _clockCenterPt.y + _clockRadius * (cos(DEGREE_TO_RADIAN(i))) };
			LineMake(hdc, _clockCenterPt, a);
			LineTo(hdc, a.x, _clockCenterPt.y);
			//LineTo(hdc, _clockCenterPt.x, _clockCenterPt.y);
			DeleteObject(starPen);

			if(_switch)
			{
				char centerPt[128];
				char strPtx[128];
				char strPty[128];
				sprintf_s(centerPt, "[중심점x, 중심점y]");
				sprintf_s(strPtx, "[sin%dθ×r + 중심점x,",i);
				sprintf_s(strPty, "cos% dθ×r + 중심점y]",i);
				TextOut(hdc, _clockCenterPt.x - strlen(centerPt)*3, _clockCenterPt.y, centerPt, strlen(centerPt));
				TextOut(hdc, a.x - strlen(strPtx)*7, a.y - 30, strPtx, strlen(strPtx));
				TextOut(hdc, a.x - strlen(strPty)*7, a.y -15, strPty, strlen(strPty));

				
			}
		}

	}


	MainGame() {}
	~MainGame() {}
};

