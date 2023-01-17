#include "stdafx.h"
#include "RandomPolygon.h"
#include "Draw.h"
HINSTANCE _hinstance;
HWND _hWnd;
LPSTR lpszClass = TEXT("다각형 그리기모드");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
/*
[READE ME]
조작법
: 좌클릭을 하면 과제1에 해당하는 랜덤 도형이 출력됩니다.
  우클릭을 하면 과제2에 해당하는 인물그림이 출력됩니다.
  스페이스바를 누르면 화면이 하얗게 지워집니다.
  ESC를 누르면 종료됩니다.

====================================================

과제1.
동그라미, 네모, 세모 총 3가지의 도형을 출력합니다.
클릭한 순간의 마우스좌표를 중심으로 도형을 생성해서 출력합니다.
삼각형의 경우, 먼저 랜덤한 삼각형을 생성한 후,
삼각형의 무게중심을 마우스포인터 위치로 옮겼습니다.
옮기면서 화면 바깥으로 비져나간 점은 화면 끝으로 옮겨주었습니다.
혹시라도 세 점이 직선상에 위치할 경우를 대비해
직선이 만들어진 경우, 직선이 되지 않을 때까지 한 점 좌표를 새롭게 만듭니다.

과제2.
얼굴 점을 따서 polygon면과 선으로 채우려고 했습니다.
손이 느려 다 못했습니다. 주말에 마저 하도록 하겠습니다..

*/
int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	_hinstance = hinstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wndClass.hInstance = hinstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		lpszClass, lpszClass, WINSTYLE,
		WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y,
		NULL, (HMENU)NULL, hinstance, NULL
	);

	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	ShowWindow(_hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	HBRUSH hbr;
	PAINTSTRUCT ps;
	POINT _ptMouse;
	RndPoly rolypoly;
	Face face;


	switch (iMsg) {
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_LBUTTONDOWN:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);

		hdc = GetDC(hWnd);
		rolypoly.draw(hdc,_ptMouse);				
		break;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		face.draw(hdc);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);	
			break;
		
		case VK_SPACE:
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}

void setWindowSize(int x, int y, int width, int height) {
	RECT rc = { 0,0,width,height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		(SWP_NOZORDER | SWP_NOMOVE));
}