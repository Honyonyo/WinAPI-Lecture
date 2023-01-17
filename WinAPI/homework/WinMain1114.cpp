#include "stdafx.h"
#include "Rect_.h"
//미완성과제. 이상해!
HINSTANCE _hInstance;                      
HWND _hWnd;                                        
POINT _ptMouse = { 0,0 };
short _mouseMoveX;
short _mouseMoveY;
Rect_ rc1_;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdParam,
    int       nCmdShow)
{
    _hInstance = hInstance;

    WNDCLASS wndClass;

    //메모리
    wndClass.cbClsExtra = 0;                                                    //클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                                    //윈도우 여분 메모리
    //화면
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               //백그라운드. 페이드 인아웃이 들어갈 수 있도록 여지를 준 get stock object
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                             //마우스커서. 아이콘 이미지 기본화살표 그냥 쓸꺼양
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //아이콘. 안쓸건데, 기본지원으로 그냥 세팅해둬.
    //윈도우 정보, 속성
    wndClass.hInstance = hInstance;                                             //윈도우를 소요한 프로그램의 식별자 정보
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    //윈도우 프로시져(현재 프로젝트에서 사용할)
    wndClass.lpszClassName = WIN_NAME;                                        //클래스 이름 (윈도우 클래스 식별자 정보)

    wndClass.lpszMenuName = NULL;                                               //메뉴 이름. 지금 안쓸꺼야~
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   //윈도우 스타일 (윈도우 다시그리기 정보)

    //1-2. 윈도우 클래스 등록
    RegisterClass(&wndClass);

    //1-3. 화면에 보여줄 윈도우 창 생성
    _hWnd = CreateWindow    //사용하는 일이 많으므로 친구하자^^
    (
        WIN_NAME,     //윈도우 클래스 식별자
        WIN_NAME,     //윈도우 타이틀 바 이름
        WINSTYLE,    //윈도우 스타일
        WINSTART_X,            //윈도우 화면 X좌표. 내가 만든 창이 뜨는 모니터 화면 위치
        WINSTART_Y,            //윈도우 화면 Y좌표. 내가 만든 창이 뜨는 모니터 화면 위치
        WINSIZE_X,            //윈도우 화면 가로크기
        WINSIZE_Y,            //윈도우 화면 세로크기
        NULL,//부모 윈도우 지정 여부 (없으면 NULL, 그치만안정성높은건 GetDesktopWindow())
        (HMENU)NULL,    //메뉴 핸들
        hInstance,      //인스턴스 지정
        NULL            //윈도우의 자식 윈도우를 생성하면 지정하고 아니라면 NULL_아마 메세지창..?경고창/
                            //필요에 의해서 사용. 지금은 null
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    //1-4. 화면에 윈도우 창 보여주기
    ShowWindow(_hWnd, nCmdShow);


    MSG message;
    /*
    게임용~
        while (true) {
            if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
                if (message.message == WM_QUIT)break;
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
    */

    while (GetMessage(&message, 0, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return (int)message.wParam;
}

char strPT[100];
short count=0;
LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wparam, LPARAM lparam) {
    HDC hdc;        //핸들dc_ GDI안에있는데. png는 안되고 bmp만 받아줌. GDI+를사용하면 PNG를 사용할 수 있다.
    PAINTSTRUCT ps; //페인트구조체

    switch (imsg) {
    case WM_CREATE:
        hdc = BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
        break;

    case WM_PAINT:         
        hdc = BeginPaint(hwnd, &ps);
        wsprintf(strPT, "(%-10d, %-10d)", _ptMouse.x, _ptMouse.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        rc1_.draw(hdc);

        EndPaint(hwnd, &ps);
        break;

    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lparam);
        _ptMouse.y = HIWORD(lparam);
        wsprintf(strPT, "(%-10d, %-10d) %d", _ptMouse.x, _ptMouse.y);
        hdc = GetDC(hwnd);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        rc1_.draw(hdc);
        break;

    case WM_LBUTTONDOWN:    //좌클릭발생        
        //rc1_.click(_ptMouse,hdc);
        InvalidateRect(hwnd, NULL, true);
        hdc = BeginPaint(hwnd, &ps);
        rc1_.drag(_ptMouse, hdc);
        //wsprintf(strPT, "(%-10d, %-10d) %d", rc1_.getPoint().x, rc1_.getPoint().y, count++);
        //TextOut(hdc, 10, 40, strPT, strlen(strPT));
        //rc1_.draw(hdc);

        rc1_.draw(hdc);
        wsprintf(strPT, "(%-10d, %-10d) %d", rc1_.getPoint().x, rc1_.getPoint().y, rc1_.getClicked());
        TextOut(hdc, 10, 40, strPT, strlen(strPT));

        EndPaint(hwnd, &ps); 
        break;

    case WM_LBUTTONUP:
        rc1_.drop();
        break;

    case WM_RBUTTONDOWN:    //우클릭 발생 

        break;

    case WM_KEYDOWN:    //키눌린상황에서 발생
        switch (wparam) {
        case VK_LEFT:
            hdc = GetDC(hwnd);
            SetTextColor(hdc, RGB(0, 0, 255));

            ReleaseDC(hwnd, hdc);
            break;
        case VK_RIGHT:
            break;
        case VK_ESCAPE:
            PostMessage(hwnd, WM_DESTROY, 0, 0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hwnd, imsg, wparam, lparam));
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width, height };
    //실제 윈도우 크기 조정
    //AdjustWindowRect(대상 객체, 사용할윈도우스타일, 메뉴 여부)
    AdjustWindowRect(&rc, WINSTYLE, false);

    //얻어온 렉트정보로 윈도우 사이즈 셋팅
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        (SWP_NOZORDER | SWP_NOMOVE));
}
//zorder 겹쳐있는 뒤에거를 어떻게 처리할지
