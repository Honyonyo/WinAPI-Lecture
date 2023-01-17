#pragma once
#include "GameNode.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define PI 3.141592653f
//���� -> ����
#define DEGREE_TO_RAIDAN(_dgr) (M_PI * (_dgr) / 180.0f )
//���� -> ����
#define RADIAN_TO_DEGREE(_rdn) (M_PI / (_rdn) * 180.0f )

#pragma region �ﰢ�Լ�
/*
	������ �� �� ����!
	�Ÿ��� ���Ҷ� ����!

	�� �ﰢ�Լ���?
	�����ﰢ���� ���� ���� �ﰢ�� ������ ���̺�� ��Ÿ���� �Լ�
	���Ӱ����� �ϴ� ���������� �������̿��� �� �ﰢ�Լ��� �̿��ϸ� ���� ����,
		- �߻�ü�� ����, ĳ������ �밢�� �̵�(3d���� �ʼ�), ��ų�������� ���.

	�ػﰢ�Լ� �ϸ� ����� ������!
	 * ����		l
	 ** �뺯		h
	 *** �غ�	b
	sin cos tan
		1. sin : ������ ������ ������ �����ִ� �Լ�
			sin��=�뺯 / ����= h/l
		2. cos : ������ �غ��� ������ ������ִ� �Լ�
			cos�� = �غ� / ����
		3. tan : �غ��� �뺯�� ������ �����ش�.
			tan�� = �غ� / �뺯
	��,,��,, 0 30 45 60 90
			https://t1.daumcdn.net/cfile/tistory/99184D445B7ED68B0D

	�� ���α׷��ֿ����� �ﰢ�Լ�
	- API������ ������ ��ǥ�踦 ����Ѵ�.
	- ������ ��ǥ��� ��ī��Ʈ ��ǥ��ʹ� �޸� y���� �Ʒ��� ������ �����Ǳ� ������
		y�� ��ǥ�� ���ϱ� ���ؼ��� ���ٸ� ó���� ���� ���� sin �տ� -�� ���̰ų� ���� +180�� �ִ´�.

	�� ����ؾ� �� ����
	- ȣ���� : ������ ��Ÿ���� ǥ������� �ϳ���, ȣ�� ���̷� ������ ǥ���ϴ� ���
		PI�� ����� 180�� ������ ǥ���ϴ� ��
		��ǻ�ʹ� ������ �ν��� �� *���� ����� �� ����.
		*�������� ���̿� ���� ȣ�� ���� �߽ɰ� = 1ȣ��(����)

	- ���� : ȣ������ ����� �� ǥ���ϴ� ���� ����
		�������� ȣ�Ǳ��̰� �������� ������ 1�����̶�� �Ѵ�,
		(�뷫 1���� = 57.3��)

	- �� : ���������� ���Ǵ� ���� ����
		������ / ����ǥ���� �Ҹ���.
		�ѹ��� = 360��

	- 60�й�
		���� �ѷ��� 360����Ͽ� ���� ũ�⸦ ��Ÿ���� ���
		PI = 3.14
		���� �ѷ� = r*2*PI
		���� ���� = r^2 * PI

				>>PI�� ���Ȱ��� 180��.
				(�Ʒ��� ���� ������ ������ �� �ִ�.)
				-Degree
				 180 Degree		= PI Radian
				 1	Degree		= PI /180 Radian
				 x	Degree		= x * PI / 180 Radian

				 - Radian
				  PI Radian		= 180 Degree
				  1 Radian		= 180 / PI Degree
				  x Radian		= x * 180 / PI Degree

				 ->��ä�� ��翡�� ������, ȣ, �߽ɰ� 3�����߿� 2������ �� �� �ִٸ� ������ �ϳ��� ���� �� �ִ�.

	�� �˸� ���� ���нĵ�
		�� �� �� �����ǰŸ�
			- �� ���� �ȴ� -> ������ �Ÿ��� �ȴ� -> ��ǥ�������� ���������� ����
			- �� �������� �� �� (x, y) ������ ��Ÿ���� ���Ѵ�.
				DeltaX, DeltaY (���̷�)

		�� �밢�� (����)�� �Ÿ�
			Distance (����) = sqrt(DeltaX^2 + DeltaY^2)
				*sqrt(a) = a�� ������
		�� ���� ���Ѵ�. (������ �������)
			float angle = acos (DeltaX/Distance);
				�ﰢ�Լ� : ������ �־ �������
				���ﰢ�Լ� : ������� �־ ������ ���
				*���ﰢ�Լ��� arc�Ǵ� a�� �տ� ǥ����.

			- ������ ���� ���̷��� ���Ѵ�.
				float DeltaX = cas(Radian) * Distance(�̵���);
				float DeltaY = -sin(Radian) * Distance(�̵���);

		�� x�� ��ǥ���ϱ�
			x = cos��(radian) * �ӵ�

		�� y�� ��ǥ���ϱ�
			y = -sin��(radian) * �ӵ�

*/

#pragma endregion


struct STAR {
	int x;
	int y;
};

class MainGame : public GameNode
{
private:
	int _count;
	bool _isLeft;
	float _radian;
	float _degree;

	HPEN _currentStarPen;
	STAR _star[5];

	SYSTEMTIME _st;			//�ð����� ����ü

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};

