#include "screenshot.h"

screenshot::screenshot(QMainWindow *parent)
    : QMainWindow(parent)
{
    this->GetImage(&this->image,1);   //获取截图

    this->setWindowTitle("Spaste");
    this->resize(this->image.width(),this->image.height());           //主窗口大小
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);    //this->setWindowOpacity(0.7);//设置透明1-全体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);//设置透明2-窗体标题栏不透明,背景透明

    this->area = new PaintArea(this);
    this->area->setImage(this->image);
    this->setCentralWidget(this->area);
}

screenshot::~screenshot()
{
}

int screenshot::GetImage(QImage *pimage, int cursor)
{
    qDebug()<<"shotcut()"<<shotcut(pimage,cursor)<<endl;
    return 0;
}
