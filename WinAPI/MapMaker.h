#pragma once
#include "GameNode.h"

struct TileGrid
{
	RECT rc;
};
struct Tile
{
	GImage* img;
	RECT rc;
	float x, y;
	int row, colunm;
};

class MapMaker : public GameNode
{
private:
	vector<vector<TileGrid>> _vMatrix;
	vector<vector<TileGrid>>::iterator _ivMatrix;

	vector<Tile> _vTile;
	vector<Tile>::iterator _ivTile;

	int _blocksize;
	bool _isTilePick;
	short _tileNumber;
	float* _pX;
	float* _pY;
	RECT* _pTileRC;
	float _distX;
	float _distY;

public:
	HRESULT init(int number);
	void release(void);
	void update(void);
	void render(void);

	void tilePick();
	void tileMove();
	void tileDrop();

	void setGrid(int number);
	void boardReset();
};

