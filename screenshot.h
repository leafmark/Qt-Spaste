#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#pragma once

#include <QApplication>
#include <QMainWindow>

#ifdef WIN32
#include "./win32/getimage.h"
#endif

#ifdef unix
#include "./unix/getimage.h"
#endif

#include "paintarea.h"

class screenshot : public QMainWindow
{
    Q_OBJECT

public:
    screenshot(QMainWindow *parent = 0);
    ~screenshot();

    QImage       image;
    PaintArea    *area;                //画布指针

    int GetImage(QImage *pimage,int cursor=0);

//public slots:
//signals:
};

#endif // SCREENSHOT_H

