#include "paintarea.h"

//构造函数
PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
}

PaintArea::~PaintArea()
{
}

void PaintArea::paint()     //绘图
{
    this->image_paint = this->image_gray;

    if(this->IsSelecting||this->IsSelected)
    {
        //计算选择框 起点、宽、高
        int t;
        int xa = this->lastPoint.x();
        int ya = this->lastPoint.y();
        int xb = this->endPoint.x();
        int yb = this->endPoint.y();
            if (xa==xb) { xb++; }
            if (xa>xb) { t=xa;xa=xb;xb=t; }
            if (ya==yb) { yb++; }
            if (ya>yb) { t=ya;ya=yb;yb=t; }
        int w = xb-xa+1;
        int h = yb-ya+1;

        this->Slx = xa;
        this->Sly = ya;
        this->Slw = w;
        this->Slh = h;

        //绘图选择框图像
        QPainter Rectpaint(&this->image_paint);
            Rectpaint.drawImage(xa,ya,*this->image_color,xa,ya,w,h);

        //绘制选择框
        QPen pen = QPen(Qt::blue);
        QBrush brush = QBrush(Qt::black);
            pen.setWidth(1);
            pen.setColor(Qt::blue);
            pen.setStyle(Qt::SolidLine);
            brush.setColor(Qt::transparent);

            Rectpaint.setPen(pen);
            Rectpaint.setBrush(brush);
            Rectpaint.drawRect(xa-1,ya-1,w+1,h+1);

        //绘制选择框控制点
            this->s1x = xa-3;        this->s1y = ya-3;
            this->s2x = xb-1;        this->s2y = this->s1y;
            this->s3x = this->s1x;   this->s3y = yb-1;
            this->s4x = this->s2x;   this->s4y = this->s3y;

            this->s5x = this->s1x;   this->s5y = ya+h/2-2;
            this->s6x = this->s2x;   this->s6y = this->s5y;
            this->s7x = xa+w/2-2;   this->s7y = this->s1y;
            this->s8x = this->s7x;  this->s8y = this->s3y;

            brush.setColor(Qt::blue);
            Rectpaint.setBrush(brush);
            Rectpaint.drawRect(this->s1x,this->s1y,4,4);
            Rectpaint.drawRect(this->s3x,this->s3y,4,4);
            Rectpaint.drawRect(this->s2x,this->s2y,4,4);
            Rectpaint.drawRect(this->s4x,this->s4y,4,4);
            Rectpaint.drawRect(this->s5x,this->s5y,4,4);
            Rectpaint.drawRect(this->s6x,this->s6y,4,4);
            Rectpaint.drawRect(this->s7x,this->s7y,4,4);
            Rectpaint.drawRect(this->s8x,this->s8y,4,4);
    }
}

void PaintArea::paintEvent(QPaintEvent *)   //重绘事件
{
    this->paint();
    QPainter paint(this);
    paint.drawImage(0,0,this->image_paint);
}

bool PaintArea::setImage(QImage *new_image)   //设置新图片
{
    this->image_color =  new_image;
    this->image_gray  = *new_image;
    this->image_paint = *new_image;

    this->width  = new_image->width();
    this->height = new_image->height();
    this->get_image_gray();

    return true;
}

void PaintArea::get_image_gray()
{
    int byteCount   = this->image_color->byteCount();             //总字节数
    int bytePerLine = this->image_color->bytesPerLine();        //每行字节数
    int bitPerPixel = bytePerLine/this->width;                 //每像素位数
    uchar *colorbit = this->image_color->bits();                //数据指针
    uchar *graybit  = this->image_gray.bits();

    for(int i=0;i<byteCount;i+=bitPerPixel)
    {
        {
            graybit[i+0] = (colorbit[i+0])/1.8;   //B
            graybit[i+1] = (colorbit[i+1])/1.8;   //G
            graybit[i+2] = (colorbit[i+2])/1.8;   //R
            graybit[i+3] = 255;                   //A
        }
    }
}

void PaintArea::save_image()
{
    this->parentWidget()->hide();
    QStringList path = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
    QString fileName = path.join(";")+"/new.png";
            fileName = QFileDialog::getSaveFileName(this,(u8"保存截图"),fileName,
                                                    "PNG(*.png);;JPEG(*.jpg);;BMP(*.bmp)");
    if (!fileName.isNull())
    {
        //保留选择框图像
        QImage Rect = QImage(this->Slw,this->Slh,QImage::Format_ARGB32);

        QPainter paintRect(&Rect);
            paintRect.drawImage(0,0,*this->image_color,
                                this->Slx,this->Sly,this->Slw,this->Slh);

        qDebug()<<"save image:"<<Rect.save(fileName)<<fileName<<endl;
    }
    this->IsSelected  = false;
    this->parentWidget()->close();
}
//*************************************
void PaintArea::mousePressEvent(QMouseEvent *event)     //鼠标按下事件
{
    if(event->button() == Qt::LeftButton)               //当鼠标左键按下
    {
        if(!this->IsSelected)
        {
            this->lastPoint = QCursor::pos();           //获得鼠标指针的当前坐标作为起始坐标
            this->IsSelecting = true;
        }
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)       //鼠标释放事件
{
    if(event->button() == Qt::LeftButton)                     //如果鼠标左键释放
    {
        if(this->IsSelecting)
        {
            this->endPoint = QCursor::pos();
            this->IsSelecting = false;
            this->IsSelected  = true;
            this->update();
        }
    }
    if(event->button() == Qt::RightButton)                    //当鼠标右键释放
    {
        if(this->IsSelected)
        {
            this->IsSelected = false;
            this->update();
        } else {
            this->parentWidget()->close();
        }
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)      //鼠标移动事件
{
    if(event->buttons()&Qt::LeftButton)                 //如果鼠标左键按着的同时移动鼠标
     {
        if(this->IsSelecting)
        {
             this->endPoint = QCursor::pos();           //获得鼠标指针的当前坐标作为终止坐标
             this->update();
        }
     }
}

void PaintArea::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event)
    if(this->IsSelected)
    {
        this->save_image();
    }
}
