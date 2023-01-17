#include "stdafx.h"
#include "Animation.h"

HRESULT Animation::init(int totalW, int totalH, int frameW, int frameH)
{
    //가로 프레임 수
    _frameWidth = frameW;
    _frameNumWidth = totalW / _frameWidth;
    //세로 프레임 수
    _frameHeight = frameH;
    _frameNumHeight = totalH / _frameHeight;
    //총 프레임 수
    _frameNum = _frameNumWidth* _frameNumHeight;

    _frameList.clear();

    for (int i = 0; i < _frameNumHeight; i++) 
    {
        for (int j = 0; j < _frameNumWidth; j++)
        {
            POINT framePos;
            framePos.x = j * _frameWidth;
            framePos.y = i * _frameHeight;

            _frameList.push_back(framePos);
        }
    }

    setDefPlayFrame();

    return S_OK;
}

void Animation::release(void)
{
    //Do nothing
}

//기본 프레임 세팅
void Animation::setDefPlayFrame(bool reverse, bool loop)
{
    _loop = loop;
    _playList.clear();

    if (reverse)
    {
        if (_loop)
        {
            for (int i = 0; i < _frameNum; i++)
            {
                _playList.push_back(i);
            }

            for (int i = _frameNum - 2; i > 0; i--)
            {
                _playList.push_back(i);
            }
        }//end if loop
        else
        {
            for (int i = 0; i < _frameNum; i++)
            {
                _playList.push_back(i);
            }

            for (int i = _frameNum - 2; i >= 0; i--)
            {
                _playList.push_back(i);
            }
        }//end else loop
    }//end if reverse
    else
    {
        for (int i = 0; i < _frameNum; i++)
        {
            _playList.push_back(i);
        }
    }
}

//원하는 프레임만 재생
void Animation::setPlayFrame(int* playArr, int arrLen, bool loop)
{
    _loop = loop;    
    _playList.clear();

    if (_loop)
    {
        for (int i = 0; i < arrLen; i++)
        {
            _playList.push_back(playArr[i]);
        }
    }//end if loop
    else
    {
        for (int i = 0; i < _frameNum; i++)
        {
            _playList.push_back(playArr[i]);
        }
    }//end else loop
}

//구간을 잘라서 재생
void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
    _loop = loop;
    _playList.clear();

    int firstFrame = start >= 0 ? start : 0;
    int lastFrame = end < _frameNum ? end : _frameNum;
    if (reverse)
    {
        if (_loop)
        {
            for (int i = firstFrame; i < lastFrame; i++)
            {
                _playList.push_back(i);
            }

            for (int i = _frameNum - 2; i > 0; i--)
            {
                _playList.push_back(i);
            }
        }//end if loop
        else
        {
            for (int i = firstFrame; i < lastFrame; i++)
            {
                _playList.push_back(i);
            }

            for (int i = _frameNum - 2; i >= 0; i--)
            {
                _playList.push_back(i);
            }
        }//end else loop
    }//end if reverse
    else
    {
        for (int i = firstFrame; i < lastFrame; i++)
        {
            _playList.push_back(i);
        }
    }
}

void Animation::setFPS(int framePerSec)
{
    _frameUpdateSec = 1.0f / framePerSec;
}

void Animation::frameUpdate(float elapsedTime)
{
    if (_isPlay)
    {
        _elapsedSec += elapsedTime;
        //프레임업데이트시간이 되었으면
        if (_elapsedSec >= _frameUpdateSec)
        {
            _elapsedSec -= _frameUpdateSec;

            _nowPlayIdx++;
            if (_nowPlayIdx == _playList.size())
            {
                if (_loop)
                {
                    _nowPlayIdx = 0;
                }
                else
                {
                    _nowPlayIdx--;
                    _isPlay = false;
                }
            }//end if 인덱스가끝까지
            cout << _nowPlayIdx << endl;
        }//end 프레임업데이트시간이 되었으면
    }
}

void Animation::aniStart(void)
{
    _isPlay = true;
    _nowPlayIdx = 0;
}

void Animation::aniStop(void)
{
    _isPlay = false;
    _nowPlayIdx = 0;
}

void Animation::aniPause(void)
{
    _isPlay = false;
}

void Animation::aniResume(void)
{
    _isPlay = true;
}

Animation::Animation(void) : _frameNum(0),
                             _frameWidth(0),
                             _frameHeight(0),
                             _frameNumWidth(0),
                             _frameNumHeight(0),
                             _frameUpdateSec(0),
                             _elapsedSec(0),
                             _isPlay(false),
                             _loop(false),
                             _nowPlayIdx(0)
{
}
