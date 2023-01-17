#pragma once
class Rect_
{
private:
	bool isClicked = false;

	POINT startRc = { 350,350 };
	short length = 100;
	short distanceX = NULL; short distanceY=NULL;

	short count = 0;

public:
	void drag(POINT pt,HDC hdc) {
		click(pt,hdc);		
		if (isClicked)
		{
			if (count ==0) {
				distanceX = startRc.x - pt.x;
				distanceY = startRc.y - pt.y;
			}
			move(distanceX + pt.x, distanceY + pt.y);
			char strPT[100];
			wsprintf(strPT, "마우스 이동중 (%-10d, %-10d) %d", distanceX + pt.x, distanceY + pt.y, count);

			TextOut(hdc, 50,100, strPT,strlen(strPT));
		}//if (isClicked)
	}//drag

	void drop() {
		isClicked = false;
		count = 0;
		distanceX = NULL;
		distanceY = NULL;
	}

	void click(POINT pt,HDC hdc) {
		if (PointInRect_point(pt, startRc, length, length))
		{
			count++;
			isClicked = true;
			TextOut(hdc, 50,80,"click", strlen("click"));
		}
		else isClicked = false;
	}

	void move(int x, int y) {
		if (isClicked) {
			startRc.x = x;
			startRc.y = y;
		}
		if(!RectInRect(0,0, WINSIZE_X,WINSIZE_Y,
			startRc.x, startRc.y,length,length))
		{
			drop();
			if (startRc.x < 0) startRc.x = 0;
			if (startRc.x > 800) startRc.x = 800;
			if (startRc.y < 0) startRc.y = 0;
			if (startRc.y > 800) startRc.y = 800;
		}
	}//move

	POINT getPoint() {
		return startRc;
	}
	bool getClicked() {
		return isClicked;
	}
	void draw(HDC hdc) {
		RectangleMake(hdc, startRc.x, startRc.y, length, length);
	}


};

