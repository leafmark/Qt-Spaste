#ifndef LINUX_H
#define LINUX_H
#pragma once

#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QImage>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int shotcut(QImage *pimage, int cursor=0);

#endif // LINUX_H
