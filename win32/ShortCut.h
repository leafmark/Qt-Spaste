#ifndef SHORTCUT_H
#define SHORTCUT_H
#pragma once

#include <QApplication>
#include <QKeySequence>
#include <QHash>
#include <QAbstractNativeEventFilter>
#include <QDebug>
#include <windows.h>
#include <comdef.h>
#include "screenshot.h"

class MyWinEventFilter;
class MyGlobalShortCut;

class MyGlobalShortCut : public QObject
{
    Q_OBJECT
public:
    MyGlobalShortCut(QString key, screenshot app);
    ~MyGlobalShortCut();

    void activateShortcut();
    bool registerHotKey();
    bool unregisterHotKey();

    QHash<QPair<quint32, quint32>, MyGlobalShortCut*> shortcuts;
private:
    screenshot app;
    QApplication *m_app;
    MyWinEventFilter *m_filter;
    QKeySequence m_key;
    Qt::Key key;
    Qt::KeyboardModifiers mods;
    static quint32 nativeKeycode(Qt::Key keycode);
    static quint32 nativeModifiers(Qt::KeyboardModifiers modifiers);

protected:
signals:
public slots:
};

class MyWinEventFilter : public QAbstractNativeEventFilter
{
public:
    MyWinEventFilter(MyGlobalShortCut *shortcut);
    ~MyWinEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);
private:
    MyGlobalShortCut *m_shortcut;
};

#endif // SHORTCUT_H
