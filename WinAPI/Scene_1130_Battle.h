#pragma once
#include "GameNode.h"
#include "Charactor.h"
/*
����2.ĳ���� ���� / ���
�ʼ� : �̹���, ���, ü�¹�, �÷��̾�(��� ���� ���), ��(���, ����, �ǰ�)
�⺻������ ��������ó�� ��ġ�Ѵ�. (+ü�¹�)
�÷��̾�(1p)�� ���� �� �� �� �� �ְ�, ���� ����ƺ�� �����Ѵ�.
����ƺ�� ���� �� �ǰ� ����� �����Ѵ�. (+���)
�÷��̾�� ������� < ->���� ���� on / off��ɸ�(�̵�x)
	����, ���, �ǰݵ��� �߻��ϸ� ��Ȳ�� �´� ����� ȭ�鿡 ������
	(�±� ������ ġ��Ÿ ��)
	������ ǥ���Ѵ�.
*/


class HomeWork : public GameNode
{
private:
	Charactor _scarecrow;
	Player* _plyr;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

