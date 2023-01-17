#pragma once

/*
����1. ��Ʈ�Ŵ��� �ϼ�
	-3���� �Լ� ������ �ǵ��� �ʰ� (�߰�x, ����x) ��� ������ �Ѵ�.
	��µǴ� ������ ������ 3����
	��ü ���۸� �о�鿩�� �ٷ� ����ϴ� ���
	�ϳ��� ���۸� �о�鿩�� ����ϴ� ���
	��ŵ ����� �� ��¹��

* ���Ǽ� + ȣȯ�� �ʼ�
	//CreateFont


����2. ĳ���� ���� / ���
	�ʼ� : �̹���, ���, ü�¹�, �÷��̾�(��� ���� ���), ��(���,����,�ǰ�)
	�⺻������ ��������ó�� ��ġ�Ѵ�. (+ü�¹�)
	�÷��̾�(1p)�� ���� �� �� �� �� �ְ�, ���� ����ƺ�� �����Ѵ�.
	����ƺ�� ���� �� �ǰ� ����� �����Ѵ�. (+���)
	�÷��̾�� ������� <->���� ���� on/off��ɸ� (�̵�x)
	����, ���, �ǰݵ��� �߻��ϸ� ��Ȳ�� �´� ����� ȭ�鿡 ������
	(�±� ������ ġ��Ÿ ��)
	������ ǥ���Ѵ�.

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