#ifndef PAINTAREA_H
#define PAINTAREA_H
#pragma once

#include <QApplication>
#include <QWidget>
#include <QMouseEvent>       //鼠标事件头文件
#include <QPoint>            //坐标头文件
#include <QPainter>          //绘图头文件
#include "QDebug"
#include <QFileDialog>          //文件对话框头文件
#include <QStandardPaths>

class PaintArea : public QWidget
{
    Q_OBJECT

public:
    explicit PaintArea(QWidget *parent = 0);
    ~PaintArea();

public:
    bool setImage(QImage *new_image);               //设置新图片
    void get_image_gray();                          //灰度图片
    void save_image();                              //保存图片

protected:
    void paint();                                    //绘图事件
    void paintEvent(QPaintEvent *);                  //重绘事件

    void mousePressEvent(QMouseEvent *);             //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);           //鼠标释放事件
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *);              //鼠标移动事件

private:
    QImage *image_color;                 //彩图
    QImage *image_gray;                  //灰度图
    QImage *image_paint;                 //画布图

    int width,height;
    QPoint lastPoint,endPoint;               //定义两个坐标对象存放鼠标指针的前后两个坐标
    bool IsSelecting=false;                     //是否正在选择区域
    bool IsSelected=false;                    //是否已选中区域

    int Selectx;
    int Selecty;
    int Selectw;
    int Selecth;

    int s1x,s1y;
    int s2x,s2y;
    int s3x,s3y;
    int s4x,s4y;
    int s5x,s5y;
    int s6x,s6y;
    int s7x,s7y;
    int s8x,s8y;

signals:

public slots:
};

#endif // PAINTAREA_H
