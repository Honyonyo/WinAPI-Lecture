#pragma once
#include "stdafx.h"//�̰� ���� �Ǵ°� �³�?
inline POINT PointMake(int x, int y) {
	POINT pt = { x, y };
	return pt;
}

//���׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY) {
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//����Ʈ�� ���׸���
inline void LineMake(HDC hdc, POINT start, POINT end) {
	MoveToEx(hdc, start.x, start.y, NULL);
	LineTo(hdc, end.x, end.y);
}


//�簢�������. ����갳�� �������� ���⼭ �Լ��� ������ ��
inline RECT RectMake(int x, int y, int width, int height) {
	RECT rc = { x, y, width, height };
	return rc;
}

//�簢�� �����(�߽����� ���̸� �̿�)
inline RECT RectMakeCenter(int x, int y, int width, int height) {
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}
inline RECT RECTMakeLT(int rcleft, int rctop, int width, int height) {
	RECT rc = { rcleft, rctop, rcleft+width, rctop+height };
	return rc;
}
//�簢�� ����� (�߽�������Ʈ�� ���̸� �̿�)
inline RECT RectMakeCenter(POINT pt, int width, int height) {
	RECT rc = { pt.x - width / 2, pt.y - height / 2, pt.x + width / 2, pt.y + height / 2 };
	return rc;
}

//�簢���׸���
inline void DrawRectMake(HDC hdc, RECT rc) {
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//�簢�� �׸��� (���ʱ� �Լ�)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x, y, x+width, y+height);
}
//�簢���׸��� (�߽����� ���ʱ� �Լ�)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}
//�簢���׸��� (�߽�������Ʈ�� ���ʱ� �Լ�)
inline void RectangleMakeCenter(HDC hdc, POINT pt, int width, int height) {
	Rectangle(hdc, pt.x - width / 2, pt.y - height / 2, pt.x + width / 2, pt.y + height / 2);
}


//Ÿ�� �׸��� (�ϸ���)
inline void EllipseMake(HDC hdc, int startX, int startY, int width, int height) {
	Ellipse(hdc, startX, startY, startX + width, startY + height);
}

//Ÿ�� �׸��� (�ϸ���, ������ ������)
inline void EllipseMakeCenter(HDC hdc, int centerX, int centerY, int halfWidth, int halfHeight) {
	Ellipse(hdc, centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
}

//Ÿ�� �׸��� (�ϸ���, ��������Ʈ�� ������)
inline void EllipseMakeCenter(HDC hdc, POINT center, int halfWidth, int halfHeight) {
	Ellipse(hdc, center.x - halfWidth, center.y - halfHeight, center.x + halfWidth, center.y + halfHeight);
}

//�Ÿ��� ����
float getDistancePow(POINT pt1, POINT pt2) {
	return (pt2.x - pt1.x) * (pt2.x - pt1.x) + (pt2.y - pt1.y) * (pt2.y - pt1.y);
}

float Slop(POINT startP, POINT drct2) {
	return ((float)drct2.y - startP.y) / ((float)drct2.x - startP.x);
}

//�浹 ���� ������¡
inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height)
{
	RECT rc = { rcDest.left + width / 2, rcDest.top + height / 2,
	rcDest.right - width / 2, rcDest.bottom - height / 2 };
	
	return rc;
}

// 
// # ���� �߰��� �� #
// 

//�� RECT�� ��ģ �κ��� �ִ��� �Ǵ��ϱ� (�� ������ true)  ���̰��̹��Լ�����;
//inline bool RectOverlapRect(RECT rc1, RECT rc2)
//{
//	int x = (rc1.right - rc2.left) >= 0 ? (rc1.right - rc2.left) : -(rc1.right - rc2.left);
//	int y = (rc1.bottom - rc2.top) >= 0 ? (rc1.bottom - rc2.top) : -(rc1.bottom - rc2.top);
//	int width = rc1.right - rc1.left + rc2.right - rc2.left;
//	int height = rc1.bottom - rc1.top + rc2.bottom - rc2.top;
//
//	if ((x <= width) && (y <= height)) return true;
//	else return false;	
//}

//rect����ü �����̱�
inline void MoveRect(RECT rc, int moveRow,int moveColumn ) {
	rc.left += moveRow;
	rc.right+= moveRow;
	rc.top += moveColumn;
	rc.bottom += moveColumn;
}
//������ �ȿ����̰� �� RECT�� ��ȯ�ϱ�
inline RECT RectMoveReturn(RECT rc, int moveRow, int moveColumn) {
	RECT tmp = rc;
	tmp.left += moveRow;
	tmp.right += moveRow;
	tmp.top += moveColumn;
	tmp.bottom += moveColumn;
	return tmp;
}


//ū RECT �ȿ� ���� RECT�� �ִ°�
inline bool RectInRect(RECT BIGrc, RECT SMALLrc) {
	if ((BIGrc.left < SMALLrc.left) && (BIGrc.right > SMALLrc.right) && (BIGrc.top < SMALLrc.top) && (BIGrc.bottom > SMALLrc.bottom))
		return true;
	else return false;
}

//1�׸� �ȿ� 2�׸� ���԰����ΰ�(�������� ����)
inline bool RectInRect(int x, int y, int width, int height,
	int x2, int y2, int width2, int height2)
{
	if (x < x2 && (x2 + width2) < (x + width) && y < y2 && (y2 + height) < (y + height)) return true;
	else return false;
}

//����Ʈ�� rect����ü �ȿ� �ִ���	//�̹� �ٸ� �Լ��� �ִ�.. PtInRect(&rc,_ptMouse)
//inline bool PointInRect( POINT pt, RECT rc ) {
//	if ((rc.left < pt.x) && (pt.x < rc.right) && (rc.top < pt.y) && (pt.y < rc.bottom))	return true;
//	else return false;
//}

//����Ʈ�� rectangle�� �ȿ� �ִ���
inline bool PointInRect(POINT pt,int boxStartX, int boxStartY, int width, int height) {
	if ((boxStartX < pt.x) && (pt.x < boxStartX+width) && (boxStartY < pt.y) && (pt.y < boxStartX+height))	return true;
	else return false;
}

 //����Ʈ�� ������+���̷� ������� rectangle �� �ȿ� �ִ���
inline bool PointInRect(POINT pt, POINT boxStart, int width, int height) {
	if ((boxStart.x < pt.x) && (pt.x < boxStart.x + width) && (boxStart.y < pt.y) && (pt.y < boxStart.y + height))	return true;
	else return false;
}

//����Ʈ�� ��(�߽����� �Ÿ�) �ȿ� �ִ���
inline bool PtInCircle(POINT pt, POINT centerCircle, int radiusCircle) {
	//��Ÿ����
	if (((centerCircle.x - pt.x) * (centerCircle.x - pt.x) + (centerCircle.y - pt.y, 2) * (centerCircle.y - pt.y, 2))
	> (radiusCircle * radiusCircle))
		return true;
	else return false;

	//�ﰢ�Լ��� ������ ��ź��Ʈ, ���ڻ��ε���� �����ϴµ�,
	//���� 4������ż� ����� �� �����ؾ��ϹǷ� ���ŷο�� ������.	
}