#include "stdafx.h"
#include "FontManager.h"

HRESULT FontManager::init(void)
{
    std::cout << "loard fontmanager OK" << std::endl;
    return S_OK;
}

void FontManager::release(void)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName,
    int fontHeight, int fontWeight, char* printString, int length, COLORREF color)
{
   // std::cout << "drawText char*" << std::endl;
    SetBkMode(hdc, TRANSPARENT);
    //색설정
    COLORREF oldTextColor = GetTextColor(hdc);
    SetTextColor(hdc, color);

    //폰트설정
    HFONT font;
    HFONT oldFont;
    font = CreateFont
                    (fontHeight, 0, 0, 0, fontWeight,
                        0, 0, 0,
                        HANGUL_CHARSET, 0, 0, 0, 0, TEXT(fontName)
                    );	//HANGUL_CHARSET : 멀티바이트  HANGEUL_CHARSET : 유니코드
    oldFont = (HFONT)(SelectObject(hdc, font));
    int endTextX = WINSIZE_X - destX - fontHeight;
    char buffer[256];
    buffer[255] = NULL;
    strcpy_s(buffer, strlen(buffer), printString);
    //char a[3];
    //a[2] = NULL;
    //for(int i = 0; i<length; i++)
    //{
    //    a[0] = buffer[i*2];
    //    a[1] = buffer[i*2 +1];
    //    TextOut(hdc, destX + fontHeight*i, destY, a, 2);
    //}
    TextOut(hdc, destX, destY, printString, length);
    SetTextColor(hdc, oldTextColor);
    SelectObject(hdc, oldFont);
    DeleteObject(font);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontHeight, int fontWeight, LPCWSTR printString, int length, COLORREF color) {
   // std::cout << "drawText LPCSTR" << std::endl;
   // std::cout << "drawText LPCWSTR*" << std::endl;
    SetBkMode(hdc, TRANSPARENT);
    //색설정
    COLORREF oldTextColor = GetTextColor(hdc);
    SetTextColor(hdc, color);

    //폰트설정
    HFONT font;
    HFONT oldFont;
    font = CreateFont
    (fontHeight, 0, 0, 0, fontWeight,
        0, 0, 0,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(fontName)
    );	//HANGUL_CHARSET : 멀티바이트  HANGEUL_CHARSET : 유니코드
    oldFont = (HFONT)(SelectObject(hdc, font));
    int endTextX = WINSIZE_X - destX - fontHeight;

        TextOutW(hdc, destX, destY, printString, wcslen(printString));

    SetTextColor(hdc, oldTextColor);
    SelectObject(hdc, oldFont);
    DeleteObject(font);

}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontHeight, int fontWeight, LPCWSTR* printString, int length, COLORREF color)
{
    //std::cout << "drawText LPCWSTR*" << std::endl;
    SetBkMode(hdc, TRANSPARENT);
    //색설정
    COLORREF oldTextColor = GetTextColor(hdc);
    SetTextColor(hdc, color);

    //폰트설정
    HFONT font;
    HFONT oldFont;
    font = CreateFont
    (fontHeight, 0, 0, 0, fontWeight,
        0, 0, 0,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(fontName)
    );	//HANGUL_CHARSET : 멀티바이트  HANGEUL_CHARSET : 유니코드
    oldFont = (HFONT)(SelectObject(hdc, font));
    int endTextX = WINSIZE_X - destX - fontHeight;

    for(int i = 0 ; i <sizeof(*printString)/sizeof(printString[0]); i++)
    {
        TextOutW(hdc, destX, destY + fontHeight * i, printString[i], wcslen(printString[i]));
    }

    SetTextColor(hdc, oldTextColor);
    SelectObject(hdc, oldFont);
    DeleteObject(font);

}