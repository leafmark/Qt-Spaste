#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    screenshot s;

//    Dialog_set w;
//    w.show();
    QString key = "CTRL+SHIFT+D";
    MyGlobalShortCut *HotKeyId = new MyGlobalShortCut(key,&s);

    return a.exec();
}
