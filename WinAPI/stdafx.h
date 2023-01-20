#pragma once
//PreCompiledHeader PCH

//4005 : DXGI등 그래픽 인터페이스에서 매크로 관련하여 많이 출력되는 경고
//프로젝트 속성 고급에서 설정 가능
#pragma warning(disable : 4005)

//프로그램에서 지원할 OS에 따라 Windows헤더이서 코드에 포함될 함수, 상수등을 제어하는데 사용이 된다.
#include <SDKDDKVer.h>

//거의 사용하지 않는 내용은 Windows헤더에서 제외
#define WIN32_LEAN_AND_MEAN
//GDI+를 사용하려면 헤더파일 꺼내와야한다.
//<ole2.h>

//!Windows헤더파일
#include <Windows.h>
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib ,"winmm.lib")
//#pragma comment (lib ,"FMOD/lib/x64/FOMD/fmodex_vc.lib")
#pragma comment (lib ,"FMOD/lib/FMOD/fmodex64_vc.lib")
#pragma comment(lib, "JsonCPP/lib_json/json_vc71_libmtd.lib")
//json_vc71_libmtd

//! 외부 헤더파일
#include "FMOD\inc\FMOD\fmod.hpp"
#include "JsonCPP/include/json/json.h"

//!C 런타임 헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>	//메모리조작함수
#include <tchar.h>	//문자셋을 변경해주는 자료메모리
#include <time.h>
#include <mmsystem.h>

/*
MBCS(Multi Byte Character Set)
	멀티바이트
	: 기존에 사용하던 문자열.
	  아스키코드에 포함되는 문자는 1바이트,
	  포함되지 않는 문자는 2바이트를 차지한다.

WBCS(Wide Byte Character Set)
	유니코드
	: 모든 문자를 2바이트로 처리한다.

VS에서의 문자표현
	MBCS/WBCS중 어느것을 사용할 것인지 명시해줘야한다.
	멀티바이트 : 문자열을 ""로 감싼다.
	유니코드 : 문자열을 ""로 감싸고 L을 붙인다.

	유니코드<->멀티바이트 이식을 위해서는 문자열 표현방식을 다 변경해줘야하기 때문에
	중간매크로형인 _T를 사용한다.


*/

//!C++런타임 헤더파일
#include <fstream>
#include <iostream>
#include <functional>
/*
c++ 11에서 추가된 시간 관련 라이브러리
기존 c런타임에서 제공하는 time함수보다 더 다양하고 확장된 기능 제공
(tiome 초안위
os와 독립적으로 적용
*/


#include <chrono>
#include <random>	//메르센트위스터 난수
#include <vector>	//동적배열
#include <list>
#include <map>		//레드블랙트리를 기반으로 키와 밸류를 가지는 자료형
#include <queue>
/*
unordered_map : Hash자료구조
중복된 데이터를 허용하지 않는다.
단 유사 데이터가 많을시 (key)해시충돌이 발송해 성능저하
*/

#include <unordered_map>	//
#include <string>	//문자열 라이브러리
//bitset : 비트연산을 좀 더 쉽게 관리해주는 함수를 지원한다. (STL)
//	ㄴ reset(), set() flip(), all(), any(), size()등등을 비트연산에 한해 지원하고있다.
#include <bitset>	//전역에 namespace std; 하면 모든거 앞에 std그거그거하니까... 

using std::vector;
using std::list;
using std::map;
using std::string;
using std::bitset;

using std::cout;
using std::endl;

#include <cassert>	//추후 설명해주세요


/*
//! D2D, D3D 헤더파일
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>		//3d11에서는 섀이더 안써도 등록필
#include <dinput.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dinput8.lib")	//입력관련
#pragma comment(lib,"dxguid.lib")	//라이브러리링크

//png렌더가 가능한 d2d팩토리만 추가해서 야매로 사용하기 쌉가능
ID2D1Factory*			_ID2DFactory = nullptr;
ID2D1HwndRenderTarget*	_ID2DRenderTarget = nullptr;
*/

/* 사용자 정의 헤더파일 */
//상호포함관계로 거대하게 묶어주기 때문에 여기다가 include 한 것 뿐이더라도 comm~에 windows.h가 include된것과 같은 효과를 줌
#include "GImage.h"
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "JsonSaveLoader.h"

using namespace MY_UTIL;

// # 싱 글 톤 #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define TIMEMANAGER TimeManager ::getSingleton() // 타임매니저
#define SCENEMANAGER SceneManager ::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()

// # 매크로 # 윈도우 창 초기화
//전체화면
//#define FULL_SCREEN

#ifdef FULL_SCREEN
#define WIN_NAME	(LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X	0
#define WINSTART_Y	0
//GetSystemMetrics : 인자로 전달되는 시스템설정정보를 반환한다.
	//SM_CXSCREEN/ SM_CYSCREEN현재 화면 기준 해상도 x / y축 반환
#define WINSIZE_X	GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	GetSystemMetrics(SM_CYSCREEN)
//					팝업 윈도우 생성 | 윈도우사이즈 최대화
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE
#else
#define WIN_NAME	(LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X	400
#define WINSTART_Y	0
#define WINSIZE_X	600
#define WINSIZE_Y	800

// WS_CAPTION 타이틀바를 가지기 위한 옵션
// WS_SYSMENU 제목표시줄에 컨트롤메뉴상자창을 만드는 옵션( _ ㅁ X )
#define WINSTYLE	WS_CAPTION | WS_SYSMENU
#endif // 0


// # 매크로 함수 #
#define SAFE_DELETE(p)	{if(p){delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)		{if(p){(p)->release();(p)=nullptr;}}

// # 전역 변수 #
// extern : 다른 헤더, 혹은 cpp에서 변수를 공유하기 위해 사용한다.
// 전역변수는 키워드를 생략해도 기본으로 extern화 되는 경우도 있다(vs버전에 따라 다름)
extern HINSTANCE	_hinstance;
extern HWND			_hWnd;

//int x, int y말고 POINT.x, POINT.y
extern POINT		_ptMouse;

