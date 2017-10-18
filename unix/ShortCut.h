#ifndef SHORTCUT_H
#define SHORTCUT_H
#pragma once

#include <QApplication>
#include <QKeySequence>
#include <QHash>
#include <QAbstractNativeEventFilter>
#include <QDebug>
#include <QX11Info>
#include "screenshot.h"
#include <X11/Xlib.h>
#include <xcb/xcb.h>

static int (*original_x_errhandler)(Display* display, XErrorEvent* event);
static int qxt_x_errhandler(Display* display, XErrorEvent *event);

class MyGlobalShortCut : public QObject
{
public:
    MyGlobalShortCut();
    MyGlobalShortCut(QString key);
    ~MyGlobalShortCut();

    bool registerHotKey();
    bool unregisterHotKey();

    QHash<QPair<quint32, quint32>, MyGlobalShortCut*> shortcuts;
private:
    QKeySequence          m_key;
    Qt::Key               key;
    Qt::KeyboardModifiers mods;
    static quint32 nativeKeycode(Qt::Key keycode);
    static quint32 nativeModifiers(Qt::KeyboardModifiers modifiers);
};

class MyWinEventFilter : public QAbstractNativeEventFilter
{
public:
    MyWinEventFilter(MyGlobalShortCut *shortcut);
    ~MyWinEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:
    MyGlobalShortCut *m_shortcut;
};
#endif // SHORTCUT_H
