#pragma once
#include "SingletonBase.h"
#include "GImage.h"

/*
STL �� �ٽ�

- Ű, ���� ���� ����
	�� ù��° first
	�� �ι�° second

- ���� �߰��ϴ� ����� insert() �� ����ϰ� Ű�� ����� ���ÿ� �߰��ؾ� �ϴ�
	pair or make_pair�� ����Ѵ�


	�Ŵ���.. ���ε� �� �� �������� ����� �ִ�... Ŭ������ ���� �־���Ѵ�.
	GImage�� ���εǾ���,
	ImageManager�� GImage�� MainGame ������ ��������� ���ش�.
*/

class ImageManager : public SingletonBase <ImageManager>
{
private:
	typedef map<string, GImage*> _mapImageList;
	typedef map<string, GImage*>::iterator mapImageIter;

private:
	_mapImageList _mImageList;

public:

	ImageManager() {}
	~ImageManager() {}

	HRESULT init(void);
	void release(void);


	GImage* addImage(string strkey, int width, int height);
	GImage* addImage(string strkey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addImage(string strkey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strkey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	GImage* addFrameImage(string strkey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));


	GImage* findImage(string strKey);
	bool deleteImage(string strKey);
	bool deleteAll();


	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int soutHeight, BYTE alpha);
	
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawRect, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawRect, int offsetX, int offsetY, BYTE alpha);
};

