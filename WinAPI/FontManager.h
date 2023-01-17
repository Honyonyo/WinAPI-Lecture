#pragma once

/*
과제1. 폰트매니저 완성
	-3개의 함수 원형을 건들지 않고 (추가x, 변수x) 기능 구현을 한다.
	출력되는 문장의 종류는 3가지
	전체 버퍼를 읽어들여서 바로 출력하는 방식
	하나씩 버퍼를 읽어들여서 출력하는 방식
	스킵 기능이 들어간 출력방식

* 편의성 + 호환성 필수
	//CreateFont


과제2. 캐릭터 공격 / 방어
	필수 : 이미지, 배경, 체력바, 플레이어(대기 공격 방어), 적(대기,공격,피격)
	기본형식은 대전게임처럼 배치한다. (+체력바)
	플레이어(1p)는 공격 및 방어를 할 수 있고, 적은 허수아비로 설정한다.
	허수아비는 공격 및 피격 모션이 존재한다. (+대기)
	플레이어는 상시조종 <->적은 공격 on/off기능만 (이동x)
	공격, 방어, 피격등이 발생하면 상황에 맞는 결과를 화면에 렌더링
	(맞기 빗나감 치명타 등)
	데미지 표기한다.

*/
enum TextDraw_Cord {
	TextDraw_NO_BUFFER = 0,
	TextDraw_BUFFER,
	TextDraw_BUFFER_SKIP
};
class FontManager : public SingletonBase <FontManager>
{
public:

	HRESULT init(void);
	void release(void);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontHeight, int fontWeight, char* printString, int length, COLORREF color);
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontHeight, int fontWeight, LPCWSTR printString, int length, COLORREF color);
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontHeight, int fontWeight, LPCWSTR* printStringArr, int length, COLORREF color);
	FontManager() {
	};
	~FontManager() {};
};