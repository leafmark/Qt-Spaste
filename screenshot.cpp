#include "screenshot.h"

screenshot::screenshot(QMainWindow *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Spaste");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|
                         Qt::Tool| Qt::X11BypassWindowManagerHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true); //设置透明2-窗体标题栏不透明,背景透明
    this->area = new PaintArea(this);
    this->image = new QImage;
}

screenshot::~screenshot()
{
}

bool screenshot::GetImage(QImage *image, bool cursor)
{
    qDebug()<<"shotcut()"<< shotcut(image,cursor)<<endl;
    return true;
}

int screenshot::cut()
{
    this->GetImage(this->image,true);   //获取截图
    qDebug()<<"PaintArea_setImage"<<this->area->setImage(this->image)<<endl;

    this->resize(this->image->width(),this->image->height());  //主窗口大小
    this->setCentralWidget(this->area);
    this->show();
    this->activateWindow();
    return 0;
}
