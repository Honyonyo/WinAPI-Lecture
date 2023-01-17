#include "stdafx.h"
#include "CarRush.h"
HRESULT MainGame::init(void)
{
	original = SelectObject(getMemDC(), GetStockObject(DC_PEN));

	_alphaA = 0;
	_isAlphaIncrease = false;

	_offsetX, _offSetY = 0;
	_bgSpeed = 0;
	_hongheaOn = false;
	_score = 0;
	_endCountdown = 300;

	_genTimer[0] = RND->getFromFloatTo(1, 10) * 1000.0f;
	_genTimer[1] = RND->getFromFloatTo(1, 10) * 1000.0f;
	_genTimer[2] = RND->getFromFloatTo(1, 10) * 1000.0f;
	_genTimer[3] = RND->getFromFloatTo(1, 10) * 1000.0f;



	GameNode::init(true);

	IMAGEMANAGER->addImage("빙산의일각", "Resources/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/Background/asphaltRoad.bmp", WINSIZE_X, 2000);

	IMAGEMANAGER->addImage("넘의차", "Resources/Images/Object/CarGreen.bmp", 0, 0, 80, 160, true, OPACITY_RGB);

	IMAGEMANAGER->addFrameImage("계기판_숫자", "Resources/Images/Object/dashboardNumber.bmp", 100, 20, 5, 1, true, OPACITY_RGB);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

}

void MainGame::update(void)
{
	GameNode::update();
	//계기판속력은 *10하면 된다
	_me.move();
	if ((_me.life <= 0) && _endCountdown > 0) {
		_endCountdown--;
		std::cout << _endCountdown << std::endl;
	}
	else if (_me.life > 0) _endCountdown = 300;


	if (_endCountdown > 0)
	{
		for (short i = 0; i < sizeof(_genTimer) / sizeof(_genTimer[0]); i++)
		{
			_genTimer[i] -= 10;
			if (_genTimer[i] <= 10) {
				_genTimer[i] = RND->getFromFloatTo(1, 10) * 1000.0f;
				genEnemy(i);
				std::cout << "적생성" << i << std::endl;
			}
		}//end for

		moveAndDistroyEnemy();
		if (KEYMANAGER->isOnceKeyDown('S')) {
			_me.shieldcount = _me.shieldSkillTime;
		}

		if (_me.shieldcount > 0) {
			(_me.shieldcount -= 10) < 0 ? _me.shieldcount = 0 : NULL;
		}
		else
		{
			for (int i = 0; i < _enemy.size(); i++)
			{
				RECT impactRc;
				if (IntersectRect(&impactRc, &_me.rc, &_enemy[i].rc)) {
					accident();
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
			if (!_hongheaOn)
			{
				_hongheaOn = true;
			}
		}

		if (_hongheaOn) {
			honghea();
		}

		_bgSpeed -= _me.speed;
	}
	else 		_bgSpeed -= 3;


}

void MainGame::render(void)
{
	//메모리디시에서 hdc로 넘어오는 과정에 문제가 있는건지, 
//memdc부분을 getHDC로 변경하면 출력 잘 된다.. 
	GameNode::render();

	//백버퍼 얻어온다.
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	//IMAGEMANAGER->render("빙산의일각", getMemDC(), 0, 0);
	IMAGEMANAGER->loopRender("배경 루프", getMemDC(),
		&RectMake(0, 0, WINSIZE_X, WINSIZE_Y), 0, _bgSpeed);

	_me.draw(getMemDC());
	if (!_enemy.empty()) {
		for (short i = 0; i < _enemy.size(); i++) {
			_enemy[i].draw(getMemDC());
		}
	}

	drawDashboard(getMemDC());
	drawUI(getMemDC());

	if (_endCountdown <= 0) {
		TextOut(getMemDC(), WINSIZE_X / 2 - 50, WINSIZE_Y / 2 - 10, "GAME OVER", strlen("GAME OVER"));
	}

	this->getBackBuffer()->render(getHDC());
}






void MainGame::accident(void)
{
	_me.crush();
	//_me.shieldcount = _me.shieldCrushTime;
}

void MainGame::genEnemy(short line)
{
	OBJCar enemy(line);
	_enemy.push_back(enemy);

}

void MainGame::moveAndDistroyEnemy()
{
	if (!_enemy.empty()) {
		vector<OBJCar>::iterator iter = _enemy.begin();
		std::cout << "적움직인다" << iter->line << " " << iter->center.x << ", " << iter->center.y << std::endl;
		/*for (iter; iter != _enemy.end();) {
			iter->move();
			if (iter->rc.top > WINSIZE_Y)
			{
				_enemy.erase(iter);
				std::cout << "적파괴" << std::endl;
			}
			iter++;
		}*/
		for (int i = 0; i < _enemy.size();) {
			_enemy[i].move(_me.speed);
			if (_enemy[i].rc.top > WINSIZE_Y)
			{
				_enemy.erase(_enemy.begin() + i);
				_score += 100;
				//std::cout << "적파괴" << std::endl; 
			}
			else i++;
		}
	}
}

void MainGame::honghea()
{
	short push = 10;
	if (!_enemy.empty()) {
		_me.speed = 19;
		for (short i = 0; i < _enemy.size();) {
			if (_enemy[i].center.x < WINSIZE_X / 2) {
				_enemy[i].center.x -= push;
				_enemy[i].rcMake();
				if (_enemy[i].rc.right < 0)
				{
					_enemy.erase(_enemy.begin() + i);
					_score += 50;
				}
				else i++;
			}//End if .x<half
			else {
				_enemy[i].center.x += push;
				_enemy[i].rcMake();
				if (_enemy[i].rc.left > WINSIZE_X)
				{
					_enemy.erase(_enemy.begin() + i);
					_score += 50;
				}
				else i++;
			}
		}//End for i
	}//End if notEmpty
	else {
		_hongheaOn = false;
		_me.speed = 7;
		_genTimer[0] = RND->getFromFloatTo(1, 10) * 1000.0f;
		_genTimer[1] = RND->getFromFloatTo(1, 10) * 1000.0f;
		_genTimer[2] = RND->getFromFloatTo(1, 10) * 1000.0f;
		_genTimer[3] = RND->getFromFloatTo(1, 10) * 1000.0f;
	}
}

void MainGame::drawEnemy(HDC hdc)
{
	if (_enemy.size() > 0) {
		for (int i = 0; i < _enemy.size(); i++) {
			_enemy[i].draw(hdc);
		}
	}
}

void MainGame::drawUI(HDC hdc)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, 0x00ffffff);	//면색
	SetDCPenColor(hdc, COLOR_POINTYELLOW);	//펜색
	RectangleMake(hdc, 10, 10, 210, 35);
	char ui[126];
	sprintf_s(ui, "현재점수 : %-10d 속력 : %-4d", _score, (int)_me.speed * 10);
	TextOut(hdc, 20, 20, ui, strlen(ui));
	SelectObject(hdc, original);
	DeleteObject(GetStockObject(DC_PEN));
	DeleteObject(GetStockObject(DC_BRUSH));

}

void MainGame::drawDashboard(HDC hdc) {
	int dbSize = WINSIZE_X / 5 - 15;
	POINT dbCenter = { WINSIZE_X - dbSize / 2 , WINSIZE_Y - dbSize / 2 };
	drawDashboardFrame(hdc, dbCenter);
	drawDashboardSpit(hdc, dbCenter);
}
void MainGame::drawDashboardFrame(HDC hdc, POINT dbCenter) {
	int dbSize = WINSIZE_X / 5;

	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	SetDCBrushColor(hdc, 0x00686868);	//면색
	SetDCPenColor(hdc, 0x00686868);	//펜색

	Rectangle(getMemDC(), dbCenter.x - dbSize, dbCenter.y, dbCenter.x, WINSIZE_Y);
	EllipseMakeCenter(getMemDC(), dbCenter, dbSize, dbSize);

	dbSize -= 15;
	SetDCBrushColor(hdc, 0x00a7a7a7);	//면색
	SetDCPenColor(hdc, 0x00a7a7a7);	//펜색
	EllipseMakeCenter(getMemDC(), dbCenter, dbSize, dbSize);

	dbSize -= 10;
	SetDCPenColor(hdc, COLOR_POINTYELLOW);	//펜색
	EllipseMakeCenter(getMemDC(), dbCenter, dbSize, dbSize);

	SetDCBrushColor(hdc, COLOR_POINTYELLOW);
	for (int i = 0; i < 19; i++) {
		float dtemp = RAD_NOWSPEED(i * 10);
		if (i % 4 == 0)
		{
			EllipseMakeCenter(getMemDC(), ((dbSize - 20) * cos(dtemp) + dbCenter.x), ((dbSize - 20) * sin(dtemp) + dbCenter.y), 3, 3);
			LineMake(hdc, dbCenter.x + dbSize * cos(dtemp), (dbCenter.y + dbSize * sin(dtemp)),
				((dbSize - 10) * cos(dtemp) + dbCenter.x), ((dbSize - 10) * sin(dtemp) + dbCenter.y));
			int corX = 0, corY = 0;
			if (i <= 10) { corY = 10; }
			else { corX = 10; }
			IMAGEMANAGER->frameRender("계기판_숫자", getMemDC()
				, (int)((dbSize - 30) * cos(dtemp) + dbCenter.x) - corX, (int)((dbSize - 30) * sin(dtemp) + dbCenter.y) - corY
				, i / 4, 0);
			//std::cout << "계기판숫자좌표 "<<(int)(dbSize - 20) * cos(dtemp) + dbCenter.x << ',' << (int)((dbSize - 20) * sin(dtemp) + dbCenter.y)
			//	<< ','<< (int)(i / 4)<<std::endl;
		}
		else
		{
			LineMake(hdc, dbCenter.x + dbSize * cos(dtemp), (dbCenter.y + dbSize * sin(dtemp)),
				((dbSize - 10) * cos(dtemp) + dbCenter.x), ((dbSize - 10) * sin(dtemp) + dbCenter.y));
		}

	}
	SetDCBrushColor(hdc, COLOR_POINTYELLOW);	//면색
	SetDCPenColor(hdc, COLOR_POINTYELLOW);	//펜색

	SelectObject(hdc, original);
	DeleteObject(GetStockObject(DC_PEN));
	DeleteObject(GetStockObject(DC_BRUSH));

}

void MainGame::drawDashboardSpit(HDC hdc, POINT dbCenter) {
	float dtemp = RAD_NOWSPEED(_me.speed * 10);

	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, 0x00ffab03);	//면색
	SetDCPenColor(hdc, 0x00ffab03);	//펜색
	int spitSize = WINSIZE_X / 5 - 50;
	POINT spit[4] = {
		dbCenter,
		{cos(dtemp + 0.2) * 30 + dbCenter.x, sin(dtemp + 0.2) * 30 + dbCenter.y},
		{cos(dtemp) * spitSize + dbCenter.x, sin(dtemp) * spitSize + dbCenter.y},
		{cos(dtemp - 0.2) * 30 + dbCenter.x, sin(dtemp - 0.2) * 30 + dbCenter.y}
	};

	Polygon(hdc, spit, 4);

	SetDCBrushColor(hdc, COLOR_POINTYELLOW);	//면색
	SetDCPenColor(hdc, COLOR_POINTYELLOW);	//펜색

	EllipseMakeCenter(getMemDC(), dbCenter, 7, 7);

	SelectObject(hdc, original);
	DeleteObject(GetStockObject(DC_PEN));
	DeleteObject(GetStockObject(DC_BRUSH));
}

void MyCar::setRc()
{
	rc = RectMakeCenter(center, CAR_SIZE_X, CAR_SIZE_Y);
	hitBox = RectMakeCenter(center, CAR_SIZE_X - 15, CAR_SIZE_Y - 15);
}

void MyCar::move()
{
	if (life > 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			if (rc.right < WINSIZE_X)
			{
				center.x += (CAR_MOVEPOINT + speed / 10);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (rc.left > 0)
			{
				center.x -= (CAR_MOVEPOINT + speed / 10);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			speed += 0.1f;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			speed -= 0.1f;
		}
		//printf("내차 중심점 %d, %d\n", center.x, center.y);
		//printf("내차 이미지 시작점 %d, %d\n", rc.left, rc.top);
		setRc();
	}
	if (KEYMANAGER->isOnceKeyDown('P')) {
		if (++life > 5) life = 5;
	}
	(speed < 0) ? speed = 0 : NULL;
	(speed > 16) ? speed = 16 : NULL;

}

void MyCar::draw(HDC hdc)
{
	IMAGEMANAGER->render("내차", hdc, rc.left, rc.top);
	IMAGEMANAGER->frameRender("생명력", hdc, center.x - 85, rc.top - 30, 0, life);
	(shieldcount > 0) ? IMAGEMANAGER->alphaRender("쉴드", hdc, center.x - 150, center.y - 135, 100) : NULL;
}

void MyCar::crush()
{
	if (--life <= 0) {
		life = 0;
	}
}

void OBJCar::move(float mySpeed)
{
	center.y += (speed + mySpeed);
	rc = RectMakeCenter(center, CAR_SIZE_X, CAR_SIZE_Y);
}

void OBJCar::rcMake()
{
	rc = RectMakeCenter(center, sizeW, sizeH);
	hitBox = RectMakeCenter(center, sizeW - 5, sizeH - 5);
}

void OBJCar::draw(HDC hdc)
{
	IMAGEMANAGER->render("넘의차", hdc, rc.left, rc.top);
}
