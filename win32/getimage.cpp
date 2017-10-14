#include "./win32/getimage.h"

bool shotcut(QImage *image, int cursor)
{
    HWND pDesktop;		//桌面窗口句柄
    RECT re;			//桌面窗口尺寸
    HDC pdeskdc;		//桌面窗口的内存画板
    HDC hMemDc;			//截图的内存画板
    HBITMAP hBmp;		//截图的位图句柄
    HBITMAP hOldBmp;	//被取代的对象的句柄

    pDesktop=GetDesktopWindow();        //获取桌面窗口句柄
    pdeskdc = GetDC(pDesktop);			//获取桌面窗口的内存画板
    GetClientRect(pDesktop,&re);		//获取桌面窗口的尺寸
    LONG Width=re.right-re.left;
    LONG Height=re.bottom-re.top;

    hMemDc=CreateCompatibleDC(pdeskdc);               //创建截图的内存画板
    hBmp=CreateCompatibleBitmap(pdeskdc,Width,Height);//创建截图的位图对象
    hOldBmp=(HBITMAP)SelectObject(hMemDc,hBmp);

    BitBlt(hMemDc,0,0,re.right-re.left,re.bottom-re.top,
           pdeskdc,0,0,SRCCOPY);//拷贝(桌面窗口的内存画板->截图的内存画板)

    if (cursor)
    {
        POINT po;
        GetCursorPos(&po);                 //获取光标位置
        SetCursor(LoadCursor(NULL, IDC_ARROW));
        HICON hinco = (HICON)GetCursor();  //获取光标图标
        DrawIcon(hMemDc,po.x,po.y,hinco);  //绘制(光标图标->截图的内存画板)
    }

    qt_fromWinHBITMAP(hMemDc,hBmp,Width,Height,image);

    return true;
}

static int qt_fromWinHBITMAP(HDC hdc, HBITMAP bitmap, int w, int h, QImage *pimage)
{
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = w;
    bmi.bmiHeader.biHeight      = -h;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = w * h * 4;

    QImage image(w, h, QImage::Format_ARGB32);
    if (image.isNull())
       return -1;

    // Get bitmap bits
    uchar *data = (uchar *) malloc(bmi.bmiHeader.biSizeImage);

    if (GetDIBits(hdc, bitmap, 0, h, data, &bmi, DIB_RGB_COLORS)) {
        // Create image and copy data into image.
        for (int y=0; y<h; ++y) {
            void *dest = (void *) image.scanLine(y);
            void *src = data + y * image.bytesPerLine();
            memcpy(dest, src, image.bytesPerLine());
        }
    } else {
        qWarning("qt_fromWinHBITMAP(), failed to get bitmap bits");
    }
    free(data);

    *pimage = image;
    return 0;
}
