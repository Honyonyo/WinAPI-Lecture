#include "stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void) {

	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;

    if(managerInit) {
        SetTimer(_hWnd, 0, 10, NULL);

        KEYMANAGER->init();
        RND->init();
        IMAGEMANAGER->init();
        FONTMANAGER->init();
        SOUNDMANAGER->init();  
        TIMEMANAGER->init();
        SCENEMANAGER->init();
    }
        return S_OK;
}

void GameNode::release(void)
{
    if(_managerInit) {
        KillTimer(_hWnd, 0);

        RND->releaseSingleton();
        KEYMANAGER->releaseSingleton();
        IMAGEMANAGER->releaseSingleton();
        SOUNDMANAGER->releaseSingleton();
        IMAGEMANAGER->release();
        FONTMANAGER->release();   
        TIMEMANAGER->release();
        TIMEMANAGER->releaseSingleton();
        SCENEMANAGER->release();

    }

    ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void) {
}

void GameNode::render(void) {
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;        //�ڵ�dc_ GDI�ȿ��ִµ�. png�� �ȵǰ� bmp�� �޾���. GDI+������ϸ� PNG�� ����� �� �ִ�.
    PAINTSTRUCT ps; //����Ʈ����ü
    switch (iMsg) {
    case WM_TIMER:
        this->update();
        break;

    case WM_PAINT:          //��¿� ���� ��� ���� ����Ѵ�(����,�׸�,���� ��� ȭ�鿡 ���̴� ��� ��)
        hdc = BeginPaint(hWnd, &ps);
        this->render();
        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;

    case WM_LBUTTONDOWN:    //��Ŭ���߻�
        break;

    case WM_LBUTTONUP:
        break;

    case WM_RBUTTONDOWN:    //��Ŭ�� �߻� 

        break;

    case WM_KEYDOWN:    //Ű������Ȳ���� �߻�
        switch (wParam) {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMsg, wParam, lParam));

}
