#pragma once
#include "SingletonBase.h"
#include "GImage.h"

/*
STL 맵 핵심

- 키, 값을 잊지 말자
	ㄴ 첫번째 first
	ㄴ 두번째 second

- 맵을 추가하는 방법은 insert() 를 사용하고 키와 밸류를 동시에 추가해야 하니
	pair or make_pair를 사용한다


	매니저.. 랩핑된 좀 더 세부적인 기능이 있는... 클래스가 따로 있어야한다.
	GImage가 랩핑되었고,
	ImageManager가 GImage와 MainGame 사이의 연결고리를 해준다.
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


