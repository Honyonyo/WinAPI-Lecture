#pragma once
#pragma region 객체지향 4대 특징 및 5대 설계원칙
/*
▶ 객체지향 프로그래밍(Object Oriented Programing)
	- 코드의 재사용성이 높고 고트 관리가 용이하다.
	- 신뢰성이 높은 프로그래밍 작성을 가능하게 한다.
		(일반화된 프로그래밍)

★▶ 객체지향 4대 특징
	1. 캡슐화(접근지정자 사용. / 은닉화는 완전은폐숨기기, 캡슐화는 보호하기)
		객체의 속성을 보호한다 (다이렉트로 뜯지 않게 되어 보호하게된다.)

	2. 상속
		객체지향에서 상속이란 하위로 내려갈 수록 좀 더 구체화 되는 것을 의미함.
		재사용성 향상/확정성 증가/ 유지보수효율 UP

	3. 다형성
		다양한 형태로 변할 수 있다. (override)
		
	4. 추상화
		공통적인 부분과 특정 특성을 분리 빛 추출해 재조합하거나 재구성하는 행위.
			(다형성 + 상속은 모두 추상화에 속한다.)

★▶ 객체지향 5대 설계 원칙 SOLID
	1. SRP
		"단일 책임의 원칙"
		결합도를 낮추고 응집도를 높혀라
		상속과 오버라이딩

		- 결합도
		모듈간의 상호 의존 정도를 나타내는 지표
		결합도가 낮아지면 상호 의존성이 줄어들어서 재사용 및 유지보수가 편리하다.

		- 응집도
		하나의 모듈 내부에 존재하는 구성요소들의 기능적 관련성
		응집도가 높은 모듈(Class, ... )은 하나의 책임에 집중할 수 있고, 독립성이 높아져 재사용과 유지보수가 편리하다.
		
	2. OCP
		"개방 폐쇄의 원칙"
		자신의 확장에는 열려있고 주변의 변화에는 닫혀있어야한다. 라는 원칙
		 - 순수가상함수로 이루어져있는 '인터페이스' 에 무조건 적용됨
			인터페이스를 상위 클래스 또는 중간에 두어 자신의 변화에 대해서는 폐쇄한다.
			인터페이스는 외부의 변화에 대해 확장성을 개방한다.

	3. LSP
		"리스코프 치환의 법칙"
		코드의 재사용성
		하위 타입은 언제나 자신의 기반이 되는 상위타입으로 교체될 수 있어야한다.

		상위 : 운송수단, 자동차 / 아반떼, 그랜져, 제네시스, ...

	4. ISP
		"인터페이스 분리의 법칙"
		클라이언트는 자신이 사용하지 않는 함수 또는 메서드에 의존관계를 맺으면 안된다.
		인터페이스로 각 기능을 분리하여 사용하는 함수 또는 메서드에만 의존관계를 형성한다.
		현재 만들어지고있는 프로젝트의 설계 방식에 따라 SRP 혹은 ISP 를 선택한다.

	5. DIP
		"의존관계 역전의 법칙"
		자신보다 변하기 쉬운것에 대해 의존하지 말아야한다.
			(자식이 부모/추상클래스에 영향 끼치지 말아야 안정적)
*/
#pragma endregion

/*관리자설명*
!!!관리자!!!
윈도우프로시저를 캡슐화했으나 우리가 사용을 하긴 해야함. 그래서 꺼내다쓸 상속받은MG를 생성했고,
관리자권한과 시동코드를 MG에 부여해서 필요할 때 Node를 발동시킬 수 있게 하는 것.
*/

// 전역변수
static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
	//순수가상함수 + 멤버변수 : 추상클래스 Abstract Class
	//특징:객체를 생성할 수 없다. (단 포인터 변수는 만들 수 있다.)
	//	추상클래스로 지정한 객체 또는 클래스는 인스턴스를 만들 수 없다.
	//	추상클래스의 자식클래스를 통해 인스턴스를 생성한다.
	//멤버 변수, 일반 멤버함수 포함여부와 상관없이 순수가상함수를 1개이상 가지고있다면 순수가상함수.
	//순수가상함수로만 이루어짐 : 인터페이스
private : 
	HDC _hdc;
	bool _managerInit;

public:
	//함수가 성공적으로 실행되었는지 체크
	//32비트 wjdtn(음수가 아닌 값은 성공, 음수 실패)
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	GImage* getBackBuffer(void) { return _backBuffer; }

	//메모리DC얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC얻기(화면DC)
	HDC getHDC() { return _hdc; }
	
	//메인프로시저
	//lresult callback의 반환으로 많이 사용됨
	//메세지 처리를 마친 후 os에게 신호를 주기 위한 값
	//	스위치에서 각 메세지에 대한 처리값을 -1 0 1로 운영체제에 어떤 작업을 해야하는지 알려준다.
	//	0을 반환하면 모든 메세지가 처리되었다는 의미.
	LRESULT MainProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	/*
	<순수가상함수>
	부모클래스에서 순수가상함수를 선언한다면 자식클래스에서는 반드시 재정의한 함수를 멤버로 가지고있어야한다.
		ㄴ 만드는 법
	virtual void IFunctionA() = 0;
	virtual void IFunctionB() = NULL;
	virtual void IFunctionC() PURE;
	virtual void IFunctionD() abstract;

	개방폐쇄 원칙 . 자신의 확장에는 열려있고, 주변의 변화에는 닫혀있다
	순수가상함수로 이루어진 클래스를 인터페이스라고 한다.
	클래스에서 반드시 정의해야할 함수를 정해주는 클래스
	c++언어는 인터페이스라는 개념을 공식적으로 지원하진 않는다.
	표기법 : 파스칼
	인터페이스(순수가상함수설계)->(상속) 추상클래스(기본기능구현)->(상속)일반 클래스

	멤버변수 및 함수를 포함할 수 없다(정적 함수 포함)
	속성을 정의하는 한정자를 사용할 수 없다. const, ...
	기본클래스를 상속받을 수 없다.
	순수가상함수만 포함시켜야한다.
	생성자/소멸자/연산자를 포함할 수 없다.
	public 속성을 가지고있어야 한다. 재정의를 위해.

	class IClass {
public:
	void idle();
	void attack();
};

class CharacterChoices abstract : IClass {
	virtual void character();
};

class Warrior : public CharacterChoices {

public: virtual void idle();
};

	인터페이스 한줄조사
	<장점 : 다중상속필수
	단점
	가상소멸자>

	*/

	GameNode() {};

	//가상소멸자!
	virtual ~GameNode() {};
};

