#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#pragma once

#include <QApplication>
#include <QMainWindow>
#include "paintarea.h"

#ifdef WIN32
#include "./win32/getimage.h"
#include <Windows.h>
#endif

#ifdef unix
#include "./unix/getimage.h"
#endif

class screenshot : public QMainWindow
{
    Q_OBJECT

public:
    screenshot(QMainWindow *parent = 0);
    ~screenshot();

    QImage       image;
    PaintArea    *area;                //画布指针

    int cut();
    int GetImage(QImage *pimage,int cursor=0);

protected:
signals:
public slots:
};

#endif // SCREENSHOT_H

