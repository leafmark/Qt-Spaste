#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#pragma once

#include <QApplication>
#include <QMainWindow>
#include "paintarea.h"

#ifdef WIN32
#include <Windows.h>
#include "./win32/getimage.h"
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
    PaintArea    area;                //画布

    int shot();
    bool GetImage(QImage *image,bool cursor=true);

protected:
signals:
public slots:
};

#endif // SCREENSHOT_H

