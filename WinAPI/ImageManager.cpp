#include "Stdafx.h"
#include "ImageManager.h"

HRESULT ImageManager::init(void)
{
	// ! Do nothing
	return S_OK;
}

void ImageManager::release(void)
{
	this->deleteAll();
}

GImage* ImageManager::addImage(string strKey, int width, int height)
{
	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{

	GImage* img = findImage(strKey);

	if (img) return img;

img = new GImage;
if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
{
	SAFE_DELETE(img);
	return nullptr;
}

_mImageList.insert(make_pair(strKey, img));

return img;
}

GImage* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{

	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{

	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{

	GImage* img = findImage(strKey);

	if (img) return img;

	img = new GImage;
	if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

GImage* ImageManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}
	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();
	for (;iter != _mImageList.end();){
		if (iter->second != nullptr) {
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
	}
}
		


	_mImageList.clear();
	return false;
}

void ImageManager::render(string strKey, HDC hdc)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc,destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	GImage* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc,destX, destY,alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int soutHeight, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX,sourY, sourWidth, soutHeight, alpha);

}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	GImage* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY,currentFrameX, currentFrameY);
}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	GImage* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void ImageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	GImage* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY,alpha);
}



//GImage* ImageManager::findImage(string strKey)
//{
//    auto key = _nImageList.find(strKey);
//
//    if (key != _nImageList.end()) {
//        return key->second;
//    }
//    return nullptr;
//}
//
//bool ImageManager::deleteImage(string strKey) {
//    auto key = _nImageList.find(strKey);
//
//    if (key != _nImageList.end()) {
//        return key->second->release();
//        SAFE_DELETE(key->second);
//        _nImageList.erase(key);
//
//        return true;
//    }
//    return nullptr;
//
//}
//
//GImage* ImageManager::addImage(string strKey, int width, int height)
//{
//    GImage *img = findImage(strKey);
//
//    if (img) return img;
//
//    img = new GImage;
//    if (FAILED(img->init(width, height))) {
//        SAFE_DELETE(img);
//        return nullptr;
//    }
//
//    _nImageList.insert(make_pair(strKey, img));
//
//    return nullptr;
//}
//
//GImage* ImageManager::addImage(string strKey, const char* fileName, int width, int height)
//{
//    GImage* img = findImage(strKey);
//
//    if (img) return img;
//
//    img = new GImage;
//    if (FAILED(img->init(fileName, width, height))) {
//        SAFE_DELETE(img);
//        return nullptr;
//    }
//
//    _nImageList.insert(make_pair(strKey, img));
//
//    return nullptr;
//}
//
//GImage* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height)
//{
//    GImage* img = findImage(strKey);
//
//    if (img) return img;
//
//    img = new GImage;
//    if (FAILED(img->init(fileName,x, y, width, height))) {
//        SAFE_DELETE(img);
//        return nullptr;
//    }
//
//    _nImageList.insert(make_pair(strKey, img));
//
//    return nullptr;
//}
//
//GImage* ImageManager::addImage(const char* fileName, float x, float y, int sidth, int height, bool isTrans, COLORREF transColor)
//{
//    return nullptr;
//}
//
//GImage* ImageManager::addImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
//{
//    return nullptr;
//}
//
//
//GImage* ImageManager::addImage(const char* fileName, float x, float y, int sidth, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
//{
//    return nullptr;
//}
