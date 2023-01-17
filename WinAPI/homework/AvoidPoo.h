#pragma once
#include "Poo.h"
class Homework
{
private:
	Poo poo;
	Poople poople;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

};

