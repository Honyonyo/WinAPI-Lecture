#include "stdafx.h"
#include "MapMaker.h"

HRESULT MapMaker::init(int number)
{
    setGrid(number);
    
    IMAGEMANAGER->addImage("타일이미지", "Resources/Images/Object/shield.bmp", 400, 400);

    //타일생성
    {
        Tile _tile1;
        _tile1.img = IMAGEMANAGER->findImage("타일이미지");
        _tile1.row = RND->getInt(number);
        _tile1.colunm = RND->getInt(number);
        _tile1.rc = _vMatrix[_tile1.row][_tile1.colunm].rc;
        _tile1.x = (_tile1.rc.left + _tile1.rc.right) *0.5;
        _tile1.y = (_tile1.rc.top + _tile1.rc.bottom) *0.5;
        _vTile.push_back(_tile1);

        Tile _tile2;
        _tile2.img = IMAGEMANAGER->findImage("타일이미지");
        _tile2.row = RND->getInt(number);
        _tile2.colunm = RND->getInt(number);
        if (_vTile[0].row == _tile2.row && _vTile[0].colunm == _tile2.colunm)
        {
            if (_tile2.row < _vMatrix.size()) ++_tile2.row;
            else --_tile2.row;
        }
        _tile2.rc = _vMatrix[_tile2.row][_tile2.colunm].rc;
        _tile2.x = (_tile2.rc.left + _tile2.rc.right) * 0.5;
        _tile2.y = (_tile2.rc.top + _tile2.rc.bottom) * 0.5;
        _vTile.push_back(_tile2);
    }

    _isTilePick = false;
    _tileNumber = -1;
    cout << "맵생성완료" << endl;
    return S_OK;
}

void MapMaker::release(void)
{
    _ivTile = _vTile.begin();
    for (; _ivTile != _vTile.end(); _ivTile++)
    {
        _ivTile->img->release();
    }
    SAFE_DELETE(_pX);
    SAFE_DELETE(_pY);
    SAFE_DELETE(_pTileRC);
}

void MapMaker::update(void)
{
    if(!_isTilePick)
        tilePick();

    if (_isTilePick)
    {
        tileMove();
    }
}

void MapMaker::render(void)
{
    for (int i = 0; i < _vMatrix.size(); i++)
    {
        for (int j = 0; j < _vMatrix[0].size(); j++)
        {
            DrawRectMake(getMemDC(), _vMatrix[i][j].rc);
        }
    }
    if (!_vTile.empty())
    {
        _ivTile = _vTile.begin();
        for (; _ivTile != _vTile.end(); _ivTile++)
        {
//           cout << "타일그리기" << endl;
            _ivTile->img->render(getMemDC(), _ivTile->rc.left, _ivTile->rc.top,0,0, _blocksize, _blocksize);
//            printf("타일랜더위치 %d, %d\n", _ivTile->rc.left, _ivTile->rc.top);
        }
    }
//    cout << "맵 랜더" << endl;
}

void MapMaker::tilePick()
{
    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
    {
        _ivTile = _vTile.begin();
        for (int i =0; _ivTile != _vTile.end(); _ivTile++)
        {
            if (PtInRect(&(_ivTile->rc), _ptMouse))
            {
                _isTilePick = true;
                _pX = &_ivTile->x;
                _pY = &_ivTile->y;
                _distX = *_pX- _ptMouse.x;
                _distY = *_pY- _ptMouse.y;
                _pTileRC = &_ivTile->rc;
                _tileNumber = i;
                cout << i+1<<"번째 타일선택" << endl;
                break;
            }
            i++;
        }//end for _vTile
    }//end if LbuutonDown
}

void MapMaker::tileMove()
{
    {
        *_pX = _ptMouse.x + _distX;
        *_pY = _ptMouse.y + _distY;
        *_pTileRC = RectMakeCenter(*_pX, *_pY, _blocksize, _blocksize);
        if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
        {
             tileDrop();
        }
    }
}

void MapMaker::tileDrop()
{
    _ivMatrix = _vMatrix.begin();
    short i = 0;
    short j = 0;
    for ( ; _ivMatrix != _vMatrix.end(); i++)
    {
        vector<TileGrid>::iterator iter = _ivMatrix->begin();
            j = 0;
        for(;iter != _ivMatrix->end();j++)
        {
            if (PtInRect(&iter->rc, { (long)*_pX, (long)*_pY }))
            {
                *_pTileRC = iter->rc;
                *_pX = (iter->rc.left + iter->rc.right) / 2;
                *_pY = (iter->rc.top + iter->rc.bottom) / 2;
                _ivMatrix = _vMatrix.end()-1;
                _vTile[_tileNumber].row = i;
                _vTile[_tileNumber].colunm = j;
                cout <<"이동 " << i << ", " << j << endl;
                break;
            }
            iter++;
        }//end for Colunm
        _ivMatrix++;
    }
    if (i >= _vMatrix.size() && j >= _vMatrix[0].size())
    {
        *_pTileRC = _vMatrix[_vTile[_tileNumber].row][_vTile[_tileNumber].colunm].rc;
        *_pX = (_vMatrix[_vTile[_tileNumber].row][_vTile[_tileNumber].colunm].rc.left + _vMatrix[_vTile[_tileNumber].row][_vTile[_tileNumber].colunm].rc.right) / 2;
        *_pY = (_vMatrix[_vTile[_tileNumber].row][_vTile[_tileNumber].colunm].rc.top + _vMatrix[_vTile[_tileNumber].row][_vTile[_tileNumber].colunm].rc.bottom) / 2;
    }
    _tileNumber = -1;
    _distX = 0;
    _distY = 0;
    _isTilePick = false;
    _pX = _pY = nullptr;
    _pTileRC = nullptr;
}

void MapMaker::setGrid(int number)
{
    {    //윈도우 가로세로중에 작은거에 맞춰서 정사각형 한 변의 길이를 만든다
        if (WINSIZE_X > WINSIZE_Y)
            _blocksize = WINSIZE_Y / number;
        else
            _blocksize = WINSIZE_X / number;

        cout << "블록 1칸 사이즈 " << _blocksize << endl;
        for (int i = 0; i < number; i++)
        {
            vector<TileGrid> _vColunm;
            for (int j = 0; j < number; j++)
            {
                TileGrid grid;
                ZeroMemory(&grid, sizeof(TileGrid));
                grid.rc = RECTMakeLT(i * _blocksize, j * _blocksize, _blocksize, _blocksize);
                _vColunm.push_back(grid);
            }//end for j
            _vMatrix.push_back(_vColunm);
        }//end for i
    }
}

void MapMaker::boardReset()
{
    vector<Tile> tmpTile;
    _vTile.clear();
    tmpTile.swap(_vTile);
    vector<vector<TileGrid>> tmpMat;
    tmpMat.swap(_vMatrix);
    _vMatrix.clear();
}
