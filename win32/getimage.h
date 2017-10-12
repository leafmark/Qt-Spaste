#ifndef WIN_H
#define WIN_H
#pragma once

#include "QDebug"
#include <QAbstractNativeEventFilter>
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
#include <tchar.h>
using namespace Gdiplus;

int shotcut(QImage *pimage, int cursor=0);
static int qt_fromWinHBITMAP(HDC hdc, HBITMAP bitmap, int w, int h, QImage *pimage);
/*
extern int Globle_HotKeyId;
class NativeEventFilter : public QAbstractNativeEventFilter
{
public:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;
};
*/
#endif // WIN_H

