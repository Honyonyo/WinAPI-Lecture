#include "Stdafx.h"
#include "GImage.h"
#include "Animation.h"

GImage::GImage() : _imageInfo(nullptr),
				   _fileName(nullptr),
				   _isTrans(false),
				   _transColor(RGB(0,0,0)),
				   _blendImage(nullptr)
					
{
	//!Do Nothing
}

HRESULT GImage::init(int width, int height)
{
	//���ʱ�ȭ ������ / �̹��� ������ ���� ��� �ִٸ� �������� �ϰڴ�.
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc,width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr;
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ������ �� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hinstance,MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = nullptr;
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������ �� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hinstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ����ó��
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//_s�� ������ �߰���. ���ڸ� �߰��� ���� �� �����ϰ� ���ڴ�.
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������ �� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hinstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ����ó��
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//_s�� ������ �߰���. ���ڸ� �߰��� ���� �� �����ϰ� ���ڴ�.
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������ �� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hinstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX-1;
	_imageInfo->maxFrameY = maxFrameY-1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// ����ó��
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//_s�� ������ �߰���. ���ڸ� �߰��� ���� �� �����ϰ� ���ڴ�.
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������ �� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


HRESULT GImage::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (_imageInfo != nullptr) this->release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDc = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hinstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX-1;
	_imageInfo->maxFrameY = maxFrameY-1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// ����ó��
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	//_s�� ������ �߰���. ���ڸ� �߰��� ���� �� �����ϰ� ���ڴ�.
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ������ �� ����
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT GImage::initForAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);
	_blendFunc.BlendFlags = 0;				//������ �ø��Ŵϱ� ������ɼ� ���� ����
	_blendFunc.AlphaFormat = 0;				//Ư�����ǿ����ߵ��̹Ƿ� ���� ��� ����
	_blendFunc.BlendOp = AC_SRC_OVER;		//����� ��ü�� ���� ���İ� ������ ���ְ� ȥ�տ������� ��Ʈ�ʿ� ���İ�(�� ��Ȯ���� �ȼ���)�� �ְڴ�. - ȥ�հ� �־��ִ� �ɼ�
	
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDc = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDc, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//�ܺ�
void GImage::release(void)
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDc, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDc);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//�����÷�Ű �ʱ�ȭ
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage) {
		SelectObject(_blendImage->hMemDc, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDc);

		//������ ����
		SAFE_DELETE(_blendImage);
	}

}

//0,0
void GImage::render(HDC hdc)
{
	if (_isTrans)
	{
		//GdiTransparentBlt(): ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� ����
		GdiTransparentBlt
		(
			hdc,				//������ ����� DC(ȭ�鿡 �������� DC)
			0,					//����� ��ǥ ����(x)
			0,					//����� ��ǥ ����(y)
			_imageInfo->width,	//����� �̹��� ����ũ��
			_imageInfo->height,	//����� �̹��� ����ũ��
			_imageInfo->hMemDc, //����� ��� �޸� DC
			0,0,				//���� ���� ����
			_imageInfo->width,	//���� ���� ����ũ��
			_imageInfo->height,	//���� ���� ����ũ��
			_transColor			//������ �� ������ ����
		);
	}
	else
	{
		//BitBlt(): DC ���� �������� ���� ���Ӻ��縦 ���ش�.
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
	}
}

// destX, destY
void GImage::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		//GdiTransparentBlt(): ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� ����
		GdiTransparentBlt
		(
			hdc,				//������ ����� DC(ȭ�鿡 �������� DC)
			destX,				//����� ��ǥ ����(x)
			destY,				//����� ��ǥ ����(y)
			_imageInfo->width,	//����� �̹��� ����ũ��
			_imageInfo->height,	//����� �̹��� ����ũ��
			_imageInfo->hMemDc, //����� ��� �޸� DC
			0, 0,				//���� ���� ����
			_imageInfo->width,	//���� ���� ����ũ��
			_imageInfo->height,	//���� ���� ����ũ��
			_transColor			//������ �� ������ ����
		);

	}
	else
	{
		//BitBlt(): DC ���� �������� ���� ���Ӻ��縦 ���ش�.
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
	}
}

//�̹��� Ŭ���� 
// ������ �̹��� ��ǥ�κ��� ����, ���� ũ�⸦ �߶� ���� ���ϴ� ��ǥ�� ���
void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		//GdiTransparentBlt(): ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� ����
		GdiTransparentBlt
		(
			hdc,				
			destX,				
			destY,				
			sourWidth,
			sourHeight,
			_imageInfo->hMemDc, 
			sourX, sourY,				
			sourWidth,	
			sourHeight,	
			_transColor			
		);
	}
	else
	{
		//BitBlt(): DC ���� �������� ���� ���Ӻ��縦 ���ش�.
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDc, sourX, sourY, SRCCOPY);
	}

}

void GImage::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	//�����Ϸ��� ��� ��ü = ���ڷ� �Ѱ��� alpha�� �Ѱ��ְڴ�.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		//1. ����ؾ��� �̹����� ������ �̹����� �����Ѵ�.
		BitBlt
		(
			_blendImage->hMemDc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0,0,
			SRCCOPY
			);

		//2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���.
		GdiTransparentBlt(
			_blendImage->hMemDc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
			);

		//3. ������ �̹����� ȭ�鿡 �׸���.
		//AlphaBlend(
		//	hdc,
		//	0, 0,
		//	_imageInfo->width,
		//	_imageInfo->height,
		//	_blendImage->hMemDc,
		//	0, 0,
		//	_imageInfo->width,
		//	_imageInfo->height,
		//	_blendFunc
		//);
	}
	else {
		//AlphaBlend(
		//	hdc,
		//	0, 0,
		//	_imageInfo->width,
		//	_imageInfo->height,
		//	_imageInfo->hMemDc,
		//	0, 0,
		//	_imageInfo->width,
		//	_imageInfo->height,
		//	_blendFunc
		//);
	}
}

void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	//�����Ϸ��� ��� ��ü = ���ڷ� �Ѱ��� alpha�� �Ѱ��ְڴ�.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		//1. ����ؾ��� �̹����� ������ �̹����� �����Ѵ�.
		BitBlt
		(
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		);

		//2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���. 
		GdiTransparentBlt
			(
				_blendImage->hMemDc,
				0,				//����� ��ǥ ����(x)
				0,				//����� ��ǥ ����(y)
				_imageInfo->width,	//����� �̹��� ����ũ��
				_imageInfo->height,	//����� �̹��� ����ũ��
				_imageInfo->hMemDc, //����� ��� �޸� DC
				0, 0,				//���� ���� ����
				_imageInfo->width,	//���� ���� ����ũ��
				_imageInfo->height,	//���� ���� ����ũ��
				_transColor			//������ �� ������ ����
				);

		//3. ������ �̹����� ȭ�鿡 �׸���.
		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else {
		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}

}

//��µ� x, y, �������x, y, ��³ʺ�width, height, ��������
void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	//�����Ϸ��� ��� ��ü = ���ڷ� �Ѱ��� alpha�� �Ѱ��ְڴ�.
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		//1. ����ؾ��� �̹����� ������ �̹����� �����Ѵ�.
		BitBlt
		(
			_blendImage->hMemDc,
			0, 0,
			sourWidth,	//����� �̹��� ����ũ��
			sourHeight,	//����� �̹��� ����ũ��
			hdc,
			0,0,				//���� ���� ����
			SRCCOPY
		);

		//2. ���� �̹����� ����� ���� �� ������ �̹����� �׸���. 
		GdiTransparentBlt
		(
			_blendImage->hMemDc,
			destX,				//����� ��ǥ ����(x)
			destY,				//����� ��ǥ ����(y)
			sourWidth,	//����� �̹��� ����ũ��
			sourHeight,	//����� �̹��� ����ũ��
			_imageInfo->hMemDc, //����� ��� �޸� DC
			0, 0,				//���� ���� ����
			sourWidth,	//���� ���� ����ũ��
			sourHeight,	//���� ���� ����ũ��
			_transColor			//������ �� ������ ����
		);

		//3. ������ �̹����� ȭ�鿡 �׸���.
		//AlphaBlend(
		//	hdc,
		//	destX, destY,
		//	sourWidth,	//����� �̹��� ����ũ��
		//	sourHeight,	//����� �̹��� ����ũ��
		//	_blendImage->hMemDc,
		//	sourX, sourY,				//���� ���� ����
		//	sourWidth,	//���� ���� ����ũ��
		//	sourHeight,	//���� ���� ����ũ��
		//	_blendFunc
		//);
	}
	else {
		//AlphaBlend(
		//	hdc,
		//	destX, destY,
		//	sourWidth,	//����� �̹��� ����ũ��
		//	sourHeight,	//����� �̹��� ����ũ��
		//	_blendImage->hMemDc,
		//	sourX, sourY,				//���� ���� ����
		//	sourWidth,	//���� ���� ����ũ��
		//	sourHeight,	//���� ���� ����ũ��
		//	_blendFunc);
	}
}

void GImage::frameRender(HDC hdc, int destX, int destY)
{
		if (_isTrans)
		{
			//GdiTransparentBlt(): ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� ����
			GdiTransparentBlt
			(
				hdc,
				destX,
				destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_transColor
			);
		}
		else
		{
			//BitBlt(): DC ���� �������� ���� ���Ӻ��縦 ���ش�.
			//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�.
			BitBlt(hdc, destX, destY, 
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,
				SRCCOPY);
		}
}

void GImage::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = (currentFrameX > _imageInfo->maxFrameX)
								? _imageInfo->maxFrameX : currentFrameX;
	_imageInfo->currentFrameY = (currentFrameY > _imageInfo->maxFrameY)
								? _imageInfo->maxFrameY : currentFrameY;
	if (_isTrans)
	{
		//GdiTransparentBlt(): ��Ʈ���� �ҷ��� �� Ư�� ������ �����ϰ� ����
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else
	{
		//BitBlt(): DC ���� �������� ���� ���Ӻ��縦 ���ش�.
		//SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�.
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDc,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}

}

void GImage::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset���� ������ ��� ����
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC���� ȭ��ũ��
	RECT rcDest;

	//�׷��� �� ��ü ���� ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight) {
		//�ҽ� ������ ����
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� �����ٸ�)
		if (y + sourHeight > drawAreaH) {
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth) {
			//���η���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� �����ٸ�)
			if (x + sourWidth > drawAreaW) {
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�.
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				sourWidth, sourHeight);

		}//End for x

	}//End for y
}

void GImage::loopAlphaRender(HDC hdc, const LPRECT drawRect, int offsetX, int offsetY, BYTE alpha)
{
	//�����Ŷ� �Ȱ��� ���ķ��� 
}

void GImage::aniRender(HDC hdc, int destX, int destY, Animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}