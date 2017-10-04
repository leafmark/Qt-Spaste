#ifndef WIN_H
#define WIN_H
#pragma once

#include <QtWinExtras/qwinfunctions.h>

#ifndef min
    #define min
#endif
#ifndef max
    #define max
#endif

#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "Gdi32.lib")

#include <windows.h>
#include <Gdiplus.h>
#include <comdef.h>
using namespace Gdiplus;

int shotcut(QImage *pimage, int cursor=0);
static int qt_fromWinHBITMAP(HDC hdc, HBITMAP bitmap, int w, int h, QImage *pimage);

#endif // WIN_H

