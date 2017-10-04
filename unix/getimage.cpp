#include "./unix/getimage.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shotcut(QImage *pimage,int cursor)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    *pimage = screen->grabWindow(0).toImage();
    qDebug()<<"pimage->width()"<<pimage->width()<<endl;
    qDebug()<<"pimage->height()"<<pimage->height()<<endl;
/*
    Window	desktop;
    Display * dsp;
    XImage	* img;

    int	screen_width;
    int	screen_height;

    dsp = XOpenDisplay(NULL);
    if ( NULL == dsp )
    {
        qDebug()<<"CaptureDesktop , Cannot connect to local display"<<endl;
        return(-1);
    }

    desktop = RootWindow( dsp, 0 ); // Refer to the root window
    if ( 0 == desktop )
    {
        qDebug()<<"CaptureDesktop , cannot get root window"<<endl;
        return(-1);
    }
    screen_width	= DisplayWidth( dsp, 0 );
    screen_height	= DisplayHeight( dsp, 0 );

    //Get the Image of the root window
    img = XGetImage( dsp, desktop, 0, 0, screen_width, screen_height, ~0, ZPixmap );

    XDestroyImage( img );
    XCloseDisplay( dsp );
*/
    return 0;
}
