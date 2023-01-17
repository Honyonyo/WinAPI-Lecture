#include "stdafx.h"
using namespace std;
#pragma once
class RndPoly {
private:
	int vertex;	//0 : 동그라미 1 :네모 2 : 세모
	POINT polypoint[3]={0};

public:

	RndPoly() {
		vertex = RND->getInt(3)+1;
	}
	~RndPoly() {
	}

	void setTriPoint(POINT mousePt) {
		POINT triGravity;
		POINT distGtoMouse;	//무게중심과 마우스포인터 사이의 거리
		polypoint[0] = { RND->getInt(WINSIZE_X),RND->getInt(WINSIZE_Y) };
		polypoint[1] = { RND->getInt(WINSIZE_X),RND->getInt(WINSIZE_Y) };
		polypoint[2] = { RND->getInt(WINSIZE_X),RND->getInt(WINSIZE_Y) };

		do {
			if (!(polypoint[0].x == polypoint[1].x && polypoint[1].x == polypoint[2].y)) {
				break;
			}
			else polypoint[0].x = RND->getInt(WINSIZE_X);
		} while (true);
		do {
			if (!(polypoint[0].y == polypoint[1].y && polypoint[1].y == polypoint[2].y)) {
				break;
		}
			else polypoint[0].y = RND->getInt(WINSIZE_Y);
		} while (true);

		triGravity.x = (polypoint[0].x + polypoint[1].x + polypoint[2].x) / 3;
		triGravity.y = (polypoint[0].y + polypoint[1].y + polypoint[2].y) / 3;

		distGtoMouse.x = mousePt.x - triGravity.x;
		distGtoMouse.y = mousePt.y - triGravity.y;

		for (int i = 0; i < 3; i++) {
			polypoint[i].x += distGtoMouse.x;
			polypoint[i].y += distGtoMouse.y;
			//삼각형의 꼭짓점이 윈도우 바깥으로 나갔을 경우 꼭짓점을 경계선으로 옮겨줌
			polypoint[i].x = (polypoint[i].x > WINSIZE_X) ? WINSIZE_X : polypoint[i].x;
			polypoint[i].x = (polypoint[i].x < 0) ? 0 : polypoint[i].x;
			polypoint[i].y = (polypoint[i].y > WINSIZE_Y) ? WINSIZE_Y : polypoint[i].y;
			polypoint[i].y = (polypoint[i].y < 0) ? 0 : polypoint[i].y;
		}

	}

	void draw(HDC hdc,POINT pt) {
			short width, height;
			width = WINSIZE_X - pt.x > 400 ? pt.x : WINSIZE_X - pt.x;
			height = WINSIZE_Y - pt.y > 400 ? pt.y : WINSIZE_Y - pt.y;
		switch (vertex) {
		case 1:
			EllipseMakeCenter(hdc, pt.x, pt.y, RND->getInt(width), RND->getInt(height));
			char strPT[30];
			wsprintf(strPT, "[%d,%d]", pt.x, pt.y);
			TextOut(hdc, pt.x - 20, pt.y - (strlen(strPT) / 2), strPT, strlen(strPT));
			break;
		case 2:
			DrawRectMake(hdc, RectMakeCenter(pt.x, pt.y, width, height));
			wsprintf(strPT, "[%d,%d]", pt.x, pt.y);
			TextOut(hdc, pt.x - 20, pt.y - (strlen(strPT) / 2), strPT, strlen(strPT));
			break;
		case 3:
			setTriPoint(pt);
			Polygon(hdc, polypoint, 3);
			wsprintf(strPT, "[%d,%d]", pt.x, pt.y);
			TextOut(hdc, pt.x - 20, pt.y - (strlen(strPT) / 2), strPT, strlen(strPT));

			break;
		}
	}
};