#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog_set w;
    w.showMinimized();

    QString key = "CTRL+SHIFT+D";
    MyGlobalShortCut *HotKeyId = new MyGlobalShortCut(key);

    MyWinEventFilter filter(HotKeyId);
    a.installNativeEventFilter(&filter);

    return a.exec();
}
