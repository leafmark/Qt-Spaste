#ifndef MAIN_H
#define MAIN_H
#pragma once

#include <QApplication>
#include "dialog_set.h"

#ifdef WIN32
#include "./win32/ShortCut.h"
#endif

#ifdef unix
#include "./unix/ShortCut.h"
#endif

#endif // MAIN_H
