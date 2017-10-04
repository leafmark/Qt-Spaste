
#include <QApplication>
#include "screenshot.h"
#include "dialog_set.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    screenshot s;
    s.show();

//    Dialog_set w;
//    w.show();

    return a.exec();
}
